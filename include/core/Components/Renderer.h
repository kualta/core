#ifndef CORE_RENDERER_H
#define CORE_RENDERER_H

#include <core/Essential.h>
#include <core/Component.h>
#include <core/Instantiable.h>

#include <bgfx/bgfx.h>
#include <core/Shader.h>

namespace core {

class Renderer : public Component, public Instantiable<Renderer> {
public:

    void Draw();

protected:
    uint16_t           viewId { 0 };
    std::vector<float> vertices { };
    core::Shader shader;

};

}

#endif //CORE_RENDERER_H
