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
#include <core/Scene/SceneData.h>
#include <core/Components.h>
#include <core/Model.h>

#include <Corrade/Containers/PointerStl.h>
#include <Magnum/Trade/ObjectData3D.h>
#include <Magnum/Trade/MeshObjectData3D.h>

namespace core {

vector<shared<Entity>> SceneData::ImportEntities() {
    vector<shared<Entity>> container;
    if (children) {
        for (uint32_t id : children->children3D()) {
            SceneData::AddEntity(container, Scene::GetCurrent()->Root(), id);
        }
    } else if (!meshes.empty() && meshes[0]) {
        SceneData::AddEntity(container, Scene::GetCurrent()->Root(), 0);
    } else {
        Logger::Log(IMPORT, WARN_HERE) << "SceneData does not contain any meshes";
    }
    
    return container;
}
vector<shared<Model>> SceneData::ImportModels(){
    vector<shared<Model>> container;
    if (children) {
        for (uint32_t id : children->children3D()) {
            SceneData::AddModel(container, id);
        }
    } else if (!meshes.empty() && meshes[0]) {
        SceneData::AddModel(container, 0);
    } else {
        Logger::Log(IMPORT, WARN_HERE) << "SceneData does not contain any meshes or SceneData";
    }
    
    return container;
}
void SceneData::AddEntity(vector<shared<Entity>>& container, const shared<Entity>& parent, uint32_t id) {
    Logger::Log(IMPORT, INFO) << "[" << id << "] Entity " << names[id];
    
    shared<Entity> entity = make_shared<Entity>(names[id], parent);
    entity->AddComponent<Transform>();
    entity->AddComponent<Renderer>(SceneData::LoadModel(id));
    
    entity->GetComponent<Transform>()->SetPosition(objects[id]->transformation().translation());
    entity->GetComponent<Transform>()->SetRotation(Quaternion::fromMatrix(objects[id]->transformation().rotation()));
    entity->GetComponent<Transform>()->SetScale(objects[id]->transformation().scaling());
    
    container.push_back(entity);
    
    /* Recursively add children */
    for (size_t childID : objects[id]->children()) {
        AddEntity(container, entity, childID);
    }
}
void SceneData::AddModel(vector<shared<Model>>& container, uint32_t id) {
    Logger::Log(IMPORT, INFO) << "[" << id << "] Model" << names[id];
    
    container.push_back(SceneData::LoadModel(id));
    
    for (size_t childID : objects[id]->children()) {
        SceneData::AddModel(container, childID);
    }
}
shared<Model> SceneData::LoadModel(uint32_t id) {
    shared<Material> material = make_shared<Material>();
    const unique<Trade::ObjectData3D>& object = objects[id];
    
    if (object->instanceType() == Trade::ObjectInstanceType3D::Mesh && id != -1 && meshes[id]) {
        const int32_t materialID = dynamic_cast<const Trade::MeshObjectData3D*>(object.get())->material();
        
        if (materialID != -1 && materials[materialID]) {
            SceneData::SetTextures(material, materialID);
        }
    }
    
    return make_shared<Model>(make_shared<Mesh>(&(*meshes[id])), Shader::standard, material);
}
void SceneData::SetTextures(const shared<Material>& material, uint32_t id) {
    auto& sceneMaterial = static_cast<const Trade::PhongMaterialData&>(*materials[id]);
    
    if (materials[id]->hasAttribute(Trade::MaterialAttribute::DiffuseTexture)) {
        auto& diffuseTexture = textures[sceneMaterial.diffuseTexture()];
        if (diffuseTexture) {
            material->SetDiffuseTexture(make_shared<Texture>(&*diffuseTexture));
        } else {
            Logger::Log(IMPORT, WARN) << "Failed to set diffuse texture of " << id << " material";
        }
    }
    if (materials[id]->hasAttribute(Trade::MaterialAttribute::SpecularTexture)) {
        auto& specularTexture = textures[sceneMaterial.specularTexture()];
        if (specularTexture) {
            material->SetSpecularTexture(make_shared<Texture>(&*specularTexture));
        } else {
            Logger::Log(IMPORT, WARN) << "Failed to set specular texture of " << id << " material";
        }
    }
    if (materials[id]->hasAttribute(Trade::MaterialAttribute::NormalTexture)) {
        auto& normalTexture = textures[sceneMaterial.normalTexture()];
        if (normalTexture) {
            material->SetNormalTexture(make_shared<Texture>(&*normalTexture));
        } else {
            Logger::Log(IMPORT, WARN) << "Failed to set normal texture of " << id << " material";
        }
    }
    if (materials[id]->hasAttribute(Trade::MaterialAttribute::AmbientTexture)) {
        auto& ambientTexture = textures[sceneMaterial.ambientTexture()];
        if (ambientTexture) {
            material->SetAmbientTexture(make_shared<Texture>(&*ambientTexture));
        } else {
            Logger::Log(IMPORT, WARN) << "Failed to set ambient texture of " << id << " material";
        }
    }
}

}
