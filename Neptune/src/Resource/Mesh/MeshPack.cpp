/**
* @file MeshPack.cpp.
* @brief The MeshPack Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "MeshPack.h"
#include "Resource/Loader/MeshLoader.h"

namespace Neptune {

	MeshPack::MeshPack(const std::string& name, bool instanced)
		: m_MeshPackName(name)
		, m_Instanced(instanced)
	    , m_UUID(UUID())
	{}

}