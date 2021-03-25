#include "Vector2.h"
#include <utility>
#include "LogManager.h"

namespace core {


Vector2::Vector2(int x, int y) : x(x_), y(y_) {  }
Vector2::Vector2(Vector2 *pVector2) : x(pVector2->x), y(pVector2->y) {  }
Vector2::~Vector2() = default;

bool Vector2::operator==(const Vector2 &other) const {
    return x == other.x &&
        y == other.y &&
        x_ == other.x_ &&
        y_ == other.y_;
}
}
