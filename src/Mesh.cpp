#include <core/Mesh.h>
#include <core/FileSystem.h>
#include <core/Logger.h>
#include <core/Exceptions.h>

namespace core {

Mesh::Mesh(aiMesh* aiMesh) :
        verticesAmount(aiMesh->mNumVertices),
        trianglesAmount(aiMesh->mNumFaces),
        indicesAmount(aiMesh->mNumFaces * 3) // Considering the model is triangulated, FIXME!
{
    UpdateVertexLayout(aiMesh);
    UpdateBuffers(aiMesh);
    UpdateBufferHandles();
}
Mesh::~Mesh() {
    delete[] positions;
    delete[] indexBuffer;
    bgfx::destroy(indexBufferHandle);
    bgfx::destroy(vertexBufferHandle);
}
void Mesh::UpdateIndexBufferHandle() {
    indexBufferHandle = bgfx::createIndexBuffer(FileSystem::CopyToMemory(indexBuffer, indicesAmount),
                                                BGFX_BUFFER_INDEX32);
}
void Mesh::UpdateVertexBufferHandle() {
    vertexBufferHandle = bgfx::createVertexBuffer(
            FileSystem::CopyToMemory(vertexBuffer, vertexLayout.getSize(verticesAmount)), vertexLayout);
}
void Mesh::UpdateBufferHandles() {
    UpdateIndexBufferHandle();
    UpdateVertexBufferHandle();
}
void Mesh::UpdateBuffers(aiMesh* aiMesh) {
    UpdatePositionBuffer(aiMesh);
    UpdateNormalBuffer(aiMesh);
    UpdateUVBuffer(aiMesh);
    UpdateIndexBuffer(aiMesh);
    UpdateVertexBuffer(aiMesh);
}
void Mesh::UpdatePositionBuffer(aiMesh *aiMesh) {
    positions = new float[verticesAmount * 3 * sizeof(float)];

    uint32_t index = 0;
    for(uint32_t i = 0; i < verticesAmount; i++) {
        const aiVector3D& vertexPos = aiMesh->mVertices[i];

        positions[index++] = vertexPos.x;
        positions[index++] = vertexPos.y;
        positions[index++] = vertexPos.z;
    }
}
void Mesh::UpdateNormalBuffer(aiMesh *aiMesh) {
    normals = new float[verticesAmount * 3 * sizeof(float)];

    uint32_t index = 0;
    for(uint32_t i = 0; i < verticesAmount; i++) {
        const aiVector3D& normal = aiMesh->mNormals[i];

        normals[index++] = normal.x;
        normals[index++] = normal.y;
        normals[index++] = normal.z;
    }
}
void Mesh::UpdateUVBuffer(aiMesh *aiMesh) {
    uvs = new float[verticesAmount * 2 * sizeof(float)];

    uint32_t index = 0;
    for(uint32_t i = 0; i < verticesAmount; i++) {
        const aiVector3D& uv = aiMesh->mTextureCoords[0][i];

        uvs[index++] = uv.x;
        uvs[index++] = uv.y;
    }
}
void Mesh::UpdateVertexBuffer(aiMesh* aiMesh) {
    vertexBuffer = new float[vertexLayout.getSize(verticesAmount) * sizeof(float)];

    uint32_t index = 0;
    uint32_t stride = vertexLayout.getStride();
    for(uint32_t i = 0; i < verticesAmount; i++) {
        const aiVector3D& uv = aiMesh->mTextureCoords[0][i];

        vertexBuffer[index++] = uv.x;
        vertexBuffer[index++] = uv.y;
    }
}
void Mesh::UpdateIndexBuffer(aiMesh* aiMesh) {
    indexBuffer = new uint32_t[indicesAmount * sizeof(uint32_t)];

    uint32_t index = 0;
    for(int i = 0; i < trianglesAmount; i++) {
        const aiFace& face = aiMesh->mFaces[i];

        indexBuffer[index++] = face.mIndices[0];
        indexBuffer[index++] = face.mIndices[1];
        indexBuffer[index++] = face.mIndices[2];
    }
}
void Mesh::UpdateVertexLayout(aiMesh *aiMesh) {
    vertexLayout.begin();

    Logger::Log(IMPORT, INFO) << "|| Importing Mesh \"" << aiMesh->mName.C_Str() << "\": ";

    if ( aiMesh->HasPositions() ) {
        Logger::Log(IMPORT, INFO) << "|| Vertices: " << verticesAmount;
        Logger::Log(IMPORT, INFO) << "|| Triangles: " << trianglesAmount;
        Logger::Log(IMPORT, INFO) << "|| Indices: " << indicesAmount;
        vertexLayout.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float);
    } else {
        Logger::Log(IMPORT, ERR_HERE) << "Import failed, mesh does not contain position info?!";
        throw core::bad_mesh("Mesh does not contain position info");
    }

    if ( aiMesh->HasVertexColors(0) ) {
        Logger::Log(IMPORT, INFO) << "|| Color channels: " << aiMesh->GetNumColorChannels();
        vertexLayout.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Float);
    } else {
        Logger::Log(IMPORT, INFO) << "|| Color channels: " << aiMesh->GetNumColorChannels();
    }

    if ( aiMesh->HasTextureCoords(0) ) {
        Logger::Log(IMPORT, INFO) << "|| Texture channels: " << aiMesh->GetNumUVChannels();
        vertexLayout.add(bgfx::Attrib::TexCoord0, 3, bgfx::AttribType::Float);
    } else {
        Logger::Log(IMPORT, INFO) << "|| Texture channels: " << aiMesh->GetNumUVChannels();
    }

    if ( aiMesh->HasNormals() ) {
        Logger::Log(IMPORT, INFO) << "|| Normals: " << "true";
        vertexLayout.add(bgfx::Attrib::Normal, 3, bgfx::AttribType::Float);
    } else {
        Logger::Log(IMPORT, INFO) << "|| Normals: " << "false";
    }

    if ( aiMesh->HasTangentsAndBitangents() ) {
        Logger::Log(IMPORT, INFO) << "|| Tangents: " << "true";
        Logger::Log(IMPORT, INFO) << "|| Bitangents: " << "true";
        vertexLayout.add(bgfx::Attrib::Tangent, 3, bgfx::AttribType::Float);
        vertexLayout.add(bgfx::Attrib::Bitangent, 3, bgfx::AttribType::Float);
    } else {
        Logger::Log(IMPORT, INFO) << "|| Tangents: " << "false";
        Logger::Log(IMPORT, INFO) << "|| Bitangents: " << "false";
    }

    vertexLayout.end();
}
bool Mesh::isValid() const {
    if (bgfx::isValid(indexBufferHandle) && bgfx::isValid(vertexBufferHandle)) {
        return true;
    } else {
        return false;
    }
}

} // namespace