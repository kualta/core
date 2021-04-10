/**
 * This header contains forward-declarations for core and bgfx classes
 */
#ifndef CORE_ESSENTIAL_H
#define CORE_ESSENTIAL_H

#include <string>
#include <vector>
#include <cstdint>


namespace core {

typedef struct Cube Cube;
class Degree;
class LogManager;
class Math;
template<int cols, int rows, typename T> class Matrix;
typedef Matrix<3, 3, float> Matrix3;
typedef Matrix<3, 3, int> Matrix3i;
typedef Matrix<4, 4, float> Matrix4;
typedef Matrix<4, 4, int> Matrix4i;
class Node;
class Object;
class Entity;
class Component;
class Primitive;
class Radian;
class RenderManager;
class Root;
typedef std::string string;
template<typename T> class Singleton;
template<int dims, typename T> class Vector;
typedef Vector<2, float> Vector2;
typedef Vector<2, int> Vector2i;
typedef Vector<3, float> Vector3;
typedef Vector<3, int> Vector3i;
typedef Vector<4, float> Vector4;
typedef struct Rect Rect;
typedef struct ColorVertex ColorVertex;
class Window;
class WindowBuilder;
class WindowPool;

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
