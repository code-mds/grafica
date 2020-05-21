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

struct TextCoord {
    GLboolean enabled;
    GLfloat s1,t1;
    GLfloat s2,t2;
    GLfloat s3,t3;
};

struct Perspective {
    GLdouble fovy;
    GLdouble zNear, zFar;
};

struct Ortho {
    GLdouble left, right, bottom, top;
    GLdouble zNear, zFar;
};

struct Color {
    Color(GLubyte r, GLubyte g, GLubyte b) : _r{r/255.0f}, _g{g/255.0f}, _b{b/255.0f}, _a{1.0} { }
    GLfloat* fv() { return &_r; }
private:
    GLfloat _r;
    GLfloat _g;
    GLfloat _b;
    GLfloat _a;
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
    void enableTexture(bool enable);
    bool isTextureEnabled();
    void draw_axes();
    void toggleAxesVisibility();

    void draw_wind(GLfloat windAngle);
    void toggleWindVisibility();

    void toggleWireframeVisibility();

    void draw_triangle3D(Triangle &triangle);
    void draw_triangle3D(const Vertex &v1, const Vertex &v2, const Vertex &v3, Color &color, const TextCoord& textCoord);
    void draw_rectangle3D(Rect &rect);
    void draw_prism(Triangle &front, Triangle &back);
    void draw_parallelepiped(Rect &front, Rect &back);

    void log(const std::string &msg) const;
    void testMinMaxLineWidth();
    void draw_volume(const Ortho &vol) const;

private:
    void internal_triangle3D(const Vertex &v1, const Vertex &v2, const Vertex &v3, const TextCoord &textCoord);

    bool _showWind = true;
    bool _showAxis = true;
    bool _showWireFrame = true;
};
#endif //GRAFICA_DRAW_UTILS_H
