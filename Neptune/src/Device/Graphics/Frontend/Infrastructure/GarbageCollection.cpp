/**
* @file GarbageCollection.cpp.
* @brief The GarbageCollection Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "GarbageCollection.h"

namespace Neptune::Graphic {
    
    GarbageCollection::~GarbageCollection()
    {
        Flush();
    }

    void GarbageCollection::Flush(uint64_t frameId)
    {
        NEPTUNE_PROFILE_ZONE
        
        std::vector<UP<IGarbage>> expired;
        
        {
            std::unique_lock lock(m_Mutex);
            
            expired.swap(m_Buckets[frameId % MaxFrameInFlight]);
        }
        
        expired.clear();
    }

    void GarbageCollection::Flush()
    {
        NEPTUNE_PROFILE_ZONE
        
        for (bool drained = false; !drained;)
        {
            drained = true;
            
            for (uint32_t i = 0; i < MaxFrameInFlight; ++i)
            {
                std::vector<UP<IGarbage>> expired;
                
                {
                    std::unique_lock lock(m_Mutex);
            
                    expired.swap(m_Buckets[i]);
                }
                
                if (!expired.empty()) drained = false;
                
                expired.clear();
            }
        }
    }
}