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
#ifndef CORE_RENDERER_H
#define CORE_RENDERER_H

#include <core/Essentials.h>
#include <core/Instantiable.h>
#include <core/IComponent.h>
#include <core/IDrawable.h>
#include <core/Shader.h>

namespace core {

/**
 * Manages Model for draw
 */
class Renderer : public IComponent, public IDrawable {
public:
    Renderer(Entity& parent,
             const shared<Model>& model,
             const string& name = "Renderer");

protected:

    /**
     * Draws attached Model
     * calculates transform matrix based on attached Transfrom component values,
     * uses provided projMtx as projection matrix
     * @param camera - projection matrix
     */
    void Draw() override;

    /**
     * Sets provided projection matrix as current on attached Model
     */
    void SetProjectionMatrix(Matrix4& mtx) override;
    
    /**
     * Sets provided transformation matrix as current on attached Model
     */
    void SetTransformMatrix(Matrix4& mtx) override;
    
    /**
     * Sets provided Light as current on attached Model
     */
    void SetLight(Light& light) override;

    /** Managed Model */
    shared<Model>   model;
    
    /** Sibling Transform */
    Transform*      transform { nullptr };

};

}

#endif //CORE_RENDERER_H
