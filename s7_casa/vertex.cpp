//
// Created by massi on 18.04.2020.
//

#include <math.h>
#include "vertex.h"

void Vertex::set(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vertex::copyFrom(const Vertex& o) {
    x = o.x;
    y = o.y;
    z = o.z;
}

Vertex Vertex::operator-() {
    return Vertex{-x, -y, -z };
}

Vertex Vertex::sum(const Vertex& o) {
    return Vertex{x + o.x, y + o.y, z + o.z };
}

//  n = v x u
//  return the normal vector
Vertex Vertex::crossProduct(const Vertex& o) {
    return Vertex{y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x };
}

//  n = v * s,
// return a vector
Vertex Vertex::scalarProduct(float scalar) {
    return Vertex{x * scalar, y * scalar, z * scalar };
}

// also known as inner product, return a scalar
// the relation of cos(a) and the two vectors
// n = v . u = |v| |u| * cos(a) = vx*ux + vy*uy + vz*uz
GLfloat Vertex::dotProduct(const Vertex& o) {
    return x*o.x + y*o.y + z*o.z;
}

// return the length of the vector
GLfloat Vertex::length() {
    return sqrt(x*x + y*y + z*z);
}

// return the normalized vector
void Vertex::normalize() {
    float len = length();
    if (len != 0) {
        x /= len;
        y /= len;
        z /= len;
    }
}

bool Vertex::inViewingVolume(const float *projectionMatrix, const float *modelviewMatrix) {
    // simulate pipeline

    // multiply current vertex by the model-view matrix
    Vertex v = this->matrixProduct(modelviewMatrix);

    // multiply the result vertex by the projection  matrix
    v = v.matrixProduct(projectionMatrix);

    // divide by the 4th coordinate (w) and get abs normalized coords
    // if any norm coords is greater than 1, i'm out of the viewing volume
    bool inBound = !(abs(v.x / v.w) > 1.0 || abs(v.y / v.w) > 1.0 || abs(v.z / v.w) > 1.0);
    if(!inBound)
        return false;

    return inBound;
}

Vertex Vertex::matrixProduct(const float *m) {
    return Vertex{
            x*m[0] + y*m[1] + z*m[2] + w*m[3],
            x*m[4] + y*m[5] + z*m[6] + w*m[7],
            x*m[8] + y*m[9] + z*m[10] + w*m[11],
            x*m[12] + y*m[13] + z*m[14] + w*m[15]};
}

void Vertex::matrixTranspose(const float *m, float *t) {
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
