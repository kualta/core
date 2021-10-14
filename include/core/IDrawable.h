#ifndef CORE_IDRAWABLE_H
#define CORE_IDRAWABLE_H

namespace core {

class IDrawable {
public:

    virtual void Draw() = 0;

};

class ICamDrawable {
public:

    virtual void Draw(Camera& camera) = 0;

};

}

#endif //CORE_IDRAWABLE_H
