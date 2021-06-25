#ifndef CORE_VKRENDERMODULE_H
#define CORE_VKRENDERMODULE_H

#include <core/Essential.h>
#include <core/Modules/IRenderModule.h>

#include <vulkan/vulkan.h>
#include <optional>

namespace core {

typedef VkRenderModule RenderModule;

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;


    bool IsComplete() {
        return graphicsFamily.has_value()
            && presentFamily.has_value();
    }
};

class VkRenderModule : public IRenderModule {
    friend class VkWindowRenderer;
public:
    VkRenderModule();
    ~VkRenderModule();

    void Frame() override;

    bool isReady();

private:
    void Init(Window& window);
    void Cleanup();
    void CreateInstance();
    void CreateSurface(Window& window);
    void CreateLogicalDevice();
    void CheckValidationLayerSupport();
    bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
    void PickPhysicalDevice();
    void AddDebugExtensions();
    void AddValidationLayers();
    void SetupDebugMessenger();

    bool IsDeviceSuitable(VkPhysicalDevice pDevice);
    QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

    void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

    static VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                             VkDebugUtilsMessageTypeFlagsEXT messageType,
                                             const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                                             void* pUserData);
    static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
                                                 const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                                                 const VkAllocationCallbacks* pAllocator,
                                                 VkDebugUtilsMessengerEXT* pDebugMessenger);
    static void DestroyDebugUtilsMessengerEXT(VkInstance instance,
                                              VkDebugUtilsMessengerEXT debugMessenger,
                                              const VkAllocationCallbacks* pAllocator);
    static void LogDebugObjectsInfo(const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData);

    VkInstance               instance;
    VkPhysicalDevice         physicalDevice { VK_NULL_HANDLE };
    VkDevice                 device;
    VkQueue                  graphicsQueue;
    VkQueue                  presentQueue;
    VkSurfaceKHR             surface;
    VkDebugUtilsMessengerEXT debugMessenger;

    bool initialized             { false };
    bool validationLayersEnabled { false };

    std::vector<const char*> requiredExtensions;
    std::vector<const char*> requiredLayers;

};

}

#endif //CORE_VKRENDERMODULE_H
