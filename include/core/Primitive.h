/**
 * Header defines primitive geometry types
 */
#ifndef CORE_PRIMITIVE_H
#define CORE_PRIMITIVE_H

#include "Essentials.h"
#include "Model.h"
#include "SceneData.h"

#include <Magnum/Trade/MeshData.h>
#include <Magnum/Primitives/Cube.h>
#include <Magnum/Primitives/UVSphere.h>
#include <Magnum/Primitives/Cone.h>
#include <Magnum/Primitives/Cylinder.h>
#include <Magnum/MeshTools/Interleave.h>
#include <Magnum/MeshTools/CompressIndices.h>
#include <Magnum/Shaders/PhongGL.h>

namespace core {

typedef struct Rect {
    float x, y;
    float w, h;
} Rect;

struct Cube : public Mesh {
    Cube() { mesh = MeshTools::compile(Primitives::cubeSolid()); }
};
struct Sphere : public Mesh {
    explicit Sphere(uint32_t rings = 25, uint32_t segments = 25) {
        mesh = MeshTools::compile(Primitives::uvSphereSolid(rings, segments));
    }
};
struct Cone : public Mesh {
    explicit Cone(uint32_t rings = 25, uint32_t segments = 25, float length = 1) {
        mesh = MeshTools::compile(Primitives::coneSolid(rings, segments, length));
    }
};
struct Cylinder : public Mesh {
    explicit Cylinder(uint32_t rings = 25, uint32_t segments = 25, float length = 1) {
        mesh = MeshTools::compile(Primitives::cylinderSolid(rings, segments, length));
    }
};
}


#endif //CORE_PRIMITIVE_H
