#ifndef __LEON_I_TEXTURE_H__
#define __LEON_I_TEXTURE_H__

#include "../types.h"

class Texture {
public:
    const uint width, height, N;

    Texture(TextureData* data_): data(data_), width(data_->width),
                                 height(data_->height), N(data_->N) {
    }

protected:
    TextureData* data;
};

#endif