//
// Created by massi on 25.04.2020.
//

#include <sstream>
#include <iomanip>
#include "camera.h"

static const float CAMERA_STEP = .25;

void Camera::moveLeft() {
    eye.x -= CAMERA_STEP;
    lookAt();
}
void Camera::moveRight() {
    eye.x += CAMERA_STEP;
    lookAt();
}
void Camera::moveBottom() {
    eye.y -= CAMERA_STEP;
    lookAt();
}
void Camera::moveTop() {
    eye.y += CAMERA_STEP;
    lookAt();
}
void Camera::moveForward() {
    eye.z -= CAMERA_STEP;
    lookAt();
}
void Camera::moveBackward() {
    eye.z += CAMERA_STEP;
    lookAt();
}

void Camera::reset() {
    eye = {0, 0, 5.0};
    center = {0, 0, 0};
    up = {0 , 1, 0};
}

void Camera::lookAt() {
    // set MODEL/VIEW matrix mode
    glMatrixMode(GL_MODELVIEW);

    // load identity matrix
    glLoadIdentity();

    gluLookAt(eye.x, eye.y, eye.z,
              center.x, center.y, center.z,
              up.x, up.y, up.z);
}

std::string Camera::toString() {
    std::ostringstream ostr;
    ostr << std::fixed << std::setprecision(2);
    ostr << "Camera: x=" << eye.x;
    ostr << ", y=" << eye.y;
    ostr << ", z=" << eye.z;
    return ostr.str();
}
