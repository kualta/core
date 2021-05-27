#ifndef CORE_FILESYSTEM_H
#define CORE_FILESYSTEM_H

#include "Essential.h"

#include <bgfx/bgfx.h>

namespace core {

class FileSystem {
public:

    static int64_t GetFileSize(const string& path);

    static const bgfx::Memory* ReadFileToMemory(const string& path, size_t size);

    template<typename T>
    static const bgfx::Memory* CopyToMemory(T* buff, size_t buffSize) {
        size_t bufferSize = buffSize * sizeof(T);

        const bgfx::Memory* mem = bgfx::alloc(bufferSize);
        std::memcpy(mem->data, buff, bufferSize);

        return mem;
    };

protected:

};



}

#endif //CORE_FILESYSTEM_H
