#pragma clang diagnostic ignored "-Wdeprecated-declarations"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

// Headers richiesti da OSX
#ifdef __APPLE__
//#include <OpenGL/gl3.h>
#include <GL/glew.h>
#include <GLUT/glut.h>
#include <iostream>


// headers richiesti da Windows e linux
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

// Funzioni per caricare, inizializzare e compilare gli shader
#include "../shaders_loader.h"
#include "Texture.h"

// Librerie matematiche
// Si usano i radianti (gli angoli in decimale sono deprecati)
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <stack>


// -------------------------------- VARIABILI GLOBALI ------------------------------- //

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
const int ANIM_MSEC = 10;

GLuint VAO;
GLuint VBO;
GLuint EBO;
Texture _texture;
GLfloat _doorAngle = 0.0;
GLboolean _doorOpen = false;
GLfloat PI_HALF = glm::pi<float>() / 2;
GLfloat DOOR_STEP = 1 / 180.0f * glm::pi<float>();


struct Vertex {
    // position
    glm::vec3 Position;
    // color
    glm::vec3 Color;
    // texCoords
    glm::vec2 TexCoords;
};

void initMenu();

std::vector<GLuint> indices;
std::vector<Vertex> vertices;

GLint projectionPos, modelviewPos; // Riferimenti alle variabili uniform
glm::mat4 projection, modelview; // Riferimenti alle matrici modelview e proiezione
int mouseoldx, mouseoldy ; // Usate dai callback del mouse

glm::vec3 initEyeloc = glm::vec3(0.0, -2.0, 6.0); // Posizione iniziale del punto di vista
glm::vec3 direction = glm::vec3(0.0, 0.0, 0.0);;
glm::vec3 eyeloc = initEyeloc;
static const GLfloat SW = 5.0f; //SCENE WIDTH

const float DOOR_THINK = 2.5f / SW;
const float HALF_DOOR_WIDTH = 2.0f / SW;
const float HALF_BASE_WIDTH = 5.0f / SW;
const float BASE_HEIGHT = 8.0f / SW;
const float WALL_THICK = 0.5f / SW;
const float WALL_HEIGHT = 6.0f / SW;

void menuCallback(int value) {
    switch (value) {
        case MNU_OPENCLOSE_DOOR:
            _doorOpen = !_doorOpen;
            break;
    }
}

// -------------------------------- INIZIALIZZAZIONI ------------------------------- //
void init() {
    initMenu();
    glEnable(GL_DEPTH_TEST);
    _texture.init();
    // Coordinate dei vertici del triangolo
    // positions          // colors           // texture coords
    vertices = {
            {{ -HALF_DOOR_WIDTH, 0, -WALL_THICK },{1.0f, 1.0f, 1.0f},   {0.0f, 0.0f} },       // bottom left front
            {{ HALF_DOOR_WIDTH, 0, -WALL_THICK },{1.0f, 1.0f, 1.0f},   {1.0f, 0.0f}},       // bottom right front
            {{ HALF_DOOR_WIDTH, WALL_HEIGHT, -WALL_THICK },{1.0f, 1.0f, 1.0f},   {1.0f, 1.0f}},       // top right front
            {{ -HALF_DOOR_WIDTH, WALL_HEIGHT, -WALL_THICK },{1.0f, 1.0f, 1.0f},   {0.0f, 1.0f}},       // top left front

            {{ HALF_DOOR_WIDTH, 0, -(WALL_THICK+DOOR_THINK) }, { 1.0f, 1.0f, 1.0f},   {0.0f, 0.0f}},       // bottom left back
            {{ -HALF_DOOR_WIDTH, 0, -(WALL_THICK+DOOR_THINK) }, { 1.0f, 1.0f, 1.0f},   {1.0f, 0.0f}},       // bottom right back
            {{ -HALF_DOOR_WIDTH, WALL_HEIGHT, -(WALL_THICK+DOOR_THINK) }, { 1.0f, 1.0f, 1.0f},   {1.0f, 1.0f}},       // top right back
            {{ HALF_DOOR_WIDTH, WALL_HEIGHT, -(WALL_THICK+DOOR_THINK) }, { 1.0f, 1.0f, 1.0f},   {0.0f, 1.0f}},       // top left back
    };
    indices = {
        0, 1, 2, 0, 2, 3, // front
        1, 4, 7, 1, 7, 2, // right
        4, 5, 6, 4, 6, 7, // back
        5, 0, 3, 5, 3, 6, // left
        0, 1, 4, 0, 4, 5, // bottom
        3, 2, 7, 3, 7, 6, // top
    };

    glGenVertexArrays(1, &VAO); // Vertex Array Object
    glGenBuffers(1, &VBO);      // Vertex Buffer Object
    glGenBuffers(1, &EBO);      // Element Buffer Object

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

    // position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,    // indice dell’attributo
            3,                  // n. di componenti (1..4)
            GL_FLOAT,           // tipo di dato
            GL_TRUE,            // se da normalizzare
            sizeof(Vertex),     // offset (in byte) fra dati consecutivi
            (void*)0);

    // color attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));

    // texture coord attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);

    // Carica gli shaders dai rispettivi files, inizializza, linka e compila
    GLuint vertexShader = initshaders(GL_VERTEX_SHADER, "shaders/shader.vert") ;
    GLuint fragmentShader = initshaders(GL_FRAGMENT_SHADER, "shaders/shader.frag") ;
    GLuint shaderProgram = initprogram(vertexShader, fragmentShader) ;
    glBindFragDataLocation(shaderProgram, 0, "outColor");

    // Inizializza la matrice di proiezione con la matrice di identità
    projection = glm::mat4(1.0f);

    // Definisce il punto di vista (posizione, dove guarda, upvector)
    modelview = glm::lookAt(initEyeloc, direction, glm::vec3(0, 1, 1));

    // Leggi le posizioni delle variabili uniform
    projectionPos = glGetUniformLocation(shaderProgram, "projection_matrix");
    modelviewPos = glGetUniformLocation(shaderProgram, "modelview_matrix");

    // Passa le matrici di proiezione e modelview allo shader
    glUniformMatrix4fv(projectionPos, 1, GL_FALSE, &projection[0][0]);
}

void initMenu() {
    int menuAnimation = glutCreateMenu(menuCallback);
    glutAddMenuEntry("Open/Close Door", MNU_OPENCLOSE_DOOR);
    glutCreateMenu(menuCallback);

    glutAddSubMenu("Animation", menuAnimation);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void rotateDoor() {
    if(_doorOpen && _doorAngle < PI_HALF) {
        _doorAngle += DOOR_STEP;
    } else if(!_doorOpen && _doorAngle > 0) {
        _doorAngle -= DOOR_STEP;
    }
}


// -------------------------------- DISPLAY ------------------------------- //
void display() {

    // Cancella il color buffer
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 ori = modelview;

    // Rotazione intorno ad uno dei vertici. Notare che l'angolo va passato in radianti. Rotazione di 1 grado
    modelview  = glm::translate(modelview, glm::vec3(-HALF_DOOR_WIDTH, 0.f, -WALL_THICK));
    modelview = glm::rotate(modelview, _doorAngle, glm::vec3(0.0f, 1.0f, 0.0f));
    modelview  = glm::translate(modelview, glm::vec3(HALF_DOOR_WIDTH, 0.f, WALL_THICK));

    // Passa la matrice di modelview allo shader
    glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &modelview[0][0]);

    // render container
    glBindVertexArray(VAO);

    // draw door
    _texture.enableTexture(true);
    _texture.bind(TextureEnum::WALL);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    _texture.enableTexture(false);

    modelview = ori;
    // Passa la matrice di modelview allo shader
    glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &modelview[0][0]);

    glFlush();
}

// -------------------------------- TIMER ------------------------------- //
void TimerFunc(int value)
{
    rotateDoor();

    glutPostRedisplay();
    glutTimerFunc(ANIM_MSEC, TimerFunc, 1);
}

// -------------------------------- RESHAPE ------------------------------- //
void reshape(int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);

    // Imposta la matrice di proiezione di tipo prospettica
    // notare che l'angolo va passato in radianti
    projection = glm::perspective(30.0f / 180.0f * glm::pi<float>(), (GLfloat)w / (GLfloat)h, 1.0f, 10.0f);
    glUniformMatrix4fv(projectionPos, 1, GL_FALSE, &projection[0][0]);
}


// -------------------------------- EVENTI DEL MOUSE ------------------------------- //


void mouse(int button, int state, int x, int y)
{

    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_UP) {
            // Do Nothing ;
        }
        else if (state == GLUT_DOWN) {
            mouseoldx = x ; mouseoldy = y ; // so we can move wrt x , y
        }
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {

        // Resetta gluLookAt al valore iniziale
        eyeloc = initEyeloc;
        modelview = glm::lookAt(eyeloc, glm::vec3(0, 0, 0), glm::vec3(0, 1, 1));

        // Invia la matrice aggiornata allo shader e ridisegna
        glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &modelview[0][0]);
        glutPostRedisplay() ;
    }
}

void mousedrag(int x, int y) {
    int xloc = x - mouseoldx;
    int yloc = y - mouseoldy;    // si usa la coordinata y per definire lo zoom in/out

    // Sposta il punto di vista di un fattore proporzionale allo spostamento del mouse
    eyeloc += glm::vec3(-0.005*xloc, -0.005*yloc, +0.005*yloc);

    if (yloc<0) yloc = 0;
    mouseoldy = y ;

    /* imposta nella modelview il nuovo punto di vista */
    modelview = glm::lookAt(eyeloc, direction, glm::vec3(0, 1, 1));

    // Invia la matrice aggiornata allo shader e ridisegna
    glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &modelview[0][0]);
    glutPostRedisplay() ;
}

// -------------------------------- EVENTI DEL MOUSE E TASTIERA ------------------------------- //
void keyboard (unsigned char key, int x, int y)
{
    switch (key) {
        case 27:  // Tasto Escape per uscire

            // Cancella tutti i buffers allocati
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
            glDeleteBuffers(1, &EBO);

            exit(0) ;
        default:
            break ;
    }
}

// -------------------------------- MAIN ------------------------------- //
int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    // OSX richiede una chiamata specifica
#ifdef __APPLE__
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_SINGLE | GLUT_RGB);
#else
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB) ;
#endif
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Hello world Shaders");

    // Inizializza Glew
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::cout << "Error: " << glewGetString(err) << std::endl;
    }

    init();

    // Vari callback.
    glutDisplayFunc(display);
    glutReshapeFunc(reshape) ;
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse) ;
    glutMotionFunc(mousedrag) ;

    glutTimerFunc(1000, TimerFunc, 1);

    glutMainLoop();

    return 0;   /* ANSI C richiede che si ritorni un int */
}
