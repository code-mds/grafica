//
// Created by massi on 01.06.2020.
//

#ifndef GL_ESEMPI_BOX_H
#define GL_ESEMPI_BOX_H

#include <GL/glew.h>
#ifdef __APPLE__
// Headers richiesti da OSX
    #include <GLUT/glut.h>
#else
// headers richiesti da Windows e linux
#include <GL/glut.h>
#endif
#include <vector>
#include "Vertex.h"

class Box {
public:
    explicit Box(std::vector<Vertex> vertices);
    ~Box();
    void draw();
    void init();

private:
    std::vector<GLuint> indices;
    std::vector<Vertex> vertices;
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
};


#endif //GL_ESEMPI_BOX_H
