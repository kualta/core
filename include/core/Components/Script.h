#ifndef CORE_SCRIPT_H
#define CORE_SCRIPT_H

#include <core/Essential.h>
#include <core/Component.h>
#include <core/ScriptBehaviour.h>

namespace core {

template<typename T>
class Script : public Component {
    static_assert(std::is_base_of<core::ScriptBehaviour, T>::value, "Script T must inherit from ScriptBehaviour");

public:
    Script(Entity& parent, const string& name = "Script");
    ~Script();

    void FixedTick() { scriptObj->FixedTick(); }

    void Tick() { scriptObj->Tick(); };

    void LateTick() { scriptObj->LateTick(); }

protected:

    ScriptBehaviour* scriptObj;
};

template<typename T>
Script<T>::Script(Entity &parent, const string &name) : Component(parent, name + " component") {
    scriptObj = new T;
    scriptObj->SetEntity(entity);
}
template<typename T>
Script<T>::~Script() {
    delete scriptObj;
}
// class

} // namespace core

#endif //CORE_SCRIPT_H
