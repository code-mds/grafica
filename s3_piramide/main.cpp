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

const float SCENE_WIDTH = 600.0f;
const float SCENE_HEIGHT = 600.0f;
const float X = 3.0f;
const float Z = 3.0f;
const float Y = 6.0f;

void draw_axis();

void draw_pyramid();

void triangle3D(GLfloat* v1, GLfloat* v2, GLfloat* v3) {
    glBegin(GL_TRIANGLES);
    glVertex3fv(v1);
    glVertex3fv(v2);
    glVertex3fv(v3);
    glEnd();
}

void draw() {
    glClear( GL_COLOR_BUFFER_BIT );
    draw_axis();
    draw_pyramid();
    glFlush();
}

void draw_axis() {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0xf0f0);
    // axes are ten units long.
    glBegin(GL_LINES);
    // Draw a red x-axis
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(10, 0, 0);
    // Draw a green y-axis
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 10, 0);
    // Draw a blue z-axis
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 10);
    glEnd();
    glDisable(GL_LINE_STIPPLE);
}

void draw_pyramid() {
    GLfloat vertices[4][3][3] = {
            {
                {-X,  0.0f, Z},    // Vertex 1 (X, Y, Z)
                {X, 0.0f, Z},      // Vertex 2 (X, Y, Z)
                {0.0f, Y, 0.0f}     // Vertex 3 (X, Y, Z)
            },
            {
                {X,  0.0f, Z},
                {X, 0.0f, -Z},
                {0.0f, Y, 0.0f}
            },
            {
                {X,  0.0f, -Z},
                {-X, 0.0f, -Z},
                {0.0f, Y, 0.0f}
            },
            {
                {-X,  0.0f, -Z},
                {-X, 0.0f, Z},
                {0.0f, Y, 0.0f}
            },

    };

    for (int i = 0; i < 4; ++i) {
        // face
        glColor3ub(0, 100+i*50, 0);
        glPolygonMode(GL_FRONT,GL_FILL);
        triangle3D(vertices[i][0], vertices[i][1], vertices[i][2]);

        // wireframe
        glColor3ub(15, 32, 112);
        glPolygonMode(GL_FRONT, GL_LINE);
        triangle3D(vertices[i][0], vertices[i][1], vertices[i][2]);
    }
}

void init(void) {
    glEnable(GL_CULL_FACE);
    glClearColor(180/255.0,180/255.0, 180/255.0, 0.0); // GREY
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Position camera at (4, 6, 5) looking at (0, 0, 0) with the vector <0, 1, 0> pointing upward.
    gluLookAt(1, 1, 2, 0, 0, 0, 0, 1, 0);
}

void reshape(int w, int h) {
    printf("reshape: w=%d, h=%d\n",w,h);
    glViewport(0, 0, (GLint) w, (GLint) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h) {
        double aspect_ratio = (GLfloat)h/(GLfloat)w;
        glOrtho (-10.0, 10.0, -10.0*aspect_ratio, 10.0*aspect_ratio, -10.0, 100.0);
    }
    else {
        double aspect_ratio = (GLfloat) w / (GLfloat) h;
        glOrtho(-10.0 * aspect_ratio, 10.0 * aspect_ratio, -10.0, 10.0, -10.0, 100.0);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
//    gluLookAt(1, 1, 1, 0, 0, 0, 0, 1, 0);
}

void keyboardS(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_RIGHT:
            glRotatef(1.0,0.0,1.0,0.0);
            glutPostRedisplay();
            break;
        case GLUT_KEY_LEFT:
            glRotatef(-1.0,0.0,1.0,0.0);
            glutPostRedisplay();
            break;
    }
}
int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(SCENE_WIDTH, SCENE_HEIGHT);
    glutCreateWindow("bandiera scozzese");
    init();
    glutDisplayFunc(draw);
    glutSpecialFunc(keyboardS);
    glutMainLoop();
}