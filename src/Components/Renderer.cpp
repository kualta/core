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
#include <core/Components/Renderer.h>
#include <core/Components/Transform.h>
#include <core/Components/Camera.h>
#include <core/Model.h>

namespace core {

Renderer::Renderer(Entity& parent, const shared<Model>& model, const string& name)
: IComponent(parent, name),
  model(model)
{
    parent.assertRequiredComponent<Transform>(this);
    transform = parent.GetComponent<Transform>();
    SetTransformMatrix(transform->GetTransformMatrix());
    transform->OnTransformChange.Subscribe([&](Matrix4& mtx) { SetTransformMatrix(mtx); });
}
void Renderer::Start() {

}
void Renderer::Tick() {

}
void Renderer::Draw() {
    model->Draw();
}
void Renderer::SetProjectionMatrix(Matrix4& mtx) {
    model->SetProjectionMatrix(mtx);
}
void Renderer::SetTransformMatrix(Matrix4& mtx) {
    model->SetTransformMatrix(mtx);
    model->SetNormalMatrix(mtx);
}
void Renderer::SetLight(Light& light) {
    switch (light.GetLightType()) {
        case Point:         model->SetPointLight(light);        break;
        case Directional:   model->SetDirectionalLight(light);  break;
        case Spot: throw std::logic_error("Not yet implemented"); break;
        case Area: throw std::logic_error("Not yet implemented"); break;
    }
}

}