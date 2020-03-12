//
// Created by massi on 12.03.2020.
//

#include "house.h"
#include "draw_utils.h"

const float SW = 10.0f; //SCENE WIDTH

const float HALF_DOOR_WIDTH = 2.0f / SW;
const float HALF_BASE_WIDTH = 5.0f / SW;
const float BASE_HEIGHT = 8.0f / SW;
const float WALL_WIDTH = 1.0f / SW;
const float WALL_HEIGHT = 6.0f / SW;
const float ROOF_HEIGHT = 11.0f / SW;

const float CHIM_LEFT = -4.0f / SW;
const float CHIM_RIGHT = -3.0f / SW;
const float CHIM_BOTTOM = 7.0f / SW;
const float CHIM_TOP = 11.0f / SW;
const float CHIM_START_DEPTH = -2.0f / SW;
const float CHIM_END_DEPTH = -4.0f / SW;
const float CHIM_THICK = .3f / SW;

#define COLOR_ROOF_EXTERNAL     230, 0, 0
#define COLOR_ROOF_INTERNAL     160, 0, 0
#define COLOR_WALL_EXTERNAL     200, 200, 200
#define COLOR_WALL_INTERNAL     80, 80, 80
#define COLOR_FLOOR             160, 160, 160

void house::draw() {
    draw_floor();
    draw_lateral_walls();
    draw_prism_walls();
    draw_roof();
    draw_chimney();
}

void house::draw_chimney() {
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

void house::draw_floor() {
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

void house::draw_roof() {
    rectangle_t rectangles[] = {
            // right roof wall
            {
                    { WALL_HEIGHT, WALL_HEIGHT, WALL_WIDTH },
                    { WALL_HEIGHT,  WALL_HEIGHT, -(BASE_HEIGHT+WALL_WIDTH)},
                    { 0,  (ROOF_HEIGHT+WALL_WIDTH), -(BASE_HEIGHT+WALL_WIDTH) },
                    { 0,  (ROOF_HEIGHT+WALL_WIDTH), WALL_WIDTH },
                    COLOR_ROOF_EXTERNAL
            },{
                    { WALL_HEIGHT,  HALF_BASE_WIDTH, -(BASE_HEIGHT+WALL_WIDTH)},
                    { WALL_HEIGHT, HALF_BASE_WIDTH, WALL_WIDTH },
                    { 0,  ROOF_HEIGHT, WALL_WIDTH },
                    { 0,  ROOF_HEIGHT, -(BASE_HEIGHT+WALL_WIDTH) },
                    COLOR_ROOF_INTERNAL
            },
            // left roof wall
            {
                    { -WALL_HEIGHT,  WALL_HEIGHT, -(BASE_HEIGHT+WALL_WIDTH)},
                    { -WALL_HEIGHT, WALL_HEIGHT, WALL_WIDTH },
                    { 0,  (ROOF_HEIGHT+WALL_WIDTH), WALL_WIDTH },
                    { 0,  (ROOF_HEIGHT+WALL_WIDTH), -(BASE_HEIGHT+WALL_WIDTH) },
                    COLOR_ROOF_EXTERNAL
            },{
                    { -WALL_HEIGHT, HALF_BASE_WIDTH, WALL_WIDTH },
                    { -WALL_HEIGHT,  HALF_BASE_WIDTH, -(BASE_HEIGHT+WALL_WIDTH)},
                    { 0,  ROOF_HEIGHT, -(BASE_HEIGHT+WALL_WIDTH) },
                    { 0,  ROOF_HEIGHT, WALL_WIDTH },
                    COLOR_ROOF_INTERNAL
            }
    };

    draw_parallelepiped(rectangles[0], rectangles[1]);
    draw_parallelepiped(rectangles[2], rectangles[3]);
}

void house::draw_prism_walls() {
    triangle_t triangles[] = {
            {
                    { -HALF_BASE_WIDTH,  WALL_HEIGHT, 0 },
                    { HALF_BASE_WIDTH, WALL_HEIGHT, 0 },
                    { 0,  ROOF_HEIGHT, 0 },
                    COLOR_WALL_EXTERNAL
            },
            {
                    { HALF_BASE_WIDTH, WALL_HEIGHT, -WALL_WIDTH },
                    { -HALF_BASE_WIDTH,  WALL_HEIGHT,  -WALL_WIDTH},
                    { 0,  ROOF_HEIGHT, -WALL_WIDTH },
                    COLOR_WALL_INTERNAL
            },
            {
                    { HALF_BASE_WIDTH, WALL_HEIGHT, -(BASE_HEIGHT) },
                    { -HALF_BASE_WIDTH,  WALL_HEIGHT, -(BASE_HEIGHT)},
                    { 0,  ROOF_HEIGHT, -BASE_HEIGHT },
                    COLOR_WALL_EXTERNAL
            },
            {
                    { -HALF_BASE_WIDTH,  WALL_HEIGHT, -(BASE_HEIGHT-WALL_WIDTH)},
                    { HALF_BASE_WIDTH, WALL_HEIGHT, -(BASE_HEIGHT-WALL_WIDTH) },
                    { 0,  ROOF_HEIGHT, -(BASE_HEIGHT-WALL_WIDTH) },
                    COLOR_WALL_INTERNAL
            },
    };

    draw_prism(triangles[0], triangles[1]);
    draw_prism(triangles[2], triangles[3]);
}

void house::draw_lateral_walls() {

    rectangle_t rectangles[10] = {
            // front walls
            {
                    { HALF_DOOR_WIDTH, 0, 0 },
                    { HALF_BASE_WIDTH, 0, 0 },
                    { HALF_BASE_WIDTH, WALL_HEIGHT, 0 },
                    { HALF_DOOR_WIDTH, WALL_HEIGHT, 0 },
                    COLOR_WALL_EXTERNAL
            },
            {
                    { (HALF_BASE_WIDTH-WALL_WIDTH), 0, -WALL_WIDTH },
                    { HALF_DOOR_WIDTH, 0, -WALL_WIDTH },
                    { HALF_DOOR_WIDTH, WALL_HEIGHT, -WALL_WIDTH },
                    { (HALF_BASE_WIDTH-WALL_WIDTH), WALL_HEIGHT, -WALL_WIDTH },
                    COLOR_WALL_INTERNAL
            },
            {
                    { -HALF_BASE_WIDTH, 0, 0},
                    { -HALF_DOOR_WIDTH, 0, 0 },
                    { -HALF_DOOR_WIDTH, WALL_HEIGHT, 0 },
                    { -HALF_BASE_WIDTH, WALL_HEIGHT, 0 },
                    COLOR_WALL_EXTERNAL
            },
            {
                    { -HALF_DOOR_WIDTH, 0, -WALL_WIDTH },
                    { -(HALF_BASE_WIDTH-WALL_WIDTH), 0, -WALL_WIDTH},
                    { -(HALF_BASE_WIDTH-WALL_WIDTH), WALL_HEIGHT, -WALL_WIDTH },
                    { -HALF_DOOR_WIDTH, WALL_HEIGHT, -WALL_WIDTH },
                    COLOR_WALL_INTERNAL
            },
            //right wall
            {
                    { HALF_BASE_WIDTH, 0, 0},
                    { HALF_BASE_WIDTH, 0, -BASE_HEIGHT },
                    { HALF_BASE_WIDTH, WALL_HEIGHT, -BASE_HEIGHT },
                    { HALF_BASE_WIDTH, WALL_HEIGHT, 0 },
                    COLOR_WALL_EXTERNAL
            },
            {
                    { (HALF_BASE_WIDTH-WALL_WIDTH), 0, -(BASE_HEIGHT-WALL_WIDTH) },
                    { (HALF_BASE_WIDTH-WALL_WIDTH), 0, -WALL_WIDTH},
                    { (HALF_BASE_WIDTH-WALL_WIDTH), WALL_HEIGHT, -WALL_WIDTH },
                    { (HALF_BASE_WIDTH-WALL_WIDTH), WALL_HEIGHT, -(BASE_HEIGHT-WALL_WIDTH) },
                    COLOR_WALL_INTERNAL
            },
            // back wall
            {
                    { HALF_BASE_WIDTH, 0, -BASE_HEIGHT },
                    { -HALF_BASE_WIDTH,  0, -BASE_HEIGHT},
                    { -HALF_BASE_WIDTH,  WALL_HEIGHT, -BASE_HEIGHT },
                    { HALF_BASE_WIDTH,  WALL_HEIGHT, -BASE_HEIGHT },
                    COLOR_WALL_EXTERNAL
            },
            {
                    { -(HALF_BASE_WIDTH-WALL_WIDTH),  0, -(BASE_HEIGHT-WALL_WIDTH)},
                    { (HALF_BASE_WIDTH-WALL_WIDTH), 0, -(BASE_HEIGHT-WALL_WIDTH) },
                    { (HALF_BASE_WIDTH-WALL_WIDTH),  WALL_HEIGHT, -(BASE_HEIGHT-WALL_WIDTH) },
                    { -(HALF_BASE_WIDTH-WALL_WIDTH),  WALL_HEIGHT, -(BASE_HEIGHT-WALL_WIDTH) },
                    COLOR_WALL_INTERNAL
            },
            //left wall
            {
                    { -HALF_BASE_WIDTH,  0, -BASE_HEIGHT},
                    { -HALF_BASE_WIDTH, 0, 0 },
                    { -HALF_BASE_WIDTH,  WALL_HEIGHT, 0 },
                    { -HALF_BASE_WIDTH,  WALL_HEIGHT, -BASE_HEIGHT },
                    COLOR_WALL_EXTERNAL
            },
            {
                    { -(HALF_BASE_WIDTH-WALL_WIDTH), 0, -WALL_WIDTH },
                    { -(HALF_BASE_WIDTH-WALL_WIDTH),  0, -(BASE_HEIGHT-WALL_WIDTH)},
                    { -(HALF_BASE_WIDTH-WALL_WIDTH),  WALL_HEIGHT, -(BASE_HEIGHT-WALL_WIDTH) },
                    { -(HALF_BASE_WIDTH-WALL_WIDTH),  WALL_HEIGHT, -WALL_WIDTH },
                    COLOR_WALL_INTERNAL
            },
    };
    int nrOfWalls = sizeof(rectangles) / sizeof(rectangles[0]);
    for (int i = 0; i < nrOfWalls; i=i+2) {
        draw_parallelepiped(rectangles[i], rectangles[i + 1]);
    }

}