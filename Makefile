PROGRAM = Forgotten_Paths
CC = gcc
LIBS = -lglut -lGL -lGLU -lm
CFLAGS = -Wall -g

$(PROGRAM): main.o mazeGenerator.o
	$(CC) $(CFLAGS) -o $(PROGRAM) main.o mazeGenerator.o $(LIBS)

main.o:  main.c mazeGenerator.o
	gcc -c $(CFLAGS) -o main.o main.c mazeGenerator.o $(LIBS)

mazeGenerator.o: mazeGenerator.c
	gcc -c $(CFLAGS) -o mazeGenerator.o mazeGenerator.c $(LIBS)

.PHONY: clean dist

clean:
	rm *.o $(PROGRAM)

