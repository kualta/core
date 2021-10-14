#ifndef CORE_SCENEVIEW_H
#define CORE_SCENEVIEW_H

#include "core/Essentials.h"
#include "core/Singleton.h"
#include "core/View.h"

using namespace Magnum;
namespace core {

class SceneView : public View, public Singleton<SceneView> {
public:

    /** Copying is not allowed */
    SceneView(const SceneView&) = delete;

    /** Move constructor */
    SceneView(SceneView&&) = default;

    /** Move assgnment operator */
    SceneView& operator=(SceneView&&) = default;

protected:
    friend class EditorModule;

    explicit SceneView(Vector2i pos = { }, Vector2i size = { });
    explicit SceneView(NoCreateT);

};

} // namespace core

#endif //CORE_SCENEVIEW_H
