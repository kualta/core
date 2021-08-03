#include <core/Model.h>
#include <core/Logger.h>

namespace core {

Model::Model(const string &file) {
    const aiScene* scene = ModelImporter::importer.ReadFile(file, aiProcess_Triangulate
                                                 | aiProcess_OptimizeMeshes
                                                 | aiProcess_GenNormals
                                                 | aiProcess_CalcTangentSpace);
    if ( !scene ) {
        Logger::Log(IMPORT, ERR_HERE) << ModelImporter::importer.GetErrorString();
        throw core::bad_file(ModelImporter::importer.GetErrorString());
    }
    // FIXME: change to new Mesh
//    mesh = new BgfxMesh(scene->mMeshes[0]);
    shader = new Shader("shaders/dx11/vs_cubes.bin", "shaders/dx11/fs_cubes.bin");
}
Model::~Model() {
    delete mesh;
    delete shader;
}

}