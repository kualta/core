#ifndef CORE_IMESH_H
#define CORE_IMESH_H

namespace core {

class IMesh {
public:

protected:

    virtual void UpdateVertexBuffer() { };
    virtual void UpdateIndexBuffer() { };

};

}

#endif //CORE_IMESH_H
