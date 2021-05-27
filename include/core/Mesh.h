#ifndef CORE_MESH_H
#define CORE_MESH_H

#include "Essential.h"
#include "Primitive.h"

#include <bgfx/bgfx.h>
#include <cstring>

namespace core {

class Mesh {
public:
    Mesh(float* vertices, size_t vSize, const int* indices, size_t iSize);
    Mesh(const std::vector<ColorVertex>& vb, const std::vector<uint16_t>& ib);

    bgfx::VertexBufferHandle CreateVertexBuffer(float* vertices, size_t vSize) const;
    bgfx::VertexBufferHandle CreateVertexBuffer(const std::vector<ColorVertex>& vb) const;

    bgfx::IndexBufferHandle CreateIndexBuffer(const int* indices, size_t iSize) const;
    bgfx::IndexBufferHandle CreateIndexBuffer(const std::vector<uint16_t>& ib) const;

    bgfx::VertexBufferHandle vertexBufferHandle { bgfx::kInvalidHandle };
    bgfx::IndexBufferHandle  indexBufferHandle  { bgfx::kInvalidHandle };
    bgfx::VertexLayout       vertexLayout;

protected:

};

}

#endif //CORE_MESH_H
