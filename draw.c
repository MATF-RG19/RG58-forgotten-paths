#include <GL/glut.h>
#include "draw.h"
#include "mazeGenerator.h"

int __height = 39;
int __width = 39;

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

    for(i=0; i<__width; i++){
        for(j=0; j<__height; j++){
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
