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
#include <core/Scene/SceneData.h>
#include <core/Components.h>
#include <core/Model.h>

namespace core {

vector<shared<Entity>> SceneData::ImportEntities() {
    vector<shared<Entity>> container;
    if (childrenData) {
        for (uint32_t id : childrenData->children3D()) {
            SceneData::AddEntity(container, Scene::Get(), id);
        }
    } else if (!meshes.empty() && meshes[0]) {
        shared<Entity> object = make_shared<Entity>("Entity", Scene::Get());
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
    if (childrenData) {
        for (uint32_t id : childrenData->children3D()) {
            AddModel(models, id);
        }
    } else if (!meshes.empty() && meshes[0]) {
        models.push_back(make_shared<Model>(make_shared<Mesh>(&(*meshes[0])), Shader::standard));
    } else {
        Logger::Log(IMPORT, WARN_HERE) << "SceneData does not contain any meshes or SceneData";
    }
    
    return models;
}
void SceneData::AddEntity(vector<shared<Entity>>& container, GraphObject* parent, uint32_t id) {
    Logger::Log(IMPORT, INFO) << "[" << id << "] Entity" << objectNames[id];
    
    shared<Entity> entity = std::make_shared<Entity>(objectNames[id], parent);
    entity->AddComponent<Transform>();
    entity->AddComponent<Renderer>(LoadModel(id));
    entity->setTransformation(objects[id]->transformation());
    container.push_back(std::move(entity));
    
    /* Recursively add children */
    for (std::size_t childId : objects[id]->children()) {
        AddEntity(container, entity.get(), childId);
    }
}
void SceneData::AddModel(vector<shared<Model>>& container, uint32_t id) {
    Logger::Log(IMPORT, INFO) << "[" << id << "] Model" << objectNames[id];
    
    container.push_back(LoadModel(id));
    
    for (std::size_t childId : objects[id]->children()) {
        AddModel(container, childId);
    }
}
shared<Model> SceneData::LoadModel(uint32_t id) {
    shared<Model> model;
    const Containers::Pointer<Trade::ObjectData3D>& object = objects[id];
    if (object->instanceType() == Trade::ObjectInstanceType3D::Mesh && id != -1 && meshes[id]) {
        const int32_t materialID = dynamic_cast<const Trade::MeshObjectData3D*>(object.get())->material();
        
        /* Material not available / not loaded, use a default material */
        if (materialID == -1 || !materials[materialID]) {
            model = make_shared<Model>(make_shared<Mesh>(&(*meshes[id])), Shader::standard, Material::standard);
            
            /* Textured material. If the texture failed to load, use a default material. */
        } else if (materials[materialID]->hasAttribute(Trade::MaterialAttribute::DiffuseTexture)) {
            const Containers::Optional<GL::Texture2D>& texture
                    = textures[static_cast<const Trade::PhongMaterialData&>(*materials[materialID]).diffuseTexture()];
            
            model = texture
                    ? make_shared<Model>(make_shared<Mesh>(&(*meshes[id])), Shader::standard, make_shared<Material>(make_shared<Texture>(&*texture)))
                    : make_shared<Model>(make_shared<Mesh>(&(*meshes[id])), Shader::standard, Material::standard);
        } else {
            model = make_shared<Model>(make_shared<Mesh>(&(*meshes[id])), Shader::standard, Material::standard);
        }
    }
    
    return model;
}

}
