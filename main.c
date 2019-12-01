#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "mazeGenerator.h"

typedef struct Point{
    double x;
    double y;
    double z;
} Point;

Point start;
Point finish;

static void on_display();
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);

int _width = 39, _height = 39;

void set_light(){
    // Pozicija svetla
    GLfloat light_position[] = { 1, 1, 1, 0 };

    // Ambijentalna komponenta svetlosti
    GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1 };

    // Difuzna komponenta svetlosti
    GLfloat light_diffuse[] = { 0.95, 0.95, 0.95, 1 };

    // Spekularna komponenta svetlosti
    GLfloat light_specular[] = { 0.8, 0.8, 0.2, 1 };

    // Koeficijenti ambijentalne refleksije materijala
    GLfloat ambient_coeffs[] = { 0.5, 0.5, 0.1, 1 };

    // Koeficijenti difuzne refleksije materijala
    GLfloat diffuse_coeffs[] = { 1, 1, 0.8, 1 };

    // Koeficijenti spekularne refleksije materijala
    GLfloat specular_coeffs[] = { 1, 1, 1, 0 };

    // Koeficijent glatkosti materijala
    GLfloat shininess = 20;

    // Brise se prethodni sadrzaj prozora
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Ukljucuje se osvjetljenje i podesavaju parametri svetla
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    // Podesavaju se parametri materijala
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}

void draw_coordinate_system(){
    // Iscrtavanje x ose
    glPushMatrix();
        glColor3f(1,0,0);
        glBegin(GL_LINES);
            glVertex3f(100,0,0);
            glVertex3f(-100,0,0);
        glEnd();
    glPopMatrix();

    // Iscrtavanje y ose
    glPushMatrix();
        glColor3f(0,1,0); 
        glBegin(GL_LINES); 
            glVertex3f(0,-100,0);
            glVertex3f(0,100,0);
        glEnd();
    glPopMatrix();

    // Iscrtavanje z ose
    glPushMatrix();
        glColor3f(0,0,1); 
        glBegin(GL_LINES);
            glVertex3f(0,0,100);
            glVertex3f(0,0,-100);
        glEnd();
    glPopMatrix();
}

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

Point find_finish(){
    double _x;
    double _z;

    int i, j;

    for(i = _width-1; i >= 0; i--)
        for(j = _height-1; j >= 0; j--)
            if(matrix[i][j] == '@'){
                _x = i;
                _z = j;
                break;
            }
    Point res;

    res.x = _x;
    res.z = _z;
    res.y = 0;
    
    return res;
}

// Iscrtavanje poda
void draw_floor(){
    glPushMatrix();
        glBegin(GL_POLYGON);
            glColor3f(1, 1, 1);
            glVertex3f(0, 0, 0);
            glVertex3f(0, 0, 195);
            glVertex3f(195, 0, 195);
            glVertex3f(195, 0, 0);
        glEnd();
    glPopMatrix();
}

// Iscrtavanje lavirinta uz pomoc matrice
// u kojoj je generisan 
void draw_maze(){

    int i, j;

    for(i=0; i<_width; i++){
        for(j=0; j<_height; j++){
            if(matrix[i][j] == '@'){
                glPushMatrix();
                    glTranslatef(5*i, 5, 5*j);
                    glScalef(5, 10, 5);
                    glutSolidCube(1);
                glPopMatrix();
            }
        }
    }
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
            break;
        case ('a'|'A'): // Kretanje levo
            break;
        case ('s'|'S'): // Kretanje dole
            break;
        case ('d'|'D'): // Kretanje desno
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

    draw_coordinate_system();

    draw_maze();
    draw_floor();

    glutSwapBuffers();
}