#ifndef CORE_GUIBEHAVIOUR_H
#define CORE_GUIBEHAVIOUR_H

#include "core/Essentials.h"
#include "core/Instantiable.h"
#include "core/ScriptedBehaviour.h"

namespace core {

class GUIBehaviour : public ScriptedBehaviour, public Instantiable<GUIBehaviour> {
public:

    virtual void OnGUI() { };

};

} // namespace core


#endif //CORE_GUIBEHAVIOUR_H
