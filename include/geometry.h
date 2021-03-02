#ifndef INTERFACERS_GEOMETRY_H
#define INTERFACERS_GEOMETRY_H


namespace core {


    class Vector2 {
    public:
        Vector2(int x, int y);
        Vector2(Vector2 *pVector2);

        ~Vector2();

    private:
        int x{}, y{};
    };

    class Geometry {



    };

    typedef struct Rect {
        int x, y;
        int w, h;
    } Rect;

}

#endif //INTERFACERS_GEOMETRY_H
