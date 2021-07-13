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
		game.ToggleMods();
	}

	void features::script_func()
	{
		game.Alert("Warming up mods.", "iVritex", "~g~[INFO]");
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
	void features::Game::ToggleMods() {
		if (Self_Godmode == true) { ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), true); }
		else{ ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), false); }

		if (Self_NeverWanted == true) { Entity player = PLAYER::PLAYER_PED_ID(); PLAYER::CLEAR_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()); PLAYER::SET_MAX_WANTED_LEVEL(0); PLAYER::SET_POLICE_IGNORE_PLAYER(player, true); PLAYER::SET_EVERYONE_IGNORE_PLAYER(player, true); PLAYER::SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(player, true); }
		else { Entity player = PLAYER::PLAYER_PED_ID(); PLAYER::CLEAR_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()); PLAYER::SET_MAX_WANTED_LEVEL(0); PLAYER::SET_POLICE_IGNORE_PLAYER(player, false); PLAYER::SET_EVERYONE_IGNORE_PLAYER(player, false); PLAYER::SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(player, false); }
	}

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
