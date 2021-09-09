#ifndef CORE_SHADER_H
#define CORE_SHADER_H

#include "Essential.h"
#include "FileSystem.h"
#include "Mesh.h"
#include "Math.h"

#include <string>
#include <fstream>

#include <Magnum/Shaders/PhongGL.h>

using namespace Magnum;
namespace core {

class Shader {
public:
    Shader();

    void Draw(Mesh* mesh);

    void SetLightPositions(Magnum::Vector4 pos);
    void SetDiffuseColor(Color3 color);
    void SetAmbientColor(Color3 color);
    void SetTransformMatrix(Magnum::Matrix4 mtx);
    void SetProjectionMatrix(Magnum::Matrix4 mtx);
    void SetNormalMatrix(Magnum::Matrix4 mtx);

protected:

    Shaders::PhongGL shader;

};

}

#endif //CORE_SHADER_H
