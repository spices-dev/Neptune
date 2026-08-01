/**
* @file ProfilerD.h file.
* @brief The ProfilerD Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PROFILER_TRACY

#ifdef NP_GRAPHICS_OPENCL_CORE
#include "Debugger/Profiler/Tracy/ProfilerImplOpenCL.h"
#endif

#ifdef NP_GRAPHICS_CUDA_CORE
#include "Debugger/Profiler/Tracy/ProfilerImplCUDA.h"
#endif

#ifdef NP_GRAPHICS_DIRECT3D11_CORE
#include "Debugger/Profiler/Tracy/ProfilerImplDirect3D11.h"
#endif

#ifdef NP_GRAPHICS_DIRECT3D12_CORE
#include "Debugger/Profiler/Tracy/ProfilerImplDirect3D12.h"
#endif

#ifdef NP_GRAPHICS_OPENGL_CORE
#include "Debugger/Profiler/Tracy/ProfilerImplOpenGL.h"
#endif

#ifdef NP_GRAPHICS_VULKAN_CORE
#include "Debugger/Profiler/Tracy/ProfilerImplVulkan.h"
#endif

#else

/**
* @brief Create Device Context.
*/
#define NEPTUNE_PROFILE_CREATE_DEVICE_CONTEXT(...)

/**
* @brief Name Device Context .
*/
#define NEPTUNE_PROFILE_NAME_DEVICE_CONTEXT(...)

/**
* @brief Destroy Device Context.
*/
#define NEPTUNE_PROFILE_DESTROY_DEVICE_CONTEXT(...)

/**
* @brief Mark Device Zone.
*/
#define NEPTUNE_PROFILE_DEVICE_ZONE(...)

/**
* @brief Collect Device Zone Data.
*/
#define NEPTUNE_PROFILE_DEVICE_COLLECT(...)

#endif
