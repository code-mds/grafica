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
#define COLOR_BACK              1.0, 1.0, 1.0, 0.0

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;
const float SW = 10.0f; //SCENE WIDTH

const float HALF_DOOR_WIDTH = 2.0f / SW;
const float HALF_BASE_WIDTH = 5.0f / SW;
const float BASE_HEIGHT = 8.0f / SW;
const float WALL_WIDTH = 1.0f / SW;
const float WALL_HEIGHT = 6.0f / SW;
const float ROOF_HEIGHT = 11.0f / SW;

const float CHIM_LEFT = -4.0f / SW;
const float CHIM_RIGHT = -3.0f / SW;
const float CHIM_BOTTOM = 7.0f / SW;
const float CHIM_TOP = 11.0f / SW;
const float CHIM_START_DEPTH = -2.0f / SW;
const float CHIM_END_DEPTH = -4.0f / SW;
const float CHIM_THICK = .3f / SW;

int _mainWindow;
bool _animation = false;
int ANIM_MSEC = 100;

void rotate(int value);
void draw_prism_walls();
void draw_lateral_walls();
void draw_roof();
void draw_floor();
void draw_chimney();

void draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw_axis();
    draw_floor();
    draw_lateral_walls();
    draw_prism_walls();
    draw_roof();
    draw_chimney();
    glutSwapBuffers();
}

void draw_chimney() {
    rectangle_t rectangles[] = {
        // LEFT SIDE
        {
            {CHIM_LEFT, CHIM_BOTTOM,  CHIM_END_DEPTH},
            {CHIM_LEFT, CHIM_BOTTOM, CHIM_START_DEPTH},
            {CHIM_LEFT, CHIM_TOP,  CHIM_START_DEPTH},
            {CHIM_LEFT, CHIM_TOP,  CHIM_END_DEPTH},
            COLOR_FLOOR
        },
        {
            {CHIM_LEFT+CHIM_THICK, CHIM_BOTTOM,  CHIM_START_DEPTH},
            {CHIM_LEFT+CHIM_THICK, CHIM_BOTTOM, CHIM_END_DEPTH},
            {CHIM_LEFT+CHIM_THICK, CHIM_TOP,  CHIM_END_DEPTH},
            {CHIM_LEFT+CHIM_THICK, CHIM_TOP,  CHIM_START_DEPTH},
                COLOR_WALL_INTERNAL
        },
            // RIGHT SIDE
        {
                {CHIM_RIGHT, CHIM_BOTTOM,  CHIM_END_DEPTH},
                {CHIM_RIGHT, CHIM_BOTTOM, CHIM_START_DEPTH},
                {CHIM_RIGHT, CHIM_TOP,  CHIM_START_DEPTH},
                {CHIM_RIGHT, CHIM_TOP,  CHIM_END_DEPTH},
                COLOR_FLOOR
        },
        {
                {CHIM_RIGHT+CHIM_THICK, CHIM_BOTTOM,  CHIM_START_DEPTH},
                {CHIM_RIGHT+CHIM_THICK, CHIM_BOTTOM, CHIM_END_DEPTH},
                {CHIM_RIGHT+CHIM_THICK, CHIM_TOP,  CHIM_END_DEPTH},
                {CHIM_RIGHT+CHIM_THICK, CHIM_TOP,  CHIM_START_DEPTH},
                COLOR_FLOOR
        },
        // FRONT
        {
                {CHIM_RIGHT+CHIM_THICK, CHIM_BOTTOM, CHIM_START_DEPTH},
                {CHIM_LEFT, CHIM_BOTTOM,  CHIM_START_DEPTH},
                {CHIM_LEFT, CHIM_TOP,  CHIM_START_DEPTH},
                {CHIM_RIGHT+CHIM_THICK, CHIM_TOP,  CHIM_START_DEPTH},
                COLOR_FLOOR
        },
        {
                {CHIM_LEFT, CHIM_BOTTOM,  CHIM_START_DEPTH+CHIM_THICK},
                {CHIM_RIGHT+CHIM_THICK, CHIM_BOTTOM, CHIM_START_DEPTH+CHIM_THICK},
                {CHIM_RIGHT+CHIM_THICK, CHIM_TOP,  CHIM_START_DEPTH+CHIM_THICK},
                {CHIM_LEFT, CHIM_TOP,  CHIM_START_DEPTH+CHIM_THICK},
                COLOR_FLOOR
        },
        // BACK
        {
                {CHIM_RIGHT, CHIM_BOTTOM, CHIM_END_DEPTH},
                {CHIM_LEFT, CHIM_BOTTOM,  CHIM_END_DEPTH},
                {CHIM_LEFT, CHIM_TOP,  CHIM_END_DEPTH},
                {CHIM_RIGHT, CHIM_TOP,  CHIM_END_DEPTH},
                COLOR_FLOOR
        },
        {
                {CHIM_LEFT, CHIM_BOTTOM,  CHIM_END_DEPTH+CHIM_THICK},
                {CHIM_RIGHT, CHIM_BOTTOM, CHIM_END_DEPTH+CHIM_THICK},
                {CHIM_RIGHT, CHIM_TOP,  CHIM_END_DEPTH+CHIM_THICK},
                {CHIM_LEFT, CHIM_TOP,  CHIM_END_DEPTH+CHIM_THICK},
                COLOR_WALL_INTERNAL
        }

    };

    int nrOfWalls = sizeof(rectangles) / sizeof(rectangles[0]);
    for (int i = 0; i < nrOfWalls; i=i+2) {
        draw_parallelepiped(rectangles[i], rectangles[i + 1]);
    }
}

void draw_floor() {
    rectangle_t rect = {
            // floor
            {HALF_BASE_WIDTH, 0,  0},
            {HALF_BASE_WIDTH, 0, -BASE_HEIGHT},
            {-HALF_BASE_WIDTH, 0, -BASE_HEIGHT},
            {-HALF_BASE_WIDTH, 0, 0},
            COLOR_FLOOR
    };

    draw_rectangle3D(rect);
}

void draw_roof() {
    rectangle_t rectangles[] = {
            // right roof wall
            {
                    { WALL_HEIGHT, WALL_HEIGHT, WALL_WIDTH },
                    { WALL_HEIGHT,  WALL_HEIGHT, -(BASE_HEIGHT+WALL_WIDTH)},
                    { 0,  (ROOF_HEIGHT+WALL_WIDTH), -(BASE_HEIGHT+WALL_WIDTH) },
                    { 0,  (ROOF_HEIGHT+WALL_WIDTH), WALL_WIDTH },
                    COLOR_ROOF_EXTERNAL
            },{
                    { WALL_HEIGHT,  HALF_BASE_WIDTH, -(BASE_HEIGHT+WALL_WIDTH)},
                    { WALL_HEIGHT, HALF_BASE_WIDTH, WALL_WIDTH },
                    { 0,  ROOF_HEIGHT, WALL_WIDTH },
                    { 0,  ROOF_HEIGHT, -(BASE_HEIGHT+WALL_WIDTH) },
                    COLOR_ROOF_INTERNAL
            },
            // left roof wall
            {
                    { -WALL_HEIGHT,  WALL_HEIGHT, -(BASE_HEIGHT+WALL_WIDTH)},
                    { -WALL_HEIGHT, WALL_HEIGHT, WALL_WIDTH },
                    { 0,  (ROOF_HEIGHT+WALL_WIDTH), WALL_WIDTH },
                    { 0,  (ROOF_HEIGHT+WALL_WIDTH), -(BASE_HEIGHT+WALL_WIDTH) },
                    COLOR_ROOF_EXTERNAL
            },{
                    { -WALL_HEIGHT, HALF_BASE_WIDTH, WALL_WIDTH },
                    { -WALL_HEIGHT,  HALF_BASE_WIDTH, -(BASE_HEIGHT+WALL_WIDTH)},
                    { 0,  ROOF_HEIGHT, -(BASE_HEIGHT+WALL_WIDTH) },
                    { 0,  ROOF_HEIGHT, WALL_WIDTH },
                    COLOR_ROOF_INTERNAL
            }
    };

    draw_parallelepiped(rectangles[0], rectangles[1]);
    draw_parallelepiped(rectangles[2], rectangles[3]);
}

void draw_prism_walls() {
   triangle_t triangles[] = {
            {
                    { -HALF_BASE_WIDTH,  WALL_HEIGHT, 0 },
                    { HALF_BASE_WIDTH, WALL_HEIGHT, 0 },
                    { 0,  ROOF_HEIGHT, 0 },
                    COLOR_WALL_EXTERNAL
            },
            {
                    { HALF_BASE_WIDTH, WALL_HEIGHT, -WALL_WIDTH },
                    { -HALF_BASE_WIDTH,  WALL_HEIGHT,  -WALL_WIDTH},
                    { 0,  ROOF_HEIGHT, -WALL_WIDTH },
                    COLOR_WALL_INTERNAL
            },
            {
                    { HALF_BASE_WIDTH, WALL_HEIGHT, -(BASE_HEIGHT) },
                    { -HALF_BASE_WIDTH,  WALL_HEIGHT, -(BASE_HEIGHT)},
                    { 0,  ROOF_HEIGHT, -BASE_HEIGHT },
                    COLOR_WALL_EXTERNAL
            },
            {
                    { -HALF_BASE_WIDTH,  WALL_HEIGHT, -(BASE_HEIGHT-WALL_WIDTH)},
                    { HALF_BASE_WIDTH, WALL_HEIGHT, -(BASE_HEIGHT-WALL_WIDTH) },
                    { 0,  ROOF_HEIGHT, -(BASE_HEIGHT-WALL_WIDTH) },
                    COLOR_WALL_INTERNAL
            },
    };

    draw_prism(triangles[0], triangles[1]);
    draw_prism(triangles[2], triangles[3]);
}

void draw_lateral_walls() {

    rectangle_t rectangles[10] = {
            // front walls
            {
                    { HALF_DOOR_WIDTH, 0, 0 },
                    { HALF_BASE_WIDTH, 0, 0 },
                    { HALF_BASE_WIDTH, WALL_HEIGHT, 0 },
                    { HALF_DOOR_WIDTH, WALL_HEIGHT, 0 },
                    COLOR_WALL_EXTERNAL
            },
            {
                    { (HALF_BASE_WIDTH-WALL_WIDTH), 0, -WALL_WIDTH },
                    { HALF_DOOR_WIDTH, 0, -WALL_WIDTH },
                    { HALF_DOOR_WIDTH, WALL_HEIGHT, -WALL_WIDTH },
                    { (HALF_BASE_WIDTH-WALL_WIDTH), WALL_HEIGHT, -WALL_WIDTH },
                    COLOR_WALL_INTERNAL
            },
            {
                    { -HALF_BASE_WIDTH, 0, 0},
                    { -HALF_DOOR_WIDTH, 0, 0 },
                    { -HALF_DOOR_WIDTH, WALL_HEIGHT, 0 },
                    { -HALF_BASE_WIDTH, WALL_HEIGHT, 0 },
                    COLOR_WALL_EXTERNAL
            },
            {
                    { -HALF_DOOR_WIDTH, 0, -WALL_WIDTH },
                    { -(HALF_BASE_WIDTH-WALL_WIDTH), 0, -WALL_WIDTH},
                    { -(HALF_BASE_WIDTH-WALL_WIDTH), WALL_HEIGHT, -WALL_WIDTH },
                    { -HALF_DOOR_WIDTH, WALL_HEIGHT, -WALL_WIDTH },
                    COLOR_WALL_INTERNAL
            },
            //right wall
            {
                    { HALF_BASE_WIDTH, 0, 0},
                    { HALF_BASE_WIDTH, 0, -BASE_HEIGHT },
                    { HALF_BASE_WIDTH, WALL_HEIGHT, -BASE_HEIGHT },
                    { HALF_BASE_WIDTH, WALL_HEIGHT, 0 },
                    COLOR_WALL_EXTERNAL
            },
            {
                    { (HALF_BASE_WIDTH-WALL_WIDTH), 0, -(BASE_HEIGHT-WALL_WIDTH) },
                    { (HALF_BASE_WIDTH-WALL_WIDTH), 0, -WALL_WIDTH},
                    { (HALF_BASE_WIDTH-WALL_WIDTH), WALL_HEIGHT, -WALL_WIDTH },
                    { (HALF_BASE_WIDTH-WALL_WIDTH), WALL_HEIGHT, -(BASE_HEIGHT-WALL_WIDTH) },
                    COLOR_WALL_INTERNAL
            },
            // back wall
            {
                    { HALF_BASE_WIDTH, 0, -BASE_HEIGHT },
                    { -HALF_BASE_WIDTH,  0, -BASE_HEIGHT},
                    { -HALF_BASE_WIDTH,  WALL_HEIGHT, -BASE_HEIGHT },
                    { HALF_BASE_WIDTH,  WALL_HEIGHT, -BASE_HEIGHT },
                    COLOR_WALL_EXTERNAL
            },
            {
                    { -(HALF_BASE_WIDTH-WALL_WIDTH),  0, -(BASE_HEIGHT-WALL_WIDTH)},
                    { (HALF_BASE_WIDTH-WALL_WIDTH), 0, -(BASE_HEIGHT-WALL_WIDTH) },
                    { (HALF_BASE_WIDTH-WALL_WIDTH),  WALL_HEIGHT, -(BASE_HEIGHT-WALL_WIDTH) },
                    { -(HALF_BASE_WIDTH-WALL_WIDTH),  WALL_HEIGHT, -(BASE_HEIGHT-WALL_WIDTH) },
                    COLOR_WALL_INTERNAL
            },
            //left wall
            {
                    { -HALF_BASE_WIDTH,  0, -BASE_HEIGHT},
                    { -HALF_BASE_WIDTH, 0, 0 },
                    { -HALF_BASE_WIDTH,  WALL_HEIGHT, 0 },
                    { -HALF_BASE_WIDTH,  WALL_HEIGHT, -BASE_HEIGHT },
                    COLOR_WALL_EXTERNAL
            },
            {
                    { -(HALF_BASE_WIDTH-WALL_WIDTH), 0, -WALL_WIDTH },
                    { -(HALF_BASE_WIDTH-WALL_WIDTH),  0, -(BASE_HEIGHT-WALL_WIDTH)},
                    { -(HALF_BASE_WIDTH-WALL_WIDTH),  WALL_HEIGHT, -(BASE_HEIGHT-WALL_WIDTH) },
                    { -(HALF_BASE_WIDTH-WALL_WIDTH),  WALL_HEIGHT, -WALL_WIDTH },
                    COLOR_WALL_INTERNAL
            },
    };
    int nrOfWalls = sizeof(rectangles) / sizeof(rectangles[0]);
    for (int i = 0; i < nrOfWalls; i=i+2) {
        draw_parallelepiped(rectangles[i], rectangles[i + 1]);
    }

}


void main_menu(int value)
{
    switch (value) {
        case 1: toggleAxesVisibility(); break;
        case 2: toggleWireframeVisibility(); break;
    }
}

void init(void) {
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glClearColor(COLOR_BACK);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -.5, 1.5, -1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Position camera at (x1, y1, z1) looking at (x2, y2, y2) with the vector <0, 1, 0> pointing upward.
    gluLookAt(-.6, 0.4, 1, 0, 0, 0, 0, 1, 0);

    glutCreateMenu(main_menu);
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
void rotate(int value) {
    if(!_animation)
        return;

    glRotatef(1.0f, 0.0f, 1.0f, 0.0f);
    glutPostRedisplay();
    glutTimerFunc(ANIM_MSEC, rotate, 0);
}

void key_handler(unsigned char key, int x, int y) {
    switch (key) {
        case 'r':
            _animation = true;
            glutTimerFunc(ANIM_MSEC, rotate, 0);
            break;

        case 's':
            _animation = false;
            break;
        case 27: // ESCAPE
            glutDestroyWindow(_mainWindow);
            exit(0);
    }
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    _mainWindow = glutCreateWindow("S5 house");
    init();
    glutDisplayFunc(draw);
    glutSpecialFunc(keyboardS);
    glutKeyboardFunc(key_handler);
    glutMainLoop();
}

