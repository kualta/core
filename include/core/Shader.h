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
    Shader(Shaders::PhongGL* shader);

    void Draw(Mesh* mesh);

    void SetLightPositions(Vector4& pos);
    void SetDiffuseColor(Color3 color);
    void SetAmbientColor(Color3 color);
    void SetTransformMatrix(Matrix4& mtx);
    void SetProjectionMatrix(Matrix4& mtx);
    void SetNormalMatrix(Matrix4& mtx);

    static Shaders::PhongGL coloredShader;
    static Shaders::PhongGL texturedShader;

protected:

    Shaders::PhongGL* shader;

};

}

#endif //CORE_SHADER_H
