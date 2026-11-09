/**
* @file AccessibleInfrastructure.h.
* @brief The AccessibleInfrastructure Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

#include <variant>

#ifdef NP_GRAPHICS_DIRECT3D11
namespace Neptune::Direct3D11      { struct AContext; }
#endif
#ifdef NP_GRAPHICS_DIRECT3D12
namespace Neptune::Direct3D12      { struct AContext; }
#endif
#ifdef NP_GRAPHICS_METAL
namespace Neptune::Metal           { struct AContext; }
#endif
#ifdef NP_GRAPHICS_OPENGL
namespace Neptune::OpenGL          { struct AContext; }
#endif
#ifdef NP_GRAPHICS_OPENGLES
namespace Neptune::OpenGLES        { struct AContext; }
#endif
#ifdef NP_GRAPHICS_VULKAN
namespace Neptune::Vulkan          { struct AContext; }
#endif
#ifdef NP_GRAPHICS_WEBGL
namespace Neptune::WebGL           { struct AContext; }
#endif
#ifdef NP_GRAPHICS_WEBGPU
namespace Neptune::WebGPU          { struct AContext; }
#endif

namespace Neptune::Graphic {
    
    using AInfrastructures = std::variant<
          std::monostate
#ifdef NP_GRAPHICS_DIRECT3D11
        , SP<Direct3D11::AContext>
#endif
#ifdef NP_GRAPHICS_DIRECT3D12
        , SP<Direct3D12::AContext>
#endif
#ifdef NP_GRAPHICS_METAL
        , SP<Metal::AContext>
#endif
#ifdef NP_GRAPHICS_OPENGL
        , SP<OpenGL::AContext>
#endif
#ifdef NP_GRAPHICS_OPENGLES
        , SP<OpenGLES::AContext>
#endif
#ifdef NP_GRAPHICS_VULKAN
        , SP<Vulkan::AContext>
#endif
#ifdef NP_GRAPHICS_WEBGL
        , SP<WebGL::AContext>
#endif
#ifdef NP_GRAPHICS_WEBGPU
        , SP<WebGPU::AContext>
#endif
    >;

    /**
    * @brief Check AInfrastructures is valid.
    * 
    * @param v AInfrastructures.
    * 
    * @return Returns true if valid.
    */
    inline bool IsValid(const AInfrastructures& v)
    {
        return !std::holds_alternative<std::monostate>(v);
    }
    
    /**
    * @brief Get AInfrastructures Context.
    * 
    * @tparam T Context.
    * @param v AInfrastructures.
    * 
    * @return Returns Context.
    */
    template<typename T>
    const SP<T>& GetContext(const AInfrastructures& v)
    {
        static const SP<T> null;
        
        auto* sp = std::get_if<SP<T>>(&v);
        
        return sp ? *sp : null;
    }
    
}