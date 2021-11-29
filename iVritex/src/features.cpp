#include "common.hpp"
#include "features.hpp"
#include "logger.hpp"
#include "natives.hpp"
#include "script.hpp"
#include "pointers.hpp"
#include "frontend/old_theme/ui.hpp";

namespace big
{
	void features::run_tick()
	{
		game.ToggleMods();
	}

	void features::script_func()
	{
		LOG_INFO("Warming up mods.");
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

		if (Self_Noclip == true) { game.NoClip(); }

		if (Menu_OldTheme) {
			GUI::Nano42();
		}
	}

	int features::Game::Alert(const char* text, const char* text2, const char* Subject)
	{
		LOG_INFO(text);
		UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
		UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", false, 7, text2, Subject, 1.0, "HELHELL");
		return UI::_DRAW_NOTIFICATION(1, 1);
	}

	void features::Game::NoClip() {
		Ped playerPed = PLAYER::PLAYER_PED_ID();
		Vector3 pos = ENTITY::GET_ENTITY_COORDS(playerPed, false); //edit th
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.x, pos.y, pos.z, false, false, false);
		if (GetAsyncKeyState(VK_KEY_S) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, 268)) {
			float fivef = .5f;
			float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
			float xVec = fivef * sin(functions.degToRad(heading)) * -1.0f;
			float yVec = fivef * cos(functions.degToRad(heading));
			ENTITY::SET_ENTITY_HEADING(playerPed, heading);

			pos.x -= xVec, pos.y -= yVec;
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.x, pos.y, pos.z, false, false, false);
		}
		if (GetAsyncKeyState(VK_KEY_W) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, 269)) {
			float fivef = .5f;
			float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
			float xVec = fivef * sin(functions.degToRad(heading)) * -1.0f;
			float yVec = fivef * cos(functions.degToRad(heading));
			ENTITY::SET_ENTITY_HEADING(playerPed, heading);

			pos.x += xVec, pos.y += yVec;
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.x, pos.y, pos.z, false, false, false);
		}
		if (GetAsyncKeyState(VK_KEY_A) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(5, 266)) {
			float fivef = 1.0f;
			float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
			ENTITY::SET_ENTITY_HEADING(playerPed, heading + 1.0f);
		}
		if (GetAsyncKeyState(VK_KEY_D) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(5, 271)) {
			float fivef = 1.0f;
			float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
			ENTITY::SET_ENTITY_HEADING(playerPed, heading - 1.0f);
		}
		if (GetAsyncKeyState(VK_SHIFT) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, 205)) {
			float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
			ENTITY::SET_ENTITY_HEADING(playerPed, heading);

			pos.z -= 0.5f;
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.x, pos.y, pos.z, false, false, false);
		}
		if (GetAsyncKeyState(VK_SPACE) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(2, 206)) {
			float heading = ENTITY::GET_ENTITY_HEADING(playerPed);
			ENTITY::SET_ENTITY_HEADING(playerPed, heading);

			pos.z += 0.5f;
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerPed, pos.x, pos.y, pos.z, false, false, false);
		}
	}

	// Functions
	bool features::Functions::fileExists(const std::string& fileName)
	{
		struct stat buffer;
		return (stat(fileName.c_str(), &buffer) == 0);
	}
	 
	float features::Functions::degToRad(float degs)
	{
		return degs * 3.141592653589793f / 180.f;
	}
}
