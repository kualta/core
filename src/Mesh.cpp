#include <core/Mesh.h>

namespace core {

Mesh::Mesh(const std::vector<ColorVertex>& vb, const std::vector<uint16_t>& ib) {
    vertexLayout.begin()
            .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
            .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
            .end();

    vertexBufferHandle = CreateVertexBuffer(vb);
    indexBufferHandle = CreateIndexBuffer(ib);
}
Mesh::Mesh(float *vertices, size_t vSize, const int *indices, size_t iSize) {
        vertexLayout.begin()
                .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
                .end();

        vertexBufferHandle = CreateVertexBuffer(vertices, vSize);
        indexBufferHandle = CreateIndexBuffer(indices, iSize);
}
bgfx::VertexBufferHandle Mesh::CreateVertexBuffer(float* vertices, size_t vSize) const {
    size_t bufferSize = vSize * sizeof(float);

    const bgfx::Memory* mem = bgfx::alloc(bufferSize);
    std::memcpy(mem->data, vertices, bufferSize);

    return bgfx::createVertexBuffer(mem, vertexLayout);
}
bgfx::VertexBufferHandle Mesh::CreateVertexBuffer(const std::vector<ColorVertex>& vb) const {
    size_t bufferSize = vb.size() * sizeof(ColorVertex);

    const bgfx::Memory* mem = bgfx::alloc(bufferSize);
    std::memcpy(mem->data, vb.data(), bufferSize);

    return bgfx::createVertexBuffer(mem, vertexLayout);
}
bgfx::IndexBufferHandle Mesh::CreateIndexBuffer(const std::vector<uint16_t>& ib) const {
    size_t bufferSize = ib.size() * sizeof(uint16_t);

    const bgfx::Memory* mem = bgfx::alloc(bufferSize);
    std::memcpy(mem->data, ib.data(), bufferSize);

    return bgfx::createIndexBuffer(mem);
}
bgfx::IndexBufferHandle Mesh::CreateIndexBuffer(const int *indices, size_t iSize) const {
    size_t bufferSize = iSize * sizeof(int);

    const bgfx::Memory* mem = bgfx::alloc(bufferSize);
    std::memcpy(mem->data, indices, bufferSize);

    return bgfx::createIndexBuffer(mem);
}

} // namespace