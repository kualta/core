#include <core/Mesh.h>

namespace core {

GL::Mesh* Mesh::GetGLMesh() {
    return mesh;
}
Mesh::Mesh(GL::Mesh* glMesh)
: mesh(glMesh)
{

}
Mesh::Mesh() {

}

}