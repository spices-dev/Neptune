/**
* @file CmdList2.cpp.
* @brief The CmdList2 Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "CmdList2.h"
#include "Device/Graphics/Backend/Direct3D12/Unit/GraphicsCommandList.h"
#include "Device/Graphics/Backend/Direct3D12/Infrastructure/Device.h"
#include "Device/Graphics/Backend/Direct3D12/Infrastructure/Queue.h"
#include "Device/Graphics/Backend/Direct3D12/Infrastructure/DebugUtilsObject.h"
#include "Device/Graphics/Backend/Direct3D12/Resource/CommandList.h"
#include "Device/Graphics/Backend/Direct3D12/Unit/Fence.h"

namespace Neptune::Direct3D12 {
	
	void CmdList2::Begin() const
	{
		NEPTUNE_PROFILE_ZONE
		
		m_CommandList->Begin();
	}
	
	void CmdList2::End()
	{
		NEPTUNE_PROFILE_ZONE
		
		m_CommandList->End();
	}

	void CmdList2::SubmitWait()
	{
		NEPTUNE_PROFILE_ZONE
		
		auto fence = CreateSP<Unit::Fence>();
		
		GetContext().Get<IGraphicQueue>()->Submit(m_CommandList->Handle(), fence);
		
		fence->Wait();
	}

	void CmdList2::SetGraphicCmdList()
	{
		NEPTUNE_PROFILE_ZONE

		m_CommandList = CreateSP<Resource::CommandList>(GetContext());

		m_CommandList->CreateCommandList(GetContext().Get<IDevice>()->Handle(), D3D12_COMMAND_LIST_TYPE_DIRECT);

		DEBUGUTILS_SETOBJECTNAME(m_CommandList->IHandle(), "CmdList2CommandList")
	}
	
}

#endif