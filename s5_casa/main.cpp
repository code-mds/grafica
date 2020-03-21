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
#define MNU_CHANGE_COLOR 6
#define MNU_OPENCLOSE_DOOR 5
#define MNU_STOP_HOUSE_ROTATION 4
#define MNU_START_HOUSE_ROTATION 3
#define MNU_TOGGLE_WIREFRAME 2
#define MNU_TOGGLE_AXIS 1

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;
const int ANIM_MSEC = 100;
const char ESCAPE = 27;
const int ROTATE_HOUSE = 0;
const int ROTATE_DOOR = 1;

int _mainWindow;
house _house;

void drawCB();
void mainMenuCB(int value);
void reshapeCB(int w, int h);
void timerCB(int value);
void specialKeyCB(int key, int x, int y);
void keyCB(unsigned char key, int x, int y);

void rotateHouse();
void rotateDoor();
void startHouseRotation();
void startDoorRotation();
void stopHouseRotation();

void drawCB() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(-.6, 0.4, 1, 0, 0, 0, 0, 1, 0);

    draw_axis();
    _house.draw();
    glutSwapBuffers();
}

void timerCB(int value) {
    switch (value) {
        case ROTATE_HOUSE:
            rotateHouse();
            break;
        case ROTATE_DOOR:
            rotateDoor();
            break;
    }
}

void rotateDoor() {
    _house.rotateDoor();
    glutTimerFunc(ANIM_MSEC, timerCB, ROTATE_DOOR);
}

void rotateHouse() {
    if(!_house.RotationEnabled())
        return;

    _house.updateRotation(true);
    glutTimerFunc(ANIM_MSEC, timerCB, ROTATE_HOUSE);
}

void stopHouseRotation() {
    _house.updateRotation(false);
}

void startHouseRotation() {
    _house.updateRotation(true);
    glutTimerFunc(ANIM_MSEC, timerCB, ROTATE_HOUSE);
}

void startDoorRotation() {
    _house.toggleDoor();
    glutTimerFunc(ANIM_MSEC, timerCB, ROTATE_DOOR);
}

void reshapeCB(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-1.5, 1.5, -1.5 * (GLfloat) h / (GLfloat) w,
                1.5 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-1.5 * (GLfloat) w / (GLfloat) h,
                1.5 * (GLfloat) w / (GLfloat) h, -1.5, 1.5, -10.0, 10.0);
    //glMatrixMode(GL_MODELVIEW);
}


void mainMenuCB(int value) {
    switch (value) {
        case MNU_TOGGLE_AXIS:
            toggleAxesVisibility(); break;
        case MNU_TOGGLE_WIREFRAME:
            toggleWireframeVisibility(); break;
        case MNU_START_HOUSE_ROTATION:
            startHouseRotation(); break;
        case MNU_STOP_HOUSE_ROTATION:
            stopHouseRotation(); break;
        case MNU_OPENCLOSE_DOOR:
            startDoorRotation(); break;
        case MNU_CHANGE_COLOR:
            _house.changeColor(); break;
    }
}

void specialKeyCB(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_F1:
            toggleAxesVisibility();
            break;
        case GLUT_KEY_F2:
            toggleWireframeVisibility();
            break;
        case GLUT_KEY_F3:
            _house.changeColor();
            break;
        case GLUT_KEY_UP:
            _house.moveUp();
            break;
        case GLUT_KEY_DOWN:
            _house.moveDown();
            break;
        case GLUT_KEY_RIGHT:
            _house.moveRight();
            break;
        case GLUT_KEY_LEFT:
            _house.moveLeft();
            break;
    }
}

void keyCB(unsigned char key, int x, int y) {
    switch (key) {
        case 'R':
        case 'r':
            startHouseRotation();
            break;

        case 'S':
        case 's':
            stopHouseRotation();
            break;

        case 'D':
        case 'd':
            startDoorRotation();
            break;

        case ESCAPE:
            glutDestroyWindow(_mainWindow);
            exit(0);
    }
}

void init() {
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    _mainWindow = glutCreateWindow("S5 house");

    glutReshapeFunc(reshapeCB);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glClearColor(COLOR_BACK);

    glutCreateMenu(mainMenuCB);
    glutAddMenuEntry("Show/Hide Axes", MNU_TOGGLE_AXIS);
    glutAddMenuEntry("Show/Hide Wireframe", MNU_TOGGLE_WIREFRAME);
    glutAddMenuEntry("Start House Rotation", MNU_START_HOUSE_ROTATION);
    glutAddMenuEntry("Stop House Rotation", MNU_STOP_HOUSE_ROTATION);
    glutAddMenuEntry("Open/Close Door", MNU_OPENCLOSE_DOOR);
    glutAddMenuEntry("Change color", MNU_CHANGE_COLOR);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(drawCB);
    glutSpecialFunc(specialKeyCB);
    glutKeyboardFunc(keyCB);
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    init();
    glutMainLoop();
}

