#ifndef CORE_BGFXRENDERER_H
#define CORE_BGFXRENDERER_H

#include <core/Essential.h>
#include <core/Components/IRenderer.h>
#include <core/Modules/BgfxMesh.h>
#include <core/Model.h>
#include <core/Shader.h>

#include <bgfx/bgfx.h>

namespace core {

class BgfxRenderer : public IRenderer {
public:
    BgfxRenderer(Entity& parent,
                 Model* model,
                 uint16_t viewId = 0,
                 const string& name = "Renderer");

    BgfxRenderer(Entity& parent,
                 Shader* shaderPtr,
                 BgfxMesh* meshPtr,
                 uint16_t viewId = 0,
                 const string& name = "Renderer");

    void Draw() override;

protected:
    uint16_t         viewId    { 0 };

};

}

#endif //CORE_BGFXRENDERER_H
