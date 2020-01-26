PROGRAM = Forgotten_Paths
CC = gcc
LIBS = -lglut -lGL -lGLU -lm
CFLAGS = -Wall -g

$(PROGRAM): main.o mazeGenerator.o draw.o image.o light.o
	$(CC) $(CFLAGS) main.o mazeGenerator.o draw.o light.o image.o -o $(PROGRAM) $(LIBS)

main.o:  main.c
	gcc -c $(CFLAGS) main.c -o main.o $(LIBS)

draw.o: draw.c
	gcc -c $(CFLAGS) draw.c -o draw.o $(LIBS)

mazeGenerator.o: mazeGenerator.c 
	gcc -c $(CFLAGS) mazeGenerator.c  -o mazeGenerator.o $(LIBS)

light.o: light.c
	gcc -c $(CFLAGS) light.c -o light.o $(LIBS)

image.o: image.c
	gcc -c  image.c -o image.o

.PHONY: clean dist

clean:
	rm *.o $(PROGRAM)

