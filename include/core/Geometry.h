#ifndef CORE_GEOMETRY_H
#define CORE_GEOMETRY_H

#include <bgfx/bgfx.h>
#include "Essential.h"

namespace core {

class Geometry {
public:
    Geometry();
    Geometry(ColorVertex* verBuf, uint16_t verBufSize, uint64_t* triBuf, uint16_t triBufSize);

    bgfx::VertexBufferHandle vbh { bgfx::kInvalidHandle };
    bgfx::IndexBufferHandle ibh  { bgfx::kInvalidHandle };
    bgfx::VertexLayout vertexLayout;

protected:

    ColorVertex*    verticesBuf  { nullptr };
    uint64_t*       trianglesBuf { nullptr };
    uint16_t        vBufSize     { 0 };
    uint16_t        tBufSize     { 0 };

};

}

#endif //CORE_GEOMETRY_H
