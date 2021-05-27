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

    bgfx::VertexBufferHandle vertexBufferHandle { bgfx::kInvalidHandle };
    bgfx::IndexBufferHandle  indexBufferHandle  { bgfx::kInvalidHandle };
    bgfx::VertexLayout       vertexLayout;

    bool isValid() const;

    size_t indicesAmount   { 0 };
    size_t verticesAmount  { 0 };
    size_t trianglesAmount { 0 };


protected:

    void UpdateBuffers();
    void UpdateIndexBuffer();
    void UpdateVertexBuffer();
    void UpdateVertexLayout(aiMesh *aiMesh);

    float*    vertices { nullptr };
    uint32_t* indices  { nullptr };


};

}

#endif //CORE_MESH_H
