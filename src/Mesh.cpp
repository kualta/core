#include <core/Mesh.h>

namespace core {

GL::Mesh* Mesh::GetGLMesh() {
    return mesh;
}
Mesh::Mesh(const GL::Mesh* glMesh)
: mesh(const_cast<GL::Mesh*>(glMesh))
{

}

}