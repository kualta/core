#ifndef CORE_SCENEIMPORTER_H
#define CORE_SCENEIMPORTER_H

#include "core/Essentials.h"
#include "SceneData.h"
#include "core/Importer.h"
#include "core/Shader.h"
#include "core/Entity.h"
#include "core/Model.h"

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

    /**
     * Creates entities with models from SceneData
     * @note Each Entity in return vector has Transform and Renderer components added
     * @param sceneData - SceneData to import from
     * @return vector<shared<Entity>>
     */
    vector<shared<Entity>> ImportEntities(const SceneData& sceneData);

    /**
     * Imports models from SceneData
     * @param sceneData - SceneData to import from
     * @return vector<shared<Model>>
     */
    vector<shared<Model>> ImportModels(const SceneData& sceneData);

protected:

    void InitImporter();
    void OpenFile(const string& filepath);
    void ImportChildrenData(SceneData& data);
    void ImportMaterials(SceneData& data);
    void ImportTextures(SceneData& data);
    void ImportMeshes(SceneData& data);
    void AddEntity(vector <shared<Entity>>& container, const SceneData& sceneData, GraphObject* parent, uint32_t id);
    void AddModel(vector<shared<Model>>& container, const SceneData& sceneData, uint32_t id);

    shared<Model> LoadModel(const SceneData& data, const unique<Trade::ObjectData3D>& objectData) const;

    Containers::Pointer<Trade::AbstractImporter> importer;
};

}

#endif //CORE_SCENEIMPORTER_H
