/**
* @file TransparentPass.frag.
* @brief This Shader Defines TransparentPass Fragment Shader Behaver.
* @author Spices.
*/

/************************************Pre Compile*******************************************/

#version 460

#extension GL_GOOGLE_include_directive : enable    /* @brief Enable include Macro. */

#include "Header/Core.h"
#include "Header/PreRendererLayout.glsl"

/*****************************************************************************************/

/************************************Fragment Input***************************************/

/**
* @brief Fragment Shader Input From Vertex Shader.
*/
layout(location = 0) in struct FragInput
{
    vec2  localOffset;
    vec3  color;
    float opacity;
    vec3  conic;
}
fragIn;

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
    vec2 d = fragIn.localOffset;
    vec3 conic = fragIn.conic;

    float power = -0.5 * (conic.x * d.x * d.x + conic.z * d.y * d.y) - conic.y * d.x * d.y;
    
    if (power > 0.0)
    {
        discard;
    }

    float alpha = min(0.99, fragIn.opacity * exp(power));
    if (alpha < 1.0 / 255.0)
    {
        discard;
    }

    outSceneColor = vec4(fragIn.color, alpha);
}

/*****************************************************************************************/