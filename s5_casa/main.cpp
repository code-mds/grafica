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
#include "house.h"

#define COLOR_BACK              1.0, 1.0, 1.0, 0.0

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;
const int ANIM_MSEC = 100;
const char ESCAPE = 27;
const int ROTATE_HOUSE = 0;
const int ROTATE_DOOR = 1;

int _mainWindow;
bool _house_rotation = false;
house _house;

void timerCB(int value);
void rotate_house();
void rotate_door();
void start_house_rotation();
void start_door_rotation();
void stop_house_rotation();

void drawCB() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw_axis();
    _house.draw();
    glutSwapBuffers();
}

void main_menu(int value)
{
    switch (value) {
        case 1: toggleAxesVisibility(); break;
        case 2: toggleWireframeVisibility(); break;
        case 3: start_house_rotation(); break;
        case 4: stop_house_rotation(); break;
        case 5: start_door_rotation(); break;
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
    glutAddMenuEntry("Start House Rotation", 3);
    glutAddMenuEntry("Stop House Rotation", 4);
    glutAddMenuEntry("Open/Close Door", 5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void specialKeyCB(int key, int x, int y) {
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
void timerCB(int value) {
    switch (value) {
        case ROTATE_HOUSE:
            rotate_house();
            break;
        case ROTATE_DOOR:
            rotate_door();
            break;
    }
}

void rotate_door() {
    _house.update_model();
    glutPostRedisplay();
    glutTimerFunc(ANIM_MSEC, timerCB, ROTATE_DOOR);
}

void rotate_house() {
    if(!_house_rotation)
        return;

    glRotatef(1.0f, 0.0f, 1.0f, 0.0f);
    glutPostRedisplay();
    glutTimerFunc(ANIM_MSEC, timerCB, ROTATE_HOUSE);
}


void keyCB(unsigned char key, int x, int y) {
    switch (key) {
        case 'R':
        case 'r':
            start_house_rotation();
            break;

        case 'S':
        case 's':
            stop_house_rotation();
            break;

        case 'D':
        case 'd':
            start_door_rotation();
            break;

        case ESCAPE:
            glutDestroyWindow(_mainWindow);
            exit(0);
    }
}

void stop_house_rotation() {
    _house_rotation = false;
}

void start_house_rotation() {
    _house_rotation = true;
    glutTimerFunc(ANIM_MSEC, timerCB, ROTATE_HOUSE);
}

void start_door_rotation() {
    _house.toggle_door();
    glutTimerFunc(ANIM_MSEC, timerCB, ROTATE_DOOR);
}

void reshapeCB(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-1.5, 1.5, -1.5 * (GLfloat) h / (GLfloat) w,
                1.5 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-1.5 * (GLfloat) w / (GLfloat) h,
                1.5 * (GLfloat) w / (GLfloat) h, -1.5, 1.5, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    _mainWindow = glutCreateWindow("S5 house");

    glutReshapeFunc(reshapeCB);
    init();
    glutDisplayFunc(drawCB);
    glutSpecialFunc(specialKeyCB);
    glutKeyboardFunc(keyCB);
    glutMainLoop();
}

