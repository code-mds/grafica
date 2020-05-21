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


// ----------------------------DEFINIZIONE SHADER ------------------------------- //
// Codice per gli shader, definito come stringa

const char *vertexShaderSource =
        "#version 330 core                              \n"
        "in vec3 position;                              \n"
        "void main()                                    \n"
        "{                                              \n"
        "   gl_Position = vec4(position, 1.0);          \n"
        "}                                              \0";

const char *fragmentShaderSource =
        "#version 330 core                              \n"
        "out vec4 FragColor;                            \n"
        "void main()                                    \n"
        "{                                              \n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);   \n"
        "}                                              \n\0";




// -------------------------------- INIZIALIZZAZIONI ------------------------------- //
void init () {

    // Coordinate dei vertici del triangolo
    float vertices[] = {
            0.0f,  0.5f, 0.0f,// Vertex 1 (X, Y, Z)
            0.5f, -0.5f, 0.0f, // Vertex 2 (X, Y, Z)
            -0.5f, -0.5f, 0.0f  // Vertex 3 (X, Y, Z)
    };

    // Si crea un Vertex Array Object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Si crea un Vertex Buffer Object
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Si copiano i vertici nel Vertex Buffer Object
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);


    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Si crea il programma shaderProgram e si linkano vertex e fragment shader
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // Si specificano quali sono gli attributi di posizione (coordinate)
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);



}

// -------------------------------- DISPLAY ------------------------------- //
void display() {

    // Cancella il color buffer
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Disegna il triangolo dalla definizione dei vertici
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glFlush();

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
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;   /* ANSI C richiede che si ritorni un int */
}
