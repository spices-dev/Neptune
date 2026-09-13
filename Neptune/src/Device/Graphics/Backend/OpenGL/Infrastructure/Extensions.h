/**
* @file Extensions.h.
* @brief The Extensions Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Backend/OpenGL/Extension/Context.h"

namespace Neptune::OpenGL {

    using IExtensions     = IInfrastructure<class Extensions, EInfrastructure::Extensions>;

    /**
    * @brief OpenGL::Extensions Class.
    * This class defines the OpenGL::Extensions behaves.
    */
    class Extensions : public Infrastructure
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context Context.
        * @param[in] e EInfrastructure.
        */
        Extensions(Context& context, EInfrastructure e);

        /**
        * @brief Destructor Function.
        */
        ~Extensions() override = default;

        /**
        * @brief Get ApiVersion Name.
        * 
        * @return Returns ApiVersion Name.
        */
        const char* GetApiVersionName() const;
        
    private:

        /**
        * @brief Create Fence.
        */
        void Create();

        /**
        * @brief Registry Extensions.
        */
        void Registry();
        
        /**
        * @brief Is Extension Meet Demand.
        * 
        * @return Returns true if meets.
        */
        bool IsExtensionMeetDemand();
        
        /**
        * @brief Is Property Meet Demand.
        *
        * @return Returns true if meets.
        */
        bool IsPropertyMeetDemand();
        
    private:

        Extension::EContext<EExtension> m_Context;              // @brief This EContext.
        uint32_t m_ApiVersion;                                  // @brief Runtime Version.
        std::vector<const char*> m_Extensions;                  // @brief Extensions.
    };
	
}

#endif