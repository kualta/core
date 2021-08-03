#ifndef CORE_IRENDERER_H
#define CORE_IRENDERER_H

#include <core/Essential.h>
#include <core/Instantiable.h>
#include <core/IComponent.h>
#include <core/IMesh.h>
#include <core/Shader.h>

namespace core {

class IRenderer : public IComponent, public Instantiable<IRenderer> {
protected:
    IRenderer(Entity& parent,
              Shader* shaderPtr,
              const string& name = "Renderer");

    IRenderer(Entity& parent,
              Model* modelPtr,
              const string& name = "Renderer");

    void Tick() override;

    virtual void Draw() = 0;

    core::Shader* shader { nullptr };

};

}

#endif //CORE_IRENDERER_H
