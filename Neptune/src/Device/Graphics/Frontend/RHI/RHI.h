/**
* @file RHI.h.
* @brief The RHI Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/Container/Empty.h"
#include "Enum.h"

#include <functional>
#include <any>

namespace Neptune::RHI {

	using RHIImplEmpty = Container::Empty;
	
	/**
	* @brief Delegate of RHI.
	*/
	struct RHIDelegate
	{
		/**
		* @brief RHI Creator Functor.
		* 
		* @param[in] e ERHI.
		* @param[in] payload payload of rhi.
		*/
		using Creator = std::function<UP<RHIImplEmpty>(ERHI e, void* payload)>;

		/**
		* @brief Set Creator Functor.
		*
		* @param[in] fn Creator.
		*/
		static void SetCreator(const Creator& fn);

		/**
		* @brief Get Creator Functor.
		*
		* @return Returns Creator Functor.
		*/
		static const Creator& GetCreator();
	};

	/**
	* @brief Template of RHI Class.
	*/
	template<ERHI E>
	class RHI
	{
	public:

		/**
		* @brief Template of RHI Implement Class.
		*/
		class Impl : public RHIImplEmpty
		{	
		public:

			/**
			* @brief Constructor Function.
			*/
			Impl() = default;

			/**
			* @brief Destructor Function.
			*/
			virtual ~Impl() = default;
		};

	public:

		/**
		* @brief Constructor Function.
		* 
		* @param[in] payload RHI Construct payload.
		*/
		explicit RHI(void* payload = nullptr)
			: m_Impl(static_cast<Impl*>(std::invoke(RHIDelegate::GetCreator(), E, payload).release()))
		{}

		/**
		* @brief Destructor Function.
		*/
		virtual ~RHI() = default;

		/**
		* @brief Get RHI Implement.
		* 
		* @return Returns RHI Implement.
		*/
		template<typename T>
		T* GetRHIImpl() const
		{
			NEPTUNE_PROFILE_ZONE

			return static_cast<T*>(m_Impl.get());
		}

	protected:

		UP<Impl> m_Impl = nullptr;     // @brief RHI Implement.
	};
}