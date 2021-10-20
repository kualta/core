/*
 * This is a stand-alone header file. No ITicker.cpp is presented.
 */

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
#ifndef CORE_ITICKER_H
#define CORE_ITICKER_H

namespace core {

/**
 * Base ticker class, defines update calls.
 */
class ITicker {
public:

    /**
     * Called before entering the Main Loop
     */
    virtual void Start() { };

    /**
     * Update with fixed delta time
     */
    virtual void FixedTick() { };

    /**
     * Early update function
     * @note Called before current frame is rendered
     */
    virtual void EarlyTick() { };

    /**
     * Main update function
     * @note Rendering of the current frame
     */
    virtual void Tick() { };

    /**
     * Late update function
     * @note Called after current frame was rendered
     */
    virtual void LateTick() { };

    /**
     * Called after Main Loop exit is requested
     */
    virtual void Stop() { };

};

}

#endif //CORE_ITICKER_H
