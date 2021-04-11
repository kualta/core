#ifndef CORE_H
#define CORE_H

//      defines
#define SDL_MAIN_HANDLED
#define NULL 0

//      std
#include <memory>
#include <string>
#include <list>
#include <ostream>
#include <cassert>

//      bgfx
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

//      SDL
#include <SDL.h>
#include <SDL_syswm.h>

//      core
/// Headers included in dependecy order
#include "core/Essential.h"
#include "core/Vector.h"
#include "core/Singleton.h"
#include "core/Node.h"
#include "core/Entity.h"
#include "core/Object.h"
#include "core/Geometry.h"
#include "core/Matrix.h"
#include "core/Primitive.h"
#include "core/Window.h"
#include "core/Logger.h"
#include "core/Math.h"
#include "core/RenderManager.h"
#include "core/WindowBuilder.h"
#include "core/WindowPool.h"
#include "core/Root.h"

#endif //CORE_H
