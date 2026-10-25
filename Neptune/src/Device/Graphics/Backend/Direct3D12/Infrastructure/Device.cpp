/**
* @file Device.cpp.
* @brief The Device Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Device.h"
#include "DebugUtilsObject.h"
#include "Extensions.h"
#include "Device/Graphics/Backend/Direct3D12/Unit/Debug.h"
#include "Device/Graphics/Backend/Direct3D12/Unit/Adapter.h"
#include "Device/Graphics/Backend/Direct3D12/Unit/InfoQueue.h"
#include "Device/Graphics/Backend/Direct3D12/Unit/DebugDevice.h"
#include "Factory.h"
#include "Core/Library/StringLibrary.h"

namespace Neptune::Direct3D12 {
	
    Device::Device(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {
		NEPTUNE_PROFILE_ZONE

        Create();
    }

	Device::~Device()
	{
		NEPTUNE_PROFILE_ZONE

		if (GetContext().Has<IDebugUtilsObject>())
		{
			Unit::InfoQueue infoQueue;

			infoQueue.CreateInfoQueue(m_Device.GetHandle());

			infoQueue.GetHandle()->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, false);
			infoQueue.GetHandle()->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, false);
			infoQueue.GetHandle()->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, false);
		}

		{
			Unit::DebugDevice debug;

			debug.CreateDebugDevice(m_Device.GetHandle());

			DIRECT3D12_CHECK(debug.GetHandle()->ReportLiveDeviceObjects(D3D12_RLDO_SUMMARY | D3D12_RLDO_DETAIL | D3D12_RLDO_IGNORE_INTERNAL))
		}
	}

	void Device::Create()
    {
		NEPTUNE_PROFILE_ZONE

    	if (GetContext().Has<IDebugUtilsObject>())
    	{
    		Unit::Debug debug;

    		debug.CreateDebug();

    		debug.EnableDebugLayer();
    	}

		Unit::Adapter adapter;

		adapter.CreateAdapter(GetContext().Get<IFactory>()->Handle());

		m_Device.CreateDevice(adapter.GetHandle(), GetMaxFeatureLevel(adapter.GetHandle()));

    	if (GetContext().Has<IDebugUtilsObject>())
		{
			Unit::DebugDevice debug;

			debug.CreateDebugDevice(m_Device.GetHandle());

			D3D12_DEBUG_DEVICE_GPU_BASED_VALIDATION_SETTINGS validationSettings = {};

			DIRECT3D12_CHECK(debug.GetHandle()->SetDebugParameter(
				D3D12_DEBUG_DEVICE_PARAMETER_GPU_BASED_VALIDATION_SETTINGS,
				&validationSettings,
				sizeof(validationSettings)
			))

			Unit::InfoQueue infoQueue;

			infoQueue.CreateInfoQueue(m_Device.GetHandle());

			infoQueue.GetHandle()->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
			infoQueue.GetHandle()->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, true);
			infoQueue.GetHandle()->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);

			DWORD cookie = 0;

			DIRECT3D12_CHECK(infoQueue.GetHandle()->RegisterMessageCallback(
				DebugCallback,
				D3D12_MESSAGE_CALLBACK_FLAG_NONE,
				nullptr,
				&cookie
			))
		}
		
    	if (!CheckFeatureMeetDemand())
    	{
    		NEPTUNE_LOG_CORE(E) << "D3D12 Device Feature Check Failed";
    		
    		return;
    	}
    	
    	DXGI_ADAPTER_DESC3 desc{};
    	adapter.GetHandle()->GetDesc3(&desc);
    	
    	NEPTUNE_LOG_CORE(I) << "D3D12 Device Selected: " << Library::WCharToChar(desc.Description);
    }

	D3D_FEATURE_LEVEL Device::GetMaxFeatureLevel(DXGIAdapter adapter) const
	{
		NEPTUNE_PROFILE_ZONE

		D3D12_FEATURE_DATA_FEATURE_LEVELS        level{};
		level.NumFeatureLevels                 = _countof(FeatureLevels);
		level.pFeatureLevelsRequested          = FeatureLevels;

		Unit::Device device;

		device.CreateDevice(adapter, MinimumLevel);

		DIRECT3D12_CHECK(device.GetHandle()->CheckFeatureSupport(D3D12_FEATURE_FEATURE_LEVELS, &level, sizeof(level)))

		return level.MaxSupportedFeatureLevel;
	}

	bool Device::CheckFeatureMeetDemand()
	{
    	NEPTUNE_PROFILE_ZONE
    	
    	bool coreSatisfied = true;
		
    	std::vector<EExtension> removedExtension;
		
    	GetContext().Get<IExtensions>()->GetContext()->View([&](const auto e, const auto& extension) {
			
			if (!extension->IsFeaturesSatisfied(m_Device.GetHandle()))
			{
				if (extension->GetState() == Extension::EExtensionState::Core)
				{
					coreSatisfied = false;

					NEPTUNE_LOG_CORE(E) << "Device Feature Required: [ " << Direct3D12::ToString(e) << " ], Which is not satisfied";
				}
				else
				{
					NEPTUNE_LOG_CORE(W) << "Device Feature Required: [ " << Direct3D12::ToString(e) << " ], Which is not satisfied";
				}
				
				removedExtension.emplace_back(e);
			}
			
		});
		
    	std::ranges::for_each(removedExtension, [&](const auto& e) {
    		
			GetContext().Get<IExtensions>()->GetContext()->UnRegistry(e);
		});
    	
    	return coreSatisfied;
	}
}

#endif