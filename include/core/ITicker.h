/*
 * This is a stand-alone header file. No ITicker.cpp is presented.
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
