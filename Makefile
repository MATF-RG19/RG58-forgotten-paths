PROGRAM = Forgotten_Paths
CC = gcc
LIBS = -lglut -lGL -lGLU -lm
CFLAGS = -Wall -g

$(PROGRAM): main.o draw.o
	$(CC) $(CFLAGS) -o $(PROGRAM) main.o draw.o $(LIBS)

main.o:  main.c
	gcc -c $(CFLAGS) -o main.o main.c $(LIBS)

draw.o: draw.c
	gcc -c $(CFLAGS) -o draw.o draw.c $(LIBS)

.PHONY: clean dist

clean:
	rm *.o $(PROGRAM)
