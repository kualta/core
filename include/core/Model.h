/*
 MIT License
 
 Copyright (c) 2021 kualta <contact@kualta.dev>
 
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
#ifndef CORE_MODEL_H
#define CORE_MODEL_H

#include "Essentials.h"
#include "IDrawable.h"
#include "Material.h"
#include "Shader.h"
#include "Mesh.h"
#include "Math.h"

#include "core/Components/Light.h"
#include <core/Components/Camera.h>
#include <core/Components/Transform.h>

namespace core {

class Model : public IDrawable {
public:
    Model(const shared<Mesh>&     mesh,
          const shared<Shader>&   shader = Shader::standard,
          const shared<Material>& material = Material::standard);

    void SetMesh(Mesh& mesh);
    void SetMesh(const shared<Mesh>& mesh);
    void SetShader(Shader& shader);
    void SetShader(const shared<Shader>& shader);
    void SetMaterial(const shared<Material>& material);
    
protected:
    friend class Renderer;
    friend class Layer;
    
    void SetProjectionMatrix(Matrix4& mtx) override;
    void SetTransformMatrix(Matrix4& mtx) override;
    void SetNormalMatrix(Matrix4& mtx);
    
    void SetPointLight(Light& light);
    void SetDirectionalLight(Light& light);
    void SetLight(Light& light);
    
    void Draw();

    shared<Mesh>     mesh;
public:
    const shared<core::Mesh>& GetMesh() const;
    const shared<core::Shader>& GetShader() const;
    const shared<core::Material>& GetMaterial() const;
protected:
    shared<Shader>   shader;
    shared<Material> material;

    GL::Buffer transformUniform;
    GL::Buffer projectionUniform;
    GL::Buffer materialUniform;
    GL::Buffer lightUniform;
    GL::Buffer drawUniform;

};

} // namespace core

#endif //CORE_MODEL_H
