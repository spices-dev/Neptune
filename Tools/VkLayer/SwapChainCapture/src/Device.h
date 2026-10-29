#include "Core.h"

namespace Neptune::VkLayer {
    
    inline PFN_vkVoidFunction vkGetDeviceProcAddr(VkDevice device, const char* pName)
    {
        return nullptr;
    }
    
}