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
	}
}

#endif