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
    explicit Light(const Vertex& pos, const Vertex& dir);
    void toggle();
    void draw();

    static void ambient();

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
