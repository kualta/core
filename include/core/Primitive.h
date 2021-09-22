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
    explicit Cube() : Mesh(&cubeMesh) { }

    static GL::Mesh cubeMesh;
};
struct Sphere : public Mesh {
    explicit Sphere() : Mesh(&sphereMesh) { }

    static GL::Mesh sphereMesh;
};
struct Cone : public Mesh {
    explicit Cone() : Mesh(&coneMesh) { }

    static GL::Mesh coneMesh;
};
struct Cylinder : public Mesh {
    explicit Cylinder() : Mesh(&cylinderMesh) { }

    static GL::Mesh cylinderMesh;
};


}


#endif //CORE_PRIMITIVE_H
