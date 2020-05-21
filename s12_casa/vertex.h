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


struct Vertex {
    GLfloat x=0, y=0, z=0, w=1;

    void set(float x, float y, float z);
    void copyFrom(const Vertex& o);
    Vertex operator-() const;
    Vertex sum(const Vertex& o) const;
    Vertex subtract(const Vertex& o) const;

    Vertex crossProduct(const Vertex& o) const;
    Vertex scalarProduct(float scalar) const;
    GLfloat dotProduct(const Vertex& u) const;
    Vertex matrixProduct(const float *m) const;
    bool inViewingVolume(const float* projectionMatrix, const float *modelviewMatrix) const;

    GLfloat length() const;

    static void matrixTranspose(const float *m, float *t);
    static Vertex normal(const Vertex &v1, const Vertex &v2, const Vertex &v3);

private:
    void normalize();
};


#endif //S7_CASA_VERTEX_H
