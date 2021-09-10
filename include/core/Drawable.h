#ifndef CORE_DRAWABLE_H
#define CORE_DRAWABLE_H

#include "Essential.h"
#include "Scene.h"

#include <Magnum/SceneGraph/Drawable.h>
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

class ColoredDrawable: public SceneGraph::Drawable3D {
public:
    explicit ColoredDrawable(Object3D& object,
                             Shaders::PhongGL& shader,
                             GL::Mesh& mesh,
                             const Color4& color,
                             SceneGraph::DrawableGroup3D& group)
    : SceneGraph::Drawable3D { object, &group },
    shader(shader),
    mesh(mesh),
    color{ color } { }

private:
    void draw(const Matrix4& transformationMatrix, SceneGraph::Camera3D& camera) override;

    Shaders::PhongGL& shader;
    GL::Mesh&         mesh;
    Color4            color;
};

class TexturedDrawable: public SceneGraph::Drawable3D {
public:
    explicit TexturedDrawable(Object3D& object,
                              Shaders::PhongGL& shader,
                              GL::Mesh& mesh,
                              GL::Texture2D& texture,
                              SceneGraph::DrawableGroup3D& group)
    : SceneGraph::Drawable3D{object, &group},
    shader(shader),
    mesh(mesh),
    texture(texture) { }

private:
    void draw(const Matrix4& transformationMatrix, SceneGraph::Camera3D& camera) override;

    Shaders::PhongGL& shader;
    GL::Mesh&         mesh;
    GL::Texture2D&    texture;
};

}

#endif //CORE_DRAWABLE_H
