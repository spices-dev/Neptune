/**
* @file Enum.h.
* @brief The Enum Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

namespace Neptune::WebGPU {

    /**
    * @brief Enum of Extension.
    */
    enum class EExtension : uint8_t
    {
        TimedWaitAny,                                // @brief TimedWaitAny.
        ShaderSourceSPIRV,                           // @brief ShaderSourceSPIRV.
        MultipleDevicesPerAdapter,                   // @brief MultipleDevicesPerAdapter.
        ReadonlyAndReadwriteStorageTextures,         // @brief ReadonlyAndReadwriteStorageTextures.
        Packed4x8IntegerDotProduct,                  // @brief Packed4x8IntegerDotProduct.
        UnrestrictedPointerParameters,               // @brief UnrestrictedPointerParameters.
        PointerCompositeAccess,                      // @brief PointerCompositeAccess.
        CoreFeaturesAndLimits,                       // @brief CoreFeaturesAndLimits.
        DepthClipControl,                            // @brief DepthClipControl.
        Depth32FloatStencil8,                        // @brief Depth32FloatStencil8.
        TextureCompressionBC,                        // @brief TextureCompressionBC.
        TextureCompressionBCSliced3D,                // @brief TextureCompressionBCSliced3D.
        TextureCompressionETC2,                      // @brief TextureCompressionETC2.
        TextureCompressionASTC,                      // @brief TextureCompressionASTC.
        TextureCompressionASTCSliced3D,              // @brief TextureCompressionASTCSliced3D.
        TimestampQuery,                              // @brief TimestampQuery.
        IndirectFirstInstance,                       // @brief IndirectFirstInstance.
        ShaderF16,                                   // @brief ShaderF16.
        RG11B10UfloatRenderable,                     // @brief RG11B10UfloatRenderable.
        BGRA8UnormStorage,                           // @brief BGRA8UnormStorage.
        Float32Filterable,                           // @brief Float32Filterable.
        Float32Blendable,                            // @brief Float32Blendable.
        ClipDistances,                               // @brief ClipDistances.
        DualSourceBlending,                          // @brief DualSourceBlending.
        Subgroups,                                   // @brief Subgroups.
        TextureFormatsTier1,                         // @brief TextureFormatsTier1.
        TextureFormatsTier2,                         // @brief TextureFormatsTier2.
        PrimitiveIndex,                              // @brief PrimitiveIndex.
        Unorm16TextureFormats,                       // @brief Unorm16TextureFormats.
        Snorm16TextureFormats,                       // @brief Snorm16TextureFormats.               Removed since 2026.09.25
        MultiDrawIndirect,                           // @brief MultiDrawIndirect.
        TextureComponentSwizzle,                     // @brief TextureComponentSwizzle.
        SubgroupSizeControl,                         // @brief SubgroupSizeControl.
        TextureCompressionUnaligned,                 // @brief TextureCompressionUnaligned.
        ChromiumExperimentalSubgroupMatrix,          // @brief ChromiumExperimentalSubgroupMatrix.
        UniformBufferStandardLayout,                 // @brief UniformBufferStandardLayout.
        SubgroupId,                                  // @brief SubgroupId.
        TextureAndSamplerLet,                        // @brief TextureAndSamplerLet.
        SubgroupUniformity,                          // @brief SubgroupUniformity.
        LinearIndexing,                              // @brief LinearIndexing.
        ImmediateAddressSpace,                       // @brief ImmediateAddressSpace.
        BufferView,                                  // @brief BufferView.
        SwizzleAssignment,                           // @brief SwizzleAssignment.
        FragmentDepth,                               // @brief FragmentDepth.
        
        Count
    };
    
    inline std::string ToString(EExtension e)
    {
        NEPTUNE_PROFILE_ZONE
        
        using enum EExtension;
        
        switch (e)
        {
            case TimedWaitAny:                              return "TimedWaitAny";
            case ShaderSourceSPIRV:                         return "ShaderSourceSPIRV";
            case MultipleDevicesPerAdapter:                 return "MultipleDevicesPerAdapter";
            case ReadonlyAndReadwriteStorageTextures:       return "ReadonlyAndReadwriteStorageTextures";
            case Packed4x8IntegerDotProduct:                return "Packed4x8IntegerDotProduct";
            case UnrestrictedPointerParameters:             return "UnrestrictedPointerParameters";
            case PointerCompositeAccess:                    return "PointerCompositeAccess";
            case CoreFeaturesAndLimits:                     return "CoreFeaturesAndLimits";
            case DepthClipControl:                          return "DepthClipControl";
            case Depth32FloatStencil8:                      return "Depth32FloatStencil8";
            case TextureCompressionBC:                      return "TextureCompressionBC";
            case TextureCompressionBCSliced3D:              return "TextureCompressionBCSliced3D";
            case TextureCompressionETC2:                    return "TextureCompressionETC2";
            case TextureCompressionASTC:                    return "TextureCompressionASTC";
            case TextureCompressionASTCSliced3D:            return "TextureCompressionASTCSliced3D";
            case TimestampQuery:                            return "TimestampQuery";
            case IndirectFirstInstance:                     return "IndirectFirstInstance";
            case ShaderF16:                                 return "ShaderF16";
            case RG11B10UfloatRenderable:                   return "RG11B10UfloatRenderable";
            case BGRA8UnormStorage:                         return "BGRA8UnormStorage";
            case Float32Filterable:                         return "Float32Filterable";
            case Float32Blendable:                          return "Float32Blendable";
            case ClipDistances:                             return "ClipDistances";
            case DualSourceBlending:                        return "DualSourceBlending";
            case Subgroups:                                 return "Subgroups";
            case TextureFormatsTier1:                       return "TextureFormatsTier1";
            case TextureFormatsTier2:                       return "TextureFormatsTier2";
            case PrimitiveIndex:                            return "PrimitiveIndex";
            case Unorm16TextureFormats:                     return "Unorm16TextureFormats";
            case Snorm16TextureFormats:                     return "Snorm16TextureFormats";
            case MultiDrawIndirect:                         return "MultiDrawIndirect";
            case TextureComponentSwizzle:                   return "TextureComponentSwizzle";
            case SubgroupSizeControl:                       return "SubgroupSizeControl";
            case TextureCompressionUnaligned:               return "TextureCompressionUnaligned";
            case ChromiumExperimentalSubgroupMatrix:        return "ChromiumExperimentalSubgroupMatrix";
            case UniformBufferStandardLayout:               return "UniformBufferStandardLayout";
            case SubgroupId:                                return "SubgroupId";
            case TextureAndSamplerLet:                      return "TextureAndSamplerLet";
            case SubgroupUniformity:                        return "SubgroupUniformity";
            case LinearIndexing:                            return "LinearIndexing";
            case ImmediateAddressSpace:                     return "ImmediateAddressSpace";
            case BufferView:                                return "BufferView";
            case SwizzleAssignment:                         return "SwizzleAssignment";
            case FragmentDepth:                             return "FragmentDepth";
            
            default:                                        return "NonNamed";
        }
    }

}

#endif