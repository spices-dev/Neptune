/**
* @file CmdList.h.
* @brief The CmdList Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Device/Graphics/Frontend/Memory.h"
#include "Data/Clock.h"

#include <functional>

namespace Neptune::RHI {
	
	/**
	* @brief Enum of Cmd.
	*/
	enum class ECmd : uint16_t 
	{
		SetGraphicCmdList,                  // @brief SetGraphicCmdList
		SetComputeCmdList,                  // @brief SetComputeCmdList
		SetRenderPass,                      // @brief SetRenderPass
		
		BeginRenderPass,                    // @brief BeginRenderPass
		EndRenderPass,                      // @brief EndRenderPass
		
		BindDescriptor,                     // @brief BindDescriptor
		BindPipeline,                       // @brief BindPipeline
		BindIndexBuffer,                    // @brief BindIndexBuffer
		
		UpdateShaderConstant,               // @brief UpdateShaderConstant
		
		FillBuffer,                         // @brief FillBuffer
		
		Draw,                               // @brief Draw
		DrawIndexed,                        // @brief DrawIndexed
		DrawIndexedIndirect,                // @brief DrawIndexedIndirect
		DrawIndirect,                       // @brief DrawIndirect
		
		Dispatch,                           // @brief Dispatch
		DispatchIndirect,                   // @brief DispatchIndirect
		
		InsertImageBarrier,                 // @brief InsertImageBarrier
		InsertMemoryBarrier,                // @brief InsertMemoryBarrier
		
		SetViewport,                        // @brief SetViewport
		
		ExecuteNative,                      // @brief ExecuteNative
		
		Count
	};
	
	/**
	* @brief Single Cmd Data.
	*/
	struct Cmd
	{
		/**
		* @brief Constructor Function.
		*/
		Cmd() : m_Clock() {}
		
		ECmd m_Op = ECmd::Count;           // @brief ECmd

		union
		{
			Data::Clock                                                                                               m_Clock;                  // @brief Data::Clock
			struct { uint32_t ref; }                                                                                  m_Ref;                    // @brief Pure Reference
			struct { uint32_t blobOffset, blobSize, shaderOffset; }                                                   m_Constant;               // @brief Shader Constant
			struct { uint32_t ref; uint64_t dstOffset, size; uint32_t data; }                                         m_Fill;                   // @brief Fill Buffer
			struct { uint32_t vertexCount, instanceCount,firstVertex, firstInstance; }                                m_Draw;                   // @brief Draw 
			struct { uint32_t indexCount, instanceCount, firstIndex; int32_t vertexOffset; uint32_t firstInstance; }  m_DrawIndexed;            // @brief DrawIndexed
			struct { uint32_t ref; uint64_t offset; uint32_t drawCount, stride; }                                     m_Indirect;               // @brief DrawIndirect
			struct { uint32_t x, y, z; }                                                                              m_Dispatch;               // @brief Dispatch
			struct { uint32_t ref; uint64_t offset; }                                                                 m_DispatchIndirect;       // @brief DispatchIndirect
			struct { uint32_t ref; uint32_t desc; }                                                                   m_ImageBarrier;           // @brief ImageBarrier
			struct { uint32_t desc; }                                                                                 m_MemoryBarrier;          // @brief MemoryBarrier
			struct { uint32_t width, height; }                                                                        m_Viewport;               // @brief Viewport
			struct { uint32_t native; }                                                                               m_Native;                 // @brief Native Reference
		};
	};
	
	/**
	* @brief Cmd Stream.
	*/
	class CmdStream
	{
	public:
		
		/**
		* @brief Constructor Function.
		*/
		CmdStream() = default;
		
		/**
		* @brief Destructor Function.
		*/
		virtual ~CmdStream() = default;
		
		NONE_COPY(CmdStream)
		
		/**
		* @brief Push a Cmd.
		* 
		* @param[in] op ECmd.
		* 
		* @return Returns Cmd.
		*/
		Cmd& Push(ECmd op)
		{
			auto& cmd = m_Cmds.emplace_back();
			
			cmd.m_Op = op;
			
			return cmd;
		}
		
		/**
		* @brief Keep a Reference.
		* 
		* @param[in] sp Reference.
		* 
		* @return Returns Reference Position.
		*/
		template<typename T>
		uint32_t Keep(const SP<T>& sp)
		{
			const auto index = static_cast<uint32_t>(m_Refs.size());
			
			m_Refs.emplace_back(sp);
			
			return index;
		}
		
		/**
		* @brief Push a Blob.
		* 
		* @param[in] data .
		* @param[in] size .
		* 
		* @return Returns Blob Position.
		*/
		uint32_t PushBlob(const void* data, uint32_t size)
		{
			const auto offset = static_cast<uint32_t>(m_Blob.size());
			
			m_Blob.resize(m_Blob.size() + size);
			
			if (size) std::memcpy(m_Blob.data() + offset, data, size);
			
			return offset;
		}
		
		/**
		* @brief Push a ImageBarrier.
		* 
		* @param[in] desc Graphic::ImageBarrierDesc.
		* 
		* @return Returns ImageBarrier Position.
		*/
		uint32_t PushImageBarrier(const Graphic::ImageBarrierDesc& desc)
		{
			const auto index = static_cast<uint32_t>(m_ImageBarriers.size());
			
			m_ImageBarriers.emplace_back(desc);
			
			return index;
		}
		
		/**
		* @brief Push a MemoryBarrier.
		* 
		* @param[in] desc Graphic::MemoryBarrierDesc.
		* 
		* @return Returns MemoryBarrier Position.
		*/
		uint32_t PushMemoryBarrier(const Graphic::MemoryBarrierDesc& desc)
		{
			const auto index = static_cast<uint32_t>(m_MemoryBarriers.size());
			
			m_MemoryBarriers.emplace_back(desc);
			
			return index;
		}
		
		/**
		* @brief Push a Native Function.
		* 
		* @param[in] fn Native Function.
		* 
		* @return Returns Function Position.
		*/
		uint32_t PushNative(std::function<void(void*)>&& fn)
		{
			const auto index = static_cast<uint32_t>(m_Natives.size());
			
			m_Natives.emplace_back(std::move(fn));
			
			return index;
		}
		
		/**
		* @brief Get Commands.
		* 
		* @return Returns Commands.
		*/
		std::span<const Cmd> Commands() const { return m_Cmds; }
		
		/**
		* @brief Get Reference Raw Pointer.
		* 
		* @param[in] index Reference Position.
		* 
		* @return Returns Reference Raw Pointer.
		*/
		template<typename T>
		T* Ptr(uint32_t index) const { return static_cast<T*>(m_Refs[index].get()); }
		
		/**
		* @brief Get Reference.
		* 
		* @param[in] index Reference Position.
		* 
		* @return Returns Reference.
		*/
		template<typename T>
		SP<T> Ref(uint32_t index) const { return std::static_pointer_cast<T>(m_Refs[index]); }
		
		/**
		* @brief Get Blob.
		* 
		* @param[in] offset Blob Offset.
		* 
		* @return Returns Blob Data.
		*/
		const void* BlobAt(uint32_t offset) const { return m_Blob.data() + offset; }
		
		/**
		* @brief Get ImageBarrier.
		* 
		* @param[in] index ImageBarrier Position.
		* 
		* @return Returns ImageBarrier.
		*/
		const Graphic::ImageBarrierDesc& ImageBarrier(uint32_t index) const { return m_ImageBarriers[index]; }
		
		/**
		* @brief Get MemoryBarrier.
		* 
		* @param[in] index MemoryBarrier Position.
		* 
		* @return Returns MemoryBarrier.
		*/
		const Graphic::MemoryBarrierDesc& MemoryBarrier(uint32_t index) const { return m_MemoryBarriers[index]; }
		
		/**
		* @brief Get Native Function.
		* 
		* @param[in] index Function Position.
		* 
		* @return Returns Function.
		*/
		const std::function<void(void*)>& Native(uint32_t index) const { return m_Natives[index]; }
		
		/**
		* @brief Reset Data.
		*/
		void Reset()
		{
			NEPTUNE_PROFILE_ZONE
			
			m_Cmds           .clear();
			m_Refs           .clear();
			m_Blob           .clear();
			m_ImageBarriers  .clear();
			m_MemoryBarriers .clear();
			m_Natives        .clear();
		}
		
	private:
		
		std::vector<Cmd>                         m_Cmds;                      // @brief Commands
		std::vector<SP<void>>                    m_Refs;                      // @brief References
		std::vector<std::byte>                   m_Blob;                      // @brief Blobs
		std::vector<Graphic::ImageBarrierDesc>   m_ImageBarriers;             // @brief ImageBarriers
		std::vector<Graphic::MemoryBarrierDesc>  m_MemoryBarriers;            // @brief MemoryBarriers
		std::vector<std::function<void(void*)>>  m_Natives;                   // @brief Native Functions
	};
}