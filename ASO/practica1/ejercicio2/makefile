CC=gcc
CFLAGS=-c -fPIC -o
LIB_NAME_STATIC=libmilibreria.a
LIB_NAME_DYNAMIC=libmilibreria.so

all: $(LIB_NAME_DYNAMIC) $(LIB_NAME_STATIC) appdynamic appstatic

# Librería estática
$(LIB_NAME_STATIC): funaux1.o funaux2.o
	ar cr $(LIB_NAME_STATIC) funaux1.o funaux2.o

# Librería dinámica
$(LIB_NAME_DYNAMIC): funaux1.o funaux2.o
	$(CC) -shared -o $(LIB_NAME_DYNAMIC) funaux1.o funaux2.o

# Objetos
funaux1.o: fun1src.c
	$(CC) $(CFLAGS) funaux1.o fun1src.c

funaux2.o: fun2src.c
	$(CC) $(CFLAGS) funaux2.o fun2src.c

# Ejecutable appdynamic
appdynamic: testmain.c $(LIB_NAME_DYNAMIC)
	$(CC) -o appdynamic testmain.c -L. -Wl,-rpath,. -lmilibreria

# Ejecutable appstatic
appstatic: testmain.c $(LIB_NAME_STATIC)
	$(CC) -o appstatic testmain.c -L. -lmilibreria -static

.PHONY: clean
clean:
	rm -rf *.o $(LIB_NAME_STATIC) $(LIB_NAME_DYNAMIC) appstatic appdynamic
