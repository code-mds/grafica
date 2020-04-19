//
// Created by massi on 18.04.2020.
//

#include <math.h>
#include "vertex.h"

void vertex_t::set(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

void vertex_t::copyFrom(const vertex_t& o) {
    x = o.x;
    y = o.y;
    z = o.z;
}

vertex_t vertex_t::operator-() {
    return vertex_t{ -x, -y, -z };
}

vertex_t vertex_t::sum(const vertex_t& o) {
    return vertex_t{ x+o.x, y+o.y, z+o.z };
}

//  n = v x u
//  return the normal vector
vertex_t vertex_t::crossProduct(const vertex_t& o) {
    return vertex_t{ y*o.z - z*o.y, z * o.x - x * o.z, x * o.y - y * o.x };
}

//  n = v * s,
// return a vector
vertex_t vertex_t::scalarProduct(float scalar) {
    return vertex_t{ x*scalar, y*scalar, z*scalar };
}

// also known as inner product, return a scalar
// the relation of cos(a) and the two vectors
// n = v . u = |v| |u| * cos(a) = vx*ux + vy*uy + vz*uz
GLfloat vertex_t::dotProduct(const vertex_t& o) {
    return x*o.x + y*o.y + z*o.z;
}

// return the length of the vector
GLfloat vertex_t::length() {
    return sqrt(x*x + y*y + z*z);
}

// return the normalized vector
void vertex_t::normalize() {
    float len = length();
    if (len != 0) {
        x /= len;
        y /= len;
        z /= len;
    }
}

bool vertex_t::inViewingVolume(const float *projectionMatrix, const float *modelviewMatrix) {
    vertex_t v = this->matrixProduct(modelviewMatrix);
    v = v.matrixProduct(projectionMatrix);

    return !(abs(v.x / v.w) > 1.0 || abs(v.y / v.w) > 1.0 || abs(v.z / v.w) > 1.0);
}

vertex_t vertex_t::matrixProduct(const float *m) {
    return vertex_t{
            x*m[0] + y*m[1] + z*m[2] + w*m[3],
            x*m[4] + y*m[5] + z*m[6] + w*m[7],
            x*m[8] + y*m[9] + z*m[10] + w*m[11],
            x*m[12] + y*m[13] + z*m[14] + w*m[15]};
}

void vertex_t::matrixTranspose(const float *m, float *t) {
    t[0] = m[0];
    t[1] = m[4];
    t[2] = m[8];
    t[3] = m[12];
    t[4] = m[1];
    t[5] = m[5];
    t[6] = m[9];
    t[7] = m[13];
    t[8] = m[2];
    t[9] = m[6];
    t[10] = m[10];
    t[11] = m[14];
    t[12] = m[3];
    t[13] = m[7];
    t[14] = m[11];
    t[15] = m[15];
}
