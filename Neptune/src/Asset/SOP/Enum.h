/**
* @file Enum.h.
* @brief The Enum Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

namespace Neptune {
    
    /**
    * @brief Enum of Object.
    */
    enum class EObject : uint8_t
    {
        Undefined = 0,     // @brief Undefined.
        Polygon,           // @brief Polygon.
        GS3D,              // @brief 3D Gaussian Splatting.
		
        Count
    };
	
    /**
    * @brief Enum of CullMode.
    */
    enum class ECullMode : uint8_t
    {
        None = 0,       // @brief Cull None.
        Front,          // @brief Cull Front.
        Back,           // @brief Cull Back.

        Count
    };
    
    /**
    * @brief Enum of CullMode.
    */
    enum class ETopology : uint8_t
    {
        TriangleList = 0,       // @brief TriangleList.
        TriangleStrip,          // @brief TriangleStrip.

        Count
    };

}