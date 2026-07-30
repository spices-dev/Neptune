/**
* @file FPSPass.frag.
* @brief This Shader Defines FPSPass Fragment Shader Behaver.
* @author Spices.
*/

/************************************Pre Compile*******************************************/

#version 460

#extension GL_GOOGLE_include_directive : enable    /* @brief Enable include Macro. */

#include "Header/Core.h"
#include "Header/PreRendererLayout.glsl"
#include "Header/SampleDigit.glsl"

/*****************************************************************************************/

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
    vec2 size = view.sceneTextureSize.xy;

    float fps = 1.0f / engineInput.frameTime;

    float v = PrintValue(texCoord * vec2(size.x, -size.y), vec2(size.x - 80.0f, -30.0f), vec2(12.0f, 16.0f), fps, 4.0f, 0.0f);
    
    if(v < 0.5f)
    {
        discard;
    }
    
    outSceneColor = vec4(1.0f, 1.0f, 1.0f, 0.4f);
}

/*****************************************************************************************/