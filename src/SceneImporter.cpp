#include <core/SceneImporter.h>
#include <core/Components/Transform.h>
#include <core/Components/Renderer.h>
#include <Corrade/Containers/PointerStl.h>
#include <core/Logger.h>

#include <memory>

namespace core {

void SceneImporter::LoadImporter() {
    importer = manager.loadAndInstantiate("AnySceneImporter");
    if (!importer) {
        Logger::Log(IMPORT, ERR_HERE) << "Failed to load or instantiate importer";
        throw std::runtime_error("Failed to load or instantiate importer");
    }
    Logger::Log(IMPORT, DEBUG) << "Loaded model importer successfully";
}
SceneData* SceneImporter::ImportScene(const string& filepath) {
    if (!importer) { LoadImporter(); }
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
        Logger::Log(IMPORT, INFO) << "Importing cubeMesh " << i << " " << importer->meshName(i);

        Containers::Optional<Trade::MeshData> meshData = importer->mesh(i);
        if(!meshData || !meshData->hasAttribute(Trade::MeshAttribute::Normal) || meshData->primitive() != MeshPrimitive::Triangles) {
            Logger::Log(IMPORT, WARN_HERE) << "Cannot load the cubeMesh, skipping";
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
void SceneImporter::OpenFile(const string& filepath) {
    if (!importer->openFile(filepath)) {
        Logger::Log(IMPORT, ERR_HERE) << "Failed to open file " << filepath;
        throw std::runtime_error("Failed to open file " + filepath);
    }
    Logger::Log(IMPORT, DEBUG) << "Opened file " << filepath;
}
void SceneImporter::CreateObject(GraphObject* parent, SceneData& data, UnsignedInt id)
{
    Logger::Log(IMPORT, INFO) << "Importing object " << id << " " << importer->object3DName(id);

    Containers::Pointer<Trade::ObjectData3D> objectData = importer->object3D(id);
    if (!objectData) {
        Logger::Log(IMPORT, ERR_HERE) << "Cannot import object, skipping";
        return;
    }

    /* Add the object to the scene and set its transformation */
    Entity* object = new Entity(importer->object3DName(id), parent);
    object->setTransformation(objectData->transformation());
    object->AddComponent<Transform>();

    Model* model;

    /* The object has a cubeMesh and the cubeMesh is loaded */
    if(objectData->instanceType() == Trade::ObjectInstanceType3D::Mesh && objectData->instance() != -1 && data.meshes[objectData->instance()]) {
        const int32_t materialId = dynamic_cast<Trade::MeshObjectData3D*>(objectData.get())->material();

        /* Material not available / not loaded, use a default material */
        if(materialId == -1 || !data.materials[materialId]) {
            model = new Model(std::make_shared<Mesh>(&(*data.meshes[id])), std::make_shared<Shader>(&Shader::coloredShader));

            /* Textured material. If the texture failed to load, again just use a default colored material. */
        } else if(data.materials[materialId]->hasAttribute(Trade::MaterialAttribute::DiffuseTexture)) {
            Containers::Optional<GL::Texture2D>& texture = data.textures[data.materials[materialId]->diffuseTexture()];
            if (texture) {
                model = new Model(std::make_shared<Mesh>(&(*data.meshes[id])), make_shared<Shader>(&Shader::texturedShader));
            } else {
                model = new Model(make_shared<Mesh>(&(*data.meshes[id])), make_shared<Shader>(&Shader::coloredShader));
            }

            /* Color-only material */
        } else {
            model = new Model(make_shared<Mesh>(&(*data.meshes[id])), make_shared<Shader>(&Shader::coloredShader));
        }

        object->AddComponent<Renderer>(model);
    }

    /* Recursively add children */
    for(std::size_t childId : objectData->children())
        CreateObject(object, data, childId);
}
void SceneImporter::ImportObjectsFromScene(SceneData& data) {
    if (data.childrenData) {
        for (uint32_t id : data.childrenData->children3D()) {
            CreateObject(Scene::Get(), data, id);
        }
    } else if (!data.meshes.empty() && data.meshes[0]) {
        Entity* object = new Entity("Entity", Scene::Get());
        Model* model = new Model(make_shared<Mesh>(&(*data.meshes[0])), make_shared<Shader>(&Shader::coloredShader));

        object->AddComponent<Transform>();
        object->AddComponent<Renderer>(model);
    } else {
        Logger::Log(IMPORT, WARN_HERE) << "SceneData does not contain any meshes";
    }
}
void SceneImporter::AddModel(vector<shared<Model>>& models, SceneData& data, uint32_t id) {
    shared<Model> model;

    Logger::Log(IMPORT, INFO) << "Importing object " << id << " " << importer->object3DName(id);
    unique<Trade::ObjectData3D> objectData = importer->object3D(id);
    if (!objectData) {
        Logger::Log(IMPORT, ERR_HERE) << "Cannot import object with id " << id << ", skipping";
        return;
    }

    /* The object has a cubeMesh and the cubeMesh is loaded */
    if(objectData->instanceType() == Trade::ObjectInstanceType3D::Mesh && objectData->instance() != -1 && data.meshes[objectData->instance()]) {
        const Int materialId = dynamic_cast<Trade::MeshObjectData3D*>(objectData.get())->material();

        /* Material not available / not loaded, use a default material */
        if (materialId == -1 || !data.materials[materialId]) {
            model = std::make_shared<Model>(make_shared<Mesh>(&(*data.meshes[objectData->instance()])), std::make_shared<Shader>(&Shader::coloredShader));

            /* Textured material. If the texture failed to load, again just use a default colored material. */
        } else if (data.materials[materialId]->hasAttribute(Trade::MaterialAttribute::DiffuseTexture)) {
            Containers::Optional<GL::Texture2D>& texture = data.textures[data.materials[materialId]->diffuseTexture()];
            if (texture) {
                model = std::make_shared<Model>(make_shared<Mesh>(&(*data.meshes[objectData->instance()])), make_shared<Shader>(&Shader::texturedShader));
            } else {
                model = std::make_shared<Model>(make_shared<Mesh>(&(*data.meshes[objectData->instance()])), make_shared<Shader>(&Shader::coloredShader));
            }
        } else {
            model = std::make_shared<Model>(make_shared<Mesh>(&(*data.meshes[objectData->instance()])), make_shared<Shader>(&Shader::coloredShader));
        }
    }

    models.push_back(std::move(model));

    for(std::size_t childId : objectData->children())
        AddModel(models, data, childId);
}
vector<shared<Model>> SceneImporter::ImportModelsFromScene(SceneData& data) {
    vector<shared<Model>> models;
    if (data.childrenData) {

        for (uint32_t id : data.childrenData->children3D()) {
            AddModel(models, data, id);
        }

    } else if (!data.meshes.empty() && data.meshes[0]) {
        models.push_back(make_shared<Model>(make_shared<Mesh>(&(*data.meshes[0])), make_shared<Shader>(&Shader::coloredShader)));
    } else {
        Logger::Log(IMPORT, WARN_HERE) << "SceneData does not contain any meshes or scene data";
    }

    return models;
}

}