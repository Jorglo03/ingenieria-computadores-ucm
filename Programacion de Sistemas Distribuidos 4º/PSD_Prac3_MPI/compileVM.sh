mpicc -o lifeGame *.c -I/usr/local/include/SDL2 -L/usr/local/lib/ -lSDL2
mpiexec -hostfile machines -np 4 lifeGame 100 100 1000 auto resultado.bmp static
