#ifndef CORE_GEOMETRY_H
#define CORE_GEOMETRY_H



namespace core {

// TODO: Extract Vector2 class to separate file
    class Vector2 {
    public:
        Vector2(int x, int y);
        Vector2(Vector2 *pVector2);
        ~Vector2();
        Vector2 operator=(Vector2 other);

        /// Read-only members
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

#endif //CORE_GEOMETRY_H
