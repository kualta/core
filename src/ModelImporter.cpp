#include <core/ModelImporter.h>
#include <core/Logger.h>

namespace core {

PluginManager::Manager<Trade::AbstractImporter> ModelImporter::manager { };
Containers::Pointer<Trade::AbstractImporter> ModelImporter::importer { };

ModelImporter::ModelImporter() {
    LoadImporter();
}
void ModelImporter::AddObject(Trade::AbstractImporter &importer,
                              Containers::ArrayView<const Containers::Optional<Trade::PhongMaterialData>> materials,
                              ModelImporter::Object3D &parent,
                              UnsignedInt i)
{

}
void ModelImporter::LoadImporter() {
    importer = manager.loadAndInstantiate("AnySceneImporter");
    if (!importer) {
        Logger::Log(IMPORT, ERR_HERE) << "Failed to load and/or instantiate importer";
        throw std::runtime_error("Failed to load and/or instantiate importer");
    }
    Logger::Log(IMPORT, INFO) << "Loaded model importer successfully";
}

}