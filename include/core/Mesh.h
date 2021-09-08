#ifndef CORE_MESH_H
#define CORE_MESH_H

#include "Essential.h"

#include <Magnum/GL/Mesh.h>
#include <Magnum/GL/Buffer.h>
#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Shaders/VertexColorGL.h>

using namespace Magnum;
namespace core {

class Mesh {
public:
    Mesh();

    GL::Mesh* GetGLMesh();

protected:

    GL::Buffer buffer;
    GL::Mesh mesh;
};


} // namespace core

#endif //CORE_MESH_H
