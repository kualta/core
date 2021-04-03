/**
 * This header contains forward-declarations for core classes
 */
#ifndef CORE_ESSENTIAL_H
#define CORE_ESSENTIAL_H

#include <cassert>
#include <cstdint>
#include "Singleton.h"

namespace core {


class LogManager;
class Math;
class Matrix;
class ObjectId;
class RenderManager;
class Root;
template<typename T> class Singleton;
template<int dims, typename T> class Vector;
typedef Vector<2, float> Vector2;
typedef Vector<2, int> Vector2i;
typedef Vector<3, float> Vector3;
typedef Vector<3, int> Vector3i;
typedef Vector<4, float> Vector4;
class Window;
class WindowBuilder;
class WindowPool;


} // namespace core


#endif //CORE_ESSENTIAL_H
