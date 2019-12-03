#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

#include "mazeGenerator.h"
#include "draw.h"
#include "light_textures.h"

// Struktura za predstavljanje tacaka
typedef struct Point{
    double x;
    double y;
    double z;
} Point;

typedef struct Player{
    double x;
    double y;
    double z;
} Player;

Point start; // Pocetna pozicija
Point finish; // Zavrsna pozicija

Player lopta; // Nas igrac

static void on_display();
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);

int _width = 39, _height = 39; // Dimenzije lavirinta

// Funkcija koja odredjuje koordinate pocetne pozicije
Point find_start(){
    double _x;
    double _z;

    int i, j;

    for(i = 0; i < _width; i++)
        for(j = 0; j < _height; j++)
            if(matrix[i][j] != '@'){
                _x = i;
                _z = j;
                break;
            }
    Point res;

    res.x = _x;
    res.z = _z;
    res.y = 0;

    printf("%lf %lf %lf\n", res.x, res.y, res.z);

    return res;
}

// Funkcija koja odredjuje kooridnate krajnje pozicije
Point find_finish(){
    double _x;
    double _z;

    int i, j;

    for(i = _width-1; i >= 0; i--)
        for(j = _height-1; j >= 0; j--)
            if(matrix[i][j] != '@'){
                _x = i;
                _z = j;
                break;
            }
    Point res;

    res.x = _x;
    res.z = _z;
    res.y = 0;

    printf("%lf %lf %lf\n", res.x, res.y, res.z);

    return res;
}

int main(int argc, char** argv){

    // Inicijalizacija gluta
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    // Kreiranje prozora
    glutInitWindowSize(1920, 1080);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Forgotten Paths");

    // Registruju se callback funkcije
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

    // Obavlja se OpenGL  inicijalizacija
    glClearColor(0.75, 0.75, 0.75, 0);

    glEnable(GL_DEPTH_TEST);

    glavna();
    start = find_start();
    finish = find_finish();

    lopta.x = finish.x;
    lopta.y = finish.y;
    lopta.z = finish.z;

    // Program ulazi u glavnu petlju
    glutMainLoop();

    return 0;
}
// Funkcija za obradu komandi sa tastature
void on_keyboard(unsigned char key, int x, int y){
    
    switch(key){

        case 27: // Prekidanje igrice
            exit(EXIT_SUCCESS);
            break;
        case ('w'|'W'): // Kretanje pravo
            lopta.x += 0.1;
            glutPostRedisplay();
            break;
        case ('a'|'A'): // Kretanje levo
            lopta.z -= 0.1;
            glutPostRedisplay();
            break;
        case ('s'|'S'): // Kretanje dole
            lopta.x -= 0.1;
            glutPostRedisplay();
            break;
        case ('d'|'D'): // Kretanje desno
            lopta.z += 0.1;
            glutPostRedisplay();
            break;
        case ('x'|'X'): // Promena pogleda
            break;
    }

    glutPostRedisplay();
}

void on_reshape(int width, int height){

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 1, 1000);
}

void on_display(void){

    set_light();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(-70, 120, -70, 50, 50, 50, 0, 1, 0);

    //draw_coordinate_system();

    draw_maze();
    draw_floor();
    
    glPushMatrix();
        glTranslatef(5*lopta.x, 5, 5*lopta.z);
        draw_player();
    glPopMatrix();

    glutSwapBuffers();
}