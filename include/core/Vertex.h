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

typedef struct ColorVertex2 {
    float x;
    float y;
    Vector3 rgb;
} ColorVertex2;

typedef struct Vertex {
    Vector3 position;
    Vector4 rgba;
} Vertex;

}

#endif //CORE_VERTEX_H
