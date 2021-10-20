/*
 MIT License
 
 Copyright (c) 2021 lectroMathew <contact@lectro.moe>
 
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
#ifndef CORE_SHADER_H
#define CORE_SHADER_H

#include "Essentials.h"
#include "FileSystem.h"
#include "Mesh.h"
#include "Math.h"

#include <string>
#include <fstream>

#include <Magnum/Shaders/PhongGL.h>
#include <Magnum/Shaders/Generic.h>
#include <Magnum/Shaders/Phong.h>

using namespace Magnum;
namespace core {

class Shader {
public:
    Shader();

    void Draw(Mesh& mesh);

    void BindLightBuffer(GL::Buffer& buffer);
    void BindDrawBuffer(GL::Buffer& buffer);
    void BindMaterialBuffer(GL::Buffer& buffer);
    void BindTransformBuffer(GL::Buffer& buffer);
    void BindProjectionBuffer(GL::Buffer& buffer);
    
    static shared<Shader> standard;

protected:

    Shaders::PhongGL shader;

};

}

#endif //CORE_SHADER_H
