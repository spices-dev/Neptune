/**
* @file TimeLine.h.
* @brief The TimeLine Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Backend/Direct3D12/Unit/Fence.h"

namespace Neptune::Direct3D12 {

	using IGraphicTimeLine     = IInfrastructure<class TimeLine, EInfrastructure::GraphicTimeLine>;
	using IComputeTimeLine     = IInfrastructure<class TimeLine, EInfrastructure::ComputeTimeLine>;

	/**
	* @brief Direct3D12::TimeLine Class.
	* This class defines the Direct3D12::TimeLine behaves.
	*/
	class TimeLine : public Infrastructure
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		* @param[in] count Fence count.
		*/
		TimeLine(Context& context, EInfrastructure e, uint32_t count = 1);

		/**
		* @brief Destructor Function.
		*/
		~TimeLine() override = default;

		/**
		* @brief Get Unit Handle.
		*
		* @param[in] id Fence id.
		* 
		* @return Returns Unit Handle.
		*/
		const Unit::Fence::Handle& Handle(uint32_t id = 0) const { return m_Fences[id % m_Fences.size()]->GetHandle(); }

		/**
		* @brief Get Unit Handle Interface.
		*
		* @param[in] id Fence id.
		* 
		* @return Returns Unit Handle Interface.
		*/
		const SP<Unit::Fence>& IHandle(uint32_t id = 0) const { return m_Fences[id % m_Fences.size()]; }
		
		/**
		* @brief Fence wait idle.
		* 
		* @param[in] frameId Frame Id.
		*/
		void Wait(uint32_t frameId) const;

	private:

		/**
		* @brief Create Fence.
		* 
		* @param[in] count Fence count.
		*/
		void Create(uint32_t count);

	private:

		std::vector<SP<Unit::Fence>> m_Fences; // @brief Container of this Fence.

	};
	
}

#endif