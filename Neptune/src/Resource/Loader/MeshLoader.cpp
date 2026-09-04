/**
* @file MeshLoader.cpp.
* @brief The MeshLoader Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "MeshLoader.h"
#include "Resource/Mesh/MeshPack.h"

namespace Neptune {

	/**
	* @brief Const variable: Mesh File Confirm header staer.
	*/
	constexpr char MeshLoaderSignStart[100] = "#ItisSpicesMeshSign: DataStart";

	/**
	* @brief Const variable: Mesh File Confirm header over.
	*/
	constexpr char MeshLoaderSignOver[100] = "#ItisSpicesMeshSign: DateOver";

	bool MeshLoader::Load(const std::string& fileName, MeshPack* outMeshPack)
	{
		NEPTUNE_PROFILE_ZONE

		return LoadFromSASSET(fileName, outMeshPack);
	}

	bool MeshLoader::LoadFromSASSET(const std::string& fileName, const MeshPack* outMeshPack)
	{
		NEPTUNE_PROFILE_ZONE

		bool isFind = false;
		std::string filePath;

		try
		{
			if (!std::filesystem::exists(filePath.c_str())) {
				return false;
			}
		}
		catch (std::error_code e)
		{
			
		}

		return true;
	}

	bool MeshLoader::WriteSASSET(int folderIndex, const std::string& fileName, const MeshPack* outMeshPack)
	{
		NEPTUNE_PROFILE_ZONE
		
		return true;
	}
}