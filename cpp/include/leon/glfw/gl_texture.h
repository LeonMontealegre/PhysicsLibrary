#ifndef __LEON_GLFW_TEXTURE_H__
#define __LEON_GLFW_TEXTURE_H__

#include <GLFW/glfw3.h>

#include "../types.h"
#include "../interfaces/texture.h"
#include "../utils/textures/texture_data.h"

class GLTexture: public Texture {
public:
    GLTexture(TextureData* data): Texture(data) {
        unit = NEXT_UNIT++;

        const GLuint type = (N == 3 ? GL_RGB : GL_RGBA);

        glGenTextures(1, &id);
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
        glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, data->get_data());
    }

private:
    static uint NEXT_UNIT;

    const uint unit;
    GLuint id;
};

uint Texture::NEXT_UNIT = 0;


#endif