#ifndef CORE_GEOMETRY_H
#define CORE_GEOMETRY_H

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
    uint32_t abgr;
} ColorVertex;


}

#endif //CORE_GEOMETRY_H
