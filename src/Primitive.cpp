#include <core/Primitive.h>

namespace core {

GL::Mesh Cube::cubeMesh = MeshTools::compile(Primitives::cubeSolid());
GL::Mesh Sphere::sphereMesh = MeshTools::compile(Primitives::uvSphereSolid(25, 25));
GL::Mesh Cone::coneMesh = MeshTools::compile(Primitives::coneSolid(25, 25, 1));
GL::Mesh Cylinder::cylinderMesh = MeshTools::compile(Primitives::cylinderSolid(25, 25, 1));

}
