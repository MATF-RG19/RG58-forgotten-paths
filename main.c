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
            glColor3f(0, 1, 0.7);
            glVertex3f(0, 0, 0);
            glVertex3f(0, 0, 78);
            glVertex3f(78, 0, 78);
            glVertex3f(78, 0, 0);
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
                    glTranslatef(2*i, 5, 2*j);
                    glScalef(2, 10, 2);
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
    glutInitWindowSize(800, 800);
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

        // Prekidanje igrice
        case 27:
            exit(EXIT_SUCCESS);
            break;
        case 'w':
            break;
        case 'a':
            break;
        case 's':
            break;
        case 'd':
            break;
        case 'x':
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

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(40, 300, 40, 50, 50, 50, 0, 1, 0);

    draw_coordinate_system();

    draw_maze();
    draw_floor();

    glutSwapBuffers();
}