#include "worker.h"

/**
 * Esta función gestiona la ejecución del proceso worker.
 * Recibe las filas a procesar, realiza el cálculo y envía el resultado al proceso master.
 */
void runWorker(int worldWidth) {

    int rank;
    int numFilasEnArea;
    MPI_Status status;
    unsigned short *top = NULL, *bottom = NULL, *area = NULL, *newWorld = NULL;

    // Obtener el rango del proceso en MPI (el identificador único del proceso)
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (DEBUG_WORKER)printf("Proceso Worker %d iniciado.\n", rank);
    
	int x = 0;
    do{
		// Recibir el número de filas en el área que este worker va a procesar
		MPI_Recv(&numFilasEnArea, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		if(x == 0){			//Se hace solo la primera vez
			top = (unsigned short *)malloc(worldWidth * sizeof(unsigned short));
			bottom = (unsigned short *)malloc(worldWidth * sizeof(unsigned short));
			area = (unsigned short *)malloc(numFilasEnArea * worldWidth * sizeof(unsigned short));
			newWorld = (unsigned short *)malloc(numFilasEnArea * worldWidth * sizeof(unsigned short));
			x = 1;
		}
		if (DEBUG_WORKER)printf("Proceso Worker %d: Número de filas en 'area' recibido (%d filas).\n", rank, numFilasEnArea);
		if(numFilasEnArea != END_PROCESSING){
			// Reservar memoria solo para el área que este worker va a procesar
			

			if (area == NULL || newWorld == NULL) {
				printf("Error al reservar memoria en el proceso Worker %d.\n", rank);
				MPI_Abort(MPI_COMM_WORLD, 1);
			}

		
			// Recibir top
			MPI_Recv(top, worldWidth, MPI_UNSIGNED_SHORT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			if (DEBUG_WORKER){
				printf("Worker %d: Top recibido. Valores:\n", rank);
				for (int i = 0; i < worldWidth; i++) {
					printf("%hu ", top[i]);
				}
				printf("\n");
			}
			
			// Recibir area
			MPI_Recv(area, numFilasEnArea * worldWidth, MPI_UNSIGNED_SHORT, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			if (DEBUG_WORKER){
				printf("Worker %d: Área recibida. Valores:\n", rank);
				for (int row = 0; row < numFilasEnArea; row++) {
					for (int col = 0; col < worldWidth; col++) {
						printf("%hu ", area[row * worldWidth + col]);
					}
					printf("\n");
				}
			}

			// Recibir bottom
			MPI_Recv(bottom, worldWidth, MPI_UNSIGNED_SHORT, 0, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			if (DEBUG_WORKER){
				printf("Worker %d: Bottom recibido. Valores:\n", rank);
				for (int i = 0; i < worldWidth; i++) {
					printf("%hu ", bottom[i]);
				}
				printf("\n");
			}
			
			

			// Procesar las filas y calcular el siguiente estado del tablero
			if (DEBUG_WORKER)printf("Proceso Worker %d: Iniciando procesamiento de filas.\n", rank);
			updateWorld(numFilasEnArea, worldWidth, area, top, bottom, newWorld);
			
			if (DEBUG_WORKER)printf("Proceso Worker %d: Enviando número de filas en área: %d al Master (rank 0).\n", rank, numFilasEnArea);
			MPI_Send(&numFilasEnArea, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

			// Enviar los resultados al proceso master
			MPI_Send(newWorld, worldWidth * numFilasEnArea, MPI_UNSIGNED_SHORT, 0, 1, MPI_COMM_WORLD);
			if (DEBUG_WORKER){
				printf("Proceso Worker %d: Resultados enviados al Master. Valores enviados:\n", rank);
				for (int row = 0; row < numFilasEnArea; row++) {
					for (int col = 0; col < worldWidth; col++) {
						printf("%hu ", newWorld[row * worldWidth + col]);
					}
					printf("\n");
				}
			}
					
				
		}
		
	}while(numFilasEnArea != END_PROCESSING);

    // Liberar memoria
    free(top);
	free(bottom);
	free(area);
	free(newWorld);
	
    if (DEBUG_WORKER)printf("Proceso Worker %d: Finalizando.\n", rank);
}

void updateWorld(int numFilasEnArea, int worldWidth, unsigned short *area, unsigned short *top, unsigned short *bottom, unsigned short *newWorld){
	for (int row = 0; row < numFilasEnArea; row++) {
		for (int col = 0; col < worldWidth; col++) {
			
			int neighbours = 0;
			tCoordinate cell, up, down, left, right, up_left, up_right, down_left, down_right;
			cell.row = row;
			cell.col = col;
			
			
			getCellLeft(&cell, worldWidth, &left);
			getCellRight(&cell, worldWidth, &right);
			// Check left
			if (getCellAtWorld(&left, area, worldWidth) == CELL_LIVE){
				neighbours++;
			}
			
			// Check right
			if (getCellAtWorld(&right, area, worldWidth) == CELL_LIVE){
				neighbours++;
			}	
			if (row == 0) {
				// Calcular la primera fila
				tCoordinate celltop;
				celltop.row = 0;
				celltop.col = col;
				
				getCellLeft(&celltop, worldWidth, &up_left);
				getCellRight(&celltop, worldWidth, &up_right);
				
				// Check up
				if (getCellAtWorld(&celltop, top, worldWidth) == CELL_LIVE){
					neighbours++;
				}					
				
				// Check up-left
				if (getCellAtWorld(&up_left, top, worldWidth) == CELL_LIVE){
					neighbours++;		
				}
				
				// Check up-right
				if (getCellAtWorld(&up_right, top, worldWidth) == CELL_LIVE){
					neighbours++;
				}	
			}
			else {
				
				getCellUp(&cell, &up);
				getCellUp(&left, &up_left);
				getCellUp(&right, &up_right);
				
				// Check up
				if (getCellAtWorld(&up, area, worldWidth) == CELL_LIVE)
					neighbours++;						
				
				// Check up-left
				if (getCellAtWorld(&up_left, area, worldWidth) == CELL_LIVE)
					neighbours++;		
				
				// Check up-right
				if (getCellAtWorld(&up_right, area, worldWidth) == CELL_LIVE)
					neighbours++;
				
			}
			
			if (row == numFilasEnArea - 1) {
				// Calcular la ultima fila
				
				tCoordinate cellbottom;
				cellbottom.row = 0;
				cellbottom.col = col;
				
				getCellLeft(&cellbottom, worldWidth, &down_left);
				getCellRight(&cellbottom, worldWidth, &down_right);
				
				// Check down
				if (getCellAtWorld(&cellbottom, bottom, worldWidth) == CELL_LIVE)
					neighbours++;						
				
				// Check down-left
				if (getCellAtWorld(&down_left, bottom, worldWidth) == CELL_LIVE)
					neighbours++;		
				
				// Check down-right
				if (getCellAtWorld(&down_right, bottom, worldWidth) == CELL_LIVE)
					neighbours++;
			}
			else {
				getCellDown(&cell, &down);
				getCellDown(&left, &down_left);
				getCellDown(&right, &down_right);

						
				// Check down
				if (getCellAtWorld(&down, area, worldWidth) == CELL_LIVE)
					neighbours++;						
				
				// Check down-left
				if (getCellAtWorld(&down_left, area, worldWidth) == CELL_LIVE)
					neighbours++;
				
				// Check down-right
				if (getCellAtWorld(&down_right, area, worldWidth) == CELL_LIVE)
					neighbours++;	
			}
							
			// Lonely cell?
			if (neighbours==0)
				calculateLonelyCell();
			
			// Cell is still alive
			if (getCellAtWorld(&cell, area, worldWidth) == CELL_LIVE && ((neighbours==2) || (neighbours==3)))
				setCellAt (&cell, newWorld, worldWidth, CELL_LIVE);
						
			// New cell is born
			else if (getCellAtWorld(&cell, area, worldWidth) == CELL_EMPTY && (neighbours==3))
				setCellAt (&cell, newWorld, worldWidth, CELL_LIVE);
			
			// Cell is dead
			else
				setCellAt (&cell, newWorld, worldWidth, CELL_EMPTY);
			
		}
	}
}

