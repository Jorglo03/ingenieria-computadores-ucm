#include "serverGame.h"

int num_ganadores = 0;
char ganadores[MAX_WINNERS][STRING_LENGTH];
char perdedores[MAX_WINNERS][STRING_LENGTH];
pthread_mutex_t mutex;

void sendMessageToPlayer (int socketClient, char* message){
	
	unsigned int l = strlen(message);
	int charsToSend = send(socketClient, &l, sizeof(l), 0); 
	if(charsToSend < 0) showError("ERROR while receiveing the number of chars to send");	

	
	int messageLength = send(socketClient, message, strlen(message), 0); 
	
	// Check bytes sent 
	if (messageLength < 0) showError("ERROR while sending message to player"); 
}

void receiveMessageFromPlayer (int socketClient, char* message){
	
	memset(message, 0, STRING_LENGTH);
	
	unsigned int l;
	int charsToRead = recv(socketClient, &l, sizeof(l), 0);
	if(charsToRead < 0) showError("ERROR while receiveing the number of chars to read");	
	
	int messageLength = recv(socketClient, message, l, 0); 
	// Check read bytes 
	if (messageLength < 0) showError("ERROR while receiving message from player"); 

}

void sendCodeToClient (int socketClient, unsigned int code){

	int messageLength = send(socketClient, &code, sizeof(code), 0); 
	
	// Check bytes sent 
	if (messageLength < 0) showError("ERROR while sending code to player"); 
	
}

void sendBoardToClient (int socketClient, tBoard board){

	int messageLength = send(socketClient, board, BOARD_HEIGHT * BOARD_WIDTH, 0); 
	
	// Check bytes sent 
	if (messageLength < 0) showError("ERROR while sending board to player"); 

}

unsigned int receiveMoveFromPlayer (int socketClient){
	
	unsigned int move;
	int msgLength = recv(socketClient, &move, sizeof(move), 0); 
	
	// Check bytes read 
	if (msgLength < 0) showError("ERROR while receiving move from player"); 
	
	return move;
}

int getSocketPlayer (tPlayer player, int player1socket, int player2socket){

	int socket;

		if (player == player1)
			socket = player1socket;
		else
			socket = player2socket;

	return socket;
}

tPlayer switchPlayer (tPlayer currentPlayer){

	tPlayer nextPlayer;

		if (currentPlayer == player1)
			nextPlayer = player2;
		else
			nextPlayer = player1;

	return nextPlayer;
}

void switchChips(char *chip1, char *chip2){
		char aux = *chip1;
		*chip1 = *chip2;
		*chip2 = aux;
}

void sendMoveResultToClient(int socketClient, tMove move){
	
	int messageLength = send(socketClient, &move, sizeof(move), 0); 
	
	// Check bytes sent 
	if (messageLength < 0) showError("ERROR while sending move result to player"); 
	
}


void writeFile(char* nombreGanador, char* nombrePerdedor){
	
	pthread_mutex_lock(&mutex);
	
	if(num_ganadores == MAX_WINNERS){
		int i;
		for(i =  MAX_WINNERS - 1; i > 0; i--){
			size_t longestLengthWinners = (strlen(ganadores[i-1]) > strlen(ganadores[i])) ? strlen(ganadores[i-1]) : strlen(ganadores[i]);
			size_t longestLengthLosers = (strlen(perdedores[i-1]) > strlen(perdedores[i])) ? strlen(perdedores[i-1]) : strlen(perdedores[i]);
			strncpy(ganadores[i], ganadores[i-1], longestLengthWinners);
			strncpy(perdedores[i], perdedores[i-1], longestLengthLosers);
		}
	}
	else{
		num_ganadores++;
		int i;
		for(i =  num_ganadores - 1; i > 0; i--){
			size_t longestLengthWinners = (strlen(ganadores[i-1]) > strlen(ganadores[i])) ? strlen(ganadores[i-1]) : strlen(ganadores[i]);
			size_t longestLengthLosers = (strlen(perdedores[i-1]) > strlen(perdedores[i])) ? strlen(perdedores[i-1]) : strlen(perdedores[i]);
			strncpy(ganadores[i], ganadores[i-1], longestLengthWinners);
			strncpy(perdedores[i], perdedores[i-1], longestLengthLosers);
		}
	}
	
	memset(ganadores[0], 0, sizeof(ganadores[0]));
	memset(perdedores[0], 0, sizeof(perdedores[0]));


	strncpy(ganadores[0], nombreGanador, strlen(nombreGanador));
	strncpy(perdedores[0], nombrePerdedor, strlen(nombrePerdedor));

	
	FILE* f = fopen(FILE_NAME, "w");

	if(f == NULL){
		showError("ERROR wile opening txt file");
		
	}

	int i;
	for(i = 0; i < num_ganadores; i++){
			fprintf(f,"%d-Ganador: %s --- Perdedor: %s\n", i + 1, ganadores[i], perdedores[i]);
	}
	
	fclose(f);

	pthread_mutex_unlock(&mutex);

}

void *threadProcessing(void *arg){

	tMove moveResult;					/** Result of player's move */
	tBoard board;						/** Board of the game */
	tString message;					/** Message sent to the players */
	unsigned int column;				/** Selected column to insert the chip */
	int endOfGame = FALSE;				/** Flag to control the end of the game*/
	tPlayer currentPlayer;				/** Current player */
	int random = rand() % 2;
	int partida;
	tString nombreGanador;
	tString nombrePerdedor;
	int empate = 0;
	
	if(random == 0) currentPlayer = player1;
		
	else currentPlayer = player2;
		
		
	struct ThreadArgs *threadArgs = (struct ThreadArgs*) arg;
	initBoard(board);
	// Detach resources
	pthread_detach(pthread_self()) ;

	// Get client socket from thread param
	int socketPlayer1 = threadArgs->socketPlayer1;
	int socketPlayer2 = threadArgs->socketPlayer2;
	char chip_currentPlayer;
	char chip_waitingPlayer;
	partida = threadArgs->partida;

	
	if(currentPlayer == player1){
		chip_currentPlayer = PLAYER_1_CHIP;
		chip_waitingPlayer = PLAYER_2_CHIP;
	}
	else{
		chip_currentPlayer = PLAYER_2_CHIP;
		chip_waitingPlayer = PLAYER_1_CHIP;
	}
	while(!endOfGame){
			
			int currentSocket = getSocketPlayer(currentPlayer, socketPlayer1, socketPlayer2);
			int waitingSocket = getSocketPlayer(!currentPlayer, socketPlayer1, socketPlayer2);
			
			sendCodeToClient(currentSocket, TURN_MOVE);
			sendCodeToClient(waitingSocket, TURN_WAIT);
			
			sprintf(message, "Its your turn. You play with:%c\n", chip_currentPlayer);
			sendMessageToPlayer(currentSocket, message);
			sprintf(message, "Your rival is thinking... please, wait! You play with:%c\n", chip_waitingPlayer);
			sendMessageToPlayer(waitingSocket, message);
			
			sendBoardToClient(currentSocket, board);
			sendBoardToClient(waitingSocket, board);
				
			do{
				column = receiveMoveFromPlayer(currentSocket);
				moveResult = checkMove(board, column);
				sendMoveResultToClient(currentSocket, moveResult);
				
			}while(moveResult != OK_move);
			
			insertChip(board, currentPlayer, column);
				
			if(checkWinner(board, currentPlayer)){
				
				sendCodeToClient(currentSocket, GAMEOVER_WIN); //Avisamos de fin de partida
				sendCodeToClient(waitingSocket, GAMEOVER_LOSE);
				
				sendBoardToClient(currentSocket, board);
				sendBoardToClient(waitingSocket, board);
				
				endOfGame = TRUE;
			}
			else if(isBoardFull(board)){
				
				sendCodeToClient(currentSocket, GAMEOVER_DRAW); //end of game
				sendCodeToClient(waitingSocket, GAMEOVER_DRAW);
				
				sendBoardToClient(currentSocket, board);
				sendBoardToClient(waitingSocket, board);
				
				empate = 1;
				endOfGame = TRUE;
			}
						
			currentPlayer = switchPlayer(currentPlayer);
			switchChips(&chip_currentPlayer, &chip_waitingPlayer);
			
		}
	
	if(currentPlayer == player1){ //cambian despues de acabar la partida por eso esto
		strncpy(nombreGanador, threadArgs->namePlayer2, STRING_LENGTH);
		strncpy(nombrePerdedor, threadArgs->namePlayer1, STRING_LENGTH);
	}
	else{
		strncpy(nombreGanador, threadArgs->namePlayer1, STRING_LENGTH);
		strncpy(nombrePerdedor, threadArgs->namePlayer2,  STRING_LENGTH);

	}
	if(!empate)
		writeFile(nombreGanador, nombrePerdedor);
	
	printf("Partida %d finalizada!\n", partida + 1);
	
	free(arg);
	close(socketPlayer1);
	close(socketPlayer2);
	
	free(threadArgs->namePlayer1);
	free(threadArgs->namePlayer2);
	pthread_exit(0);
	
}



int main(int argc, char *argv[]){

	int socketfd;						/** Socket descriptor */
	struct sockaddr_in serverAddress;	/** Server address structure */
	unsigned int port;					/** Listening port */
	struct sockaddr_in player1Address;	/** Client address structure for player 1 */
	struct sockaddr_in player2Address;	/** Client address structure for player 2 */
	int socketPlayer1, socketPlayer2;	/** Socket descriptor for each player */
	unsigned int clientLength;			/** Length of client structure */

	tString player1Name;				/** Name of player 1 */
	tString player2Name;				/** Name of player 2 */

	pthread_mutex_init(&mutex, NULL);

		// Check arguments
		if (argc != 2) {
			fprintf(stderr,"ERROR wrong number of arguments\n");
			fprintf(stderr,"Usage:\n$>%s port\n", argv[0]);
			exit(1);
		}

		// Init seed
		srand(time(NULL));

		// Create the socket
		socketfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		// Check
		if (socketfd < 0)
			showError("ERROR while opening socket");

		// Init server structure
		memset(&serverAddress, 0, sizeof(serverAddress));

		// Get listening port
		port = atoi(argv[1]);

		// Fill server structure
		serverAddress.sin_family = AF_INET; 
		serverAddress.sin_addr.s_addr = htonl(INADDR_ANY); 
		serverAddress.sin_port = htons(port); 

		// Bind
		if (bind(socketfd,  (struct sockaddr *) &serverAddress,  sizeof(serverAddress)) < 0) 
			showError("ERROR while binding");

		// Listen	
		listen(socketfd, 10);
		
		
		int i = 0;
		while(1){
			//Accept 
			clientLength = sizeof(player1Address); 
			socketPlayer1  = accept(socketfd,  (struct sockaddr  *)  &player1Address, &clientLength);
			socketPlayer2  = accept(socketfd,  (struct sockaddr  *)  &player2Address, &clientLength);
			
			if (socketPlayer1 < 0) showError("ERROR while accepting player 1");
			
			if (socketPlayer2 < 0) showError("ERROR while accepting player 2");
			
			printf("Clientes de la partida %d conectados\n", i + 1);
			
			receiveMessageFromPlayer(socketPlayer1, player1Name);
			receiveMessageFromPlayer(socketPlayer2, player2Name);
			printf("Name of player 1 received: %s\n", player1Name);
			printf("Name of player 2 received: %s\n", player2Name);

			
			sendMessageToPlayer(socketPlayer1, player2Name);
			sendMessageToPlayer(socketPlayer2, player1Name);
			
			
			struct ThreadArgs *threadArgs;
			// Allocate memory
			if ((threadArgs = malloc(sizeof(struct ThreadArgs))) == NULL)
				showError("Error while allocating memory");
			
			threadArgs->socketPlayer1 = socketPlayer1;
			threadArgs->socketPlayer2 = socketPlayer2;
			threadArgs->partida = i;
			threadArgs->namePlayer1 = strdup(player1Name);
			threadArgs->namePlayer2 = strdup(player2Name);
			
			
			pthread_t threadID;
			
			if(pthread_create(&threadID, NULL, threadProcessing, (void*)threadArgs) != 0)
				showError("pthread_create() failed");
			
			i++;
				
		}
		
		close(socketfd);

}
