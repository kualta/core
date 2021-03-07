#include <core.h>
#include "geometry.h"

namespace core {

    Vector2::Vector2(int x, int y) {
        this->x = x;
        this->y = y;
    }

    Vector2::Vector2(Vector2 *pVector2) {
        this->x = pVector2->x;
        this->y = pVector2->y;
    }

    Vector2::Vector2() {
        this->x = NULL;
        this->y = NULL;
    }

    Vector2::~Vector2() = default;

Rect::Rect(int x, int y, int w, int h)
    : x(x), y(y), w(w), h(h)
{

}
}