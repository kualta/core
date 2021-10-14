#include <core/Scene/SceneView.h>
#include <core/Logger.h>
#include "Magnum/GL/Renderer.h"
#include "Magnum/GL/AbstractFramebuffer.h"

namespace core {

SceneView::SceneView(Vector2i pos, Vector2i size) : View("Scene", pos, size) {

}
SceneView::SceneView(NoCreateT) : View(NoCreate) {

}

}