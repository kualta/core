#ifndef CORE_BGFXMESH_H
#define CORE_BGFXMESH_H

#include "core/Essential.h"
#include "core/Primitive.h"
#include "IRendererMesh.h"

#include <assimp/mesh.h>
#include <bgfx/bgfx.h>
#include <cstring>

namespace core {

#ifdef CORE_SIMPLIFY_SYNTAX
typedef class BgfxMesh Mesh;
#endif

class BgfxMesh : public IRendererMesh {
public:
    explicit BgfxMesh(aiMesh* aiMesh);
    ~BgfxMesh();

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

    float*    vertexBuffer  { nullptr };
    uint32_t* indexBuffer   { nullptr };

};

}

#endif //CORE_BGFXMESH_H
