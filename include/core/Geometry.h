#ifndef CORE_GEOMETRY_H
#define CORE_GEOMETRY_H

#include "Essential.h"
#include "Primitive.h"

#include <bgfx/bgfx.h>
#include <cstring>

namespace core {

class Geometry {
public:
    Geometry(std::vector<ColorVertex> vb, std::vector<uint16_t> ib);

    bgfx::VertexBufferHandle CreateVertexBuffer(const std::vector<ColorVertex>& vb) const;
    bgfx::IndexBufferHandle CreateIndexBuffer(const std::vector<uint16_t>& ib) const;

    bgfx::VertexBufferHandle vertexBufferHandle { bgfx::kInvalidHandle };
    bgfx::IndexBufferHandle  indexBufferHandle  { bgfx::kInvalidHandle };
    bgfx::VertexLayout       vertexLayout;

protected:

    std::vector<ColorVertex> verticesBuf;
    std::vector<uint16_t>    trianglesBuf;
};

}

#endif //CORE_GEOMETRY_H
