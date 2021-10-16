#ifndef CORE_SCRIPT_H
#define CORE_SCRIPT_H

#include <core/Essentials.h>
#include <core/IComponent.h>
#include <core/ScriptedBehaviour.h>

namespace core {

template<typename T>
class Script : public IComponent {
    static_assert(std::is_base_of<core::ScriptedBehaviour, T>::value, "Script T must inherit from ScriptedBehaviour");

public:
    Script(Entity& parent, const string& name = "Script");
    ~Script();

    void FixedTick() override { scriptObj->FixedTick(); }

    void EarlyTick() override { scriptObj->EarlyTick(); };

    void Tick()      override { scriptObj->Tick(); };

    void LateTick()  override { scriptObj->LateTick(); }

protected:

    ScriptedBehaviour* scriptObj;
};

template<typename T>
Script<T>::Script(Entity &parent, const string &name)
: IComponent(parent, name) {
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
