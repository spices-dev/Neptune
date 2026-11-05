/**
* @file Tuple.h.
* @brief The Tuple Helper Functions Definitions and Implementation.
* @author VisualGMQ.
*/

#pragma once
#include "Core/Concept.h"

#include <tuple>

namespace Neptune::Container {

	namespace detail {

		/**
		* @brief Iter a tuple.
		* 
		* @tparam Idx Size of tuple.
		* @tparam Tuple tuple.
		* @tparam Function Iter Function.
		*/
		template<size_t... Idx, IsTuple Tuple, typename Function>
		void IterTuple(Tuple& tuple, Function&& fn, std::index_sequence<Idx...>)
		{
			(std::invoke(std::forward<Function>(fn), std::get<Idx>(tuple)), ...);
		}

		/**
		* @brief wrap_tuple base.
		* 
		* @tparam W Wrapper Template.
		* @tparam T Tuple.
		*/
		template <template <typename> typename W, typename T>
		struct wrap_tuple;
		
		/**
		* @brief wrap_tuple implement.
		* 
		* @tparam W Wrapper Template.
		* @tparam T Tuple.
		*/
		template <template <typename> typename W, typename... T>
		struct wrap_tuple<W, std::tuple<T...>> 
		{
			using type = std::tuple<W<T>...>;
		};
		
		
	}

	/**
	* @brief Iter a tuple.
	* 
	* @tparam Tuple tuple.
	* @tparam Function Iter Function.
	*/
	template<IsTuple Tuple, typename Function>
	void IterTuple(Tuple& tuple, Function&& fn)
	{
		detail::IterTuple(tuple, std::forward<Function>(fn), std::make_index_sequence<std::tuple_size_v<Tuple>>());
	}
	
	/**
	* @brief simplify of wrap_tuple::type.
	* 
	* @tparam W Wrapper Template.
	* @tparam T Tuple.
	*/
	template <template <typename> typename W, typename... T>
	using wrap_tuple_t = typename detail::wrap_tuple<W, T...>::type;
}