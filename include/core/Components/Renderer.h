#ifndef CORE_RENDERER_H
#define CORE_RENDERER_H

#include <core/Essentials.h>
#include <core/Instantiable.h>
#include <core/IComponent.h>
#include <core/IDrawable.h>
#include <core/Shader.h>

namespace core {

class Renderer : public IComponent, public ICamDrawable {
public:
    Renderer(Entity& parent,
             const shared<Model>& model,
             const string& name = "Renderer");

    /**
     * Draws attached Model
     * calculates transform matrix based on attached Transfrom component values,
     * uses provided projMtx as projection matrix
     * @param camera - projection matrix
     */
    void Draw(Camera &camera) override;

protected:
    void Tick() override;

    shared<Model>   model;
    Transform*      transform { nullptr };

};

}

#endif //CORE_RENDERER_H
