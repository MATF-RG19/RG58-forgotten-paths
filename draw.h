#ifndef DRAW_H
#define DRAW_H

int _width, _height; // Dimenzije lavirinta

extern void draw_maze(); // Funkcija koja vrsi iscrtavanje lavirinta
 
extern void draw_floor(); // Funkcija za iscrtavanje poda

extern void draw_coordinate_system(); // Funkcija za iscrtavanje koordinatnog sistema

extern void draw_player(); // Funkcija za iscrtavanje igraca

extern void init_texture(); // Funkcija za inicijalizaciju tekstura

extern void draw_game_over(); // Funkcija za prikaz zavrsnog ekrana

extern void renderStrokeString(int x, int y,int z,void* font, char *string); // Funkcija za ispisivanje teksta

#endif
