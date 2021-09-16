#ifndef CORE_OBJECTTAG_H
#define CORE_OBJECTTAG_H

enum objectTag {
    INTERNAL, // For engine logs
    GENERAL,  // For other logs
    NETWORK,  // Network module logs
    PHYSICS,  // Physics module logs
    MEMORY,   // For memory logs (allocs etc.)
    OBJECT,   // Object logs
    WINDOW,   // Window module logs
    RENDER,   // Rendering module logs
    IMPORT,   // Importing logs
    SCENE,    // Scene module logs
    INPUT_T,  // Input module logs // FIXME Naming
};

#endif //CORE_OBJECTTAG_H
