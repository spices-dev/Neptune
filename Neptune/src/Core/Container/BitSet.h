/**
* @file BitSet.hpp.
* @brief The BitSet Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/Concept.h"

#include <bitset>
#include <shared_mutex>
#include <mutex>

namespace Neptune::Container {

    /**
    * @brief Bit Set.
    * 
    * @tparam T specific stored type.
    * 
    * @note thread safe.
    */
    template<IsEnum T>
    class BitSet
    {
    public:
        
        using TSize = std::underlying_type_t<T>; // @brief Size Type of T.
        
    public:

        /**
        * @brief Constructor Function.
        */
        BitSet() = default;

        /**
        * @brief Constructor Function.
        */
        explicit BitSet(const T& t)
        {
            Set(t, true);
        }
        
        /**
        * @brief Destructor Function.
        */
        virtual ~BitSet() = default;

        /**
        * @brief Copy Constructor Function.
        *
        * @param[in] other BitSet.
        */
        BitSet(const BitSet& other)
        {
            std::shared_lock lock(other.m_Mutex);

            m_Bits = other.m_Bits;
        }

        /**
        * @brief Copy Assignment Operation.
        *
        * @param[in] other BitSet.
        */
        BitSet& operator=(const BitSet& other)
        {
            if (this == &other) return *this;
            
            if (this < &other)
            {
                std::unique_lock lock1(m_Mutex);
                
                std::unique_lock lock2(other.m_Mutex);

                m_Bits = other.m_Bits;
            }
            else
            {
                std::unique_lock lock2(other.m_Mutex);

                std::unique_lock lock1(m_Mutex);
                
                m_Bits = other.m_Bits;
            }
        }

        /**
        * @brief Move Constructor Function.
        *
        * @param[in] other BitSet.
        */
        BitSet(BitSet&& other) noexcept
        {
            std::unique_lock lock(other.m_Mutex);

            m_Bits = std::move(other.m_Bits);
        }

        /**
        * @brief Move Assignment Operation.
        *
        * @param[in] other BitSet.
        */
        BitSet& operator=(BitSet&& other) noexcept
        {
            if (this == &other) return *this;

            if (this < &other)
            {
                std::unique_lock lock1(m_Mutex);
                
                std::unique_lock lock2(other.m_Mutex);
                
                m_Bits = std::move(other.m_Bits);
            }
            else
            {
                std::unique_lock lock2(other.m_Mutex);
                
                std::unique_lock lock1(m_Mutex);

                m_Bits = std::move(other.m_Bits);
            }

            return *this;
        }

        /**
        * @brief | Bit Operation.
        *
        * @param[in] other BitSet.
        *
        * @return Returns new BitSet.
        */
        BitSet operator|(const BitSet& other) const
        {
            BitSet result;

            if (this == &other)
            {
                std::shared_lock lock(m_Mutex);
                
                result.m_Bits = m_Bits;
                
                return result;
            }

            if (this < &other)
            {
                std::shared_lock lock1(m_Mutex);
                
                std::shared_lock lock2(other.m_Mutex);
                
                result.m_Bits = m_Bits | other.m_Bits;
            }
            else
            {
                std::shared_lock lock2(other.m_Mutex);
                
                std::shared_lock lock1(m_Mutex);
                
                result.m_Bits = m_Bits | other.m_Bits;
            }

            return result;
        }

        /**
        * @brief & Bit Operation.
        *
        * @param[in] other BitSet.
        *
        * @return Returns new BitSet.
        */
        BitSet operator&(const BitSet& other) const
        {
            BitSet result;

            if (this == &other)
            {
                std::shared_lock lock(m_Mutex);
                
                result.m_Bits = m_Bits;
                
                return result;
            }

            if (this < &other)
            {
                std::shared_lock lock1(m_Mutex);
                
                std::shared_lock lock2(other.m_Mutex);
                
                result.m_Bits = m_Bits & other.m_Bits;
            }
            else
            {
                std::shared_lock lock2(other.m_Mutex);
                
                std::shared_lock lock1(m_Mutex);
                
                result.m_Bits = m_Bits & other.m_Bits;
            }

            return result;
        }

        /**
        * @brief |= Bit Operation.
        *
        * @param[in] other BitSet.
        *
        * @return Returns this.
        */
        BitSet& operator|=(const BitSet& other)
        {
            if (this == &other) return *this;

            if (this < &other)
            {
                std::unique_lock lock1(m_Mutex);
                
                std::shared_lock lock2(other.m_Mutex);
                
                m_Bits |= other.m_Bits;
            }
            else
            {
                std::shared_lock lock2(other.m_Mutex);
                
                std::unique_lock lock1(m_Mutex);
                
                m_Bits |= other.m_Bits;
            }

            return *this;
        }

        /**
        * @brief ^= Bit Operation.
        *
        * @param[in] other BitSet.
        *
        * @return Returns this.
        */
        BitSet& operator^=(const BitSet& other)
        {
            if (this == &other)
            {
                std::unique_lock lock(m_Mutex);
                
                m_Bits ^= m_Bits;
                
                return *this;
            }

            if (this < &other)
            {
                std::unique_lock lock1(m_Mutex);
                
                std::shared_lock lock2(other.m_Mutex);
                
                m_Bits ^= other.m_Bits;
            }
            else
            {
                std::shared_lock lock2(other.m_Mutex);
                
                std::unique_lock lock1(m_Mutex);
                
                m_Bits ^= other.m_Bits;
            }

            return *this;
        }
        
        /**
        * @brief &= Bit Operation.
        *
        * @param[in] other BitSet.
        *
        * @return Returns this.
        */
        BitSet& operator&=(const BitSet& other)
        {
            if (this == &other) return *this;

            if (this < &other)
            {
                std::unique_lock lock1(m_Mutex);
                
                std::shared_lock lock2(other.m_Mutex);
                
                m_Bits &= other.m_Bits;
            }
            else
            {
                std::shared_lock lock2(other.m_Mutex);
                
                std::unique_lock lock1(m_Mutex);
                
                m_Bits &= other.m_Bits;
            }

            return *this;
        }

        /**
        * @brief == Operation.
        *
        * @param[in] other BitSet.
        *
        * @return Returns true if equal.
        */
        bool operator==(const BitSet& other) const
        {
            if (this == &other) return true;

            if (this < &other)
            {
                std::shared_lock lock1(m_Mutex);
                
                std::shared_lock lock2(other.m_Mutex);
                
                return m_Bits == other.m_Bits;
            }
            else
            {
                std::shared_lock lock2(other.m_Mutex);
                
                std::shared_lock lock1(m_Mutex);
                
                return m_Bits == other.m_Bits;
            }
        }

        /**
        * @brief != Operation.
        *
        * @param[in] other BitSet.
        *
        * @return Returns true if not equal.
        */
        bool operator!=(const BitSet& other) const
        {
            return !(*this == other);
        }

        /**
        * @brief To TSize.
        *
        * @return Returns TSize.
        */
        explicit operator TSize() const
        {
            std::shared_lock lock(m_Mutex);

            return static_cast<TSize>(m_Bits.to_ulong());
        }

        /**
        * @brief Set bit with value.
        *
        * @param[in] bit Bit item.
        * @param[in] value Bit value.
        * 
        * @return Returns true if succeeded.
        */
        bool Set(T bit, bool value)
        {
            if (bit > T::Count) return false;

            if (bit == T::Count)
            {
                Reset();

                if (value)
                {
                    Flip();
                }
                
                return true;
            }

            std::unique_lock lock(m_Mutex);

            m_Bits.set(static_cast<size_t>(static_cast<TSize>(bit)), value);

            return true;
        }

        /**
        * @brief Test bit.
        *
        * @param[in] bit Bit item.
        *
        * @return Returns bit value or failed.
        */
        bool Test(T bit) const
        {
            if (bit > T::Count) return false;

            if (bit == T::Count)
            {
                return !None();
            }

            std::shared_lock lock(m_Mutex);

            return m_Bits.test(static_cast<size_t>(static_cast<TSize>(bit)));
        }

        /**
        * @brief Reset all bits.
        */
        void Reset()
        {
            std::unique_lock lock(m_Mutex);

            m_Bits.reset();
        }

        /**
        * @brief Reset bit.
        *
        * @param[in] bit Bit item.
        * 
        * @return Returns true if succeeded.
        */
        bool Reset(T bit)
        {
            if (bit > T::Count) return false;

            if (bit == T::Count)
            {
                Reset();
                
                return true; 
            }

            std::unique_lock lock(m_Mutex);

            m_Bits.reset(static_cast<size_t>(static_cast<TSize>(bit)));

            return true;
        }

        /**
        * @brief Flip all bits.
        */
        void Flip()
        {
            std::unique_lock lock(m_Mutex);

            m_Bits.flip();
        }

        /**
        * @brief Flip bit.
        *
        * @param[in] bit Bit item.
        * 
        * @return Returns true if succeeded.
        */
        bool Flip(T bit)
        {
            if (bit > T::Count) return false;

            if (bit == T::Count)
            {
                Flip();
                
                return true;
            }

            std::unique_lock lock(m_Mutex);

            m_Bits.flip(static_cast<size_t>(static_cast<TSize>(bit)));

            return true;
        }

        /**
        * @brief Is any bit set.
        *
        * @return Returns true if exist bit not set.
        */
        bool Any() const
        {
            std::shared_lock lock(m_Mutex);

            return m_Bits.any();
        }

        /**
        * @brief Is all bits not set.
        *
        * @return Returns true if all bits not set.
        */
        bool None() const
        {
            std::shared_lock lock(m_Mutex);

            return m_Bits.none();
        }
        
    private:
        
        std::bitset<static_cast<size_t>(T::Count)> m_Bits{};  // @brief Stored bitset.
        mutable std::shared_mutex m_Mutex;                    // @brief Mutex.

    };

}
