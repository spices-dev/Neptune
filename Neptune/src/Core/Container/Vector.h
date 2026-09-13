/**
* @file Vector.h.
* @brief The Vector Class Definitions and Implementation.
* @author Spices.
*/

#pragma once

#include <cstdlib>
#include <memory>
#include <utility>

namespace Neptune::Container {

	/**
	* @brief This Class is similar to std::vector
	* Used In:
	* MemoryPool.
	* 
	* @note Not thread safe.
	*/
	template<typename T>
	class Vector
	{
	public:
		
		NONE_COPY(Vector)
		
		static const T null;
		
	public:

		/**
		* @brief Constructor Function.
		*/
		Vector() = default;

		/**
		* @brief Destructor Function.
		*/
		virtual ~Vector();

		/**
		* @brief Move Constructor Function.
		* 
		* @param[in] other Vector.
		*/
		Vector(Vector&& other) noexcept
			: m_Begin(other.m_Begin)
			, m_End(other.m_End)
			, m_UseCount(other.m_UseCount)
			, m_SpareCount(other.m_SpareCount)
			, m_ExpandRate(other.m_ExpandRate)
		{
			other.m_Begin      = nullptr;
			other.m_End        = nullptr;
			other.m_UseCount   = 0;
			other.m_SpareCount = 0;
		}
		
		/**
		* @brief Move Assignment Operation.
		*
		* @param[in] other Vector.
		*/
		Vector& operator=(Vector&& other) noexcept
		{
			if (this == &other) return *this;
			
			for (size_t i = 0; i < m_UseCount; ++i)
			{
				std::destroy_at(&m_Begin[i]);
			}
			
			free(m_Begin);

			m_Begin      = other.m_Begin;
			m_End        = other.m_End;
			m_UseCount   = other.m_UseCount;
			m_SpareCount = other.m_SpareCount;
			m_ExpandRate = other.m_ExpandRate;

			other.m_Begin      = nullptr;
			other.m_End        = nullptr;
			other.m_UseCount   = 0;
			other.m_SpareCount = 0;

			return *this;
		}
		
		/**
		* @brief Get vector Begin Pointer.
		* 
		* @return Return vector Begin Pointer.
		*/
		const T* Begin() const { return m_Begin; }

		/**
		* @brief Get vector size.
		* 
		* @return Returns vector size.
		*/
		size_t Size() const { return m_UseCount; }

		/**
		* @brief Determine if vector is empty.
		* 
		* @return Returns true if empty.
		*/
		bool Empty() const { return m_UseCount == 0; }

		/**
		* @brief Push an element in the end of vector.
		* 
		* @param[in] element .
		*/
		void PushBack(const T& element);

		/**
		* @brief Get element by index.
		* 
		* @param[in] index .
		* 
		* @return Returns element.
		*/
		const T& Get(size_t index) const;

	private:
		
		T*     m_Begin      = nullptr;      // @brief Vector Begin Pointer.
		T*     m_End        = nullptr;      // @brief Vector End Pointer.
		size_t m_UseCount   = 0;            // @brief vector used size.
		size_t m_SpareCount = 0;            // @brief vector spare count.
		size_t m_ExpandRate = 2;            // @brief Vector expand rate.
	};

	template<typename T>
	const T Vector<T>::null = {};

	template<typename T>
	inline Vector<T>::~Vector()
	{
		if (m_UseCount == 0) return;
		
		for (size_t i = 0; i < m_UseCount; ++i)
		{
			std::destroy_at(&m_Begin[i]);
		}

		free(m_Begin);
	}

	template<typename T>
	inline void Vector<T>::PushBack(const T& element)
	{
		if (m_SpareCount == 0)
		{
			const size_t oldCount       = m_UseCount;
			const size_t newCapacity    = oldCount == 0 ? m_ExpandRate : oldCount * m_ExpandRate;
			const size_t newBytes       = sizeof(T) * newCapacity;

			T* om       = m_Begin;
			T* newBegin = static_cast<T*>(malloc(newBytes));

			for (size_t i = 0; i < oldCount; ++i)
			{
				std::construct_at(&newBegin[i], std::move(om[i]));

				std::destroy_at(&om[i]);
			}

			free(om);

			m_Begin       = newBegin;
			m_End         = m_Begin + oldCount;
			m_SpareCount  = newCapacity - oldCount;
		}

		std::construct_at(m_End, element);

		++m_UseCount;
		--m_SpareCount;
		++m_End;
	}

	template<typename T>
	inline const T& Vector<T>::Get(size_t index) const
	{
		if (m_UseCount <= index) return null;

		return m_Begin[index];
	}
}