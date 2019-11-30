#ifndef MAZE_GENERATE_H
#define MAZE_GENERATE_H

// Dimenzije lavirinta
extern int width; 
extern int height;

typedef struct{
	int x, y; // Koordinate cvora
	void *parent; // Pokazivac na roditelja
	char c; // Karakter koji se stampa
	char dirs; // Smerovi koji u ovom momentu nisu obilazeni
} Node;

extern Node* nodes;
extern char** matrix; // Matrica koja cuva lavirint

extern void glavna();

extern int init(); // Funkcija za inicijalizaciju

// Povezuje cvor sa nasumicnim susedom, ukoliko je moguce, i vraca
// adresu sledeceg cvora koji treba da se poseti
extern Node* link(Node* n);

extern void draw(); // Iscrtava lavirint u terminal

extern void edit_maze(); // Dodaje ulaz i izlaz u lavirint

extern char** make_matrix(); // Prebacuje lavirint u formu matrice

#endif
