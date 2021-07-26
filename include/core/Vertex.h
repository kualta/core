#ifndef CORE_VERTEX_H
#define CORE_VERTEX_H

#include "Essential.h"
#include "Vector.h"

namespace core {

typedef struct ColorVertex {
    float x;
    float y;
    float z;
    Vector4 argb;
} ColorVertex;

}

#endif //CORE_VERTEX_H
