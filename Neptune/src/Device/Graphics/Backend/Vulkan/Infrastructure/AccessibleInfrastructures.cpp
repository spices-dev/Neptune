/**
* @file AccessibleInfrastructures.cpp.
* @brief The AccessibleInfrastructures Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "AccessibleInfrastructures.h"
#include "Instance.h"
#include "PhysicalDevice.h"
#include "Device.h"
#include "Extensions.h"
#include "Queue.h"
#include "DescriptorPool.h"
#include "Device/Graphics/Backend/Vulkan/Extension/Queue.h"

namespace Neptune::Vulkan {

	AccessibleInfrastructures::AccessibleInfrastructures(Context& context, EInfrastructure e)
		: Infrastructure(context, e)
	{
		NEPTUNE_PROFILE_ZONE

		Create();
	}

	void AccessibleInfrastructures::Create()
	{
		NEPTUNE_PROFILE_ZONE
		
		m_Context = CreateSP<AContext>();
		
		m_Context->Registry<AInstance>            (Infrastructure::GetContext().Get<IInstance>()->Handle());
		m_Context->Registry<AApiVersion>          (Infrastructure::GetContext().Get<IInstance>()->GetApiVersion());
		m_Context->Registry<APhysicalDevice>      (Infrastructure::GetContext().Get<IPhysicalDevice>()->Handle());
		m_Context->Registry<ADevice>              (Infrastructure::GetContext().Get<IDevice>()->Handle());
		m_Context->Registry<AGraphicQueueFamily>  (Infrastructure::GetContext().Get<IExtensions>()->GetContext()->Get<Extension::IQueue>()->GetQueueFamily(VK_QUEUE_GRAPHICS_BIT));
		m_Context->Registry<AGraphicQueue>        (Infrastructure::GetContext().Get<IGraphicQueue>()->Handle());
		m_Context->Registry<ADescriptorPool>      (Infrastructure::GetContext().Get<IDescriptorPool>()->Handle());
		m_Context->Registry<AMSAASamples>         (VK_SAMPLE_COUNT_1_BIT);
		m_Context->Registry<AAllocator>           (GetAllocator());
		m_Context->Registry<ACheckResultFn>       (+[](VkResult result) { std::invoke(HandleResultDelegate::GetHandler(), result); });
	}
}

#endif