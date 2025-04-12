#include "mpi.h"
#include "world.h"

// Enables/Disables the log messages from worker processes
#define DEBUG_WORKER 0


void runWorker(int worldWidth);

void updateWorld(int numFilasEnArea, int worldWidth, unsigned short *area, unsigned short *top, unsigned short *bottom, unsigned short *newWorld);
