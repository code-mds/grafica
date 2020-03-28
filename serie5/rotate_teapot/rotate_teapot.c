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

#define AXIS_LENGHT 1.0
#define RITARDO 10

static GLfloat angle = 0.0; // angolo di rotazione
static GLboolean do_spin = 0;

void assi_e_centro() {
    glBegin(GL_LINES);
        glLineWidth(2.0);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(- AXIS_LENGHT,  0.0, 0.0);
        glVertex3f( AXIS_LENGHT,  0.0, 0.0);
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0.0,  AXIS_LENGHT, 0.0);
        glVertex3f(0.0, -AXIS_LENGHT, 0.0);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0.0,  0.0, AXIS_LENGHT);
        glVertex3f(0.0, 0.0, -AXIS_LENGHT);
    glEnd();
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(10.0);
    glBegin(GL_POINTS);
        glVertex2f(-0.0, 0.0);
    glEnd();
    glLineWidth(1.0);
    glPointSize(1.0);
}

void set_viewpoint (){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1.0,2.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    set_viewpoint ();
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2.0);
    assi_e_centro();
    glTranslatef (-0.5,0.0,0.0);
    glutWireCube(0.3);
    glTranslatef (1.0,0.0,0.0);
    glRotatef(angle, 0.0, 1.0, 0.0);
    glutWireTeapot(0.3);
    glutSwapBuffers();
}

void spinDisplay(int id)
{
    angle = angle + 1.0;
    if (angle > 360.0)
        angle = angle - 360.0;
    glutPostRedisplay();
    glutTimerFunc(RITARDO, spinDisplay, id);
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLint) w, (GLint) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w,
                    1.5*(GLfloat)h/(GLfloat)w, -5.0, 5.0);
    else
        glOrtho(-1.5*(GLfloat)w/(GLfloat)h,
                    1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -5.0, 5.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)	{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (100, 100);
    glutCreateWindow (argv[0]);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glClearColor (1.0, 1.0, 1.0, 0.0);
    glPolygonMode(GL_FRONT,GL_LINE);

    glutReshapeWindow (500,500);
    glutPostRedisplay();
    glutTimerFunc(RITARDO, spinDisplay, 1);
    glutMainLoop();
}
