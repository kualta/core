#ifndef INTERFACERS_GEOMETRY_H
#define INTERFACERS_GEOMETRY_H


namespace core {


    class Vector2 {
    public:
        Vector2(int x, int y);
        Vector2(Vector2 *pVector2);

        ~Vector2();

        const int &x;
        const int &y;

    private:
        int x_;
        int y_;
    };

    class Geometry {



    };

    typedef struct Rect {
        Rect(int x, int y, int w, int h);
        Rect(Vector2 pos, int w, int h);
        Rect(Vector2 position, Vector2 resolution);
        Vector2 position;
        int w, h;
    } Rect;

}

#endif //INTERFACERS_GEOMETRY_H
