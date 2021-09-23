#ifndef CORE_GUIBEHAVIOUR_H
#define CORE_GUIBEHAVIOUR_H

#include "Essentials.h"
#include "Instantiable.h"
#include "ScriptedBehaviour.h"

namespace core {

class GUIBehaviour : public ScriptedBehaviour, public Instantiable<GUIBehaviour> {
public:

    virtual void OnGUI() { };

};

} // namespace core


#endif //CORE_GUIBEHAVIOUR_H
