#include <core/Geometry.h>
#include <core/Primitive.h>

namespace core {

Geometry::Geometry() {

}
Geometry::Geometry(ColorVertex* verBuf, uint16_t verBufSize, uint64_t *triBuf, uint16_t triBufSize)
: verticesBuf(verBuf), trianglesBuf(triBuf), vBufSize(verBufSize), tBufSize(triBufSize) {

    vertexLayout.begin()
            .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
            .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
            .end();

    vbh = bgfx::createVertexBuffer(bgfx::makeRef(verticesBuf, vBufSize), vertexLayout);
    ibh = bgfx::createIndexBuffer(bgfx::makeRef(trianglesBuf, tBufSize));
}

} // namespace