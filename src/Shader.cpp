#include <core/Shader.h>

namespace core {

Shader::Shader(const string& vShaderPath, const string& fShaderPath)
: vertexShader(LoadShader(vShaderPath)), fragmentShader(LoadShader(fShaderPath)) {

}
void Shader::SetVertexShader(const string& path) {
    vertexShader = LoadShader(path);
}
void Shader::SetFragmentShader(const string& path) {
    fragmentShader = LoadShader(path);
}
void Shader::UpdateShader() {
    if (IsValid(vertexShader) && IsValid(fragmentShader)) {
        program = bgfx::createProgram(vertexShader, fragmentShader, true);
    }
}
bgfx::ShaderHandle Shader::LoadShader(const string& path) {

    int64_t shaderSize = FileSystem::GetFileSize(path);
    const bgfx::Memory* shaderMemory = FileSystem::ReadFileToMemory(path, shaderSize);

    bgfx::ShaderHandle handle = bgfx::createShader(shaderMemory);

    return handle;
}
bool Shader::IsValid() {
    return bgfx::isValid(program);
}

}