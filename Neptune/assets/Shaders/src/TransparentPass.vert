/**
* @file TransparentPass.vert.
* @brief This Shader Defines TransparentPass Vertex Shader Behaver.
* @author Spices.
*/

/************************************Pre Compile*******************************************/

#version 460

#extension GL_GOOGLE_include_directive : enable    /* @brief Enable include Macro. */

#include "Header/PreRendererLayout.glsl"
#include "Header/GS3DDescLayout.glsl"

/*****************************************************************************************/

/************************************Vertex Output****************************************/

/**
* @brief Vertex Shader Output to Fragment Shader.
*/
layout(location = 0) out struct FragInput
{
    vec2 texCoord;
}
vertOut;

/*****************************************************************************************/

/********************************Descriptor List******************************************/
        
/**
* @brief GS3DDesc Address.
*/
layout(set = 1, binding = 1) uniform uint64_t descAddress;  /* @see GS3DDesc */

/*****************************************************************************************/
        
/**********************************Shader Entry*******************************************/

void main()
{
    ExplainGS3DDesciption(descAddress);
    vec3 pos = mat3(view.inView) * position;

    vertOut.texCoord = vec2(0.5f);
    gl_Position = view.projection * view.view  * model * vec4(pos, 1.0);
}

/*****************************************************************************************/