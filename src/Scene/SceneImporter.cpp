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

#include <memory>

namespace core {

unique<Trade::AbstractImporter> SceneImporter::importer { nullptr };

void SceneImporter::InitImporter() {
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
shared<SceneData> SceneImporter::ImportScene(const string& filepath) {
    unique<SceneImporter> sceneImporter = std::make_unique<SceneImporter>();
    
    if (!importer) { sceneImporter->InitImporter(); }
    sceneImporter->OpenFile(filepath);

    shared<SceneData> data = make_shared<SceneData>();
    sceneImporter->ImportChildrenData(*data);
    sceneImporter->ImportObjectData(*data);
    sceneImporter->ImportMaterials(*data);
    sceneImporter->ImportTextures(*data);
    sceneImporter->ImportMeshes(*data);
    importer->close();
    
    return data;
}
void SceneImporter::ImportTextures(SceneData& data) {
    data.textures = std::vector<std::optional<GL::Texture2D>> { importer->textureCount() };
    
    for (uint32_t i = 0; i != importer->textureCount(); ++i) {
        std::optional<Trade::TextureData> textureData = std::optional<Trade::TextureData>(importer->texture(i));
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
        const std::optional<Trade::ImageData2D> imageData = std::optional<Trade::ImageData2D>(importer->image2D(imageID));
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
    data.materials = std::vector<std::optional<Trade::MaterialData>> { importer->materialCount() };
    for (uint32_t i = 0; i != importer->materialCount(); ++i) {
   
        std::optional<Trade::MaterialData> materialData = std::optional<Trade::MaterialData>(importer->material(i));
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
            Logger::Log(IMPORT, INFO) << " | Diffuse texture:   " << (material.hasAttribute(Trade::MaterialAttribute::DiffuseTexture) ? "Yes" : "No");
            Logger::Log(IMPORT, INFO) << " | Specular texture:  " << (material.hasAttribute(Trade::MaterialAttribute::SpecularTexture) ? "Yes" : "No");
            Logger::Log(IMPORT, INFO) << " | Occlusion texture: " << (material.hasAttribute(Trade::MaterialAttribute::OcclusionTexture) ? "Yes" : "No");
            Logger::Log(IMPORT, INFO) << " | Normal texture:    " << (material.hasAttribute(Trade::MaterialAttribute::NormalTexture) ? "Yes" : "No");
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
    data.meshes = std::vector<std::optional<GL::Mesh>> { importer->meshCount() };
    for (uint32_t i = 0; i != importer->meshCount(); ++i) {
        std::optional<Trade::MeshData> meshData = std::optional<Trade::MeshData>(importer->mesh(i));
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
    data.objects = std::vector<unique<Trade::ObjectData3D>> { importer->object3DCount() };
    data.objectNames = std::vector<string> { importer->object3DCount() };
    for (uint32_t i = 0; i != importer->object3DCount(); ++i) {
        unique<Trade::ObjectData3D> objectData = importer->object3D(i);
        string name = importer->object3DName(i);
        if (!objectData) {
            Logger::Log(IMPORT, INFO) << "[" << i << "] Model failed to import, skipping";
            continue;
        }
        Logger::Log(IMPORT, INFO) << "[" << i << "] Model" << importer->object3DName(i);
        
        data.objects[i] = std::move(objectData);
        data.objectNames[i] = name;
    }
}
void SceneImporter::ImportChildrenData(SceneData& data) {
    if (importer->defaultScene() != -1) {
        Logger::Log(IMPORT, INFO) << "Importing Default Scene " << importer->sceneName(importer->defaultScene());
        data.childrenData = std::optional<Trade::SceneData>(importer->scene(importer->defaultScene()));
        if (!data.childrenData) {
            Logger::Log(IMPORT, ERR_HERE) << "Children data failed to load";
            throw std::runtime_error("Cannot load scene, Children data failed to load");
        }
    }
}
GL::TextureFormat SceneImporter::GetTextureFormat(PixelFormat pixelFormat) {
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