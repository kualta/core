#ifndef CORE_IDRAWABLE_H
#define CORE_IDRAWABLE_H

#include "Math.h"

namespace core {

class IDrawable {
public:

    virtual void Draw() = 0;
    virtual void SetProjectionMatrix(Matrix4& mtx) = 0;

};

}

#endif //CORE_IDRAWABLE_H
