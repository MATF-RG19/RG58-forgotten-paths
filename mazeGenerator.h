#ifndef MAZE_GENERATE_H
#define MAZE_GENERATE_H

int width;
int height;

typedef struct{
	int x, y; //Koordinate cvora
	void *parent; //Pokazivac na roditelja
	char c; //Karakter koji se stampa
	char dirs; //Smerovi koji u ovom momentu nisu obilazeni
} Node;

Node* nodes;
char** matrix; //Lavirint

void glavna();

int init(); //Funkcija za inicijalizaciju

//Povezuje cvor sa nasumicnim susedom, ukoliko je moguce, i vraca
//adresu sledeceg cvora koji treba da se poseti
Node* link(Node* n);

void draw(); //Iscrtava lavirint u terminal

void edit_maze(); //Dodaje ulaz i izlaz u lavirint

char** make_matrix(); //Prebacuje lavirint u formu matrice

#endif
