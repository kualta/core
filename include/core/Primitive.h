/**
 * Header defines primitive geometry types
 */
#ifndef CORE_PRIMITIVE_H
#define CORE_PRIMITIVE_H

#include "Essential.h"

namespace core {

typedef struct Rect {
    int x, y;
    int w, h;
} Rect;

typedef struct ColorVertex {
    float x;
    float y;
    float z;
    abgr abgr;
} ColorVertex;

class Primitive {
    // TODO: Hide vectors behind Primitive's methods
};

struct Cube : public Primitive {
    const std::vector<ColorVertex> vertices {
            {-1.0f,  1.0f,  1.0f, 0xff000000 },
            { 1.0f,  1.0f,  1.0f, 0xff0000ff },
            {-1.0f, -1.0f,  1.0f, 0xff00ff00 },
            { 1.0f, -1.0f,  1.0f, 0xff00ffff },
            {-1.0f,  1.0f, -1.0f, 0xffff0000 },
            { 1.0f,  1.0f, -1.0f, 0xffff00ff },
            {-1.0f, -1.0f, -1.0f, 0xffffff00 },
            { 1.0f, -1.0f, -1.0f, 0xffffffff }
    };
    const std::vector<uint16_t> triangles {
            0, 1, 2,
            1, 3, 2,
            4, 6, 5,
            5, 6, 7,
            0, 2, 4,
            4, 2, 6,
            1, 5, 3,
            5, 7, 3,
            0, 4, 1,
            4, 5, 1,
            2, 3, 6,
            6, 3, 7,
    };
};

}


#endif //CORE_PRIMITIVE_H
