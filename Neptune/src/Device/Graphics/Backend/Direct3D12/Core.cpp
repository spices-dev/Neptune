/**
* @file Core.cpp.
* @brief The Core Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Core.h"

extern "C" {

	DLL_EXPORT extern const UINT D3D12SDKVersion = DIRECT3D12_VERSION;    // @brief Agility SDK defined d3d12 runtime version.

	DLL_EXPORT extern const char* D3D12SDKPath = DIRECT3D12_DLL_PATH;     // @brief Agility SDK searched d3d12 dll path.
}

namespace Neptune::Direct3D12 {

	namespace {
	
		HandleResultDelegate::Handler s_Handler;   // @brief HandleResultDelegate::Handler instance.
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

	void STDMETHODCALLTYPE DebugCallback(
		D3D12_MESSAGE_CATEGORY category,
		D3D12_MESSAGE_SEVERITY severity,
		D3D12_MESSAGE_ID       id,
		LPCSTR                 message,
		void*                  context
	) {
		NEPTUNE_PROFILE_ZONE

		std::stringstream ss;

		ss <<
		"Direct3D12 Validation layer:\n			" <<
		"MessageIdNumber: " <<id <<
		"\n			MessageIdName: " << category;
		ss << "\n			Message: " << message;

		switch (severity)
		{
		case D3D12_MESSAGE_SEVERITY_MESSAGE:
			{
				NEPTUNE_LOG_CORE(T) << ss.str();
				break;
			}
		case D3D12_MESSAGE_SEVERITY_INFO:
			{
				NEPTUNE_LOG_CORE(I) << ss.str();
				break;
			}
		case D3D12_MESSAGE_SEVERITY_WARNING:
			{
				NEPTUNE_LOG_CORE(W) << ss.str();
				break;
			}
		case D3D12_MESSAGE_SEVERITY_ERROR:
			{
				NEPTUNE_LOG_CORE(E) << ss.str();
				break;
			}
		default:
			{
				NEPTUNE_LOG_CORE(I) << ss.str();
				break;
			}
		}
	}
	
	void HandleResult(HRESULT result)
	{
        NEPTUNE_PROFILE_ZONE

		if (!FAILED(result)) return;

		const char* label = "";
		switch (result)
		{

#ifdef D3D12_ERROR_ADAPTER_NOT_FOUND
			case D3D12_ERROR_ADAPTER_NOT_FOUND:                          label = "Cached PSO was created on a different adapter and cannot be reused";                       break;
#endif
			
#ifdef D3D12_ERROR_DRIVER_VERSION_MISMATCH
			case D3D12_ERROR_DRIVER_VERSION_MISMATCH:                    label = "Cached PSO was created on a different driver version and cannot be reused";                break;
#endif
			
#ifdef D3D12_ERROR_INVALID_REDIST
			case D3D12_ERROR_INVALID_REDIST:                             label = "Invalid Redist";                                                                           break;
#endif

			case E_FAIL:												 label = "Generic failure";                                                                          break;
			case E_INVALIDARG:											 label = "Invalid parameter passed to function";                                                     break;
			case E_OUTOFMEMORY:                                          label = "Out of Memory";                                                                            break;
			case E_NOTIMPL:                                              label = "Method not implemented for the given parameter combination";                               break;
			case E_ACCESSDENIED:                                         label = "Access denied";                                                                            break;
			case E_NOINTERFACE:                                          label = "No such interface supported";                                                              break;
			case DXGI_ERROR_INVALID_CALL:                                label = "Invalid method call";                                                                      break;
			case DXGI_ERROR_WAS_STILL_DRAWING:                           label = "Previous operation is still drawing";                                                      break;
			case DXGI_ERROR_DEVICE_REMOVED:                              label = "Device was removed";                                                                       break;
			case DXGI_ERROR_DEVICE_RESET:                                label = "Device was reset due to invalid command or hang";                                          break;
			case DXGI_ERROR_DRIVER_INTERNAL_ERROR:                       label = "Driver internal error occurred";                                                           break;
			case DXGI_ERROR_UNSUPPORTED:                                 label = "Operation not supported by the device or driver";                                          break;
			case DXGI_ERROR_SDK_COMPONENT_MISSING:                       label = "Debug layer requires 'Graphics Tools' optional feature. Install via Windows Settings";     break;
			case DXGI_ERROR_FRAME_STATISTICS_DISJOINT:                   label = "Frame statistics are disjoint from previous queries";                                      break;
			case DXGI_ERROR_NONEXCLUSIVE:                                label = "Could not acquire fullscreen exclusive mode";                                              break;
			case DXGI_ERROR_NOT_CURRENTLY_AVAILABLE:                     label = "Resource or operation not currently available";                                            break;
			case DXGI_ERROR_NOT_FOUND:									 label = "Requested object or resource not found";                                                   break;
			case DXGI_ERROR_WAIT_TIMEOUT:                                label = "Wait operation timed out";                                                                 break;
			default:                                                     label = "Unknown Error";                                                                            break;
		}

        NEPTUNE_LOG_CORE(E) << "Direct3D12 Error: [ " << label << " ]";
	}
}

#endif