#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

#include "../Headers/mazeGenerator.h"
#include "../Headers/draw.h"
#include "../Headers/light.h"

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

// Indikator kraja igre
int is_game_over;
// Konstanta pi
static float pi = 3.141592653589793;

// Uglovi u sfernom koordinatnom sistemu koji
// odredjuju polozaj vidne tacke. */
static float phi;
static float theta;

// Inkrementi gornjih uglova
static float delta_phi;
static float delta_theta;

Point start; // Pocetna pozicija
Point finish; // Zavrsna pozicija

Player lopta; // Nas igrac

// Kumulativana matrica rotacije
static float matrixR[16];

// Koordinate pokazivaca misa
static int mouse_x = 0;
static int mouse_y = 0;

// Callback funkcije
static void on_display();
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_mouse(int button, int state, int x, int y);
static void on_motion(int x, int y);

int _width = 39, _height = 39; // Dimenzije lavirinta
double _h;

// Funkcija koja odredjuje koordinate krajnje pozicije
Point find_finish(){
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

    //printf("%lf %lf %lf\n", res.x, res.y, res.z);

    return res;
}

// Funkcija koja odredjuje kooridnate pocetne pozicije
Point find_start(){
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

    //printf("%lf %lf %lf\n", res.x, res.y, res.z);

    return res;
}

// Funkcija koja proverava da li
// je igrac stigao do kraja
int is_win(int x, int y){
    if(x == finish.x && y == finish.z)
        return 1;
    else
        return 0;
}

// Funkcija za detektovanje kolizija
// sa prednjim zidovima
int collision_front(){

    if(is_game_over)
        return 0;

    int poz1 = floor(lopta.x+0.9);
    int poz2 = round(lopta.z-0.2);
    int poz3 = round(lopta.z+0.2);

    if(is_win(poz1, poz2)){
        is_game_over = 1;
    }

    if(matrix[poz1][poz2] == '@' || matrix[poz1][poz3] == '@')
        return 0;
    else
        return 1;
}

// Funkcija za detektovanje kolizija
// sa zadnjim zidovima
int collision_back(){

    if(is_game_over)
        return 0;

    int poz1 = floor(lopta.x+0.1);
    int poz2 = round(lopta.z-0.2);
    int poz3 = round(lopta.z+0.2);

    if(is_win(poz1, poz2)){
        is_game_over = 1;
    }

    if(poz1 == 0 && poz2 == 1)
        return 0;

    if(matrix[poz1][poz2] == '@' || matrix[poz1][poz3] == '@')
        return 0;
    else
        return 1;
}

// Funkcija za detektovanje kolizija
// sa levim zidovima
int collision_left(){

    if(is_game_over)
        return 0;

    int poz1 = floor(lopta.z+0.1);
    int poz2 = round(lopta.x-0.2);
    int poz3 = round(lopta.x+0.2);

    if(is_win(poz2, poz1)){
        is_game_over = 1;
    }

    if(matrix[poz2][poz1] == '@' || matrix[poz3][poz1] == '@')
        return 0;
    else
        return 1;
}

// Funkcija za detektovanje kolizija
// sa desnim zidovima
int collision_right(){

    if(is_game_over)
        return 0;

    int poz1 = floor(lopta.z+0.9);
    int poz2 = round(lopta.x-0.2);
    int poz3 = round(lopta.x+0.2);

    if(is_win(poz2, poz1)){
        is_game_over = 1;
    }

    if(matrix[poz2][poz1] == '@' || matrix[poz3][poz1] == '@')
        return 0;
    else
        return 1;
}

// Funkcija koja vrsi inicijalizaciju globalnih promenljivih
void initialize(){
    phi = pi/2;
    theta = pi/4;

    delta_phi = pi/90;
    delta_theta = pi/90;

    glavna();
    start = find_start();
    finish = find_finish();

    lopta.x = start.x;
    lopta.y = start.y;
    lopta.z = start.z;

    is_game_over = 0;

    _h = (double)(-_width*5/2);
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
    glClearColor(0, 0, 0, 0);

    glEnable(GL_DEPTH_TEST);
    init_texture();
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
        case 'w': // Kretanje napred
        case 'W':
            if(!is_game_over){
                if(collision_front()) // Proverava se kolizija sa prednjim zidom
                    lopta.x += 0.2;
                break;
            }
        case 'a': // Kretanje levo
        case 'A':
            if(!is_game_over){
                if(collision_left()) // Proverava se kolizija sa levim zidom
                    lopta.z -= 0.2;
                break;
            }
        case 's': // Kretanje nazad
        case 'S':  
            if(!is_game_over){
                if(collision_back()) // Proverava se kolizija sa zadnjim zidom
                    lopta.x -= 0.2;
                break;
            }
        case 'd': // Kretanje desno
        case 'D':
            if(!is_game_over){
                if(collision_right()) // Proverava se kolizija sa desnim zidom
                    lopta.z += 0.2;
                break;
            }
        case 'p': // Dekrementira se ugao phi i ponovo iscrtava scena
        case 'P':
            if(phi > -pi/2)
                phi -= delta_phi;
            break;
        case 'o':  // Inkrementira se ugao phi i ponovo iscrtava scena
        case 'O':
            if(phi < pi/2)
                phi += delta_phi;
            break;
        /*case 'm': // Ispisujemo "Game over!"
        case 'M':
            is_game_over = !is_game_over;
            break;*/
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

// Funkcija koja regulise akcije
// prilikom promene dimenzija prozora
void on_reshape(int width, int height){

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 1, 1000);
    glutFullScreen();
}

void on_display(void){

    glShadeModel(GL_FLAT);

    if(!is_game_over){

        set_light(); // Podesava se osvetljenje

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Brise se prethodni sadrzaj prozora
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        gluLookAt(-100, 200 + 100*cos(theta)*sin(phi), -100, 0, 0, 0, 0, 1, 0);

        glMultMatrixf(matrixR);

        //draw_coordinate_system();

        draw_floor();
        draw_maze();
        
        // Iscrtava se lopta
        glPushMatrix();
            glTranslatef(5*lopta.x+_h, 1.5, 5*lopta.z+_h);
            draw_player();
        glPopMatrix();
    }
    else{
        glClearColor(0, 0, 0, 0);
        draw_game_over();
    }

    glutSwapBuffers();
}
