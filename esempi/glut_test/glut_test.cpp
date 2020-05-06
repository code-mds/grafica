//glut_test.cpp
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

// Headers richiesti da OSX
#ifdef __APPLE__
//#include <OpenGL/gl3.h>
#include <GL/glew.h>
#include <GLUT/glut.h>
#include <iostream>

// headers richiesti da Windows e linux
#else
#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

#endif

using namespace std;

/* Display callback function */
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    /* Display a red square */
    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(-0.5f, 0.5f);
    glEnd();

    glutSwapBuffers();
}


/* Keyboard callback function */
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        /* Exit on escape key press */
        case '\x1B':
        {
            exit(EXIT_SUCCESS);
            break;
        }
    }
}

void reshape(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}



int main(int argc, char* argv[]) {

    // Initialize GLUT
    glutInit(&argc, argv);
    // Set up some memory buffers for our display
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    // Set the window size
    glutInitWindowSize(800, 600);

    /* Create a single window with a keyboard, display and reshape callback */
    glutCreateWindow("GLUT Test");
    glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
    glutDisplayFunc(display);



    // This initializes the entry points in the OpenGL driver so we can
    // call all the functions in the API.
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "GLEW error");
        return 1;
    }

    glutMainLoop();
    return 0;
}

