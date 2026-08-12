/**
* @file Version.h.
* @brief The Version Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_METAL

#include <Metal/Metal.hpp>

namespace Neptune::Metal {

	using MTLAutoreleasePool                = NS::AutoreleasePool*;
	
	//using MTLAccelerationStructure          = MTL4::AccelerationStructure*;
	using MTLArchive                        = MTL4::Archive*;
	using MTLArgumentTable                  = MTL4::ArgumentTable*;
	using MTLBinaryFunction                 = MTL4::BinaryFunction*;
	using MTLBinaryFunctionDescriptor       = MTL4::BinaryFunctionDescriptor*;
	using MTLCommandAllocator               = MTL4::CommandAllocator*;
	using MTLCommandBuffer                  = MTL4::CommandBuffer*;
	using MTLCommandEncoder                 = MTL4::CommandEncoder*;
	using MTLCommandQueue                   = MTL4::CommandQueue*;
	using MTLCommitFeedback                 = MTL4::CommitFeedback*;
	using MTLCompiler                       = MTL4::Compiler*;
	using MTLCompilerTask                   = MTL4::CompilerTask*;
	using MTLComputeCommandEncoder          = MTL4::ComputeCommandEncoder*;
	//using MTLComputePipeline                = MTL4::ComputePipeline*;
	//using MTLCounters                       = MTL4::Counters*;
	using MTLFunctionDescriptor             = MTL4::FunctionDescriptor*;
	using MTLLibraryDescriptor              = MTL4::LibraryDescriptor*;
	using MTLLibraryFunctionDescriptor      = MTL4::LibraryFunctionDescriptor*;
	//using MTLLinkingDescriptor              = MTL4::LinkingDescriptor*;
	using MTLMachineLearningCommandEncoder  = MTL4::MachineLearningCommandEncoder*;
	//using MTLMachineLearningPipeline        = MTL4::MachineLearningPipeline*;
	//using MTLMeshRenderPipeline             = MTL::MeshRenderPipeline*;
	//using MTLPipelineDataSetSerializer      = MTL::PipelineDataSetSerializer*;
	//using MTLPipelineState                  = MTL::PipelineState*;
	using MTLRenderCommandEncoder           = MTL::RenderCommandEncoder*;
	//using MTLRenderPass                     = MTL::RenderPass*;
	//using MTLRenderPipeline                 = MTL::RenderPipeline*;
	//using MTLSpecializedFunctionDescriptor  = MTL::SpecializedFunctionDescriptor*;
	//using MTLStitchedFunctionDescriptor     = MTL::StitchedFunctionDescriptor*;
	//using MTLTileRenderPipeline             = MTL::TileRenderPipeline*;
	using MTLAllocation                     = MTL::Allocation*;
	using MTLBlitCommandEncoder             = MTL::BlitCommandEncoder*;
	//using MTLBlitPass                       = MTL::BlitPass*;
	using MTLBuffer                         = MTL::Buffer*;
	using MTLCaptureManager                 = MTL::CaptureManager*;
	using MTLCaptureScope                   = MTL::CaptureScope*;
	//using MTLComputePass                    = MTL::ComputePass*;
	//using MTLComputePipeline                = MTL::ComputePipeline*;
	//using MTLCounters                       = MTL::Counters*;
	using MTLDataType                       = MTL::DataType*;
	//using MTLDefines                        = MTL::Defines*;
	//using MTLDepthStencil                   = MTL::DepthStencil*;
	using MTLDevice                         = MTL::Device*;
	using MTLDrawable                       = MTL::Drawable*;
	using MTLDynamicLibrary                 = MTL::DynamicLibrary*;
	using MTLEvent                          = MTL::Event*;
	using MTLFence                          = MTL::Fence*;
	using MTLFunctionConstantValues         = MTL::FunctionConstantValues*;
	using MTLFunctionHandle                 = MTL::FunctionHandle*;
	using MTLFunctionLog                    = MTL::FunctionLog*;
	//using MTLFunctionStitching              = MTL::FunctionStitching*;
	using MTLGPUAddress                     = MTL::GPUAddress*;
	//using MTLHeaderBridge                   = MTL::HeaderBridge*;
	using MTLHeap                           = MTL::Heap*;
	using MTLIndirectCommandBuffer          = MTL::IndirectCommandBuffer*;
	//using MTLIndirectCommandEncoder         = MTL::IndirectCommandEncoder*;
	using MTLIntersectionFunctionTable      = MTL::IntersectionFunctionTable*;
	using MTLIOCommandBuffer                = MTL::IOCommandBuffer*;
	using MTLIOCommandQueue                 = MTL::IOCommandQueue*;
	//using MTLIOCompressor                   = MTL::IOCompressor*;
	using MTLLibrary                        = MTL::Library*;
	using MTLLinkedFunctions                = MTL::LinkedFunctions*;
	using MTLLogState                       = MTL::LogState*;
	using MTLParallelRenderCommandEncoder   = MTL::ParallelRenderCommandEncoder*;
	//using MTLPipeline                       = MTL::Pipeline*;
	using MTLRenderPipelineState            = MTL::RenderPipelineState*;
	//using MTLRasterizationRate              = MTL::RasterizationRate*;
	using MTLRenderCommandEncoder           = MTL::RenderCommandEncoder*;
	//using MTLRenderPass                     = MTL::RenderPass*;
	//using MTLRenderPipeline                 = MTL::RenderPipeline*;
	using MTLResidencySet                   = MTL::ResidencySet*;
	using MTLResource                       = MTL::Resource*;
	using MTLResourceStateCommandEncoder    = MTL::ResourceStateCommandEncoder*;
	//using MTLResourceStatePass              = MTL::ResourceStatePass*;
	using MTLResourceViewPool               = MTL::ResourceViewPool*;
	//using MTLSampler                        = MTL::Sampler*;
	using MTLStageInputOutputDescriptor     = MTL::StageInputOutputDescriptor*;
	using MTLTensor                         = MTL::Tensor*;
	using MTLTexture                        = MTL::Texture*;
	using MTLTextureViewPool                = MTL::TextureViewPool*;
	//using MTLTypes                          = MTL::Types*;
	//using MTLVersion                        = MTL::Version*;
	using MTLVertexDescriptor               = MTL::VertexDescriptor*;
	using MTLVisibleFunctionTable            = MTL::VisibleFunctionTable*;

}

#endif