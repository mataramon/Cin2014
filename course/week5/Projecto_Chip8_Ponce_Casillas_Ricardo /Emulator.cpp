#include "corechip8.h"
#include <GL/glut.h>
#include <iostream>


void keyDown(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void initGL();
void render();
void draw_square(float x_coord, float y_coord);
void idle();


CoreChip8 Core;




int main(int argc, char **argv){

	if (argc == 1){
		cerr << "Error: no input file " << endl;
		return 1;
	}

        Core.init();
        Core.LoadGame(argv[1]);

	glutInit(&argc, argv);          
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(640, 320);
        glutInitWindowPosition(320, 320);
	glutCreateWindow("Emulator");


        initGL();

	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);

	glutDisplayFunc(render);

        glutIdleFunc(idle);

        glutMainLoop();

return 0;
}



void keyDown(unsigned char key, int x, int y){

	if(key == 27)    
		exit(0);

	if(key == '1')		Core.Keys[0x1] = 1;
	else if(key == '2')	Core.Keys[0x2] = 1;
	else if(key == '3')	Core.Keys[0x3] = 1;
	else if(key == '4')	Core.Keys[0xC] = 1;

	else if(key == 'q')	Core.Keys[0x4] = 1;
	else if(key == 'w')	Core.Keys[0x5] = 1;
	else if(key == 'e')	Core.Keys[0x6] = 1;
	else if(key == 'r')	Core.Keys[0xD] = 1;

	else if(key == 'a')	Core.Keys[0x7] = 1;
	else if(key == 's')	Core.Keys[0x8] = 1;
	else if(key == 'd')	Core.Keys[0x9] = 1;
	else if(key == 'f')	Core.Keys[0xE] = 1;

	else if(key == 'z')	Core.Keys[0xA] = 1;
	else if(key == 'x')	Core.Keys[0x0] = 1;
	else if(key == 'c')	Core.Keys[0xB] = 1;
	else if(key == 'v')	Core.Keys[0xF] = 1;

}

void keyUp(unsigned char key, int x, int y){

     if(key == '1')		Core.Keys[0x1] = 0;
     else if(key == '2')	Core.Keys[0x2] = 0;
     else if(key == '3')	Core.Keys[0x3] = 0;
     else if(key == '4')	Core.Keys[0xC] = 0;

     else if(key == 'q')	Core.Keys[0x4] = 0;
     else if(key == 'w')	Core.Keys[0x5] = 0;
     else if(key == 'e')	Core.Keys[0x6] = 0;
     else if(key == 'r')	Core.Keys[0xD] = 0;

     else if(key == 'a')	Core.Keys[0x7] = 0;
     else if(key == 's')	Core.Keys[0x8] = 0;
     else if(key == 'd')	Core.Keys[0x9] = 0;
     else if(key == 'f')	Core.Keys[0xE] = 0;

     else if(key == 'z')	Core.Keys[0xA] = 0;
     else if(key == 'x')	Core.Keys[0x0] = 0;
     else if(key == 'c')	Core.Keys[0xB] = 0;
     else if(key == 'v')	Core.Keys[0xF] = 0;
}


void initGL() {

     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluOrtho2D(0.0,640, 320, 0.0);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();

     glClearColor(0.f, 0.f, 0.f, 1.f);
}



void render(){

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    Core.FDXemulate();

    int i, j;
    for (i = 0; i < 64; i++) {
         for (j = 0; j < 32; j++) {
             if (Core.Screen[i][j] == 1) draw_square((float)(i * 10), (float)(j * 10));

         } 
    } 

    glutSwapBuffers();
    Core.DecrementTimers();
}


void draw_square(float x_coord, float y_coord) {

     glBegin(GL_QUADS);
     glColor3f(0.0f, 1.0f, 1.0f);
     glVertex2f(x_coord, y_coord);
     glVertex2f(x_coord + 10, y_coord);
     glVertex2f(x_coord + 10, y_coord + 10);
     glVertex2f(x_coord, y_coord + 10);
     glEnd();
}


void idle() {
     glutPostRedisplay();
} 
