//
// Created by massi on 02.05.2020.
//

#include <stdexcept>
#include "light.h"

static const GLenum LIGHTS[] = { GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3, GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7 };

int Light::LastCreated = 0;

void Light::toggle() {
    _isOn = !_isOn;
    glutPostRedisplay();
}

Light::Light() :
    Light{Vertex{1.0, 1.0, 1.0, 1.0}, Vertex{1,0,0}} //w=0.0 => luce direzionale)
{
}

// The light source can be a POSITIONAL (w > 0) or DIRECTIONAL (w = 0) light source depending on the w value.
// A POSITIONAL light source is positioned at the location (x, y, z).
// The source emits light from that particular location towards all directions. It is used to simulate lamp, bulb ...
// A DIRECTIONAL one haven't got any location. The source emits light from an infinite location, the ray are all parallel and have the direction (x, y, z).
// A directional is not subject to attenuation since it is at an infinite distance. It is used to simulate the sun for example.
Light::Light(const Vertex& pos, const Vertex& dir) :
    _isOn{true},
    _lightNum{LastCreated},
    _position{pos},
    _direction{dir}
{
    if(LastCreated == 8)
        throw std::out_of_range("max number of lights is 8");

    LastCreated++;
}

void Light::draw() {
    if(!_isOn) {
        glDisable(LIGHTS[_lightNum]);
    } else {
        glEnable(LIGHTS[_lightNum]);
        glLightfv(LIGHTS[_lightNum], GL_POSITION, &_position.x);
        drawSpot();
        drawLightSource();
    }
}

void Light::drawLightSource() const {
    glPushMatrix();
    glTranslatef (_position.x, _position.y, _position.z);
    glDisable (GL_LIGHTING);
    glColor3f (1.0, 1.0, 0.0);
    glutWireCube (0.03);
    glEnable (GL_LIGHTING);
    glPopMatrix ();
}


void Light::drawSpot() {
    // For each lights, we defines their ambient, diffuse and specular color
    glLightfv(LIGHTS[_lightNum], GL_AMBIENT, MATERIAL_BLACK);
    glLightfv(LIGHTS[_lightNum], GL_DIFFUSE, MATERIAL_WHITE);
    glLightfv(LIGHTS[_lightNum], GL_SPECULAR, MATERIAL_WHITE);

    // In OpenGl, we also can defines the light attenuation with the distance.
    // OpenGl calculates an attenuation factor (between 0 and 1) that is multiplied to the ambient, diffuse and specular color.
    // By default, they are no attenuation (attenuation factor is 1) so you have to defines your own attenuation.
    glLightf(LIGHTS[_lightNum], GL_CONSTANT_ATTENUATION, 1.0);
    glLightf(LIGHTS[_lightNum], GL_LINEAR_ATTENUATION, 0.2);
    glLightf(LIGHTS[_lightNum], GL_QUADRATIC_ATTENUATION, 0.08);

    // We have seen that positional source emits light in all the direction.
    // But, we can creates a spot that emits lights into an emission cone by restricting the emission area of the light source.
    glLightf(LIGHTS[_lightNum], GL_SPOT_CUTOFF, 30.0);
    glLightf(LIGHTS[_lightNum], GL_SPOT_EXPONENT, 2.0);
    glLightfv(LIGHTS[_lightNum], GL_SPOT_DIRECTION, &_direction.x);
}

void Light::globalAmbient() {
    // set the global ambient color a bit darker
    // so that we can see spot lights
    GLfloat ambientLight[] = {0.6f, 0.6f, 0.6f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
}

GLboolean Light::isColorMaterialOn() {
    GLboolean isColorMaterial;
    glGetBooleanv(GL_COLOR_MATERIAL, &isColorMaterial);
    return isColorMaterial;
}
