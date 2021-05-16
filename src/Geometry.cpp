#include <core/Geometry.h>

namespace core {

Geometry::Geometry(std::vector<ColorVertex> vb, std::vector<uint16_t> ib)
: verticesBuf(std::move(vb)), trianglesBuf(std::move(ib)) {

    vertexLayout.begin()
            .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
            .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
            .end();

    vertexBufferHandle = CreateVertexBuffer(verticesBuf);
    indexBufferHandle = CreateIndexBuffer(trianglesBuf);
}
bgfx::VertexBufferHandle Geometry::CreateVertexBuffer(const std::vector<ColorVertex>& vb) const {
    size_t vecBytesSize = vb.size() * sizeof(ColorVertex);

    const bgfx::Memory* mem = bgfx::alloc(vecBytesSize);
    std::memcpy(mem->data, vb.data(), vecBytesSize);

    return bgfx::createVertexBuffer(mem, vertexLayout);
}
bgfx::IndexBufferHandle Geometry::CreateIndexBuffer(const std::vector<uint16_t>& ib) const {
    size_t vecBytesSize = ib.size() * sizeof(uint16_t);

    const bgfx::Memory* mem = bgfx::alloc(vecBytesSize);
    std::memcpy(mem->data, ib.data(), vecBytesSize);

    return bgfx::createIndexBuffer(mem);

}

} // namespace