#include "master.h"

void runMaster(int worldWidth, int worldHeight, int totalIterations, int autoMode, int distModeStatic, int grainSize, char* outputFile, SDL_Window* window, SDL_Renderer* renderer) {
    int rank, numProcesos;
    MPI_Status status;
    int numFilasEnArea;
    struct timeval stop, start;
    
	// User's input and events
	char ch;

    unsigned short *currentWorld = NULL, *newWorld = NULL;
	
    // Inicializar MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcesos);

    if (numProcesos < 3) {
        fprintf(stderr, "Se necesitan al menos 3 procesos para ejecutar el programa.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    // Inicializar el tablero
    if (DEBUG_MASTER)printf("Inicializando el tablero...\n");
    currentWorld = (unsigned short*)malloc(worldWidth * worldHeight * sizeof(unsigned short));
    newWorld = (unsigned short*)malloc(worldWidth * worldHeight * sizeof(unsigned short));
    if (!currentWorld || !newWorld) {
        fprintf(stderr, "Error al asignar memoria para el tablero.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }
    clearWorld (currentWorld, worldWidth, worldHeight);
	clearWorld (newWorld, worldWidth, worldHeight);	

    initRandomWorld(currentWorld, worldWidth, worldHeight);
    if (DEBUG_MASTER)printf("Tablero inicializado con tamaño %dx%d.\n", worldWidth, worldHeight);
    
    if (DEBUG_MASTER){
		printf("Imprimiendo el tablero...\n");
		for (int row = 0; row < worldHeight; row++) {
			for (int col = 0; col < worldWidth; col++) {
				printf("%d ", currentWorld[row * worldWidth + col]);
			}
			printf("\n");  // Imprimir un salto de línea al final de cada fila
		}
    }
    
	// Clear renderer and draw iteration 0
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(renderer);		
    drawWorld(newWorld, currentWorld, renderer, 0, worldHeight - 1, worldWidth, worldHeight);
	SDL_RenderPresent(renderer);
	SDL_UpdateWindowSurface(window);
	
	printf ("Press Enter to continue...\n");
	ch = getchar();
		
	int grano = worldHeight / (numProcesos - 1);
	
    for (int iteration = 0; iteration < totalIterations; iteration++) {
		
		// Set timer for this iteration
		gettimeofday(&start, NULL);
		
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(renderer);	
		
        if (DEBUG_MASTER)printf("\n------------------- Iteración %d de %d -------------------\n", iteration + 1, totalIterations);
        
		int indicesMundo[numProcesos - 1]; // Array para guardar el índice inicial de cada worker
		int indiceMundo = 0;
		
        // Distribuir trabajo
        if (DEBUG_MASTER)printf("Distribuyendo trabajo a los procesos worker...\n");
        if (distModeStatic) {
            // Distribución de trabajo estática (división en bloques de filas)
            int remainingRows = worldHeight % (numProcesos - 1);
            
            for (int i = 1; i < numProcesos; i++) {
                unsigned short* top;
                unsigned short* area = NULL;
                unsigned short* bottom;
                int extraRow = 0;

				// Guardar el índice inicial para este proceso
				indicesMundo[i - 1] = indiceMundo;
				
                // Top
                if (indiceMundo == 0) {
                    top = currentWorld + (worldWidth * (worldHeight - 1));
                } else {
                    top = currentWorld + (worldWidth * (indiceMundo - 1));
                }

                // Area
                area = currentWorld + (worldWidth * indiceMundo);

                // Bottom
                if (indiceMundo + grano == worldHeight) {
                    bottom = currentWorld;
                } else {
                    if (remainingRows > 0) {
                        extraRow = 1;
                        remainingRows--;
                    }
                    bottom = currentWorld + (worldWidth * (indiceMundo + grano + extraRow));
                }
                // Calcular el número de filas entre top y bottom
				numFilasEnArea = grano + extraRow;

				 
				if (DEBUG_MASTER){
					// Mostrar el contenido del top
					printf("Proceso %d: Contenido del top:\n", i);
					for (int col = 0; col < worldWidth; col++) {
						printf("%d ", top[col]);
					}
					printf("\n");
				

					// Mostrar el contenido del área que se va a enviar
					printf("Área enviada al proceso %d:\n", i);
					for (int fila = 0; fila < grano + extraRow; fila++) {
						printf("Fila %d: ", indiceMundo + fila);
						for (int col = 0; col < worldWidth; col++) {
							printf("%d ", area[fila * worldWidth + col]);
						}
						printf("\n");
					}

					// Mostrar el contenido del bottom
					printf("Proceso %d: Contenido del bottom:\n", i);
					for (int col = 0; col < worldWidth; col++) {
						printf("%d ", bottom[col]);
					}
					printf("\n");
				
					printf("El valor de indiceMundo es: %d\n", indiceMundo);
				}
				// Enviar número de filas en 'area'
				MPI_Send(&numFilasEnArea, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
				if (DEBUG_MASTER)printf("Proceso %d: Número de filas en 'area' enviado (%d filas).\n", i, numFilasEnArea);
				
                // Enviar filas
				MPI_Send(top, worldWidth, MPI_UNSIGNED_SHORT, i, 1, MPI_COMM_WORLD);
				if (DEBUG_MASTER)printf("Proceso %d: Top enviado\n", i);
			

				//Area
                MPI_Send(area, worldWidth * numFilasEnArea, MPI_UNSIGNED_SHORT, i, 2, MPI_COMM_WORLD);
                if (DEBUG_MASTER)printf("Proceso %d: Área enviada.\n", i);

				//Bottom
                MPI_Send(bottom, worldWidth, MPI_UNSIGNED_SHORT, i, 3, MPI_COMM_WORLD);
                if (DEBUG_MASTER)printf("Proceso %d: Bottom enviado.\n", i);
				
				
                indiceMundo += grano + extraRow;
				
			}
		} else {
            // Distribución de trabajo dinámica
            int i = 1;
            while (i < numProcesos && indiceMundo<worldHeight) {
				unsigned short* top;
                unsigned short* area = NULL;
                unsigned short* bottom;

                numFilasEnArea = grainSize;
                
				// Top
                if (indiceMundo == 0) {
                    top = currentWorld + (worldWidth * (worldHeight - 1));
                } else {
                    top = currentWorld + (worldWidth * (indiceMundo - 1));
                }
				
				
				// Area
				area = currentWorld + (worldWidth * indiceMundo);
				
				if(indiceMundo + grainSize > worldHeight) {
					numFilasEnArea = worldHeight - indiceMundo;
				}
				
				// Bottom
				if (indiceMundo + grainSize >= worldHeight) {
					bottom = currentWorld;
				} else {
					bottom = currentWorld + (worldWidth * (indiceMundo + grainSize));
				}
                
                // Guardar el índice inicial para este proceso
				indicesMundo[i - 1] = indiceMundo;
				
				MPI_Send(&numFilasEnArea, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
				if (DEBUG_MASTER)printf("Proceso %d: Número de filas en 'area' enviado (%d filas).\n", i, numFilasEnArea);
				
				// Enviar filas
				MPI_Send(top, worldWidth, MPI_UNSIGNED_SHORT, i, 1, MPI_COMM_WORLD);
				if (DEBUG_MASTER)printf("Proceso %d: Top enviado\n", i);
			

				//Area
				MPI_Send(area, worldWidth * numFilasEnArea, MPI_UNSIGNED_SHORT, i, 2, MPI_COMM_WORLD);
				if (DEBUG_MASTER)printf("Proceso %d: Área enviada.\n", i);

				//Bottom
				MPI_Send(bottom, worldWidth, MPI_UNSIGNED_SHORT, i, 3, MPI_COMM_WORLD);
				if (DEBUG_MASTER)printf("Proceso %d: Bottom enviado.\n", i);
				
				indiceMundo += numFilasEnArea;
				i++;
			}
        }
    
  
            
		// Recibir resultados
		if (DEBUG_MASTER)printf("Recibiendo resultados de los procesos worker...\n");
		int recv = 0;
		int numFilasEnArea;

		while(recv != worldHeight){
			// Recibir el número de filas procesadas por el worker
			MPI_Recv(&numFilasEnArea, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
			if (DEBUG_MASTER)printf("Master: Recibido número de filas procesadas: %d, desde el worker con rank %d.\n", numFilasEnArea, status.MPI_SOURCE);


			unsigned short* puntero = newWorld + indicesMundo[status.MPI_SOURCE-1]* worldWidth;
			MPI_Recv(puntero, worldWidth * numFilasEnArea, MPI_UNSIGNED_SHORT, status.MPI_SOURCE, 1, MPI_COMM_WORLD, &status);
			
			int numFilasEnArea_send;
			if (!distModeStatic){
				if(indiceMundo < worldHeight){
					if (DEBUG_MASTER)printf("Enviando datos de vuelta al proceso %d\n", status.MPI_SOURCE);
					
					unsigned short* top;
					unsigned short* area_send = NULL;
					unsigned short* bottom;
					
					// Guardar el índice inicial para este proceso
					indicesMundo[status.MPI_SOURCE - 1] = indiceMundo;
				
					top = currentWorld + (worldWidth * (indiceMundo - 1));
					
					area_send = currentWorld + (worldWidth * indiceMundo);
					
					if(worldHeight - indiceMundo < grainSize){
						numFilasEnArea_send = worldHeight - indiceMundo;
						bottom = currentWorld;
						indiceMundo = worldHeight;
					}
					else{
						numFilasEnArea_send = grainSize;
						bottom = currentWorld + (worldWidth * (indiceMundo + grainSize));
						indiceMundo += numFilasEnArea_send;
					}
					
					MPI_Send(&numFilasEnArea_send, 1, MPI_INT, status.MPI_SOURCE, 0, MPI_COMM_WORLD);
					if (DEBUG_MASTER)printf("Proceso %d: Número de filas en 'area' enviado (%d filas).\n", status.MPI_SOURCE, numFilasEnArea);
					
					// Enviar filas
					MPI_Send(top, worldWidth, MPI_UNSIGNED_SHORT, status.MPI_SOURCE, 1, MPI_COMM_WORLD);
					if (DEBUG_MASTER)printf("Proceso %d: Top enviado\n", status.MPI_SOURCE);
				

					//Area
					MPI_Send(area_send, worldWidth * numFilasEnArea_send, MPI_UNSIGNED_SHORT, status.MPI_SOURCE, 2, MPI_COMM_WORLD);
					if (DEBUG_MASTER)printf("Proceso %d: Área enviada.\n", status.MPI_SOURCE);

					//Bottom
					MPI_Send(bottom, worldWidth, MPI_UNSIGNED_SHORT, status.MPI_SOURCE, 3, MPI_COMM_WORLD);
					if (DEBUG_MASTER)printf("Proceso %d: Bottom enviado.\n", status.MPI_SOURCE);


				}
			}
			
			recv = recv + numFilasEnArea;
			 
		}
		
		if (((rand() % 100) < PROB_CATACLYSM) && (iteration % ITER_CATACLYSM == 0)) {
			// Fila y columna central
			int centerRow = worldHeight / 2;
			int centerCol = worldWidth / 2;
			
			for (int col = 0; col < worldWidth; col++) {
				currentWorld[centerRow * worldWidth + col] = CELL_CATACLYSM;
				newWorld[centerRow * worldWidth + col] = CELL_EMPTY;
			}

			for (int row = 0; row < worldHeight; row++) {
				currentWorld[row * worldWidth + centerCol] = CELL_CATACLYSM;
				newWorld[row * worldWidth + centerCol] = CELL_EMPTY;
			}
		}
            
        if (DEBUG_MASTER){
			printf("Imprimiendo el tablero...\n");
			for (int row = 0; row < worldHeight; row++) {
				for (int col = 0; col < worldWidth; col++) {
					printf("%d ", newWorld[row * worldWidth + col]);
				}
				printf("\n");  // Imprimir un salto de línea al final de cada fila
			}
		}
        
        drawWorld(currentWorld, newWorld, renderer, 0, worldHeight - 1, worldWidth, worldHeight);
		clearWorld (currentWorld, worldWidth, worldHeight);	   
		
		// Intercambiar tableros
		unsigned short* temp = currentWorld;
		currentWorld = newWorld;
		newWorld = temp;	
		
		if (DEBUG_MASTER)printf("Mundos cambiados\n");
		
		
		SDL_RenderPresent(renderer);
		SDL_UpdateWindowSurface(window);	
		
		if (!autoMode){
			printf ("Press Enter to continue...\n");
			ch = getchar();
		}		
		// End timer for this iteration
		gettimeofday(&stop, NULL);
		printf ("%f seconds\n", (double) ((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec)/1000000.0);			

	}

	if (DEBUG_MASTER)printf("Fuera del bucle\n");

	numFilasEnArea = END_PROCESSING;
	
	for(int i = 1; i < numProcesos;i++){
		MPI_Send(&numFilasEnArea, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
	}

    
    // Guardar la última imagen
    /*if (outputFile != NULL)	
		saveImage(renderer, outputFile, worldWidth * CELL_SIZE, worldHeight * CELL_SIZE);
	*/

    // Liberar memoria
    free(currentWorld);
    free(newWorld);
    
    // Destroy window		
	SDL_DestroyWindow(window);

	// Game over
	printf ("Game Over!!! Press Enter to continue...\n");
	ch = getchar();
		
    // Exiting...
    SDL_Quit();
    
}
