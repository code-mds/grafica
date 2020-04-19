//
// Created by massi on 18.04.2020.
//

#ifndef S7_CASA_PLANE_H
#define S7_CASA_PLANE_H

#include "vertex.h"

struct plane_t {
    vertex_t normal, point;
    float d;

    plane_t( vertex_t &v1,  vertex_t &v2,  vertex_t &v3);
    plane_t(void);

    void set3Points( vertex_t &v1,  vertex_t &v2,  vertex_t &v3);
    void setNormalAndPoint(vertex_t &n, vertex_t &p);
    void setCoefficients(float A, float B, float C, float D);
    float distance(vertex_t &p);
};


#endif //S7_CASA_PLANE_H
