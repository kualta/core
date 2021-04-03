#ifndef CORE_H
#define CORE_H

//      defines
#define SDL_MAIN_HANDLED
#define NULL 0

//      std
#include <memory>
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
#include "core/Singleton.h"
#include "core/ObjectId.h"
#include "core/Vector.h"
#include "core/Geometry.h"
#include "core/Window.h"
#include "core/LogManager.h"
#include "core/Math.h"
#include "core/RenderManager.h"
#include "core/WindowBuilder.h"
#include "core/WindowPool.h"
#include "core/Root.h"

#endif //CORE_H
