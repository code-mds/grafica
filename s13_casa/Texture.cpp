//
// Created by massi on 21.05.2020.
//

#include "Texture.h"
#include "RgbImage.h"

#define TEXTURES_NUM 4

const char * textureFiles[TEXTURES_NUM] = {
    "images/wall_texture.bmp",
    "images/wood_texture.bmp",
    "images/roof_texture.bmp",
    "images/marble_texture.bmp"
};

void Texture::init()  {
    glGenTextures (TEXTURES_NUM, _textures);
    for (int i = 0; i < TEXTURES_NUM; ++i) {
        // Pixel alignment: each row is word aligned (aligned to a 4 byte boundary)
        // Therefore, no need to call glPixelStore( GL_UNPACK_ALIGNMENT, ... );
        RgbImage rgbImg(textureFiles[i]);
        glBindTexture(GL_TEXTURE_2D, _textures[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                     rgbImg.GetNumCols(), rgbImg.GetNumRows(),
                     0, GL_RGB, GL_UNSIGNED_BYTE, rgbImg.ImageData());
    }
}

void Texture::bind(TextureEnum texture) {
    glBindTexture(GL_TEXTURE_2D, _textures[texture]);
}

void Texture::enableTexture(bool enable) {
    if(enable)
        glEnable(GL_TEXTURE_2D);
    else
        glDisable(GL_TEXTURE_2D);
}

bool Texture::isTextureEnabled() {
    GLboolean isTextureEnabled;
    glGetBooleanv(GL_TEXTURE_2D, &isTextureEnabled);
    return isTextureEnabled;
}
