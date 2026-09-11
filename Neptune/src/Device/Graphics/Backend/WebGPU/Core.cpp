/**
* @file Core.cpp.
* @brief The Core Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "Core.h"

namespace Neptune::WebGPU {

	namespace {
	
		HandleResultDelegate::Handler     s_Handler;       // @brief HandleResultDelegate::Handler instance.
		HandleResultDelegate::WaitHandler s_WaitHandler;   // @brief HandleResultDelegate::WaitHandler instance.
	}

	void HandleResultDelegate::SetHandler(const Handler& fn)
	{
        NEPTUNE_PROFILE_ZONE

		s_Handler = fn;
	}

	const HandleResultDelegate::Handler& HandleResultDelegate::GetHandler()
	{
        NEPTUNE_PROFILE_ZONE

		return s_Handler;
	}

	void HandleResultDelegate::SetWaitHandler(const WaitHandler& fn)
	{
        NEPTUNE_PROFILE_ZONE

		s_WaitHandler = fn;
	}

	const HandleResultDelegate::WaitHandler& HandleResultDelegate::GetWaitHandler()
	{
        NEPTUNE_PROFILE_ZONE

		return s_WaitHandler;
	}
	
	void DeviceLostCallback(WGPUDevice const*, WGPUDeviceLostReason reason, WGPUStringView message, void*, void*)
	{
        NEPTUNE_PROFILE_ZONE

        const char* label = "";
        switch (reason)
        {
            case WGPUDeviceLostReason_Unknown:            label = "Unknown"; break;
            case WGPUDeviceLostReason_Destroyed:          label = "Destroyed"; break;
            case WGPUDeviceLostReason_CallbackCancelled:  label = "CallbackCancelled"; break;
            case WGPUDeviceLostReason_FailedCreation:     label = "FailedCreation"; break;
            default:                                      label = "Unknown";
        }

        NEPTUNE_LOG_CORE(E) << "WebGPU DeviceLost: [ " << label << " ]: " << message.data;
	}

	void UncapturedErrorCallback(WGPUDevice const*, WGPUErrorType type, WGPUStringView message, void*, void*)
	{
        NEPTUNE_PROFILE_ZONE

		if (type == WGPUErrorType_NoError)
        {
            return;
        }

        const char* label = "";
        switch (type)
        {
            case WGPUErrorType_Validation:  label = "Validation"; break;
            case WGPUErrorType_OutOfMemory: label = "Out of memory"; break;
            case WGPUErrorType_Internal:    label = "Internal"; break;
            case WGPUErrorType_Unknown:     label = "Unknown"; break;
            default:                        label = "Unknown";
        }

		NEPTUNE_LOG_CORE(E) << "WebGPU UncapturedError: [ " << label << " ]: " << message.data;
	}

	void HandleResult(WGPUStatus result)
	{
        NEPTUNE_PROFILE_ZONE

		if (result == WGPUStatus_Success) return;

		const char* label = "";
		switch (result)
		{
			case WGPUStatus_Error:                                       label = "Error";                               break;
			default:                                                     label = "Unknown Error";                       break;
		}

        NEPTUNE_LOG_CORE(E) << "WebGPU Error: [ " << label << " ]";
	}

	void HandleWaitResult(WGPUWaitStatus result)
	{
        NEPTUNE_PROFILE_ZONE

		if (result == WGPUWaitStatus_Success) return;

		const char* label = "";
		switch (result)
		{
			case WGPUWaitStatus_TimedOut:                                label = "Wait TimeOut";                        break;
			case WGPUWaitStatus_Error:                                   label = "Wait Error";                          break;
			default:                                                     label = "Unknown Error";                       break;
		}

		NEPTUNE_LOG_CORE(E) << "WebGPU Error: [ " << label << " ]";
	}
}

#endif