#include <GL/glut.h>
#include <stdlib.h>

#include "mazeGenerator.h"

static void on_display();
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);

int width = 39, height = 39;

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

    // int i, j;
   
    // for(i = 0; i < height; i++){
    //     for(j = 0; j < width; j++){
    //         glLoadIdentity();
    //         if(matrix[i][j] == '@'){
    //             glPushMatrix();
    //                 glColor3f(0.0, 1.0, 0.0);
    //                 glTranslatef(5.0,5.0,0.0);
    //                 glutSolidCube(5);
    //             glPopMatrix();
    //         }
    //     }
    // }   
}
// Sve ovo iznad sam stavio pod komentar

// void draw_maze(){

//     glPushMatrix();
//         glColor3f(0.0, 1.0, 0.0);
//         glTranslatef(0, 2.5, 0);
//         glutSolidCube(5);
//     glPopMatrix();

// }

int main(int argc, char** argv){

    //Inicijalizacija gluta
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    //Kreiranje prozora
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Forgotten Paths");

    //Registruju se callback funkcije
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);

    //Obavlja se OpenGL  inicijalizacija
    glClearColor(0.75, 0.75, 0.75, 0);

    glEnable(GL_DEPTH_TEST);

    //Program ulazi u glavnu petlju
    glutMainLoop();

    return 0;
}
//Funkcija za obradu komandi sa tastature
void on_keyboard(unsigned char key, int x, int y){
    
    switch(key){

        case 27:
            exit(EXIT_SUCCESS);
            break;
    }

    glutPostRedisplay();
}

void on_reshape(int width, int height){

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 1, 100);
}

void on_display(void){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(10, 30, 20, 0, 0, 0, 0, 1, 0);

    draw_coordinate_system();

    draw_maze();

    glutSwapBuffers();
}
