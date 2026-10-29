#include <vulkan/vulkan.h>
#include <vulkan/vk_layer.h>

#ifdef _MSC_VER
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __attribute__((visibility("default")))
#endif