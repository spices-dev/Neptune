/**
* @file LayerHeader.h.
* @brief The LayerHeader Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Device/Graphics/Backend/Vulkan/Layer/ApiDump.h"
#include "Device/Graphics/Backend/Vulkan/Layer/CrashDiagnostic.h"
#include "Device/Graphics/Backend/Vulkan/Layer/GfxReconstruct.h"
#include "Device/Graphics/Backend/Vulkan/Layer/Monitor.h"
#include "Device/Graphics/Backend/Vulkan/Layer/ScreenShot.h"
#include "Device/Graphics/Backend/Vulkan/Layer/Validation.h"
#include "Device/Graphics/Backend/Vulkan/Layer/Profiles.h"
#include "Device/Graphics/Backend/Vulkan/Layer/ShaderObject.h"
#include "Device/Graphics/Backend/Vulkan/Layer/Synchronization2.h"
#include "Device/Graphics/Backend/Vulkan/Layer/EOSOverlay.h"
#include "Device/Graphics/Backend/Vulkan/Layer/GPUTrace.h"
#include "Device/Graphics/Backend/Vulkan/Layer/NgfxCapture.h"
#include "Device/Graphics/Backend/Vulkan/Layer/Nomad.h"
#include "Device/Graphics/Backend/Vulkan/Layer/Optimus.h"
#include "Device/Graphics/Backend/Vulkan/Layer/Present.h"
#include "Device/Graphics/Backend/Vulkan/Layer/ShaderDebugger.h"
#include "Device/Graphics/Backend/Vulkan/Layer/Capture.h"
#include "Device/Graphics/Backend/Vulkan/Layer/GvkRestorePoint.h"
#include "Device/Graphics/Backend/Vulkan/Layer/GvkStateTracker.h"
#include "Device/Graphics/Backend/Vulkan/Layer/GvkVirtualSwapchain.h"

#endif