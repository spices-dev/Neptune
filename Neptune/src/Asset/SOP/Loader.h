/**
* @file Loader.h.
* @brief The SOPLoader Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/Container/MemoryBuffer.h"

namespace Neptune::SOP {
	
	/**
	* @brief Loader Class.
	*/
	class Loader
	{
	public:

		/**
		* @brief Load SOP data from a .asset file.
		* 
		* @param[in] file mesh file path.
		* @param[in,out] obj Object.
		* 
		* @return Returns true if load data successfully.
		*/
		static bool Load(const std::filesystem::path& file, class Object* obj);

		/**
		* @brief Load SOP data from memory data.
		* 
		* @param[in] memory mesh memory buffer.
		* @param[in,out] obj Object.
		* 
		* @return Returns true if load data successfully.
		*/
		static bool Load(MemoryBuffer& memory, class Object* obj);
		
	private:

		/**
		* @brief Load Polygon data from stream.
		* 
		* @param[in] stream stream.
		* @param[in,out] obj Polygon.
		* 
		* @return Returns true if load data successfully.
		*/
		static bool Load(std::istream& stream, class Polygon* obj);
		
		/**
		* @brief Load GS3D data from stream.
		* 
		* @param[in] stream stream.
		* @param[in,out] obj Mesh GS3D.
		* 
		* @return Returns true if load data successfully.
		*/
		static bool Load(std::istream& stream, class GS3D* obj);
	};
}