//
// Created by massi on 12.03.2020.
//

#include <glm/ext/matrix_transform.hpp>
#include "house.h"

GLfloat PI_HALF = glm::pi<float>() / 2;
GLfloat DOOR_STEP = 1 / 180.0f * glm::pi<float>();

static const GLfloat SW = 10.0f; //SCENE WIDTH

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

const float CYLINDER_RADIUS = .01f / SW;
const float CYLINDER_HEIGHT = 3.0f /SW;

const float FLAG_HEIGHT = 1.0f / SW;
const float FLAG_WIDTH = .03f / SW;

const float TRANSLATION_STEP = .05;
const float ROTATION_STEP = 1.0;

House::House(glm::mat4& modelview, GLint& modelviewPos, Texture& texture) :
    _texture{texture},
    modelview{modelview},
    modelviewPos{modelviewPos},
    // setup door
    _door{std::vector<Vertex>{
            // front face
            {{ -HALF_DOOR_WIDTH, 0, -WALL_THICK },
                    {1.0f, 1.0f, 1.0f},{0.0f, 0.0f} },       // bottom left
            {{ HALF_DOOR_WIDTH, 0, -WALL_THICK },
                    {1.0f, 1.0f, 1.0f},{1.0f, 0.0f}},       // bottom right
            {{ HALF_DOOR_WIDTH, WALL_HEIGHT, -WALL_THICK },
                    {1.0f, 1.0f, 1.0f},{1.0f, 1.0f}},       // top right
            {{ -HALF_DOOR_WIDTH, WALL_HEIGHT, -WALL_THICK },
                    {1.0f, 1.0f, 1.0f},{0.0f, 1.0f}},       // top left
            // back face
            {{ HALF_DOOR_WIDTH, 0, -(WALL_THICK+DOOR_THINK) },
                    { 1.0f, 1.0f, 1.0f},{0.0f, 0.0f}},       // bottom left
            {{ -HALF_DOOR_WIDTH, 0, -(WALL_THICK+DOOR_THINK) },
                    { 1.0f, 1.0f, 1.0f},{1.0f, 0.0f}},       // bottom right
            {{ -HALF_DOOR_WIDTH, WALL_HEIGHT, -(WALL_THICK+DOOR_THINK) },
                    { 1.0f, 1.0f, 1.0f},{1.0f, 1.0f}},       // top right
            {{ HALF_DOOR_WIDTH, WALL_HEIGHT, -(WALL_THICK+DOOR_THINK) },
                    { 1.0f, 1.0f, 1.0f},{0.0f, 1.0f}},       // top left
    }},

    _floor{std::vector<Vertex>{
            // front face
                {{HALF_BASE_WIDTH, 0, 0},
                 {1.0f, 1.0f, 1.0f},{0.0f, 0.0f} },       // bottom left
                {{HALF_BASE_WIDTH, 0, -BASE_HEIGHT},
                 {1.0f, 1.0f, 1.0f},{1.0f, 0.0f}},       // bottom right
                {{-HALF_BASE_WIDTH, 0, -BASE_HEIGHT},
                 {1.0f, 1.0f, 1.0f},{1.0f, 1.0f}},       // top right
                {{-HALF_BASE_WIDTH, 0, 0},
                 {1.0f, 1.0f, 1.0f},{0.0f, 1.0f}},       // top left
            // back face
                {{HALF_BASE_WIDTH, 0, -BASE_HEIGHT},
                 { 1.0f, 1.0f, 1.0f},{0.0f, 0.0f}},       // bottom left
                {{HALF_BASE_WIDTH, 0,  0},
                 { 1.0f, 1.0f, 1.0f},{1.0f, 0.0f}},       // bottom right
                {{-HALF_BASE_WIDTH, 0, 0},
                 { 1.0f, 1.0f, 1.0f},{1.0f, 1.0f}},       // top right
                {{-HALF_BASE_WIDTH, 0, -BASE_HEIGHT},
                        { 1.0f, 1.0f, 1.0f},{0.0f, 1.0f}},       // top left
    }},

    //left wall
    _wallLeft{std::vector<Vertex>{
            // front face
            {{ -HALF_BASE_WIDTH,  0, -BASE_HEIGHT},
                    {1.0f, 1.0f, 1.0f},{0.0f, 0.0f} },       // bottom left
            {{ -HALF_BASE_WIDTH, 0, 0 },
                    {1.0f, 1.0f, 1.0f},{1.0f, 0.0f}},       // bottom right
            { { -HALF_BASE_WIDTH,  WALL_HEIGHT, 0 },
                    {1.0f, 1.0f, 1.0f},{1.0f, 1.0f}},       // top right
            { { -HALF_BASE_WIDTH,  WALL_HEIGHT, -BASE_HEIGHT },
                    {1.0f, 1.0f, 1.0f},{0.0f, 1.0f}},       // top left
            // back face
            {{ -(HALF_BASE_WIDTH - WALL_THICK), 0, -WALL_THICK },
                    { 1.0f, 1.0f, 1.0f},{0.0f, 0.0f}},       // bottom left
            {{ -(HALF_BASE_WIDTH - WALL_THICK), 0, -(BASE_HEIGHT - WALL_THICK)},
                    { 1.0f, 1.0f, 1.0f},{1.0f, 0.0f}},       // bottom right
            { { -(HALF_BASE_WIDTH - WALL_THICK), WALL_HEIGHT, -(BASE_HEIGHT - WALL_THICK) },
                    { 1.0f, 1.0f, 1.0f},{1.0f, 1.0f}},       // top right
            {  { -(HALF_BASE_WIDTH - WALL_THICK), WALL_HEIGHT, -WALL_THICK },
                    { 1.0f, 1.0f, 1.0f},{0.0f, 1.0f}},       // top left
    }},
    //right wall
    _wallRight{std::vector<Vertex>{
            // front face
            {{ HALF_BASE_WIDTH, 0, 0},
                    {1.0f, 1.0f, 1.0f},{0.0f, 0.0f} },       // bottom left
            {{ HALF_BASE_WIDTH, 0, -BASE_HEIGHT },
                    {1.0f, 1.0f, 1.0f},{1.0f, 0.0f}},       // bottom right
            {{ HALF_BASE_WIDTH, WALL_HEIGHT, -BASE_HEIGHT },
                    {1.0f, 1.0f, 1.0f},{1.0f, 1.0f}},       // top right
            {{ HALF_BASE_WIDTH, WALL_HEIGHT, 0 },
                    {1.0f, 1.0f, 1.0f},{0.0f, 1.0f}},       // top left
            // back face
            {{ (HALF_BASE_WIDTH - WALL_THICK),  0, -(BASE_HEIGHT - WALL_THICK) },
                    { 1.0f, 1.0f, 1.0f},{0.0f, 0.0f}},       // bottom left
            {{ (HALF_BASE_WIDTH - WALL_THICK),  0, -WALL_THICK},
                    { 1.0f, 1.0f, 1.0f},{1.0f, 0.0f}},       // bottom right
            {{ (HALF_BASE_WIDTH - WALL_THICK),  WALL_HEIGHT, -WALL_THICK },
                    { 1.0f, 1.0f, 1.0f},{1.0f, 1.0f}},       // top right
            {{ (HALF_BASE_WIDTH - WALL_THICK),  WALL_HEIGHT, -(BASE_HEIGHT - WALL_THICK) },
                    { 1.0f, 1.0f, 1.0f},{0.0f, 1.0f}},       // top left
    }},

    //back wall
    _wallBack{std::vector<Vertex>{
            // front face
            {{ HALF_BASE_WIDTH, 0, -BASE_HEIGHT },
                    {1.0f, 1.0f, 1.0f},{0.0f, 0.0f} },       // bottom left
            {{ -HALF_BASE_WIDTH,  0, -BASE_HEIGHT},
                    {1.0f, 1.0f, 1.0f},{1.0f, 0.0f}},       // bottom right
            {{ -HALF_BASE_WIDTH,  WALL_HEIGHT, -BASE_HEIGHT },
                    {1.0f, 1.0f, 1.0f},{1.0f, 1.0f}},       // top right
            {{ HALF_BASE_WIDTH,  WALL_HEIGHT, -BASE_HEIGHT },
                    {1.0f, 1.0f, 1.0f},{0.0f, 1.0f}},       // top left
            // back face
            {{ -(HALF_BASE_WIDTH - WALL_THICK), 0, -(BASE_HEIGHT - WALL_THICK)},
                    { 1.0f, 1.0f, 1.0f},{0.0f, 0.0f}},       // bottom left
            { { (HALF_BASE_WIDTH - WALL_THICK),  0, -(BASE_HEIGHT - WALL_THICK) },
                    { 1.0f, 1.0f, 1.0f},{1.0f, 0.0f}},       // bottom right
            {{ (HALF_BASE_WIDTH - WALL_THICK),  WALL_HEIGHT, -(BASE_HEIGHT - WALL_THICK) },
                    { 1.0f, 1.0f, 1.0f},{1.0f, 1.0f}},       // top right
            { { -(HALF_BASE_WIDTH - WALL_THICK), WALL_HEIGHT, -(BASE_HEIGHT - WALL_THICK) },
                    { 1.0f, 1.0f, 1.0f},{0.0f, 1.0f}},       // top left
    }},

    //front left wall
    _wallFrontLeft{std::vector<Vertex>{
            // front face
            {{ -HALF_DOOR_WIDTH, 0, 0},
                    {1.0f, 1.0f, 1.0f},{0.0f, 0.0f} },       // bottom left
            {{ -HALF_BASE_WIDTH, 0, 0 },
                    {1.0f, 1.0f, 1.0f},{1.0f, 0.0f}},       // bottom right
            {{ -HALF_BASE_WIDTH, WALL_HEIGHT, 0 },
                    {1.0f, 1.0f, 1.0f},{1.0f, 1.0f}},       // top right
            { { -HALF_DOOR_WIDTH, WALL_HEIGHT, 0 },
                    {1.0f, 1.0f, 1.0f},{0.0f, 1.0f}},       // top left
            // back face
            {{ -HALF_DOOR_WIDTH,                0, -WALL_THICK },
                    { 1.0f, 1.0f, 1.0f},{0.0f, 0.0f}},       // bottom left
            {{ -(HALF_BASE_WIDTH - WALL_THICK), 0, -WALL_THICK},
                    { 1.0f, 1.0f, 1.0f},{1.0f, 0.0f}},       // bottom right
            {{ -(HALF_BASE_WIDTH - WALL_THICK), WALL_HEIGHT, -WALL_THICK },
                    { 1.0f, 1.0f, 1.0f},{1.0f, 1.0f}},       // top right
            {{ -HALF_DOOR_WIDTH,                WALL_HEIGHT, -WALL_THICK },
                    { 1.0f, 1.0f, 1.0f},{0.0f, 1.0f}},       // top left
    }},

    //front right wall
    _wallFrontRight{std::vector<Vertex>{
            // front face
            {{ HALF_DOOR_WIDTH, 0, 0 },
                    {1.0f, 1.0f, 1.0f},{0.0f, 0.0f} },       // bottom left
            {{ HALF_BASE_WIDTH, 0, 0 },
                    {1.0f, 1.0f, 1.0f},{1.0f, 0.0f}},       // bottom right
            {{ HALF_BASE_WIDTH, WALL_HEIGHT, 0 },
                    {1.0f, 1.0f, 1.0f},{1.0f, 1.0f}},       // top right
            { { HALF_DOOR_WIDTH, WALL_HEIGHT, 0 },
                    {1.0f, 1.0f, 1.0f},{0.0f, 1.0f}},       // top left
            // back face
            {{ (HALF_BASE_WIDTH - WALL_THICK),  0, -WALL_THICK },
                    { 1.0f, 1.0f, 1.0f},{0.0f, 0.0f}},       // bottom left
            {{ HALF_DOOR_WIDTH,                 0, -WALL_THICK },
                    { 1.0f, 1.0f, 1.0f},{1.0f, 0.0f}},       // bottom right
            {{ HALF_DOOR_WIDTH,                 WALL_HEIGHT, -WALL_THICK },
                    { 1.0f, 1.0f, 1.0f},{1.0f, 1.0f}},       // top right
            {{ (HALF_BASE_WIDTH - WALL_THICK),  WALL_HEIGHT, -WALL_THICK },
                    { 1.0f, 1.0f, 1.0f},{0.0f, 1.0f}},       // top left

    }}

{
    _quadric = gluNewQuadric();
}


House::~House() {
    gluDeleteQuadric(_quadric);
}

void House::draw() {
    // save origina matrix
    glm::mat4 ori{modelview};

    glTranslatef(_translationX, _translationY, _translationZ);
    glRotatef(_rotationX, 0.0f, 1.0f, 0.0f);

    drawFloor();
    drawLateralWalls();
//    drawPrismWalls();
//    drawRoof();
//    drawCylinder();
//    drawFlag();
//    drawChimney();
    drawDoor();

    // restore original matrix
    modelview = ori;
    glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &modelview[0][0]);
}

//void House::drawChimney() {
//    _texture.enableTexture(true);
//    _texture.bind(TextureEnum::WALL);
//
//    setExternalMaterial();
//    Rect rectangles[] = {
//            // LEFT SIDE
//            {
//                    {CHIM_LEFT, CHIM_BOTTOM,  CHIM_END_DEPTH},
//                    {CHIM_LEFT, CHIM_BOTTOM, CHIM_START_DEPTH},
//                    {CHIM_LEFT, CHIM_TOP,  CHIM_START_DEPTH},
//                    {CHIM_LEFT, CHIM_TOP,  CHIM_END_DEPTH},
//                    COLOR_FLOOR
//            },
//            {
//                    {CHIM_LEFT+CHIM_THICK, CHIM_BOTTOM,  CHIM_START_DEPTH},
//                    {CHIM_LEFT+CHIM_THICK, CHIM_BOTTOM, CHIM_END_DEPTH},
//                    {CHIM_LEFT+CHIM_THICK, CHIM_TOP,  CHIM_END_DEPTH},
//                    {CHIM_LEFT+CHIM_THICK, CHIM_TOP,  CHIM_START_DEPTH},
//                    COLOR_WALL_INTERNAL
//            },
//            // RIGHT SIDE
//            {
//                    {CHIM_RIGHT, CHIM_BOTTOM,  CHIM_END_DEPTH},
//                    {CHIM_RIGHT, CHIM_BOTTOM, CHIM_START_DEPTH},
//                    {CHIM_RIGHT, CHIM_TOP,  CHIM_START_DEPTH},
//                    {CHIM_RIGHT, CHIM_TOP,  CHIM_END_DEPTH},
//                    COLOR_FLOOR
//            },
//            {
//                    {CHIM_RIGHT+CHIM_THICK, CHIM_BOTTOM,  CHIM_START_DEPTH},
//                    {CHIM_RIGHT+CHIM_THICK, CHIM_BOTTOM, CHIM_END_DEPTH},
//                    {CHIM_RIGHT+CHIM_THICK, CHIM_TOP,  CHIM_END_DEPTH},
//                    {CHIM_RIGHT+CHIM_THICK, CHIM_TOP,  CHIM_START_DEPTH},
//                    COLOR_FLOOR
//            },
//            // FRONT
//            {
//                    {CHIM_RIGHT+CHIM_THICK, CHIM_BOTTOM, CHIM_START_DEPTH},
//                    {CHIM_LEFT, CHIM_BOTTOM,  CHIM_START_DEPTH},
//                    {CHIM_LEFT, CHIM_TOP,  CHIM_START_DEPTH},
//                    {CHIM_RIGHT+CHIM_THICK, CHIM_TOP,  CHIM_START_DEPTH},
//                    COLOR_FLOOR
//            },
//            {
//                    {CHIM_LEFT, CHIM_BOTTOM,  CHIM_START_DEPTH+CHIM_THICK},
//                    {CHIM_RIGHT+CHIM_THICK, CHIM_BOTTOM, CHIM_START_DEPTH+CHIM_THICK},
//                    {CHIM_RIGHT+CHIM_THICK, CHIM_TOP,  CHIM_START_DEPTH+CHIM_THICK},
//                    {CHIM_LEFT, CHIM_TOP,  CHIM_START_DEPTH+CHIM_THICK},
//                    COLOR_FLOOR
//            },
//            // BACK
//            {
//                    {CHIM_RIGHT, CHIM_BOTTOM, CHIM_END_DEPTH},
//                    {CHIM_LEFT, CHIM_BOTTOM,  CHIM_END_DEPTH},
//                    {CHIM_LEFT, CHIM_TOP,  CHIM_END_DEPTH},
//                    {CHIM_RIGHT, CHIM_TOP,  CHIM_END_DEPTH},
//                    COLOR_FLOOR
//            },
//            {
//                    {CHIM_LEFT, CHIM_BOTTOM,  CHIM_END_DEPTH+CHIM_THICK},
//                    {CHIM_RIGHT, CHIM_BOTTOM, CHIM_END_DEPTH+CHIM_THICK},
//                    {CHIM_RIGHT, CHIM_TOP,  CHIM_END_DEPTH+CHIM_THICK},
//                    {CHIM_LEFT, CHIM_TOP,  CHIM_END_DEPTH+CHIM_THICK},
//                    COLOR_WALL_INTERNAL
//            }
//
//    };
//
//    int nrOfWalls = sizeof(rectangles) / sizeof(rectangles[0]);
//    for (int i = 0; i < nrOfWalls; i=i+2) {
//        _utils.draw_parallelepiped(rectangles[i], rectangles[i + 1]);
//    }
//
//    _texture.enableTexture(false);
//}
//
void House::drawFloor() {
    // draw door
    _texture.enableTexture(true);
    _texture.bind(TextureEnum::MARBLE);
    _floor.draw();
    _texture.enableTexture(false);
}

//void House::drawRoof() {
//    _texture.enableTexture(true);
//    _texture.bind(TextureEnum::ROOF);
//
//    glMaterialfv(GL_FRONT, GL_SPECULAR, MATERIAL_RED);
//    glMaterialf(GL_FRONT, GL_SHININESS, SHININESS_HIGH);
//
//    Rect rectangles[] = {
//            // right roof wall
//            {
//                    { HALF_BASE_WIDTH + ROOF_THICK, WALL_HEIGHT, ROOF_THICK },
//                    { HALF_BASE_WIDTH + ROOF_THICK,  WALL_HEIGHT, -(BASE_HEIGHT + ROOF_THICK)},
//                    { 0, ROOF_HEIGHT + ROOF_THICK, -(BASE_HEIGHT + ROOF_THICK) },
//                    { 0, ROOF_HEIGHT + ROOF_THICK, ROOF_THICK },
//                    _colorRoofExternal
//            },{
//                    { HALF_BASE_WIDTH+ ROOF_THICK,  WALL_HEIGHT- ROOF_THICK, -(BASE_HEIGHT + ROOF_THICK)},
//                    { HALF_BASE_WIDTH+ ROOF_THICK, WALL_HEIGHT- ROOF_THICK,   ROOF_THICK },
//                    { 0,  ROOF_HEIGHT, ROOF_THICK },
//                    { 0,  ROOF_HEIGHT, -(BASE_HEIGHT + ROOF_THICK) },
//                    _colorRoofInternal
//            },
//            // left roof wall
//            {
//                    { -(HALF_BASE_WIDTH + ROOF_THICK),  WALL_HEIGHT,    -(BASE_HEIGHT + ROOF_THICK)},
//                    { -(HALF_BASE_WIDTH + ROOF_THICK), WALL_HEIGHT,      ROOF_THICK },
//                    { 0,  (ROOF_HEIGHT + ROOF_THICK), ROOF_THICK },
//                    { 0,  (ROOF_HEIGHT + ROOF_THICK), -(BASE_HEIGHT + ROOF_THICK) },
//                    _colorRoofExternal
//            },{
//                    { -(HALF_BASE_WIDTH + ROOF_THICK), WALL_HEIGHT- ROOF_THICK, ROOF_THICK },
//                    { -(HALF_BASE_WIDTH + ROOF_THICK),  WALL_HEIGHT- ROOF_THICK, -(BASE_HEIGHT + ROOF_THICK)},
//                    { 0,  ROOF_HEIGHT, -(BASE_HEIGHT + ROOF_THICK) },
//                    { 0,  ROOF_HEIGHT, ROOF_THICK },
//                    _colorRoofInternal
//            }
//    };
//
//    _utils.draw_parallelepiped(rectangles[0], rectangles[1]);
//    _utils.draw_parallelepiped(rectangles[2], rectangles[3]);
//    _texture.enableTexture(false);
//}
//
//void House::setExternalMaterial() const {
//    glMaterialfv(GL_FRONT, GL_SPECULAR, MATERIAL_WHITE);
//    glMaterialf(GL_FRONT, GL_SHININESS, SHININESS_LOW);
//}
//
//void House::drawPrismWalls() {
//    setExternalMaterial();
//    _texture.enableTexture(true);
//    _texture.bind(TextureEnum::WALL);
//    Triangle triangles[] = {
//            {
//                    { -HALF_BASE_WIDTH,  WALL_HEIGHT, 0 },
//                    { HALF_BASE_WIDTH, WALL_HEIGHT, 0 },
//                    { 0,  ROOF_HEIGHT, 0 },
//                    _colorWallExternal
//            },
//            {
//                    { HALF_BASE_WIDTH, WALL_HEIGHT, -WALL_THICK },
//                    { -HALF_BASE_WIDTH,  WALL_HEIGHT,  -WALL_THICK},
//                    { 0,  ROOF_HEIGHT, -WALL_THICK },
//                    COLOR_WALL_INTERNAL
//            },
//            {
//                    { HALF_BASE_WIDTH, WALL_HEIGHT, -(BASE_HEIGHT) },
//                    { -HALF_BASE_WIDTH,  WALL_HEIGHT, -(BASE_HEIGHT)},
//                    { 0,  ROOF_HEIGHT, -BASE_HEIGHT },
//                    _colorWallExternal
//            },
//            {
//                    { -HALF_BASE_WIDTH,  WALL_HEIGHT, -(BASE_HEIGHT - WALL_THICK)},
//                    { HALF_BASE_WIDTH, WALL_HEIGHT, -(BASE_HEIGHT - WALL_THICK) },
//                    { 0,  ROOF_HEIGHT, -(BASE_HEIGHT - WALL_THICK) },
//                    COLOR_WALL_INTERNAL
//            },
//    };
//
//    _utils.draw_prism(triangles[0], triangles[1]);
//    _utils.draw_prism(triangles[2], triangles[3]);
//    _texture.enableTexture(false);
//}
//
void House::drawLateralWalls() {

    _texture.enableTexture(true);
    _texture.bind(TextureEnum::WALL);

    _wallRight.draw();
    _wallBack.draw();
    _wallLeft.draw();
    _wallRight.draw();
    _wallFrontLeft.draw();
    _wallFrontRight.draw();

    _texture.enableTexture(false);
}

void House::drawDoor() {
    glm::mat4 ori{modelview};

    // Rotazione intorno ad uno dei vertici. Notare che l'angolo va passato in radianti. Rotazione di 1 grado
    modelview  = glm::translate(modelview, glm::vec3(-HALF_DOOR_WIDTH, 0.f, -WALL_THICK));
    modelview = glm::rotate(modelview, _doorAngle, glm::vec3(0.0f, 1.0f, 0.0f));
    modelview  = glm::translate(modelview, glm::vec3(HALF_DOOR_WIDTH, 0.f, WALL_THICK));

    // Passa la matrice di modelview allo shader
    glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &modelview[0][0]);

    // draw door
    _texture.enableTexture(true);
    _texture.bind(TextureEnum::WOOD);
    _door.draw();
    _texture.enableTexture(false);

    modelview = ori;
}

void House::toggleDoor() {
    _doorOpen = !_doorOpen;
}

void House::updateAnimation() {
    if(_rotationEnabled)
        _rotationX += ROTATION_STEP;

    if(_windAngle > _flagAngle) {
        _flagAngle++;
    } else if(_windAngle < _flagAngle) {
        _flagAngle--;
    }

    glutPostRedisplay();
}

void House::rotateDoor() {
    if(_doorOpen && _doorAngle < PI_HALF) {
        _doorAngle += DOOR_STEP;
    } else if(!_doorOpen && _doorAngle > 0) {
        _doorAngle -= DOOR_STEP;
    }
}

void House::moveNear() {
    _translationZ -= TRANSLATION_STEP;
    glutPostRedisplay();
}

void House::moveFar() {
    _translationZ += TRANSLATION_STEP;
    glutPostRedisplay();
}

void House::moveUp() {
    _translationY += TRANSLATION_STEP;
    glutPostRedisplay();
}

void House::moveDown() {
    _translationY -= TRANSLATION_STEP;
    glutPostRedisplay();
}

void House::moveRight() {
    _translationX += TRANSLATION_STEP;
    glutPostRedisplay();
}

void House::moveLeft() {
    _translationX -= TRANSLATION_STEP;
    glutPostRedisplay();
}

void House::updateRotation(bool enabled) {
    _rotationEnabled = enabled;
}

bool House::rotationEnabled() {
    return _rotationEnabled;
}

//void House::drawFlag() {
//    glMaterialfv(GL_FRONT, GL_SPECULAR, MATERIAL_BLACK);
//    glMaterialf(GL_FRONT, GL_SHININESS, SHININESS_OFF);
//
//    Triangle triangles[] = {
//            {
//                    { -FLAG_WIDTH,  0, 0 },
//                    { -FLAG_WIDTH, FLAG_HEIGHT, 0 },
//                    { -FLAG_WIDTH,  FLAG_HEIGHT/2, -FLAG_HEIGHT },
//                    COLOR_FLAG
//            },
//            {
//                    { FLAG_WIDTH, FLAG_HEIGHT, 0 },
//                    { FLAG_WIDTH, 0, 0 },
//                    { FLAG_WIDTH,  FLAG_HEIGHT/2, -FLAG_HEIGHT },
//                    COLOR_FLAG
//            }
//    };
//
//    glPushMatrix();
//    glTranslatef(0, ROOF_HEIGHT+CYLINDER_HEIGHT-FLAG_HEIGHT, 0);
//    glRotatef(_flagAngle-_rotationX, 0, 1, 0);
//    _utils.draw_prism(triangles[0], triangles[1]);
//    glPopMatrix();
//}
//
//// flag cylinder
//void House::drawCylinder() const {
//    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, MATERIAL_BLACK);
//    glMaterialfv(GL_FRONT, GL_SPECULAR, MATERIAL_BLACK);
//    glMaterialf(GL_FRONT, GL_SHININESS, SHININESS_OFF);
//
//    gluQuadricDrawStyle(_quadric, GLU_LINE);
//    gluQuadricNormals(_quadric, GLU_SMOOTH);
//
//    glPushMatrix();
//    glLineWidth(1.0f);
//    glColor3ub(15, 32, 112);
//    glTranslatef(0, ROOF_HEIGHT, 0);
//    glRotatef(-90, 1, 0, 0);
//    gluCylinder(_quadric, CYLINDER_RADIUS, CYLINDER_RADIUS, CYLINDER_HEIGHT, 32, 32);
//    glPopMatrix();
//}

void House::updateWind(GLfloat windAngle) {
    _windAngle = windAngle;
    glutPostRedisplay();
}

void House::reset() {
    _windAngle = 0.0;
    _translationX = 0.0;
    _translationY = 0.0;
    _translationZ = 0.0;
    _rotationX = 0.0;
    _flagAngle = 0.0;
    _doorAngle = 0.0;
    _doorOpen = false;
    _rotationEnabled = false;
}

void House::init() {
    _door.init();
    _floor.init();
    _wallBack.init();
    _wallLeft.init();
    _wallRight.init();
    _wallFrontLeft.init();
    _wallFrontRight.init();
}
