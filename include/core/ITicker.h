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
     * Called before main loop is entered, but after Core has been built
     */
    virtual void Start() { };

    /**
     * Update with fixed delta, called before Tick()
     *      @Includes Physics
     */
    virtual void FixedTick() { };

    /**
     * Early update function, called before current frame is rendered
     */
    virtual void EarlyTick() { };

    /**
     * Main update function
     *      @Includes Modules update
     *      @Includes inputModule update
     *      @Includes Window update
     *      @Includes Rendering
     */
    virtual void Tick() { };

    /**
     * Late update function, called after current frame has been rendered
     */
    virtual void LateTick() { };

    /**
     * Called after main loop exit is requested
     */
    virtual void Stop() { };

};

}

#endif //CORE_ITICKER_H
