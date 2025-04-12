#include "client.h"

#define DEBUG_CLIENT 1


unsigned int readMove (){

	xsd__string enteredMove;
	unsigned int move;
	unsigned int isRightMove;

		// Init...
		enteredMove = (xsd__string) malloc (STRING_LENGTH);
		memset (enteredMove, 0, STRING_LENGTH);
		isRightMove = FALSE;
		move = STRING_LENGTH;

		while (!isRightMove){

			printf ("Enter a move [0-%d]:", BOARD_WIDTH-1);

			// Read move
			fgets (enteredMove, STRING_LENGTH-1, stdin);

			// Remove new-line char
			enteredMove[strlen(enteredMove)-1] = 0;

			// Length of entered move is not correct
			if (strlen(enteredMove) != 1){
				printf ("Entered move is not correct. It must be a number in the interval [0-%d]\n", BOARD_WIDTH-1);
			}

			// Check if entered move is a number
			else if (isdigit(enteredMove[0])){

				// Convert move to an int
				move =  enteredMove[0] - '0';

				if (move >= BOARD_WIDTH)
					printf ("Entered move is not correct. It must be a number in the interval [0-%d]\n", BOARD_WIDTH-1);
				else
					isRightMove = TRUE;
			}

			// Entered move is not a number
			else
				printf ("Entered move is not correct. It must be a number in the interval [0-%d]\n", BOARD_WIDTH-1);
		}

	return move;
}


int main(int argc, char **argv){

	struct soap soap;					/** Soap struct */
	char *serverURL;					/** Server URL */
	unsigned int endOfGame;				/** Flag to control the end of the game */
	conecta4ns__tMessage playerName;	/** Player name */
	conecta4ns__tBlock gameStatus;		/** Game status */
	conecta4ns__tMove moveResult;		/** Move result */
	conecta4ns__tPlayer currentPlayer;
	unsigned int playerMove;			/** Player move */
	int resCode;						/** Return code from server */


		// Init gSOAP environment
		soap_init(&soap);

		// Obtain server address
		serverURL = argv[1];

		// Allocate memory for player name and init
		playerName.msg = (xsd__string) malloc (STRING_LENGTH);
		memset(playerName.msg, 0, STRING_LENGTH);

		// Allocate memory for game status and init
        allocClearBlock (&soap, &gameStatus);
  
		// Init
		resCode = -1;
		endOfGame = FALSE;
		gameStatus.code = 0;

		// Check arguments
		if (argc !=2) {
			printf("Usage: %s http://server:port\n",argv[0]);
			exit(0);
		}

		do{
			printf("Enter your player name: ");
			fgets(playerName.msg, STRING_LENGTH - 1, stdin);
			playerName.msg[strcspn(playerName.msg, "\n")] = 0; // Eliminar el salto de linea

			playerName.__size = strlen(playerName.msg);
			
			// Registra el jugador en el servidor
			resCode = soap_call_conecta4ns__register (&soap, serverURL, "", playerName, &gameStatus.code);
			// Comprobar el código de estado devuelto por el servidor
			if (gameStatus.code == ERROR_SERVER_FULL) {
				printf("Error: Server full, no empty games available.\n");
			} else if (gameStatus.code == ERROR_PLAYER_REPEATED) {
				printf("Error: That user is already registered in the game.\n");
			}
		} while(gameStatus.code < 0);
		
		
		int gameID = gameStatus.code;
		if (resCode == SOAP_OK) {
			printf("Registered successfully: %s\n", playerName.msg);
		} else {
			soap_print_fault(&soap, stderr);
			endOfGame = TRUE;
		}

		unsigned int column;
		
		// Bucle principal
		while (!endOfGame) {
			
			// Se lee el estado actual de la partida
			resCode = soap_call_conecta4ns__getStatus(&soap, serverURL, "", playerName, gameID, &gameStatus);
			if (resCode != 0) {
				printf("Error getting game status. Code: %d\n", resCode);
				exit(1);
			}
			
			// Pinta el mensaje y el tablero del server
			printBoard(gameStatus.board, gameStatus.msgStruct.msg);
			

			if (gameStatus.code == GAMEOVER_DRAW) {
					printf("It's a draw!\n\n");
					endOfGame = TRUE;
			} else if (gameStatus.code == GAMEOVER_LOSE) {
					printf("Sorry, you lost! Better luck next time.\n\n");
					endOfGame = TRUE;
			}
			else if (gameStatus.code == TURN_MOVE) {

				do{
					// Lee el movimiento del jugador
					playerMove = readMove();

					// Inserta la ficha en el tablero
					resCode = soap_call_conecta4ns__insertChip(&soap, serverURL, "", playerName, gameID, playerMove, &gameStatus);
					if(gameStatus.code == -1){
						printf("Error: La columna %d ya esta llena, introduzca otra columna\n", playerMove);
					}
				}while(gameStatus.code == -1);
				
				if (resCode != 0) {
					printf("Error inserting chip. Code: %d\n", resCode);
					exit(1);
				}

				// Pinta el tablero actualizado
				printBoard(gameStatus.board, gameStatus.msgStruct.msg);

				// Comprueba si el juego ha terminado
				if (gameStatus.code == GAMEOVER_WIN) {
					printf("Congratulations! You win!\n\n");
					endOfGame = TRUE;
				} else if (gameStatus.code == GAMEOVER_DRAW) {
					printf("It's a draw!\n\n");
					endOfGame = TRUE;
				}
			}
		}


		free(playerName.msg);
		// Clean the environment
		soap_destroy(&soap);
		soap_end(&soap);
		soap_done(&soap);

  return 0;
}
