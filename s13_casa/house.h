//
// Created by massi on 12.03.2020.
//

#ifndef GRAFICA_HOUSE_H
#define GRAFICA_HOUSE_H

#include <vector>
#include "Texture.h"
#include "solid.h"

class House {
public:
    explicit House(glm::mat4& modelview, GLint& modelviewPos, Texture& texture);
    ~House();

    void init();
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
    void drawPrismWalls();
    void drawLateralWalls();
    void drawRoof();
    void drawFloor();
    void drawChimney();
    void drawDoor();
    void drawFlag();
    void drawCylinder() const;

private:
    bool _doorOpen = false;
    bool _rotationEnabled = false;

    GLfloat _doorAngle = 0.0;
    GLfloat _translationZ = 0.0;
    GLfloat _translationY = 0.0;
    GLfloat _translationX = 0.0;
    GLfloat _rotationX = 0.0;
    GLfloat _windAngle = 0.0;
    GLfloat _flagAngle = 0.0;

    GLUquadric *_quadric;
    Texture& _texture;
    glm::mat4& modelview;
    GLint& modelviewPos;

    Box _floor;
    Box _door;

    Box _wallRight;
    Box _wallBack;
    Box _wallLeft;
    Box _wallFrontLeft;
    Box _wallFrontRight;

    Box _chimRight;
    Box _chimLeft;
    Box _chimBack;
    Box _chimFront;

    Box _roofRight;
    Box _roofLeft;

    Prism _triangleFront;
    Prism _triangleBack;

    void setExternalMaterial() const;
};


#endif //GRAFICA_HOUSE_H
