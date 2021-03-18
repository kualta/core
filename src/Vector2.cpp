#include "Vector2.h"

#include <utility>

namespace core {


Vector2::Vector2(int x, int y) : x(x_), y(y_) {  }
Vector2::Vector2(Vector2 *pVector2) : x(pVector2->x), y(pVector2->y) {  }
Vector2::~Vector2() = default;

Vector2 Vector2::operator=(Vector2 other) {
    std::swap(this->x_, other.x_);
    std::swap(this->y_, other.y_);
    return *this;
}

}
