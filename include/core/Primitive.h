/**
 * Header defines primitive geometry types
 */
#ifndef CORE_PRIMITIVE_H
#define CORE_PRIMITIVE_H

#include "Essentials.h"
#include "Model.h"

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

class Cube : public Mesh {
public:
//    Cube() {
//        GL::Mesh glMesh = MeshTools::compile(Primitives::cubeSolid());
//        mesh = &glMesh;
//    }
};

class Sphere : public Mesh {
public:
//    Sphere() { mesh = MeshTools::compile(Primitives::uvSphereSolid(25, 25)); }
};

class Cone : public Mesh {
public:
//    Cone() { mesh = MeshTools::compile(Primitives::coneSolid(25, 25, 1)); }
};

class Cylinder : public Mesh {
public:
//    Cylinder() { mesh = MeshTools::compile(Primitives::coneSolid(25, 25, 1)); }
};
}


#endif //CORE_PRIMITIVE_H
