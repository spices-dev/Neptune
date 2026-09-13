/**
* @file Resource.h.
* @brief The Resource Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

#include <any>
#include <functional>
#include <memory>
#include <mutex>

namespace Neptune {

	/**
	* @brief Resource Wrapper of ResourceInstance.
	*/
	class Resource
	{
	public:

		/**
		* @brief Enum of ResourceState
		*/
		enum class ResourceStateEnum
		{
			UnLoad    = 0,   /* @brief UnLoad.         */
			OnLoading = 1,   /* @brief On Loading.     */
			Loaded    = 2,   /* @brief Already Loaded. */
			OnDestroy = 3,   /* @brief On Destroy.     */
		};

	public:

		/**
		* @brief Constructor Function.
		* 
		* @param[in] fn function pointer of create resource instance.
		*/
		explicit Resource(const std::function<std::any()>& fn)
			: m_Creator(fn)
			, m_State(ResourceStateEnum::UnLoad)
		{}

		/**
		* @brief Constructor Function.
		* This mode cannot call CreateResource().
		* 
		* @param[in] resource Resource instance.
		*/
		explicit Resource(const std::any& resource)
			: m_Creator(nullptr)
			, m_State(ResourceStateEnum::Loaded)
			, m_Resource(resource)
		{}

		/**
		* @brief Unload resource.
		*/
		virtual ~Resource()
		{
			NEPTUNE_PROFILE_ZONE

			UnLoad();
		}

		/**
		* @brief Get resource state.
		* @return Returns resource state.
		*/
		ResourceStateEnum GetState() const { return m_State; }

		/**
		* @brief Get resource instance.
		* @return Returns resource instance.
		*/
		template<typename T>
		std::shared_ptr<T> GetResource();
		
		/**
		* @brief UnLoad this resource.
		*/
		void UnLoad();

	private:

		/**
		* @brief Create resource instance.
		*/
		void CreateResource();

	private:
		
		std::any m_Resource;                               // @brief Resource instance wrapper.
		std::atomic<ResourceStateEnum> m_State;            // @brief Resource state.
		std::function<std::any()> m_Creator;               // @brief Resource create function.
		mutable std::mutex m_Mutex;                        // @brief Mutex of this resource.
	};

	inline void Resource::UnLoad()
	{
		NEPTUNE_PROFILE_ZONE

		std::unique_lock lock(m_Mutex);
		
		if (m_State == ResourceStateEnum::UnLoad) return;
		
		m_State = ResourceStateEnum::OnDestroy;

		m_Resource.reset();

		m_State = ResourceStateEnum::UnLoad;
	}

	inline void Resource::CreateResource()
	{
		NEPTUNE_PROFILE_ZONE

		std::unique_lock lock(m_Mutex);
		
		if (m_State == ResourceStateEnum::Loaded) return;
		
		m_State = ResourceStateEnum::OnLoading;

		m_Resource = std::invoke(m_Creator);

		m_State = ResourceStateEnum::Loaded;
	}

	template<typename T>
	inline SP<T> Resource::GetResource()
	{
		NEPTUNE_PROFILE_ZONE

		std::unique_lock lock(m_Mutex);

		if (m_State == ResourceStateEnum::Loaded)
		{
			return std::any_cast<SP<T>>(m_Resource);
		}

		m_State = ResourceStateEnum::OnLoading;

		m_Resource = std::invoke(m_Creator);

		m_State = ResourceStateEnum::Loaded;

		return std::any_cast<SP<T>>(m_Resource);
	}
}