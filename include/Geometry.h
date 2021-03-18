#ifndef CORE_GEOMETRY_H
#define CORE_GEOMETRY_H

#include "Vector2.h"


namespace core {


typedef struct Rect {
    Rect(int x, int y, int w, int h);
    Rect(Vector2 pos, int w, int h);
    Rect(Vector2 pos, Vector2 res);
    Vector2 position;
    int w, h;
} Rect;

class Geometry {

};


}

#endif //CORE_GEOMETRY_H
