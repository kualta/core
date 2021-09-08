#include <core/Mesh.h>
#include <core/Logger.h>

using namespace Math::Literals;
namespace core {

Mesh::Mesh() {

    struct TriangleVertex {
        Magnum::Vector2 position;
        Magnum::Color3 color;
    };
    const TriangleVertex data[]{
            {{-0.5f, -0.5f}, 0xff0000_rgbf},    /* Left vertex, red color */
            {{ 0.5f, -0.5f}, 0x00ff00_rgbf},    /* Right vertex, green color */
            {{ 0.0f,  0.5f}, 0x0000ff_rgbf}     /* Top vertex, blue color */
    };
    buffer.setData(data);
    mesh.setCount(3)
            .addVertexBuffer(std::move(buffer), 0,
                             Shaders::VertexColorGL2D::Position { },
                             Shaders::VertexColorGL2D::Color3 { });
}
GL::Mesh* Mesh::GetGLMesh() {
    return &mesh;
}

}