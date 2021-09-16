#ifndef CORE_SCENEDATA_H
#define CORE_SCENEDATA_H

#include "Essential.h"

#include <Corrade/Containers/Array.h>
#include <Corrade/Containers/Optional.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/GL/Texture.h>
#include <Magnum/GL/TextureFormat.h>
#include <Magnum/Trade/PhongMaterialData.h>

using namespace Magnum;
namespace core {

struct SceneData {
    Containers::Array<Containers::Optional<GL::Mesh>> meshes { };
    Containers::Array<Containers::Optional<GL::Texture2D>> textures { };
    Containers::Array<Containers::Optional<Trade::PhongMaterialData>> materials { };
};

}

#endif //CORE_SCENEDATA_H
