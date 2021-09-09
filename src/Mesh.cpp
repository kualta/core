#include <core/Mesh.h>
#include <core/Logger.h>
#include <Magnum/Primitives/Cube.h>
#include <Magnum/MeshTools/Interleave.h>
#include <Magnum/MeshTools/CompressIndices.h>
#include "Magnum/Shaders/PhongGL.h"

using namespace Math::Literals;
namespace core {

Mesh::Mesh() {
//    Trade::MeshData data;
//    mesh = MeshTools::compile(data);
}
GL::Mesh* Mesh::GetGLMesh() {
    return &mesh;
}

}