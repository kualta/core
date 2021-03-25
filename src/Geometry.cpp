#include "Geometry.h"


namespace core {


Rect::Rect(int x, int y, int w, int h)
    : position(new Vector2(x, y)), w(w), h(h) {
}
Rect::Rect(Vector2 pos, int w, int h)
    : position(pos), w(w), h(h) {
}
Rect::Rect(Vector2 pos, Vector2 res)
    : position(pos), w(res.x), h(res.y){
}


}