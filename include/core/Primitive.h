/**
 * Header defines primitive geometry types
 */
#ifndef CORE_PRIMITIVE_H
#define CORE_PRIMITIVE_H

#include "Essential.h"
#include "Vertex.h"
#include "Vector.h"
#include "Model.h"

#include <Magnum/Trade/MeshData.h>
#include <Magnum/Primitives/Cube.h>
#include <Magnum/MeshTools/Interleave.h>
#include <Magnum/MeshTools/CompressIndices.h>
#include <Magnum/Shaders/PhongGL.h>

namespace core {

typedef struct Rect {
    float x, y;
    float w, h;
} Rect;

class Cube : public Mesh {
public:
    Cube() {
        Trade::MeshData cubeData = Primitives::cubeSolid();
        std::pair<Containers::Array<char>, MeshIndexType> compressed = MeshTools::compressIndices(cubeData.indicesAsArray());

        vertices.setData(MeshTools::interleave(cubeData.positions3DAsArray(), cubeData.normalsAsArray()));
        indices.setData(compressed.first);

        mesh
            .setPrimitive(cubeData.primitive())
            .setCount(cubeData.indexCount())
            .addVertexBuffer(std::move(vertices), 0, Shaders::PhongGL::Position{ }, Shaders::PhongGL::Normal{ })
            .setIndexBuffer(std::move(indices), 0, compressed.second);
    }
};

}


#endif //CORE_PRIMITIVE_H
