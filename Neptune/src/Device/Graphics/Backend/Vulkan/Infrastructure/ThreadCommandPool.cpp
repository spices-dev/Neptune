/**
* @file ThreadCommandPool.cpp.
* @brief The ThreadCommandPool Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "ThreadCommandPool.h"
#include "Device.h"
#include "DebugUtilsObject.h"
#include "Extensions.h"
#include "Device/Graphics/Backend/Vulkan/Extension/Queue.h"

namespace Neptune::Vulkan {

	namespace {
	
		/**
		* @brief Thread CommandPool Thread ID.
		*/
		class ThreadID
		{
		public:

			/**
			* @brief Constructor Function.
			*/
			ThreadID() = default;

			/**
			* @brief Destructor Function.
			*/
			virtual ~ThreadID()
			{
				if (!m_GuardDeleter)
				{
					return;
				}

				if (m_GraphicId.has_value())     std::invoke(m_GuardDeleter, m_GraphicId.value());
				if (m_ComputeId.has_value())     std::invoke(m_GuardDeleter, m_ComputeId.value());
				if (m_TransferId.has_value())    std::invoke(m_GuardDeleter, m_TransferId.value());
				if (m_VideoEncodeId.has_value()) std::invoke(m_GuardDeleter, m_VideoEncodeId.value());
				if (m_VideoDecodeId.has_value()) std::invoke(m_GuardDeleter, m_VideoDecodeId.value());
				if (m_OpticalFlowId.has_value()) std::invoke(m_GuardDeleter, m_OpticalFlowId.value());
			}

			/**
			* @brief Get Thread CommandPool id.
			* 
			* @param[in] e EInfrastructure.
			* 
			* @return Returns Thread CommandPool id.
			*/
			const std::optional<UUID>& Id(EInfrastructure e) const
			{
				static constexpr std::optional<UUID> nullopt = std::nullopt; 
				
				using enum EInfrastructure;
				
				switch (e)
				{
					case GraphicThreadCommandPool:     return m_GraphicId;
					case ComputeThreadCommandPool:     return m_ComputeId;
					case TransferThreadCommandPool:    return m_TransferId;
					case VideoEncodeThreadCommandPool: return m_VideoEncodeId;
					case VideoDecodeThreadCommandPool: return m_VideoDecodeId;
					case OpticalFlowThreadCommandPool: return m_OpticalFlowId;
					default: return nullopt;
				}
			}

			/**
			* @brief Set Thread CommandPool id.
			*
			* @param[in] id Thread CommandPool id.
			* @param[in] e EInfrastructure.
			*/
			void SetId(const UUID& id, EInfrastructure e)
			{
				using enum EInfrastructure;
				
				switch (e)
				{
					case GraphicThreadCommandPool:     m_GraphicId     = id; return;
					case ComputeThreadCommandPool:     m_ComputeId     = id; return;
					case TransferThreadCommandPool:    m_TransferId    = id; return;
					case VideoEncodeThreadCommandPool: m_VideoEncodeId = id; return;
					case VideoDecodeThreadCommandPool: m_VideoDecodeId = id; return;
					case OpticalFlowThreadCommandPool: m_OpticalFlowId = id; return;
					default: return;
				}
			}

			/**
			* @brief Set Thread CommandPool Guard Deleter.
			*
			* @param[in] deleter Thread CommandPool Guard Deleter.
			*/
			void SetGuardDeleter(const std::function<void(UUID)>& deleter)
			{
				m_GuardDeleter = deleter;
			}

		public:

			std::optional<UUID> m_GraphicId;            // @brief Graphic Sub Thread CommandPool id.
			std::optional<UUID> m_ComputeId;            // @brief Compute Sub Thread CommandPool id.
			std::optional<UUID> m_TransferId;           // @brief Transfer Sub Thread CommandPool id.
			std::optional<UUID> m_VideoEncodeId;        // @brief VideoEncode Sub Thread CommandPool id.
			std::optional<UUID> m_VideoDecodeId;        // @brief VideoDecode Sub Thread CommandPool id.
			std::optional<UUID> m_OpticalFlowId;        // @brief OpticalFlow Sub Thread CommandPool id.

			std::function<void(UUID)> m_GuardDeleter;   // @brief ThreadCommandPool Guard.
		};

		thread_local ThreadID s_TLSThreadID;            // @brief Thread id instance.

	}

	ThreadCommandPool::ThreadCommandPool(Context& context, EInfrastructure e)
		: Infrastructure(context, e)
		, m_Life(CreateSP<std::monostate>())
	{}

	const VkCommandPool& ThreadCommandPool::Handle()
	{
		NEPTUNE_PROFILE_ZONE

		auto id = s_TLSThreadID.Id(GetEInfrastructure());

		if (id.has_value())
		{
			return m_CommandPools[id.value()]->GetHandle();
		}

		UUID uuid;

		s_TLSThreadID.SetId(uuid, GetEInfrastructure());

		WP life = m_Life;
		s_TLSThreadID.SetGuardDeleter([life, this](UUID id) {
			if (!life.lock())
			{
				return;
			}
			
			this->Release(id);
		});

		auto commandPool = Create();

		std::unique_lock lock(m_Mutex);

		m_CommandPools[uuid] = commandPool;

		return commandPool->GetHandle();
	}

	void ThreadCommandPool::Release(UUID id)
	{
		NEPTUNE_PROFILE_ZONE

		std::unique_lock lock(m_Mutex);

		m_CommandPools.erase(id);
	}

	SP<Unit::CommandPool> ThreadCommandPool::Create() const
	{
		NEPTUNE_PROFILE_ZONE

		VkCommandPoolCreateInfo                   poolInfo{};
		poolInfo.sType                          = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolInfo.flags                          = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		poolInfo.queueFamilyIndex               = GetQueueFamily();

		auto commandPool = CreateSP<Unit::CommandPool>();

		commandPool->CreateCommandPool(GetContext().Get<IDevice>()->Handle(), poolInfo);

		DEBUGUTILS_SETOBJECTNAME(*commandPool, ToString())

		return commandPool;
	}

	uint32_t ThreadCommandPool::GetQueueFamily() const
	{
		NEPTUNE_PROFILE_ZONE

		using enum EInfrastructure;
		
		switch (GetEInfrastructure())
		{
			case GraphicThreadCommandPool:	   return GetContext().Get<IExtensions>()->GetContext().Get<Extension::IQueue>()->GetQueueFamily(VK_QUEUE_GRAPHICS_BIT);
			case ComputeThreadCommandPool:     return GetContext().Get<IExtensions>()->GetContext().Get<Extension::IQueue>()->GetQueueFamily(VK_QUEUE_COMPUTE_BIT);
			case TransferThreadCommandPool:    return GetContext().Get<IExtensions>()->GetContext().Get<Extension::IQueue>()->GetQueueFamily(VK_QUEUE_TRANSFER_BIT);
			case VideoEncodeThreadCommandPool: return GetContext().Get<IExtensions>()->GetContext().Get<Extension::IQueue>()->GetQueueFamily(VK_QUEUE_VIDEO_ENCODE_BIT_KHR);
			case VideoDecodeThreadCommandPool: return GetContext().Get<IExtensions>()->GetContext().Get<Extension::IQueue>()->GetQueueFamily(VK_QUEUE_VIDEO_DECODE_BIT_KHR);
			case OpticalFlowThreadCommandPool: return GetContext().Get<IExtensions>()->GetContext().Get<Extension::IQueue>()->GetQueueFamily(VK_QUEUE_OPTICAL_FLOW_BIT_NV);
			default: return 0;
		}
	}
}

#endif