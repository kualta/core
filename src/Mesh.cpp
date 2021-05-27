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
    Logger::Log(IMPORT, INFO) << "|| Processing Mesh \"" << aiMesh->mName.C_Str() << "\": ";

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
    UpdateIndexBuffer(aiMesh);
    UpdateVertexBuffer(aiMesh);
}
void Mesh::UpdateVertexBuffer(aiMesh* aiMesh) {
    vertexBuffer = new float[vertexLayout.getSize(verticesAmount)];

    uint32_t step = vertexLayout.getStride() / sizeof(float);
    uint32_t offset = 0;

    if ( vertexLayout.has(bgfx::Attrib::Position ) ) {
        offset = vertexLayout.getOffset(bgfx::Attrib::Position) / sizeof(float);
        for(size_t vNum = 0; vNum < verticesAmount; vNum++) {
            const aiVector3D& vertexPos = aiMesh->mVertices[vNum];

            vertexBuffer[vNum * step + offset + 0] = vertexPos[0];
            vertexBuffer[vNum * step + offset + 1] = vertexPos[1];
            vertexBuffer[vNum * step + offset + 2] = vertexPos[2];
        }
    }
    if ( vertexLayout.has(bgfx::Attrib::Color0 ) ) {
        offset = vertexLayout.getOffset(bgfx::Attrib::Color0) / sizeof(float);
        for(size_t vNum = 0; vNum < verticesAmount; vNum++) {
            const aiColor4D& vertexColor = aiMesh->mColors[0][vNum];

            vertexBuffer[vNum * step + offset + 0] = vertexColor[0];
            vertexBuffer[vNum * step + offset + 1] = vertexColor[1];
            vertexBuffer[vNum * step + offset + 2] = vertexColor[2];
            vertexBuffer[vNum * step + offset + 3] = vertexColor[3];
        }
    }
    if ( vertexLayout.has(bgfx::Attrib::TexCoord0 ) ) {
        offset = vertexLayout.getOffset(bgfx::Attrib::TexCoord0) / sizeof(float);
        for(size_t vNum = 0; vNum < verticesAmount; vNum++) {
            const aiVector3D& uv = aiMesh->mTextureCoords[0][vNum];

            vertexBuffer[vNum * step + offset + 0] = uv[0];
            vertexBuffer[vNum * step + offset + 1] = uv[1];
        }
    }
    if ( vertexLayout.has(bgfx::Attrib::Normal ) ) {
        offset = vertexLayout.getOffset(bgfx::Attrib::Normal) / sizeof(float);
        for(size_t vNum = 0; vNum < verticesAmount; vNum++) {
            const aiVector3D& normal = aiMesh->mNormals[vNum];

            vertexBuffer[vNum * step + offset + 0] = normal[0];
            vertexBuffer[vNum * step + offset + 1] = normal[1];
            vertexBuffer[vNum * step + offset + 2] = normal[2];
        }
    }
    if ( vertexLayout.has(bgfx::Attrib::Tangent ) && vertexLayout.has(bgfx::Attrib::Bitangent) ) {
        for(size_t vNum = 0; vNum < verticesAmount; vNum++) {
            const aiVector3D& tangent = aiMesh->mTangents[vNum];
            const aiVector3D& bitangent = aiMesh->mBitangents[vNum];

            offset = vertexLayout.getOffset(bgfx::Attrib::Tangent) / sizeof(float);
            vertexBuffer[vNum * step + offset + 0] = tangent[0];
            vertexBuffer[vNum * step + offset + 1] = tangent[1];
            vertexBuffer[vNum * step + offset + 2] = tangent[2];

            offset = vertexLayout.getOffset(bgfx::Attrib::Bitangent) / sizeof(float);
            vertexBuffer[vNum * step + offset + 0] = bitangent[0];
            vertexBuffer[vNum * step + offset + 1] = bitangent[1];
            vertexBuffer[vNum * step + offset + 2] = bitangent[2];
        }
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