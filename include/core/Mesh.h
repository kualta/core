#ifndef CORE_MESH_H
#define CORE_MESH_H

#include "Essential.h"
#include "Primitive.h"

#include <assimp/mesh.h>
#include <bgfx/bgfx.h>
#include <cstring>

namespace core {

class Mesh {
public:
    explicit Mesh(aiMesh* aiMesh);
    ~Mesh();
    Mesh(float* vertices, size_t vSize, const uint32_t* indices, size_t iSize);
    Mesh(const std::vector<ColorVertex>& vb, const std::vector<uint16_t>& ib);


    bgfx::VertexBufferHandle CreateVertexBuffer(float* vertices, size_t vSize);
    bgfx::VertexBufferHandle CreateVertexBuffer(const std::vector<ColorVertex>& vb);

    bgfx::IndexBufferHandle CreateIndexBuffer(const uint32_t* indices, size_t iSize);
    bgfx::IndexBufferHandle CreateIndexBuffer(const std::vector<uint16_t>& ib);

    bgfx::VertexBufferHandle vertexBufferHandle { bgfx::kInvalidHandle };
    bgfx::IndexBufferHandle  indexBufferHandle  { bgfx::kInvalidHandle };
    bgfx::VertexLayout       vertexLayout;

    bool isValid();

    size_t indicesAmount   { 0 };
    size_t verticesAmount  { 0 };
    size_t trianglesAmount { 0 };


protected:

    void UpdateBuffers();
    void UpdateIndexBuffer();
    void UpdateVertexBuffer();

    // TO BE MOVED TO Memory TODO
    template<typename T>
    const bgfx::Memory* AllocAndCopy(T* buff, size_t buffSize) {
        size_t bufferSize = buffSize * sizeof(T);

        const bgfx::Memory* mem = bgfx::alloc(bufferSize);
        std::memcpy(mem->data, buff, bufferSize);

        return mem;
    };
    // TO BE MOVED TO Memory

    float*    vertices { nullptr };
    uint32_t* indices  { nullptr };


};

}

#endif //CORE_MESH_H
