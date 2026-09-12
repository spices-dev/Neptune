/**
* @file Tree.hpp.
* @brief The Tree Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/Concept.h"

#include <memory>
#include <queue>
#include <shared_mutex>

namespace Neptune::Container {

    /**
    * @brief simple tree.
    * 
    * @tparam T specific stored type.
    * 
    * @note thread safe.
    */
    template<typename T>
    class Tree
    {
    public:

        /**
        * @brief Constructor Function.
        */
        Tree() : m_Data{} {}
        
        /**
        * @brief Constructor Function.
        *
        * @param[in] args T construct params.
        */
        template<typename ...Args>
        explicit Tree(std::in_place_t, Args&&... args)
            : m_Data{ std::forward<Args>(args)... }
        {}

        /**
        * @brief Destructor Function.
        */
        virtual ~Tree() = default;

        /**
        * @brief Add a child to this tree.
        * 
        * @param[in] args T construct params.
        * 
        * @return Returns child.
        */
        template<typename ...Args>
        Tree* AddChild(Args&&... args)
        {
            std::unique_lock lock(m_Mutex);
            
            m_Child.push_back(CreateUP<Tree>(std::in_place, std::forward<Args>(args)...));

            return m_Child.back().get();
        }

        /**
        * @brief Visit this data.
        *
        * @param[in] fn Visitor.
        * @param[in] args Visitor params.
        */
        template<typename F, typename ...Args>
        void View(F&& fn, Args&&...  args) const
        {
            std::shared_lock lock(m_Mutex);
            
            std::invoke(std::forward<F>(fn), m_Data, std::forward<Args>(args)...);
        }
        
        /**
        * @brief Visit child with DSF.
        *
        * @param[in] fn Visitor.
        * @param[in] args Visitor params.
        */
        template<typename F, typename ...Args>
        void ViewDSF(F&& fn, Args&&...  args) const
        {
            auto visitor = [&]<typename T0, typename T1>(T0&& data, T1&& depth) {
                
                return std::invoke(std::forward<F>(fn), std::forward<T0>(data), std::forward<T1>(depth), std::forward<Args>(args)...);
            };
            
            ViewDSFImpl(visitor, 0);
        }

        /**
        * @brief Visit child with WSF.
        *
        * @param[in] fn Visitor.
        * @param[in] args Visitor params.
        */
        template<typename F, typename ...Args>
        void ViewWSF(F&& fn, Args&&...  args) const
        {
            auto visitor = [&]<typename T0, typename T1>(T0&& data, T1&& depth) {
                
                return std::invoke(std::forward<F>(fn), std::forward<T0>(data), std::forward<T1>(depth), std::forward<Args>(args)...);
            };
            
            ViewWSFImpl(visitor);
        }

        /**
        * @brief Set this node data.
        * 
        * @param[in] data The data.
        */
        void SetData(const T& data)
        {
            std::unique_lock lock(m_Mutex);
            
            m_Data = data;
        }

        /**
        * @brief Get this node data.
        *
        * @return Returns this node data.
        */
        [[nodiscard]] T GetData() const
        {
            std::shared_lock lock(m_Mutex);
            
            return m_Data;
        }

    private:

        /**
        * @brief Visit child with DSF Implementation.
        *
        * @param[in] fn Visitor.
        * @param[in] depth Visitor depth.
        *
        * @return Returns true if it needs to block.
        */
        template<typename F>
        requires std::is_same_v<std::invoke_result_t<F, T, uint32_t>, bool>
        bool ViewDSFImpl(F&& fn, uint32_t depth) const;

        /**
        * @brief Visit child with WSF Implementation.
        *
        * @param[in] fn Visitor.
        *
        * @return Returns true if it needs to block.
        */
        template<typename F>
        requires std::is_same_v<std::invoke_result_t<F, T, uint32_t>, bool>
        bool ViewWSFImpl(F&& fn) const;

    private:
        
        std::vector<UP<Tree>> m_Child {};               // @brief Children node.
        T m_Data;                                       // @brief This node stored data.
        mutable std::shared_mutex m_Mutex;              // @brief Mutex.

    };

    template <typename T>
    template <typename F>
    requires std::is_same_v<std::invoke_result_t<F, T, uint32_t>, bool>
    bool Tree<T>::ViewDSFImpl(F&& fn, uint32_t depth) const
    {
        T data;
        std::vector<Tree*> children;
        
        {
            std::shared_lock lock(m_Mutex);

            data = m_Data;

            children.reserve(m_Child.size());
            
            for (auto& child : m_Child)
            {
                children.push_back(child.get());
            }
        }
        
        if (std::invoke(std::forward<F>(fn), data, depth))
        {
            return true;
        }
        
        for (auto& child : children)
        {
            if (child->ViewDSFImpl(std::forward<F>(fn), depth + 1))
            {
                return true;
            }
        }

        return false;
    }

    template <typename T>
    template <typename F>
    requires std::is_same_v<std::invoke_result_t<F, T, uint32_t>, bool>
    bool Tree<T>::ViewWSFImpl(F&& fn) const
    {
        std::queue<std::pair<const Tree*, uint32_t>> queue;

        queue.push({ this, 0 });

        while (!queue.empty())
        {
            auto [ node, depth ] = queue.front();
            queue.pop();      
            
            T data;
            std::vector<Tree*> children;
            
            {
                std::shared_lock lock(node->m_Mutex);

                data = node->m_Data;

                children.reserve(node->m_Child.size());
                
                for (auto& child : node->m_Child)
                {
                    children.push_back(child.get());
                }
            }
            
            if (std::invoke(std::forward<F>(fn), data, depth))
            {
                return true;
            }
            
            for (auto& child : children)
            {
                queue.push({ child, depth + 1 });
            }
        }
        
        return false;
    }
}
