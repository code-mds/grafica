//
// Created by massi on 19.04.2020.
//

#ifndef S7_CASA_FRUSTUM_H
#define S7_CASA_FRUSTUM_H

#include "plane.h"
#include "draw_utils.h"

class Frustum {
private:
    enum {
        TOP = 0,
        BOTTOM,
        LEFT,
        RIGHT,
        NEARP,
        FARP
    };

public:
    enum {OUTSIDE, INTERSECT, INSIDE};

    // 6 planes of the frustum
    plane_t _pl[6];

    // near: top-left, top-right, bottom-left, bottom-right
    vertex_t _ntl, _ntr, _nbl, _nbr;
    // far: top-left, top-right, bottom-left, bottom-right
    vertex_t _ftl, _ftr, _fbl, _fbr;

    // distance from eye: near, far
    float _zNear, _zFar;
    // far: width, height
    float _nw, _nh;
    // near: width, height
    float _fw, _fh;
    float _ratio, _angle, _tang;

    void setCamInternals(const Perspective& perspective);
    void setCamDef(vertex_t &eye, vertex_t &center, vertex_t &up);
    int pointInFrustum(vertex_t &p);
    void draw();

    void drawPoints();
    void drawLines();
    void drawPlanes();
    void drawNormals();

};

#endif //S7_CASA_FRUSTUM_H
