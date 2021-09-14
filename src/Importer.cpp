#include <core/Importer.h>

namespace core {

PluginManager::Manager<Trade::AbstractImporter> Importer::manager { };

}