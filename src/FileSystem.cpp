/*
 MIT License
 
 Copyright (c) 2021 lectroMathew <contact@lectro.moe>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */
#include <core/FileSystem.h>
#include <fstream>

namespace core {

int64_t FileSystem::GetFileSize(const string& path) {
    std::ifstream file(path, std::ifstream::ate | std::ifstream::binary);
    return file.tellg();
}
std::vector<char> FileSystem::ReadFile(const string& filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        Logger::Log(IMPORT, ERR_HERE) << "Failed to open file at " << filename;
        throw std::runtime_error("Failed to open file at " + filename);
    }

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);
    Logger::Log(MEMORY, INFO) << "|ALLOC| Buffer size : " << fileSize << " bytes";
    file.seekg(0);
    file.read(buffer.data(), static_cast<int32_t>(fileSize));
    file.close();

    Logger::Log(IMPORT, INFO) << "Read " << buffer.size() << " bytes from " << filename;

    return buffer;
}

}
