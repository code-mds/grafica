//
// Created by massi on 02.05.2020.
//

#include <stdexcept>
#include "light.h"

GLenum Light::LastCreated = GL_LIGHT0;

void Light::toggle() {
    _isOn = !_isOn;
    update();
}

void Light::update() const {
    if(_isOn)
        glEnable(_lightNum);
    else
        glDisable(_lightNum);

    glutPostRedisplay();
}

Light::Light() :
    Light{Vertex{1.0, 1.0, 1.0, 1.0}} //w=0.0 => luce direzionale)
{
}

Light::Light(const Vertex& pos) :
    _isOn{true},
    _lightNum{Light::LastCreated},
    _position{pos}
{
    if(Light::LastCreated == GL_LIGHT7)
        throw std::out_of_range("max_lights = 8");

    Light::LastCreated++;
}

void Light::draw() {
    glLightfv(_lightNum, GL_POSITION, &_position.x);
    glLightfv(_lightNum, GL_DIFFUSE, &_direction.x);

    drawLightSource();
}

void Light::drawLightSource() const {
    glPushMatrix();
    glTranslatef (_position.x, _position.y, _position.z);
    glDisable (GL_LIGHTING);
    glColor3f (0.0, 1.0, 1.0);
    glutWireCube (0.1);
    glEnable (GL_LIGHTING);
    glPopMatrix ();
}
