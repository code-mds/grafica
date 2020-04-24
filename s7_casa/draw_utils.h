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
#include <math.h>
#include "vertex.h"

struct Camera {
    vertex_t eye{0, 0, 5.0};
    vertex_t center{0, 0, 0};
    vertex_t up{0 , 1, 0};

    void reset();

    void moveLeft();
    void moveRight();

    void moveBottom();
    void moveTop();

    void moveForward();
    void moveBackward();

    void lookAt();
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
    void draw_axes();
    void toggleAxesVisibility();

    void draw_wind(GLfloat windAngle);
    void toggleWindVisibility();

    void toggleWireframeVisibility();

    void draw_triangle3D(Triangle &triangle);
    void draw_triangle3D(vertex_t &v1, vertex_t &v2, vertex_t &v3, color_t &color);
    void draw_rectangle3D(rectangle_t &rect);
    void draw_prism(Triangle &front, Triangle &back);
    void draw_parallelepiped(rectangle_t &front, rectangle_t &back);

    static void log(std::string msg);
    void testMinMaxLineWidth();
    void draw_volume(const Ortho &vol) const;

private:
    void internal_triangle3D(const vertex_t &v1, const vertex_t &v2, const vertex_t &v3);

    bool _showWind = true;
    bool _showAxis = true;
    bool _showWireFrame = true;
};
#endif //GRAFICA_DRAW_UTILS_H
