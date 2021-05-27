#include <core/Model.h>
#include <core/Logger.h>

namespace core {

Model::Model(const string &file) {
    scene = ModelImporter::importer.ReadFile(file, aiProcess_CalcTangentSpace       |
                                                    aiProcess_Triangulate            |
                                                    aiProcess_JoinIdenticalVertices  |
                                                    aiProcess_SortByPType);
    if ( !scene ) {
        Logger::Log(ASSET, ERR_HERE) << ModelImporter::importer.GetErrorString();
    }
    geometry = new Mesh(scene.);
}
Model::~Model() {
    delete geometry;
}

}