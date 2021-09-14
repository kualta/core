#ifndef CORE_SCENEIMPORTER_H
#define CORE_SCENEIMPORTER_H

#include "Essential.h"
#include "Drawable.h"
#include "Shader.h"
#include "Importer.h"
#include "SceneData.h"

#include <Corrade/Containers/Array.h>
#include <Corrade/Containers/Optional.h>
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
#include <Magnum/Trade/ImageData.h>
#include <Magnum/Trade/MeshData.h>
#include <Magnum/Trade/MeshObjectData3D.h>
#include <Magnum/Trade/PhongMaterialData.h>
#include <Magnum/Trade/SceneData.h>
#include <Magnum/Trade/TextureData.h>

using namespace Magnum;
namespace core {

class SceneImporter : public Importer {
public:

    /**
     * Imports and returns pointer to core::SceneData
     * @param filepath - path to scene file
     * @return core::SceneData* data
     */
    SceneData* ImportScene(const string& filepath);

    void CreateObject(GraphObject* parent, SceneData& data, UnsignedInt id);
    void ImportObjectsFromScene(SceneData& data);

protected:

    void LoadImporter();
    void OpenFile(const string& filepath);

    void ImportTextures(SceneData& data);
    void ImportMaterials(SceneData& data);
    void ImportMeshes(SceneData& data);

    Containers::Pointer<Trade::AbstractImporter> importer;

};

}

#endif //CORE_SCENEIMPORTER_H
