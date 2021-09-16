#ifndef CORE_RENDERER_H
#define CORE_RENDERER_H

#include <core/Essential.h>
#include <core/Instantiable.h>
#include <core/IComponent.h>
#include <core/Shader.h>

namespace core {

class Renderer : public IComponent, public Instantiable<Renderer> {
public:
    Renderer(Entity& parent,
             Model* model,
             const string& name = "Renderer");

    /**
     * Draws attached Model
     * calculates transform matrix based on attached Transfrom component values,
     * uses provided projMtx as projection matrix
     * @param camera - projection matrix
     */
    void Draw(Camera &camera);

protected:
    void Tick() override;

    Model*     model;
    Transform* transform { nullptr };

};

}

#endif //CORE_RENDERER_H
