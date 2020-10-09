#ifndef __LEON_TEXTURE_ATLAS_H__
#define __LEON_TEXTURE_ATLAS_H__

#include <string>
#include <map>

#include "../../vector.h"
#include "../../color.h"
#include "texture_data.h"

class TextureAtlas {
public:
    struct TextureInfo {
        Vec2ui pos, size;
        Color avg_color;
    };

    TextureAtlas(TextureData* data_ = NULL): data(data_) {
    }

    void put(const std::string& tag, const TextureInfo& i) {
        info.insert(std::make_pair(tag, i));
    }

    const TextureInfo& operator [] (const std::string& key) {
        return info[key];
    }

    void set_data(TextureData* data_) {
        data = data_;
    }

    TextureData* get_data() {
        return data;
    }

private:
    std::map<std::string, TextureInfo> info;
    TextureData* data;
};

#endif