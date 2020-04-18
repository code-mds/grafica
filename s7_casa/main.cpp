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
#include <iomanip>
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
#define PROJ_ORTHOGRAPHIC 'a'
#define PROJ_PERSPECTIVE 'p'

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int ANIM_MSEC = 50;
const int WIND_MSEC = 5000;
const char ESCAPE = 27;

struct AppGlobals {
    // global variables
    GLfloat windAngle = 0.0;
    int mainWindow = 0;
    GLdouble fovy = 60.0;
    camera_t camera{-1, 0, 3.0, 0, 0, 0, 0 , .1, 0};
    volume_t volume{-5.0, 5.0, -5.0, 5.0, -5.0, 10.0};
    char projection_type = PROJ_PERSPECTIVE;
    draw_utils utils;
    house house{utils};
};

AppGlobals* _app;

void displayCallback() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set MODEL/VIEW matrix mode
    glMatrixMode(GL_MODELVIEW);

    // load identity matrix
    glLoadIdentity();

    // view transformation must be called before model transformation
    // coordinates: eye, center/lookat, up vector
    gluLookAt(_app->camera.eyex, _app->camera.eyey, _app->camera.eyez,
              _app->camera.centerx, _app->camera.centery, _app->camera.centerz,
              _app->camera.upx, _app->camera.upy, _app->camera.upz);

    // model transformations
    _app->utils.draw_wind(_app->windAngle);
    _app->utils.draw_axis(_app->volume);
    _app->house.draw();

    glutSwapBuffers();
}

void windCallback(int value) {
    _app->windAngle = rand() % 360 + 1;
    _app->house.updateWind(_app->windAngle);
    glutTimerFunc(WIND_MSEC, windCallback, 0);
}

void animationCallback(int value) {
    if(_app->house.rotationEnabled())
        _app->house.updateRotation(true);

    _app->house.rotateDoor();
    _app->house.updateAnimation();

    glutTimerFunc(ANIM_MSEC, animationCallback, 0);
}

void reshapeCallback(int w, int h) {
    glViewport(0, 0, w, h);
    reshape(w, h);
}

void reshape(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLdouble l{_app->volume.left};
    GLdouble r{_app->volume.right};
    GLdouble b{_app->volume.bottom};
    GLdouble t{_app->volume.top};
    GLdouble n{_app->volume.n};
    GLdouble f{_app->volume.f};
    GLdouble ratio{1.0};

    if(_app->projection_type == PROJ_ORTHOGRAPHIC) {
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
        gluPerspective(_app->fovy, aspect, 1.0, 500.0);
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
            _app->utils.toggleAxesVisibility();
            break;
        case MNU_TOGGLE_WIREFRAME:
            _app->utils.toggleWireframeVisibility();
            break;
        case MNU_TOGGLE_WIND:
            _app->utils.toggleWindVisibility();
            break;
        case MNU_START_HOUSE_ROTATION:
            _app->house.updateRotation(true);
            break;
        case MNU_STOP_HOUSE_ROTATION:
            _app->house.updateRotation(false);
            break;
        case MNU_OPENCLOSE_DOOR:
            _app->house.toggleDoor();
            break;
        case MNU_CHANGE_COLOR:
            _app->house.changeColor();
            break;
    }
}

void setProspectiveProjection() {
    _app->utils.log("Projection: Prospective");
    forceReshape(PROJ_PERSPECTIVE);
}

void setOrthographicProjection() {
    _app->utils.log("Projection: Orthographic");
    forceReshape(PROJ_ORTHOGRAPHIC);
}

void forceReshape(char type) {
    _app->projection_type = type;
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    reshape(viewport[2], viewport[3]);
}

void specialKeyCallback(int key, int x, int y) {
    switch (key) {

        case GLUT_KEY_F9:
            _app->fovy -= 1;
            _app->utils.log("fovy=" + std::to_string(_app->fovy));
            reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
            break;
        case GLUT_KEY_F10:
            _app->fovy += 1;
            _app->utils.log("fovy=" + std::to_string(_app->fovy));
            reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
            break;

        case GLUT_KEY_F11:
            _app->camera.eyez -= .05;
            updateCamera();
            break;
        case GLUT_KEY_F12:
            _app->camera.eyez += .05;
            updateCamera();
            break;
        case GLUT_KEY_UP:
            _app->camera.eyey += .05;
            updateCamera();
            break;
        case GLUT_KEY_DOWN:
            _app->camera.eyey -= .05;
            updateCamera();
            break;
        case GLUT_KEY_RIGHT:
            _app->camera.eyex += .05;
            updateCamera();
            break;
        case GLUT_KEY_LEFT:
            _app->camera.eyex -= .05;
            updateCamera();
            break;

        case GLUT_KEY_F1:
            // translation: -X
            _app->house.moveLeft();
            break;
        case GLUT_KEY_F2:
            // translation: +X
            _app->house.moveRight();
            break;
        case GLUT_KEY_F3:
            // translation: +Y
            _app->house.moveUp();
            break;
        case GLUT_KEY_F4:
            // translation: -Y
            _app->house.moveDown();
            break;
        case GLUT_KEY_F5:
            // translation: -Z
            _app->house.moveNear();
            break;
        case GLUT_KEY_F6:
            // translation: +Z
            _app->house.moveFar();
            break;

    }
}

void updateCamera() {
    std::ostringstream ostr;
    ostr << std::fixed << std::setprecision(2);
    ostr << "Camera: x=" << _app->camera.eyex;
    ostr << ", y=" << _app->camera.eyey;
    ostr << ", z=" << _app->camera.eyez;
    _app->utils.log(ostr.str());

    glutPostRedisplay();
}

void keyCallback(unsigned char key, int x, int y) {
    switch (key) {
        case 'c':
        case 'C':
            _app->house.changeColor();
            break;

        case 'X':
        case 'x':
            _app->utils.toggleAxesVisibility();
            break;

        case 'W':
        case 'w':
            _app->utils.toggleWireframeVisibility();
            break;

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
            _app->house.updateRotation(true);
            break;

        case 'S':
        case 's':
            _app->house.updateRotation(false);
            break;

        case 'D':
        case 'd':
            _app->house.toggleDoor();
            break;

        case ESCAPE:
            glutDestroyWindow(_app->mainWindow);
            exit(0);
    }
}

void appInit() {
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    _app->mainWindow = glutCreateWindow("house");

    glutReshapeFunc(reshapeCallback);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glClearColor(COLOR_BACK);

    createMenu();

    glutDisplayFunc(displayCallback);
    glutSpecialFunc(specialKeyCallback);
    glutKeyboardFunc(keyCallback);

    glutTimerFunc(ANIM_MSEC, animationCallback, 0);
    glutTimerFunc(WIND_MSEC, windCallback, 0);
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
    AppGlobals app;
    _app = &app;

    glutInit(&argc, argv);
    appInit();

    glutMainLoop();
}
