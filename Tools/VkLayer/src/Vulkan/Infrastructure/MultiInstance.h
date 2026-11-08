/**
* @file MultiInstance.h.
* @brief The MultiInstance Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Vulkan/Core.h"
#include "Core/Core.h"
#include "Infrastructure.h"

#include <unordered_map>
#include <shared_mutex>
#include <ranges>

namespace Neptune::Vulkan {
    
    /**
    * @brief MultiInstance.
    * 
    * @tparam Id Instance Id.
    * @tparam T Instance.
    */
    template<typename Id, typename T>
    class MultiInstance : public Infrastructure
    {
    public:
        
        /**
        * @brief Constructor Function.
        */
        MultiInstance() = default;
        
        /**
        * @brief Destructor Function.
        */
        ~MultiInstance() override = default;
        
        /**
        * @brief Registry Instance.
        *
        * @param[in] t Instance.
        */
        template<typename Id_, typename T_>
        requires std::is_same_v<std::decay_t<Id_>, Id> && std::is_same_v<std::decay_t<T_>, UP<T>>
        void Registry(Id_&& id, T_&& t);
        
        /**
        * @brief Unregister Instance.
        *
        * @param[in] id Instance id.
        */
        template<typename Id_>
        void UnRegistry(Id_&& id);
        
        /**
        * @brief Get Instance.
        * 
        * @param[in] id Instance id.
        * 
        * @return Returns Instance.
        */
        template<typename Id_>
        const T& Get(Id_&& id) const;
        
        /**
        * @brief Is registry Instance.
        *
        * @param[in] id Instance id.
        * 
        * @return Returns true if registry.
        */
        template<typename Id_>
        bool Has(Id_&& id) const;
        
        /**
        * @brief If Instances is empty.
        * 
        * @return Returns true if empty.
        */
        bool Empty() const;
        
        /**
        * @brief View all Instances.
        * 
        * @param[in] fn Iter Functor.
        */
        template<typename F>
        void View(F&& fn) const;
        
    private:
        
        std::unordered_map<Id, UP<T>> m_Instances;  // @brief Container of Instance.
        mutable std::shared_mutex m_Mutex;          // @brief this mutex.
    };

    template <typename Id, typename T>
    template <typename Id_, typename T_>
    requires std::is_same_v<std::decay_t<Id_>, Id> && std::is_same_v<std::decay_t<T_>, UP<T>>
    void MultiInstance<Id, T>::Registry(Id_&& id, T_&& t)
    {
        std::unique_lock lock(m_Mutex);
        
        m_Instances.emplace(std::forward<Id_>(id), std::forward<T_>(t));
    }

    template <typename Id, typename T>
    template <typename Id_>
    void MultiInstance<Id, T>::UnRegistry(Id_&& id)
    {
        std::unique_lock lock(m_Mutex);
        
        m_Instances.erase(m_Instances.find(std::forward<Id_>(id)));
    }

    template <typename Id, typename T>
    template <typename Id_>
    const T& MultiInstance<Id, T>::Get(Id_&& id) const
    {
        std::shared_lock lock(m_Mutex);
        
        return *m_Instances.at(std::forward<Id_>(id));
    }

    template <typename Id, typename T>
    template <typename Id_>
    bool MultiInstance<Id, T>::Has(Id_&& id) const
    {
        std::shared_lock lock(m_Mutex);
        
        return m_Instances.contains(std::forward<Id_>(id));
    }

    template <typename Id, typename T>
    bool MultiInstance<Id, T>::Empty() const
    {
        std::shared_lock lock(m_Mutex);
        
        return m_Instances.empty();
    }

    template <typename Id, typename T>
    template <typename F>
    void MultiInstance<Id, T>::View(F&& fn) const
    {
        std::unique_lock lock(m_Mutex);
        
        for (const auto& v : m_Instances | std::views::values)
        {
            std::invoke(std::forward<F>(fn), v);
        }
    }
}
