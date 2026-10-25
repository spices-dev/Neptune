/**
* @file Extensions.cpp.
* @brief The Extension Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Extensions.h"
#include "Device/Graphics/Backend/Direct3D12/Extension/ExtensionHeader.h"
#include "Window/Window.h"

namespace Neptune::Direct3D12 {

	Extensions::Extensions(Context& context, EInfrastructure e)
		: Infrastructure(context, e)
	{
		NEPTUNE_PROFILE_ZONE

		Create();
	}

	void Extensions::Create()
	{
		NEPTUNE_PROFILE_ZONE
		
		m_Context = CreateSP<Extension::EContext<EExtension>>();
		
		m_Context->Registry<Extension::IWaveOps>                                                      (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IExpandedComputeResourceStates>                                (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IInt64ShaderOps>                                               (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IDepthBoundsTest>                                              (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IProgrammableSamplePositions>                                  (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::ICopyQueueTimestampQueries>                                    (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::ICastingFullyTypedFormat>                                      (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IWriteBufferImmediate>                                         (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IViewInstancing>                                               (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IBarycentrics>                                                 (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IMSAA64KBAlignedTexture>                                       (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::ISharedResourceCompatibility>                                  (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::INative16BitShaderOps>                                         (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::ISRVOnlyTiledResource>                                         (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IRaytracing>                                                   (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IAdditionalShadingRates>                                       (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IPerPrimitiveShadingRateWithViewportIndexing>                  (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IVariableShadingRate>                                          (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IShadingRateImageTileSize>                                     (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IBackgroundProcessing>                                         (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IMeshShader>									                  (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::ISamplerFeedback>							                  (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IUnalignedBlockTextures>                                       (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IMeshShaderPipelineStats>                                      (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IMeshShaderFullRangeRenderTargetArrayIndex>                    (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IAtomicInt64OnTypedResource>                                   (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IAtomicInt64OnGroupShared>                                     (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IDerivativesInMeshAndAmplificationShaders>                     (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IWaveMMA>									                  (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IVariableRateShadingSumCombiner>                               (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IMeshShaderPerPrimitiveShadingRate>                            (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IAtomicInt64OnDescriptorHeapResource>                          (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IMSPrimitivesPipelineStatisticIncludesCulledPrimitives>        (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IEnhancedBarriers>                             				  (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IRelaxedFormatCasting>                         				  (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IUnrestrictedBufferTextureCopyPitch>                           (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IUnrestrictedVertexElementAlignment>                           (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IInvertedViewportHeightFlipsY>                         		  (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IInvertedViewportDepthFlipsZ>                          		  (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::ITextureCopyBetweenDimensions>                         		  (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IAlphaBlendFactor>                              				  (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IAdvancedTextureOps>                            				  (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IWriteableMSAATextures>                          			  (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IIndependentFrontAndBackStencilRefMask>                        (Extension::EExtensionState::Extent);

	}
}

#endif