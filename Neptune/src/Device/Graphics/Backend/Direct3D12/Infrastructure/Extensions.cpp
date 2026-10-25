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
		
		m_Context->Registry<Extension::IWaveOps>                                      (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IExpandedComputeResourceStates>                (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IInt64ShaderOps>                               (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IDepthBoundsTest>                              (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IProgrammableSamplePositions>                  (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::ICopyQueueTimestampQueries>                    (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::ICastingFullyTypedFormat>                      (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IWriteBufferImmediate>                         (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IViewInstancing>                               (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IBarycentrics>                                 (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IMSAA64KBAlignedTexture>                       (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::ISharedResourceCompatibility>                  (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::INative16BitShaderOps>                         (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::ISRVOnlyTiledResource>                         (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IRaytracing>                                   (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IAdditionalShadingRates>                       (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IPerPrimitiveShadingRateWithViewportIndexing>  (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IVariableShadingRate>                          (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IShadingRateImageTileSize>                     (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IBackgroundProcessing>                         (Extension::EExtensionState::Extent);

	}
}

#endif