/**
* @file BitSet.h.
* @brief The BitSet Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/Concept.h"

#include <atomic>
#include <type_traits>
#include <array>

namespace Neptune::Container {

    /**
    * @brief Bit Set.
    * 
    * @tparam T specific stored type.
    * 
    * @note thread safe.
    */
    template<IsNotEmptyEnum T>
    class BitSet
    {
    public:
        
        using TSize = std::underlying_type_t<T>; // @brief Size Type of T.
        
    private:

        using Word = std::uint64_t;

        static constexpr size_t kBitsPerWord = sizeof(Word) * 8;
        static constexpr size_t kBitCount    = static_cast<size_t>(T::Count);
        static constexpr size_t kWordCount   = (kBitCount + kBitsPerWord - 1) / kBitsPerWord;
        
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
        * @brief Constructor Function.
        * 
        * @param[in] bits Bits.
        */
        template<typename... Bits>
        requires (sizeof...(Bits) >= 1) && (IsSame<Bits, T> && ...)
        explicit BitSet(Bits... bits)
        {
            (Set(bits, true), ...);
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
            for (size_t i = 0; i < kWordCount; ++i)
            {
                m_Words[i].store(other.m_Words[i].load(std::memory_order_acquire), std::memory_order_relaxed);
            }
        }

        /**
        * @brief Copy Assignment Operation.
        *
        * @param[in] other BitSet.
        * 
        * @return Returns this.
        */
        BitSet& operator=(const BitSet& other)
        {
            if (this == &other) return *this;
            
            for (size_t i = 0; i < kWordCount; ++i)
            {
                m_Words[i].store(other.m_Words[i].load(std::memory_order_acquire), std::memory_order_relaxed);
            }

            return *this;
        }

        /**
        * @brief Move Constructor Function.
        *
        * @param[in] other BitSet.
        */
        BitSet(BitSet&& other) noexcept
            : BitSet(static_cast<const BitSet&>(other))
        {}

        /**
        * @brief Move Assignment Operation.
        *
        * @param[in] other BitSet.
        * 
        * @return Returns this.
        */
        BitSet& operator=(BitSet&& other) noexcept
        {
            return (*this = static_cast<const BitSet&>(other));
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

            for (size_t i = 0; i < kWordCount; ++i)
            {
                result.m_Words[i].store(m_Words[i].load(std::memory_order_acquire) | other.m_Words[i].load(std::memory_order_acquire),std::memory_order_relaxed);
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

            for (size_t i = 0; i < kWordCount; ++i)
            {
                result.m_Words[i].store(m_Words[i].load(std::memory_order_acquire) & other.m_Words[i].load(std::memory_order_acquire),std::memory_order_relaxed);
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
            for (size_t i = 0; i < kWordCount; ++i)
            {
                m_Words[i].fetch_or(other.m_Words[i].load(std::memory_order_acquire), std::memory_order_acq_rel);
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
            for (size_t i = 0; i < kWordCount; ++i)
            {
                m_Words[i].fetch_xor(other.m_Words[i].load(std::memory_order_acquire), std::memory_order_acq_rel);
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
            for (size_t i = 0; i < kWordCount; ++i)
            {
                m_Words[i].fetch_and(other.m_Words[i].load(std::memory_order_acquire), std::memory_order_acq_rel);
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
            for (size_t i = 0; i < kWordCount; ++i)
            {
                if (m_Words[i].load(std::memory_order_acquire) != other.m_Words[i].load(std::memory_order_acquire))
                {
                    return false;
                }
            }

            return true;
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
        requires (kWordCount == 1)
        {
            return static_cast<TSize>(m_Words[0].load(std::memory_order_acquire));
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
                value ? SetAll() : Reset();
                return true;
            }

            const size_t index      = static_cast<size_t>(static_cast<TSize>(bit));
            const size_t wordIndex  = index / kBitsPerWord;
            const Word   mask       = Word{1} << (index % kBitsPerWord);

            if (value)
            {
                m_Words[wordIndex].fetch_or(mask, std::memory_order_acq_rel);
            }
            else
            {
                m_Words[wordIndex].fetch_and(static_cast<Word>(~mask), std::memory_order_acq_rel);
            }

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

            const size_t index     = static_cast<size_t>(static_cast<TSize>(bit));
            const size_t wordIndex = index / kBitsPerWord;
            const Word   mask      = Word{1} << (index % kBitsPerWord);

            return (m_Words[wordIndex].load(std::memory_order_acquire) & mask) != 0;
        }

        /**
        * @brief Reset all bits.
        */
        void Reset()
        {
            for (auto& word : m_Words)
            {
                word.store(0, std::memory_order_release);
            }
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

            Set(bit, false);

            return true;
        }

        /**
        * @brief Flip all bits.
        */
        void Flip()
        {
            for (size_t i = 0; i < kWordCount; ++i)
            {
                m_Words[i].fetch_xor(WordMask(i), std::memory_order_acq_rel);
            }
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

            const size_t index     = static_cast<size_t>(static_cast<TSize>(bit));
            const size_t wordIndex = index / kBitsPerWord;
            const Word   mask      = Word{1} << (index % kBitsPerWord);

            m_Words[wordIndex].fetch_xor(mask, std::memory_order_acq_rel);

            return true;
        }

        /**
        * @brief Is any bit set.
        *
        * @return Returns true if exist bit not set.
        */
        bool Any() const
        {
            for (auto& word : m_Words)
            {
                if (word.load(std::memory_order_acquire) != 0) return true;
            }

            return false;
        }

        /**
        * @brief Is all bits not set.
        *
        * @return Returns true if all bits not set.
        */
        bool None() const
        {
            return !Any();
        }
        
    private:
        
        /**
        * @brief Set every bit to 1.
        */
        void SetAll()
        {
            for (size_t i = 0; i < kWordCount; ++i)
            {
                m_Words[i].store(WordMask(i), std::memory_order_release);
            }
        }

        /**
        * @brief Get Mask of the valid bits within word.
        * 
        * @param[in] wordIndex .
        * 
        * @return Returns WordMask.
        */
        static constexpr Word WordMask(size_t wordIndex)
        {
            const size_t bitsBefore     = wordIndex * kBitsPerWord;
            const size_t bitsRemaining  = kBitCount > bitsBefore ? kBitCount - bitsBefore : 0;

            if (bitsRemaining >= kBitsPerWord)
            {
                return ~Word{0};
            }

            return (Word{1} << bitsRemaining) - 1;
        }
        
    private:
        
         std::array<std::atomic<Word>, kWordCount> m_Words{};          // @brief Stored bitset.

    };

}
