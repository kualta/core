#ifndef CORE_SHADER_H
#define CORE_SHADER_H

#include "Essential.h"

#include <string>
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
    bgfx::ShaderHandle LoadShader(string path);

    static string ShadersPathFromRenderer();


    bgfx::ShaderHandle vertexShader;
    bgfx::ShaderHandle fragmentShader;

    static string shadersPath;

};

}

#endif //CORE_SHADER_H
