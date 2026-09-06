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

    vec2 ndcDir  = vec2(2.0 * texCoord.x - 1.0, 2.0 * texCoord.y - 1.0);
        
    vec4 clipDir = vec4(ndcDir, 1.0, 1.0);

    vec4 viewDir = view.inProjection * clipDir;

    viewDir /= viewDir.w;

    vec3 worldDir = normalize(view.inView * vec4(viewDir.xyz, 0.0)).xyz;

    worldDir.y *= -1;
        
    if(worldDir.y > 0.0f)
    {
        outSceneColor = mix(vec4(1.0f), vec4(0.25f, 0.5f, 1.0f, 1.0f), worldDir.y);
    }
    else
    {
        outSceneColor   = vec4(1.0f);
    }
}

/*****************************************************************************************/