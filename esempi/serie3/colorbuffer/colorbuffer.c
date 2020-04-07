
#include <stdio.h>
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

void draw() {
	glClearColor(1.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);		
    
    glFlush();							
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);				// chiamate glut per la gestione delle finestre
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("colorbuffer");
    glutDisplayFunc(draw);
    glutMainLoop();
}
