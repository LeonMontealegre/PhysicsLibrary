#ifndef __LEON_TEXTURE_DATA_H__
#define __LEON_TEXTURE_DATA_H__

#include <string>
#include <vector>

#include "../../types.h"

class TextureData {
public:
    const std::string name;
    const uint width, height, N;

    TextureData(const std::string& name_, uint w, uint h, uint N_, unsigned char* data_):
                name(name_), width(w), height(h), N(N_), data(data_) {
    }
    ~TextureData() {
        delete [] data;
    }

    void set(uint x, uint y, uint channel, unsigned char val) {
        data[(y*width + x)*N + channel] = val;
    }

    unsigned char get(uint x, uint y, uint channel) const {
        return data[(y*width + x)*N + channel];
    }

    void fill(uint x0, uint y0, const TextureData& other) {
        for (uint y = 0; y < other.height; y++) {
            for (uint x = 0; x < other.width; x++) {
                for (uint n = 0; n < N; n++) {
                    unsigned char a = other.get(x, y, n);
                    set(x+x0, y+y0, n, a);
                }
            }
        }
    }

    const unsigned char* get_data() const {
        return data;
    }

private:
    unsigned char* data;
};

#endif