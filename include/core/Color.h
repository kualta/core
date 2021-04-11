#ifndef CORE_COLOR_H
#define CORE_COLOR_H


namespace core {

/**
 * rgba constants for convinience
 */
struct RgbaColor {
    static const uint32_t white = 0xffffffff;
    static const uint32_t grey = 0x808080ff;
    static const uint32_t silver = 0xc0c0c0ff;
    static const uint32_t black = 0x000000ff;
    static const uint32_t red = 0xff0000ff;
    static const uint32_t green = 0x00ff00ff;
    static const uint32_t blue = 0x0000ffff;
    static const uint32_t yellow = 0xffff00ff;
    static const uint32_t cyan = 0x00ffffff;
    static const uint32_t pink = 0xffc0cbff;
    static const uint32_t corePurple = 0x784278ff;
};

/**
 * abgr constants for convinience
 */
struct AbgrColor {
    static const uint32_t white = 0xffffffff;
    static const uint32_t grey = 0xff808080;
    static const uint32_t silver = 0xffc0c0c0;
    static const uint32_t black = 0xff000000;
    static const uint32_t red = 0xff0000ff;
    static const uint32_t green = 0xff00ff00;
    static const uint32_t blue = 0xffff0000;
    static const uint32_t yellow = 0xff00ffff;
    static const uint32_t cyan = 0xffffffff00;
    static const uint32_t pink = 0xffcbc0ff;
    static const uint32_t corePurple = 0xff784278;
};

class Color {

};

}


#endif //CORE_COLOR_H
