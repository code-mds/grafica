//
// Created by massi on 12.03.2020.
//

#ifndef GRAFICA_HOUSE_H
#define GRAFICA_HOUSE_H

#include <GL/glew.h>

class house {
public:
    void draw();
    void toggleDoor();
    void rotateDoor();

    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();

    void updateRotation(bool enabled);

    bool RotationEnabled();

private:
    GLboolean _doorOpen = false;
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
