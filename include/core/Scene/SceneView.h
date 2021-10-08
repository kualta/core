#ifndef CORE_SCENEVIEW_H
#define CORE_SCENEVIEW_H

#include "core/Essentials.h"
#include "core/Math.h"
#include "core/Shader.h"

#include <Magnum/GL/Renderbuffer.h>
#include <Magnum/GL/RenderbufferFormat.h>
#include <Magnum/GL/TextureFormat.h>
#include <Magnum/GL/Framebuffer.h>
#include <Magnum/GL/Texture.h>
#include <Magnum/GL/Buffer.h>
#include <Magnum/Shaders/FlatGL.h>

using namespace Magnum;
namespace core {

class SceneView {
public:
    SceneView();
    SceneView(Vector2i pos, Vector2i size);

    static void BindBuffer();
    static void BindColor();
    static void Resize(Vector2i pos, Vector2i size);

    static GL::Framebuffer& GetFrameBuffer();

protected:

    static GL::Framebuffer framebuffer;
    static GL::Renderbuffer color;
    static GL::Renderbuffer depthStencil;
    static Shaders::FlatGL2D shader;
    static Vector2i bufferPos;
    static Vector2i bufferSize;

};

} // namespace core

#endif //CORE_SCENEVIEW_H
