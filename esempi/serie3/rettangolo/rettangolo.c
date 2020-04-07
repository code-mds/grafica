#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#include <GL\glew.h>
#include <GL\freeglut.h>

void draw() {
	glClearColor(0.0, 0.0, 0.0, 0.0);  	
  	glClear(GL_COLOR_BUFFER_BIT);	
   
   	glLoadIdentity();
	glColor3f(1.0, 1.0, 1.0);			
    glOrtho(0.0, 4.0, 0.0, 4.0, -1.0, 1.0);	 
    
  	GLint v1[] = {1,1};
    GLint v2[] = {3,2};
    
    glRectiv(v1,v2);


    glFlush();
    
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);				// chiamate glut per la gestione delle finestre
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("openGL");
    glutDisplayFunc(draw);
    glutMainLoop();
}

