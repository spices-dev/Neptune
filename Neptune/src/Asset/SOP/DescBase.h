/**
* @file DescBase.h.
* @brief The DescBase Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/Concept.h"
#include "Attribute.h"
#include "Header/Core.h"

namespace Neptune::SOP {
	
#define Update_Attribute(item)                                                   \
	{                                                                            \
		using Item = Decay<decltype(item)>;                                      \
		BufferCreateInfo info{};                                                 \
		info.size = item.host->size() * sizeof(typename Item::T_);               \
		info.usage.Set(Graphic::EBufferUsage::TransferDst);                      \
		item.device->CreateBuffer(info);                                         \
		item.device->WriteToBuffer(item.host->data(), info.size);                \
		item.device->Flush(info.size);                                           \
		item.device->SetName(#item);                                             \
		(*desc.host)[0].item##Address = item.device->GetDeviceAddress();         \
	}
	
#define Update_Desc(item)                                                        \
	{                                                                            \
		using Item = Decay<decltype(item)>;                                      \
		BufferCreateInfo info{};                                                 \
		info.size = item.host->size() * sizeof(typename Item::T_);               \
		info.usage.Set(Graphic::EBufferUsage::TransferDst);                      \
		item.device->CreateBuffer(info);                                         \
		item.device->WriteToBuffer(item.host->data(), info.size);                \
		item.device->Flush(info.size);                                           \
		item.device->SetName(#item);                                             \
		item##Address = item.device->GetDeviceAddress();                         \
	}
	
	/**
	* @brief DescBase Struct.
	*/
	template<typename T>
	struct DescBase
	{
		/**
		* @brief Constructor Function.
		*/
		DescBase()
		{
			desc.host->resize(1);
		}

		/**
		* @brief Destructor Function.
		*/
		virtual ~DescBase() = default;
		
		/**
		* @brief Upload Host data to Device.
		*/
		virtual void UploadToDevice();
		
		using Desc = Attribute<T>;  
		
		Desc desc;                   // @brief this Desc.
		uint64_t descAddress = 0;    // @brief this Desc Device Address.
	};
	
	template<typename T>
	void DescBase<T>::UploadToDevice()
	{
		NEPTUNE_PROFILE_ZONE
		
		Update_Desc(desc)
	}
}