#include <core/Scene/SceneView.h>
#include <core/Logger.h>
#include "Magnum/GL/Renderer.h"
#include "Magnum/GL/AbstractFramebuffer.h"

namespace core {

Magnum::GL::Framebuffer SceneView::framebuffer { NoCreate };
Shaders::FlatGL2D SceneView::shader { NoCreate };
GL::Renderbuffer SceneView::color { NoCreate };
GL::Renderbuffer SceneView::depthStencil { NoCreate };
Vector2i SceneView::bufferPos   { 0, 0 };
Vector2i SceneView::bufferSize  { 100, 1000 };

SceneView::SceneView() {

}
SceneView::SceneView(Vector2i pos, Vector2i size) {
    bufferPos = pos;
    bufferSize = size;

    color = GL::Renderbuffer { };
    depthStencil = GL::Renderbuffer { };
    shader = Shaders::FlatGL2D { Shaders::FlatGL2D::Flag::Textured };

    Resize(pos, size);
}
void SceneView::Resize(Vector2i pos, Vector2i size) {
    bufferPos = pos;
    bufferSize = size;

    color.setStorage(GL::RenderbufferFormat::RGBA8, bufferSize);
    depthStencil.setStorage(GL::RenderbufferFormat::Depth24Stencil8, bufferSize);

    framebuffer = GL::Framebuffer{ { {0, 0}, bufferSize } };
    framebuffer.attachRenderbuffer(GL::Framebuffer::ColorAttachment { 0 }, color);
    framebuffer.attachRenderbuffer(GL::Framebuffer::BufferAttachment::DepthStencil, depthStencil);
}
void SceneView::BindBuffer() {
    if (framebuffer.id() == 0) {
        Logger::Log(RENDER, ERR_HERE) << "Cannot bind uninitialized framebuffer";
        throw std::runtime_error("Cannot bind uninitialized framebuffer");
    }

    framebuffer
        .clear(GL::FramebufferClear::Color | GL::FramebufferClear::Depth)
        .bind();
}
void SceneView::BindColor() {
    if (shader.id() == 0) {
        Logger::Log(RENDER, ERR_HERE) << "Cannot bind uninitialized shader";
        throw std::runtime_error("Cannot bind uninitialized shader");
    }

    // FIXME: Refactoring needed, this could be done better
    Vector2i oglPosition = Vector2i{bufferPos.x(), GL::defaultFramebuffer.viewport().size().y() - bufferPos.y()};
    GL::Framebuffer::blit(framebuffer,
                          GL::defaultFramebuffer,
                          { { 0, 0 }, bufferSize },
                          { oglPosition - (bufferSize * Vector2i{-1, 1}), oglPosition },
                          GL::FramebufferBlit::Color,
                          GL::FramebufferBlitFilter::Nearest);
}
GL::Framebuffer& SceneView::GetFrameBuffer() {
    return framebuffer;
}

}