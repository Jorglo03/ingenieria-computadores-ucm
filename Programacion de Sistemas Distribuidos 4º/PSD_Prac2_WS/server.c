#include "server.h"

/** Flag to enable debugging */
#define DEBUG_SERVER 1

/** Array with games */
tGame games[MAX_GAMES];

/** Mutex to protect the game status field in the array of games */
pthread_mutex_t mutexStatusArray;


void initServerStructures (){

    if (DEBUG_SERVER)
        printf ("Initializing...\n");

    // Init seed
    srand (time(NULL));

    // Init each game
    for (int i=0; i<MAX_GAMES; i++){

        // Allocate and init board
        games[i].board = (xsd__string) malloc (BOARD_WIDTH*BOARD_HEIGHT);
        initBoard (games[i].board);

        // Calculate the first player to play
        if ((rand()%2)==0)
            games[i].currentPlayer = player1;
        else
            games[i].currentPlayer = player2;

        // Allocate and init player names
        games[i].player1Name = (xsd__string) malloc (STRING_LENGTH);
        games[i].player2Name = (xsd__string) malloc (STRING_LENGTH);
        memset (games[i].player1Name, 0, STRING_LENGTH);
        memset (games[i].player2Name, 0, STRING_LENGTH);

        // Game status
        games[i].endOfGame = FALSE;
        games[i].status = gameEmpty;

        // Init mutex and cond variable
        pthread_mutex_init(&games[i].gameMutex, NULL);
        pthread_cond_init(&games[i].playerTurnCond, NULL);
    }
}

conecta4ns__tPlayer switchPlayer (conecta4ns__tPlayer currentPlayer){
    return (currentPlayer == player1) ? player2 : player1;
}

int searchEmptyGame (){
	
    for (int i = 0; i < MAX_GAMES; i++) {
        if (games[i].status == gameEmpty || games[i].status == gameWaitingPlayer) {
            return i; // Found an empty game
        }
    }
    return ERROR_SERVER_FULL; // No empty game found
	
}

int checkPlayer (xsd__string playerName, int gameId){
	
	if (strcmp(playerName, games[gameId].player1Name) == 0)
        return TRUE;
    if (strcmp(playerName, games[gameId].player2Name) == 0)
        return TRUE;
        
    return FALSE;
  
}

void freeGameByIndex (int index){
	
	if (index < 0 || index >= MAX_GAMES) {
        fprintf(stderr, "Invalid game index: %d\n", index);
        return;
    }
    
	pthread_mutex_lock(&mutexStatusArray);

    // Init board
	initBoard (games[index].board);

	// Calculate the first player to play
	if ((rand()%2)==0)
		games[index].currentPlayer = player1;
	else
		games[index].currentPlayer = player2;

	// Init player names
	memset (games[index].player1Name, 0, STRING_LENGTH);
	memset (games[index].player2Name, 0, STRING_LENGTH);

	// Game status
	games[index].endOfGame = FALSE;
	games[index].status = gameEmpty;

	// Init mutex and cond variable
	pthread_mutex_init(&games[index].gameMutex, NULL);
	pthread_cond_init(&games[index].playerTurnCond, NULL);

    pthread_mutex_unlock(&mutexStatusArray);
	
}

void copyGameStatusStructure (conecta4ns__tBlock* status, char* message, xsd__string board, int newCode){
    
    // Set the new code
    status->code = newCode;
    
    // Copy the message
    memset((status->msgStruct).msg, 0, STRING_LENGTH);
    strcpy ((status->msgStruct).msg, message);
    (status->msgStruct).__size = strlen ((status->msgStruct).msg) + 1;	//+1 por el caracter nulo
    status->msgStruct.msg[status->msgStruct.__size-1] = '\0';	//Caracter nulo

    // Copy the board, only if it is not NULL
    if (board == NULL){
        status->board = NULL;
        status->__size = 0;
    }
    else{
        strncpy (status->board, board, BOARD_WIDTH*BOARD_HEIGHT);
        status->__size = BOARD_WIDTH*BOARD_HEIGHT;
    }
}

int conecta4ns__register(struct soap *soap, conecta4ns__tMessage playerName, int *code) {
    int gameIndex = -1;

    // Set \0 at the end of the string
    playerName.msg[playerName.__size] = 0;

    if (DEBUG_SERVER)
        printf("[Register] Registering player -> [%s]\n", playerName.msg);

    // Buscar una partida vacía o con un hueco para un segundo jugador
    pthread_mutex_lock(&mutexStatusArray); // Protege la región crítica que accede al array de partidas
    gameIndex = searchEmptyGame(); // Busca una partida vacía o con un solo jugador
    pthread_mutex_unlock(&mutexStatusArray);

    // Verificar si el servidor está lleno (no hay partida con espacio disponible)
    if (gameIndex < 0) {
        *code = ERROR_SERVER_FULL;
        if (DEBUG_SERVER)
            printf("[Register] Server full, no empty games available.\n");
        return SOAP_OK;
    }

    // Bloquear el acceso exclusivo a la partida seleccionada
    pthread_mutex_lock(&games[gameIndex].gameMutex);

    // Verificar si el nombre del jugador ya está registrado en la partida
    if (checkPlayer (playerName.msg, gameIndex)) {
        *code = ERROR_PLAYER_REPEATED;
        pthread_mutex_unlock(&games[gameIndex].gameMutex);
        if (DEBUG_SERVER)
            printf("[Register] Player [%s] already registered in this game.\n", playerName.msg);
        return SOAP_OK;
    }

    // Registrar el jugador en la partida
    if (games[gameIndex].status == gameEmpty) {
        strcpy(games[gameIndex].player1Name, playerName.msg);
        games[gameIndex].status = gameWaitingPlayer;
        printf("Player 1 (%s) registered in game %d.\n", playerName.msg, gameIndex+1);

        // Esperar hasta que se registre el segundo jugador
        while (games[gameIndex].status == gameWaitingPlayer) {
            if (DEBUG_SERVER)
                printf("[Register] Waiting for second player to register in game %d.\n", gameIndex+1);
            pthread_cond_wait(&games[gameIndex].playerTurnCond, &games[gameIndex].gameMutex);
        }

    } else if (games[gameIndex].status == gameWaitingPlayer) {
        strcpy(games[gameIndex].player2Name, playerName.msg);
        games[gameIndex].status = gameReady;
        printf("Player 2 (%s) registered in game %d.\n", playerName.msg, gameIndex+1);

        // Notificar al primer jugador que está listo para empezar
        pthread_cond_signal(&games[gameIndex].playerTurnCond);
    }

    // Registrar exitosamente, devolver el índice de la partida como el código
    *code = gameIndex;

    // Desbloquear acceso a la partida
    pthread_mutex_unlock(&games[gameIndex].gameMutex);

    return SOAP_OK;
}



int conecta4ns__getStatus(struct soap *soap, conecta4ns__tMessage playerName, int gameId, conecta4ns__tBlock* status) {
    
    char messageToPlayer[STRING_LENGTH];

    // Set \0 at the end of the string and alloc memory for the status
    playerName.msg[playerName.__size] = 0;
    allocClearBlock(soap, status);

    if (DEBUG_SERVER)
		printf ("[Status] Receiving getStatus() request from -> %s [%d] in game %d\n", playerName.msg, playerName.__size, gameId+1);

    // Validar ID de partida
    if (gameId < 0 || gameId >= MAX_GAMES || games[gameId].status == gameEmpty) {
        strcpy(messageToPlayer, "Error: ID de partida incorrecto.");
        copyGameStatusStructure(status, messageToPlayer, status->board, ERROR_WRONG_GAMEID);
        if (DEBUG_SERVER)
            printf("[Status] Game ID %d is invalid.\n", gameId+1);
        return SOAP_OK;
    }

    // Bloquear acceso a la partida
    pthread_mutex_lock(&games[gameId].gameMutex);

    // Verificar si el jugador pertenece a la partida
    if (strcmp(games[gameId].player1Name, playerName.msg) != 0 && strcmp(games[gameId].player2Name, playerName.msg) != 0) {
        strcpy(messageToPlayer, "Error: Jugador no encontrado en esta partida.");
        copyGameStatusStructure(status, messageToPlayer, games[gameId].board, ERROR_PLAYER_NOT_FOUND);
        pthread_mutex_unlock(&games[gameId].gameMutex);
        if (DEBUG_SERVER)
            printf("[Status] Player [%s] not found in game %d.\n", playerName.msg, gameId+1);
        return SOAP_OK;
    }

    // Esperar hasta que sea el turno del jugador
    while (((strcmp(playerName.msg, games[gameId].player1Name) == 0 && games[gameId].currentPlayer != player1) ||
           (strcmp(playerName.msg, games[gameId].player2Name) == 0 && games[gameId].currentPlayer != player2)) &&
           !games[gameId].endOfGame) {
		if (DEBUG_SERVER)
			printf("[Status] Waiting for player [%s] to take their turn in game %d...\n", playerName.msg, gameId+1);

        pthread_cond_wait(&games[gameId].playerTurnCond, &games[gameId].gameMutex);
    }

    // Verificar si la partida ha terminado
    if (games[gameId].endOfGame) {
        if (isBoardFull(games[gameId].board)) {
            strcpy(messageToPlayer, "Game over.");
            copyGameStatusStructure(status, messageToPlayer, games[gameId].board, GAMEOVER_DRAW);
        } else {
            strcpy(messageToPlayer, "Game over. The opponent wins.");
            copyGameStatusStructure(status, messageToPlayer, games[gameId].board, GAMEOVER_LOSE);
        }
        freeGameByIndex(gameId);
    } else {
        // Si la partida no ha terminado, determinar si es el turno del jugador o no
		if (games[gameId].currentPlayer == player1 && strcmp(playerName.msg, games[gameId].player1Name) == 0) {
			// Jugador 1, con su ficha
			sprintf(messageToPlayer, "It's your turn. You play with: %c", PLAYER_1_CHIP);
			copyGameStatusStructure(status, messageToPlayer, games[gameId].board, TURN_MOVE);
		} else if (games[gameId].currentPlayer == player2 && strcmp(playerName.msg, games[gameId].player2Name) == 0) {
			// Jugador 2, con su ficha
			sprintf(messageToPlayer, "It's your turn. You play with: %c", PLAYER_2_CHIP);
			copyGameStatusStructure(status, messageToPlayer, games[gameId].board, TURN_MOVE);
		} else {
			// Esperando al oponente, mostrando su ficha también
			sprintf(messageToPlayer, "Your rival is thinking... please, wait! You play with: %c", 
					(games[gameId].currentPlayer == player1) ? PLAYER_1_CHIP : PLAYER_2_CHIP);
			copyGameStatusStructure(status, messageToPlayer, games[gameId].board, TURN_WAIT);
		}
    }
    // Desbloquear acceso a la partida
    pthread_mutex_unlock(&games[gameId].gameMutex);

    
    return SOAP_OK;
}


int conecta4ns__insertChip (struct soap *soap, conecta4ns__tMessage playerName, int gameId, unsigned int playerMove, conecta4ns__tBlock* status) {
    char messageToPlayer[STRING_LENGTH];

    // Terminar la cadena del nombre del jugador con '\0'
    playerName.msg[playerName.__size] = 0;

    // Asignar memoria para la estructura de estado
    allocClearBlock(soap, status);

    // Validar ID del juego
    if (gameId < 0 || gameId >= MAX_GAMES) {
        strcpy(messageToPlayer, "Invalid game ID.");
        copyGameStatusStructure(status, messageToPlayer, NULL, ERROR_WRONG_GAMEID);
        return SOAP_OK;
    }

    // Bloquear el acceso concurrente al juego
    pthread_mutex_lock(&games[gameId].gameMutex);

    // Verificar si el jugador está registrado en el juego
    int playerId = checkPlayer(playerName.msg, gameId);
    if (playerId == -1) {
        strcpy(messageToPlayer, "Player not found in this game.");
        copyGameStatusStructure(status, messageToPlayer, NULL, ERROR_PLAYER_NOT_FOUND);
        pthread_mutex_unlock(&games[gameId].gameMutex);
        return SOAP_OK;
    }

    // Verificar si es el turno del jugador
	if ((games[gameId].currentPlayer == 0 && strcmp(playerName.msg, games[gameId].player1Name) != 0) ||
		(games[gameId].currentPlayer == 1 && strcmp(playerName.msg, games[gameId].player2Name) != 0)) {
		strcpy(messageToPlayer, "It is not your turn.");
		copyGameStatusStructure(status, messageToPlayer, games[gameId].board, TURN_WAIT);
		pthread_mutex_unlock(&games[gameId].gameMutex);
		return SOAP_OK;
	}

    // Verificar si el movimiento es válido (columna llena o no)
    conecta4ns__tMove moveResult = checkMove(games[gameId].board, playerMove);
    if (moveResult == fullColumn_move) {
        strcpy(messageToPlayer, "Column is full.");
        copyGameStatusStructure(status, messageToPlayer, games[gameId].board, -1);
        pthread_mutex_unlock(&games[gameId].gameMutex);
        return SOAP_OK;
    }

    // Insertar la ficha en el tablero
    insertChip(games[gameId].board, games[gameId].currentPlayer, playerMove);
	if (DEBUG_SERVER) {
        printf("[Insert Chip] Player %s inserted a chip into column %d in game %d.\n", playerName.msg, playerMove, gameId+1);
    }
    
    // Verificar si el jugador ha ganado
    if (checkWinner(games[gameId].board, games[gameId].currentPlayer)) {
        games[gameId].endOfGame = TRUE;
        pthread_cond_signal(&games[gameId].playerTurnCond);
        strcpy(messageToPlayer, "Fantastic move! You've won the game!");
        copyGameStatusStructure(status, messageToPlayer, games[gameId].board, GAMEOVER_WIN);
        pthread_mutex_unlock(&games[gameId].gameMutex);
        if (DEBUG_SERVER) {
            printf("[Insert Chip] Player %s has won the game %d.\n", playerName.msg, gameId+1);
        }
        return SOAP_OK;
    }

    // Verificar si el tablero está lleno (empate)
    if (isBoardFull(games[gameId].board)) {
        games[gameId].endOfGame = TRUE;
        pthread_cond_signal(&games[gameId].playerTurnCond);
        strcpy(messageToPlayer, "You have draw.");
        copyGameStatusStructure(status, messageToPlayer, games[gameId].board, GAMEOVER_DRAW);
        pthread_mutex_unlock(&games[gameId].gameMutex);
        if (DEBUG_SERVER) {
            printf("[Insert Chip] Game %d is a draw.\n", gameId+1);
        }
        return SOAP_OK;
    }

    // Cambiar el turno al siguiente jugador
    games[gameId].currentPlayer = switchPlayer(games[gameId].currentPlayer);
	pthread_cond_signal(&games[gameId].playerTurnCond);
	
    sprintf(messageToPlayer, "Your rival is thinking... please, wait! You play with: %c", 			//Se cambian los chips para que aparezcan correctamente
					(games[gameId].currentPlayer == player1) ? PLAYER_2_CHIP : PLAYER_1_CHIP);
			copyGameStatusStructure(status, messageToPlayer, games[gameId].board, TURN_WAIT);

    // Desbloquear el mutex del juego
    pthread_mutex_unlock(&games[gameId].gameMutex);

    return SOAP_OK;
}


void *processRequest(void *soap){

	pthread_detach(pthread_self());

	if (DEBUG_SERVER)
		printf ("Processing a new request...\n");

	soap_serve((struct soap*)soap);
	soap_destroy((struct soap*)soap);
	soap_end((struct soap*)soap);
	soap_done((struct soap*)soap);
	free(soap);

	return NULL;
}

int main(int argc, char **argv){ 

	struct soap soap;
	struct soap *tsoap;
	pthread_t tid;
	int port;
	SOAP_SOCKET m, s;

		// Init soap environment
		soap_init(&soap);

		// Configure timeouts
		soap.send_timeout = 60; // 60 seconds
		soap.recv_timeout = 60; // 60 seconds
		soap.accept_timeout = 3600; // server stops after 1 hour of inactivity
		soap.max_keep_alive = 100; // max keep-alive sequence

		initServerStructures();
        pthread_mutex_init(&mutexStatusArray, NULL);

		// Get listening port
		port = atoi(argv[1]);

		// Bind
		m = soap_bind(&soap, NULL, port, 100);

		if (!soap_valid_socket(m)){
			exit(1);
		}

		printf("Server is ON ...\n");

		while (TRUE){

			// Accept a new connection
			s = soap_accept(&soap);

			// Socket is not valid :(
			if (!soap_valid_socket(s)){

				if (soap.errnum){
					soap_print_fault(&soap, stderr);
					exit(1);
				}

				fprintf(stderr, "Time out!\n");
				break;
			}

			// Copy the SOAP environment
			tsoap = soap_copy(&soap);

			if (!tsoap){
				printf ("SOAP copy error!\n");
				break;
			}

			// Create a new thread to process the request
			pthread_create(&tid, NULL, (void*(*)(void*))processRequest, (void*)tsoap);
		}

	// Detach SOAP environment
	soap_done(&soap);
	return 0;
}
