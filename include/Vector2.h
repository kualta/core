#ifndef CORE_VECTOR2_H
#define CORE_VECTOR2_H


namespace core {


class Vector2 {
public:
    Vector2(float x, float y);
    Vector2(Vector2 *pVector2);
    ~Vector2();

    float x;
    float y;
};


}

#endif //CORE_VECTOR2_H
