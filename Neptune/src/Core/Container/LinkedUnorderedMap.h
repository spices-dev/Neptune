/**
* @file LinkedUnorderedMap.h.
* @brief The LinkedUnorderedMap Class Definitions and Implementation.
* @author Spices.
*/

#pragma once

#include "Core/Core.h"

#include <unordered_map>
#include <shared_mutex>
#include <list>
#include <functional>

namespace Neptune::Container {

	/**
	* @brief The container combines hashmap and list together.
	* Used in the case that we want iter a hashmap in order.
	* 
	*  @note thread safe.
	*/
	template<typename K, typename V>
	class LinkedUnorderedMap
	{
	public:
		
		static const K kNull;
		static const V vNull;

	public:

		/**
		* @brief Constructor Function.
		*/
		LinkedUnorderedMap() = default;

		/**
		* @brief Destructor Function.
		*/
		virtual ~LinkedUnorderedMap() = default;

		/**
		* @brief Clear this container's data.
		*/
		void Clear();

		/**
		* @brief The container's element size.
		* 
		* @return Returns the size of the container.
		*/
		size_t Size() const { return m_Size.load(); }

		/**
		* @brief Is container empty.
		* 
		* @return Returns true if empty.
		*/
		bool Empty() const { return m_Size.load() == 0; }
		
		/**
		* @brief Add an element to this container.
		* 
		* @param[in] key K the key.
		* @param[in] value V the value.
		*/
		void PushBack(const K& key, const V& value);

		/**
		* @brief Find the value by key.
		* 
		* @param[in] key K the key.
		* 
		* @return Returns the value that founded.
		*/
		const V& At(const K& key) const;

		/**
		* @brief Determine whether the key is in the container.
		* 
		* @param[in] key K the key.
		* 
		* @return Returns true if it has key inside the container.
		*/
		bool Contains(const K& key) const;

		/**
		* @brief Remove an element inside the container if founded by key.
		* 
		* @param[in] key K the key.
		* 
		* @return Returns true if succeeded.
		*/
		bool Erase(const K& key);

		/**
		* @brief Iter the container in order.
		* 
		* @param[in] fn The function of how to iter the container.
		*/
		template<typename F>
		void ForEach(F&& fn) const;
		
		/**
		* @brief Get the previous element by the key.
		* 
		* @param[in] key the key.
		* 
		* @return Returns the previous element.
		* 
		* @note It's slow, so do not use it unnecessary. 
		*/
		const V& Prev(const K& key) const;

		/**
		* @brief Get the next element by the key.
		* 
		* @param[in] key the key.
		* 
		* @return Returns the next element.
		* 
		* @note It's slow, so do not use it unnecessary. 
		*/
		const V& Next(const K& key) const;

		/**
		* @brief Get the first element of this container.
		* 
		* @return Returns the first element found.
		*/
		const V& Begin() const;

		/**
		* @brief Get the end element of this container.
		* 
		* @return Returns the end element found.
		*/
		const V& End() const;

		/**
		* @brief Get the end key of this container.
		* 
		* @return Returns the end key found.
		*/
		const K& EndK() const;
		
		/**
		* @brief Get Keys.
		* 
		* @return Returns Keys.
		*/
		std::vector<K> Keys() const;
		
	private:
		
		std::list<K> m_Keys;                 // @brief The container keeps iter in order.
		std::unordered_map<K, V> m_Map;      // @brief The container keeps quick search.
		mutable std::shared_mutex m_Mutex;   // @brief Mutex for this container.
		std::atomic_int m_Size = 0;          // @brief This container size.
	};

	template<typename K, typename V>
	const K LinkedUnorderedMap<K, V>::kNull = {};

	template<typename K, typename V>
	const V LinkedUnorderedMap<K, V>::vNull = {};

	template<typename K, typename V>
	inline void LinkedUnorderedMap<K, V>::Clear()
	{
		std::unique_lock lock(m_Mutex);

		m_Keys.clear();
		m_Map.clear();
		m_Size = 0;
	}

	template<typename K, typename V>
	inline void LinkedUnorderedMap<K, V>::PushBack(const K& key, const V& value)
	{
		std::unique_lock lock(m_Mutex);

		if (!m_Map.contains(key))
		{
			m_Keys.push_back(key);

			++m_Size;
		}

		m_Map[key] = value;
	}

	template<typename K, typename V>
	inline const V& LinkedUnorderedMap<K, V>::At(const K& key) const
	{
		std::shared_lock lock(m_Mutex);

		if (!m_Map.contains(key)) return vNull;
		
		return m_Map.at(key);
	}

	template<typename K, typename V>
	inline bool LinkedUnorderedMap<K, V>::Contains(const K& key) const
	{
		std::shared_lock lock(m_Mutex);

		return m_Map.contains(key);
	}

	template<typename K, typename V>
	inline bool LinkedUnorderedMap<K, V>::Erase(const K& key)
	{
		std::unique_lock lock(m_Mutex);

		if (!m_Map.contains(key)) return false;
		
		m_Keys.remove(key);
		
		m_Map.erase(m_Map.find(key));

		--m_Size;
		
		return true;
	}

	template<typename K, typename V>
	template<typename F>
	inline void LinkedUnorderedMap<K, V>::ForEach(F&& fn) const
	{
		std::shared_lock lock(m_Mutex);

		for (const K& key : m_Keys)
		{
			/**
			* @brief The function defines how to iter.
			* 
			* @param[in] key K the key.
			* @param[in] value V the value.
			* 
			* @return Retunrs True if want break this for loop.
			*/
			if(std::invoke(std::forward<F>(fn), key, m_Map.at(key))) break;
		}
	}

	template<typename K, typename V>
	inline const V& LinkedUnorderedMap<K, V>::Prev(const K& key) const
	{
		std::shared_lock lock(m_Mutex);
		
		if (m_Keys.empty()) return vNull;
		
		for (auto it = m_Keys.begin(); it != m_Keys.end(); ++it)
		{
			if (*it == key)
			{
				if (it == m_Keys.begin()) return vNull;
				
				return m_Map.at(*std::prev(it));
			}
		}

		return vNull;
	}

	template<typename K, typename V>
	inline const V& LinkedUnorderedMap<K, V>::Next(const K& key) const
	{
		std::shared_lock lock(m_Mutex);
		
		if (m_Keys.empty()) return vNull;
		
		for (auto it = m_Keys.begin(); it != m_Keys.end(); ++it)
		{
			if (*it == key)
			{
				auto next = std::next(it);

				if (next == m_Keys.end()) return vNull;

				return m_Map.at(*next);
			}
		}

		return vNull;
	}

	template<typename K, typename V>
	const V& LinkedUnorderedMap<K, V>::Begin() const
	{
		std::shared_lock lock(m_Mutex);

		if (m_Keys.empty()) return vNull;

		return m_Map.at(m_Keys.front());
	}

	template<typename K, typename V>
	const V& LinkedUnorderedMap<K, V>::End() const
	{
		std::shared_lock lock(m_Mutex);

		if (m_Keys.empty()) return vNull;

		return m_Map.at(m_Keys.back());
	}

	template<typename K, typename V>
	const K& LinkedUnorderedMap<K, V>::EndK() const
	{
		std::shared_lock lock(m_Mutex);

		if (m_Keys.empty()) return kNull;

		return m_Keys.back();
	}

	template <typename K, typename V>
	std::vector<K> LinkedUnorderedMap<K, V>::Keys() const
	{
		std::shared_lock lock(m_Mutex);
		
		return { m_Keys.begin(), m_Keys.end() };
	}
}
