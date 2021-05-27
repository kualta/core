#include <core/Mesh.h>

namespace core {

Mesh::Mesh(aiMesh *aiMesh) :
        verticesAmount(aiMesh->mNumVertices),
        trianglesAmount(aiMesh->mNumFaces),
        indicesAmount(aiMesh->mNumFaces * 3) // Considering the model is triangulated, FIXME!
{
    vertexLayout.begin()
            .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
            .end();

    vertices = new float[verticesAmount * 3 * sizeof(float)];
    indices = new uint32_t[indicesAmount * sizeof(uint32_t)];

    uint32_t vInd = 0;
    for(unsigned int j = 0; j < verticesAmount; j++) {
        const aiVector3D* vp = &(aiMesh->mVertices[j]);

        vertices[vInd++] = vp->x;
        vertices[vInd++] = vp->y;
        vertices[vInd++] = vp->z;
    }
    uint32_t iInd = 0;
    for(int i = 0; i < trianglesAmount; i++) {
        const aiFace* vf = &(aiMesh->mFaces[i]);

        indices[iInd++] = vf->mIndices[0];
        indices[iInd++] = vf->mIndices[1];
        indices[iInd++] = vf->mIndices[2];
    }

    UpdateBuffers();
}
Mesh::~Mesh() {
    delete[] vertices;
    delete[] indices;
    bgfx::destroy(indexBufferHandle);
    bgfx::destroy(vertexBufferHandle);
}
Mesh::Mesh(const std::vector<ColorVertex>& vb, const std::vector<uint16_t>& ib) {
    vertexLayout.begin()
            .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
            .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
            .end();

    vertexBufferHandle = CreateVertexBuffer(vb);
    indexBufferHandle = CreateIndexBuffer(ib);
}
Mesh::Mesh(float *vertices, size_t vSize, const uint32_t* indices, size_t iSize) {
        vertexLayout.begin()
                .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
                .end();

        vertexBufferHandle = CreateVertexBuffer(vertices, vSize);
        indexBufferHandle = CreateIndexBuffer(indices, iSize);
}
bgfx::VertexBufferHandle Mesh::CreateVertexBuffer(float* vertices, size_t vSize) {
    size_t bufferSize = vSize * sizeof(float);

    const bgfx::Memory* mem = bgfx::alloc(bufferSize);
    std::memcpy(mem->data, vertices, bufferSize);

    return bgfx::createVertexBuffer(mem, vertexLayout);
}
bgfx::VertexBufferHandle Mesh::CreateVertexBuffer(const std::vector<ColorVertex>& vb) {
    size_t bufferSize = vb.size() * sizeof(ColorVertex);

    const bgfx::Memory* mem = bgfx::alloc(bufferSize);
    std::memcpy(mem->data, vb.data(), bufferSize);

    return bgfx::createVertexBuffer(mem, vertexLayout);
}
bgfx::IndexBufferHandle Mesh::CreateIndexBuffer(const std::vector<uint16_t>& ib) {
    size_t bufferSize = ib.size() * sizeof(uint16_t);

    const bgfx::Memory* mem = bgfx::alloc(bufferSize);
    std::memcpy(mem->data, ib.data(), bufferSize);

    return bgfx::createIndexBuffer(mem);
}
bgfx::IndexBufferHandle Mesh::CreateIndexBuffer(const uint32_t *indices, size_t iSize) {
    size_t bufferSize = iSize * sizeof(int);

    const bgfx::Memory* mem = bgfx::alloc(bufferSize);
    std::memcpy(mem->data, indices, bufferSize);

    return bgfx::createIndexBuffer(mem);
}
void Mesh::UpdateIndexBuffer() {
    indexBufferHandle = bgfx::createIndexBuffer(AllocAndCopy(indices, indicesAmount), BGFX_BUFFER_INDEX32);
}
void Mesh::UpdateVertexBuffer() {
    vertexBufferHandle = bgfx::createVertexBuffer(AllocAndCopy(vertices, verticesAmount * 3), vertexLayout);
}
void Mesh::UpdateBuffers() {
    UpdateIndexBuffer();
    UpdateVertexBuffer();
}
bool Mesh::isValid() {
    if (bgfx::isValid(indexBufferHandle) && bgfx::isValid(vertexBufferHandle)) {
        return true;
    } else {
        return false;
    }
}

} // namespace