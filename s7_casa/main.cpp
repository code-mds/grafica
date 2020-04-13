//glut_test.cpp
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
#include <iostream>
#include "draw_utils.h"
#include "house.h"
#include "main.h"

#define COLOR_BACK 1.0, 1.0, 1.0, 0.0
#define MNU_ORTHO 9
#define MNU_PERSPECTIVE 8
#define MNU_TOGGLE_WIND 7
#define MNU_CHANGE_COLOR 6
#define MNU_OPENCLOSE_DOOR 5
#define MNU_STOP_HOUSE_ROTATION 4
#define MNU_START_HOUSE_ROTATION 3
#define MNU_TOGGLE_WIREFRAME 2
#define MNU_TOGGLE_AXIS 1

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int ANIM_MSEC = 50;
const int WIND_MSEC = 5000;
const char ESCAPE = 27;

// global variables
GLfloat _windAngle = 0.0;
int _mainWindow = 0;
GLdouble _fovy = 60.0;
lookat_t _camera{0, 0, 3.0, 0, 0, 0, 0 , .1, 0};
volume_t _volume{-5.0, 5.0, -5.0, 5.0, -5.0, 10.0};
char _projection_type = 'p';
house _house;

void displayCallback() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set MODEL/VIEW matrix mode
    glMatrixMode(GL_MODELVIEW);

    // load identity matrix
    glLoadIdentity();

    // view transformation must be called before model transformation
    // coordinates: eye, center/lookat, up vector
    gluLookAt(_camera.eyex, _camera.eyey, _camera.eyez,
              _camera.centerx, _camera.centery, _camera.centerz,
              _camera.upx, _camera.upy, _camera.upz);

    // model transformations
    draw_wind(_windAngle);
    draw_axis(_volume);
    _house.draw();

    glutSwapBuffers();
}

void windCallaback(int value) {
    _windAngle = rand() % 360 + 1;
    _house.updateWind(_windAngle);
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


    GLdouble l{_volume.left};
    GLdouble r{_volume.right};
    GLdouble b{_volume.bottom};
    GLdouble t{_volume.top};
    GLdouble n{_volume.n};
    GLdouble f{_volume.f};
    GLdouble ratio{1.0};


    if(_projection_type == 'a') {
        // orthographic projection
        if (w <= h) {
            ratio = (GLdouble) h / w;
            b*=ratio;
            t*=ratio;
        } else {
            ratio = (GLdouble) w / h;
            l*=ratio;
            r*=ratio;
        }
        glOrtho(l, r, b, t, n, f);
    } else {
        // perspective projection
        GLdouble aspect = (GLdouble)w/h;
        gluPerspective(_fovy, aspect, 1.0, 50.0);
    }
}


void menuCallback(int value) {
    switch (value) {
        case MNU_ORTHO:
            setOrthographicProjection();
            break;
        case MNU_PERSPECTIVE:
            setProspectiveProjection();
            break;
        case MNU_TOGGLE_AXIS:
            toggleAxesVisibility();
            break;
        case MNU_TOGGLE_WIREFRAME:
            toggleWireframeVisibility();
            break;
        case MNU_TOGGLE_WIND:
            toggleWindVisibility();
            break;
        case MNU_START_HOUSE_ROTATION:
            _house.updateRotation(true);
            break;
        case MNU_STOP_HOUSE_ROTATION:
            _house.updateRotation(false);
            break;
        case MNU_OPENCLOSE_DOOR:
            _house.toggleDoor();
            break;
        case MNU_CHANGE_COLOR:
            _house.changeColor();
            break;
    }
}

void setProspectiveProjection() {
    _projection_type = 'p';
    reshapeCallaback(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

void setOrthographicProjection() {
    _projection_type = 'a';
    reshapeCallaback(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
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

        case GLUT_KEY_F9:
            _fovy -= 1;
            std::cout << "_fovy " << _fovy << std::endl;
            reshapeCallaback(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
            break;
        case GLUT_KEY_F10:
            _fovy += 1;
            std::cout << "_fovy " << _fovy << std::endl;
            reshapeCallaback(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
            break;
        case GLUT_KEY_F11:
            _camera.eyez -= .05;
            updateCamera();
            break;
        case GLUT_KEY_F12:
            _camera.eyez += .05;
            updateCamera();
            break;
        case GLUT_KEY_UP:
            _camera.eyey += .05;
            updateCamera();
            break;
        case GLUT_KEY_DOWN:
            _camera.eyey -= .05;
            updateCamera();
            break;
        case GLUT_KEY_RIGHT:
            _camera.eyex += .05;
            updateCamera();
            break;
        case GLUT_KEY_LEFT:
            _camera.eyex -= .05;
            updateCamera();
            break;

        case GLUT_KEY_F7:
            // translation: -X
            _house.moveLeft();
            break;
        case GLUT_KEY_F8:
            // translation: +X
            _house.moveRight();
            break;

        case GLUT_KEY_HOME:
            // translation: -Z
            _house.moveNear();
            break;
        case GLUT_KEY_END:
            // translation: +Z
            _house.moveFar();
            break;

        case GLUT_KEY_PAGE_UP:
            // translation: +Y
            _house.moveUp();
            break;
        case GLUT_KEY_PAGE_DOWN:
            // translation: -Y
            _house.moveDown();
            break;
    }
}

void updateCamera() {
    std::cout << "Camera: x=" << _camera.eyex;
    std::cout << ", y=" << _camera.eyey;
    std::cout << ", z=" << _camera.eyez << std::endl;
    glutPostRedisplay();
}

void keyCallback(unsigned char key, int x, int y) {
    switch (key) {
        case 'A':
        case 'a':
            setOrthographicProjection();
            break;

        case 'P':
        case 'p':
            setProspectiveProjection();
            break;

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

    createMenu();

    glutDisplayFunc(displayCallback);
    glutSpecialFunc(specialKeyCallback);
    glutKeyboardFunc(keyCallback);

    glutTimerFunc(ANIM_MSEC, animationCallaback, 0);
    glutTimerFunc(WIND_MSEC, windCallaback, 0);
}

void createMenu() {
    int menuProj = glutCreateMenu(menuCallback);
    glutAddMenuEntry("Perspective", MNU_PERSPECTIVE);
    glutAddMenuEntry("Ortho", MNU_ORTHO);
    glutCreateMenu(menuCallback);

    int menuStructure = glutCreateMenu(menuCallback);
    glutAddMenuEntry("Show/Hide Wind", MNU_TOGGLE_WIND);
    glutAddMenuEntry("Show/Hide Axes", MNU_TOGGLE_AXIS);
    glutAddMenuEntry("Show/Hide Wireframe", MNU_TOGGLE_WIREFRAME);
    glutAddMenuEntry("Change color", MNU_CHANGE_COLOR);
    glutCreateMenu(menuCallback);

    int menuAnimation = glutCreateMenu(menuCallback);
    glutAddMenuEntry("Start House Rotation", MNU_START_HOUSE_ROTATION);
    glutAddMenuEntry("Stop House Rotation", MNU_STOP_HOUSE_ROTATION);
    glutAddMenuEntry("Open/Close Door", MNU_OPENCLOSE_DOOR);
    glutCreateMenu(menuCallback);

    glutAddSubMenu("Structure", menuStructure);
    glutAddSubMenu("Animation", menuAnimation);
    glutAddSubMenu("Projection", menuProj);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    init();

    glutMainLoop();
}
