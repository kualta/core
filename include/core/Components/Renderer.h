#ifndef CORE_RENDERER_H
#define CORE_RENDERER_H

#include <core/Essential.h>
#include <core/Component.h>
#include <core/Instantiable.h>
#include <core/Shader.h>

#include <bgfx/bgfx.h>
#include <core/Geometry.h>

namespace core {

class Renderer : public Component, public Instantiable<Renderer> {
public:
    // TODO: Add default shader so it could be defaulted
    explicit Renderer(Entity* parent = nullptr,
             Shader* shaderPtr = nullptr,
             Geometry* geometryPtr = nullptr,
             uint16_t viewId = 0,
             string name = "Renderer");

    void Draw();

    void Update() override;

protected:
    uint16_t         viewId    { 0 };
    core::Geometry*  geometry  { };
    core::Shader*    shader    { nullptr };

};

}

#endif //CORE_RENDERER_H
