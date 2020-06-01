//
// Created by massi on 01.06.2020.
//

#ifndef S13_CASA_SOLID_H
#define S13_CASA_SOLID_H

#include <GL/glew.h>
#ifdef __APPLE__
// Headers richiesti da OSX
    #include <GLUT/glut.h>
#else
// headers richiesti da Windows e linux
#include <GL/glut.h>
#endif
#include <vector>
#include "vertex.h"

class Solid {
public:
    explicit Solid(std::vector<Vertex> vertices, std::vector<GLuint> indices);
    ~Solid();
    void draw();
    void init();

protected:
    std::vector<GLuint> _indices;
    std::vector<Vertex> _vertices;
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
};

class Box : public Solid {
public:
    explicit Box(std::vector<Vertex> vertices);
};

class Prism : public Solid {
public:
    explicit Prism(std::vector<Vertex> vertices);
};


#endif //S13_CASA_SOLID_H
