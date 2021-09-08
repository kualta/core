#include <core/Model.h>
#include <core/Logger.h>

namespace core {

Model::~Model() {
    delete mesh;
    delete shader;
}
Model::Model(Mesh* _mesh, Shader* _shader)
: mesh(_mesh), shader(_shader)
{

}
void Model::Draw() {
    shader->Draw(mesh);
}

}