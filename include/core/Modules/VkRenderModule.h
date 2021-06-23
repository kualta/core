#ifndef CORE_VKRENDERMODULE_H
#define CORE_VKRENDERMODULE_H

#include <core/Essential.h>
#include <core/Modules/IRenderModule.h>

#include <vulkan/vulkan.h>

namespace core {

class VkRenderModule : public IRenderModule {
public:
    VkRenderModule();
    ~VkRenderModule();

    void Frame() override;

private:
    void Init();
    void Cleanup();
    void CreateInstance();

    VkInstance instance;

};

}

#endif //CORE_VKRENDERMODULE_H
