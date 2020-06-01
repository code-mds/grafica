//
// Created by massi on 25.04.2020.
//

#ifndef CASA_CAMERA_H
#define CASA_CAMERA_H

#include <GL/glew.h>
#ifdef __APPLE__
// Headers richiesti da OSX
    #include <GLUT/glut.h>
#else
// headers richiesti da Windows e linux
#include <GL/glut.h>
#endif
#include <string>

struct Camera {
    Camera(glm::mat4& modelview, GLint& modelviewPos);
    glm::mat4& modelview;
    GLint& modelviewPos;

    glm::vec3 eye;
    glm::vec3 center;
    glm::vec3 up;

    void reset();

    void moveLeft();
    void moveRight();

    void moveBottom();
    void moveTop();

    void moveForward();
    void moveBackward();

    void lookAt();

    std::string toString();
};


#endif //CASA_CAMERA_H
