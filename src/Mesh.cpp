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

    vertices = new float[verticesAmount * 3 * sizeof(float)];
    indices = new uint32_t[indicesAmount * sizeof(uint32_t)];

    uint32_t vInd = 0;
    for(unsigned int j = 0; j < verticesAmount; j++) {
        const aiVector3D& vertexPos = aiMesh->mVertices[j];

        vertices[vInd++] = vertexPos.x;
        vertices[vInd++] = vertexPos.y;
        vertices[vInd++] = vertexPos.z;
    }
    uint32_t iInd = 0;
    for(int i = 0; i < trianglesAmount; i++) {
        const aiFace& face = aiMesh->mFaces[i];

        indices[iInd++] = face.mIndices[0];
        indices[iInd++] = face.mIndices[1];
        indices[iInd++] = face.mIndices[2];
    }

    UpdateBuffers();
}
Mesh::~Mesh() {
    delete[] vertices;
    delete[] indices;
    bgfx::destroy(indexBufferHandle);
    bgfx::destroy(vertexBufferHandle);
}
void Mesh::UpdateIndexBuffer() {
    indexBufferHandle = bgfx::createIndexBuffer(FileSystem::CopyToMemory(indices, indicesAmount),
                                                BGFX_BUFFER_INDEX32);
}
void Mesh::UpdateVertexBuffer() {
    vertexBufferHandle = bgfx::createVertexBuffer(FileSystem::CopyToMemory(vertices, verticesAmount * 3),
                                                  vertexLayout);
}
void Mesh::UpdateBuffers() {
    UpdateIndexBuffer();
    UpdateVertexBuffer();
}
bool Mesh::isValid() const {
    if (bgfx::isValid(indexBufferHandle) && bgfx::isValid(vertexBufferHandle)) {
        return true;
    } else {
        return false;
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

} // namespace