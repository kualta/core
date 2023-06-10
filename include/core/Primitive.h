/**
 * Header defines primitive geometry types
 */

/*
 MIT License
 
 Copyright (c) 2021 kualta <contact@kualta.dev>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */
#ifndef CORE_PRIMITIVE_H
#define CORE_PRIMITIVE_H

#include "Essentials.h"
#include "Model.h"
#include "core/Scene/SceneData.h"

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
