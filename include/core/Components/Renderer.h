#ifndef CORE_RENDERER_H
#define CORE_RENDERER_H

#include <core/Essential.h>
#include <core/Component.h>
#include <core/Instantiable.h>

namespace core {

class Renderer : public Component, public Instantiable<Renderer> {
public:

    void Draw();


};

}

#endif //CORE_RENDERER_H
