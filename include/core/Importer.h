#ifndef CORE_IMPORTER_H
#define CORE_IMPORTER_H

#include "Essential.h"

#include <Corrade/PluginManager/Manager.h>
#include <Magnum/Trade/AbstractImporter.h>

using namespace Magnum;
namespace core {

class Importer {
public:

    static PluginManager::Manager<Trade::AbstractImporter> manager;

};

}

#endif //CORE_IMPORTER_H
