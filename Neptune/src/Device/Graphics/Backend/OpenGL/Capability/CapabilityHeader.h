/**
* @file CapabilityHeader.h.
* @brief The CapabilityHeader Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Device/Graphics/Backend/OpenGL/Capability/DirectStateAccess.h"
#include "Device/Graphics/Backend/OpenGL/Capability/BufferStorage.h"
#include "Device/Graphics/Backend/OpenGL/Capability/ComputeShader.h"
#include "Device/Graphics/Backend/OpenGL/Capability/MultiDrawIndirect.h"
#include "Device/Graphics/Backend/OpenGL/Capability/IndirectParameters.h"
#include "Device/Graphics/Backend/OpenGL/Capability/ShaderDrawParameters.h"
#include "Device/Graphics/Backend/OpenGL/Capability/ShaderStorageBufferObject.h"
#include "Device/Graphics/Backend/OpenGL/Capability/BindlessTexture.h"
#include "Device/Graphics/Backend/OpenGL/Capability/Spirv.h"
#include "Device/Graphics/Backend/OpenGL/Capability/SeparateShaderObjects.h"
#include "Device/Graphics/Backend/OpenGL/Capability/ParallelShaderCompile.h"
#include "Device/Graphics/Backend/OpenGL/Capability/ClipControl.h"
#include "Device/Graphics/Backend/OpenGL/Capability/ConservativeRaster.h"
#include "Device/Graphics/Backend/OpenGL/Capability/TextureView.h"
#include "Device/Graphics/Backend/OpenGL/Capability/TextureBarrier.h"
#include "Device/Graphics/Backend/OpenGL/Capability/TextureFilterAnisotropic.h"
#include "Device/Graphics/Backend/OpenGL/Capability/SparseTexture.h"
#include "Device/Graphics/Backend/OpenGL/Capability/MeshShader.h"
#include "Device/Graphics/Backend/OpenGL/Capability/ShadingRateImage.h"
#include "Device/Graphics/Backend/OpenGL/Capability/ShaderSubGroup.h"
#include "Device/Graphics/Backend/OpenGL/Capability/ShaderGroupVote.h"
#include "Device/Graphics/Backend/OpenGL/Capability/ShaderInt64.h"
#include "Device/Graphics/Backend/OpenGL/Capability/FragmentShaderInterlock.h"
#include "Device/Graphics/Backend/OpenGL/Capability/ShaderViewportLayerArray.h"
#include "Device/Graphics/Backend/OpenGL/Capability/MemoryObject.h"
#include "Device/Graphics/Backend/OpenGL/Capability/Semaphore.h"
#include "Device/Graphics/Backend/OpenGL/Capability/Debug.h"
#include "Device/Graphics/Backend/OpenGL/Capability/TimerQuery.h"
#include "Device/Graphics/Backend/OpenGL/Capability/PipelineStatisticsQuery.h"
#include "Device/Graphics/Backend/OpenGL/Capability/GetProgramBinary.h"
#include "Device/Graphics/Backend/OpenGL/Capability/Robustness.h"
#include "Device/Graphics/Backend/OpenGL/Capability/ES32Compatibility.h"
#include "Device/Graphics/Backend/OpenGL/Capability/FragmentShaderBarycentric.h"
#include "Device/Graphics/Backend/OpenGL/Capability/InvalidateSubdata.h"
#include "Device/Graphics/Backend/OpenGL/Capability/MultiBind.h"
#include "Device/Graphics/Backend/OpenGL/Capability/QueryBufferObject.h"
#include "Device/Graphics/Backend/OpenGL/Capability/TimelineSemaphore.h"
#include "Device/Graphics/Backend/OpenGL/Capability/VertexAttribBinding.h"
#include "Device/Graphics/Backend/OpenGL/Capability/KeydMutex.h"

#endif