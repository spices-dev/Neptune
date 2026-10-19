/**
* @file BasePass.frag.slang.
* @brief This Shader Defines BasePass Fragment Shader Behaver.
* @author Spices.
*/

/************************************Pre Compile*******************************************/

#include "Header/PreRendererLayout.slangh"

/*****************************************************************************************/

/************************************Fragment Input***************************************/

/**
* @brief Fragment Shader Input From Vertex Shader.
*/
struct FSInput
{
    [[vk::location(0)]] float2 texCoord : TEXCOORD0;
};

/*****************************************************************************************/
        
/************************************Fragment Output**************************************/

/**
* @brief Fragment Shader Output to FrameBuffer.
*/
struct FSOutput
{
    [[vk::location(0)]] float4 outSceneColor : SV_Target0;
};

/*****************************************************************************************/

/********************************Descriptor List******************************************/

[[vk::binding(0, 1)]] Sampler2D bgImage;

/*****************************************************************************************/
        
/**********************************Shader Entry*******************************************/
        
[shader("fragment")]
FSOutput main(FSInput input)
{
    float2 ndcDir  = float2(2.0 * input.texCoord.x - 1.0, 2.0 * input.texCoord.y - 1.0);

    float4 clipDir = float4(ndcDir, 1.0, 1.0);

    float4 viewDir = mul(view.inProjection, clipDir);

    viewDir /= viewDir.w;

    float3 worldDir = normalize(mul(view.inView, float4(viewDir.xyz, 0.0)).xyz);

    worldDir.y *= -1.0;
        
    float4 color = float4(1.0f);
            
    if(worldDir.y > 0.0f)
    {
        color = lerp(float4(1.0f), float4(0.25f, 0.5f, 1.0f, 1.0f), worldDir.y);
    }

    float4 image = bgImage.Sample(input.texCoord);

    FSOutput output;
    output.outSceneColor = lerp(color, image, image.a);
    return output;
}

/*****************************************************************************************/