#ifndef CORE_RENDERER_H
#define CORE_RENDERER_H

#include <core/Essential.h>
#include <core/Component.h>
#include <core/Instantiable.h>
#include <core/Shader.h>

#include <bgfx/bgfx.h>

namespace core {

class Renderer : public Component, public Instantiable<Renderer> {
public:
    Renderer(Entity& parent,
             uint16_t viewId = 0,
             float* buf = nullptr,
             Shader* shader = nullptr);

    void Draw();

protected:
    uint16_t        viewId      { 0 };
    float*          verticesBuf { nullptr };
    core::Shader*   shader      { nullptr };

};

}

#endif //CORE_RENDERER_H
