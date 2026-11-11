/**
* @file RHI.h.
* @brief The RHI Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Enum.h"
#include "Core/Container/Empty.h"

namespace Neptune::RHI {

	/**
	* @brief RHIImplEmpty
	*/
	using RHIImplEmpty = Container::Empty;

	/**
	* @brief RHIDelegate
	*/
	struct RHIDelegate
	{
		/**
		* @brief RHIDelegate Scope
		*/
		struct Scope
		{
			/**
			* @brief Constructor Function.
			*/
			Scope() = default;
			
			/**
			* @brief Constructor Function.
			* 
			* @param[in] delegate RHIDelegate.
			*/
			Scope(RHIDelegate* delegate);
			
			/**
			* @brief Destructor Function.
			*/
			~Scope();
			
			NONE_COPY(Scope)
			
			/**
			* @brief Move Constructor Function.
			*
			* @param[in] other Scope.
			*/
			Scope(Scope&& other) noexcept;
			
			/**
			* @brief Move Assignment Operation.
			*/
			Scope& operator=(Scope&&) = delete;
			
			/**
			* @brief Operation () override.
			* 
			* @return Returns in scope RHIDelegate.
			*/
			RHIDelegate* operator()() const;
			
		private:
			
			RHIDelegate* m_Prev  = nullptr;  // @brief Previous RHIDelegate.
			bool         m_Owned = false;    // @brief Owned RHIDelegate.
		};
		
		/**
		* @brief Constructor Function.
		*/
		RHIDelegate();
		
		/**
		* @brief Destructor Function.
		*/
		virtual ~RHIDelegate();
		
		/**
		* @brief RHI Creator Functor.
		* 
		* @param[in] e ERHI.
		* @param[in] payload payload of rhi.
		*/
		virtual UP<RHIImplEmpty> CreateRHI(ERHI e, void* payload) const = 0;

	protected:

		Scope m_Scope;  // @brief Delegate Scope.
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
		class Impl : public RHIImplEmpty {};

	public:

		/**
		* @brief Constructor Function.
		* 
		* @param[in] payload RHI Construct payload.
		*/
		explicit RHI(void* payload = nullptr)
			: m_Impl(ConstructRHI(payload))
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

	private:
		
		/**
		* @brief Construct RHI.
		* 
		* @param[in] payload RHI Construct payload.
		*/
		Impl* ConstructRHI(void* payload)
		{
			if (auto* delegate = RHIDelegate::Scope()())
			{
				if (auto rhi = delegate->CreateRHI(E, payload))
				{
					return static_cast<Impl*>(rhi.release());
				}
				
				NEPTUNE_ASSERT(false)
			}
			
			NEPTUNE_LOG_CORE(E) << "RHIDelegate not in scope.";
			
			NEPTUNE_ASSERT(false)
		}
		
	protected:

		UP<Impl> m_Impl = nullptr;     // @brief RHI Implement.
	};
}
