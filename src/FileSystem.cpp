#include <core/FileSystem.h>
#include <fstream>

namespace core {

int64_t FileSystem::GetFileSize(const string& path) {
    std::ifstream file(path, std::ifstream::ate | std::ifstream::binary);
    return file.tellg();
}
const bgfx::Memory* FileSystem::ReadFileToMemory(const string &path, int32_t size) {
    std::ifstream file(path, std::ios::binary);

    const bgfx::Memory* mem = bgfx::alloc(size + 1);

    file.read(reinterpret_cast<char *>(mem->data), size);

    mem->data[mem->size - 1] = '\0';

    return mem;
}

}
