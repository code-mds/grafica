//
// Created by massi on 12.03.2020.
//

#ifndef GRAFICA_HOUSE_H
#define GRAFICA_HOUSE_H

#include "draw_utils.h"

class House {
public:
    explicit House(draw_utils& utils);
    ~House();
    void draw();
    void toggleDoor();
    void rotateDoor();

    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();
    void moveNear();
    void moveFar();
    void reset();

    void updateRotation(bool enabled);

    bool rotationEnabled();
    void changeColor();
    void updateWind(GLfloat windAngle);
    void updateAnimation();
    bool inBoundaries();

private:
    bool _colorStandard = true;
    color_t _colorRoofInternal;
    color_t _colorRoofExternal;
    color_t _colorWallExternal;

    bool _doorOpen = false;
    bool _rotationEnabled = false;

    GLfloat _doorAngle = 0.0;
    GLfloat _translationZ = 0.0;
    GLfloat _translationY = 0.0;
    GLfloat _translationX = 0.0;
    GLfloat _rotationX = 0.0;
    GLfloat _windAngle = 0.0;
    GLfloat _flagAngle = 0.0;

    void drawPrismWalls();
    void drawLateralWalls();
    void drawRoof();
    void drawFloor();
    void drawChimney();
    void drawDoor();
    void drawFlag();
    void drawCylinder() const;
    void setupVolume();

    GLUquadric *_quadric;
    draw_utils& _utils;
    volume_t _volume;
};


#endif //GRAFICA_HOUSE_H
