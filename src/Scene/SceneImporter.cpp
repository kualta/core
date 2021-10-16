#include <core/Scene/SceneImporter.h>
#include <core/Components/Transform.h>
#include <core/Components/Renderer.h>
#include <Corrade/Containers/PointerStl.h>
#include <core/Logger.h>

#include <memory>

namespace core {

vector<shared<Entity>> SceneImporter::ImportEntities(const SceneData& sceneData) {
    vector<shared<Entity>> container;
    if (sceneData.childrenData) {
        for (uint32_t id : sceneData.childrenData->children3D()) {
            AddEntity(container, sceneData, Scene::Get(), id);
        }
    } else if (!sceneData.meshes.empty() && sceneData.meshes[0]) {
        shared<Entity> object = std::make_shared<Entity>("Entity", Scene::Get());
        object->AddComponent<Transform>();
        object->AddComponent<Renderer>(std::make_shared<Model>(make_shared<Mesh>(&(*sceneData.meshes[0])),
                                                               make_shared<Shader>()));
        container.push_back(std::move(object));
    } else {
        Logger::Log(IMPORT, WARN_HERE) << "SceneData does not contain any meshes";
    }

    return container;
}
vector<shared<Model>> SceneImporter::ImportModels(const SceneData& sceneData) {
    vector<shared<Model>> models;
    if (sceneData.childrenData) {
        for (uint32_t id : sceneData.childrenData->children3D()) {
            AddModel(models, sceneData, id);
        }
    } else if (!sceneData.meshes.empty() && sceneData.meshes[0]) {
        models.push_back(make_shared<Model>(make_shared<Mesh>(&(*sceneData.meshes[0])), make_shared<Shader>()));
    } else {
        Logger::Log(IMPORT, WARN_HERE) << "SceneData does not contain any meshes or scene sceneData";
    }

    return models;
}
void SceneImporter::InitImporter() {
    importer = manager.loadAndInstantiate("AnySceneImporter");
    if (!importer) {
        Logger::Log(IMPORT, ERR_HERE) << "Failed to load or instantiate importer";
        throw std::runtime_error("Failed to load or instantiate importer");
    }
    Logger::Log(IMPORT, DEBUG) << "Loaded model importer successfully";
}
void SceneImporter::OpenFile(const string& filepath) {
    if (!importer->openFile(filepath)) {
        Logger::Log(IMPORT, ERR_HERE) << "Failed to open file " << filepath;
        throw std::runtime_error("Failed to open file " + filepath);
    }
    Logger::Log(IMPORT, DEBUG) << "Opened file " << filepath;
}
SceneData* SceneImporter::ImportScene(const string& filepath) {
    if (!importer) { InitImporter(); }
    OpenFile(filepath);

    SceneData* data = new SceneData();
    ImportChildrenData(*data);
    ImportMaterials(*data);
    ImportTextures(*data);
    ImportMeshes(*data);

    return data;
}
void SceneImporter::ImportTextures(SceneData& data) {
    data.textures = Containers::Array<Containers::Optional<GL::Texture2D>> { importer->textureCount() };
    for(UnsignedInt i = 0; i != importer->textureCount(); ++i) {
        Logger::Log(IMPORT, INFO) << "Importing texture" << i << importer->textureName(i);

        Containers::Optional<Trade::TextureData> textureData = importer->texture(i);
        if (!textureData || textureData->type() != Trade::TextureType::Texture2D) {
            Logger::Log(IMPORT, WARN) << "Cannot load texture properties, skipping";
            continue;
        }

        Logger::Log(IMPORT, INFO) << "Importing image " << textureData->image() << importer->image2DName(textureData->image());

        Containers::Optional<Trade::ImageData2D> imageData = importer->image2D(textureData->image());
        GL::TextureFormat format;
        if(imageData && imageData->format() == PixelFormat::RGB8Unorm)
            format = GL::TextureFormat::RGB8;
        else if(imageData && imageData->format() == PixelFormat::RGBA8Unorm)
            format = GL::TextureFormat::RGBA8;
        else {
            Logger::Log(IMPORT, WARN) << "Cannot load texture image, skipping";
            continue;
        }

        GL::Texture2D texture;
        texture
                .setMagnificationFilter(textureData->magnificationFilter())
                .setMinificationFilter(textureData->minificationFilter(), textureData->mipmapFilter())
                .setWrapping(textureData->wrapping().xy())
                .setStorage(Math::log2(imageData->size().max()) + 1, format, imageData->size())
                .setSubImage(0, { }, *imageData)
                .generateMipmap();

        data.textures[i] = std::move(texture);
    }
}
void SceneImporter::ImportMaterials(SceneData &data) {
    data.materials = Containers::Array<Containers::Optional<Trade::PhongMaterialData>> { importer->materialCount() };
    for (UnsignedInt i = 0; i != importer->materialCount(); ++i) {
        Logger::Log(IMPORT, INFO) << "Importing material " << i << " " << importer->materialName(i);

        Containers::Optional<Trade::MaterialData> materialData = importer->material(i);
        if (!materialData || !(materialData->types() & Trade::MaterialType::Phong)) {
            Logger::Log(IMPORT, WARN) << "Cannot load material, skipping";
            continue;
        }

        data.materials[i] = std::move(static_cast<Trade::PhongMaterialData&>(*materialData));
    }
}
void SceneImporter::ImportMeshes(SceneData& data) {
    data.meshes = Containers::Array<Containers::Optional<GL::Mesh>> { importer->meshCount() };
    for(UnsignedInt i = 0; i != importer->meshCount(); ++i) {
        Logger::Log(IMPORT, INFO) << "Importing mesh " << i << " " << importer->meshName(i);

        Containers::Optional<Trade::MeshData> meshData = importer->mesh(i);
        if(!meshData || !meshData->hasAttribute(Trade::MeshAttribute::Normal) || meshData->primitive() != MeshPrimitive::Triangles) {
            Logger::Log(IMPORT, WARN_HERE) << "Cannot load the mesh, skipping";
            continue;
        }

        /* Compile the cubeMesh */
        data.meshes[i] = MeshTools::compile(*meshData);
    }
}
void SceneImporter::ImportChildrenData(SceneData &data) {
    if (importer->defaultScene() != -1) {
        Logger::Log(IMPORT, INFO) << "Importing default scene data" << importer->sceneName(importer->defaultScene());
        data.childrenData = importer->scene(importer->defaultScene());
        if (!data.childrenData) {
            Logger::Log(IMPORT, ERR_HERE) << "Cannot load scene";
            throw std::runtime_error("Cannot load scene");
        }
    }
}
void SceneImporter::AddEntity(vector <shared<Entity>>& container, const SceneData& sceneData, GraphObject* parent, uint32_t id)
{
    Logger::Log(IMPORT, INFO) << "Importing entity " << id << " " << importer->object3DName(id);
    unique<Trade::ObjectData3D> objectData = importer->object3D(id);
    if (!objectData) {
        Logger::Log(IMPORT, ERR_HERE) << "Cannot import entity with id " << id << ", skipping";
        return;
    }

    shared<Entity> entity = std::make_shared<Entity>(importer->object3DName(id), parent);
    entity->AddComponent<Transform>();
    entity->AddComponent<Renderer>(LoadModel(sceneData, objectData));
    entity->setTransformation(objectData->transformation());
    container.push_back(std::move(entity));

    /* Recursively add children */
    for(std::size_t childId : objectData->children())
        AddEntity(container, sceneData, entity.get(), childId);
}
void SceneImporter::AddModel(vector<shared<Model>>& container, const SceneData& sceneData, uint32_t id) {
    Logger::Log(IMPORT, INFO) << "Importing object " << id << " " << importer->object3DName(id);
    unique<Trade::ObjectData3D> objectData = importer->object3D(id);
    if (!objectData) {
        Logger::Log(IMPORT, ERR_HERE) << "Cannot import object with id " << id << ", skipping";
        return;
    }
    container.push_back(LoadModel(sceneData, objectData));

    for(std::size_t childId : objectData->children())
        AddModel(container, sceneData, childId);
}
shared<Model> SceneImporter::LoadModel(const SceneData& data, const unique<Trade::ObjectData3D>& objectData) const {
    shared<Model> model;
    int32_t id = objectData->instance();

    if(objectData->instanceType() == Trade::ObjectInstanceType3D::Mesh && id != -1 && data.meshes[id]) {
        const int32_t materialId = dynamic_cast<Trade::MeshObjectData3D*>(objectData.get())->material();

        /* Material not available / not loaded, use a default material */
        if (materialId == -1 || !data.materials[materialId]) {
            model = std::make_shared<Model>(make_shared<Mesh>(&(*data.meshes[id])), make_shared<Shader>());

            /* Textured material. If the texture failed to load, again just use a default colored material. */
        } else if (data.materials[materialId]->hasAttribute(Trade::MaterialAttribute::DiffuseTexture)) {
            const Containers::Optional<GL::Texture2D>& texture = data.textures[data.materials[materialId]->diffuseTexture()];

            if (texture) {
                model = std::make_shared<Model>(make_shared<Mesh>(&(*data.meshes[id])), make_shared<Shader>());
            } else {
                model = std::make_shared<Model>(make_shared<Mesh>(&(*data.meshes[id])), make_shared<Shader>());
            }
        } else {
            model = std::make_shared<Model>(make_shared<Mesh>(&(*data.meshes[id])), make_shared<Shader>());
        }
    }

    return model;
}

}