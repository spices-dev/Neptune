/**
* @file Object.h.
* @brief The Object Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Enum.h"

namespace Neptune::SOP {

	/**
	* @brief Object Class.
	*/
	class Object
	{
	public:

		/**
		* @brief Constructor Function.
		* 
		* @param[in] file FilePath.
		*/
		explicit Object(const std::filesystem::path& file) : m_FilePath(file) {}

		/**
		* @brief Destructor Function.
		*/
		virtual ~Object() = default;
		
		/**
		* @brief Get FilePath.
		* 
		* @return Returns FilePath.
		*/
		const std::filesystem::path& FilePath() const { return m_FilePath; }
		
		/**
		* @brief Load Asset from Disk.
		* 
		* @return Returns true if succeeded.
		*/
		bool Load();

	private:

		EObject m_Enum = EObject::Undefined;      // @brief EMesh.
		std::filesystem::path m_FilePath;         // @brief Description.
		
		friend class Loader;
	};
}