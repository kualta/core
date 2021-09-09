#ifndef CORE_COLOR_H
#define CORE_COLOR_H

#include <Magnum/Math/Color.h>

using namespace Magnum;
namespace core {

typedef Math::Color3<Float> Color3;
typedef Math::Color4<Float> Color4;
typedef Math::Color3<Half> Color3h;
typedef Math::Color4<Half> Color4h;
typedef Math::Color3<UnsignedByte> Color3ub;
typedef Math::Color4<UnsignedByte> Color4ub;
typedef Math::Color3<UnsignedShort> Color3us;
typedef Math::Color4<UnsignedShort> Color4us;

}


#endif //CORE_COLOR_H
