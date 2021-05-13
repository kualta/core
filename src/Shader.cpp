#include <core/Shader.h>
#include <cstring>
#include <fstream>

namespace core {

string Shader::shadersPath {  };

Shader::Shader(bgfx::ShaderHandle handle){

}
void Shader::SetShader(shaderType type, string path) {
    switch (type) {
        case VERTEX:   vertexShader   = LoadShader(path); break;
        case FRAGMENT: fragmentShader = LoadShader(path); break;
    }
}
bgfx::ShaderHandle Shader::LoadShader(string path) {

//    size_t shaderLen = strlen(shaderPath);
//    size_t fileLen = strlen(path);
//    char* filePath = (char*)calloc(1, shaderLen + fileLen + 1);
//    memcpy(filePath, shaderPath, shaderLen);
//    memcpy(&filePath[shaderLen], path, fileLen);

    std::ifstream file(path, std::ifstream::ate | std::ifstream::binary);

//    FILE* file;
//    fopen_s(&file, path, "rb");
//    fseek(file, 0, SEEK_END);
//    long fileSize = ftell(file);
//    fseek(file, 0, SEEK_SET);

    const bgfx::Memory *mem = bgfx::alloc(fileSize + 1);
    fread(mem->data, 1, fileSize, file);
    mem->data[mem->size - 1] = '\0';
    fclose(file);

    return bgfx::createShader(mem);
}

}