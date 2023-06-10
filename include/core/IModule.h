/*
 * This is a stand-alone header file. No IModule.cpp is presented.
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
#ifndef CORE_IMODULE_H
#define CORE_IMODULE_H

#include "Essentials.h"
#include "Instantiable.h"
#include "ObjectTag.h"
#include "ITicker.h"
#include "Logger.h"

#include <utility>

namespace core {

class IModule : public Instantiable<IModule>, public Object, public ITicker {
public:


    ObjectTag tag {GENERAL };

protected:
    explicit IModule(const string& moduleName = "Unnamed", ObjectTag moduleTag = GENERAL)
    : Object(moduleName + " module"), tag(moduleTag)
    {
        Logger::Log(tag, INFO) << "Initialized " << name;
    };
    ~IModule() {
        Logger::Log(tag, INFO) << "Destroyed " << name;
    }

};


}

#endif //CORE_IMODULE_H
