#include <core.h>
#include <utility>
#include "geometry.h"


namespace core {


Vector2::Vector2(int x, int y) : x(x_), y(y_) {  }
Vector2::Vector2(Vector2 *pVector2) : x(pVector2->x), y(pVector2->y) {  }
Vector2::~Vector2() = default;
Vector2 Vector2::operator=(Vector2 other) {
    std::swap(this->x_, other.x_);
    std::swap(this->y_, other.y_);

    return *this;
}

Rect::Rect(int x, int y, int w, int h)
    : position(Vector2(x, y)), w(w), h(h) {

}
Rect::Rect(Vector2 pos, int w, int h)
    : position(pos), w(w), h(h) {
}
Rect::Rect(Vector2 pos, Vector2 res)
    : position(pos), w(res.x), h(res.y){

}


}