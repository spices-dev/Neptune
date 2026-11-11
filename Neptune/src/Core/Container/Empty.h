/**
* @file Empty.h.
* @brief The Empty Struct Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Concept.h"

namespace Neptune::Container {

    /**
    * @brief Pure Empty struct.
    */
    struct PureEmpty {};
 
    /**
    * @brief Empty struct.
    */
    struct Empty { virtual ~Empty() = default; };
    
}