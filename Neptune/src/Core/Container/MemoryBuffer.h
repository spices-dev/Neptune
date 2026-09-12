/**
* @file MemoryBuffer.h.
* @brief The MemoryBuffer Struct Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Concept.h"

#include <streambuf>
#include <istream>

namespace Neptune::Container {

    /**
    * @brief Memory Buffer.
    * 
    * @note Not thread safe.
    */
    struct MemoryBuffer : std::streambuf 
    {
        /**
        * @brief Constructor Function.
        * 
        * @param[in] begin Data pointer.
        * @param[in] size Data Bytes.
        */
        MemoryBuffer(const char* begin, uint32_t size) 
        {
            auto* b = const_cast<char*>(begin);
            auto* e = b + size;
        
            setg(b, b, e);
        }
    
        /**
        * @brief seekoffs.
        * 
        * @param[in] off off_type.
        * @param[in] dir std::ios_base::seekdir.
        * @param[in] which std::ios_base::openmode.
        * 
        * @return Returns pos_type.
        */
        pos_type seekoff(off_type off, std::ios_base::seekdir dir, std::ios_base::openmode which) override 
        {
            char* target = nullptr;
            
            if (dir == std::ios_base::cur)
            {
                target = gptr() + off;
            }
            else if (dir == std::ios_base::end)
            {
                target = egptr() + off;
            }
            else if (dir == std::ios_base::beg)
            {
                target = eback() + off;
            }
            else
            {
                return pos_type(off_type(-1));
            }
            
            if (target < eback() || target > egptr())
            {
                return pos_type(off_type(-1));
            }

            setg(eback(), target, egptr());
        
            return pos_type(gptr() - eback());
        }

        /**
        * @brief seekpos.
        * 
        * @param[in] pos pos_type.
        * @param[in] which std::ios_base::openmode.
        * 
        * @return Returns pos_type.
        */
        pos_type seekpos(pos_type pos, std::ios_base::openmode which) override 
        {
            return seekoff(off_type(pos), std::ios_base::beg, which);
        }
    };

}