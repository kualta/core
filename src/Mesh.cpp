#include <core/Mesh.h>
#include <core/Logger.h>

namespace core {

//Mesh::Mesh(aiMesh *aiMesh)
//: verticesAmount(aiMesh->mNumVertices),
//trianglesAmount(aiMesh->mNumFaces),
//indicesAmount(aiMesh->mNumFaces * 3) // Considering the model is triangulated, FIXME!
//{
//    Logger::Log(IMPORT, INFO) << "Processing Mesh " << aiMesh->mName.C_Str();
//
//    const int16_t elementSize = sizeof(float);
//    //    const uint32_t step = .getStride() / elementSize;
//
//    //    vertexBuffer = new float[vertexLayout.getSize(verticesAmount) / elementSize];
//    uint32_t offset = 0;
//
//    // TODO: Move to new VertexLayout class constructor
//    if ( aiMesh->HasPositions() ) {
//        Logger::Log(IMPORT, INFO) << " | Vertices: " << verticesAmount;
//        Logger::Log(IMPORT, INFO) << " | Triangles: " << trianglesAmount;
//        Logger::Log(IMPORT, INFO) << " | Indices: " << indicesAmount;
//    } else {
//        Logger::Log(IMPORT, ERR_HERE) << "Import failed, mesh does not contain position info?!";
//        throw core::bad_mesh("Mesh does not contain position info");
//    }
//
//    if ( aiMesh->HasVertexColors(0) ) {
//        Logger::Log(IMPORT, INFO) << " | Color channels: " << aiMesh->GetNumColorChannels();
//    }
//
//    if ( aiMesh->HasTextureCoords(0) ) {
//        Logger::Log(IMPORT, INFO) << " | Texture channels: " << aiMesh->GetNumUVChannels();
//    }
//
//    if ( aiMesh->HasNormals() ) {
//        Logger::Log(IMPORT, INFO) << " | Normals: " << "true";
//    }
//
//    if ( aiMesh->HasTangentsAndBitangents() ) {
//        Logger::Log(IMPORT, INFO) << " | Tangents: " << "true";
//        Logger::Log(IMPORT, INFO) << " | Bitangents: " << "true";
//    }
//
//    for(size_t vNum = 0; vNum < verticesAmount; vNum++) {
//        const aiVector3D& vertexPos = aiMesh->mVertices[vNum];
//
//        //        vertexBuffer[vNum * step + offset + 0] = vertexPos[0];
//        //        vertexBuffer[vNum * step + offset + 1] = vertexPos[1];
//        //        vertexBuffer[vNum * step + offset + 2] = vertexPos[2];
//    }
//
//    indexBuffer = new uint32_t[indicesAmount * sizeof(uint32_t)];
//
//    uint32_t index = 0;
//    for(int i = 0; i < trianglesAmount; i++) {
//        const aiFace& face = aiMesh->mFaces[i];
//
//        indexBuffer[index++] = face.mIndices[0];
//        indexBuffer[index++] = face.mIndices[1];
//        indexBuffer[index++] = face.mIndices[2];
//    }
//}

}