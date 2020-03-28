//glut_test.cpp
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

// Headers richiesti da OSX
#ifdef __APPLE__
//#include <OpenGL/gl3.h>
//#include <GL/glew.h>
#include <GLUT/glut.h>
//#include <iostream>

// headers richiesti da Windows e linux
#else
#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
//#include <iostream>

#endif

void rettangolo() {
    glBegin(GL_POLYGON);
    glVertex2f(-0.5, -0.5);
    glVertex2f( 0.5, -0.5);
    glVertex2f( 0.5,  0.5);
    glVertex2f(-0.5,  0.5);
    glEnd();
}

void assi_e_centro() {
    glBegin(GL_LINES);
    glVertex2f(-1.2,  0.0);
    glVertex2f( 1.2,  0.0);
    glVertex2f(0.0,  1.2);
    glVertex2f(0.0, -1.2);
    glEnd();
    glPointSize(10.0);
    glBegin(GL_POINTS);
    glVertex2f(-0.5, -0.5);
    glEnd();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(1.0);
    assi_e_centro() ;
    glLineWidth(3.0);
    rettangolo();
    glTranslatef(-0.5,-0.5,0.0);
    glColor3f(1.0, 0.0, 0.0);
    rettangolo();
    glRotatef(30.0,0.0,0.0,1.0);
    glColor3f(0.0, 1.0, 0.0);
    rettangolo();
    glTranslatef(0.5,0.5,0.0);
    glColor3f(0.0, 0.0, 1.0);
    rettangolo();
    glFlush();
}


void reshape(int w, int h) {
    glViewport(0, 0, (GLint) w, (GLint) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        gluOrtho2D (-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w,
                    1.5*(GLfloat)h/(GLfloat)w);
    else
        gluOrtho2D (-1.5*(GLfloat)w/(GLfloat)h,
                    1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)	{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (100, 100);
    glutCreateWindow (argv[0]);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glClearColor (1.0, 1.0, 1.0, 0.0);
    glPolygonMode(GL_FRONT,GL_LINE);

    glutReshapeWindow (500,500);
    glutMainLoop();
}
