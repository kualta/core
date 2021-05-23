/*
 * This is a stand-alone header file. No ITicker.cpp is presented.
 */
#ifndef CORE_ITICKER_H
#define CORE_ITICKER_H

namespace core {

/**
 * Base ticker class, defines update calls.
 *
 * @remark Update flow usually means that higher-ticked object pass
 * the tick down to their updatable children
 */
class ITicker {
public:

    /**
     * Update with fixed delta, called before Tick()
     *      @Includes Physics
     */
    virtual void FixedTick() { };

    /**
     * Main update function
     *      @Includes Modules update
     *      @Includes Input update
     *      @Includes Window update
     *      @Includes Rendering
     */
    virtual void Tick() { };

    /**
     * Late update function, called after current frame has been rendered
     */
    virtual void LateTick() { };

};

}

#endif //CORE_ITICKER_H
