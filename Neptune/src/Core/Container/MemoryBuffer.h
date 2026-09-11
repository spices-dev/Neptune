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
    */
    struct MemoryBuffer : std::streambuf 
    {
        MemoryBuffer(const char* begin, uint32_t size) {

            auto* b = const_cast<char*>(begin);
            auto* e = b + size;
        
            setg(b, b, e);
        }
    
        pos_type seekoff(off_type off, std::ios_base::seekdir dir, std::ios_base::openmode which) override 
        {
            if (dir == std::ios_base::cur)
            {
                gbump(static_cast<int>(off));
            }
            else if (dir == std::ios_base::end)
            {
                setg(eback(), egptr() + off, egptr());
            }
            else if (dir == std::ios_base::beg)
            {
                setg(eback(), eback() + off, egptr());
            }
        
            return gptr() - eback();
        }

        pos_type seekpos(pos_type pos, std::ios_base::openmode which) override 
        {
            return seekoff(off_type(pos), std::ios_base::beg, which);
        }
    };

}