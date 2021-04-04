#include <core/Geometry.h>
#include <core/Vector.h>


namespace core {


Rect::Rect(int x, int y, int w, int h)
    : x(x), y(y), w(w), h(h) {  }
Rect::Rect(const Vector2 &pos, int w, int h)
    : x(pos.x), y(pos.y), w(w), h(h) {  }
Rect::Rect(const Vector2 *pos, int w, int h)
    : x(pos->x), y(pos->y), w(w), h(h)  {  }
Rect::Rect(const Vector2 &pos, const Vector2 &res)
    : x(pos.x), y(pos.y), w(res.x), h(res.y){  }

ColorVertex::ColorVertex(float x, float y, float z, uint32_t abgr)
    : x(x), y(y), z(z), abgr(abgr) {  }

} // namespace