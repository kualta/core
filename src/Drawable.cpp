#include <core/Drawable.h>

namespace core {

void ColoredDrawable::draw(const Matrix4& transformationMatrix, SceneGraph::Camera3D& camera) {
    shader
    .setDiffuseColor(color)
    .setLightPositions({ { camera.cameraMatrix().transformPoint({-3.0f, 10.0f, 10.0f}), 0.0f } })
    .setTransformationMatrix(transformationMatrix)
    .setNormalMatrix(transformationMatrix.normalMatrix())
    .setProjectionMatrix(camera.projectionMatrix())
    .draw(mesh);
}

void TexturedDrawable::draw(const Matrix4& transformationMatrix, SceneGraph::Camera3D& camera) {
    shader .setLightPositions({ { camera.cameraMatrix().transformPoint({-3.0f, 10.0f, 10.0f}), 0.0f } });
}

}