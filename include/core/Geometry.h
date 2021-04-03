#ifndef CORE_GEOMETRY_H
#define CORE_GEOMETRY_H

#include "Essential.h"


namespace core {


typedef struct Rect {
    Rect(int x, int y, int w, int h);
    Rect(Vector2 pos, int w, int h);
    Rect(Vector2 pos, Vector2 res);
    Vector2 position;
    int w, h;
} Rect;

typedef struct ColorVertex {
    ColorVertex(float x, float y, float z, uint32_t abgr);
    float x;
    float y;
    float z;
    uint32_t abgr;
} ColorVertex;

class Geometry {

};


}

#endif //CORE_GEOMETRY_H
