//glut_test.cpp
//glut_test.cpp
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#ifdef __APPLE__
    // Headers richiesti da OSX
    #include <GL/glew.h>
    #include <GLUT/glut.h>
#else
    // headers richiesti da Windows e linux
#include <GL/glew.h>
#include <GL/freeglut.h>
#endif

#include <cstdlib>
#include "camera.h"
#include "draw_utils.h"
#include "house.h"
#include "main.h"
#include "RgbImage.h"
#include "Texture.h"

#define ANG2RAD (3.14159265358979323846 / 180.0 * 0.5)

#define COLOR_BKG 1.0, 1.0, 1.0, 0.0
#define CAPTURE_FILENAME "capture.bmp"

#define MNU_SAVE_BMP 17
#define MNU_TOGGLE_CLIPPLANE 16
#define MNU_LIGHT_POS_2REL 15
#define MNU_LIGHT_POS_1REL 14
#define MNU_LIGHT_POS_2ABS 13
#define MNU_TOGGLE_LIGHT2 12
#define MNU_TOGGLE_LIGHT1 11
#define MNU_RESET 10
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
    int mainWindowID = 0;

    // The light source can be a POSITIONAL (w > 0) or DIRECTIONAL (w = 0) light source depending on the w value.
    Light light1{Vertex{-.4, 1.2, -.6, 1.0}, Vertex{.1, .1, 1}};
    Light light2{Vertex{.2, .1, .5, 1.0}, Vertex{-.1, .1, -1}};
    Texture texture;
    Camera camera;

    //Clip Plane equation: Ax + By + Cz + D = 0
    GLdouble clip_plane_0[4]={ -1.0, -0.3, 0.0, 0.5 };
    bool enableClipPlane = false;

    Ortho ortho{-6.0, 6.0, -6.0, 6.0, -6.0, 50.0};
    Perspective perspective{  45.0, 1.0, 100.0};
    char projection_type = PROJ_PERSPECTIVE; //PROJ_ORTHOGRAPHIC

    draw_utils utils;
    House house{utils, light1, light2, texture};
};

static AppGlobals* _app;

void displayCallback() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // view transformation must be called before model transformation
    _app->camera.lookAt();

    // model transformations
    _app->utils.draw_wind(_app->windAngle);
    _app->utils.draw_axes();
    _app->house.draw();
    glClipPlane (GL_CLIP_PLANE0, _app->clip_plane_0);
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

    GLdouble aspect = (GLdouble)w/(h==0 ? 1 : h);

    if(_app->projection_type == PROJ_ORTHOGRAPHIC) {
        GLdouble l{_app->ortho.left};
        GLdouble r{_app->ortho.right};
        GLdouble b{_app->ortho.bottom};
        GLdouble t{_app->ortho.top};
        // orthographic projection
        if (w <= h) {
            b /= aspect;
            t /= aspect;
        } else {
            l *= aspect;
            r *= aspect;
        }
        glOrtho(l, r, b, t, _app->ortho.zNear, _app->ortho.zFar);
    } else {
        // perspective projection using glFrustum
        GLdouble fH = tan(_app->perspective.fovy * ANG2RAD) * _app->perspective.zNear;
        GLdouble fW = fH * aspect;
        glFrustum(-fW, fW, -fH, fH, _app->perspective.zNear, _app->perspective.zFar);

        // perspective projection using gluPerspective
        //gluPerspective(_app->perspective.fovy, aspect, _app->perspective.zNear, _app->perspective.zFar);
    }
}


void menuCallback(int value) {
    switch (value) {
        case MNU_SAVE_BMP:
            saveFile();
            break;
        case MNU_TOGGLE_CLIPPLANE:
            toggleClipPlane();
            break;
        case MNU_LIGHT_POS_2REL:
            _app->light2.setRelative(true);
            _app->light1.setRelative(true);
            break;
        case MNU_LIGHT_POS_1REL:
            _app->light2.setRelative(false);
            _app->light1.setRelative(true);
            break;
        case MNU_LIGHT_POS_2ABS:
            _app->light2.setRelative(false);
            _app->light1.setRelative(false);
            break;
        case MNU_TOGGLE_LIGHT2:
            _app->light2.toggle();
            break;
        case MNU_TOGGLE_LIGHT1:
            _app->light1.toggle();
            break;
        case MNU_RESET:
            reset();
            break;
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
        default:
            _app->utils.log("unhandled MENU");
            break;
    }
}

void toggleClipPlane() {
    _app->enableClipPlane = !_app->enableClipPlane;
    if(_app->enableClipPlane) {
        glEnable(GL_CLIP_PLANE0);
    } else {
        glDisable(GL_CLIP_PLANE0);
    }
    glutPostRedisplay();
}

/**
 * reset model and camera to initial values
 */
void reset() {
    _app->camera.reset();
    _app->house.reset();
    _app->utils.log("reset");
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
    GLint viewport[4]; //x,y,w,h
    glGetIntegerv(GL_VIEWPORT, viewport);
    reshape(viewport[2], viewport[3]);
}

void specialKeyCallback(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_F12:
            reset();
            break;
        case GLUT_KEY_F9:
            _app->perspective.fovy -= 1;
            _app->utils.log("fovy=" + std::to_string(_app->perspective.fovy));
            reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
            break;
        case GLUT_KEY_F10:
            _app->perspective.fovy += 1;
            _app->utils.log("fovy=" + std::to_string(_app->perspective.fovy));
            reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
            break;

        case GLUT_KEY_PAGE_DOWN:
            _app->camera.moveBackward();
            if(!_app->house.inBoundaries())
                _app->camera.moveForward();

            updateCamera();
            break;
        case GLUT_KEY_PAGE_UP:
            _app->camera.moveForward();
            if(!_app->house.inBoundaries())
                _app->camera.moveBackward();
            updateCamera();
            break;
        case GLUT_KEY_UP:
            _app->camera.moveTop();
            if(!_app->house.inBoundaries())
                _app->camera.moveBottom();
            updateCamera();
            break;
        case GLUT_KEY_DOWN:
            _app->camera.moveBottom();
            if(!_app->house.inBoundaries())
                _app->camera.moveTop();
            updateCamera();
            break;
        case GLUT_KEY_RIGHT:
            _app->camera.moveRight();
            if(!_app->house.inBoundaries())
                _app->camera.moveLeft();
            updateCamera();
            break;
        case GLUT_KEY_LEFT:
            _app->camera.moveLeft();
            if(!_app->house.inBoundaries())
                _app->camera.moveRight();
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
        default:
            _app->utils.log("unhandled key");
            break;
    }
}

void updateCamera() {
    _app->utils.log(_app->camera.toString());
    glutPostRedisplay();
}

void keyCallback(unsigned char key, int x, int y) {
    switch (key) {
        case 'C':
        case 'c':
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
            glutDestroyWindow(_app->mainWindowID);
            exit(0);

        default:
            _app->utils.log("unhandled key");
            break;
    }
}

void appInit() {

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    _app->mainWindowID = glutCreateWindow("house");

    glClearColor(COLOR_BKG);
    if(_app->enableClipPlane) {
        glEnable(GL_CLIP_PLANE0);
    } else {
        glDisable(GL_CLIP_PLANE0);
    }

    initLight();
    initTexture();
    createMenu();

    glutReshapeFunc(reshapeCallback);
    glutDisplayFunc(displayCallback);
    glutSpecialFunc(specialKeyCallback);
    glutKeyboardFunc(keyCallback);

    glutTimerFunc(ANIM_MSEC, animationCallback, 0);
    glutTimerFunc(WIND_MSEC, windCallback, 0);
}


void initTexture() {
    _app->texture.init();
}

void initLight() {
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
//    glEnable(GL_COLOR_MATERIAL);
    Light::globalAmbient();
}

void saveFile()
{
    RgbImage theTexMap;
    theTexMap.LoadFromOpenglBuffer();
    theTexMap.WriteBmpFile(CAPTURE_FILENAME);
}

void createMenu() {
    int menuFile = glutCreateMenu(menuCallback);
    glutAddMenuEntry("Export as bmp", MNU_SAVE_BMP);

    int menuLight = glutCreateMenu(menuCallback);
    glutAddMenuEntry("On/Off Light 1", MNU_TOGGLE_LIGHT1);
    glutAddMenuEntry("On/Off Light 2", MNU_TOGGLE_LIGHT2);
    glutAddMenuEntry("Light 1/2 in relative position", MNU_LIGHT_POS_2REL);
    glutAddMenuEntry("Light 1 in relative position", MNU_LIGHT_POS_1REL);
    glutAddMenuEntry("Light 1/2 in absolute position", MNU_LIGHT_POS_2ABS);

    int menuProjection = glutCreateMenu(menuCallback);
    glutAddMenuEntry("Perspective", MNU_PERSPECTIVE);
    glutAddMenuEntry("Ortho", MNU_ORTHO);
    glutAddMenuEntry("Toggle Clip Plane", MNU_TOGGLE_CLIPPLANE);
    glutCreateMenu(menuCallback);

    int menuStructure = glutCreateMenu(menuCallback);
    glutAddMenuEntry("Show/Hide Wind", MNU_TOGGLE_WIND);
    glutAddMenuEntry("Show/Hide Axes", MNU_TOGGLE_AXIS);
    glutAddMenuEntry("Show/Hide Wireframe", MNU_TOGGLE_WIREFRAME);
    glutAddMenuEntry("Change color", MNU_CHANGE_COLOR);
    glutAddMenuEntry("Reset", MNU_RESET);
    glutCreateMenu(menuCallback);

    int menuAnimation = glutCreateMenu(menuCallback);
    glutAddMenuEntry("Start House Rotation", MNU_START_HOUSE_ROTATION);
    glutAddMenuEntry("Stop House Rotation", MNU_STOP_HOUSE_ROTATION);
    glutAddMenuEntry("Open/Close Door", MNU_OPENCLOSE_DOOR);
    glutCreateMenu(menuCallback);

    glutAddSubMenu("File", menuFile);
    glutAddSubMenu("Light", menuLight);
    glutAddSubMenu("Structure", menuStructure);
    glutAddSubMenu("Animation", menuAnimation);
    glutAddSubMenu("Projection", menuProjection);
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
