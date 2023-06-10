/**
 * Check Script.tpp for template definitions
 */
/*
 MIT License
 
 Copyright (c) 2021 kualta <contact@kualta.dev>
 
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
#ifndef CORE_SCRIPT_H
#define CORE_SCRIPT_H

#include <core/Essentials.h>
#include <core/IComponent.h>
#include <core/ScriptedBehaviour.h>

namespace core {

/**
 * Handles lifetime of ScriptedBehaviour, passes all ITcker calls to it
 */
template<typename T>
class Script : public IComponent {
static_assert(std::is_base_of<ScriptedBehaviour, T>::value, "Script T must inherit from ScriptedBehaviour");

public:
    
    Script(Entity& parent, const string& name = "Script");
    ~Script();

protected:
    
    void FixedTick() override;
    void EarlyTick() override;
    void Start() override;
    void Tick() override;
    void Stop() override;
    void LateTick() override;
    

    /** Attached ScriptedBehaviour */
    ScriptedBehaviour* scriptedBehaviour;
};

} // namespace core

#include "Script.tpp"

#endif //CORE_SCRIPT_H
