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

GLubyte COLOR_ROOF_EXTERNAL[] = {203, 0, 0 };
GLubyte COLOR_ROOF_INTERNAL[] = {170, 0, 0 };
GLubyte COLOR_WALL_EXTERNAL[] = {192, 192, 192 };
GLubyte COLOR_WALL_INTERNAL[] = {80, 80, 80 };
GLubyte COLOR_FLOOR[] = {160, 160, 160 };

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;
const float SCENE_WIDTH = 10.0f;

void draw_triangle_walls();
void draw_lateral_walls();
void draw_roof();
void draw_floor();

void draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw_axis();
    draw_floor();
    draw_lateral_walls();
    draw_triangle_walls();
    draw_roof();
    glutSwapBuffers();
}

void draw_floor() {
    GLfloat vertices[4][3] = {
            // floor
            {5 / SCENE_WIDTH, 0 / SCENE_WIDTH,  0 / SCENE_WIDTH},
            {5 / SCENE_WIDTH, 0 / SCENE_WIDTH,  -8 / SCENE_WIDTH},
            {-5 / SCENE_WIDTH, 0 / SCENE_WIDTH, -8 / SCENE_WIDTH},
            {-5 / SCENE_WIDTH, 0 / SCENE_WIDTH, 0 / SCENE_WIDTH},
    };

    glPolygonMode(GL_FRONT,GL_FILL);
    draw_rectangle3D(vertices[0], vertices[1], vertices[2], vertices[3], COLOR_FLOOR);
}

void draw_roof() {
    GLfloat vertices[][8][3] = {
            // right roof wall
            {
                    { 6/SCENE_WIDTH, 6/SCENE_WIDTH, 1/SCENE_WIDTH }, //bottomLeft1
                    { 6/SCENE_WIDTH,  6/SCENE_WIDTH, -9/SCENE_WIDTH}, //bottomRight1
                    { 0/SCENE_WIDTH,  12/SCENE_WIDTH, -9/SCENE_WIDTH }, //topRight1
                    { 0/SCENE_WIDTH,  12/SCENE_WIDTH, 1/SCENE_WIDTH }, //topLeft2

                    { 6/SCENE_WIDTH,  5/SCENE_WIDTH, -9/SCENE_WIDTH}, //bottomLeft2
                    { 6/SCENE_WIDTH, 5/SCENE_WIDTH, 1/SCENE_WIDTH },  //bottomRight2
                    { 0/SCENE_WIDTH,  11/SCENE_WIDTH, 1/SCENE_WIDTH }, //topRight2
                    { 0/SCENE_WIDTH,  11/SCENE_WIDTH, -9/SCENE_WIDTH }, //topLeft2
            },
            // left roof wall
            {
                    { -6/SCENE_WIDTH,  6/SCENE_WIDTH, -9/SCENE_WIDTH},
                    { -6/SCENE_WIDTH, 6/SCENE_WIDTH, 1/SCENE_WIDTH },
                    { 0/SCENE_WIDTH,  12/SCENE_WIDTH, 1/SCENE_WIDTH },
                    { 0/SCENE_WIDTH,  12/SCENE_WIDTH, -9/SCENE_WIDTH },

                    { -6/SCENE_WIDTH, 5/SCENE_WIDTH, 1/SCENE_WIDTH },
                    { -6/SCENE_WIDTH,  5/SCENE_WIDTH, -9/SCENE_WIDTH},
                    { 0/SCENE_WIDTH,  11/SCENE_WIDTH, -9/SCENE_WIDTH },
                    { 0/SCENE_WIDTH,  11/SCENE_WIDTH, 1/SCENE_WIDTH },
            }
    };

    int nrOfWalls = sizeof(vertices) / sizeof(vertices[0]);
    for (int i = 0; i < nrOfWalls; ++i) {

        draw_paralleleliped(vertices[i][0], vertices[i][1], vertices[i][2], vertices[i][3],
                            vertices[i][4], vertices[i][5], vertices[i][6], vertices[i][7], COLOR_ROOF_EXTERNAL, COLOR_ROOF_INTERNAL);
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
                    { 5/SCENE_WIDTH, 6/SCENE_WIDTH, -1/SCENE_WIDTH },
                    { -5/SCENE_WIDTH,  6/SCENE_WIDTH,  -1/SCENE_WIDTH},
                    { 0,  11/SCENE_WIDTH, -1/SCENE_WIDTH }
            },
            {
                    { 5/SCENE_WIDTH, 6/SCENE_WIDTH, -8/SCENE_WIDTH },
                    { -5/SCENE_WIDTH,  6/SCENE_WIDTH, -8/SCENE_WIDTH},
                    { 0,  11/SCENE_WIDTH, -8/SCENE_WIDTH }
            },
            {
                    { -5/SCENE_WIDTH,  6/SCENE_WIDTH, -7/SCENE_WIDTH},
                    { 5/SCENE_WIDTH, 6/SCENE_WIDTH, -7/SCENE_WIDTH },
                    { 0,  11/SCENE_WIDTH, -7/SCENE_WIDTH }
            },
    };

    int nrOfWalls = sizeof(vertices) / sizeof(vertices[0]);
    for (int i = 0; i < nrOfWalls; ++i) {
        draw_triangle3D(vertices[i][0], vertices[i][1], vertices[i][2], i%2==0 ? COLOR_WALL_EXTERNAL : COLOR_WALL_INTERNAL);
    }
}

void draw_lateral_walls() {

    GLfloat vertices[][8][3] = {
            // front walls
            {
                    { 2/SCENE_WIDTH, 0, 0 },
                    { 5/SCENE_WIDTH, 0, 0 },
                    { 5/SCENE_WIDTH, 6/SCENE_WIDTH, 0 },
                    { 2/SCENE_WIDTH, 6/SCENE_WIDTH, 0 },

                    { 5/SCENE_WIDTH, 0, -1/SCENE_WIDTH },
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
                    { 5/SCENE_WIDTH, 0, -1/SCENE_WIDTH},
                    { 5/SCENE_WIDTH, 0, -8/SCENE_WIDTH },
                    { 5/SCENE_WIDTH, 6/SCENE_WIDTH, -8/SCENE_WIDTH },
                    { 5/SCENE_WIDTH, 6/SCENE_WIDTH, -1/SCENE_WIDTH },

                    { 4/SCENE_WIDTH, 0, -8/SCENE_WIDTH },
                    { 4/SCENE_WIDTH, 0, -1/SCENE_WIDTH},
                    { 4/SCENE_WIDTH, 6/SCENE_WIDTH, -1/SCENE_WIDTH },
                    { 4/SCENE_WIDTH, 6/SCENE_WIDTH, -8/SCENE_WIDTH },

            },
            // back wall
            {
                    { 4/SCENE_WIDTH, 0, -8/SCENE_WIDTH },
                    { -4/SCENE_WIDTH,  0, -8/SCENE_WIDTH},
                    { -4/SCENE_WIDTH,  6/SCENE_WIDTH, -8/SCENE_WIDTH },
                    { 4/SCENE_WIDTH,  6/SCENE_WIDTH, -8/SCENE_WIDTH },

                    { -4/SCENE_WIDTH,  0, -7/SCENE_WIDTH},
                    { 4/SCENE_WIDTH, 0, -7/SCENE_WIDTH },
                    { 4/SCENE_WIDTH,  6/SCENE_WIDTH, -7/SCENE_WIDTH },
                    { -4/SCENE_WIDTH,  6/SCENE_WIDTH, -7/SCENE_WIDTH },
            },
            //left wall
            {
                    { -5/SCENE_WIDTH,  0, -8/SCENE_WIDTH},
                    { -5/SCENE_WIDTH, 0, -1/SCENE_WIDTH },
                    { -5/SCENE_WIDTH,  6/SCENE_WIDTH, -1/SCENE_WIDTH },
                    { -5/SCENE_WIDTH,  6/SCENE_WIDTH, -8/SCENE_WIDTH },

                    { -4/SCENE_WIDTH, 0, -1/SCENE_WIDTH },
                    { -4/SCENE_WIDTH,  0, -8/SCENE_WIDTH},
                    { -4/SCENE_WIDTH,  6/SCENE_WIDTH, -8/SCENE_WIDTH },
                    { -4/SCENE_WIDTH,  6/SCENE_WIDTH, -1/SCENE_WIDTH },
            },
    };
    int nrOfWalls = sizeof(vertices) / sizeof(vertices[0]);
    for (int i = 0; i < nrOfWalls; ++i) {
        draw_paralleleliped(vertices[i][0], vertices[i][1], vertices[i][2], vertices[i][3],
                            vertices[i][4], vertices[i][5], vertices[i][6], vertices[i][7], COLOR_WALL_EXTERNAL, COLOR_WALL_INTERNAL);
    }

}

void init(void) {
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -.5, 1.5, -1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Position camera at (x1, y1, z1) looking at (x2, y2, y2) with the vector <0, 1, 0> pointing upward.
    gluLookAt(-1, 0.5, 2, 0, 0, 0, 0, 1, 0);
}

void keyboardS(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_F1:
            showAxis = !showAxis;
            glutPostRedisplay();
            break;
        case GLUT_KEY_F2:
            showWireFrame = !showWireFrame;
            glutPostRedisplay();
            break;
        case GLUT_KEY_UP:
            glRotatef(1.0,1.0,0.0,0.0);
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            glRotatef(1.0,-1.0,0.0,0.0);
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
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("S4 house");
    init();
    glutDisplayFunc(draw);
    glutSpecialFunc(keyboardS);
    glutMainLoop();
}