PROGRAM = Forgotten_Paths
CC = gcc
LIBS = -lglut -lGL -lGLU -lm
CFLAGS = -Wall -g

$(PROGRAM): main.o mazeGenerator.o draw.o
	$(CC) $(CFLAGS) -o $(PROGRAM) main.o mazeGenerator.o draw.o light_textures.o $(LIBS)

main.o:  main.c mazeGenerator.o draw.o light_textures.o
	gcc -c $(CFLAGS) -o main.o main.c mazeGenerator.o draw.o light_textures.o $(LIBS)

draw.o: draw.c mazeGenerator.o
	gcc -c $(CFLAGS) -o draw.o draw.c mazeGenerator.o $(LIBS)

mazeGenerator.o: mazeGenerator.c
	gcc -c $(CFLAGS) -o mazeGenerator.o mazeGenerator.c $(LIBS)

light_textures.o: light_textures.c
	gcc -c $(CFLAGS) -o light_textures.o light_textures.c $(LIBS)

.PHONY: clean dist

clean:
	rm *.o $(PROGRAM)

