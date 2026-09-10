/**
* @file Extension.h.
* @brief The Extension Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Core/Container/KVTuple.h"
#include "Device/Graphics/Backend/Vulkan/Core.h"

namespace Neptune::Vulkan::Extension {
    
    /**
    * @brief Enum of Extension State.
    */
    enum class EExtensionState : uint8_t
    {
        Core = 0,       // @brief Core.
        Extent,         // @brief Extent.
    };
    
    /**
    * @brief Concept: Is VkStructure.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsVkStructure = requires(T t) {
        t.sType;
        t.pNext;
    };
    
    /**
    * @brief Vulkan::Extension Class.
    * This class defines the Vulkan::Extension behaves.
    */
    class Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit Extension(EExtensionState state = EExtensionState::Core) : m_State(state) {}
        
        /**
        * @brief Destructor Function.
        */
        virtual ~Extension() = default;

        /**
        * @brief Get EExtensionState.
        * 
        * @return Returns EExtensionState.
        */
        EExtensionState GetState() const { return m_State; }
        
        /**
        * @brief Add VkInstance Extension Requirement.
        * 
        * @param[in] name Extension Name.
        * @param[in] value On/Off.
        */
        void AddInstanceExtensions(const char* name, bool value = true);
        
        /**
        * @brief Add VkPhysicalDevice/VkDevice Extension Requirement.
        * 
        * @param[in] name Extension Name.
        * @param[in] value On/Off.
        */
        void AddDeviceExtensions(const char* name, bool value = true);
        
        /**
        * @brief Get VkInstance Extension Requirement.
        * 
        * @return Returns VkInstance Extension Requirement.
        */
        const std::unordered_map<const char*, bool>& GetInstanceExtensions() const { return m_InstanceExtensions; }
        
        /**
        * @brief Get VkPhysicalDevice/VkDevice Extension Requirement.
        * 
        * @return Returns VkPhysicalDevice/VkDevice Extension Requirement.
        */
        const std::unordered_map<const char*, bool>& GetDeviceExtensions() const { return m_DeviceExtensions; }

        /**
        * @brief Build Device Feature Chain.
        * 
        * @param[in,out] pNext pNext Chain.
        * @param[in] filter Feature Filter.
        */
        virtual void BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter) {}
        
        /**
        * @brief Build Device Property Chain.
        * 
        * @param[in,out] pNext pNext Chain.
        * @param[in] filter Feature Filter.
        */
        virtual void BuildPropertyChain(void**& pNext, const std::function<bool(VkStructureType)>& filter) {}
        
        /**
        * @brief Build Device Surface Capabilities Chain.
        * 
        * @param[in,out] pNext pNext Chain.
        * @param[in] filter SurfaceCapabilities Filter.
        */
        virtual void BuildSurfaceCapabilitiesChain(void**& pNext, const std::function<bool(VkStructureType)>& filter) {}
        
        /**
        * @brief Is Device Features satisfied.
        * 
        * @return Returns true if satisfied.
        */
        virtual bool IsFeaturesSatisfied() { return true; }
        
        /**
        * @brief Is Device Properties satisfied.
        * 
        * @return Returns true if satisfied.
        */
        virtual bool IsPropertiesSatisfied() { return true; }
        
        /**
        * @brief Is Device Surface Capabilities satisfied.
        * 
        * @return Returns true if satisfied.
        */
        virtual bool IsSurfaceCapabilitiesSatisfied() { return true; }
        
        /**
        * @brief Is Device Queue satisfied.
        * 
        * @param[in] queues VkQueueFlagBits.
        * 
        * @return Returns true if satisfied.
        */
        virtual bool IsQueueSatisfied(const std::unordered_set<VkQueueFlagBits>& queues) const { return true; }
        
        /**
        * @brief Is Device Surface Formats satisfied.
        * 
        * @param[in] formats VkSurfaceFormatKHR.
        * 
        * @return Returns true if satisfied.
        */
        virtual bool IsSurfaceFormatsSatisfied(const std::vector<VkSurfaceFormatKHR>& formats) { return true; }
        
        template<typename T>
        requires IsVkStructure<RemoveRef<T>>
        void LinkToChain(void**& pNext, const std::function<bool(VkStructureType)>& filter, T& t)
        {
            NEPTUNE_PROFILE_ZONE

            if (!std::invoke(filter, t.sType)) return;
            
            *pNext = &t;

            pNext  = &t.pNext;

            *pNext = nullptr;
        }
        
    private:
        
        EExtensionState m_State;                                         // @brief EExtensionState.
        std::unordered_map<const char*, bool> m_InstanceExtensions;      // @brief VkInstance Extensions.
        std::unordered_map<const char*, bool> m_DeviceExtensions;        // @brief VkPhysicalDevice/VkDevice Extensions.
    };
}

#endif