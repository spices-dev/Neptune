/**
* @file RenderBackendInterface.h.
* @brief The Interface Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_WINDOW_SDL

#include "Core/Core.h"
#include "Render/Frontend/Enum.h"

struct SDL_Window;

namespace Neptune::SDL {

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
        * @brief Interface of SDL Hint Configuration with RenderBackend.
        * 
        * @return Returns Window Flag.
        */
        virtual uint64_t Hint() const = 0;

        /**
        * @brief Interface of SDL API Load Configuration with RenderBackend.
        * 
        * @param[in] handle SDL_Window.
        */
        virtual void APILoad(SDL_Window* handle) const = 0;
        
        /**
        * @brief Interface of SDL API UnLoad Configuration with RenderBackend.
        */
        virtual void APIUnLoad() const = 0;
        
        /**
        * @brief Interface of Get SDL Window Extension.
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
        * @brief Interface of SDL Hint Configuration with RenderBackend.
        * 
        * @return Returns Window Flag.
        */
        uint64_t Hint() const override;

        /**
        * @brief Interface of SDL API Load Configuration with RenderBackend.
        * 
        * @param[in] handle SDL_Window.
        */
        void APILoad(SDL_Window* handle) const override;
        
        /**
        * @brief Interface of SDL API UnLoad Configuration with RenderBackend.
        */
        void APIUnLoad() const override;
        
        /**
        * @brief Interface of Get SDL Window Extension.
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
        * @brief Interface of SDL Hint Configuration with RenderBackend.
        * 
        * @return Returns Window Flag.
        */
        uint64_t Hint() const override;

        /**
        * @brief Interface of SDL API Load Configuration with RenderBackend.
        * 
        * @param[in] handle SDL_Window.
        */
        void APILoad(SDL_Window* handle) const override {}
        
        /**
        * @brief Interface of SDL API UnLoad Configuration with RenderBackend.
        */
        void APIUnLoad() const override {}
        
        /**
        * @brief Interface of Get SDL Window Extension.
        *
        * @return Returns Window Extension.
        */
        std::vector<const char*> Extension() const override;
    };

#endif
    
#ifdef NP_GRAPHICS_DIRECT3D11
    
    /**
    * @brief Direct3D11 APIInterface.
    */
    class Direct3D11Interface : public APIInterface
    {
    public:

        /**
        * @brief Destructor Function.
        */
        ~Direct3D11Interface() override = default;
        
        /**
        * @brief Interface of SDL Hint Configuration with RenderBackend.
        * 
        * @return Returns Window Flag.
        */
        uint64_t Hint() const override;

        /**
        * @brief Interface of SDL API Load Configuration with RenderBackend.
        * 
        * @param[in] handle SDL_Window.
        */
        void APILoad(SDL_Window* handle) const override {}
        
        /**
        * @brief Interface of SDL API UnLoad Configuration with RenderBackend.
        */
        void APIUnLoad() const override {}
        
        /**
        * @brief Interface of Get SDL Window Extension.
        *
        * @return Returns Window Extension.
        */
        std::vector<const char*> Extension() const override { return {}; }
    };
    
#endif
    
#ifdef NP_GRAPHICS_DIRECT3D12
    
    /**
    * @brief Direct3D12 APIInterface.
    */
    class Direct3D12Interface : public APIInterface
    {
    public:

        /**
        * @brief Destructor Function.
        */
        ~Direct3D12Interface() override = default;
        
        /**
        * @brief Interface of SDL Hint Configuration with RenderBackend.
        * 
        * @return Returns Window Flag.
        */
        uint64_t Hint() const override;

        /**
        * @brief Interface of SDL API Load Configuration with RenderBackend.
        * 
        * @param[in] handle SDL_Window.
        */
        void APILoad(SDL_Window* handle) const override {}
        
        /**
        * @brief Interface of SDL API UnLoad Configuration with RenderBackend.
        */
        void APIUnLoad() const override {}
        
        /**
        * @brief Interface of Get SDL Window Extension.
        *
        * @return Returns Window Extension.
        */
        std::vector<const char*> Extension() const override { return {}; }
    };
    
#endif
    
#ifdef NP_GRAPHICS_METAL
    
    /**
    * @brief Metal APIInterface.
    */
    class MetalInterface : public APIInterface
    {
    public:

        /**
        * @brief Destructor Function.
        */
        ~MetalInterface() override = default;
        
        /**
        * @brief Interface of SDL Hint Configuration with RenderBackend.
        * 
        * @return Returns Window Flag.
        */
        uint64_t Hint() const override;

        /**
        * @brief Interface of SDL API Load Configuration with RenderBackend.
        * 
        * @param[in] handle SDL_Window.
        */
        void APILoad(SDL_Window* handle) const override {}
        
        /**
        * @brief Interface of SDL API UnLoad Configuration with RenderBackend.
        */
        void APIUnLoad() const override {}
        
        /**
        * @brief Interface of Get SDL Window Extension.
        *
        * @return Returns Window Extension.
        */
        std::vector<const char*> Extension() const override { return {}; }
    };
    
#endif

}

#endif