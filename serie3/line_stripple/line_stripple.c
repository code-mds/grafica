#include <stdio.h>
//#include <GL/gl.h>
#include <GLUT/glut.h>


void draw() {
	glClearColor(0.0, 0.0, 0.0, 0.0);  	
  	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();		
   
	glColor3f(1.0, 1.0, 1.0);			
    glOrtho(0.0, 4.0, 0.0, 4.0, -1.0, 1.0);	    
  
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, 0xf0f0);

  	glBegin(GL_LINE_LOOP);				//definisce il poligono e i 4 vertici
    	glVertex2i(1, 1);
    	glVertex2i(3, 1);
    	glVertex2i(3, 3);
    	glVertex2i(1, 3);
    glEnd();


	glDisable(GL_LINE_STIPPLE);
    
    glFlush();						
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);				// chiamate glut per la gestione delle finestre
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("whitesquare");
    glutDisplayFunc(draw);
    glutMainLoop();
}

