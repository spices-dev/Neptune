/**
* @file RHI.cpp.
* @brief The RHIDelegate Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "RHI.h"

namespace Neptune::RHI {

	namespace {

		thread_local RHIDelegate* s_Delegate;   // @brief Thread RHIDelegate.
	}
	
	RHIDelegate::Scope::Scope(RHIDelegate* delegate)
		: m_Prev(s_Delegate)
	{
		s_Delegate = delegate;
	}

	RHIDelegate::Scope::~Scope()
	{
		if (m_Prev)
		{
			s_Delegate = m_Prev;
		}
	}

	RHIDelegate* RHIDelegate::Scope::operator()() const
	{
		return s_Delegate;
	}
}