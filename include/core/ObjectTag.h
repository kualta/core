#ifndef CORE_OBJECTTAG_H
#define CORE_OBJECTTAG_H

enum ObjectTag {
    INTERNAL,   // Engine-related
    OBJECT,     // Object-related
    RENDER,     // Render-related
    IMPORT,     // Import-related
    MEMORY,     // Memory-management

    NETWORK,    // Network module
    PHYSICS,    // Physics module
    WINDOW,     // Window module
    MODULE,     // Generic module
    SCENE,      // Scene module

    GENERAL     // Other
};

#endif //CORE_OBJECTTAG_H
