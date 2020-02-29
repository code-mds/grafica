#pragma clang diagnostic ignored "-Wdeprecated-declarations"
// Headers richiesti da OSX
#ifdef __APPLE__
//#include <OpenGL/gl3.h>
#include <GL/glew.h>
#include <GLUT/glut.h>
// headers richiesti da Windows e linux
#else
#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#endif



void draw() {
	glClearColor(0.0, 0.0, 0.0, 0.0);  	
  	glClear(GL_COLOR_BUFFER_BIT);	
	glLoadIdentity();		

	glColor3f(1.0, 1.0, 1.0);			
    glOrtho(0.0, 30.0, 0.0, 30.0, -1.0, 1.0);	 
    
    GLint v0[] = {8,19};
    GLint v1[] = {6,14};
 	GLint v2[] = {14,21};
 	GLint v3[] = {14,13};
 	GLint v4[] = {19,21};
	GLint v5[] = {20,11};

	glBegin(GL_TRIANGLE_STRIP);
		glVertex2iv(v0);
		glVertex2iv(v1);		
		glVertex2iv(v2);
		glColor3f(1.0, 0.0, 0.0);			
    	glVertex2iv(v3);
		glColor3f(0.0, 1.0, 0.0);				
    	glVertex2iv(v4);
		glVertex2iv(v5);
    glEnd();

    
    glFlush();							
}


void reshape(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);				// chiamate glut per la gestione delle finestre
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("whitesquare");
    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);
    glutMainLoop();
}

