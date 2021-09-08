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

    virtual void Draw();

protected:
    void Tick() override;

    Shader* shader { nullptr };
    Mesh*   mesh   { nullptr };

};

}

#endif //CORE_RENDERER_H
