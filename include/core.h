#ifndef CORE_H
#define CORE_H

// FIXME: DEPRECATED HEADER, TO BE DELETED

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
//#include <SDL.h>
//#include <SDL_syswm.h>

//      core
/// Headers included in dependecy order
#include "core/Essential.h"
#include "core/Vector.h"
#include "core/Singleton.h"
#include "core/Node.h"
#include "core/Pool.h"
#include "core/Entity.h"
#include "core/Object.h"
#include "core/Color.h"
#include "core/Geometry.h"
#include "core/Matrix.h"
#include "core/Primitive.h"
#include "core/Logger.h"
#include "core/Math.h"
#include "core/Core.h"

// FIXME: DEPRECATED HEADER, TO BE DELETED

#endif //CORE_H
