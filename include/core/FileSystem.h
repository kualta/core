#ifndef CORE_FILESYSTEM_H
#define CORE_FILESYSTEM_H

#include "Essential.h"
#include "Logger.h"

namespace core {

class FileSystem {
public:

    static int64_t GetFileSize(const string& path);
    static std::vector<char> ReadFile(const string& filename);

protected:

};



}

#endif //CORE_FILESYSTEM_H
