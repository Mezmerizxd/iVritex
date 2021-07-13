#include "common.hpp"
#include "features.hpp"
#include "logger.hpp"
#include "natives.hpp"
#include "script.hpp"
#include "pointers.hpp"

namespace big
{
	void features::run_tick()
	{
	}

	void features::script_func()
	{
		while (true)
		{
			run_tick();
			script::get_current()->yield();
		}
	}

	// Menu
	void features::Menu::fancyHeader()
	{

		//g_pointers->m_fileregister(&textureID, m_FilePath.str().c_str(), true, file, false);
		//GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT("Themes", false);
	}

	// Game
	int features::Game::Alert(const char* text, const char* text2, const char* Subject)
	{
		UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
		UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", false, 7, text2, Subject, 1.0, "HELHELL");
		return UI::_DRAW_NOTIFICATION(1, 1);
	}

	// Functions
	bool features::Functions::fileExists(const std::string& fileName)
	{
		struct stat buffer;
		return (stat(fileName.c_str(), &buffer) == 0);
	}
}
