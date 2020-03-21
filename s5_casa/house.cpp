//
// Created by massi on 12.03.2020.
//

#include "house.h"
#include "draw_utils.h"

const float SW = 10.0f; //SCENE WIDTH

const float DOOR_THINK = 0.5f / SW;
const float HALF_DOOR_WIDTH = 2.0f / SW;
const float HALF_BASE_WIDTH = 5.0f / SW;
const float BASE_HEIGHT = 8.0f / SW;
const float WALL_THICK = 0.5f / SW;
const float WALL_HEIGHT = 6.0f / SW;

const float ROOF_HEIGHT = 11.0f / SW;
const float ROOF_THICK = 0.5f / SW;

const float CHIM_LEFT = -3.0f / SW;
const float CHIM_RIGHT = -2.0f / SW;
const float CHIM_BOTTOM = 7.0f / SW;
const float CHIM_TOP = 11.0f / SW;
const float CHIM_START_DEPTH = -3.5f / SW;
const float CHIM_END_DEPTH = -4.5f / SW;
const float CHIM_THICK = .3f / SW;

const float TRANSLATION_STEP = .05;
const float ROTATION_STEP = 1.0;

color_t COLOR_ROOF_EXTERNAL_1 = { 230, 0, 0 };
color_t COLOR_ROOF_EXTERNAL_2 = { 109, 76, 65 };

color_t COLOR_WALL_EXTERNAL_1 = { 238, 238, 238 };
color_t COLOR_WALL_EXTERNAL_2 = { 188, 170, 164 };

#define COLOR_ROOF_INTERNAL     160, 0, 0
#define COLOR_WALL_INTERNAL     80, 80, 80

#define COLOR_DOOR              141, 110, 99
#define COLOR_FLOOR             160, 160, 160

house::house() :
    _colorRoofExternal{COLOR_ROOF_EXTERNAL_1},
    _colorWallExternal{COLOR_WALL_EXTERNAL_1}
{
}

void house::draw() {
    glRotatef(_rotationX, 0.0f, 1.0f, 0.0f);
    glTranslatef(_translationX, _translationY, 0.0f);

    glPushMatrix();
    drawFloor();
    drawLateralWalls();
    drawPrismWalls();
    drawRoof();
    drawChimney();
    drawDoor();
    glPopMatrix();
}

void house::drawChimney() {
    rectangle_t rectangles[] = {
            // LEFT SIDE
            {
                    {CHIM_LEFT, CHIM_BOTTOM,  CHIM_END_DEPTH},
                    {CHIM_LEFT, CHIM_BOTTOM, CHIM_START_DEPTH},
                    {CHIM_LEFT, CHIM_TOP,  CHIM_START_DEPTH},
                    {CHIM_LEFT, CHIM_TOP,  CHIM_END_DEPTH},
                    COLOR_FLOOR
            },
            {
                    {CHIM_LEFT+CHIM_THICK, CHIM_BOTTOM,  CHIM_START_DEPTH},
                    {CHIM_LEFT+CHIM_THICK, CHIM_BOTTOM, CHIM_END_DEPTH},
                    {CHIM_LEFT+CHIM_THICK, CHIM_TOP,  CHIM_END_DEPTH},
                    {CHIM_LEFT+CHIM_THICK, CHIM_TOP,  CHIM_START_DEPTH},
                    COLOR_WALL_INTERNAL
            },
            // RIGHT SIDE
            {
                    {CHIM_RIGHT, CHIM_BOTTOM,  CHIM_END_DEPTH},
                    {CHIM_RIGHT, CHIM_BOTTOM, CHIM_START_DEPTH},
                    {CHIM_RIGHT, CHIM_TOP,  CHIM_START_DEPTH},
                    {CHIM_RIGHT, CHIM_TOP,  CHIM_END_DEPTH},
                    COLOR_FLOOR
            },
            {
                    {CHIM_RIGHT+CHIM_THICK, CHIM_BOTTOM,  CHIM_START_DEPTH},
                    {CHIM_RIGHT+CHIM_THICK, CHIM_BOTTOM, CHIM_END_DEPTH},
                    {CHIM_RIGHT+CHIM_THICK, CHIM_TOP,  CHIM_END_DEPTH},
                    {CHIM_RIGHT+CHIM_THICK, CHIM_TOP,  CHIM_START_DEPTH},
                    COLOR_FLOOR
            },
            // FRONT
            {
                    {CHIM_RIGHT+CHIM_THICK, CHIM_BOTTOM, CHIM_START_DEPTH},
                    {CHIM_LEFT, CHIM_BOTTOM,  CHIM_START_DEPTH},
                    {CHIM_LEFT, CHIM_TOP,  CHIM_START_DEPTH},
                    {CHIM_RIGHT+CHIM_THICK, CHIM_TOP,  CHIM_START_DEPTH},
                    COLOR_FLOOR
            },
            {
                    {CHIM_LEFT, CHIM_BOTTOM,  CHIM_START_DEPTH+CHIM_THICK},
                    {CHIM_RIGHT+CHIM_THICK, CHIM_BOTTOM, CHIM_START_DEPTH+CHIM_THICK},
                    {CHIM_RIGHT+CHIM_THICK, CHIM_TOP,  CHIM_START_DEPTH+CHIM_THICK},
                    {CHIM_LEFT, CHIM_TOP,  CHIM_START_DEPTH+CHIM_THICK},
                    COLOR_FLOOR
            },
            // BACK
            {
                    {CHIM_RIGHT, CHIM_BOTTOM, CHIM_END_DEPTH},
                    {CHIM_LEFT, CHIM_BOTTOM,  CHIM_END_DEPTH},
                    {CHIM_LEFT, CHIM_TOP,  CHIM_END_DEPTH},
                    {CHIM_RIGHT, CHIM_TOP,  CHIM_END_DEPTH},
                    COLOR_FLOOR
            },
            {
                    {CHIM_LEFT, CHIM_BOTTOM,  CHIM_END_DEPTH+CHIM_THICK},
                    {CHIM_RIGHT, CHIM_BOTTOM, CHIM_END_DEPTH+CHIM_THICK},
                    {CHIM_RIGHT, CHIM_TOP,  CHIM_END_DEPTH+CHIM_THICK},
                    {CHIM_LEFT, CHIM_TOP,  CHIM_END_DEPTH+CHIM_THICK},
                    COLOR_WALL_INTERNAL
            }

    };

    int nrOfWalls = sizeof(rectangles) / sizeof(rectangles[0]);
    for (int i = 0; i < nrOfWalls; i=i+2) {
        draw_parallelepiped(rectangles[i], rectangles[i + 1]);
    }
}

void house::drawFloor() {
    rectangle_t rect = {
            // floor
            {HALF_BASE_WIDTH, 0,  0},
            {HALF_BASE_WIDTH, 0, -BASE_HEIGHT},
            {-HALF_BASE_WIDTH, 0, -BASE_HEIGHT},
            {-HALF_BASE_WIDTH, 0, 0},
            COLOR_FLOOR
    };

    draw_rectangle3D(rect);
}

void house::drawRoof() {
    rectangle_t rectangles[] = {
            // right roof wall
            {
                    { HALF_BASE_WIDTH + ROOF_THICK, WALL_HEIGHT, ROOF_THICK },
                    { HALF_BASE_WIDTH + ROOF_THICK,  WALL_HEIGHT, -(BASE_HEIGHT + ROOF_THICK)},
                    { 0, ROOF_HEIGHT + ROOF_THICK, -(BASE_HEIGHT + ROOF_THICK) },
                    { 0, ROOF_HEIGHT + ROOF_THICK, ROOF_THICK },
                    _colorRoofExternal
            },{
                    { HALF_BASE_WIDTH+ ROOF_THICK,  WALL_HEIGHT- ROOF_THICK, -(BASE_HEIGHT + ROOF_THICK)},
                    { HALF_BASE_WIDTH+ ROOF_THICK, WALL_HEIGHT- ROOF_THICK,   ROOF_THICK },
                    { 0,  ROOF_HEIGHT, ROOF_THICK },
                    { 0,  ROOF_HEIGHT, -(BASE_HEIGHT + ROOF_THICK) },
                    COLOR_ROOF_INTERNAL
            },
            // left roof wall
            {
                    { -(HALF_BASE_WIDTH + ROOF_THICK),  WALL_HEIGHT,    -(BASE_HEIGHT + ROOF_THICK)},
                    { -(HALF_BASE_WIDTH + ROOF_THICK), WALL_HEIGHT,      ROOF_THICK },
                    { 0,  (ROOF_HEIGHT + ROOF_THICK), ROOF_THICK },
                    { 0,  (ROOF_HEIGHT + ROOF_THICK), -(BASE_HEIGHT + ROOF_THICK) },
                    _colorRoofExternal
            },{
                    { -(HALF_BASE_WIDTH + ROOF_THICK), WALL_HEIGHT- ROOF_THICK, ROOF_THICK },
                    { -(HALF_BASE_WIDTH + ROOF_THICK),  WALL_HEIGHT- ROOF_THICK, -(BASE_HEIGHT + ROOF_THICK)},
                    { 0,  ROOF_HEIGHT, -(BASE_HEIGHT + ROOF_THICK) },
                    { 0,  ROOF_HEIGHT, ROOF_THICK },
                    COLOR_ROOF_INTERNAL
            }
    };

    draw_parallelepiped(rectangles[0], rectangles[1]);
    draw_parallelepiped(rectangles[2], rectangles[3]);
}

void house::drawPrismWalls() {
    triangle_t triangles[] = {
            {
                    { -HALF_BASE_WIDTH,  WALL_HEIGHT, 0 },
                    { HALF_BASE_WIDTH, WALL_HEIGHT, 0 },
                    { 0,  ROOF_HEIGHT, 0 },
                    _colorWallExternal
            },
            {
                    { HALF_BASE_WIDTH, WALL_HEIGHT, -WALL_THICK },
                    { -HALF_BASE_WIDTH,  WALL_HEIGHT,  -WALL_THICK},
                    { 0,  ROOF_HEIGHT, -WALL_THICK },
                    COLOR_WALL_INTERNAL
            },
            {
                    { HALF_BASE_WIDTH, WALL_HEIGHT, -(BASE_HEIGHT) },
                    { -HALF_BASE_WIDTH,  WALL_HEIGHT, -(BASE_HEIGHT)},
                    { 0,  ROOF_HEIGHT, -BASE_HEIGHT },
                    _colorWallExternal
            },
            {
                    { -HALF_BASE_WIDTH,  WALL_HEIGHT, -(BASE_HEIGHT - WALL_THICK)},
                    { HALF_BASE_WIDTH, WALL_HEIGHT, -(BASE_HEIGHT - WALL_THICK) },
                    { 0,  ROOF_HEIGHT, -(BASE_HEIGHT - WALL_THICK) },
                    COLOR_WALL_INTERNAL
            },
    };

    draw_prism(triangles[0], triangles[1]);
    draw_prism(triangles[2], triangles[3]);
}

void house::drawLateralWalls() {

    rectangle_t rectangles[] = {
            // front walls
            {
                    { HALF_DOOR_WIDTH, 0, 0 },
                    { HALF_BASE_WIDTH, 0, 0 },
                    { HALF_BASE_WIDTH, WALL_HEIGHT, 0 },
                    { HALF_DOOR_WIDTH, WALL_HEIGHT, 0 },
                    _colorWallExternal
            },
            {
                    { (HALF_BASE_WIDTH - WALL_THICK),  0, -WALL_THICK },
                    { HALF_DOOR_WIDTH,                 0, -WALL_THICK },
                    { HALF_DOOR_WIDTH,                 WALL_HEIGHT, -WALL_THICK },
                    { (HALF_BASE_WIDTH - WALL_THICK),  WALL_HEIGHT, -WALL_THICK },
                    COLOR_WALL_INTERNAL
            },
            {
                    { -HALF_BASE_WIDTH, 0, 0},
                    { -HALF_DOOR_WIDTH, 0, 0 },
                    { -HALF_DOOR_WIDTH, WALL_HEIGHT, 0 },
                    { -HALF_BASE_WIDTH, WALL_HEIGHT, 0 },
                    _colorWallExternal
            },
            {
                    { -HALF_DOOR_WIDTH,                0, -WALL_THICK },
                    { -(HALF_BASE_WIDTH - WALL_THICK), 0, -WALL_THICK},
                    { -(HALF_BASE_WIDTH - WALL_THICK), WALL_HEIGHT, -WALL_THICK },
                    { -HALF_DOOR_WIDTH,                WALL_HEIGHT, -WALL_THICK },
                    COLOR_WALL_INTERNAL
            },
            //right wall
            {
                    { HALF_BASE_WIDTH, 0, 0},
                    { HALF_BASE_WIDTH, 0, -BASE_HEIGHT },
                    { HALF_BASE_WIDTH, WALL_HEIGHT, -BASE_HEIGHT },
                    { HALF_BASE_WIDTH, WALL_HEIGHT, 0 },
                    _colorWallExternal
            },
            {
                    { (HALF_BASE_WIDTH - WALL_THICK),  0, -(BASE_HEIGHT - WALL_THICK) },
                    { (HALF_BASE_WIDTH - WALL_THICK),  0, -WALL_THICK},
                    { (HALF_BASE_WIDTH - WALL_THICK),  WALL_HEIGHT, -WALL_THICK },
                    { (HALF_BASE_WIDTH - WALL_THICK),  WALL_HEIGHT, -(BASE_HEIGHT - WALL_THICK) },
                    COLOR_WALL_INTERNAL
            },
            // back wall
            {
                    { HALF_BASE_WIDTH, 0, -BASE_HEIGHT },
                    { -HALF_BASE_WIDTH,  0, -BASE_HEIGHT},
                    { -HALF_BASE_WIDTH,  WALL_HEIGHT, -BASE_HEIGHT },
                    { HALF_BASE_WIDTH,  WALL_HEIGHT, -BASE_HEIGHT },
                    _colorWallExternal
            },
            {
                    { -(HALF_BASE_WIDTH - WALL_THICK), 0, -(BASE_HEIGHT - WALL_THICK)},
                    { (HALF_BASE_WIDTH - WALL_THICK),  0, -(BASE_HEIGHT - WALL_THICK) },
                    { (HALF_BASE_WIDTH - WALL_THICK),  WALL_HEIGHT, -(BASE_HEIGHT - WALL_THICK) },
                    { -(HALF_BASE_WIDTH - WALL_THICK), WALL_HEIGHT, -(BASE_HEIGHT - WALL_THICK) },
                    COLOR_WALL_INTERNAL
            },
            //left wall
            {
                    { -HALF_BASE_WIDTH,  0, -BASE_HEIGHT},
                    { -HALF_BASE_WIDTH, 0, 0 },
                    { -HALF_BASE_WIDTH,  WALL_HEIGHT, 0 },
                    { -HALF_BASE_WIDTH,  WALL_HEIGHT, -BASE_HEIGHT },
                    _colorWallExternal
            },
            {
                    { -(HALF_BASE_WIDTH - WALL_THICK), 0, -WALL_THICK },
                    { -(HALF_BASE_WIDTH - WALL_THICK), 0, -(BASE_HEIGHT - WALL_THICK)},
                    { -(HALF_BASE_WIDTH - WALL_THICK), WALL_HEIGHT, -(BASE_HEIGHT - WALL_THICK) },
                    { -(HALF_BASE_WIDTH - WALL_THICK), WALL_HEIGHT, -WALL_THICK },
                    COLOR_WALL_INTERNAL
            },
    };
    int nrOfWalls = sizeof(rectangles) / sizeof(rectangles[0]);
    for (int i = 0; i < nrOfWalls; i=i+2) {
        draw_parallelepiped(rectangles[i], rectangles[i + 1]);
    }

}

void house::drawDoor() {
    glPushMatrix();
    glTranslated(-HALF_DOOR_WIDTH, 0.f, -WALL_THICK);
    glRotatef(_doorAngle, 0.0, 1.0, 0.0);
    glTranslated(HALF_DOOR_WIDTH, 0.f, WALL_THICK);
    rectangle_t rectangles[] = {
            // front walls
            {
                    { -HALF_DOOR_WIDTH, 0, -WALL_THICK },
                    { HALF_DOOR_WIDTH, 0, -WALL_THICK },
                    { HALF_DOOR_WIDTH, WALL_HEIGHT, -WALL_THICK },
                    { -HALF_DOOR_WIDTH, WALL_HEIGHT, -WALL_THICK },
                    COLOR_DOOR
            },
            {
                    { HALF_DOOR_WIDTH, 0, -(WALL_THICK+DOOR_THINK) },
                    { -HALF_DOOR_WIDTH, 0, -(WALL_THICK+DOOR_THINK) },
                    { -HALF_DOOR_WIDTH, WALL_HEIGHT, -(WALL_THICK+DOOR_THINK) },
                    { HALF_DOOR_WIDTH, WALL_HEIGHT, -(WALL_THICK+DOOR_THINK) },
                    COLOR_DOOR
            },
    };
    int nrOfWalls = sizeof(rectangles) / sizeof(rectangles[0]);
    for (int i = 0; i < nrOfWalls; i=i+2) {
        draw_parallelepiped(rectangles[i], rectangles[i + 1]);
    }
    glPopMatrix();
}

void house::toggleDoor() {
    _doorOpen = !_doorOpen;
}

void house::rotateDoor() {
    if(_doorOpen && _doorAngle < 90) {
        _doorAngle++;
    } else if(!_doorOpen && _doorAngle > 0) {
        _doorAngle--;
    }
    glutPostRedisplay();
}

void house::moveUp() {
    _translationY += TRANSLATION_STEP;
    glutPostRedisplay();
}

void house::moveDown() {
    _translationY -= TRANSLATION_STEP;
    glutPostRedisplay();
}

void house::moveRight() {
    _translationX += TRANSLATION_STEP;
    glutPostRedisplay();
}

void house::moveLeft() {
    _translationX -= TRANSLATION_STEP;
    glutPostRedisplay();
}

void house::updateRotation(bool enabled) {
    _rotationEnabled = enabled;
    _rotationX += ROTATION_STEP;
    glutPostRedisplay();
}

bool house::RotationEnabled() {
    return _rotationEnabled;
}

void house::changeColor() {
    _colorStandard = !_colorStandard;
    _colorRoofExternal = _colorStandard ? COLOR_ROOF_EXTERNAL_1 : COLOR_ROOF_EXTERNAL_2;
    _colorWallExternal  = _colorStandard ? COLOR_WALL_EXTERNAL_1 : COLOR_WALL_EXTERNAL_2;
    glutPostRedisplay();
}
