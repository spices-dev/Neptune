/**
* @file RHI.cpp.
* @brief The RHIDelegate Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "RHI.h"

namespace Neptune::RHI {

	namespace {

		thread_local RHIDelegate* s_TLSDelegate = nullptr;           // @brief Thread Local RHIDelegate.
		std::atomic<RHIDelegate*> s_Delegate    = { nullptr };  // @brief Global RHIDelegate.
	}
	
	RHIDelegate::Scope::Scope(RHIDelegate* delegate)
		: m_Prev(s_TLSDelegate)
		, m_Owned(true)
	{
		s_TLSDelegate = delegate;
	}

	RHIDelegate::Scope::~Scope()
	{
		if (m_Owned)
		{
			s_TLSDelegate = m_Prev;
		}
	}

	RHIDelegate::Scope::Scope(Scope&& other) noexcept
		: m_Prev(other.m_Prev)
		, m_Owned(other.m_Owned)
	{
		other.m_Owned = false;
	}

	RHIDelegate* RHIDelegate::Scope::operator()() const
	{
		return s_TLSDelegate ? s_TLSDelegate : s_Delegate.load(std::memory_order_acquire);
	}

	RHIDelegate::RHIDelegate()
		: m_Scope(this)
	{
		RHIDelegate* expected = nullptr;
		
		const auto result = s_Delegate.compare_exchange_strong(expected, this);
		
		NEPTUNE_ASSERT(result)
	}

	RHIDelegate::~RHIDelegate()
	{
		RHIDelegate* self = this;
		
		s_Delegate.compare_exchange_strong(self, nullptr);
	}
}