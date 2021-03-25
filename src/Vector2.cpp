#include "Vector2.h"
#include <utility>
#include "LogManager.h"

namespace core {


Vector2::Vector2(float x, float y) : x(x), y(y) {  }
Vector2::Vector2(Vector2 *pVector2) : x(pVector2->x), y(pVector2->y) {  }
Vector2::~Vector2() = default;

}
