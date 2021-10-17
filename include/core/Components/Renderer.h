#ifndef CORE_RENDERER_H
#define CORE_RENDERER_H

#include <core/Essentials.h>
#include <core/Instantiable.h>
#include <core/IComponent.h>
#include <core/IDrawable.h>
#include <core/Shader.h>

namespace core {

class Renderer : public IComponent, public IDrawable {
public:
    Renderer(Entity& parent,
             const shared<Model>& model,
             const string& name = "Renderer");


protected:

    void Start() override;
    void Tick() override;

    /**
     * Draws attached Model
     * calculates transform matrix based on attached Transfrom component values,
     * uses provided projMtx as projection matrix
     * @param camera - projection matrix
     */
    void Draw() override;

    void SetProjectionMatrix(Matrix4& mtx) override;
    void SetTransformMatrix(Matrix4& mtx) override;
    void SetLight(Light& light) override;

    shared<Model>   model;
    Transform*      transform { nullptr };

};

}

#endif //CORE_RENDERER_H
