//
// Created by massi on 05.03.2020.
//

#ifndef GRAFICA_DRAW_UTILS_H
#define GRAFICA_DRAW_UTILS_H

#ifdef __APPLE__
#include <GL/glew.h>
#include <GLUT/glut.h>
#else
// headers richiesti da Windows e linux
#include <GL/glew.h>
#include <GL/freeglut.h>
#endif

#include <string>
#include <cmath>
#include "vertex.h"

struct Perspective {
    GLdouble fovy;
    GLdouble zNear, zFar;
};

struct Ortho {
    GLdouble left, right, bottom, top;
    GLdouble zNear, zFar;
};

struct Color {
    GLubyte r{255};
    GLubyte g{255};
    GLubyte b{255};
};

struct Triangle {
    Vertex v1, v2, v3;
    Color color;
};

struct Rect {
    Vertex v1, v2, v3, v4;
    Color color;
};

struct Volume {
    Vertex vertexes[8];
};

class draw_utils {
public:
    void draw_axes();
    void toggleAxesVisibility();

    void draw_wind(GLfloat windAngle);
    void toggleWindVisibility();

    void toggleWireframeVisibility();

    void draw_triangle3D(Triangle &triangle);
    void draw_triangle3D(Vertex &v1, Vertex &v2, Vertex &v3, Color &color);
    void draw_rectangle3D(Rect &rect);
    void draw_prism(Triangle &front, Triangle &back);
    void draw_parallelepiped(Rect &front, Rect &back);

    void log(std::string msg);
    void testMinMaxLineWidth();
    void draw_volume(const Ortho &vol) const;

private:
    void internal_triangle3D(const Vertex &v1, const Vertex &v2, const Vertex &v3);

    bool _showWind = true;
    bool _showAxis = true;
    bool _showWireFrame = true;
};
#endif //GRAFICA_DRAW_UTILS_H
