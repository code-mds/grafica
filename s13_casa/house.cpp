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
const float ROTATION_STEP = 1 / 180.0f * glm::pi<float>();

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
    }},

//front right wall
    _roofRight{std::vector<Vertex>{
            // front face
            {{ HALF_BASE_WIDTH + ROOF_THICK, WALL_HEIGHT, ROOF_THICK },
                    {1.0f, 1.0f, 1.0f},{0.0f, 0.0f} },       // bottom left
            { { HALF_BASE_WIDTH + ROOF_THICK,  WALL_HEIGHT, -(BASE_HEIGHT + ROOF_THICK)},
                    {1.0f, 1.0f, 1.0f},{1.0f, 0.0f}},       // bottom right
            {{ 0, ROOF_HEIGHT + ROOF_THICK, -(BASE_HEIGHT + ROOF_THICK) },
                    {1.0f, 1.0f, 1.0f},{1.0f, 1.0f}},       // top right
            {{ 0, ROOF_HEIGHT + ROOF_THICK, ROOF_THICK },
                    {1.0f, 1.0f, 1.0f},{0.0f, 1.0f}},       // top left
            // back face
            {{ HALF_BASE_WIDTH+ ROOF_THICK,  WALL_HEIGHT- ROOF_THICK, -(BASE_HEIGHT + ROOF_THICK)},
                    { 1.0f, 1.0f, 1.0f},{0.0f, 0.0f}},       // bottom left
            {{ HALF_BASE_WIDTH+ ROOF_THICK, WALL_HEIGHT- ROOF_THICK,   ROOF_THICK },
                    { 1.0f, 1.0f, 1.0f},{1.0f, 0.0f}},       // bottom right
            {{ 0,  ROOF_HEIGHT, ROOF_THICK },
                    { 1.0f, 1.0f, 1.0f},{1.0f, 1.0f}},       // top right
            {{ 0,  ROOF_HEIGHT, -(BASE_HEIGHT + ROOF_THICK) },
                    { 1.0f, 1.0f, 1.0f},{0.0f, 1.0f}},       // top left
    }},

//front right wall
    _roofLeft{std::vector<Vertex>{
            // front face
            {{ -(HALF_BASE_WIDTH + ROOF_THICK),  WALL_HEIGHT,    -(BASE_HEIGHT + ROOF_THICK)},
                    {1.0f, 1.0f, 1.0f},{0.0f, 0.0f} },       // bottom left
            { { -(HALF_BASE_WIDTH + ROOF_THICK), WALL_HEIGHT,      ROOF_THICK },
                    {1.0f, 1.0f, 1.0f},{1.0f, 0.0f}},       // bottom right
            {{ 0,  (ROOF_HEIGHT + ROOF_THICK), ROOF_THICK },
                    {1.0f, 1.0f, 1.0f},{1.0f, 1.0f}},       // top right
            { { 0,  (ROOF_HEIGHT + ROOF_THICK), -(BASE_HEIGHT + ROOF_THICK) },
                    {1.0f, 1.0f, 1.0f},{0.0f, 1.0f}},       // top left
            // back face
            {{ -(HALF_BASE_WIDTH + ROOF_THICK), WALL_HEIGHT- ROOF_THICK, ROOF_THICK },
                    { 1.0f, 1.0f, 1.0f},{0.0f, 0.0f}},       // bottom left
            {{ -(HALF_BASE_WIDTH + ROOF_THICK),  WALL_HEIGHT- ROOF_THICK, -(BASE_HEIGHT + ROOF_THICK)},
                    { 1.0f, 1.0f, 1.0f},{1.0f, 0.0f}},       // bottom right
            { { 0,  ROOF_HEIGHT, -(BASE_HEIGHT + ROOF_THICK) },
                    { 1.0f, 1.0f, 1.0f},{1.0f, 1.0f}},       // top right
            {{ 0,  ROOF_HEIGHT, ROOF_THICK },
                    { 1.0f, 1.0f, 1.0f},{0.0f, 1.0f}},       // top left
    }},

    //front triangle
    _triangleFront{std::vector<Vertex>{
        // front face
            {{ -HALF_BASE_WIDTH,  WALL_HEIGHT, 0 },
                    {1.0f, 1.0f, 1.0f},{0.0f, 0.0f} },       // bottom left
            {{ HALF_BASE_WIDTH, WALL_HEIGHT, 0 },
                    {1.0f, 1.0f, 1.0f},{1.0f, 0.0f}},       // bottom right
            {{ 0,  ROOF_HEIGHT, 0 },
                    {1.0f, 1.0f, 1.0f},{0.5f, 1.0f}},       // top right
            // back face
            {{ HALF_BASE_WIDTH, WALL_HEIGHT, -WALL_THICK },
                    { 1.0f, 1.0f, 1.0f},{0.0f, 0.0f}},       // bottom left
            { { -HALF_BASE_WIDTH,  WALL_HEIGHT,  -WALL_THICK},
                    { 1.0f, 1.0f, 1.0f},{1.0f, 0.0f}},       // bottom right
            {  { 0,  ROOF_HEIGHT, -WALL_THICK },
                    { 1.0f, 1.0f, 1.0f},{0.5f, 1.0f}},       // top right
    }},
    //back triangle
    _triangleBack{std::vector<Vertex>{
            // front face
            {{ HALF_BASE_WIDTH, WALL_HEIGHT, -(BASE_HEIGHT) },
                    {1.0f, 1.0f, 1.0f},{0.0f, 0.0f} },       // bottom left
            {  { -HALF_BASE_WIDTH,  WALL_HEIGHT, -(BASE_HEIGHT)},
                    {1.0f, 1.0f, 1.0f},{1.0f, 0.0f}},       // bottom right
            {{ 0,  ROOF_HEIGHT, -BASE_HEIGHT },
                    {1.0f, 1.0f, 1.0f},{0.5f, 1.0f}},       // top right
            // back face
            {{ -HALF_BASE_WIDTH,  WALL_HEIGHT, -(BASE_HEIGHT - WALL_THICK)},
                    { 1.0f, 1.0f, 1.0f},{0.0f, 0.0f}},       // bottom left
            {{ HALF_BASE_WIDTH, WALL_HEIGHT, -(BASE_HEIGHT - WALL_THICK) },
                    { 1.0f, 1.0f, 1.0f},{1.0f, 0.0f}},       // bottom right
            { { 0,  ROOF_HEIGHT, -(BASE_HEIGHT - WALL_THICK) },
                    { 1.0f, 1.0f, 1.0f},{0.5f, 1.0f}},       // top right
    }},

    //chimney
    _chimLeft{std::vector<Vertex>{
            // front face
            {{CHIM_LEFT, CHIM_BOTTOM,  CHIM_END_DEPTH},
                    {1.0f, 1.0f, 1.0f},{0.0f, 0.0f} },       // bottom left
            {{CHIM_LEFT, CHIM_BOTTOM, CHIM_START_DEPTH},
                    {1.0f, 1.0f, 1.0f},{1.0f, 0.0f}},       // bottom right
            { {CHIM_LEFT, CHIM_TOP,  CHIM_START_DEPTH},
                    {1.0f, 1.0f, 1.0f},{1.0f, 1.0f}},       // top right
            { {CHIM_LEFT, CHIM_TOP,  CHIM_END_DEPTH},
                    {1.0f, 1.0f, 1.0f},{0.0f, 1.0f}},       // top right
            // back face
            {{CHIM_LEFT+CHIM_THICK, CHIM_BOTTOM,  CHIM_START_DEPTH},
                    { 1.0f, 1.0f, 1.0f},{0.0f, 0.0f}},       // bottom left
            {{CHIM_LEFT+CHIM_THICK, CHIM_BOTTOM, CHIM_END_DEPTH},
                    { 1.0f, 1.0f, 1.0f},{1.0f, 0.0f}},       // bottom right
            {{CHIM_LEFT+CHIM_THICK, CHIM_TOP,  CHIM_END_DEPTH},
                    { 1.0f, 1.0f, 1.0f},{1.0f, 1.0f}},       // top right
            {{CHIM_LEFT+CHIM_THICK, CHIM_TOP,  CHIM_START_DEPTH},
                    { 1.0f, 1.0f, 1.0f},{0.0f, 1.0f}},       // top right
    }},

    _chimRight{std::vector<Vertex>{
            // front face
            {{CHIM_RIGHT, CHIM_BOTTOM,  CHIM_END_DEPTH},
                    {1.0f, 1.0f, 1.0f},{0.0f, 0.0f} },       // bottom left
            {{CHIM_RIGHT, CHIM_BOTTOM, CHIM_START_DEPTH},
                    {1.0f, 1.0f, 1.0f},{1.0f, 0.0f}},       // bottom right
            {{CHIM_RIGHT, CHIM_TOP,  CHIM_START_DEPTH},
                    {1.0f, 1.0f, 1.0f},{1.0f, 1.0f}},       // top right
            {{CHIM_RIGHT, CHIM_TOP,  CHIM_END_DEPTH},
                    {1.0f, 1.0f, 1.0f},{0.0f, 1.0f}},       // top right
            // back face
            {{CHIM_RIGHT+CHIM_THICK, CHIM_BOTTOM,  CHIM_START_DEPTH},
                    { 1.0f, 1.0f, 1.0f},{0.0f, 0.0f}},       // bottom left
            {{CHIM_RIGHT+CHIM_THICK, CHIM_BOTTOM, CHIM_END_DEPTH},
                    { 1.0f, 1.0f, 1.0f},{1.0f, 0.0f}},       // bottom right
            {{CHIM_RIGHT+CHIM_THICK, CHIM_TOP,  CHIM_END_DEPTH},
                    { 1.0f, 1.0f, 1.0f},{1.0f, 1.0f}},       // top right
            {{CHIM_RIGHT+CHIM_THICK, CHIM_TOP,  CHIM_START_DEPTH},
                    { 1.0f, 1.0f, 1.0f},{0.0f, 1.0f}},       // top right
    }},

    _chimFront{std::vector<Vertex>{
            // front face
            {{CHIM_RIGHT+CHIM_THICK, CHIM_BOTTOM, CHIM_START_DEPTH},
                    {1.0f, 1.0f, 1.0f},{0.0f, 0.0f} },       // bottom left
            {{CHIM_LEFT, CHIM_BOTTOM,  CHIM_START_DEPTH},
                    {1.0f, 1.0f, 1.0f},{1.0f, 0.0f}},       // bottom right
            {{CHIM_LEFT, CHIM_TOP,  CHIM_START_DEPTH},
                    {1.0f, 1.0f, 1.0f},{1.0f, 1.0f}},       // top right
            {{CHIM_RIGHT+CHIM_THICK, CHIM_TOP,  CHIM_START_DEPTH},
                    {1.0f, 1.0f, 1.0f},{0.0f, 1.0f}},       // top right
            // back face
            {{CHIM_LEFT, CHIM_BOTTOM,  CHIM_START_DEPTH+CHIM_THICK},
                    { 1.0f, 1.0f, 1.0f},{0.0f, 0.0f}},       // bottom left
            {{CHIM_RIGHT+CHIM_THICK, CHIM_BOTTOM, CHIM_START_DEPTH+CHIM_THICK},
                    { 1.0f, 1.0f, 1.0f},{1.0f, 0.0f}},       // bottom right
            {{CHIM_RIGHT+CHIM_THICK, CHIM_TOP,  CHIM_START_DEPTH+CHIM_THICK},
                    { 1.0f, 1.0f, 1.0f},{1.0f, 1.0f}},       // top right
            {{CHIM_LEFT, CHIM_TOP,  CHIM_START_DEPTH+CHIM_THICK},
                    { 1.0f, 1.0f, 1.0f},{0.0f, 1.0f}},       // top right
    }},

    _chimBack{std::vector<Vertex>{
            // front face
            {{CHIM_RIGHT, CHIM_BOTTOM, CHIM_END_DEPTH},
                    {1.0f, 1.0f, 1.0f},{0.0f, 0.0f} },       // bottom left
            {{CHIM_LEFT, CHIM_BOTTOM,  CHIM_END_DEPTH},
                    {1.0f, 1.0f, 1.0f},{1.0f, 0.0f}},       // bottom right
            {{CHIM_LEFT, CHIM_TOP,  CHIM_END_DEPTH},
                    {1.0f, 1.0f, 1.0f},{1.0f, 1.0f}},       // top right
            {{CHIM_RIGHT, CHIM_TOP,  CHIM_END_DEPTH},
                    {1.0f, 1.0f, 1.0f},{0.0f, 1.0f}},       // top right
            // back face
            {{CHIM_LEFT, CHIM_BOTTOM,  CHIM_END_DEPTH+CHIM_THICK},
                    { 1.0f, 1.0f, 1.0f},{0.0f, 0.0f}},       // bottom left
            {{CHIM_RIGHT, CHIM_BOTTOM, CHIM_END_DEPTH+CHIM_THICK},
                    { 1.0f, 1.0f, 1.0f},{1.0f, 0.0f}},       // bottom right
            {{CHIM_RIGHT, CHIM_TOP,  CHIM_END_DEPTH+CHIM_THICK},
                    { 1.0f, 1.0f, 1.0f},{1.0f, 1.0f}},       // top right
            { {CHIM_LEFT, CHIM_TOP,  CHIM_END_DEPTH+CHIM_THICK},
                    { 1.0f, 1.0f, 1.0f},{0.0f, 1.0f}},       // top right
    }},

//back triangle
    _flag{std::vector<Vertex>{
            // front face
            {{ -FLAG_WIDTH,  0, 0 },
                    {1.0f, 1.0f, 1.0f},{0.0f, 0.0f} },       // bottom left
            {{ -FLAG_WIDTH, FLAG_HEIGHT, 0 },
                    {1.0f, 1.0f, 1.0f},{1.0f, 0.0f}},       // bottom right
            {{ -FLAG_WIDTH,  FLAG_HEIGHT/2, -FLAG_HEIGHT },
                    {1.0f, 1.0f, 1.0f},{0.5f, 1.0f}},       // top right
            // back face
            {{ FLAG_WIDTH, FLAG_HEIGHT, 0 },
                    { 1.0f, 1.0f, 1.0f},{0.0f, 0.0f}},       // bottom left
            {{ FLAG_WIDTH, 0, 0 },
                    { 1.0f, 1.0f, 1.0f},{1.0f, 0.0f}},       // bottom right
            {{ FLAG_WIDTH,  FLAG_HEIGHT/2, -FLAG_HEIGHT },
                    { 1.0f, 1.0f, 1.0f},{0.5f, 1.0f}},       // top right
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

    modelview  = glm::translate(modelview, glm::vec3(-_translationX, _translationY, _translationZ));
    modelview = glm::rotate(modelview, _rotationX, glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &modelview[0][0]);

    drawFloor();
    drawLateralWalls();
    drawRoof();
    drawCylinder();
    drawFlag();
    drawChimney();
    drawDoor();

    // restore original matrix
    modelview = ori;
    glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &modelview[0][0]);
}

void House::drawChimney() {
    _texture.enableTexture(true);
    _texture.bind(TextureEnum::WALL);
    _chimRight.draw();
    _chimLeft.draw();
    _chimBack.draw();
    _chimFront.draw();
    _texture.enableTexture(false);
}

void House::drawFloor() {
    // draw door
    _texture.enableTexture(true);
    _texture.bind(TextureEnum::MARBLE);
    _floor.draw();
    _texture.enableTexture(false);
}

void House::drawRoof() {
    _texture.enableTexture(true);
    _texture.bind(TextureEnum::ROOF);
    _roofLeft.draw();
    _roofRight.draw();
    _texture.enableTexture(false);
}

void House::drawLateralWalls() {
    _texture.enableTexture(true);
    _texture.bind(TextureEnum::WALL);

    _wallRight.draw();
    _wallBack.draw();
    _wallLeft.draw();
    _wallRight.draw();
    _wallFrontLeft.draw();
    _wallFrontRight.draw();
    _triangleFront.draw();
    _triangleBack.draw();

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

    // restore original matrix
    modelview = ori;
    glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &modelview[0][0]);
}

void House::toggleDoor() {
    _doorOpen = !_doorOpen;
}

void House::updateAnimation() {
    if(_rotationEnabled)
        _rotationX += ROTATION_STEP;

    if(_windAngle > _flagAngle) {
        _flagAngle += ROTATION_STEP;
    } else if(_windAngle < _flagAngle) {
        _flagAngle -= ROTATION_STEP;
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

void House::drawFlag() {

    glm::mat4 ori{modelview};

    // Rotazione intorno ad uno dei vertici. Notare che l'angolo va passato in radianti. Rotazione di 1 grado
    modelview  = glm::translate(modelview, glm::vec3(0, ROOF_HEIGHT+CYLINDER_HEIGHT-FLAG_HEIGHT, 0));
    modelview = glm::rotate(modelview, _flagAngle-_rotationX, glm::vec3(0.0f, 1.0f, 0.0f));

    // Passa la matrice di modelview allo shader
    glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &modelview[0][0]);

    // draw door
    _texture.enableTexture(true);
    _texture.bind(TextureEnum::FLAG);
    _flag.draw();
    _texture.enableTexture(false);

    // restore original matrix
    modelview = ori;
    glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &modelview[0][0]);
}

// flag cylinder
void House::drawCylinder() const {
    gluQuadricDrawStyle(_quadric, GLU_LINE);
    gluQuadricNormals(_quadric, GLU_SMOOTH);

    glPushMatrix();
    glLineWidth(1.0f);

    glm::mat4 ori{modelview};

    // Rotazione intorno ad uno dei vertici. Notare che l'angolo va passato in radianti. Rotazione di 1 grado
    modelview  = glm::translate(modelview, glm::vec3(0, ROOF_HEIGHT, 0));
    modelview = glm::rotate(modelview, -PI_HALF, glm::vec3(1.0f, 0.0f, 0.0f));

    // Passa la matrice di modelview allo shader
    glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &modelview[0][0]);

    gluCylinder(_quadric, CYLINDER_RADIUS, CYLINDER_RADIUS, CYLINDER_HEIGHT, 32, 32);

    // restore original matrix
    modelview = ori;
    glUniformMatrix4fv(modelviewPos, 1, GL_FALSE, &modelview[0][0]);
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
}

void House::init() {
    _door.init();
    _floor.init();

    _wallBack.init();
    _wallLeft.init();
    _wallRight.init();
    _wallFrontLeft.init();
    _wallFrontRight.init();
    _triangleFront.init();
    _triangleBack.init();

    _roofLeft.init();
    _roofRight.init();

    _chimRight.init();
    _chimLeft.init();
    _chimBack.init();
    _chimFront.init();

    _flag.init();
}
