#ifndef CORE_MODELIMPORTER_H
#define CORE_MODELIMPORTER_H

#include "Essential.h"

#include <Corrade/Containers/Array.h>
#include <Corrade/Containers/Optional.h>
#include <Corrade/PluginManager/Manager.h>
#include <Corrade/Utility/Arguments.h>
#include <Corrade/Utility/DebugStl.h>
#include <Magnum/ImageView.h>
#include <Magnum/Mesh.h>
#include <Magnum/PixelFormat.h>
#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/GL/Texture.h>
#include <Magnum/GL/TextureFormat.h>
#include <Magnum/Math/Color.h>
#include <Magnum/MeshTools/Compile.h>
#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/SceneGraph/Camera.h>
#include <Magnum/SceneGraph/Drawable.h>
#include <Magnum/SceneGraph/MatrixTransformation3D.h>
#include <Magnum/SceneGraph/Scene.h>
#include <Magnum/Shaders/PhongGL.h>
#include <Magnum/Trade/AbstractImporter.h>
#include <Magnum/Trade/ImageData.h>
#include <Magnum/Trade/MeshData.h>
#include <Magnum/Trade/MeshObjectData3D.h>
#include <Magnum/Trade/PhongMaterialData.h>
#include <Magnum/Trade/SceneData.h>
#include <Magnum/Trade/TextureData.h>

using namespace Magnum;
namespace core {

class ModelImporter {
    typedef SceneGraph::Object<SceneGraph::MatrixTransformation3D> Object3D;
    typedef SceneGraph::Scene<SceneGraph::MatrixTransformation3D> Scene3D;
public:
    ModelImporter();

    void AddObject(Trade::AbstractImporter& importer, Containers::ArrayView<const Containers::Optional<Trade::PhongMaterialData>> materials, Object3D& parent, UnsignedInt i);
    void LoadImporter();

    Containers::Array<Containers::Optional<GL::Mesh>> meshes;
    Containers::Array<Containers::Optional<GL::Texture2D>> textures;
    Scene3D scene;

    static PluginManager::Manager<Trade::AbstractImporter> manager;
    static Containers::Pointer<Trade::AbstractImporter> importer;
};

}

#endif //CORE_MODELIMPORTER_H
