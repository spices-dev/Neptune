/**
* @file FPSPass.vert.slang.
* @brief This Shader Defines FPSPass Vertex Shader Behaver.
* @author Spices.
*/

/************************************Pre Compile*******************************************/

#include "Header/PreRendererLayout.slangh"

/*****************************************************************************************/

/************************************Vertex Output****************************************/

/**
* @brief Vertex Shader Output to Fragment Shader.
*/
struct VSOutput
{
	[[vk::location(0)]] float2 texCoord : TEXCOORD0;
	float4 position                     : SV_Position;
};

/*****************************************************************************************/

/**********************************Shader Entry*******************************************/
		
[shader("vertex")]
VSOutput main(uint vertexIndex : SV_VertexID)
{
	VSOutput output;
    
    float2 uv = float2(float((vertexIndex << 1) & 2u), float(vertexIndex & 2u));
    output.texCoord = uv;

	uv.y = 1.0 - uv.y;
    output.position = float4(uv * 2.0f - 1.0f, 1.0f, 1.0f);
    
    return output;
}

/*****************************************************************************************/