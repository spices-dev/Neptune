/**
* @file Enum.h.
* @brief The Enum Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D12

namespace Neptune::Direct3D12 {

    /**
    * @brief Enum of Extension.
    */
    enum class EExtension : uint8_t
    {
        WaveOps = 0,                                              // @brief WaveOps
        ExpandedComputeResourceStates,                            // @brief ExpandedComputeResourceStates
        Int64ShaderOps,                                           // @brief Int64ShaderOps
        DepthBoundsTest,                                          // @brief DepthBoundsTest
        ProgrammableSamplePositions,                              // @brief ProgrammableSamplePositions
        CopyQueueTimestampQueries,                                // @brief CopyQueueTimestampQueries
        CastingFullyTypedFormat,                                  // @brief CastingFullyTypedFormat
        WriteBufferImmediate,                                     // @brief WriteBufferImmediate
        ViewInstancing,                                           // @brief ViewInstancing
        Barycentrics,                                             // @brief Barycentrics
        MSAA64KBAlignedTexture,                                   // @brief MSAA64KBAlignedTexture
        SharedResourceCompatibility,                              // @brief SharedResourceCompatibility
        Native16BitShaderOps,                                     // @brief Native16BitShaderOps
        SRVOnlyTiledResource,                                     // @brief SRVOnlyTiledResource
        Raytracing,                                               // @brief Raytracing
        AdditionalShadingRates,                                   // @brief AdditionalShadingRates
        PerPrimitiveShadingRateWithViewportIndexing,              // @brief PerPrimitiveShadingRateWithViewportIndexing
        VariableShadingRate,                                      // @brief VariableShadingRate
        ShadingRateImageTileSize,                                 // @brief ShadingRateImageTileSize
        BackgroundProcessing,                                     // @brief BackgroundProcessing
        
        
        
        MeshShader,
        RenderPass,
        SamplerFeedback,

        Count
    };
    
    inline std::string ToString(EExtension e)
    {
        NEPTUNE_PROFILE_ZONE
        
        using enum EExtension;
        
        switch (e)
        {
            case WaveOps:                                           return "WaveOps";
            case ExpandedComputeResourceStates:                     return "ExpandedComputeResourceStates";
            case Int64ShaderOps:                                    return "Int64ShaderOps";
            case DepthBoundsTest:                                   return "DepthBoundsTest";
            case ProgrammableSamplePositions:                       return "ProgrammableSamplePositions";
            case CopyQueueTimestampQueries:                         return "CopyQueueTimestampQueries";
            case CastingFullyTypedFormat:                           return "CastingFullyTypedFormat";
            case WriteBufferImmediate:                              return "WriteBufferImmediate";
            case ViewInstancing:                                    return "ViewInstancing";
            case Barycentrics:                                      return "Barycentrics";
            case MSAA64KBAlignedTexture:                            return "MSAA64KBAlignedTexture";
            case SharedResourceCompatibility:                       return "SharedResourceCompatibility";
            case Native16BitShaderOps:                              return "Native16BitShaderOps";
            case SRVOnlyTiledResource:                              return "SRVOnlyTiledResource";
            case Raytracing:                                        return "Raytracing";
            case AdditionalShadingRates:                            return "AdditionalShadingRates";
            case PerPrimitiveShadingRateWithViewportIndexing:       return "PerPrimitiveShadingRateWithViewportIndexing";
            case VariableShadingRate:                               return "VariableShadingRate";
            case ShadingRateImageTileSize:                          return "ShadingRateImageTileSize";
            case BackgroundProcessing:                              return "BackgroundProcessing";
            default:                                                return "NonNamed";
        }
    }

}

#endif