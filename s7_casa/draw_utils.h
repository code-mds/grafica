//
// Created by massi on 05.03.2020.
//

#ifndef GRAFICA_DRAW_UTILS_H
#define GRAFICA_DRAW_UTILS_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
// headers richiesti da Windows e linux
#include <GL\glew.h>
#include <GL\freeglut.h>
#include "draw_utils.h"
#endif

#include <string>
#include <math.h>
#include "vertex.h"

extern bool _showWind;
extern bool _showAxis;
extern bool _showWireFrame;

struct Camera {
    vertex_t eye;
    vertex_t center;
    vertex_t up;
};

struct Perspective {
    GLdouble fovy;
    GLdouble ratio;
    GLdouble zNear, zFar;
};

struct Ortho {
    GLdouble left, right, bottom, top;
    GLdouble zNear, zFar;
};

struct color_t {
    GLubyte r,g,b;
};


struct Triangle {
    vertex_t v1, v2, v3;
    color_t color;
};

struct rectangle_t {
    vertex_t v1, v2, v3, v4;
    color_t color;
};

struct volume_t {
    vertex_t vertex[8];
};

class draw_utils {
public:
    void draw_wind(GLfloat windAngle);
    void draw_axis();
    void draw_volume(const Ortho &vol) const;
    void toggleAxesVisibility();
    void toggleWireframeVisibility();
    void toggleWindVisibility();
    void testMinMaxLineWidth();
    void draw_triangle3D(Triangle &triangle);
    void draw_triangle3D(vertex_t &v1, vertex_t &v2, vertex_t &v3, color_t &color);
    void draw_rectangle3D(rectangle_t &rect);
    void draw_prism(Triangle &front, Triangle &back);
    void draw_parallelepiped(rectangle_t &front, rectangle_t &back);
    void log(std::string msg);

private:
    void internal_triangle3D(const vertex_t &v1, const vertex_t &v2, const vertex_t &v3);

    bool _showWind = true;
    bool _showAxis = true;
    bool _showWireFrame = true;
};
#endif //GRAFICA_DRAW_UTILS_H
