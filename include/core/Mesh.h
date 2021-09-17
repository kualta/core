#ifndef CORE_MESH_H
#define CORE_MESH_H

#include "Essentials.h"

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
    Mesh(GL::Mesh&& glMesh);

    GL::Mesh* GetGLMesh();

protected:

    GL::Mesh mesh;

};


} // namespace core

#endif //CORE_MESH_H
