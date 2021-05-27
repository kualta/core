#include <core/Model.h>
#include <core/Logger.h>

namespace core {

Model::Model(const string &file) {
    scene = ModelImporter::importer.ReadFile(file, aiProcess_Triangulate | aiProcess_OptimizeMeshes);
    if ( !scene ) {
        Logger::Log(IMPORT, ERR_HERE) << ModelImporter::importer.GetErrorString();
    }
    mesh = new Mesh(scene->mMeshes[0]);
    shader = new Shader("shaders/dx11/vs_cubes.bin", "shaders/dx11/fs_cubes.bin");
}
Model::~Model() {
    delete mesh;
}

}