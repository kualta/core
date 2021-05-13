#include <core/Components/Renderer.h>

namespace core {

void Renderer::Draw() {

    bgfx::submit(viewId,vfProgram);
}

}