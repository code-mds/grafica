#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#include <GL/glew.h>
#ifdef __APPLE__
// Headers richiesti da OSX
    #include <GLUT/glut.h>
#else
// headers richiesti da Windows e linux
#include <GL/glut.h>
#endif

// Librerie matematiche
// Si usano i radianti (gli angoli in decimale sono deprecati)
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stdlib.h>
#include <iostream>

// Funzioni per caricare, inizializzare e compilare gli shader
#include "shaders_loader.h"
#include "Texture.h"
#include "solid.h"
#include "house.h"
#include "main.h"
#include "RgbImage.h"
#include "camera.h"

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
    GLint projectionPos, modelviewPos; // Riferimenti alle variabili uniform
    glm::mat4 projection, modelview; // Riferimenti alle matrici modelview e proiezione
    Camera camera{modelview, modelviewPos};

    // global variables
    GLfloat windAngle = 0.0;
    int mainWindowID = 0;
    GLfloat fovy = 30;

    Texture texture;

    //Clip Plane equation: Ax + By + Cz + D = 0
    GLdouble clip_plane_0[4]={ -1.0, -0.3, 0.0, 0.5 };
    bool enableClipPlane = false;

    House house{modelview, modelviewPos, texture};
};


static AppGlobals* _app;

void log(std::basic_string<char> msg) {
    std::cout << msg << std::endl;
}

void displayCallback() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // view transformation must be called before model transformation
    _app->camera.lookAt();

    // draw house
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
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    GLfloat aspect = (GLfloat)w/(h==0 ? 1.0 : h);
    // Imposta la matrice di proiezione di tipo prospettica
    // notare che l'angolo va passato in radianti
    _app->projection = glm::perspective(_app->fovy / 180.0f * glm::pi<float>(), aspect, 1.0f, 10.0f);
    glUniformMatrix4fv(_app->projectionPos, 1, GL_FALSE, &_app->projection[0][0]);
}

void menuCallback(int value) {
    switch (value) {
        case MNU_SAVE_BMP:
            saveFile();
            break;
        case MNU_TOGGLE_CLIPPLANE:
            toggleClipPlane();
            break;
        case MNU_RESET:
            reset();
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
        default:
            log("unhandled MENU");
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
    log("reset");
}

void specialKeyCallback(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_F12:
            reset();
            break;
        case GLUT_KEY_F9:
            _app->fovy -= 1;
            log("fovy=" + std::to_string(_app->fovy));
            //TODO reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
            break;
        case GLUT_KEY_F10:
            _app->fovy += 1;
            log("fovy=" + std::to_string(_app->fovy));
            //TODO reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
            break;

        case GLUT_KEY_PAGE_DOWN:
            _app->camera.moveBackward();
            updateCamera();
            break;
        case GLUT_KEY_PAGE_UP:
            _app->camera.moveForward();
            updateCamera();
            break;
        case GLUT_KEY_UP:
            _app->camera.moveTop();
            updateCamera();
            break;
        case GLUT_KEY_DOWN:
            _app->camera.moveBottom();
            updateCamera();
            break;
        case GLUT_KEY_RIGHT:
            _app->camera.moveRight();
            updateCamera();
            break;
        case GLUT_KEY_LEFT:
            _app->camera.moveLeft();
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
            log("unhandled key");
            break;
    }
}

void updateCamera() {
    log(_app->camera.toString());
    glutPostRedisplay();
}

void keyCallback(unsigned char key, int x, int y) {
    switch (key) {
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
            log("unhandled key");
            break;
    }
}

void initApp() {

#ifdef __APPLE__
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_SINGLE | GLUT_RGB);
#else
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
#endif

    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    _app->mainWindowID = glutCreateWindow("house shader");

    // Inizializza Glew
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::cout << "Error: " << glewGetString(err) << std::endl;
    }

    glEnable(GL_DEPTH_TEST);
    glClearColor(COLOR_BKG);
    if(_app->enableClipPlane) {
        glEnable(GL_CLIP_PLANE0);
    } else {
        glDisable(GL_CLIP_PLANE0);
    }

    _app->texture.init();
    _app->house.init();
    initShader();
    createMenu();

    // callbacks
    glutReshapeFunc(reshapeCallback);
    glutDisplayFunc(displayCallback);
    glutSpecialFunc(specialKeyCallback);
    glutKeyboardFunc(keyCallback);

    // timers
    glutTimerFunc(ANIM_MSEC, animationCallback, 0);
    glutTimerFunc(WIND_MSEC, windCallback, 0);
}

void initShader() {
    // Carica gli shaders dai rispettivi files, inizializza, linka e compila
    GLuint vertexShader = initshaders(GL_VERTEX_SHADER, "shaders/shader.vert") ;
    GLuint fragmentShader = initshaders(GL_FRAGMENT_SHADER, "shaders/shader.frag") ;
    GLuint shaderProgram = initprogram(vertexShader, fragmentShader) ;
    glBindFragDataLocation(shaderProgram, 0, "outColor");

    // Inizializza la matrice di proiezione con la matrice di identità
    _app->projection = glm::mat4(1.0f);

    // Definisce il punto di vista (posizione, dove guarda, upvector)
    _app->modelview = glm::lookAt(_app->camera.eye, _app->camera.center, _app->camera.up);

    // Leggi le posizioni delle variabili uniform
    _app->projectionPos = glGetUniformLocation(shaderProgram, "projection_matrix");
    _app->modelviewPos = glGetUniformLocation(shaderProgram, "modelview_matrix");

    // Passa le matrici di proiezione e modelview allo shader
    glUniformMatrix4fv(_app->projectionPos, 1, GL_FALSE, &_app->projection[0][0]);
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

    int menuStructure = glutCreateMenu(menuCallback);
    glutAddMenuEntry("Reset", MNU_RESET);
    glutCreateMenu(menuCallback);

    int menuAnimation = glutCreateMenu(menuCallback);
    glutAddMenuEntry("Start House Rotation", MNU_START_HOUSE_ROTATION);
    glutAddMenuEntry("Stop House Rotation", MNU_STOP_HOUSE_ROTATION);
    glutAddMenuEntry("Open/Close Door", MNU_OPENCLOSE_DOOR);
    glutCreateMenu(menuCallback);

    glutAddSubMenu("File", menuFile);
    glutAddSubMenu("Structure", menuStructure);
    glutAddSubMenu("Animation", menuAnimation);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char* argv[]) {
    AppGlobals app;
    _app = &app;

    glutInit(&argc, argv);
    initApp();
    glutMainLoop();
}
