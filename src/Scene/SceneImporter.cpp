/*
 MIT License
 
 Copyright (c) 2021 lectroMathew <contact@lectro.moe>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */
#include <core/Scene/SceneImporter.h>
#include <core/Components/Transform.h>
#include <core/Components/Renderer.h>
#include <core/Logger.h>

#include <Corrade/Containers/PointerStl.h>
#include <Magnum/Trade/FlatMaterialData.h>
#include <Magnum/Trade/PhongMaterialData.h>
#include <Magnum/Trade/MaterialData.h>


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
        object->AddComponent<Renderer>(std::make_shared<Model>(make_shared<Mesh>(&(*sceneData.meshes[0])), Shader::standard));
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
        models.push_back(make_shared<Model>(make_shared<Mesh>(&(*sceneData.meshes[0])), Shader::standard));
    } else {
        Logger::Log(IMPORT, WARN_HERE) << "SceneData does not contain any meshes or SceneData";
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
    
    for (uint32_t i = 0; i != importer->textureCount(); ++i) {
        Containers::Optional<Trade::TextureData> textureData = importer->texture(i);
        if (!textureData) {
            Logger::Log(IMPORT, WARN) << "[" << i << "] " << "failed to load, skipping";
            continue;
        } else if (textureData->type() != Trade::TextureType::Texture2D) {
            Logger::Log(IMPORT, WARN_HERE) << "[" << i << "] " << "unsupported texture type, skipping";
            continue;
        }
        Logger::Log(IMPORT, INFO)  << "[" << i << "] Texture " << importer->textureName(i);
        Logger::Log(IMPORT, DEBUG) << " | Filter: "    << (int)textureData->magnificationFilter();
        Logger::Log(IMPORT, DEBUG) << " | Mipmap: "    << (int)textureData->mipmapFilter();
        Logger::Log(IMPORT, DEBUG) << " | Wrapping: "  << (int)textureData->wrapping().x() << 'x'
                                                       << (int)textureData->wrapping().y();
    
        const uint32_t imageID = textureData->image();
        const Containers::Optional<Trade::ImageData2D> imageData = importer->image2D(imageID);
        const GL::TextureFormat format = GetTextureFormat(imageData->format());
        if (!imageData) {
            Logger::Log(IMPORT, WARN_HERE) << " | Image " << imageID << " failed to load, skipping";
            continue;
        }
        Logger::Log(IMPORT, INFO) << " | Image format: " << (int) imageData->format();
    
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
void SceneImporter::ImportMaterials(SceneData& data) {
    data.materials = Containers::Array<Containers::Optional<Trade::MaterialData>> { importer->materialCount() };
    for (uint32_t i = 0; i != importer->materialCount(); ++i) {
        
        Containers::Optional<Trade::MaterialData> materialData = importer->material(i);
        if (!materialData) {
            Logger::Log(IMPORT, WARN) << "[" << i << "] Material failed to load, skipping";
            continue;
        }
        Logger::Log(IMPORT, INFO) << "[" << i << "] Material " << importer->materialName(i);
    
        Trade::MaterialTypes materialTypes = materialData->types();
        if (materialTypes & Trade::MaterialType::PbrSpecularGlossiness
        or  materialTypes & Trade::MaterialType::PbrMetallicRoughness
        or  materialTypes & Trade::MaterialType::PbrClearCoat)
        {
            Logger::Log(IMPORT, WARN_HERE) << "PBR materials not yet implemented!";
        }
        
        if (materialTypes & Trade::MaterialType::Phong) {
            Logger::Log(IMPORT, INFO) << " | Material type: Phong";
            data.materials[i] = std::move(static_cast<Trade::PhongMaterialData&>(*materialData));
        } else if (materialTypes & Trade::MaterialType::Flat) {
            Logger::Log(IMPORT, INFO) << " | Material type: Flat";
            data.materials[i] = std::move(static_cast<Trade::FlatMaterialData&>(*materialData));
        }
    }
}
void SceneImporter::ImportMeshes(SceneData& data) {
    data.meshes = Containers::Array<Containers::Optional<GL::Mesh>> { importer->meshCount() };
    for (uint32_t i = 0; i != importer->meshCount(); ++i) {
        Containers::Optional<Trade::MeshData> meshData = importer->mesh(i);
        if (!meshData) {
            Logger::Log(IMPORT, WARN_HERE) << "[" << i << "] Mesh failed to load, skipping";
            continue;
        }
        if (!meshData->hasAttribute(Trade::MeshAttribute::Normal) || meshData->primitive() != MeshPrimitive::Triangles) {
            Logger::Log(IMPORT, WARN_HERE) << "[" << i << "] Mesh: Cannot deduce normal data, skipping";
            continue;
        }
        Logger::Log(IMPORT, INFO) << "[" << i << "] Mesh " << importer->meshName(i);
    
        data.meshes[i] = MeshTools::compile(*meshData);
    }
}
void SceneImporter::ImportChildrenData(SceneData &data) {
    if (importer->defaultScene() != -1) {
        Logger::Log(IMPORT, INFO) << "Importing Default Scene " << importer->sceneName(importer->defaultScene());
        data.childrenData = importer->scene(importer->defaultScene());
        if (!data.childrenData) {
            Logger::Log(IMPORT, ERR_HERE) << "Children data failed to load";
            throw std::runtime_error("Cannot load scene, Children data failed to load");
        }
    }
}
void SceneImporter::AddEntity(vector <shared<Entity>>& container, const SceneData& sceneData, GraphObject* parent, uint32_t id) {
    unique<Trade::ObjectData3D> objectData = importer->object3D(id);
    if (!objectData) {
        Logger::Log(IMPORT, ERR_HERE)<< "[" << id << "] Entity failed to import, skipping";
        return;
    }
    Logger::Log(IMPORT, INFO) << "[" << id << "] Entity" << importer->object3DName(id);

    shared<Entity> entity = std::make_shared<Entity>(importer->object3DName(id), parent);
    entity->AddComponent<Transform>();
    entity->AddComponent<Renderer>(LoadModel(sceneData, objectData));
    entity->setTransformation(objectData->transformation());
    container.push_back(std::move(entity));

    /* Recursively add children */
    for (std::size_t childId : objectData->children()) {
        AddEntity(container, sceneData, entity.get(), childId);
    }
}
void SceneImporter::AddModel(vector<shared<Model>>& container, const SceneData& sceneData, uint32_t id) {
    unique<Trade::ObjectData3D> objectData = importer->object3D(id);
    if (!objectData) {
        Logger::Log(IMPORT, INFO) << "[" << id << "] Model failed to import, skipping";
        return;
    }
    Logger::Log(IMPORT, INFO) << "[" << id << "] Model" << importer->object3DName(id);
    
    container.push_back(LoadModel(sceneData, objectData));

    for (std::size_t childId : objectData->children()) {
        AddModel(container, sceneData, childId);
    }
}
shared<Model> SceneImporter::LoadModel(const SceneData& data, const unique<Trade::ObjectData3D>& objectData) const {
    shared<Model> model;
    const int32_t id = objectData->instance();
    if (objectData->instanceType() == Trade::ObjectInstanceType3D::Mesh && id != -1 && data.meshes[id]) {
        const int32_t materialID = dynamic_cast<Trade::MeshObjectData3D*>(objectData.get())->material();

        /* Material not available / not loaded, use a default material */
        if (materialID == -1 || !data.materials[materialID]) {
            model = make_shared<Model>(make_shared<Mesh>(&(*data.meshes[id])), Shader::standard, Material::standard);

            /* Textured material. If the texture failed to load, use a default material. */
        } else if (data.materials[materialID]->hasAttribute(Trade::MaterialAttribute::DiffuseTexture)) {
            const Containers::Optional<GL::Texture2D>& texture
            = data.textures[static_cast<const Trade::PhongMaterialData&>(*data.materials[materialID]).diffuseTexture()];

            model = texture
                    ? make_shared<Model>(make_shared<Mesh>(&(*data.meshes[id])), Shader::standard, make_shared<Material>(
                            make_shared<GL::Texture2D>(std::move(const_cast<GL::Texture2D&>(*texture)))))
                    : make_shared<Model>(make_shared<Mesh>(&(*data.meshes[id])), Shader::standard, Material::standard);
        } else {
            model = make_shared<Model>(make_shared<Mesh>(&(*data.meshes[id])), Shader::standard, Material::standard);
        }
    }

    return model;
}
GL::TextureFormat SceneImporter::GetTextureFormat(PixelFormat pixelFormat) const {
    GL::TextureFormat format;
    switch (pixelFormat) {
        case PixelFormat::R8Unorm:      format = GL::TextureFormat::R8; break;
        case PixelFormat::RG8Unorm:     format = GL::TextureFormat::RG8; break;
        case PixelFormat::RGB8Unorm:    format = GL::TextureFormat::RGB8; break;
        case PixelFormat::RGBA8Unorm:   format = GL::TextureFormat::RGBA8; break;
        case PixelFormat::R8Snorm:      format = GL::TextureFormat::R8Snorm; break;
        case PixelFormat::RG8Snorm:     format = GL::TextureFormat::RG8Snorm; break;
        case PixelFormat::RGB8Snorm:    format = GL::TextureFormat::RGB8Snorm; break;
        case PixelFormat::RGBA8Snorm:   format = GL::TextureFormat::RGBA8Snorm; break;
        case PixelFormat::R8Srgb:       format = GL::TextureFormat::SR8; break;
        case PixelFormat::RGB8Srgb:     format = GL::TextureFormat::SRGB8; break;
        case PixelFormat::RGBA8Srgb:    format = GL::TextureFormat::SRGB8Alpha8; break;
        case PixelFormat::R8UI:         format = GL::TextureFormat::R8UI; break;
        case PixelFormat::RG8UI:        format = GL::TextureFormat::RG8UI; break;
        case PixelFormat::RGB8UI:       format = GL::TextureFormat::RGB8UI; break;
        case PixelFormat::RGBA8UI:      format = GL::TextureFormat::RGBA8UI; break;
        case PixelFormat::R8I:          format = GL::TextureFormat::R8I; break;
        case PixelFormat::RG8I:         format = GL::TextureFormat::RG8I; break;
        case PixelFormat::RGB8I:        format = GL::TextureFormat::RGB8I; break;
        case PixelFormat::RGBA8I:       format = GL::TextureFormat::RGBA8I; break;
        case PixelFormat::R16Unorm:     format = GL::TextureFormat::R16; break;
        case PixelFormat::RG16Unorm:    format = GL::TextureFormat::RG16; break;
        case PixelFormat::RGB16Unorm:   format = GL::TextureFormat::RGB16; break;
        case PixelFormat::RGBA16Unorm:  format = GL::TextureFormat::RGBA16; break;
        case PixelFormat::R16Snorm:     format = GL::TextureFormat::R16Snorm; break;
        case PixelFormat::RG16Snorm:    format = GL::TextureFormat::RG16Snorm; break;
        case PixelFormat::RGB16Snorm:   format = GL::TextureFormat::RGB16Snorm; break;
        case PixelFormat::RGBA16Snorm:  format = GL::TextureFormat::RGBA16Snorm; break;
        case PixelFormat::R16UI:        format = GL::TextureFormat::R16UI; break;
        case PixelFormat::RG16UI:       format = GL::TextureFormat::RG16UI; break;
        case PixelFormat::RGB16UI:      format = GL::TextureFormat::RGB16UI; break;
        case PixelFormat::RGBA16UI:     format = GL::TextureFormat::RGBA16UI; break;
        case PixelFormat::R16I:         format = GL::TextureFormat::R16I; break;
        case PixelFormat::RG16I:        format = GL::TextureFormat::RG16I; break;
        case PixelFormat::RGB16I:       format = GL::TextureFormat::RGB16I; break;
        case PixelFormat::RGBA16I:      format = GL::TextureFormat::RGBA16I; break;
        case PixelFormat::R32UI:        format = GL::TextureFormat::R32UI; break;
        case PixelFormat::RG32UI:       format = GL::TextureFormat::RG32UI; break;
        case PixelFormat::RGB32UI:      format = GL::TextureFormat::RGB32UI; break;
        case PixelFormat::RGBA32UI:     format = GL::TextureFormat::RGBA32UI; break;
        case PixelFormat::R32I:         format = GL::TextureFormat::R32I; break;
        case PixelFormat::RG32I:        format = GL::TextureFormat::RG32I; break;
        case PixelFormat::RGB32I:       format = GL::TextureFormat::RGB32I; break;
        case PixelFormat::RGBA32I:      format = GL::TextureFormat::RGBA32I; break;
        case PixelFormat::R16F:         format = GL::TextureFormat::R16F; break;
        case PixelFormat::RG16F:        format = GL::TextureFormat::RG16F; break;
        case PixelFormat::RGB16F:       format = GL::TextureFormat::RGB16F; break;
        case PixelFormat::RGBA16F:      format = GL::TextureFormat::RGBA16F; break;
        case PixelFormat::R32F:         format = GL::TextureFormat::R32F; break;
        case PixelFormat::RG32F:        format = GL::TextureFormat::RG32F; break;
        case PixelFormat::RGB32F:       format = GL::TextureFormat::RGB32F; break;
        case PixelFormat::RGBA32F:      format = GL::TextureFormat::RGBA32F; break;
        case PixelFormat::Depth32F:     format = GL::TextureFormat::DepthComponent32F; break;
        case PixelFormat::Stencil8UI:   format = GL::TextureFormat::StencilIndex8; break;
        case PixelFormat::Depth16Unorm: format = GL::TextureFormat::DepthComponent16; break;
        case PixelFormat::Depth24Unorm: format = GL::TextureFormat::DepthComponent24; break;
        case PixelFormat::Depth24UnormStencil8UI: format = GL::TextureFormat::Depth24Stencil8; break;
        case PixelFormat::Depth32FStencil8UI: format = GL::TextureFormat::Depth32FStencil8; break;
        case PixelFormat::Depth16UnormStencil8UI: throw std::logic_error("Unsupported pixel format"); // VK-speciffic
        case PixelFormat::RG8Srgb: throw std::logic_error("Unsupported pixel format"); // < GL::TextureFormat::SRG8 is not a thing yet, FIXME: Update magnum to upstream
    }
    return format;
}

}