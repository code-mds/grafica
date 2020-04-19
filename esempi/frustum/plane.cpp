//
// Created by massi on 18.04.2020.
//

#include "plane.h"

plane_t::plane_t( vertex_t &v1,  vertex_t &v2,  vertex_t &v3) {
    set3Points(v1,v2,v3);
}

plane_t::plane_t() {}

void plane_t::set3Points( vertex_t &v1,  vertex_t &v2,  vertex_t &v3) {
    vertex_t aux1{}, aux2{};
    aux1 = v1.sum(-v2);
    aux2 = v3.sum(-v2);
    normal = aux2.crossProduct(aux1);
    normal.normalize();
    point.copyFrom(v2);
    d = -(normal.dotProduct(point));
}

/*
 * n is the normal, p is a point
 */
void plane_t::setNormalAndPoint(vertex_t &n, vertex_t &p) {
    normal.copyFrom(n);
    normal.normalize();
    d = -(normal.dotProduct(p));
}

/*
 * Ax + By + Cz + D = 0
 */
void plane_t::setCoefficients(float A, float B, float C, float D) {
    // set the normal vector
    normal.set(A, B, C);
    //compute the length of the vector
    float l = normal.length();
    // normalize the vector
    normal.set(A / l, B / l, C / l);
    // and divide D by the length as well
    this->d = D / l;
}

/*
 * dist(plane,p) = A*px + B*py + C*pz + D = n . p  + D
 * distance = 0 -> in plane
 * distance > 0 -> in the side of the normal
 * distance < 0 -> opposite to the normal
 */
float plane_t::distance(vertex_t &p) {
    return (d + normal.dotProduct(p));
}
