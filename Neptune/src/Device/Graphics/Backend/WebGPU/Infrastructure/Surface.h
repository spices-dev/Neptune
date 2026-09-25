/**
* @file Surface.h.
* @brief The Surface Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Backend/WebGPU/Unit/Surface.h"
#include "Device/Graphics/Backend/WebGPU/Unit/Texture.h"
#include "Device/Graphics/Backend/WebGPU/Unit/TextureView.h"

#include <glm/vec2.hpp>

namespace Neptune::WebGPU {

    /**
    * @brief Surface Property.
    */
    struct SurfaceProperty
    {
        WGPUSurfaceCapabilities         capabilities{};                    // @brief WGPUSurfaceCapabilities.
        glm::uvec2                      surfaceSize = {100, 100};      // @brief Surface Extent2D.
    };
    
    using ISurface = IInfrastructure<class Surface, EInfrastructure::Surface>;

    /**
    * @brief WebGPU::Surface Class.
    * This class defines the WebGPU::Surface behaves.
    */
    class Surface : public Infrastructure
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context Context.
        * @param[in] e EInfrastructure.
        * @param[in] extent Window Extent.
        */
        Surface(Context& context, EInfrastructure e, const glm::uvec2& extent);

        /**
        * @brief Destructor Function.
        */
        ~Surface() override = default;

        /**
        * @brief Get Unit Handle.
        *
        * @return Returns Unit Handle.
        */
        const Unit::Surface::Handle& Handle() const { return m_Surface.GetHandle(); }

        /**
        * @brief Get Texture Unit Handle.
        *
        * @return Returns Texture Unit Handle.
        */
        const Unit::Texture::Handle& Texture() const { return m_SurfaceTexture.texture; }
        
        /**
        * @brief Get TextureView Unit Handle.
        *
        * @return Returns TextureView Unit Handle.
        */
        const Unit::TextureView::Handle& TextureView() const { return m_SurfaceView->GetHandle(); }
        
        /**
        * @brief Get Next Image.
        */
        bool GetNextImage();
        
        /**
        * @brief Present.
        * 
        * @return Returns true if succeeded.
        */
        bool Present() const;
        
        /**
        * @brief Get Surface Capabilities.
        */
        const SurfaceProperty& GetCapabilities() const { return m_SurfaceProperty; }
        
    private:

        /**
        * @brief Create Surface.
        */
        void Create();

        /**
        * @brief Configure Surface.
        */
        void Configure() const;
        
        /**
        * @brief Configure Surface.
        */
        void Unconfigure() const;

    private:

        Unit::Surface            m_Surface;                  // @brief This Surface.
        WGPUSurfaceTexture       m_SurfaceTexture;           // @brief WGPUSurfaceTexture.
        UP<Unit::TextureView>    m_SurfaceView;              // @brief Surface TextureView.
        SurfaceProperty          m_SurfaceProperty;          // @brief SurfaceProperty.
    };

}

#endif