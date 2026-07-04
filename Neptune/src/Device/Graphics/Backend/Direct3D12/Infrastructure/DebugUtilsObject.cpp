/**
* @file DebugUtilsObject.cpp.
* @brief The DebugUtilsObject Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "DebugUtilsObject.h"

#ifdef NEPTUNE_DEBUG
#define USE_PIX
#endif

#ifdef _MSC_VER

#include <WinPixEventRuntime/pix3.h>

#endif

namespace Neptune::Direct3D12 {

	DebugUtilsObject::DebugUtilsObject(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {}

	void DebugUtilsObject::BeginLabel(D3D12GraphicsCommandList cmdList, const std::string& caption) const
	{
		NEPTUNE_PROFILE_ZONE

#ifdef _MSC_VER
		
		PIXBeginEvent(cmdList, 0, caption.c_str());
		
#endif
		
	}

	void DebugUtilsObject::EndLabel(D3D12GraphicsCommandList cmdList) const
	{
		NEPTUNE_PROFILE_ZONE

#ifdef _MSC_VER
		
		PIXEndEvent(cmdList);
		
#endif
		
	}

	void DebugUtilsObject::InsertLabel(D3D12GraphicsCommandList cmdList, const std::string& caption) const
	{
		NEPTUNE_PROFILE_ZONE

#ifdef _MSC_VER
		
		PIXSetMarker(cmdList, 0, caption.c_str());
		
#endif
		
	}
	
	void DebugUtilsObject::BeginQueueLabel(D3D12CommandQueue queue, const std::string& caption) const
	{
		NEPTUNE_PROFILE_ZONE

#ifdef _MSC_VER
		
		PIXBeginEvent(queue, 0, caption.c_str());
		
#endif
		
	}

	void DebugUtilsObject::EndQueueLabel(D3D12CommandQueue queue) const
	{
		NEPTUNE_PROFILE_ZONE

#ifdef _MSC_VER
		
		PIXEndEvent(queue);
		
#endif
		
	}

	void DebugUtilsObject::InsertQueueLabel(D3D12CommandQueue queue, const std::string& caption) const
	{
		NEPTUNE_PROFILE_ZONE

#ifdef _MSC_VER
		
		PIXSetMarker(queue, 0, caption.c_str());
		
#endif
		
	}
}

#endif