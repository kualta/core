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
