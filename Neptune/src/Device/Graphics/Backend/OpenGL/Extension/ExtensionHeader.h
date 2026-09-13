/**
* @file ExtensionHeader.h.
* @brief The ExtensionHeader Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Device/Graphics/Backend/OpenGL/Extension/DirectStateAccess.h"
#include "Device/Graphics/Backend/OpenGL/Extension/BufferStorage.h"
#include "Device/Graphics/Backend/OpenGL/Extension/ComputeShader.h"
#include "Device/Graphics/Backend/OpenGL/Extension/MultiDrawIndirect.h"
#include "Device/Graphics/Backend/OpenGL/Extension/IndirectParameters.h"
#include "Device/Graphics/Backend/OpenGL/Extension/ShaderDrawParameters.h"
#include "Device/Graphics/Backend/OpenGL/Extension/ShaderStorageBufferObject.h"
#include "Device/Graphics/Backend/OpenGL/Extension/BindlessTexture.h"
#include "Device/Graphics/Backend/OpenGL/Extension/Spirv.h"
#include "Device/Graphics/Backend/OpenGL/Extension/SeparateShaderObjects.h"
#include "Device/Graphics/Backend/OpenGL/Extension/ParallelShaderCompile.h"
#include "Device/Graphics/Backend/OpenGL/Extension/ClipControl.h"
#include "Device/Graphics/Backend/OpenGL/Extension/ConservativeRaster.h"
#include "Device/Graphics/Backend/OpenGL/Extension/TextureView.h"
#include "Device/Graphics/Backend/OpenGL/Extension/TextureBarrier.h"
#include "Device/Graphics/Backend/OpenGL/Extension/TextureFilterAnisotropic.h"
#include "Device/Graphics/Backend/OpenGL/Extension/SparseTexture.h"
#include "Device/Graphics/Backend/OpenGL/Extension/MeshShader.h"
#include "Device/Graphics/Backend/OpenGL/Extension/ShadingRateImage.h"
#include "Device/Graphics/Backend/OpenGL/Extension/ShaderSubGroup.h"
#include "Device/Graphics/Backend/OpenGL/Extension/ShaderGroupVote.h"
#include "Device/Graphics/Backend/OpenGL/Extension/ShaderInt64.h"
#include "Device/Graphics/Backend/OpenGL/Extension/FragmentShaderInterlock.h"
#include "Device/Graphics/Backend/OpenGL/Extension/ShaderViewportLayerArray.h"
#include "Device/Graphics/Backend/OpenGL/Extension/MemoryObject.h"
#include "Device/Graphics/Backend/OpenGL/Extension/Semaphore.h"
#include "Device/Graphics/Backend/OpenGL/Extension/Debug.h"
#include "Device/Graphics/Backend/OpenGL/Extension/TimerQuery.h"
#include "Device/Graphics/Backend/OpenGL/Extension/PipelineStatisticsQuery.h"
#include "Device/Graphics/Backend/OpenGL/Extension/GetProgramBinary.h"
#include "Device/Graphics/Backend/OpenGL/Extension/Robustness.h"
#include "Device/Graphics/Backend/OpenGL/Extension/ES32Compatibility.h"
#include "Device/Graphics/Backend/OpenGL/Extension/FragmentShaderBarycentric.h"
#include "Device/Graphics/Backend/OpenGL/Extension/InvalidateSubdata.h"
#include "Device/Graphics/Backend/OpenGL/Extension/MultiBind.h"
#include "Device/Graphics/Backend/OpenGL/Extension/QueryBufferObject.h"
#include "Device/Graphics/Backend/OpenGL/Extension/TimelineSemaphore.h"
#include "Device/Graphics/Backend/OpenGL/Extension/VertexAttribBinding.h"
#include "Device/Graphics/Backend/OpenGL/Extension/KeydMutex.h"
#include "Device/Graphics/Backend/OpenGL/Extension/ViewportLayerArray.h"

#endif