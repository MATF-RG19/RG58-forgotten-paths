#ifndef DRAW_H
#define DRAW_H

int _width, _height; // Dimenzije lavirinta

extern void draw_maze(); // Funkcija koja vrsi iscrtavanje lavirinta
 
extern void draw_floor(); // Funkcija za iscrtavanje poda

extern void draw_coordinate_system(); // Funkcija za iscrtavanje koordinatnog sistema

extern void draw_player(); // Funkcija za iscrtavanje igraca

extern void init_texture(); // Funkcija za inicijalizaciju tekstura

#endif