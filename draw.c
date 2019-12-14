#include <GL/glut.h>
#include "draw.h"
#include "mazeGenerator.h"
#include "image.h"

int __height = 39;
int __width = 39;

double h = (double)(-39*5/2);

static GLuint names[1]; // Niz imena tekstura
#define FILENAME0 "floor.bmp" // Tekstura poda

// Funkcija za inicijalizovanje struktura
void init_texture(){

    glEnable(GL_TEXTURE_2D);

    glTexEnvf(GL_TEXTURE_ENV,
              GL_TEXTURE_ENV_MODE,
              GL_REPLACE);

    Image * image; // Objekat koji predstavlja teksturu

    image = image_init(0, 0); // Ucitavamo sliku koja predstavlja teksturu

    image_read(image, FILENAME0);

    glGenTextures(1, names); // Vrsi se generisanje identifikatora tekstura

    glBindTexture(GL_TEXTURE_2D, names[0]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    glBindTexture(GL_TEXTURE_2D, 0); // Iskljucujemo teksturu

    image_done(image);
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

// Iscrtavanje poda
void draw_floor(){
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, names[0]);
        glBegin(GL_POLYGON);
            glColor3f(1, 1, 1);
            glTexCoord2f(0, 0);
            glVertex3f(-h, 0, -h);
            glTexCoord2f(0, h);
            glVertex3f(-h, 0, h);
            glTexCoord2f(h, h);
            glVertex3f(h, 0, h);
            glTexCoord2f(h, 0);
            glVertex3f(h, 0, -h);
        glEnd();
        glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}

// Iscrtavanje lavirinta uz pomoc matrice
// u kojoj je generisan 
void draw_maze(){

    int i, j;

    for(i=0; i<__width; i++){
        for(j=0; j<__height; j++){
            if(matrix[i][j] == '@'){
                glPushMatrix();
                    glTranslatef(h + 5*i, 5, h + 5*j);
                    glScalef(5, 10, 5);
                    glColor3f(0, 0, 1);
                    glutSolidCube(1);
                glPopMatrix();
            }
        }
    }
}

void draw_player(){
    glColor3f(1, 0, 0);
    GLUquadric *quad;
    quad = gluNewQuadric();
    gluSphere(quad,1.5,1000,10);
}