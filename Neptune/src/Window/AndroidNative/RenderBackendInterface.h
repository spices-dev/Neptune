/**
* @file RenderBackendInterface.h.
* @brief The Interface Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_WINDOW_ANDROIDNATIVE

#include "Core/Core.h"
#include "Render/Frontend/Enum.h"

namespace Neptune::AndroidNative {

    /**
    * @brief APIInterface Class.
    */
    class APIInterface
    {
    public:

        /**
        * @brief Destructor Function.
        */
        virtual ~APIInterface() = default;
        
        /**
        * @brief Interface of Get GLFW Window Extension.
        *
        * @return Returns Window Extension.
        */
        virtual std::vector<const char*> Extension() const = 0;
    };

    /**
    * @brief Create APIInterface With RenderBackend.
    * 
    * @param[in] backend RenderBackendEnum.
    * 
    * @return Returns APIInterface.
    */
    UP<APIInterface> CreateInterface(RenderBackendEnum backend);

#ifdef NP_GRAPHICS_OPENGL
    
    /**
    * @brief OpenGL APIInterface.
    */
    class OpenGLInterface : public APIInterface
    {
    public:
        
        /**
        * @brief Destructor Function.
        */
        ~OpenGLInterface() override = default;
        
        /**
        * @brief Interface of Get GLFW Window Extension.
        *
        * @return Returns Window Extension.
        */
        std::vector<const char*> Extension() const override { return {}; }
    };

#endif
    
#ifdef NP_GRAPHICS_VULKAN
    
    /**
    * @brief Vulkan APIInterface.
    */
    class VulkanInterface : public APIInterface
    {
    public:
        
        /**
        * @brief Destructor Function.
        */
        ~VulkanInterface() override = default;
        
        /**
        * @brief Interface of Get GLFW Window Extension.
        *
        * @return Returns Window Extension.
        */
        std::vector<const char*> Extension() const override;
    };
    
#endif

}

#endif