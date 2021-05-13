#include <core/Shader.h>

namespace core {

Shader::Shader(bgfx::ShaderHandle handle){

}
void Shader::SetShader(shaderType type, string path) {
    switch (type) {
        case VERTEX:   vertexShader   = LoadShader(path); break;
        case FRAGMENT: fragmentShader = LoadShader(path); break;
    }
}
bgfx::ShaderHandle Shader::LoadShader(const string& path) {

    int64_t shaderSize = FileSystem::GetFileSize(path);

    const bgfx::Memory* shaderMemory = FileSystem::ReadFileToMemory(path, shaderSize);

    bgfx::ShaderHandle handle = bgfx::createShader(shaderMemory);

    return handle;
}

}