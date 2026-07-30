/**
* @file PreRendererLayout.glsl.
* @brief This Shader Header File Defines Pre Shader DescriptorSets.
* @author Spices.
*/

/************************************Pre Compile*******************************************/

#ifndef PRERENDERER_LAYOUT_H
#define PRERENDERER_LAYOUT_H

#include "Core.h"

/*****************************************************************************************/

/*************************************Pre Renderer Data***********************************/

/**
* @brief Global View Struct.
*/
layout(set = 0, binding = 0) uniform ShaderView 
{
    View view;                        /* @see View */
};

/**
* @brief Application Inout Struct.
*/
layout(set = 0, binding = 1) uniform ShaderInput 
{
    Input engineInput;          /* @see EngineInput */
};

/**
* @brief BindLess Texture Buffer.
*/
layout (set = BINDLESS_TEXTURE_SET, binding = BINDLESS_TEXTURE_BINDING) uniform sampler2D BindLessTextureBuffer[];

/*****************************************************************************************/

#endif