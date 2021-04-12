/**
 * This header contains forward-declarations for core and bgfx classes
 */
#ifndef CORE_ESSENTIAL_H
#define CORE_ESSENTIAL_H

#include <string>
#include <vector>
#include <cstdint>


namespace core {

struct RgbaColor;
struct AbgrColor;

class Color;
class Degree;
class Entity;
class Logger;
class Math;
class Object;
class Component;
class Primitive;
class Radian;
class Renderer;
class Root;
class Window;
class WindowBuilder;
class WindowPool;


template<int cols, int rows, typename T> class Matrix;
template<int dims, typename T> class Vector;
template<typename T> class Node;
template<typename T> class Singleton;


typedef std::string string;
typedef uint32_t rgba;
typedef uint32_t abgr;

typedef struct Cube Cube;
typedef struct Rect Rect;
typedef struct ColorVertex ColorVertex;

typedef Matrix<3, 3, float> Matrix3;
typedef Matrix<3, 3, int> Matrix3i;
typedef Matrix<4, 4, float> Matrix4;
typedef Matrix<4, 4, int> Matrix4i;

typedef Vector<2, float> Vector2;
typedef Vector<2, int> Vector2i;
typedef Vector<3, float> Vector3;
typedef Vector<3, int> Vector3i;
typedef Vector<4, float> Vector4;


} // namespace core


namespace bgfx {

class PlatformData;

} // namespace bgfx


/// Defined by CORE_HEAVY_ESSENTIALS option in CMakeLists.txt
#ifdef CORE_HEAVY_ESSENTIALS
#include "Matrix.h"
#include "Vector.h"
#include "Object.h"
#include "Singleton.h"
#endif


#endif //CORE_ESSENTIAL_H
