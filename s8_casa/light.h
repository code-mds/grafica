//
// Created by massi on 02.05.2020.
//

#ifndef S8_CASA_LIGHT_H
#define S8_CASA_LIGHT_H

#ifdef __APPLE__
#include <GL/glew.h>
#include <GLUT/glut.h>
#else
// headers richiesti da Windows e linux
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "vertex.h"

#endif

static const GLfloat MATERIAL_WHITE[] = {1.0, 1.0, 1.0, 1.0 };
static const GLfloat MATERIAL_BLACK[] = {0.0f, 0.0f, 0.0f, 1.0f};
static const GLfloat MATERIAL_RED[] = {1.0f, 0.0f, 0.0f, 1.0f};
static const GLfloat MATERIAL_YELLOW[] = {0.1f, 1.0f, 0.0f, 1.0f};

static const GLfloat SHININESS_OFF = 0.0f;
static const GLfloat SHININESS_LOW = 20.0f;
static const GLfloat SHININESS_HIGH = 100.0f;

class Light {
public:
    Light();
    explicit Light(const Vertex& pos, const Vertex& dir);
    void toggle();
    void draw();

    static void globalAmbient();
    static GLboolean isColorMaterialOn();

private:
    void drawLightSource() const;

    static int LastCreated;

    bool _isOn;
    int _lightNum;
    Vertex _position;
    Vertex _direction;

    void drawSpot();
};


#endif //S8_CASA_LIGHT_H
