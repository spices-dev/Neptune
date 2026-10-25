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
        MeshShader,                                               // @brief MeshShader
        SamplerFeedback,                                          // @brief SamplerFeedback
        UnalignedBlockTextures,                                   // @brief UnalignedBlockTextures
        MeshShaderPipelineStats,                                  // @brief MeshShaderPipelineStats
        MeshShaderFullRangeRenderTargetArrayIndex,                // @brief MeshShaderFullRangeRenderTargetArrayIndex      
        AtomicInt64OnTypedResource,                               // @brief AtomicInt64OnTypedResource
        AtomicInt64OnGroupShared,                                 // @brief AtomicInt64OnGroupShared
        DerivativesInMeshAndAmplificationShaders,                 // @brief DerivativesInMeshAndAmplificationShaders
        WaveMMA,                                                  // @brief WaveMMA
        VariableRateShadingSumCombiner,                           // @brief VariableRateShadingSumCombiner
        MeshShaderPerPrimitiveShadingRate,                        // @brief MeshShaderPerPrimitiveShadingRate
        AtomicInt64OnDescriptorHeapResource,                      // @brief AtomicInt64OnDescriptorHeapResource
        MSPrimitivesPipelineStatisticIncludesCulledPrimitives,    // @brief MSPrimitivesPipelineStatisticIncludesCulledPrimitives       
        EnhancedBarriers,                                         // @brief EnhancedBarriers
        RelaxedFormatCasting,                                     // @brief RelaxedFormatCasting
        UnrestrictedBufferTextureCopyPitch,                       // @brief UnrestrictedBufferTextureCopyPitch
        UnrestrictedVertexElementAlignment,                       // @brief UnrestrictedVertexElementAlignment
        InvertedViewportHeightFlipsY,                             // @brief InvertedViewportHeightFlipsY
        InvertedViewportDepthFlipsZ,                              // @brief InvertedViewportDepthFlipsZ
        TextureCopyBetweenDimensions,                             // @brief TextureCopyBetweenDimensions
        AlphaBlendFactor,                                         // @brief AlphaBlendFactor
        AdvancedTextureOps,                                       // @brief AdvancedTextureOps
        WriteableMSAATextures,                                    // @brief WriteableMSAATextures
        IndependentFrontAndBackStencilRefMask,                    // @brief IndependentFrontAndBackStencilRefMask
        

        RenderPass,

        Count
    };
    
    inline std::string ToString(EExtension e)
    {
        NEPTUNE_PROFILE_ZONE
        
        using enum EExtension;
        
        switch (e)
        {
            case WaveOps:                                                          return "WaveOps";
            case ExpandedComputeResourceStates:                                    return "ExpandedComputeResourceStates";
            case Int64ShaderOps:                                                   return "Int64ShaderOps";
            case DepthBoundsTest:                                                  return "DepthBoundsTest";
            case ProgrammableSamplePositions:                                      return "ProgrammableSamplePositions";
            case CopyQueueTimestampQueries:                                        return "CopyQueueTimestampQueries";
            case CastingFullyTypedFormat:                                          return "CastingFullyTypedFormat";
            case WriteBufferImmediate:                                             return "WriteBufferImmediate";
            case ViewInstancing:                                                   return "ViewInstancing";
            case Barycentrics:                                                     return "Barycentrics";
            case MSAA64KBAlignedTexture:                                           return "MSAA64KBAlignedTexture";
            case SharedResourceCompatibility:                                      return "SharedResourceCompatibility";
            case Native16BitShaderOps:                                             return "Native16BitShaderOps";
            case SRVOnlyTiledResource:                                             return "SRVOnlyTiledResource";
            case Raytracing:                                                       return "Raytracing";
            case AdditionalShadingRates:                                           return "AdditionalShadingRates";
            case PerPrimitiveShadingRateWithViewportIndexing:                      return "PerPrimitiveShadingRateWithViewportIndexing";
            case VariableShadingRate:                                              return "VariableShadingRate";
            case ShadingRateImageTileSize:                                         return "ShadingRateImageTileSize";
            case BackgroundProcessing:                                             return "BackgroundProcessing";
            case MeshShader:                                                       return "MeshShader";
            case SamplerFeedback:                                                  return "SamplerFeedback";
            case UnalignedBlockTextures:                                           return "UnalignedBlockTextures";
            case MeshShaderPipelineStats:                                          return "MeshShaderPipelineStats";
            case MeshShaderFullRangeRenderTargetArrayIndex:                        return "MeshShaderFullRangeRenderTargetArrayIndex";
            case AtomicInt64OnTypedResource:                                       return "AtomicInt64OnTypedResource";
            case AtomicInt64OnGroupShared:                                         return "AtomicInt64OnGroupShared";
            case DerivativesInMeshAndAmplificationShaders:                         return "DerivativesInMeshAndAmplificationShaders";
            case WaveMMA:                                                          return "WaveMMA";
            case VariableRateShadingSumCombiner:                                   return "VariableRateShadingSumCombiner";
            case MeshShaderPerPrimitiveShadingRate:                                return "MeshShaderPerPrimitiveShadingRate";
            case AtomicInt64OnDescriptorHeapResource:                              return "AtomicInt64OnDescriptorHeapResource";
            case MSPrimitivesPipelineStatisticIncludesCulledPrimitives:            return "MSPrimitivesPipelineStatisticIncludesCulledPrimitives";
            case EnhancedBarriers:                                                 return "EnhancedBarriers";
            case RelaxedFormatCasting:                                             return "RelaxedFormatCasting";
            case UnrestrictedBufferTextureCopyPitch:                               return "UnrestrictedBufferTextureCopyPitch";
            case UnrestrictedVertexElementAlignment:                               return "UnrestrictedVertexElementAlignment";
            case InvertedViewportHeightFlipsY:                                     return "InvertedViewportHeightFlipsY";
            case InvertedViewportDepthFlipsZ:                                      return "InvertedViewportDepthFlipsZ";
            case TextureCopyBetweenDimensions:                                     return "TextureCopyBetweenDimensions";
            case AlphaBlendFactor:                                                 return "AlphaBlendFactor";
            case AdvancedTextureOps:                                               return "AdvancedTextureOps";
            case WriteableMSAATextures:                                            return "WriteableMSAATextures";
            case IndependentFrontAndBackStencilRefMask:                            return "IndependentFrontAndBackStencilRefMask";
            default:                                                               return "NonNamed";
        }
    }

}

#endif