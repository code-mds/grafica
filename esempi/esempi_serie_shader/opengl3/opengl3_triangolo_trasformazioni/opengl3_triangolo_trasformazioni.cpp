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

// Librerie matematiche
// Si usano i radianti (gli angoli in decimale sono deprecati)
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


// -------------------------------- VARIABILI GLOBALI ------------------------------- //

GLuint vao;
GLuint vbo;
GLint projectionPos, modelviewPos; // Riferimenti alle variabili uniform
glm::mat4 projection, modelview; // Riferimenti alle matrici modelview e proiezione
int mouseoldx, mouseoldy ; // Usate dai callback del mouse

glm::vec3 initEyeloc = glm::vec3(0.0, -2.0, 6.0); // Posizione iniziale del punto di vista
glm::vec3 eyeloc = initEyeloc;


// -------------------------------- INIZIALIZZAZIONI ------------------------------- //
void init () {


    // Coordinate dei vertici del triangolo
    float vertices[] = {
            0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Vertex 1 (X, Y, Z)
            0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // Vertex 2 (X, Y, Z)
            -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f // Vertex 3 (X, Y, Z)
    };

    // Si crea un Vertex Array Object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Si crea un Vertex Buffer Object
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Si copiano i vertici nel Vertex Buffer Object
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    // Carica gli shaders dai rispettivi files, inizializza, linka e compila
    GLuint vertexShader = initshaders(GL_VERTEX_SHADER, "shaders/shader.vert") ;
    GLuint fragmentShader = initshaders(GL_FRAGMENT_SHADER, "shaders/shader.frag") ;
    GLuint shaderProgram = initprogram(vertexShader, fragmentShader) ;
    glBindFragDataLocation(shaderProgram, 0, "outColor");


    // Si specificano quali sono gli attributi di posizione dei vertici
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray((GLuint) posAttrib);
    glVertexAttribPointer((GLuint) posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

    // e gli attributi di colore dei vertici
    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray((GLuint) colAttrib);
    glVertexAttribPointer((GLuint) colAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Inizializza la matrice di proiezione con la matrice di identità
    projection = glm::mat4(1.0f);

    // Definisce il punto di vista (posizione, dove guarda, upvector)
    modelview = glm::lookAt(initEyeloc, glm::vec3(0,0,0), glm::vec3(0, 1, 1));

    // Leggi le posizioni delle variabili uniform
    projectionPos = glGetUniformLocation(shaderProgram, "projection_matrix");
    modelviewPos = glGetUniformLocation(shaderProgram, "modelview_matrix");


    // Passa le matrici di proiezione e modelview allo shader
    glUniformMatrix4fv(projectionPos, 1, GL_FALSE, &projection[0][0]);


}

// -------------------------------- DISPLAY ------------------------------- //
void display() {

    // Cancella il color buffer
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Rotazione intorno ad uno dei vertici. Notare che l'angolo va passato in radianti. Rotazione di 1 grado
    modelview  = glm::translate(modelview, glm::vec3(0.5f, -0.5f, 0.0f));
    modelview = glm::rotate(modelview, 1 / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 0.0f, 1.0f));
    modelview  = glm::translate(modelview, glm::vec3(-0.5f, 0.5f, 0.0f));

    // Passa la matrice di modelview allo shader
    glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &modelview[0][0]);


    // Disegna il triangolo dalla definizione dei vertici
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glFlush();
}

// -------------------------------- TIMER ------------------------------- //
void TimerFunc(int value)
{
    glutPostRedisplay();
    glutTimerFunc(10, TimerFunc, 1);
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
    int yloc = y - mouseoldy  ;    // si usa la coordinata y per definire lo zoom in/out

    // Sposta il punto di vista di un fattore proporzionale allo spostamento del mouse
    eyeloc += glm::vec3(0.0, -0.005*yloc, +0.005*yloc);

    if (yloc<0) yloc = 0;
    mouseoldy = y ;

    /* imposta nella modelview il nuovo punto di vista */
    modelview = glm::lookAt(eyeloc, glm::vec3(0, 0, 0), glm::vec3(0, 1, 1));

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
            glDeleteVertexArrays(1, &vao);
            glDeleteBuffers(1, &vbo);

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

    init ();

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
