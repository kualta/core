#include <core/Geometry.h>
#include <core/Vector.h>


namespace core {


Rect::Rect(int x, int y, int w, int h)
    : position(Vector2(x, y).Ptr()), w(w), h(h) {
}
Rect::Rect(Vector2 pos, int w, int h)
    : position(pos.Ptr()), w(w), h(h) {
}
Rect::Rect(Vector2 pos, Vector2 res)
    : position(pos.Ptr()), w(res.x), h(res.y){
}

ColorVertex::ColorVertex(float x, float y, float z, uint32_t abgr)
    : x(x), y(y), z(z), abgr(abgr) {

}

} // namespace