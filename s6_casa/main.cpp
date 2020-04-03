//glut_test.cpp
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#ifdef __APPLE__
    // Headers richiesti da OSX
    #include <GLUT/glut.h>
#else
    // headers richiesti da Windows e linux
    #include <GL\glew.h>
    #include <GL\freeglut.h>
#endif

#include <cstdlib>
#include "draw_utils.h"
#include "house.h"

#define COLOR_BACK 1.0, 1.0, 1.0, 0.0
#define MNU_CHANGE_COLOR 6
#define MNU_OPENCLOSE_DOOR 5
#define MNU_STOP_HOUSE_ROTATION 4
#define MNU_START_HOUSE_ROTATION 3
#define MNU_TOGGLE_WIREFRAME 2
#define MNU_TOGGLE_AXIS 1

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const int ANIM_MSEC = 100;
const int WIND_MSEC = 5000;
const char ESCAPE = 27;

int _mainWindow;
house _house;

void displayCallback();
void menuCallback(int value);
void reshapeCallaback(int w, int h);
void animationCallaback(int value);
void windCallaback(int value);
void specialKeyCallback(int key, int x, int y);
void keyCallback(unsigned char key, int x, int y);

void rotateHouse();

void displayCallback() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set MODEL/VIEW matrix mode
    glMatrixMode(GL_MODELVIEW);

    // load identity matrix
    glLoadIdentity();

    // view transformation must be called before model transformation
    // coordinates: eye, center/lookat, up vector
    gluLookAt(-.6, 0.4, 0.5, 0, 0, 0, 0, .6, 0);

    // model transformations
    draw_axis();
    _house.draw();

    glutSwapBuffers();
}


void windCallaback(int value) {
    _house.updateWind();
    glutTimerFunc(WIND_MSEC, windCallaback, 0);
}

void animationCallaback(int value) {
    rotateHouse();
    _house.rotateDoor();
    _house.updateAnimation();

    glutTimerFunc(ANIM_MSEC, animationCallaback, 0);
}

void rotateHouse() {
    if(!_house.rotationEnabled())
        return;

    _house.updateRotation(true);
}

void reshapeCallaback(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-1.5, 1.5, -1.5 * (GLfloat) h / (GLfloat) w,
                1.5 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-1.5 * (GLfloat) w / (GLfloat) h,
                1.5 * (GLfloat) w / (GLfloat) h, -1.5, 1.5, -10.0, 10.0);
}


void menuCallback(int value) {
    switch (value) {
        case MNU_TOGGLE_AXIS:
            toggleAxesVisibility(); break;
        case MNU_TOGGLE_WIREFRAME:
            toggleWireframeVisibility(); break;
        case MNU_START_HOUSE_ROTATION:
            _house.updateRotation(true); break;
        case MNU_STOP_HOUSE_ROTATION:
            _house.updateRotation(false); break;
        case MNU_OPENCLOSE_DOOR:
            _house.toggleDoor();
            break;
        case MNU_CHANGE_COLOR:
            _house.changeColor();
            break;
    }
}

void specialKeyCallback(int key, int x, int y) {
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
        case GLUT_KEY_PAGE_UP:
            _house.moveNear();
            break;
        case GLUT_KEY_PAGE_DOWN:
            _house.moveFar();
            break;
    }
}

void keyCallback(unsigned char key, int x, int y) {
    switch (key) {
        case 'R':
        case 'r':
            _house.updateRotation(true);
            break;

        case 'S':
        case 's':
            _house.updateRotation(false);
            break;

        case 'D':
        case 'd':
            _house.toggleDoor();
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

    glutReshapeFunc(reshapeCallaback);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glClearColor(COLOR_BACK);

    glutCreateMenu(menuCallback);
    glutAddMenuEntry("Show/Hide Axes", MNU_TOGGLE_AXIS);
    glutAddMenuEntry("Show/Hide Wireframe", MNU_TOGGLE_WIREFRAME);
    glutAddMenuEntry("Start House Rotation", MNU_START_HOUSE_ROTATION);
    glutAddMenuEntry("Stop House Rotation", MNU_STOP_HOUSE_ROTATION);
    glutAddMenuEntry("Open/Close Door", MNU_OPENCLOSE_DOOR);
    glutAddMenuEntry("Change color", MNU_CHANGE_COLOR);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(displayCallback);
    glutSpecialFunc(specialKeyCallback);
    glutKeyboardFunc(keyCallback);

    glutTimerFunc(ANIM_MSEC, animationCallaback, 0);
    glutTimerFunc(WIND_MSEC, windCallaback, 0);
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    init();
    glutMainLoop();
}

