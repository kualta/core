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
#ifndef CORE_SCENEIMPORTER_H
#define CORE_SCENEIMPORTER_H

#include "core/Essentials.h"
#include "core/Importer.h"
#include "core/Shader.h"
#include "core/Entity.h"
#include "core/Model.h"
#include "core/Scene/SceneData.h"

using namespace Magnum;
namespace core {

class SceneImporter : public Importer {
public:
    SceneImporter();

    /**
     * Imports and returns pointer to core::SceneData
     * @param filepath - path to scene file
     * @return core::SceneData* data
     */
    shared<SceneData> ImportScene(const string& filepath);
    
protected:
    
    static GL::TextureFormat GetTextureFormat(PixelFormat pixelFormat);
    
    void InitImporter();
    void OpenFile(const string& filepath);
    
    void ImportChildrenData(SceneData& data);
    void ImportObjectData(SceneData& data);
    void ImportMaterials(SceneData& data);
    void ImportTextures(SceneData& data);
    void ImportMeshes(SceneData& data);
    
    unique<Trade::AbstractImporter> importer;
    
};

}

#endif //CORE_SCENEIMPORTER_H
