PROGRAM = Forgotten_Paths
CC = gcc
LIBS = -lglut -lGL -lGLU -lm
CFLAGS = -Wall -g

$(PROGRAM): main.o drugi.o
	$(CC) $(CFLAGS) -o $(PROGRAM) main.o drugi.o $(LIBS)

main.o:  main.c drugi.o
	gcc -c $(CFLAGS) -o main.o main.c drugi.o $(LIBS)

drugi.o: drugi.c
	gcc -c $(CFLAGS) -o drugi.o drugi.c $(LIBS)

.PHONY: clean dist

clean:
	rm *.o $(PROGRAM)

