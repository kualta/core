#include <core/GUI/GUIContext.h>

#include <Magnum/ImageView.h>
#include <Magnum/GL/Context.h>
#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Extensions.h>
#include <Magnum/GL/PixelFormat.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/GL/Shader.h>
#include <Magnum/GL/TextureFormat.h>
#include "Magnum/ImGuiIntegration/Integration.h"

namespace core {

GUIContext::GUIContext(const Vector2& size, const Vector2i& windowSize, const Vector2i& framebufferSize)
: GUIContext { *ImGui::CreateContext(), size, windowSize, framebufferSize } { }

GUIContext::GUIContext(const Vector2i& size)
: GUIContext { Vector2 { size }, size, size } { }

GUIContext::GUIContext(ImGuiContext& context, const Vector2& size, const Vector2i& windowSize, const Vector2i& framebufferSize)
: context { &context }, shader { Shaders::FlatGL2D::Flag::Textured | Shaders::FlatGL2D::Flag::VertexColor } {
    ImGui::SetCurrentContext(&context);

    ImGuiIO &io = ImGui::GetIO();
    io.KeyMap[ImGuiKey_Tab]        = ImGuiKey_Tab;
    io.KeyMap[ImGuiKey_LeftArrow]  = ImGuiKey_LeftArrow;
    io.KeyMap[ImGuiKey_RightArrow] = ImGuiKey_RightArrow;
    io.KeyMap[ImGuiKey_UpArrow]    = ImGuiKey_UpArrow;
    io.KeyMap[ImGuiKey_DownArrow]  = ImGuiKey_DownArrow;
    io.KeyMap[ImGuiKey_PageUp]     = ImGuiKey_PageUp;
    io.KeyMap[ImGuiKey_PageDown]   = ImGuiKey_PageDown;
    io.KeyMap[ImGuiKey_Home]       = ImGuiKey_Home;
    io.KeyMap[ImGuiKey_End]        = ImGuiKey_End;
    io.KeyMap[ImGuiKey_Delete]     = ImGuiKey_Delete;
    io.KeyMap[ImGuiKey_Backspace]  = ImGuiKey_Backspace;
    io.KeyMap[ImGuiKey_Space]      = ImGuiKey_Space;
    io.KeyMap[ImGuiKey_Enter]      = ImGuiKey_Enter;
    io.KeyMap[ImGuiKey_Escape]     = ImGuiKey_Escape;
    io.KeyMap[ImGuiKey_A]          = ImGuiKey_A;
    io.KeyMap[ImGuiKey_C]          = ImGuiKey_C;
    io.KeyMap[ImGuiKey_V]          = ImGuiKey_V;
    io.KeyMap[ImGuiKey_X]          = ImGuiKey_X;
    io.KeyMap[ImGuiKey_Y]          = ImGuiKey_Y;
    io.KeyMap[ImGuiKey_Z]          = ImGuiKey_Z;

    /* Tell ImGui that changing mouse cursors is supported */
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;

    /* Set up framebuffer sizes, font supersampling etc. and upload the glyph cache */
    Relayout(size, windowSize, framebufferSize);

    mesh.setPrimitive(GL::MeshPrimitive::Triangles);
    mesh.addVertexBuffer(vertexBuffer, 0,
                          Shaders::FlatGL2D::Position { },
                          Shaders::FlatGL2D::TextureCoordinates { },
                          Shaders::FlatGL2D::Color4{ Shaders::FlatGL2D::Color4::DataType::UnsignedByte,
                                                     Shaders::FlatGL2D::Color4::DataOption::Normalized });
    timeline.start();
}

GUIContext::GUIContext(ImGuiContext& context, const Vector2i& size)
: GUIContext { context, Vector2 { size }, size, size } { }

GUIContext::GUIContext(NoCreateT) noexcept
: context      { nullptr  },
  shader       { NoCreate },
  mesh         { NoCreate },
  texture      { NoCreate },
  vertexBuffer { NoCreate },
  indexBuffer  { NoCreate } { }

GUIContext::GUIContext(GUIContext&& other) noexcept
:
context            { other.context                 },
shader             { std::move(other.shader)       },
timeline           { std::move(other.timeline)     },
eventScaling       { other.eventScaling            },
supersamplingRatio { other.supersamplingRatio      },
mesh               { std::move(other.mesh)         },
texture            { std::move(other.texture)      },
vertexBuffer       { std::move(other.vertexBuffer) },
indexBuffer        { std::move(other.indexBuffer)  }
{
    other.context = nullptr;
    /* Update the pointer to texture */
    ImGuiContext* current = ImGui::GetCurrentContext();
    ImGui::SetCurrentContext(context);
    ImGui::GetIO().Fonts->SetTexID(reinterpret_cast<ImTextureID>(&texture));
    ImGui::SetCurrentContext(current);
}

GUIContext::~GUIContext() {
    if (context) {
        /* Ensure we destroy the context we're linked to */
        ImGui::SetCurrentContext(context);
        ImGui::DestroyContext();
    }
}

GUIContext& GUIContext::operator=(GUIContext&& other) noexcept {
    std::swap(context, other.context);
    std::swap(shader, other.shader);
    std::swap(texture, other.texture);
    std::swap(vertexBuffer, other.vertexBuffer);
    std::swap(indexBuffer, other.indexBuffer);
    std::swap(timeline, other.timeline);
    std::swap(mesh, other.mesh);
    std::swap(supersamplingRatio, other.supersamplingRatio);
    std::swap(eventScaling, other.eventScaling);

    /* Update the pointers to texture */
    ImGuiContext* current = ImGui::GetCurrentContext();
    if (context) {
        ImGui::SetCurrentContext(context);
        ImGui::GetIO().Fonts->SetTexID(reinterpret_cast<ImTextureID>(&texture));
    }
    if (other.context) {
        ImGui::SetCurrentContext(other.context);
        ImGui::GetIO().Fonts->SetTexID(reinterpret_cast<ImTextureID>(&other.texture));
    }
    ImGui::SetCurrentContext(current);

    return *this;
}

ImGuiContext* GUIContext::Release() {
    ImGuiContext* oldContext = context;
    context = nullptr;
    return oldContext;
}

void GUIContext::Relayout(const Vector2& size, const Vector2i& windowSize, const Vector2i& framebufferSize) {
    /* Ensure we use the context we're linked to */
    ImGui::SetCurrentContext(context);

    /* If size of the UI is 1024x576 with a 16px font but it's rendered to a
       3840x2160 framebuffer, we need to supersample the font 3,75x to get
       crisp enough look. */
    const Vector2 newSupersamplingRatio = Vector2(framebufferSize) / size;

    /* ImGui unfortunately expects that event coordinates == positioning
       coordinates, which means we have to scale the events like they would be
       related to `size` and not `windowSize`. */
    eventScaling = size / Vector2{windowSize};

    ImGuiIO& io = ImGui::GetIO();

    /* If the supersampling ratio changed, we need to regenerate the font. Do
       that also if the fonts are not loaded yet -- that means these were
       supplied by the user after GUIContext was created (or after last call to
       Relayout()). */
    bool allFontsLoaded = !io.Fonts->Fonts.empty();
    for (auto& font: io.Fonts->Fonts) {
        if (!font->IsLoaded()) {
            allFontsLoaded = false;
            break;
        }
    }
    if (supersamplingRatio != newSupersamplingRatio || !allFontsLoaded) {
        /* Need to use > 0.0f instead of just != 0 so we catch NaNs too */
        const Float nonZeroSupersamplingRatio = (newSupersamplingRatio.x() > 0.0f ? newSupersamplingRatio.x() : 1.0f);

        /* If there's no fonts yet (first run) or only one font and it's the
           one we set earier (has the [SCALED] suffix), wipe it and replace
           with a differently scaled version. Otherwise assume the fonts are
           user-supplied, do not touch them and just rebuild the cache. */
        if (io.Fonts->Fonts.empty() || (io.Fonts->Fonts.size() == 1 && std::strcmp(io.Fonts->Fonts[0]->GetDebugName(), "ProggyClean.ttf, 13px [SCALED]") == 0)) {
            /* Clear all fonts. Can't just replace the default font,
               unfortunately */
            io.Fonts->Clear();

            /* Because ImGui doesn't have native HiDPI support yet, we upscale
               the font for glyph prerendering and then downscale it back for
               the UI */
            ImFontConfig cfg;
            std::strcpy(cfg.Name, "ProggyClean.ttf, 13px [SCALED]");
            cfg.SizePixels = 13.0f * nonZeroSupersamplingRatio;
            io.Fonts->AddFontDefault(&cfg);
        }

        supersamplingRatio = newSupersamplingRatio;

        /* Downscale back the upscaled font to achieve supersampling */
        io.FontGlobalScale = 1.0f / nonZeroSupersamplingRatio;

        unsigned char* pixels;
        int width, height;
        int pixelSize;
        io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height, &pixelSize);
        CORRADE_INTERNAL_ASSERT(width > 0 && height > 0 && pixelSize == 4);

        ImageView2D image { GL::PixelFormat::RGBA,
                            GL::PixelType::UnsignedByte, { width, height },
                            { pixels, std::size_t(pixelSize*width*height) } };

        texture = GL::Texture2D { };
        texture.setMagnificationFilter(GL::SamplerFilter::Linear)
                .setMinificationFilter(GL::SamplerFilter::Linear)
        #ifndef MAGNUM_TARGET_GLES2
                .setStorage(1, GL::TextureFormat::RGBA8, image.size())
                .setSubImage(0, { }, image);
        #else
            .setImage(0, GL::TextureFormat::RGBA, image);
        #endif

        /* Clear texture to save RAM, we have it on the GPU now */
        io.Fonts->ClearTexData();

        /* Make the texture available through the ImFontAtlas */
        io.Fonts->SetTexID(reinterpret_cast<ImTextureID>(&texture));
    }

    /* Display size is the window size. Scaling of this to the actual window
       and framebuffer size is done on the magnum side when rendering. */
    io.DisplaySize = ImVec2(Vector2(size));
    /* io.DisplayFramebufferScale is currently not used by imgui (1.66b), so
       why bother */
}
void GUIContext::Relayout(const Vector2i& size) {
    Relayout(Vector2 { size }, size, size);
}
void GUIContext::NewFrame() {
    /* Ensure we use the context we're linked to */
    ImGui::SetCurrentContext(context);

    timeline.nextFrame();

    ImGuiIO& io = ImGui::GetIO();
    io.DeltaTime = timeline.previousFrameDuration();
    /* Since v1.68 and https://github.com/ocornut/imgui/commit/3c07ec6a6126fb6b98523a9685d1f0f78ca3c40c,
       ImGui disallows zero delta time to "prevent subtle issues".
       Unfortunately that *does* cause subtle issues, especially in combination
       with SDL2 on Windows -- when the window is being dragged across the
       screen, SDL temporarily halts all event processing and then fires all
       pending events at once, causing zero delta time. A bugreport for this
       is opened since 2016 -- https://bugzilla.libsdl.org/show_bug.cgi?id=2077
       but there was nothing done last time I checked (March 2020). More info
       also at https://github.com/mosra/magnum-integration/issues/57 */
    if (ImGui::GetFrameCount() != 0) {
        io.DeltaTime = Math::max(io.DeltaTime, std::numeric_limits<float>::epsilon());
    }

    /* Fire delayed mouse events. This sets MouseDown both in case the press
       happened in this frame but also if both press and release happened at
       the same frame */
    for (const Int buttonId: {0, 1, 2}) {
        io.MouseDown[buttonId] = mousePressed[buttonId] || mousePressedInThisFrame[buttonId];
    }

    ImGui::NewFrame();

    /* It's a new frame, clear any indicators for received mouse presses in
       this frame */
    mousePressedInThisFrame = { };
}

void GUIContext::DrawFrame() {
    /* Ensure we use the context we're linked to */
    ImGui::SetCurrentContext(context);

    ImGui::Render();

    ImGuiIO& io = ImGui::GetIO();
    const Vector2 fbSize = Vector2 { io.DisplaySize } * Vector2 { io.DisplayFramebufferScale };
    if (!fbSize.product()) return;

    ImDrawData* drawData = ImGui::GetDrawData();
    CORRADE_INTERNAL_ASSERT(drawData); /* This is always valid after Render() */
    drawData->ScaleClipRects(io.DisplayFramebufferScale);

    const Matrix3 projection =
              Matrix3::translation( { -1.0f, 1.0f } )
            * Matrix3::scaling( { 2.0f / Vector2(io.DisplaySize) } )
            * Matrix3::scaling( { 1.0f, -1.0f } );
    shader.setTransformationProjectionMatrix(projection);

    for (std::int_fast32_t n = 0; n < drawData->CmdListsCount; ++n) {
        const ImDrawList* cmdList = drawData->CmdLists[n];
        ImDrawIdx indexBufferOffset = 0;

        vertexBuffer.setData( { cmdList->VtxBuffer.Data, std::size_t(cmdList->VtxBuffer.Size) }, GL::BufferUsage::StreamDraw);
        indexBuffer.setData( { cmdList->IdxBuffer.Data, std::size_t(cmdList->IdxBuffer.Size) }, GL::BufferUsage::StreamDraw);

        for(std::int_fast32_t c = 0; c < cmdList->CmdBuffer.Size; ++c) {
            const ImDrawCmd* pcmd = &cmdList->CmdBuffer[c];

            GL::Renderer::setScissor(Range2Di { Range2D {
                    { pcmd->ClipRect.x, fbSize.y() - pcmd->ClipRect.w },
                    { pcmd->ClipRect.z, fbSize.y() - pcmd->ClipRect.y } }.scaled(supersamplingRatio) });

            mesh.setCount(pcmd->ElemCount);
            mesh.setIndexBuffer(indexBuffer, indexBufferOffset * sizeof(ImDrawIdx),
                                 sizeof(ImDrawIdx) == 2
                                 ? GL::MeshIndexType::UnsignedShort
                                 : GL::MeshIndexType::UnsignedInt);

            indexBufferOffset += pcmd->ElemCount;

            shader
                .bindTexture(*static_cast<GL::Texture2D*>(pcmd->TextureId))
                .draw(mesh);
        }
    }

    /* Reset scissor rectangle back to the full framebuffer size. Instead the
       users would be required to disable the scissor right after as otherwise
       the framebuffer clear would only happen on whatever the last scissor
       was. (And I hope the floating-point precision is enough here.) */
    GL::Renderer::setScissor(Range2Di{ Range2D{{ }, fbSize}.scaled(supersamplingRatio) });
}

}