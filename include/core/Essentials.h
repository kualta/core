/**
 * Forward declarations for Core classes
 */
/*
 MIT License
 
 Copyright (c) 2021 lectroMathew <contact@lectro.moe>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */
#ifndef CORE_ESSENTIALS_H
#define CORE_ESSENTIALS_H

/**     Core defines     */
#ifndef SDL_MAIN_HANDLED
#   define SDL_MAIN_HANDLED
#endif

#ifndef NULL
#   define NULL 0
#endif

#ifndef CORE_MAJOR_VERSION
#   define CORE_MAJOR_VERSION 0
#endif
#ifndef CORE_MINOR_VERSION
#   define CORE_MINOR_VERSION 4
#endif
#ifndef CORE_PATCH_VERSION
#   define CORE_PATCH_VERSION 0
#endif

#ifndef __FILENAME__
#   ifdef _WIN32
#       define __FILENAME__ (strrchr("\\" __FILE__, '\\') + 1)
#   endif
#   ifdef __unix__
#       define __FILENAME__ (strrchr("/" __FILE__, '/') + 1)
#   endif
#endif

/**     Core std includes     */
#include <optional>
#include <cstring>
#include <utility>
#include <cstdint>
#include <cassert>
#include <string>
#include <vector>
#include <memory>

/**     Core std defines     */
namespace core {

template<typename T> using shared = std::shared_ptr<T>;
template<typename T> using unique = std::unique_ptr<T>;
template<typename T> using weak = std::weak_ptr<T>;
using std::make_shared;
using std::make_unique;
using std::optional;
using std::vector;
using std::string;
using std::size_t;

}

/**     Core forward-declarations     */
namespace core {

class Core;
class CoreConfig;
class EngineLoop;
class Entity;
class FileSystem;
class Layer;
class Light;
class Logger;
class LogEntry;
class Mesh;
class Model;
class Object;
class Scene;
class ScriptedBehaviour;
class Shader;
class GUIBehaviour;
class GUIContext;

// Core Module classes
class GUIModule;
class EditorModule;
class ApplicationModule;
class EngineModule;
class SceneModule;
class InputModule;

// Core Components classes
class Camera;
class SceneCamera;
class Renderer;
class Transform;
class Light;
template<typename T> class Script;

// Core interface classes
class IDrawable;
class IComponent;
class IModule;
class ITicker;
class IModuleContainer;

// Core template classes
template<typename T> class Pool;
template<typename T> class Singleton;
template<typename T> class Instantiable;
template<typename T> class TypeMap;
template<class T, class D> class ModuleContainer;
template<typename T> class LayerLinked;

// Core structs
typedef struct Rect Rect;
struct Cube;
struct Sphere;
struct Cone;
struct Cylinder;
struct WireCube;
struct WireSphere;
struct WireCone;
struct WireCylinder;

} // namespace core

#endif //CORE_ESSENTIALS_H
