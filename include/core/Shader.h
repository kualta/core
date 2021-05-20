#ifndef CORE_SHADER_H
#define CORE_SHADER_H

#include "Essential.h"
#include "FileSystem.h"

#include <string>
#include <fstream>
#include <bgfx/bgfx.h>

namespace core {

class Shader {
public:
    Shader(const string& vertexShaderPath, const string& fragmentShaderPath);

    void SetVertexShader(const string& path);
    void SetFragmentShader(const string& path);
    void UpdateShader();
    bool IsValid();

    bgfx::ProgramHandle program { bgfx::kInvalidHandle };

protected:
    static bgfx::ShaderHandle LoadShader(const string& path);

    bgfx::ShaderHandle  vertexShader   { bgfx::kInvalidHandle };
    bgfx::ShaderHandle  fragmentShader { bgfx::kInvalidHandle };
};

}

#endif //CORE_SHADER_H
