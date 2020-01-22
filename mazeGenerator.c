// Deo koda je preuzet sa adrese 
// https://en.wikipedia.org/wiki/Maze_generation_algorithm

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define check_error(expr, msg)\
    do{\
        if(!(expr)){\
            fprintf(stderr, "%s\n", msg);\
            exit(EXIT_FAILURE);\
        }\
    }while(0)

typedef struct{
	int x, y; // Koordinate cvora
	void *parent; // Pokazivac na roditelja
	char c; // Karakter koji se stampa
	char dirs; // Smerovi koji u ovom momentu nisu obilazeni
} Node;

Node *nodes;

// Dimenzije lavirinta
int width = 39;
int height = 39; 

int init();

Node* link(Node* n);

void draw();

void edit_maze();

char** make_matrix();

char** matrix;

void glavna(){
	Node *start, *last;

	// Nasumican seed
	srand(time(NULL));
	
	// Inicijalizuj lavirint
    check_error(!init(), "Nema dovoljno memorije!");
	
	// Podesi pocetni cvor
	start = nodes + 1 + width;
	start->parent = start;
	last = start;

    // Povezuj cvorove dok pocetni cvor nije dostignut
	while((last = link(last)) != start);	

	// Pravi ulaz i izlaz
	edit_maze();

	matrix = make_matrix();

	//draw();
}

int init(){

	int i, j;
	Node* n;
	
	// Vrsi se alokacija memorije za lavirint
	nodes = calloc(width * height, sizeof(Node));
	check_error(nodes != NULL, "Neuspesna alokacija!");
		
	// Inicijalizuj neophodne cvorove
	for (i = 0; i < width; i++){
		for (j = 0; j < height; j++ ){

			n = nodes + i + j * width;
			if (i * j % 2){
				n->x = i;
				n->y = j;
				n->dirs = 15; // Sva cetiri pravca mogu da se obidju, pa postavljamo cetiri najniza bita na 1
				n->c = ' '; 
			}
			else n->c = '@'; // Dodaje se zid izmedju cvorova
		}
	}
	return 0;
}

// Prebacujemo lavirint u formu matrice radi lakseg baratanja
char** make_matrix(){
	
	char** matrix1;
	
	matrix1 = malloc(height * sizeof(char*));
	check_error(matrix1 != NULL, "Greska prilikom alokacije memorije!");

	int i, j;
	for(i = 0; i < height; i++){
		matrix1[i] = malloc(width * sizeof(char));
		check_error(matrix1[i] != NULL, "Greska prilikom alokacije memorije!");
	}

	for (i = 0; i < height; i++){
		for (j = 0; j < width; j++){
			matrix1[i][j] = nodes[j + i * width].c;
		}
	}

	return matrix1;
}

// Ispisuje lavirint u terminal
void draw(){
	// int i, j;

    // for (i = 0; i < height; i++){
	// 	for (j = 0; j < width; j++){
	// 		printf("%c", matrix[i][j]);
	// 	}
	// 	printf("\n");
	// }

	int i, j;

	for (i = 0; i < height; i++){
		for (j = 0; j < width; j++){
			printf("%c", nodes[j + i * width].c);
		}
		printf("\n");
	}
}

// Povezuje cvor sa nasumicnim susedom, ukoliko je moguce, i vraca
// adresu sledeceg cvora koji treba da se poseti
Node* link(Node* n){

	int x, y;
	char dir;
	Node *dest;
	
    // Nista ne mozemo ako je null pointer poslat
	if(n == NULL) return NULL;
	
	// Sve dok postoje neobidjeni pravci
	while(n->dirs){
		
    	// Nasumicno biraj pravac
		dir = (1 << (rand() % 4));
		
		// Ako je taj pravac vec obidjen, trazi sledeci
		if(~n->dirs & dir) continue;
		
		// Obelezi ga kao obidjen
		n->dirs &= ~dir;
		
		// U zavisnosti od izabranog pravca
		switch(dir){
			// Proveri da li je moguce ici desno
			case 1:
				if(n->x + 2 < width){
					x = n->x + 2;
					y = n->y;
				}
				else continue;
				break;
			
			// Proveri da li je moguce ici dole
			case 2:
				if(n->y + 2 < height){
					x = n->x;
					y = n->y + 2;
				}
				else continue;
				break;
			
			// Proveri da li je moguce ici levo
			case 4:
				if(n->x - 2 >= 0){
					x = n->x - 2;
					y = n->y;
				}
				else continue;
				break;
			
			// Proveri da li je moguce ici gore
			case 8:
				if(n->y - 2 >= 0){
					x = n->x;
					y = n->y - 2;
				}
				else continue;
				break;
		}
		
        // Prebaci krajnji cvor u pokazivac
		dest = nodes + x + y * width;
		
		// Postaraj se da krajnji cvor nije zid
		if(dest->c == ' '){
            		// Ako je krajnji cvor povezan vec - prekini
			if(dest->parent != NULL) continue;
			
			// U suprotnom, povezi ga
			dest->parent = n;
			
			// Ukloni zid izmedju cvorova
			nodes[n->x + (x - n->x) / 2 + (n->y + (y - n->y) / 2) * width].c = ' ';
			
			// Vrati adresu dete-cvora
			return dest;
		}
	}
	
    // Ukoliko se nista vise ne moze uraditi, vrati adresu dete-cvora
	return n->parent;
}

void edit_maze(){

	// Pravimo rucno ulaz u lavirint
	int i, j = 1;
	for(i = 0; i < width; i++){
		Node* n = nodes + i + j * width;
		if(n->c == ' '){
			n = nodes + i;
			n->c = ' ';
			break;
		}	
	}

	// Pravimo rucno izlaz iz lavirinta
	j = height-2;
	for(i = width-1; i >= 0; i--){
		Node* n = nodes + i + j * width;
		if(n->c == ' '){
			n = nodes + i + (height-1) * width;
			n->c = ' ';
			break;
		}	
	}
}
