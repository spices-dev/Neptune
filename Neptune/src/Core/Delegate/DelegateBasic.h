/**
* @file DelegateBasic.h
* @brief The Delegate_Basic Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/Container/LinkedUnorderedMap.h"

namespace Neptune {

	/**
	* @brief Basic Class of Delegate.
	* Instance inherited from it and use delegate feature.
	* 
	* @note thread safe.
	*/
	template<typename... Args>
	class Delegate_Basic
	{
	public:

		/**
		* @brief Agent Function.
		* 
		* @tparam Args
		*/
		using Agent = std::function<void(Args...)>;

	public:

		/**
		* @brief Constructor Function.
		*/
		Delegate_Basic() = default;

		/**
		* @brief Destructor Function.
		*/
		virtual ~Delegate_Basic() = default;

		/**
		* @brief Bind Function pointer to delegate.
		* 
		* @param[in] func Function pointer.
		* 
		* @return Returns Agent Handle.
		*/
		template<typename Fn>
		uint64_t Bind(Fn&& func);

		/**
		* @brief UnBind Function pointer from delegate.
		* 
		* @param[in] handle Agent Handle.
		* 
		* @return Returns true if unbind successfully.
		*/
		bool UnBind(uint64_t handle);

		/**
		* @brief Get size of Agents.
		* 
		* @return Returns the size of Agents.
		*/
		size_t Size() const { return m_Agents->Size(); }

		/**
		* @brief Determine if this Delegate is empty;
		* 
		* @return Returns true if empty.
		*/
		bool Empty() const { return m_Agents->Size() == 0; }

		/**
		* @brief Execute all function pointer. 
		* 
		* @param[in] args .
		*/
		template<typename... Args1>
		void Broadcast(Args1&&... args) const;

	private:
		
		SP<Container::LinkedUnorderedMap<uint64_t, Agent>> m_Agents = CreateSP<Container::LinkedUnorderedMap<uint64_t, Agent>>();  // @brief Map of Agent Function Pointer.
		SP<std::atomic_uint64_t> m_Handle = CreateSP<std::atomic_uint64_t>(0);   // @brief Current Bind Handle.
	};

	template<typename ...Args>
	template<typename Fn>
	inline uint64_t Delegate_Basic<Args...>::Bind(Fn&& func)
	{
		NEPTUNE_PROFILE_ZONE

		auto& handle = *m_Handle;

		m_Agents->PushBack(handle, func);
		
		return handle++;
	}

	template<typename ...Args>
	inline bool Delegate_Basic<Args...>::UnBind(uint64_t handle)
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Agents->Contains(handle)) return false;
		
		m_Agents->Erase(handle);

		return true;
	}

	template<typename ...Args>
	template<typename... Args1>
	inline void Delegate_Basic<Args...>::Broadcast(Args1&&... args) const
	{
		NEPTUNE_PROFILE_ZONE

		m_Agents->ForEach([&](const auto& k, const auto& v) {
			
			std::invoke(v, args...);
			
			return false;
		});
	}

/**
* @brief Use this macro to instance a Delegate Class.
* Any Parameter Specific.
*/
#define DELEGATE(name, ...)                                                \
	class Delegate##name : public Neptune::Delegate_Basic<__VA_ARGS__>     \
	{                                                                      \
	public:                                                                \
		Delegate##name() : Neptune::Delegate_Basic<__VA_ARGS__>() {}       \
		~Delegate##name() override = default;                              \
	}; 

}