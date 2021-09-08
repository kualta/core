/**
 * This header contains forward-declarations for core and bgfx classes
 */
#ifndef CORE_ESSENTIAL_H
#define CORE_ESSENTIAL_H

// ### Core defines ###
#ifndef SDL_MAIN_HANDLED
#   define SDL_MAIN_HANDLED
#endif

#ifndef NULL
#   define NULL 0
#endif

#ifndef __FILENAME__
#   ifdef _WIN32
#       define __FILENAME__ (strrchr("\\" __FILE__, '\\') + 1)
#   endif
#   ifdef __unix__
#       define __FILENAME__ (strrchr("/" __FILE__, '/') + 1)
#   endif
#endif

#ifndef CORE_MAJOR_VERSION
#   define CORE_MAJOR_VERSION 0
#endif

#ifndef CORE_MINOR_VERSION
#   define CORE_MINOR_VERSION 2
#endif

#ifndef CORE_PATCH_VERSION
#   define CORE_PATCH_VERSION 0
#endif
// Core defines

// ### Core includes ###
#include <string>
#include <cstring>
#include <vector>
#include <cstdint>
#include <cassert>

#include "Exceptions.h"
// Core includes

namespace core {

class WindowModule;

class Color;
class IComponent;
class Core;
class CoreConfig;
class Degree;
class EngineLoop;
class Entity;
class Event;
class EventDispatcher;
class FileSystem;
class IModule;
class IModuleContainer;
class Renderer;
class ITicker;
class IWindowRenderer;
class Logger;
class Log;
class Math;
class Mesh;
class Model;
class ModelImporter;
class Object;
class Primitive;
class Quaternion;
class Radian;
class ScriptBehaviour;
class Shader;
class Window;
class WindowBuilder;

// Core Module classes
class WindowModule;
class EngineModule;
class SceneModule;
class InputModule;
class IRenderModule;

// DERendeModule
class DERenderModule;

// Core Components classes
class Camera;
class Transform;
template<typename T> class Script;

template<int cols, int rows, typename T> class Matrix;
template<int dims, typename T> class Vector;
template<typename T> class Pool;
template<typename T> class Node;
template<typename T> class Singleton;
template<typename T> class Instantiable;
template<typename T> class TypeMap;
template <class T, class D> class ModuleContainer;

typedef std::string string;
typedef uint32_t rgba;
typedef uint32_t abgr;

typedef struct Cube Cube;
typedef struct Rect Rect;
typedef struct Vertex Vertex;
typedef struct ColorVertex ColorVertex;
typedef struct ColorVertex2 ColorVertex2;

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

/// Defined by CORE_HEAVY_ESSENTIALS option in CMakeLists.txt
#ifdef CORE_HEAVY_ESSENTIALS
#include "Matrix.h"
#include "Vector.h"
#endif


#endif //CORE_ESSENTIAL_H
