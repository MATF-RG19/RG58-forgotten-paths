#include <GL/glut.h>
#include "../Headers/draw.h"
#include "../Headers/mazeGenerator.h"
#include "../Headers/image.h"
#include <stdio.h>
#include <string.h>

#define MAX_LENGTH (100) // Maksimalna duzina reci

// Visina i sirina naseg lavirinta
int __height = 39;
int __width = 39;

char word[MAX_LENGTH];

double h = (double)(-39*5/2);

static GLuint names[1]; // Niz imena tekstura
#define FILENAME0 "../Textures/floor.bmp" // Tekstura poda

// Funkcija za inicijalizovanje tekstura
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

// Iscrtavanje i teksturisanje poda
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

// Iscrtavanje igraca
void draw_player(){
    glColor3f(1, 0, 0);
    GLUquadric *quad;
    quad = gluNewQuadric();
    gluSphere(quad,1.5,1000,10);
}

void renderStrokeString(int x, int y,int z,void* font, char *string){

    int len; // Duzina reci
    glDisable(GL_LIGHTING);
    glColor3f(1,0,0); // Postavljamo boju teksta
    // Postavljamo dimenzije slova
    glScalef(0.01,0.01,5);
    glTranslatef(x,y,z);
    len = strlen(string);
    for (int i = 0; i < len; i++)
    {
        glutStrokeCharacter(font, string[i]);
    }
    glEnable(GL_LIGHTING); // Ponovo ukljucujemo osvetljenje
}

void draw_game_over(){   

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);

    // Centriramo koordinate za ispis teksta
    const int x = -540;
    const int y = 0;
    const int z = 0;

    // Ispisujemo "Game over!"
    sprintf(word,"Game over!");
    glPushMatrix();
        glScalef(0.05, 0.05, 5);
        glPushAttrib(GL_LINE_BIT);
            glLineWidth(5); // Postavljamo debljinu linije
            renderStrokeString(x, y, z, GLUT_STROKE_MONO_ROMAN, word);
        glPopAttrib();
    glPopMatrix();
}
