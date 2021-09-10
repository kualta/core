#include <core/ModelImporter.h>
#include <core/Math.h>
#include <core/Logger.h>

namespace core {

PluginManager::Manager<Trade::AbstractImporter> ModelImporter::manager { };
Containers::Pointer<Trade::AbstractImporter> ModelImporter::importer { };

Containers::Array<Containers::Optional<GL::Mesh>> ModelImporter::meshes;
Containers::Array<Containers::Optional<GL::Texture2D>> ModelImporter::textures;

ModelImporter::ModelImporter() {
    LoadImporter();
}
void ModelImporter::AddObject(Trade::AbstractImporter &importer,
                              Containers::ArrayView<const Containers::Optional<Trade::PhongMaterialData>> materials,
                              Object3D &parent,
                              UnsignedInt i)
{
    Logger::Log(IMPORT, INFO) << "Importing object" << i << importer.object3DName(i);
    Containers::Pointer<Trade::ObjectData3D> objectData = importer.object3D(i);
    if (!objectData) {
        Logger::Log(IMPORT, ERR_HERE) << "Cannot import object, skipping";
        return;
    }

    /* Add the object to the scene and set its transformation */
    auto* object = new Object3D { &parent };
    object->setTransformation(objectData->transformation());

    /* Add a drawable if the object has a mesh and the mesh is loaded */
    if(objectData->instanceType() == Trade::ObjectInstanceType3D::Mesh && objectData->instance() != -1 && meshes[objectData->instance()]) {
        const Int materialId = static_cast<Trade::MeshObjectData3D*>(objectData.get())->material();

        /* Material not available / not loaded, use a default material */
        if(materialId == -1 || !materials[materialId]) {
            new ColoredDrawable { *object, Shader::coloredShader, *meshes[objectData->instance()], 0xffffff_rgbf, Scene::drawables };

            /* Textured material. If the texture failed to load, again just use a default colored material. */
        } else if(materials[materialId]->hasAttribute(Trade::MaterialAttribute::DiffuseTexture)) {
            Containers::Optional<GL::Texture2D>& texture = textures[materials[materialId]->diffuseTexture()];
            if(texture)
                new TexturedDrawable { *object, Shader::texturedShader, *meshes[objectData->instance()], *texture, Scene::drawables };
            else
                new ColoredDrawable { *object, Shader::coloredShader, *meshes[objectData->instance()], 0xffffff_rgbf, Scene::drawables };

            /* Color-only material */
        } else {
            new ColoredDrawable { *object, Shader::coloredShader, *meshes[objectData->instance()], materials[materialId]->diffuseColor(), Scene::drawables };
        }
    }

    /* Recursively add children */
    for(std::size_t id: objectData->children())
        AddObject(importer, materials, *object, id);
}
void ModelImporter::LoadImporter() {
    importer = manager.loadAndInstantiate("AnySceneImporter");
    if (!importer) {
        Logger::Log(IMPORT, ERR_HERE) << "Failed to load or instantiate importer";
        throw std::runtime_error("Failed to load or instantiate importer");
    }
    Logger::Log(IMPORT, INFO) << "Loaded model importer successfully";
}
void ModelImporter::LoadModel(const string& filepath) {
    if (!importer) { LoadImporter(); }
    if (!importer->openFile(filepath)) {
        Logger::Log(IMPORT, ERR_HERE) << "Failed to open file " << filepath;
        throw std::runtime_error("Failed to open file " + filepath);
    }
    Logger::Log(IMPORT, INFO) << "Opened file " << filepath;

    textures = Containers::Array<Containers::Optional<GL::Texture2D>>{ importer->textureCount() };
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

        textures[i] = std::move(texture);
    }

    Containers::Array<Containers::Optional<Trade::PhongMaterialData>> materials{ importer->materialCount() };
    for (UnsignedInt i = 0; i != importer->materialCount(); ++i) {
        Logger::Log(IMPORT, INFO) << "Importing material" << i << importer->materialName(i);

        Containers::Optional<Trade::MaterialData> materialData = importer->material(i);
        if (!materialData || !(materialData->types() & Trade::MaterialType::Phong)) {
            Logger::Log(IMPORT, WARN) << "Cannot load material, skipping";
            continue;
        }

        materials[i] = std::move(static_cast<Trade::PhongMaterialData&>(*materialData));
    }

    if (importer->defaultScene() != -1) {
         Logger::Log(IMPORT, INFO) << "Adding default scene " << importer->sceneName(importer->defaultScene());

        Containers::Optional<Trade::SceneData> sceneData = importer->scene(importer->defaultScene());
        if (!sceneData) {
            Logger::Log(IMPORT, ERR_HERE) << "Cannot load scene";
            return;
        }

        /* Recursively add all children */
        for (UnsignedInt objectId: sceneData->children3D())
            AddObject(*importer, materials, Scene::manipulator, objectId);

        /* The format has no scene support, display just the first loaded mesh with
           a default material and be done with it */
    } else if (!meshes.empty() && meshes[0])
        new ColoredDrawable { Scene::manipulator, Shader::coloredShader, *meshes[0], 0xffffff_rgbf, Scene::drawables };
}

}