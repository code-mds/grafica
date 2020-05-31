//
// Created by massi on 21.05.2020.
//

#ifndef S12_CASA_TEXTURE_H
#define S12_CASA_TEXTURE_H

#ifdef __APPLE__
#include <GL/glew.h>
#include <GLUT/glut.h>
#else
// headers richiesti da Windows e linux
#include <GL/glew.h>
#include <GL/freeglut.h>
#endif

struct TextCoord {
    GLboolean enabled;
    GLfloat s1,t1;
    GLfloat s2,t2;
    GLfloat s3,t3;
    GLfloat s4,t4;
};

enum TextureEnum { WALL=0, WOOD, ROOF };

class Texture {

public:
    void init();
    void bind(TextureEnum textureIdx);
    static void enableTexture(bool enable);
    static bool isTextureEnabled();
private:
    GLuint _textures[3];
};


#endif //S12_CASA_TEXTURE_H
