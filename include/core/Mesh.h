#ifndef CORE_MESH_H
#define CORE_MESH_H

#include "Essential.h"

#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/Shaders/VertexColorGL.h>
#include <Magnum/MeshTools/Compile.h>
#include <Magnum/Trade/MeshData.h>
#include <Magnum/Math/Color.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/GL/Buffer.h>

using namespace Magnum;
namespace core {

class Mesh {
public:
    Mesh();

    GL::Mesh* GetGLMesh();

protected:

    GL::Mesh   mesh;

    GL::Buffer vertices;
    GL::Buffer indices;
};


} // namespace core

#endif //CORE_MESH_H
