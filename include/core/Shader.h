#ifndef CORE_SHADER_H
#define CORE_SHADER_H

#include "Essential.h"
#include "FileSystem.h"

#include <string>
#include <fstream>

namespace core {

class Shader {
public:
    Shader(const string& vertexShaderPath, const string& fragmentShaderPath);

    void SetVertexShader(const string& path);
    void SetFragmentShader(const string& path);

};

}

#endif //CORE_SHADER_H
