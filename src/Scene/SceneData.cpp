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

#include <Corrade/Containers/Pointer.h>
#include <Corrade/Containers/Array.h>
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
        shared<Entity> object = make_shared<Entity>("Entity", Scene::GetCurrent()->Root());
        object->AddComponent<Transform>();
        object->AddComponent<Renderer>(make_shared<Model>(make_shared<Mesh>(&(*meshes[0])), Shader::standard));
        
        container.push_back(std::move(object));
    } else {
        Logger::Log(IMPORT, WARN_HERE) << "SceneData does not contain any meshes";
    }
    
    return container;
}
vector<shared<Model>> SceneData::ImportModels(){
    vector<shared<Model>> models;
    if (children) {
        for (uint32_t id : children->children3D()) {
            AddModel(models, id);
        }
    } else if (!meshes.empty() && meshes[0]) {
        models.push_back(make_shared<Model>(make_shared<Mesh>(&(*meshes[0])), Shader::standard));
    } else {
        Logger::Log(IMPORT, WARN_HERE) << "SceneData does not contain any meshes or SceneData";
    }
    
    return models;
}
void SceneData::AddEntity(vector<shared<Entity>>& container, const shared<Entity>& parent, uint32_t id) {
    Logger::Log(IMPORT, INFO) << "[" << id << "] Entity " << names[id];
    
    shared<Entity> entity = make_shared<Entity>(names[id], parent);
    entity->AddComponent<Transform>();
    entity->AddComponent<Renderer>(LoadModel(id));
    
    if (parent && parent->HasComponent<Transform>()) {
        Transform* parentTransform = parent->GetComponent<Transform>();
        entity->GetComponent<Transform>()->SetScale(parentTransform->GetScale());
        entity->GetComponent<Transform>()->SetRotation(parentTransform->GetRotation());
        entity->GetComponent<Transform>()->SetPosition(parentTransform->GetPosition());
    }
    
    if (objects[id]->flags() & Trade::ObjectFlag3D::HasTranslationRotationScaling) {
        entity->GetComponent<Transform>()->Scale(objects[id]->scaling());
        entity->GetComponent<Transform>()->Rotate(objects[id]->rotation());
        entity->GetComponent<Transform>()->Translate(objects[id]->translation());
    } else {
        entity->GetComponent<Transform>()->Scale(objects[id]->transformation().scaling());
        entity->GetComponent<Transform>()->Rotate(Quaternion::fromMatrix(objects[id]->transformation().rotation()));
        entity->GetComponent<Transform>()->Translate(objects[id]->transformation().translation());
    }
    
    container.push_back(entity);
    
    /* Recursively add children */
    for (size_t childID : objects[id]->children()) {
        AddEntity(container, entity, childID);
    }
}
void SceneData::AddModel(vector<shared<Model>>& container, uint32_t id) {
    Logger::Log(IMPORT, INFO) << "[" << id << "] Model" << names[id];
    
    container.push_back(LoadModel(id));
    
    for (size_t childID : objects[id]->children()) {
        AddModel(container, childID);
    }
}
shared<Model> SceneData::LoadModel(uint32_t id) {
    shared<Material> material = make_shared<Material>();
    const unique<Trade::ObjectData3D>& object = objects[id];
    if (object->instanceType() == Trade::ObjectInstanceType3D::Mesh && id != -1 && meshes[id]) {
        const int32_t materialID = dynamic_cast<const Trade::MeshObjectData3D*>(object.get())->material();
        
        if (materialID != -1 && materials[materialID]) {
            SetTextures(material, materialID);
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
