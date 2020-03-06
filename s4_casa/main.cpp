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
// headers richiesti da Windows e linux
#else
#include <GL\glew.h>
#include <GL\freeglut.h>
#include "draw_utils.h"
#endif

using namespace std;

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;
const float SCENE_WIDTH = 10.0f;
const float SCENE_HEIGHT = 10.0f;

void draw_triangle_walls();
void draw_perimetral_walls();
void draw_roof();

void draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw_axis();
    draw_perimetral_walls();
    draw_triangle_walls();
    draw_roof();
    glFlush();
}

void draw_roof() {
    GLfloat vertices[][8][3] = {
            // right roof wall
            {
                    { 6/SCENE_WIDTH, 6/SCENE_WIDTH, 1/SCENE_WIDTH },
                    { 6/SCENE_WIDTH,  6/SCENE_WIDTH, -9/SCENE_WIDTH},
                    { 0,  12/SCENE_WIDTH, -9/SCENE_WIDTH },
                    { 0,  12/SCENE_WIDTH, 1/SCENE_WIDTH },

                    { 6/SCENE_WIDTH,  5/SCENE_WIDTH, -9/SCENE_WIDTH},
                    { 6/SCENE_WIDTH, 5/SCENE_WIDTH, 1/SCENE_WIDTH },
                    { 0,  11/SCENE_WIDTH, 1/SCENE_WIDTH },
                    { 0,  11/SCENE_WIDTH, -9/SCENE_WIDTH },
            },
            // left roof wall
            {
                    { -6/SCENE_WIDTH,  6/SCENE_WIDTH, -9/SCENE_WIDTH},
                    { -6/SCENE_WIDTH, 6/SCENE_WIDTH, 1/SCENE_WIDTH },
                    { 0,  12/SCENE_WIDTH, 1/SCENE_WIDTH },
                    { 0,  12/SCENE_WIDTH, -9/SCENE_WIDTH },

                    { -6/SCENE_WIDTH, 5/SCENE_WIDTH, 1/SCENE_WIDTH },
                    { -6/SCENE_WIDTH,  5/SCENE_WIDTH, -9/SCENE_WIDTH},
                    { 0,  11/SCENE_WIDTH, -9/SCENE_WIDTH },
                    { 0,  11/SCENE_WIDTH, 1/SCENE_WIDTH },
            }
    };

    int nrOfWalls = sizeof(vertices) / sizeof(vertices[0]);
    for (int i = 0; i < nrOfWalls; ++i) {
        glColor3ub(255, 0, 0);
        glPolygonMode(GL_FRONT,GL_FILL);

        draw_paralleliped(vertices[i][0], vertices[i][1], vertices[i][2], vertices[i][3],
                          vertices[i][4], vertices[i][5], vertices[i][6], vertices[i][7], .0f);
        draw_paralleliped(vertices[i][0], vertices[i][1], vertices[i][2], vertices[i][3],
                          vertices[i][4], vertices[i][5], vertices[i][6], vertices[i][7], 1.0f);
    }
}

void draw_triangle_walls() {
    GLfloat vertices[][3][3] = {
            {
                    { -5/SCENE_WIDTH,  6/SCENE_WIDTH, 0},
                    { 5/SCENE_WIDTH, 6/SCENE_WIDTH, 0 },
                    { 0,  11/SCENE_WIDTH, 0 }
            },
            {
                    { 5/SCENE_WIDTH, 6/SCENE_WIDTH, -8/SCENE_WIDTH },
                    { -5/SCENE_WIDTH,  6/SCENE_WIDTH, -8/SCENE_WIDTH},
                    { 0,  11/SCENE_WIDTH, -8/SCENE_WIDTH }
            }
    };
    int nrOfWalls = sizeof(vertices) / sizeof(vertices[0]);
    for (int i = 0; i < nrOfWalls; ++i) {
        glColor3ub(255, 255, 255);
        glPolygonMode(GL_FRONT,GL_FILL);
        draw_triangle3D(vertices[i][0], vertices[i][1], vertices[i][2], 0);
        draw_triangle3D(vertices[i][0], vertices[i][1], vertices[i][2], 1.0);
    }
}

void draw_perimetral_walls() {

    GLfloat vertices[][8][3] = {
            // front walls
            {
                    { 2/SCENE_WIDTH, 0, 0 },
                    { 5/SCENE_WIDTH, 0, 0},
                    { 5/SCENE_WIDTH, 6/SCENE_WIDTH, 0 },
                    { 2/SCENE_WIDTH, 6/SCENE_WIDTH, 0 },

                    { 5/SCENE_WIDTH, 0, -1/SCENE_WIDTH},
                    { 2/SCENE_WIDTH, 0, -1/SCENE_WIDTH },
                    { 2/SCENE_WIDTH, 6/SCENE_WIDTH, -1/SCENE_WIDTH },
                    { 5/SCENE_WIDTH, 6/SCENE_WIDTH, -1/SCENE_WIDTH },
            },
            {
                    { -5/SCENE_WIDTH, 0, 0},
                    { -2/SCENE_WIDTH, 0, 0 },
                    { -2/SCENE_WIDTH, 6/SCENE_WIDTH, 0 },
                    { -5/SCENE_WIDTH, 6/SCENE_WIDTH, 0 },

                    { -2/SCENE_WIDTH, 0, -1/SCENE_WIDTH },
                    { -5/SCENE_WIDTH, 0, -1/SCENE_WIDTH},
                    { -5/SCENE_WIDTH, 6/SCENE_WIDTH, -1/SCENE_WIDTH },
                    { -2/SCENE_WIDTH, 6/SCENE_WIDTH, -1/SCENE_WIDTH },
            },
            //right wall
            {
                    { 5/SCENE_WIDTH, 0, 0},
                    { 5/SCENE_WIDTH, 0, -8/SCENE_WIDTH },
                    { 5/SCENE_WIDTH, 6/SCENE_WIDTH, -8/SCENE_WIDTH },
                    { 5/SCENE_WIDTH, 6/SCENE_WIDTH, 0 },

                    { 4/SCENE_WIDTH, 0, -8/SCENE_WIDTH },
                    { 4/SCENE_WIDTH, 0, 0},
                    { 4/SCENE_WIDTH, 6/SCENE_WIDTH, 0 },
                    { 4/SCENE_WIDTH, 6/SCENE_WIDTH, -8/SCENE_WIDTH },

            },
            // back wall
            {
                    { 5/SCENE_WIDTH, 0, -8/SCENE_WIDTH },
                    { -5/SCENE_WIDTH,  0, -8/SCENE_WIDTH},
                    { -5/SCENE_WIDTH,  6/SCENE_WIDTH, -8/SCENE_WIDTH },
                    { 5/SCENE_WIDTH,  6/SCENE_WIDTH, -8/SCENE_WIDTH },

                    { -5/SCENE_WIDTH,  0, -7/SCENE_WIDTH},
                    { 5/SCENE_WIDTH, 0, -7/SCENE_WIDTH },
                    { 5/SCENE_WIDTH,  6/SCENE_WIDTH, -7/SCENE_WIDTH },
                    { -5/SCENE_WIDTH,  6/SCENE_WIDTH, -7/SCENE_WIDTH },
            },
            //left wall
            {
                    { -5/SCENE_WIDTH,  0, -8/SCENE_WIDTH},
                    { -5/SCENE_WIDTH, 0, 0 },
                    { -5/SCENE_WIDTH,  6/SCENE_WIDTH, 0 },
                    { -5/SCENE_WIDTH,  6/SCENE_WIDTH, -8/SCENE_WIDTH },

                    { -4/SCENE_WIDTH, 0, 0 },
                    { -4/SCENE_WIDTH,  0, -8/SCENE_WIDTH},
                    { -4/SCENE_WIDTH,  6/SCENE_WIDTH, -8/SCENE_WIDTH },
                    { -4/SCENE_WIDTH,  6/SCENE_WIDTH, 0 },
            },
    };
    int nrOfWalls = sizeof(vertices) / sizeof(vertices[0]);
    for (int i = 0; i < nrOfWalls; ++i) {
        glColor3ub(255, 255, 255);
        glPolygonMode(GL_FRONT,GL_FILL);
        draw_paralleliped(vertices[i][0], vertices[i][1], vertices[i][2], vertices[i][3],
                          vertices[i][4], vertices[i][5], vertices[i][6], vertices[i][7], .0f);
        draw_paralleliped(vertices[i][0], vertices[i][1], vertices[i][2], vertices[i][3],
                          vertices[i][4], vertices[i][5], vertices[i][6], vertices[i][7], 1.0f);
    }
}

void init(void) {
    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);
    glClearColor(180/255.0,180/255.0, 180/255.0, 0.0); // GREY
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -.5, 1.5, -1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Position camera at (4, 6, 5) looking at (0, 0, 0) with the vector <0, 1, 0> pointing upward.
    gluLookAt(-1, 0.5, 2, 0, 0, 0, 0, 1, 0);
}

void keyboardS(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_F1:
            showAxis = true;
            glutPostRedisplay();
            break;
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
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("S4 house");
    init();
    glutDisplayFunc(draw);
    glutSpecialFunc(keyboardS);
    glutMainLoop();
}