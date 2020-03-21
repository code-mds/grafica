//
// Created by massi on 12.03.2020.
//

#ifndef GRAFICA_HOUSE_H
#define GRAFICA_HOUSE_H

#include <GL/glew.h>
#include "draw_utils.h"

class house {
public:
    house();
    void draw();
    void toggleDoor();
    void rotateDoor();

    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();

    void updateRotation(bool enabled);

    bool RotationEnabled();

    void changeColor();

private:
    bool _colorStandard = true;
    color_t _colorRoofExternal;
    color_t _colorWallExternal;

    bool _doorOpen = false;
    GLfloat _doorAngle = 0.0;
    GLfloat _translationY = 0.0;
    GLfloat _translationX = 0.0;
    GLfloat _rotationX = 0.0;
    bool _rotationEnabled = false;

    void drawPrismWalls();
    void drawLateralWalls();
    void drawRoof();
    void drawFloor();
    void drawChimney();
    void drawDoor();

};


#endif //GRAFICA_HOUSE_H
