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
    outSceneColor = vec4(1.0f, 1.0f, 1.0f, 0.4f);
}

/*****************************************************************************************/