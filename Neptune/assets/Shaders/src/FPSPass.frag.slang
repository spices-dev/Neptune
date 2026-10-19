/**
* @file FPSPass.frag.slang.
* @brief This Shader Defines FPSPass Fragment Shader Behaver.
* @author Spices.
*/

/************************************Pre Compile*******************************************/

#include "Header/PreRendererLayout.slangh"
#include "Header/SampleDigit.slangh"

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
        
/**********************************Shader Entry*******************************************/
        
[shader("fragment")]
FSOutput main(FSInput input)
{
    float2 size = view.sceneTextureSize.xy;

    float fps = 1.0f / engineInput.frameTime;

    float v = PrintValue(input.texCoord * float2(size.x, -size.y), float2(size.x - 80.0f, -30.0f), float2(12.0f, 16.0f), fps, 4.0f, 0.0f);
    
    if(v < 0.5f)
    {
        discard;
    }
    
    FSOutput output;
    output.outSceneColor = float4(1.0f, 0.0f, 0.0f, 0.4f);
    return output;
}

/*****************************************************************************************/