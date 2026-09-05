/**
* @file Polygon.cpp.
* @brief The Polygon Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Polygon.h"

namespace Neptune::SOP {
    
    void PolygonDesc::UploadToDevice() const
    {
        NEPTUNE_PROFILE_ZONE
        
        Update_Attribute(positions)
        Update_Attribute(normals)
        Update_Attribute(colors)
        Update_Attribute(texCoords)
        Update_Attribute(vertices)
        Update_Attribute(primitivePoints)
        Update_Attribute(primitiveVertices)
        Update_Attribute(primitiveLocations)
        Update_Attribute(primitiveLocations)
        Update_Attribute(meshlets)
        Update_Attribute(lods)
    }
    
    void Polygon::CreateRHIBuffer() const
    {
        NEPTUNE_PROFILE_ZONE

        m_Desc.UploadToDevice();
    }
}