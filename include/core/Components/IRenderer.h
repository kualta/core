#ifndef CORE_IRENDERER_H
#define CORE_IRENDERER_H

#include "core/Essential.h"
#include "core/IComponent.h"
#include "core/Instantiable.h"
#include "core/Modules/BgfxMesh.h"
#include "core/Shader.h"

namespace core {

class IRenderer : public IComponent, public Instantiable<IRenderer> {
protected:
    IRenderer(Entity& parent,
              Shader* shaderPtr,
              BgfxMesh* meshPtr,
              const string& name = "Renderer");

    IRenderer(Entity& parent,
              Model* modelPtr,
              const string& name = "Renderer");

    void Tick() override;

    virtual void Draw() = 0;

    core::BgfxMesh*      mesh      {nullptr };
    core::Shader*    shader    { nullptr };

};

}

#endif //CORE_IRENDERER_H
