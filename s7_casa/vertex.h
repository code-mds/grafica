//
// Created by massi on 18.04.2020.
//

#ifndef S7_CASA_VERTEX_H
#define S7_CASA_VERTEX_H

#ifdef __APPLE__
    // Headers richiesti da OSX
    #include <GL/glew.h>
    #include <GLUT/glut.h>
#else
// headers richiesti da Windows e linux
    #include <GL/glew.h>
    #include <GL/freeglut.h>
#endif


struct vertex_t {
    GLfloat x, y, z, w=1;

    void set(float x, float y, float z);
    void copyFrom(const vertex_t& o);
    vertex_t operator-();
    vertex_t sum(const vertex_t& o);
    vertex_t crossProduct(const vertex_t& o);
    vertex_t scalarProduct(float scalar);
    GLfloat dotProduct(const vertex_t& u);
    vertex_t matrixProduct(const float *m);
    bool inViewingVolume(const float* projectionMatrix, const float *modelviewMatrix);
    static void matrixTranspose(const float *m, float *t);

    GLfloat length();
    void normalize();
};


#endif //S7_CASA_VERTEX_H
