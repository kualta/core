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

    void UpdateVertexLayout(aiMesh *aiMesh);

    void UpdateBuffers(aiMesh* aiMesh);
    void UpdateVertexBuffer(aiMesh* aiMesh);
    void UpdateIndexBuffer(aiMesh* aiMesh);

    void UpdateBufferHandles();
    void UpdateIndexBufferHandle();
    void UpdateVertexBufferHandle();

    float*    positions { nullptr };
    float*    normals   { nullptr };
    float*    uvs       { nullptr };

    float*    vertexBuffer  { nullptr };
    uint32_t* indexBuffer   { nullptr };

};

}

#endif //CORE_MESH_H
