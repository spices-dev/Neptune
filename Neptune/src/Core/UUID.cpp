/**
* @file UUID.cpp.
* @brief The UUID Class Implementation.
* @author The Cherno.
*/

#include "Pchheader.h"
#include "UUID.h"

namespace Neptune {

    namespace {
        
        thread_local std::mt19937_64 s_Engine = [] {
            std::random_device rd;
            std::seed_seq seed{ rd(), rd(), rd(), rd() };
            return std::mt19937_64(seed);
        }();

        thread_local std::uniform_int_distribution<uint64_t> s_UniformDistribution;
        
    }
    
    UUID::UUID()
        : m_UUID(s_UniformDistribution(s_Engine))
    {}

    UUID::UUID(uint64_t uuid)
        : m_UUID(uuid)
    {}

    std::string UUID::ToString() const
    {
        NEPTUNE_PROFILE_ZONE

        std::stringstream ss;
        ss << m_UUID;

        return ss.str();
    }
}