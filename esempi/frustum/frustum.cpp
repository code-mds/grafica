//
// Created by massi on 19.04.2020.
//

#include <cmath>
#include "frustum.h"

#define ANG2RAD 3.14159265358979323846/180.0

void Frustum::setCamInternals(const Perspective& perspective) {
    _angle = perspective.fovy;
    _ratio = perspective.ratio;
    _zNear = perspective.zNear;
    _zFar = perspective.zFar;

    _tang = (float)tan(_angle * ANG2RAD * 0.5) ;
    _nh = _zNear * _tang;
    _nw = _nh * _ratio;
    _fh = _zFar * _tang;
    _fw = _fh * _ratio;
}

void Frustum::setCamDef(vertex_t &eye, vertex_t &center, vertex_t &up) {
    vertex_t Z = eye.sum(-center);
    Z.normalize();

    vertex_t X = up.crossProduct(Z);
    X.normalize();

    vertex_t Y = Z.crossProduct(X);

    vertex_t nc = eye.sum(- Z.scalarProduct(_zNear));
    vertex_t fc = eye.sum(- Z.scalarProduct(_zFar));

    _ntl = nc.sum(Y.scalarProduct(_nh)).sum(- X.scalarProduct(_nw));
    _ntr = nc.sum(Y.scalarProduct(_nh)).sum(X.scalarProduct(_nw));
    _nbl = nc.sum(-Y.scalarProduct(_nh)).sum(- X.scalarProduct(_nw));
    _nbr = nc.sum(-Y.scalarProduct(_nh)).sum(X.scalarProduct(_nw));

    _ftl = fc.sum(Y.scalarProduct(_fh)).sum(- X.scalarProduct(_fw));
    _ftr = fc.sum(Y.scalarProduct(_fh)).sum(X.scalarProduct(_fw));
    _fbl = fc.sum(-Y.scalarProduct(_fh)).sum(- X.scalarProduct(_fw));
    _fbr = nc.sum(-Y.scalarProduct(_fh)).sum(X.scalarProduct(_fw));

    _pl[TOP].set3Points(_ntr, _ntl, _ftl);
    _pl[BOTTOM].set3Points(_nbl, _nbr, _fbr);
    _pl[LEFT].set3Points(_ntl, _nbl, _fbl);
    _pl[RIGHT].set3Points(_nbr, _ntr, _fbr);
    _pl[NEARP].set3Points(_ntl, _ntr, _nbr);
    _pl[FARP].set3Points(_ftr, _ftl, _fbl);
}

int Frustum::pointInFrustum(vertex_t &p) {
    for(int i=0; i < 6; i++) {
        if (_pl[i].distance(p) < 0)
            return OUTSIDE;
    }
    return INSIDE;
}

void Frustum::draw() {
    drawPoints();
    drawLines();
    drawPlanes();
    drawNormals();
}

void Frustum::drawPoints() {
    glBegin(GL_POINTS);

    glVertex3f(_ntl.x,_ntl.y,_ntl.z);
    glVertex3f(_ntr.x,_ntr.y,_ntr.z);
    glVertex3f(_nbl.x,_nbl.y,_nbl.z);
    glVertex3f(_nbr.x,_nbr.y,_nbr.z);

    glVertex3f(_ftl.x,_ftl.y,_ftl.z);
    glVertex3f(_ftr.x,_ftr.y,_ftr.z);
    glVertex3f(_fbl.x,_fbl.y,_fbl.z);
    glVertex3f(_fbr.x,_fbr.y,_fbr.z);

    glEnd();
}

void Frustum::drawLines() {

    glBegin(GL_LINE_LOOP);
    //near plane
    glVertex3f(_ntl.x,_ntl.y,_ntl.z);
    glVertex3f(_ntr.x,_ntr.y,_ntr.z);
    glVertex3f(_nbr.x,_nbr.y,_nbr.z);
    glVertex3f(_nbl.x,_nbl.y,_nbl.z);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //far plane
    glVertex3f(_ftr.x,_ftr.y,_ftr.z);
    glVertex3f(_ftl.x,_ftl.y,_ftl.z);
    glVertex3f(_fbl.x,_fbl.y,_fbl.z);
    glVertex3f(_fbr.x,_fbr.y,_fbr.z);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //bottom plane
    glVertex3f(_nbl.x,_nbl.y,_nbl.z);
    glVertex3f(_nbr.x,_nbr.y,_nbr.z);
    glVertex3f(_fbr.x,_fbr.y,_fbr.z);
    glVertex3f(_fbl.x,_fbl.y,_fbl.z);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //top plane
    glVertex3f(_ntr.x,_ntr.y,_ntr.z);
    glVertex3f(_ntl.x,_ntl.y,_ntl.z);
    glVertex3f(_ftl.x,_ftl.y,_ftl.z);
    glVertex3f(_ftr.x,_ftr.y,_ftr.z);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //left plane
    glVertex3f(_ntl.x,_ntl.y,_ntl.z);
    glVertex3f(_nbl.x,_nbl.y,_nbl.z);
    glVertex3f(_fbl.x,_fbl.y,_fbl.z);
    glVertex3f(_ftl.x,_ftl.y,_ftl.z);
    glEnd();

    glBegin(GL_LINE_LOOP);
    // right plane
    glVertex3f(_nbr.x,_nbr.y,_nbr.z);
    glVertex3f(_ntr.x,_ntr.y,_ntr.z);
    glVertex3f(_ftr.x,_ftr.y,_ftr.z);
    glVertex3f(_fbr.x,_fbr.y,_fbr.z);

    glEnd();
}


void Frustum::drawPlanes() {

    glBegin(GL_QUADS);

    //near plane
    glVertex3f(_ntl.x,_ntl.y,_ntl.z);
    glVertex3f(_ntr.x,_ntr.y,_ntr.z);
    glVertex3f(_nbr.x,_nbr.y,_nbr.z);
    glVertex3f(_nbl.x,_nbl.y,_nbl.z);

    //far plane
    glVertex3f(_ftr.x,_ftr.y,_ftr.z);
    glVertex3f(_ftl.x,_ftl.y,_ftl.z);
    glVertex3f(_fbl.x,_fbl.y,_fbl.z);
    glVertex3f(_fbr.x,_fbr.y,_fbr.z);

    //bottom plane
    glVertex3f(_nbl.x,_nbl.y,_nbl.z);
    glVertex3f(_nbr.x,_nbr.y,_nbr.z);
    glVertex3f(_fbr.x,_fbr.y,_fbr.z);
    glVertex3f(_fbl.x,_fbl.y,_fbl.z);

    //top plane
    glVertex3f(_ntr.x,_ntr.y,_ntr.z);
    glVertex3f(_ntl.x,_ntl.y,_ntl.z);
    glVertex3f(_ftl.x,_ftl.y,_ftl.z);
    glVertex3f(_ftr.x,_ftr.y,_ftr.z);

    //left plane

    glVertex3f(_ntl.x,_ntl.y,_ntl.z);
    glVertex3f(_nbl.x,_nbl.y,_nbl.z);
    glVertex3f(_fbl.x,_fbl.y,_fbl.z);
    glVertex3f(_ftl.x,_ftl.y,_ftl.z);

    // right plane
    glVertex3f(_nbr.x,_nbr.y,_nbr.z);
    glVertex3f(_ntr.x,_ntr.y,_ntr.z);
    glVertex3f(_ftr.x,_ftr.y,_ftr.z);
    glVertex3f(_fbr.x,_fbr.y,_fbr.z);

    glEnd();

}

void Frustum::drawNormals() {

    vertex_t a,b;

    glBegin(GL_LINES);

    // near
    a = (_ntr.sum(_ntl).sum(_nbr).sum(_nbl)).scalarProduct(.25);
    b = a.sum(_pl[NEARP].normal);
    glVertex3f(a.x,a.y,a.z);
    glVertex3f(b.x,b.y,b.z);

//    // far
//    a = (_ftr + _ftl + _fbr + _fbl) * 0.25;
//    b = a + _pl[FARP].normal;
//    glVertex3f(a.x,a.y,a.z);
//    glVertex3f(b.x,b.y,b.z);
//
//    // left
//    a = (_ftl + _fbl + _nbl + _ntl) * 0.25;
//    b = a + _pl[LEFT].normal;
//    glVertex3f(a.x,a.y,a.z);
//    glVertex3f(b.x,b.y,b.z);
//
//    // right
//    a = (_ftr + _nbr + _fbr + _ntr) * 0.25;
//    b = a + _pl[RIGHT].normal;
//    glVertex3f(a.x,a.y,a.z);
//    glVertex3f(b.x,b.y,b.z);
//
//    // top
//    a = (_ftr + _ftl + _ntr + _ntl) * 0.25;
//    b = a + _pl[TOP].normal;
//    glVertex3f(a.x,a.y,a.z);
//    glVertex3f(b.x,b.y,b.z);
//
//    // bottom
//    a = (_fbr + _fbl + _nbr + _nbl) * 0.25;
//    b = a + _pl[BOTTOM].normal;
//    glVertex3f(a.x,a.y,a.z);
//    glVertex3f(b.x,b.y,b.z);

   glEnd();
}