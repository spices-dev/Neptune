/**
* @file MeshLoader.h.
* @brief The MeshLoader Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

namespace Neptune {

	class MeshPack;
	
	/**
	* @brief MeshLoader Class.
	*/
	class MeshLoader
	{
	public:

		/**
		* @brief Public called API, it is entrance.
		* 
		* @param[in] fileName mesh file name.
		* @param[in,out] outMeshPack mesh pack pointer, only pass this to it.
		* Feel free for using row pointer here, it's very safe, for this API only called during MeshPack.
		* 
		* @return Returns true if load data successfully.
		*/
		static bool Load(const std::string& fileName, MeshPack* outMeshPack);

	private:

		/**
		* @brief Load data from a .sasset file.
		* 
		* @param[in] fileName Mesh file path in disk.
		* @param[in,out] outMeshPack mesh pack pointer, only pass this to it.
		* 
		* @return Returns true if load data successfully.
		*/
		static bool LoadFromSASSET(const std::string& fileName, const MeshPack* outMeshPack);

		/**
		* @brief Write the read data to the sasset file.
		* 
		* @param[in] fileName Mesh file path in disk.
		* @param[in] folderIndex Index of Resource Folder.
		* @param[in,out] outMeshPack mesh pack pointer, only pass this to it.
		* 
		* @return Returns true if write data successfully.
		*/
		static bool WriteSASSET(int folderIndex, const std::string& fileName, const MeshPack* outMeshPack);
	};
}