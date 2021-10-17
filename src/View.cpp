#include <core/View.h>
#include <Magnum/GL/DefaultFramebuffer.h>
#include <core/Logger.h>
#include "Magnum/GL/Renderer.h"
#include "Magnum/GL/AbstractFramebuffer.h"

namespace core {

View::View(const string& name, Vector2i pos, Vector2i size)
: Object(name + " view"),
  frameBuffer(GL::Framebuffer { { { 0, 0 }, size } } ),
  colorBuffer(GL::Renderbuffer { }),
  depthStencil(GL::Renderbuffer { }),
  bufferPos(pos),
  bufferSize(size)
{
    Resize(pos, size);
}
View::View(NoCreateT)
: Object("Uninitialized View"),
  frameBuffer(NoCreate),
  colorBuffer(NoCreate),
  depthStencil(NoCreate)
{

}
void View::Resize(Vector2i pos, Vector2i size) {
    bufferPos = pos;
    bufferSize = size;

    colorBuffer.setStorage(GL::RenderbufferFormat::RGBA8, bufferSize);
    depthStencil.setStorage(GL::RenderbufferFormat::Depth24Stencil8, bufferSize);

    frameBuffer = GL::Framebuffer{ { { 0, 0 }, bufferSize } };
    frameBuffer.attachRenderbuffer(GL::Framebuffer::ColorAttachment { 0 }, colorBuffer);
    frameBuffer.attachRenderbuffer(GL::Framebuffer::BufferAttachment::DepthStencil, depthStencil);

    OnResize.Trigger(frameBuffer.viewport().size());
}
void View::Bind() {
    frameBuffer
            .clear(GL::FramebufferClear::Color | GL::FramebufferClear::Depth)
            .bind();
}
void View::Blit() {
    // FIXME: Refactoring needed, this could be done better
    Vector2i oglPosition = Vector2i { bufferPos.x(), GL::defaultFramebuffer.viewport().size().y() - bufferPos.y() };
    GL::Framebuffer::blit(frameBuffer,
                          GL::defaultFramebuffer,
                          { { 0, 0 }, bufferSize },
                          { oglPosition - (bufferSize * Vector2i { -1, 1 } ), oglPosition },
                          GL::FramebufferBlit::Color | GL::FramebufferBlit::Depth | GL::FramebufferBlit::Stencil,
                          GL::FramebufferBlitFilter::Nearest);
}
GL::Framebuffer& View::GetFrameBuffer() {
    return frameBuffer;
}

}