#ifndef CORE_RENDERMANAGER_H
#define CORE_RENDERMANAGER_H

#include "Singleton.h"
#include "ObjectId.h"
#include "Window.h"


namespace core {


class RenderManager : public Singleton<RenderManager>, public ObjectId {
public:

    void CreateRenderer(const Window& window);

protected:

private:

};


}



#endif //CORE_RENDERMANAGER_H
