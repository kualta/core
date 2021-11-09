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
#include <Corrade/Containers/OptionalStl.h>
#include <Magnum/Trade/FlatMaterialData.h>
#include <Magnum/Trade/PhongMaterialData.h>
#include <Magnum/Trade/MaterialData.h>
#include <Magnum/Trade/TextureData.h>
#include <Magnum/Trade/ObjectData3D.h>
#include <Magnum/Trade/ImageData.h>
#include <Magnum/GL/Texture.h>
#include <Magnum/PixelFormat.h>
#include <Magnum/ImageView.h>

#include <memory>

namespace core {

SceneImporter::SceneImporter() {
    InitImporter();
}
void SceneImporter::InitImporter() {
    if (importer) { return; }
    
    importer = manager.loadAndInstantiate("AnySceneImporter");
    
    if (!importer) {
        Logger::Log(IMPORT, ERR_HERE) << "Failed to load or instantiate importer";
        throw std::runtime_error("Failed to load or instantiate importer");
    }
    Logger::Log(IMPORT, DEBUG) << "Loaded scene importer successfully";
}
void SceneImporter::OpenFile(const string& filepath) {
    if (!importer->openFile(filepath)) {
        Logger::Log(IMPORT, ERR_HERE) << "Failed to open file " << filepath;
        throw std::runtime_error("Failed to open file " + filepath);
    }
    Logger::Log(IMPORT, DEBUG) << "Opened file " << filepath;
}
void SceneImporter::CloseFile() {
    importer->close();
}
shared<SceneData> SceneImporter::Import(const string& filepath) {
    shared<SceneData> data = make_shared<SceneData>();
    OpenFile(filepath);
    
    ImportChildrenData(*data);
    ImportObjectData(*data);
    ImportMaterials(*data);
    ImportTextures(*data);
    ImportMeshes(*data);
    
    CloseFile();
    return data;
}
void SceneImporter::ImportTextures(SceneData& data) {
    data.textures = vector<optional<GL::Texture2D>> { importer->textureCount() };
    
    for (uint32_t i = 0; i != importer->textureCount(); i++) {
        optional<Trade::TextureData> textureData = optional<Trade::TextureData>(importer->texture(i));
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
        const optional<Trade::ImageData2D> imageData = optional<Trade::ImageData2D>(importer->image2D(imageID));
        const GL::TextureFormat format { imageData->format() };
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
    data.materials = vector<optional<Trade::MaterialData>> { importer->materialCount() };
    for (uint32_t i = 0; i != importer->materialCount(); ++i) {
   
        optional<Trade::MaterialData> materialData = optional<Trade::MaterialData>(importer->material(i));
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
            auto& material = static_cast<Trade::PhongMaterialData&>(*materialData);
            Logger::Log(IMPORT, INFO) << " | Material type: Phong";
            Logger::Log(IMPORT, INFO) << " | Diffuse texture:   " << (material.hasAttribute(Trade::MaterialAttribute::DiffuseTexture)   ? "Yes" : "No");
            Logger::Log(IMPORT, INFO) << " | Specular texture:  " << (material.hasAttribute(Trade::MaterialAttribute::SpecularTexture)  ? "Yes" : "No");
            Logger::Log(IMPORT, INFO) << " | Occlusion texture: " << (material.hasAttribute(Trade::MaterialAttribute::OcclusionTexture) ? "Yes" : "No");
            Logger::Log(IMPORT, INFO) << " | Normal texture:    " << (material.hasAttribute(Trade::MaterialAttribute::NormalTexture)    ? "Yes" : "No");
            data.materials[i] = std::move(material);
        } else if (materialTypes & Trade::MaterialType::Flat) {
            auto& material = static_cast<Trade::FlatMaterialData&>(*materialData);
            Logger::Log(IMPORT, INFO) << " | Material type: Flat";
            Logger::Log(IMPORT, INFO) << " | Texture: " << (material.hasTexture() ? "Yes" : "No");
            data.materials[i] = std::move(material);
        }
    }
}
void SceneImporter::ImportMeshes(SceneData& data) {
    data.meshes = vector<optional<GL::Mesh>> { importer->meshCount() };
    for (uint32_t i = 0; i != importer->meshCount(); ++i) {
        optional<Trade::MeshData> meshData = optional<Trade::MeshData>(importer->mesh(i));
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
void SceneImporter::ImportObjectData(SceneData& data) {
    data.objects = vector<unique<Trade::ObjectData3D>> { importer->object3DCount() };
    data.names = vector<string> { importer->object3DCount() };
    for (uint32_t i = 0; i != importer->object3DCount(); ++i) {
        unique<Trade::ObjectData3D> objectData = importer->object3D(i);
        string name = importer->object3DName(i);
        if (!objectData) {
            Logger::Log(IMPORT, INFO) << "[" << i << "] Model failed to import, skipping";
            continue;
        }
        Logger::Log(IMPORT, INFO) << "[" << i << "] Model" << importer->object3DName(i);
        
        data.objects[i] = std::move(objectData);
        data.names[i] = name;
    }
}
void SceneImporter::ImportChildrenData(SceneData& data) {
    if (importer->defaultScene() != -1) {
        Logger::Log(IMPORT, INFO) << "Importing Default Scene " << importer->sceneName(importer->defaultScene());
        data.children = optional<Trade::SceneData>(importer->scene(importer->defaultScene()));
        if (!data.children) {
            Logger::Log(IMPORT, ERR_HERE) << "Children data failed to load";
            throw std::runtime_error("Cannot load scene, Children data failed to load");
        }
    }
}

}