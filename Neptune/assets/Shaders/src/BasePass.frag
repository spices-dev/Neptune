/**
* @file BasePass.frag.
* @brief This Shader Defines BasePass Fragment Shader Behaver.
* @author Spices.
*/

/************************************Pre Compile*******************************************/

#version 460

#extension GL_GOOGLE_include_directive : enable    /* @brief Enable include Macro. */

#include "Header/Core.h"
#include "Header/PreRendererLayout.glsl"

/*****************************************************************************************/
        
layout(set = 1, binding = 0) uniform sampler2D videoImage;

/************************************Fragment Input***************************************/

/**
* @brief Fragment Shader Input From Vertex Shader.
*/
layout(location = 0) in vec2 texCoord;

/*****************************************************************************************/
        
/************************************Fragment Output**************************************/

/**
* @brief Fragment Shader Output to FrameBuffer.
*/
layout(location = 0) out vec4 outSceneColor;

/*****************************************************************************************/
        
/**********************************Shader Entry*******************************************/
        
void main()
{
    //outSceneColor = texture(videoImage, texCoord);

    if(prd.rayDirection.y > 0.0f)
    {
        outSceneColor = mix(vec3(1.0f), vec3(0.25f, 0.5f, 1.0f), prd.rayDirection.y);
    }
    else
    {
        outSceneColor   = vec3(1.0f);
    }
}

/*****************************************************************************************/