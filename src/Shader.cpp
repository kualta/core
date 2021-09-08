#include <core/Shader.h>

namespace core {

Shader::Shader() {

}
void Shader::Draw(Mesh* mesh) {
    shader.draw(*mesh->GetGLMesh());
}

}