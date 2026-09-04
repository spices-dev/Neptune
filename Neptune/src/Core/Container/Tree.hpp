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
    */
    template<typename T>
    class Tree
    {
    public:

        /**
        * @brief Constructor Function.
        */
        Tree()
            : m_Data{}
        {}
        
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
            
            m_Child.push_back(std::make_unique<Tree>(std::in_place, std::forward<Args>(args)...));

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
        * @brief Visit child with DFS.
        *
        * @param[in] fn Visitor.
        * @param[in] args Visitor params.
        */
        template<typename F, typename ...Args>
        void ViewDFS(F&& fn, Args&&...  args) const
        {
            std::shared_lock lock(m_Mutex);
            
            auto visitor = [&]<typename T0, typename T1>(T0&& data, T1&& depth) {
                
                return std::invoke(std::forward<F>(fn), std::forward<T0>(data), std::forward<T1>(depth), std::forward<Args>(args)...);
            };
            
            ViewDFSImpl(visitor, 0);
        }

        /**
        * @brief Visit child with WSF.
        *
        * @param[in] fn Visitor.
        * @param[in] args Visitor params.
        */
        template<typename F, typename ...Args>
        void ViewWFS(F&& fn, Args&&...  args) const
        {
            std::shared_lock lock(m_Mutex);
            
            auto visitor = [&]<typename T0, typename T1>(T0&& data, T1&& depth) {
                
                return std::invoke(std::forward<F>(fn), std::forward<T0>(data), std::forward<T1>(depth), std::forward<Args>(args)...);
            };
            
            ViewWFSImpl(visitor);
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
        [[nodiscard]] const T& GetData() const { return m_Data; }

    private:

        /**
        * @brief Visit child with DFS Implementation.
        *
        * @param[in] fn Visitor.
        * @param[in] depth Visitor depth.
        *
        * @return Returns true if it needs to continue.
        */
        template<typename F>
        requires std::is_same_v<std::invoke_result_t<F, T, uint32_t>, bool>
        bool ViewDFSImpl(F&& fn, uint32_t depth) const;

        /**
        * @brief Visit child with WFS Implementation.
        *
        * @param[in] fn Visitor.
        *
        * @return Returns true if it needs to continue.
        */
        template<typename F>
        requires std::is_same_v<std::invoke_result_t<F, T, uint32_t>, bool>
        bool ViewWFSImpl(F&& fn) const;

    private:
        
        std::vector<std::unique_ptr<Tree>> m_Child {};  // @brief Children node.
        T m_Data;                                       // @brief This node stored data.
        mutable std::shared_mutex m_Mutex;              // @brief Mutex.

    };

    template <typename T>
    template <typename F>
    requires std::is_same_v<std::invoke_result_t<F, T, uint32_t>, bool>
    bool Tree<T>::ViewDFSImpl(F&& fn, uint32_t depth) const
    {
        if (!std::invoke(std::forward<F>(fn), m_Data, depth))
        {
            return false;
        }
        
        for (auto& child : m_Child)
        {
            if (!child->ViewDFSImpl(std::forward<F>(fn), depth + 1))
            {
                return false;
            }
        }

        return true;
    }

    template <typename T>
    template <typename F>
    requires std::is_same_v<std::invoke_result_t<F, T, uint32_t>, bool>
    bool Tree<T>::ViewWFSImpl(F&& fn) const
    {
        std::queue<std::pair<const Tree*, uint32_t>> queue;

        queue.push({ this, 0 });

        while (!queue.empty())
        {
            auto [ node, depth ] = queue.front();
            queue.pop();      
            
            if (!std::invoke(std::forward<F>(fn), node->m_Data, depth))
            {
                return false;
            }
            
            for (auto& child : node->m_Child)
            {
                queue.push({ child.get(), depth + 1 });
            }
        }
        
        return true;
    }
}
