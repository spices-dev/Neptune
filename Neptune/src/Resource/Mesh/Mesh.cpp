/**
* @file Mesh.cpp.
* @brief The Mesh Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Mesh.h"

namespace Neptune {

	Mesh& Mesh::AddPack(const SP<MeshPack>& meshPack)
	{
		NEPTUNE_PROFILE_ZONE

		meshPack->OnCreatePack();

		m_Pack->PushBack(m_Pack->Size(), meshPack);

		return *this;
	}
}