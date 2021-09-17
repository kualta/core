#ifndef CORE_SCENEIMPORTER_H
#define CORE_SCENEIMPORTER_H

#include "Essentials.h"
#include "SceneData.h"
#include "Importer.h"
#include "Shader.h"
#include "Entity.h"
#include "Model.h"

using namespace Magnum;
namespace core {

class SceneImporter : public Importer {
public:

    /**
     * Imports and returns pointer to core::SceneData
     * @param filepath - path to scene file
     * @return core::SceneData* data
     */
    SceneData* ImportScene(const string& filepath);

    void CreateObject(GraphObject* parent, SceneData& data, UnsignedInt id);
    void ImportObjectsFromScene(SceneData& data);

protected:

    void LoadImporter();
    void OpenFile(const string& filepath);

    void ImportTextures(SceneData& data);
    void ImportMaterials(SceneData& data);
    void ImportMeshes(SceneData& data);

    Containers::Pointer<Trade::AbstractImporter> importer;

};

}

#endif //CORE_SCENEIMPORTER_H
