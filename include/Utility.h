#ifndef CORE_UTILITY_H
#define CORE_UTILITY_H

#include "core.h"

#include <memory>
#include <vector>


namespace core {

std::vector<std::shared_ptr<Window>> windows_pool;

unsigned int MakeWindow(const std::string &title, Rect rect);


}

#endif //CORE_UTILITY_H
