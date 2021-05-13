#ifndef CORE_FILESYSTEM_H
#define CORE_FILESYSTEM_H

#include "Essential.h"

#include <bgfx/bgfx.h>

namespace core {

class FileSystem {
public:

    static int64_t GetFileSize(const string& path);

    static const bgfx::Memory* ReadFileToMemory(const string& path, int32_t size);

protected:

};



}

#endif //CORE_FILESYSTEM_H
