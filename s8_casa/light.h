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

class Light {
public:
    Light();
    Light(const Vertex& pos);
    void toggle();
    void draw();

private:
    void update() const;

    bool _isOn;
    GLenum _lightNum;
    Vertex _position;
    Vertex _direction;

    static GLenum LastCreated;

    void drawLightSource() const;
};


#endif //S8_CASA_LIGHT_H
