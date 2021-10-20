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
#ifndef CORE_LAYER_H
#define CORE_LAYER_H

#include "Essentials.h"
#include "IDrawable.h"
#include "Instantiable.h"
#include "Object.h"

namespace core {

class Layer : public Object, public IDrawable {
public:
    explicit Layer(const string& name);

    /** Move constructor */
    Layer(Layer&& other) = default;

    /** Copying is not allowed */
    Layer(const Layer& other) = delete;

    static bool LayerExist(const string& name);
    static Layer* CreateNewLayer(const string& name);
    static Layer* Get(const string& name);

    template<typename T>
    void Link(T& obj);

    template<typename T>
    void Unlink(T& obj);

    template<typename T>
    bool IsLinked(T& obj);

    void Draw() override;
    void SetProjectionMatrix(Matrix4& mtx) override;
    void SetTransformMatrix(Matrix4& mtx) override;
    void SetLight(Light& light) override;

protected:
    friend class Camera;

    template<typename T>
    vector<T*>& GetContainerForType();

    std::vector<Entity*> entities;
    std::vector<Camera*> cameras;
    std::vector<Light*>  lights;

private:

    template<typename T>
    void assertSupportedType();


    static std::vector<unique<Layer>> layers;

};

} // namespace core

#include "Layer.tpp"

#endif //CORE_LAYER_H
