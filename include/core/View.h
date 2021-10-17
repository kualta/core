#ifndef CORE_VIEW_H
#define CORE_VIEW_H

#include "Essentials.h"
#include "Object.h"
#include "Math.h"
#include "Event.h"

#include <Magnum/GL/Renderbuffer.h>
#include <Magnum/GL/RenderbufferFormat.h>
#include <Magnum/GL/TextureFormat.h>
#include <Magnum/GL/Framebuffer.h>
#include <Magnum/GL/Texture.h>
#include <Magnum/GL/Buffer.h>

namespace core {

class View : public Object {
public:
    View(const string& name, Vector2i pos = { }, Vector2i size = { });
    View(NoCreateT);

    Event<Vector2i> OnResize;

    /** Copying is not allowed */
    View(const View&) = delete;

    /** Move constuctor */
    View(View&&) = default;

    void Bind();
    void Blit();
    void Resize(Vector2i pos, Vector2i size);
    GL::Framebuffer& GetFrameBuffer();

    /** Move assignment */
    View& operator=(View&&) noexcept = default;

    /** Copying is not allowed */
    View& operator=(const View&) = delete;


protected:

    GL::Framebuffer  frameBuffer;
    GL::Renderbuffer colorBuffer;
    GL::Renderbuffer depthStencil;
    Vector2i         bufferPos;
    Vector2i         bufferSize;

};

} // namespace core

#endif //CORE_VIEW_H
