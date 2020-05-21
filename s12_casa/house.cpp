//
// Created by massi on 12.03.2020.
//

#include "house.h"

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

Color COLOR_ROOF_INTERNAL_1 = {160, 0, 0 };
Color COLOR_ROOF_INTERNAL_2 = {100, 70, 60 };

Color COLOR_ROOF_EXTERNAL_1 = {230, 0, 0 };
Color COLOR_ROOF_EXTERNAL_2 = {109, 76, 65 };

Color COLOR_WALL_EXTERNAL_1 = {238, 238, 238 };
Color COLOR_WALL_EXTERNAL_2 = {188, 170, 164 };


#define COLOR_WALL_INTERNAL     {80, 80, 80}
#define COLOR_DOOR              {141, 110, 99}
#define COLOR_FLOOR             {160, 160, 160}
#define COLOR_FLAG              {153,206,255}

House::House(draw_utils& utils, Light& light1, Light& light2, Texture& texture) :
    _utils{utils},
    _light1{light1},
    _light2{light2},
    _texture{texture},
    _colorRoofInternal{COLOR_ROOF_INTERNAL_1},
    _colorRoofExternal{COLOR_ROOF_EXTERNAL_1},
    _colorWallExternal{COLOR_WALL_EXTERNAL_1}
{
    _quadric = gluNewQuadric();
    setupVolume();
}

void House::setupVolume() {
    GLfloat x = HALF_BASE_WIDTH + ROOF_THICK;
    GLfloat y = ROOF_HEIGHT + CYLINDER_HEIGHT;
    GLfloat z = BASE_HEIGHT + ROOF_THICK;
    int i=0;
    // front vertexes
    _volume.vertexes[i++] = {-x, 0.0, ROOF_THICK };
    _volume.vertexes[i++] = {x, 0.0, ROOF_THICK };
    _volume.vertexes[i++] = {x, y, ROOF_THICK };
    _volume.vertexes[i++] = {-x, y, ROOF_THICK };
    // back vertexes
    _volume.vertexes[i++] = {-x, y, -z };
    _volume.vertexes[i++] = {x, 0.0, -z };
    _volume.vertexes[i++] = {x, y, -z };
    _volume.vertexes[i++] = {-x, y, -z };
}

House::~House() {
    gluDeleteQuadric(_quadric);
}

void House::draw() {
    if(!_light1.isRelative())
        _light1.draw();
    if(!_light2.isRelative())
        _light2.draw();

    glPushMatrix();
    glTranslatef(_translationX, _translationY, _translationZ);
    glRotatef(_rotationX, 0.0f, 1.0f, 0.0f);

    if(_light1.isRelative())
        _light1.draw();
    if(_light2.isRelative())
        _light2.draw();

    drawFloor();
    drawLateralWalls();
    drawPrismWalls();
    drawRoof();
    drawCylinder();
    drawFlag();
    drawChimney();
    drawDoor();
    glPopMatrix();
}

void House::drawChimney() {
    _texture.enableTexture(true);
    _texture.bind(TextureEnum::WALL);

    setExternalMaterial();
    Rect rectangles[] = {
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
        _utils.draw_parallelepiped(rectangles[i], rectangles[i + 1]);
    }

    _texture.enableTexture(false);
}

void House::drawFloor() {
    Rect rectangles[] = {
            // floor inside
            {
                {HALF_BASE_WIDTH, 0, 0},
                {HALF_BASE_WIDTH, 0, -BASE_HEIGHT},
                {-HALF_BASE_WIDTH, 0, -BASE_HEIGHT},
                {-HALF_BASE_WIDTH, 0, 0},
                COLOR_FLOOR
            },
            {
                // floor outside
                {HALF_BASE_WIDTH, 0, -BASE_HEIGHT},
                {HALF_BASE_WIDTH, 0,  0},
                {-HALF_BASE_WIDTH, 0, 0},
                {-HALF_BASE_WIDTH, 0, -BASE_HEIGHT},
                COLOR_FLOOR
            }
    };

    _utils.draw_parallelepiped(rectangles[0], rectangles[1]);
}

void House::drawRoof() {
    _texture.enableTexture(true);
    _texture.bind(TextureEnum::ROOF);

    glMaterialfv(GL_FRONT, GL_SPECULAR, MATERIAL_RED);
    glMaterialf(GL_FRONT, GL_SHININESS, SHININESS_HIGH);

    Rect rectangles[] = {
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
                    _colorRoofInternal
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
                    _colorRoofInternal
            }
    };

    _utils.draw_parallelepiped(rectangles[0], rectangles[1]);
    _utils.draw_parallelepiped(rectangles[2], rectangles[3]);
    _texture.enableTexture(false);
}

void House::setExternalMaterial() const {
    glMaterialfv(GL_FRONT, GL_SPECULAR, MATERIAL_WHITE);
    glMaterialf(GL_FRONT, GL_SHININESS, SHININESS_LOW);
}

void House::drawPrismWalls() {
    setExternalMaterial();
    _texture.enableTexture(true);
    _texture.bind(TextureEnum::WALL);
    Triangle triangles[] = {
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

    _utils.draw_prism(triangles[0], triangles[1]);
    _utils.draw_prism(triangles[2], triangles[3]);
    _texture.enableTexture(false);
}

void House::drawLateralWalls() {
    setExternalMaterial();
    _texture.enableTexture(true);
    _texture.bind(TextureEnum::WALL);

    Rect rectangles[] = {
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
        _utils.draw_parallelepiped(rectangles[i], rectangles[i + 1]);
    }
    _texture.enableTexture(false);
}

void House::drawDoor() {
    glPushMatrix();
    _texture.enableTexture(true);
    _texture.bind(TextureEnum::WOOD);

    glMaterialfv(GL_FRONT, GL_SPECULAR, MATERIAL_BLACK);
    glMaterialf(GL_FRONT, GL_SHININESS, SHININESS_OFF);

    glTranslatef(-HALF_DOOR_WIDTH, 0.f, -WALL_THICK);
    glRotatef(_doorAngle, 0.0, 1.0, 0.0);
    glTranslatef(HALF_DOOR_WIDTH, 0.f, WALL_THICK);
    Rect rectangles[] = {
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
        _utils.draw_parallelepiped(rectangles[i], rectangles[i + 1]);
    }
    glPopMatrix();
    _texture.enableTexture(false);
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
    if(_doorOpen && _doorAngle < 90) {
        _doorAngle++;
    } else if(!_doorOpen && _doorAngle > 0) {
        _doorAngle--;
    }
}

void House::moveNear() {
    _translationZ -= TRANSLATION_STEP;
    if(!inBoundaries())
        _translationZ += TRANSLATION_STEP;

    glutPostRedisplay();
    _utils.log("Translation Z:" + std::to_string(_translationZ));
}

void House::moveFar() {
    _translationZ += TRANSLATION_STEP;
    if(!inBoundaries())
        _translationZ -= TRANSLATION_STEP;

    glutPostRedisplay();
    _utils.log("Translation Z:" + std::to_string(_translationZ));
}

void House::moveUp() {
    _translationY += TRANSLATION_STEP;
    if(!inBoundaries())
        _translationY -= TRANSLATION_STEP;

    glutPostRedisplay();
    _utils.log("Translation Y:" + std::to_string(_translationY));
}

void House::moveDown() {
    _translationY -= TRANSLATION_STEP;
    if(!inBoundaries())
        _translationY += TRANSLATION_STEP;

    glutPostRedisplay();
    _utils.log("Translation Y:" + std::to_string(_translationY));
}

void House::moveRight() {
    _translationX += TRANSLATION_STEP;
    if(!inBoundaries())
        _translationX -= TRANSLATION_STEP;

    glutPostRedisplay();
    _utils.log("Translation X:" + std::to_string(_translationX));
}

void House::moveLeft() {
    _translationX -= TRANSLATION_STEP;
    if(!inBoundaries())
        _translationX += TRANSLATION_STEP;

    glutPostRedisplay();
    _utils.log("Translation X:" + std::to_string(_translationX));
}

void House::updateRotation(bool enabled) {
    _rotationEnabled = enabled;
}

bool House::rotationEnabled() {
    return _rotationEnabled;
}

void House::changeColor() {
    _colorStandard = !_colorStandard;
    updateColor();
    glutPostRedisplay();
}

void House::updateColor() {
    _colorRoofInternal = _colorStandard ? COLOR_ROOF_INTERNAL_1 : COLOR_ROOF_INTERNAL_2;
    _colorRoofExternal = _colorStandard ? COLOR_ROOF_EXTERNAL_1 : COLOR_ROOF_EXTERNAL_2;
    _colorWallExternal = _colorStandard ? COLOR_WALL_EXTERNAL_1 : COLOR_WALL_EXTERNAL_2;
}

void House::drawFlag() {
    glMaterialfv(GL_FRONT, GL_SPECULAR, MATERIAL_BLACK);
    glMaterialf(GL_FRONT, GL_SHININESS, SHININESS_OFF);

    Triangle triangles[] = {
            {
                    { -FLAG_WIDTH,  0, 0 },
                    { -FLAG_WIDTH, FLAG_HEIGHT, 0 },
                    { -FLAG_WIDTH,  FLAG_HEIGHT/2, -FLAG_HEIGHT },
                    COLOR_FLAG
            },
            {
                    { FLAG_WIDTH, FLAG_HEIGHT, 0 },
                    { FLAG_WIDTH, 0, 0 },
                    { FLAG_WIDTH,  FLAG_HEIGHT/2, -FLAG_HEIGHT },
                    COLOR_FLAG
            }
    };

    glPushMatrix();
    glTranslatef(0, ROOF_HEIGHT+CYLINDER_HEIGHT-FLAG_HEIGHT, 0);
    glRotatef(_flagAngle-_rotationX, 0, 1, 0);
    _utils.draw_prism(triangles[0], triangles[1]);
    glPopMatrix();
}

// flag cylinder
void House::drawCylinder() const {
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, MATERIAL_BLACK);
    glMaterialfv(GL_FRONT, GL_SPECULAR, MATERIAL_BLACK);
    glMaterialf(GL_FRONT, GL_SHININESS, SHININESS_OFF);

    gluQuadricDrawStyle(_quadric, GLU_LINE);
    gluQuadricNormals(_quadric, GLU_SMOOTH);

    glPushMatrix();
    glLineWidth(1.0f);
    glColor3ub(15, 32, 112);
    glTranslatef(0, ROOF_HEIGHT, 0);
    glRotatef(-90, 1, 0, 0);
    gluCylinder(_quadric, CYLINDER_RADIUS, CYLINDER_RADIUS, CYLINDER_HEIGHT, 32, 32);
    glPopMatrix();
}

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
    _colorStandard = true;
    updateColor();
}

bool House::inBoundaries() {
    float tempMatrix[16], projectionMatrix[16], modelviewMatrix[16];

    glGetFloatv(GL_MODELVIEW_MATRIX, tempMatrix);
    Vertex::matrixTranspose(tempMatrix, modelviewMatrix);

    glGetFloatv(GL_PROJECTION_MATRIX, tempMatrix);
    Vertex::matrixTranspose(tempMatrix, projectionMatrix);

    // verify that all the 8 vertex of the box containing the house
    // stay inside the viewing volume
    for (auto & vertex : _volume.vertexes) {
        // calculate where the volume vertex will stay when the translation is applied
        Vertex v = vertex.sum({_translationX, _translationY, _translationZ});
        // check if the new vertex is in viewing volume
        if(!v.inViewingVolume(projectionMatrix, modelviewMatrix)) {
            _utils.log("OUT of boundaries");
            return false;
        }
    }
    _utils.log("house IN boundaries");
    return true;
}