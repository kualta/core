#ifndef CORE_IRENDERER_H
#define CORE_IRENDERER_H

#include "Essential.h"
#include "IComponent.h"
#include "Instantiable.h"
#include "Mesh.h"
#include "Shader.h"

namespace core {

class IRenderer : public IComponent, public Instantiable<IRenderer> {
protected:
    // TODO: Add default shader so it could be defaulted
    IRenderer(Entity& parent,
              Shader* shaderPtr,
              Mesh* meshPtr,
              const string& name = "Renderer");

    IRenderer(Entity& parent,
              Model* modelPtr,
              const string& name = "Renderer");

    void Tick() override;

    virtual void Draw() = 0;

    core::Mesh*      mesh      { nullptr };
    core::Shader*    shader    { nullptr };

};

}

#endif //CORE_IRENDERER_H
