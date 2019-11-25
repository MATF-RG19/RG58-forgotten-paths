#include <GL/glut.h>
#include <stdio.h>
#include <time.h>

#include "draw.h"
//#include "mazeGenerator.h"

int width = 39, height = 39;

/*
void draw_maze(){ 

    Node *start, *last;

	//Nasumican seed
	srand(time(NULL));
	
	//Inicijalizuj lavirint
    init();
	
	//Podesi pocetni cvor
	start = nodes + 1 + width;
	start->parent = start;
	last = start;

    	//Povezuj cvorove dok pocetni cvor nije dostignut
	while((last = link(last)) != start);	

	//Pravi ulaz i izlaz
	edit_maze();

	matrix = make_matrix();

	//draw();

    int i, j;
   
    for(i = 0; i < height; i++)
        for(j = 0; j < width; j++)
            if(matrix[i][j] == '@'){
                glPushMatrix();
                glColor3f(0.0, 1.0, 0.0);
                glTranslatef(10.0,30.0,0.0);
                glutSolidCube(5);
                glPopMatrix();
            }
}
Sve ovo iznad sam stavio pod komentar
*/

void draw_maze(){

    glPushMatrix();
    glColor3f(0.0, 1.0, 0.0);
    glTranslatef(10.0, 30.0, 0.0);
    glutSolidCube(5);
    glPopMatrix();

}

void draw_coordinate_system(){
    //Iscrtavanje x ose
    glPushMatrix();
        glColor3f(1,0,0);
        glBegin(GL_LINES);
            glVertex3f(100,0,0);
            glVertex3f(-100,0,0);
        glEnd();
    glPopMatrix();

    //Iscrtavanje y ose
    glPushMatrix();
        glColor3f(0,1,0); 
        glBegin(GL_LINES); 
            glVertex3f(0,-100,0);
            glVertex3f(0,100,0);
        glEnd();
    glPopMatrix();

    //Iscrtavanje z ose
    glPushMatrix();
        glColor3f(0,0,1); 
        glBegin(GL_LINES);
            glVertex3f(0,0,100);
            glVertex3f(0,0,-100);
        glEnd();
    glPopMatrix();
}
