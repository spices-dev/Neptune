/**
* @file VideoPlayer.h.
* @brief The VideoPlayer Class Definitions.
* @author Spices.
*/

#pragma once
#include <Core/Core.h>
#include <Scripts/NativeScripts/NativeScript.h>

#include <filesystem>

namespace Neptune::Video {
	
	class Demuxer;
	class Decoder;
}

namespace Neptune::Editor {
	
	/**
	* @brief Video Player Script.
	*/
	class VideoPlayer : public NativeScript
	{
	public:

		/**
		* @brief Constructor Function.
		* 
		* @param[in] path Video File Path.
		*/
		VideoPlayer(const std::filesystem::path& path);
		
		/**
		* @brief Destructor Function.
		*/
		~VideoPlayer() override;

		/**
		* @brief This interface defines to behave on specific component on attached.
		*/
		void OnAttached() override;
		
		/**
		* @brief This interface defines the behave on specific component tick every frame.
		*/
		void OnTick() override;

	private:

		std::filesystem::path m_InFile;                    // @brief Video File
		UP<Video::Demuxer> m_Demuxer = nullptr;            // @brief Demuxer
		UP<Video::Decoder> m_Decoder = nullptr;            // @brief Decoder
	};
}