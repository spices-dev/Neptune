/**
* @file ProfilerImplVulkan.h file.
* @brief The ProfilerImplVulkan Class Definitions.
* @author Spices.
*/

#pragma once

#if defined(NP_PROFILER_TRACY) && defined(NP_GRAPHICS_VULKAN)

#include <volk.h>
#include <tracy/TracyVulkan.hpp>

#define NEPTUNE_PROFILE_CREATE_DEVICE_CONTEXT(...)           TracyVkContext(__VA_ARGS__)
#define NEPTUNE_PROFILE_NAME_DEVICE_CONTEXT(...)             TracyVkContextName(__VA_ARGS__)
#define NEPTUNE_PROFILE_DESTROY_DEVICE_CONTEXT(...)          TracyVkDestroy(__VA_ARGS__)
#define NEPTUNE_PROFILE_DEVICE_ZONE(...)                     TracyVkZone(__VA_ARGS__)
#define NEPTUNE_PROFILE_DEVICE_COLLECT(...)                  TracyVkCollect(__VA_ARGS__)

#endif