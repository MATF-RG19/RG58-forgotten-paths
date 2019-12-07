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

// Struktura koja predstavlja igraca
typedef struct Player{
    double x;
    double y;
    double z;
} Player;

int first_person; // Indikator moda

// Konstanta pi
static float pi = 3.141592653589793;

// Uglovi u sfernom koordinatnom sistemu koji
// odredjuju polozaj vidne tacke. */
static float phi;
static float theta;

// Inkrementi gornjih uglova
static float delta_phi;
static float delta_theta;

double _h = (double)(-39*5/2);

Point start; // Pocetna pozicija
Point finish; // Zavrsna pozicija

Player lopta; // Nas igrac

// Kumulativana matrica rotacije
static float matrixR[16];

// Koordinate pokazivaca misa
static int mouse_x = 0;
static int mouse_y = 0;

static void on_display();
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_mouse(int button, int state, int x, int y);
static void on_motion(int x, int y);

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


int nema_kolizije1(){
    int poz1 = floor(lopta.x/5);
    int poz2 = floor(lopta.z/5);
    printf("%d %d\n", poz1, poz2);
    if(matrix[poz1][poz2+1] == '@')
        return 0;
    else
        return 1;
}
/*
int nema_kolizije2(){
    int poz1 = (int)(floor(lopta.z))-1.2;
    int poz2 = (int)(floor(lopta.x));
    if(matrix[poz2][poz1] == '@')
        return 0;
    else
        return 1;
}

int nema_kolizije3(){
    int poz1 = (int)(floor(lopta.x));
    int poz2 = (int)(floor(lopta.z));
    printf("%d %d", poz1, poz2);
    if(matrix[poz1][poz2] == '@')
        return 0;
    else
        return 1;
}

int nema_kolizije4(){
    double new_z = lopta.z + 1.1;
    int poz1 = (int)(floor(new_z));
    int poz2 = (int)(floor(lopta.x));
    if(matrix[poz2][poz1] == '@')
        return 0;
    else
        return 1;
}
*/

void initialize(){
    phi = 0;
    theta = pi/4;

    delta_phi = pi/90;
    delta_theta = pi/90;

    glavna();
    start = find_start();
    finish = find_finish();

    lopta.x = finish.x;
    lopta.y = finish.y;
    lopta.z = finish.z;

    first_person = 1;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glGetFloatv(GL_MODELVIEW_MATRIX, matrixR);
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
    glutMouseFunc(on_mouse);
    glutMotionFunc(on_motion);

    // Obavlja se OpenGL  inicijalizacija
    glClearColor(0.75, 0.75, 0.75, 0);

    glEnable(GL_DEPTH_TEST);

    initialize();

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
        case 'w': // Kretanje pravo
        case 'W':
            if(nema_kolizije1())
                lopta.x += 0.2;
            printf("%lf  %lf\n", lopta.x, lopta.z);
            glutPostRedisplay();
            break;
        case 'a': // Kretanje levo
        case 'A':
            lopta.z -= 0.2;
            glutPostRedisplay();
            break;
        case 's': // Kretanje dole
        case 'S':  
            lopta.x -= 0.2;
            glutPostRedisplay();
            break;
        case 'd': // Kretanje desno
        case 'D':
            lopta.z += 0.2;
            glutPostRedisplay();
            break;
        case 'x': // Promena pogleda
        case 'X':
            if(first_person)
                first_person = 0;
            else
                first_person = 1;
            break;
        case 'p': //Dekrementira se ugao phi i ponovo iscrtava scena
        case 'P': 
            phi -= delta_phi;
            if (phi > 2 * pi) {
                phi -= 2 * pi;
            } else if (phi < 0) {
                phi += 2 * pi;
            }
            glutPostRedisplay();
            break;
        case 'o':  // Inkrementira se ugao phi i ponovo iscrtava scena
        case 'O':
            phi += delta_phi;
            if (phi > 2 * pi) {
                phi -= 2 * pi;
            } else if (phi < 0) {
                phi += 2 * pi;
            }
            glutPostRedisplay();
            break;
    }

    glutPostRedisplay();
}

static void on_mouse(int button, int state, int x, int y){

    // Pamti se pozicija kursora
    mouse_x = x;
    mouse_y = y;
}

void on_motion(int x, int y){
    // Promena pozicije kursora
    int delta_x;

    // Izracunava se promena pozicije kursora
    delta_x = x - mouse_x;

    // Pamti se nova pozicija kursora
    mouse_x = x;
    mouse_y = y;

    // Izracunava se nova matrica rotacije
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glLoadIdentity();
        glRotatef(180 * (float) delta_x / 1920, 0, 1, 0);
        glMultMatrixf(matrixR);

        glGetFloatv(GL_MODELVIEW_MATRIX, matrixR);
    glPopMatrix();

    // Forsira se ponovno iscrtavanje prozora
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
    // Imamo dva pogleda, jedan je u prvom licu
    // dok u drugom imamo pogled iz visine
    if(first_person == 0)
        gluLookAt(-100, 200+ 100 * cos(theta) * sin(phi), -100, 0, 0, 0, 0, 1, 0);
    else
        gluLookAt(lopta.x, lopta.y, lopta.z, 0, 0, 0, 0, 1, 0);

    glMultMatrixf(matrixR);

    draw_coordinate_system();

    draw_maze();
    draw_floor();
    
    glPushMatrix();
        glTranslatef(5*lopta.x+_h, 5, 5*lopta.z+_h);
        draw_player();
    glPopMatrix();

    glutSwapBuffers();
}