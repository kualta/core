#ifndef CORE_RENDERER_H
#define CORE_RENDERER_H

#include <core/Essential.h>
#include <core/Instantiable.h>
#include <core/Component.h>
#include <core/Mesh.h>
#include <core/Model.h>
#include <core/Shader.h>

#include <bgfx/bgfx.h>

namespace core {

class Renderer : public Component, public Instantiable<Renderer> {
public:
    Renderer(Entity& parent,
             Model* model,
             uint16_t viewId = 0,
             const string& name = "Renderer");
    // TODO: Add default shader so it could be defaulted
    Renderer(Entity& parent,
             Shader* shaderPtr,
             Mesh* geometryPtr,
             uint16_t viewId = 0,
             const string& name = "Renderer");

    void Tick() override;

    void Draw();

protected:
    uint16_t         viewId    { 0 };
    core::Model*     model     { };
    core::Mesh*      mesh      { };
    core::Shader*    shader    { nullptr };

};

}

#endif //CORE_RENDERER_H
