#ifndef CORE_SHADER_H
#define CORE_SHADER_H

#include "Essential.h"
#include "FileSystem.h"

#include <string>
#include <fstream>
#include <bgfx/bgfx.h>

namespace core {

enum shaderType {
    VERTEX,
    FRAGMENT
};

class Shader {
public:
    Shader(bgfx::ShaderHandle handle);

    void SetShader(shaderType type, string path);

protected:
    bgfx::ShaderHandle LoadShader(const string& path);

    bgfx::ShaderHandle vertexShader;
    bgfx::ShaderHandle fragmentShader;

};

}

#endif //CORE_SHADER_H
