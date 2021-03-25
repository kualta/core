#ifndef CORE_VECTOR2_H
#define CORE_VECTOR2_H

namespace core {


class Vector2 {
public:
    Vector2(int x, int y);
    Vector2(Vector2 *pVector2);
    ~Vector2();
    bool operator==(const Vector2 &other) const;
    bool operator!=(const Vector2 &rhs) const;

    /// Read-only members
    const int &x;
    const int &y;

private:
    int x_;
    int y_;
};


}

#endif //CORE_VECTOR2_H
