//glut_test.cpp
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#ifdef __APPLE__
    // Headers richiesti da OSX
    #include <GL/glew.h>
    #include <GLUT/glut.h>
#else
    // headers richiesti da Windows e linux
    #include <GL\glew.h>
    #include <GL\freeglut.h>
#endif
#include "draw_utils.h"

#define COLOR_ROOF_EXTERNAL     230, 0, 0
#define COLOR_ROOF_INTERNAL     160, 0, 0
#define COLOR_WALL_EXTERNAL     200, 200, 200
#define COLOR_WALL_INTERNAL     80, 80, 80
#define COLOR_FLOOR             160, 160, 160

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;
const float SW = 10.0f; //SCENE WIDTH

const float HALF_DOOR_WIDTH = 2.0f;
const float HALF_BASE_WIDTH = 5.0f;
const float BASE_HEIGHT = 8.0f;
const float WALL_THICK = 1.0f;
const float WALL_HEIGHT = 6.0f;
const float ROOF_HEIGHT = 11.0f;

void draw_prism_walls();
void draw_lateral_walls();
void draw_roof();
void draw_floor();

void drawCB() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw_axis();
    draw_floor();
    draw_lateral_walls();
    draw_prism_walls();
    draw_roof();
    glutSwapBuffers();
}

void draw_floor() {
    rectangle_t rect = {
            // floor
            {HALF_BASE_WIDTH / SW, 0,  0},
            {HALF_BASE_WIDTH / SW, 0, -BASE_HEIGHT / SW},
            {-HALF_BASE_WIDTH / SW, 0, -BASE_HEIGHT / SW},
            {-HALF_BASE_WIDTH / SW, 0, 0},
            COLOR_FLOOR
    };

    draw_rectangle3D(&rect);
}

void draw_roof() {
    rectangle_t rectangles[] = {
            // right roof wall
            {
                    { WALL_HEIGHT/SW, WALL_HEIGHT/SW,      WALL_THICK / SW },
                    { WALL_HEIGHT/SW,  WALL_HEIGHT/SW,      -(BASE_HEIGHT + WALL_THICK) / SW},
                    { 0,  (ROOF_HEIGHT + WALL_THICK) / SW, -(BASE_HEIGHT + WALL_THICK) / SW },
                    { 0,  (ROOF_HEIGHT + WALL_THICK) / SW, WALL_THICK / SW },
                    COLOR_ROOF_EXTERNAL
            },{
                    { WALL_HEIGHT/SW,  HALF_BASE_WIDTH/SW, -(BASE_HEIGHT + WALL_THICK) / SW},
                    { WALL_HEIGHT/SW, HALF_BASE_WIDTH/SW,   WALL_THICK / SW },
                    { 0,  ROOF_HEIGHT/SW,                  WALL_THICK / SW },
                    { 0,  ROOF_HEIGHT/SW,                  -(BASE_HEIGHT + WALL_THICK) / SW },
                    COLOR_ROOF_INTERNAL
            },
            // left roof wall
            {
                    { -WALL_HEIGHT/SW,  WALL_HEIGHT/SW,    -(BASE_HEIGHT + WALL_THICK) / SW},
                    { -WALL_HEIGHT/SW, WALL_HEIGHT/SW,      WALL_THICK / SW },
                    { 0,  (ROOF_HEIGHT + WALL_THICK) / SW, WALL_THICK / SW },
                    { 0,  (ROOF_HEIGHT + WALL_THICK) / SW, -(BASE_HEIGHT + WALL_THICK) / SW },
                    COLOR_ROOF_EXTERNAL
            },{
                    { -WALL_HEIGHT/SW, HALF_BASE_WIDTH/SW, WALL_THICK / SW },
                    { -WALL_HEIGHT/SW,  HALF_BASE_WIDTH/SW, -(BASE_HEIGHT + WALL_THICK) / SW},
                    { 0,  ROOF_HEIGHT/SW,                  -(BASE_HEIGHT + WALL_THICK) / SW },
                    { 0,  ROOF_HEIGHT/SW,                  WALL_THICK / SW },
                    COLOR_ROOF_INTERNAL
            }
    };

    draw_parallelepiped(&rectangles[0], &rectangles[1]);
    draw_parallelepiped(&rectangles[2], &rectangles[3]);
}

void draw_prism_walls() {
    rectangle_t rect[] = {
            {
                    {HALF_BASE_WIDTH/SW, WALL_HEIGHT/SW, 0},
                    {-HALF_BASE_WIDTH/SW, WALL_HEIGHT/SW, 0},
                    {-HALF_BASE_WIDTH/SW, WALL_HEIGHT/SW, -WALL_THICK / SW},
                    {HALF_BASE_WIDTH/SW, WALL_HEIGHT/SW, -WALL_THICK / SW},
                    COLOR_FLOOR
            },
            {
                    {HALF_BASE_WIDTH/SW, WALL_HEIGHT/SW, -(BASE_HEIGHT - WALL_THICK) / SW},
                    {-HALF_BASE_WIDTH/SW, WALL_HEIGHT/SW, -(BASE_HEIGHT - WALL_THICK) / SW},
                    {-HALF_BASE_WIDTH/SW, WALL_HEIGHT/SW, -(BASE_HEIGHT) / SW},
                    {HALF_BASE_WIDTH/SW, WALL_HEIGHT/SW, -(BASE_HEIGHT) / SW},
                    COLOR_FLOOR
            },
    };

    draw_rectangle3D(&rect[0]);
    draw_rectangle3D(&rect[1]);

    vertex_t vertices[][3] = {
            {
                    { -HALF_BASE_WIDTH/SW,  WALL_HEIGHT/SW, 0 },
                    { HALF_BASE_WIDTH/SW, WALL_HEIGHT/SW, 0 },
                    { 0,  ROOF_HEIGHT/SW, 0 }
            },
            {
                    { HALF_BASE_WIDTH/SW, WALL_HEIGHT/SW,   -WALL_THICK / SW },
                    { -HALF_BASE_WIDTH/SW,  WALL_HEIGHT/SW, -WALL_THICK / SW},
                    { 0,  ROOF_HEIGHT/SW, -WALL_THICK / SW }
            },
            {
                    { HALF_BASE_WIDTH/SW, WALL_HEIGHT/SW, -(BASE_HEIGHT)/SW },
                    { -HALF_BASE_WIDTH/SW,  WALL_HEIGHT/SW, -(BASE_HEIGHT)/SW},
                    { 0,  ROOF_HEIGHT/SW, -BASE_HEIGHT/SW }
            },
            {
                    { -HALF_BASE_WIDTH/SW,  WALL_HEIGHT/SW, -(BASE_HEIGHT - WALL_THICK) / SW},
                    { HALF_BASE_WIDTH/SW, WALL_HEIGHT/SW,   -(BASE_HEIGHT - WALL_THICK) / SW },
                    { 0,  ROOF_HEIGHT/SW, -(BASE_HEIGHT - WALL_THICK) / SW }
            },
    };

    color_t frontColor = { COLOR_WALL_EXTERNAL };
    color_t backColor =  { COLOR_WALL_INTERNAL };

    int nrOfWalls = sizeof(vertices) / sizeof(vertices[0]);
    for (int i = 0; i < nrOfWalls; ++i) {
        draw_triangle3D(&vertices[i][0], &vertices[i][1], &vertices[i][2],
                        i%2==0 ? &frontColor : &backColor);
    }
}

void draw_lateral_walls() {

    rectangle_t rectangles[10] = {
            // front walls
            {
                    { HALF_DOOR_WIDTH/SW, 0, 0 },
                    { HALF_BASE_WIDTH/SW, 0, 0 },
                    { HALF_BASE_WIDTH/SW, WALL_HEIGHT/SW, 0 },
                    { HALF_DOOR_WIDTH/SW, WALL_HEIGHT/SW, 0 },
                    COLOR_WALL_EXTERNAL
            },
            {
                    { (HALF_BASE_WIDTH - WALL_THICK) / SW,  0, -WALL_THICK / SW },
                    { HALF_DOOR_WIDTH/SW,                   0, -WALL_THICK / SW },
                    { HALF_DOOR_WIDTH/SW, WALL_HEIGHT/SW,                     -WALL_THICK / SW },
                    { (HALF_BASE_WIDTH - WALL_THICK) / SW,  WALL_HEIGHT / SW, -WALL_THICK / SW },
                    COLOR_WALL_INTERNAL
            },
            {
                    { -HALF_BASE_WIDTH/SW, 0, 0},
                    { -HALF_DOOR_WIDTH/SW, 0, 0 },
                    { -HALF_DOOR_WIDTH/SW, WALL_HEIGHT/SW, 0 },
                    { -HALF_BASE_WIDTH/SW, WALL_HEIGHT/SW, 0 },
                    COLOR_WALL_EXTERNAL
            },
            {
                    { -HALF_DOOR_WIDTH/SW,                  0, -WALL_THICK / SW },
                    { -(HALF_BASE_WIDTH - WALL_THICK) / SW, 0, -WALL_THICK / SW},
                    { -(HALF_BASE_WIDTH - WALL_THICK) / SW, WALL_HEIGHT / SW, -WALL_THICK / SW },
                    { -HALF_DOOR_WIDTH/SW, WALL_HEIGHT/SW,                    -WALL_THICK / SW },
                    COLOR_WALL_INTERNAL
            },
            //right wall
            {
                    { HALF_BASE_WIDTH/SW, 0, 0},
                    { HALF_BASE_WIDTH/SW, 0, -BASE_HEIGHT/SW },
                    { HALF_BASE_WIDTH/SW, WALL_HEIGHT/SW, -BASE_HEIGHT/SW },
                    { HALF_BASE_WIDTH/SW, WALL_HEIGHT/SW, 0 },
                    COLOR_WALL_EXTERNAL
            },
            {
                    { (HALF_BASE_WIDTH - WALL_THICK) / SW,  0, -(BASE_HEIGHT - WALL_THICK) / SW },
                    { (HALF_BASE_WIDTH - WALL_THICK) / SW,  0, -WALL_THICK / SW},
                    { (HALF_BASE_WIDTH - WALL_THICK) / SW, WALL_HEIGHT / SW,  -WALL_THICK / SW },
                    { (HALF_BASE_WIDTH - WALL_THICK) / SW,  WALL_HEIGHT / SW, -(BASE_HEIGHT - WALL_THICK) / SW },
                    COLOR_WALL_INTERNAL
            },
            // back wall
            {
                    { HALF_BASE_WIDTH/SW, 0, -BASE_HEIGHT/SW },
                    { -HALF_BASE_WIDTH/SW,  0, -BASE_HEIGHT/SW},
                    { -HALF_BASE_WIDTH/SW,  WALL_HEIGHT/SW, -BASE_HEIGHT/SW },
                    { HALF_BASE_WIDTH/SW,  WALL_HEIGHT/SW, -BASE_HEIGHT/SW },
                    COLOR_WALL_EXTERNAL
            },
            {
                    { -(HALF_BASE_WIDTH - WALL_THICK) / SW, 0, -(BASE_HEIGHT - WALL_THICK) / SW},
                    { (HALF_BASE_WIDTH - WALL_THICK) / SW,  0, -(BASE_HEIGHT - WALL_THICK) / SW },
                    { (HALF_BASE_WIDTH - WALL_THICK) / SW, WALL_HEIGHT / SW,  -(BASE_HEIGHT - WALL_THICK) / SW },
                    { -(HALF_BASE_WIDTH - WALL_THICK) / SW, WALL_HEIGHT / SW, -(BASE_HEIGHT - WALL_THICK) / SW },
                    COLOR_WALL_INTERNAL
            },
            //left wall
            {
                    { -HALF_BASE_WIDTH/SW,  0, -BASE_HEIGHT/SW},
                    { -HALF_BASE_WIDTH/SW, 0, 0 },
                    { -HALF_BASE_WIDTH/SW,  WALL_HEIGHT/SW, 0 },
                    { -HALF_BASE_WIDTH/SW,  WALL_HEIGHT/SW, -BASE_HEIGHT/SW },
                    COLOR_WALL_EXTERNAL
            },
            {
                    { -(HALF_BASE_WIDTH - WALL_THICK) / SW, 0, -WALL_THICK / SW },
                    { -(HALF_BASE_WIDTH - WALL_THICK) / SW, 0, -(BASE_HEIGHT - WALL_THICK) / SW},
                    { -(HALF_BASE_WIDTH - WALL_THICK) / SW, WALL_HEIGHT / SW, -(BASE_HEIGHT - WALL_THICK) / SW },
                    { -(HALF_BASE_WIDTH - WALL_THICK) / SW, WALL_HEIGHT / SW, -WALL_THICK / SW },
                    COLOR_WALL_INTERNAL
            },
    };
    int nrOfWalls = sizeof(rectangles) / sizeof(rectangles[0]);
    for (int i = 0; i < nrOfWalls; i=i+2) {
        draw_parallelepiped(&rectangles[i], &rectangles[i + 1]);
    }

}

void mainMenuCB(int value)
{
    switch (value) {
        case 1: toggleAxesVisibility(); break;
        case 2:
            toggleWireframeVisibility(); break;
    }
}

void init(void) {
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -.5, 1.5, -1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Position camera at (x1, y1, z1) looking at (x2, y2, y2) with the vector <0, 1, 0> pointing upward.
    gluLookAt(-.6, 0.4, 1, 0, 0, 0, 0, 1, 0);

    glutCreateMenu(mainMenuCB);
    glutAddMenuEntry("Show/Hide Axes", 1);
    glutAddMenuEntry("Show/Hide Wireframe", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void keyboardS(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_F1:
            toggleAxesVisibility();
            break;
        case GLUT_KEY_F2:
            toggleWireframeVisibility();
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
    glutDisplayFunc(drawCB);
    glutSpecialFunc(keyboardS);
    glutMainLoop();
}

