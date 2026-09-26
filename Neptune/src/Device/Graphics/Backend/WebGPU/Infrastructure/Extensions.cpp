/**
* @file Extensions.cpp.
* @brief The Extension Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "Extensions.h"
#include "Device/Graphics/Backend/WebGPU/Extension/ExtensionHeader.h"

namespace Neptune::WebGPU {

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
		
		m_Context->Registry<Extension::ITimedWaitAny>                                 (Extension::EExtensionState::Core);
		m_Context->Registry<Extension::IShaderSourceSPIRV>                            (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IMultipleDevicesPerAdapter>                    (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IReadonlyAndReadwriteStorageTextures>          (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IPacked4x8IntegerDotProduct>                   (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IUnrestrictedPointerParameters>                (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IPointerCompositeAccess>                       (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::ICoreFeaturesAndLimits>                        (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IDepthClipControl>                             (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IDepth32FloatStencil8>                         (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::ITextureCompressionBC>                         (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::ITextureCompressionBCSliced3D>                 (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::ITextureCompressionETC2>                       (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::ITextureCompressionASTC>                       (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::ITextureCompressionASTCSliced3D>               (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::ITimestampQuery>                               (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IIndirectFirstInstance>                        (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IShaderF16>                                    (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IRG11B10UfloatRenderable>                      (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IBGRA8UnormStorage>                            (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IFloat32Filterable>                            (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IFloat32Blendable>                             (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IClipDistances>                                (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IDualSourceBlending>                           (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::ISubgroups>                                    (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::ITextureFormatsTier1>                          (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::ITextureFormatsTier2>                          (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IPrimitiveIndex>                               (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IUnorm16TextureFormats>                        (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::ISnorm16TextureFormats>                        (Extension::EExtensionState::Extent);
		m_Context->Registry<Extension::IMultiDrawIndirect>                            (Extension::EExtensionState::Extent);
	}
}

#endif