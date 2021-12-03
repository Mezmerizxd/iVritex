#include "ui.hpp"
#include "backend/natives.hpp"
#include "features.hpp"

// This uses Nano42

#define IsKeyPressed(key) GetAsyncKeyState(key) & 0x8000

bool MenuOpen = false;

void GUI::Nano42()
{
	CONTROLS::DISABLE_CONTROL_ACTION(0, 27, true);
	if (!MenuOpen)
	{
		Settings::menuLevel == 0 ? MenuLevelHandler::MoveMenu(SubMenus::MainMenu) : Settings::menuLevel == 1 ? MenuLevelHandler::BackMenu() : NULL;
		Settings::keyPressPreviousTick = GetTickCount();
		MenuOpen = true;
	}

	GUI::Checks::Controlls();
	switch (GUI::Settings::currentMenu)
	{
	case MainMenu:
	{
		GUI::Title("~p~iVritex ~s~Menu");
		GUI::MenuOption("[~p~Self~s~]", SelfMenu);
		GUI::MenuOption("[~p~Network~s~]", NetworkMenu);
		GUI::MenuOption("[~p~Weapons~s~]", WeaponMenu);
		GUI::MenuOption("[~p~Vehicle Spawner~s~]", VehicleSpawnMenu);
		GUI::MenuOption("[~p~Vehicle Options~s~]", VehicleMenu);
		GUI::MenuOption("[~p~Teleport~s~]", TeleportMenu);
		GUI::MenuOption("[~p~Misc~s~]", MiscMenu);
		GUI::MenuOption("[~p~Bypass~s~]", BypassMenu);
		GUI::MenuOption("[~p~Recovery~s~]", RecoveryMenu);
		GUI::MenuOption("[~p~Protections~s~]", ProtectionMenu);
		GUI::MenuOption("[~p~Credits~s~]", CreditMenu);
	}break;
	}
}

enum eControl
{
	ControlNextCamera = 0,
	ControlLookLeftRight = 1,
	ControlLookUpDown = 2,
	ControlLookUpOnly = 3,
	ControlLookDownOnly = 4,
	ControlLookLeftOnly = 5,
	ControlLookRightOnly = 6,
	ControlCinematicSlowMo = 7,
	ControlFlyUpDown = 8,
	ControlFlyLeftRight = 9,
	ControlScriptedFlyZUp = 10,
	ControlScriptedFlyZDown = 11,
	ControlWeaponWheelUpDown = 12,
	ControlWeaponWheelLeftRight = 13,
	ControlWeaponWheelNext = 14,
	ControlWeaponWheelPrev = 15,
	ControlSelectNextWeapon = 16,
	ControlSelectPrevWeapon = 17,
	ControlSkipCutscene = 18,
	ControlCharacterWheel = 19,
	ControlMultiplayerInfo = 20,
	ControlSprint = 21,
	ControlJump = 22,
	ControlEnter = 23,
	ControlAttack = 24,
	ControlAim = 25,
	ControlLookBehind = 26,
	ControlPhone = 27,
	ControlSpecialAbility = 28,
	ControlSpecialAbilitySecondary = 29,
	ControlMoveLeftRight = 30,
	ControlMoveUpDown = 31,
	ControlMoveUpOnly = 32,
	ControlMoveDownOnly = 33,
	ControlMoveLeftOnly = 34,
	ControlMoveRightOnly = 35,
	ControlDuck = 36,
	ControlSelectWeapon = 37,
	ControlPickup = 38,
	ControlSniperZoom = 39,
	ControlSniperZoomInOnly = 40,
	ControlSniperZoomOutOnly = 41,
	ControlSniperZoomInSecondary = 42,
	ControlSniperZoomOutSecondary = 43,
	ControlCover = 44,
	ControlReload = 45,
	ControlTalk = 46,
	ControlDetonate = 47,
	ControlHUDSpecial = 48,
	ControlArrest = 49,
	ControlAccurateAim = 50,
	ControlContext = 51,
	ControlContextSecondary = 52,
	ControlWeaponSpecial = 53,
	ControlWeaponSpecial2 = 54,
	ControlDive = 55,
	ControlDropWeapon = 56,
	ControlDropAmmo = 57,
	ControlThrowGrenade = 58,
	ControlVehicleMoveLeftRight = 59,
	ControlVehicleMoveUpDown = 60,
	ControlVehicleMoveUpOnly = 61,
	ControlVehicleMoveDownOnly = 62,
	ControlVehicleMoveLeftOnly = 63,
	ControlVehicleMoveRightOnly = 64,
	ControlVehicleSpecial = 65,
	ControlVehicleGunLeftRight = 66,
	ControlVehicleGunUpDown = 67,
	ControlVehicleAim = 68,
	ControlVehicleAttack = 69,
	ControlVehicleAttack2 = 70,
	ControlVehicleAccelerate = 71,
	ControlVehicleBrake = 72,
	ControlVehicleDuck = 73,
	ControlVehicleHeadlight = 74,
	ControlVehicleExit = 75,
	ControlVehicleHandbrake = 76,
	ControlVehicleHotwireLeft = 77,
	ControlVehicleHotwireRight = 78,
	ControlVehicleLookBehind = 79,
	ControlVehicleCinCam = 80,
	ControlVehicleNextRadio = 81,
	ControlVehiclePrevRadio = 82,
	ControlVehicleNextRadioTrack = 83,
	ControlVehiclePrevRadioTrack = 84,
	ControlVehicleRadioWheel = 85,
	ControlVehicleHorn = 86,
	ControlVehicleFlyThrottleUp = 87,
	ControlVehicleFlyThrottleDown = 88,
	ControlVehicleFlyYawLeft = 89,
	ControlVehicleFlyYawRight = 90,
	ControlVehiclePassengerAim = 91,
	ControlVehiclePassengerAttack = 92,
	ControlVehicleSpecialAbilityFranklin = 93,
	ControlVehicleStuntUpDown = 94,
	ControlVehicleCinematicUpDown = 95,
	ControlVehicleCinematicUpOnly = 96,
	ControlVehicleCinematicDownOnly = 97,
	ControlVehicleCinematicLeftRight = 98,
	ControlVehicleSelectNextWeapon = 99,
	ControlVehicleSelectPrevWeapon = 100,
	ControlVehicleRoof = 101,
	ControlVehicleJump = 102,
	ControlVehicleGrapplingHook = 103,
	ControlVehicleShuffle = 104,
	ControlVehicleDropProjectile = 105,
	ControlVehicleMouseControlOverride = 106,
	ControlVehicleFlyRollLeftRight = 107,
	ControlVehicleFlyRollLeftOnly = 108,
	ControlVehicleFlyRollRightOnly = 109,
	ControlVehicleFlyPitchUpDown = 110,
	ControlVehicleFlyPitchUpOnly = 111,
	ControlVehicleFlyPitchDownOnly = 112,
	ControlVehicleFlyUnderCarriage = 113,
	ControlVehicleFlyAttack = 114,
	ControlVehicleFlySelectNextWeapon = 115,
	ControlVehicleFlySelectPrevWeapon = 116,
	ControlVehicleFlySelectTargetLeft = 117,
	ControlVehicleFlySelectTargetRight = 118,
	ControlVehicleFlyVerticalFlightMode = 119,
	ControlVehicleFlyDuck = 120,
	ControlVehicleFlyAttackCamera = 121,
	ControlVehicleFlyMouseControlOverride = 122,
	ControlVehicleSubTurnLeftRight = 123,
	ControlVehicleSubTurnLeftOnly = 124,
	ControlVehicleSubTurnRightOnly = 125,
	ControlVehicleSubPitchUpDown = 126,
	ControlVehicleSubPitchUpOnly = 127,
	ControlVehicleSubPitchDownOnly = 128,
	ControlVehicleSubThrottleUp = 129,
	ControlVehicleSubThrottleDown = 130,
	ControlVehicleSubAscend = 131,
	ControlVehicleSubDescend = 132,
	ControlVehicleSubTurnHardLeft = 133,
	ControlVehicleSubTurnHardRight = 134,
	ControlVehicleSubMouseControlOverride = 135,
	ControlVehiclePushbikePedal = 136,
	ControlVehiclePushbikeSprint = 137,
	ControlVehiclePushbikeFrontBrake = 138,
	ControlVehiclePushbikeRearBrake = 139,
	ControlMeleeAttackLight = 140,
	ControlMeleeAttackHeavy = 141,
	ControlMeleeAttackAlternate = 142,
	ControlMeleeBlock = 143,
	ControlParachuteDeploy = 144,
	ControlParachuteDetach = 145,
	ControlParachuteTurnLeftRight = 146,
	ControlParachuteTurnLeftOnly = 147,
	ControlParachuteTurnRightOnly = 148,
	ControlParachutePitchUpDown = 149,
	ControlParachutePitchUpOnly = 150,
	ControlParachutePitchDownOnly = 151,
	ControlParachuteBrakeLeft = 152,
	ControlParachuteBrakeRight = 153,
	ControlParachuteSmoke = 154,
	ControlParachutePrecisionLanding = 155,
	ControlMap = 156,
	ControlSelectWeaponUnarmed = 157,
	ControlSelectWeaponMelee = 158,
	ControlSelectWeaponHandgun = 159,
	ControlSelectWeaponShotgun = 160,
	ControlSelectWeaponSmg = 161,
	ControlSelectWeaponAutoRifle = 162,
	ControlSelectWeaponSniper = 163,
	ControlSelectWeaponHeavy = 164,
	ControlSelectWeaponSpecial = 165,
	ControlSelectCharacterMichael = 166,
	ControlSelectCharacterFranklin = 167,
	ControlSelectCharacterTrevor = 168,
	ControlSelectCharacterMultiplayer = 169,
	ControlSaveReplayClip = 170,
	ControlSpecialAbilityPC = 171,
	ControlPhoneUp = 172,
	ControlPhoneDown = 173,
	ControlPhoneLeft = 174,
	ControlPhoneRight = 175,
	ControlPhoneSelect = 176,
	ControlPhoneCancel = 177,
	ControlPhoneOption = 178,
	ControlPhoneExtraOption = 179,
	ControlPhoneScrollForward = 180,
	ControlPhoneScrollBackward = 181,
	ControlPhoneCameraFocusLock = 182,
	ControlPhoneCameraGrid = 183,
	ControlPhoneCameraSelfie = 184,
	ControlPhoneCameraDOF = 185,
	ControlPhoneCameraExpression = 186,
	ControlFrontendDown = 187,
	ControlFrontendUp = 188,
	ControlFrontendLeft = 189,
	ControlFrontendRight = 190,
	ControlFrontendRdown = 191,
	ControlFrontendRup = 192,
	ControlFrontendRleft = 193,
	ControlFrontendRright = 194,
	ControlFrontendAxisX = 195,
	ControlFrontendAxisY = 196,
	ControlFrontendRightAxisX = 197,
	ControlFrontendRightAxisY = 198,
	ControlFrontendPause = 199,
	ControlFrontendPauseAlternate = 200,
	ControlFrontendAccept = 201,
	ControlFrontendCancel = 202,
	ControlFrontendX = 203,
	ControlFrontendY = 204,
	ControlFrontendLb = 205,
	ControlFrontendRb = 206,
	ControlFrontendLt = 207,
	ControlFrontendRt = 208,
	ControlFrontendLs = 209,
	ControlFrontendRs = 210,
	ControlFrontendLeaderboard = 211,
	ControlFrontendSocialClub = 212,
	ControlFrontendSocialClubSecondary = 213,
	ControlFrontendDelete = 214,
	ControlFrontendEndscreenAccept = 215,
	ControlFrontendEndscreenExpand = 216,
	ControlFrontendSelect = 217,
	ControlScriptLeftAxisX = 218,
	ControlScriptLeftAxisY = 219,
	ControlScriptRightAxisX = 220,
	ControlScriptRightAxisY = 221,
	ControlScriptRUp = 222,
	ControlScriptRDown = 223,
	ControlScriptRLeft = 224,
	ControlScriptRRight = 225,
	ControlScriptLB = 226,
	ControlScriptRB = 227,
	ControlScriptLT = 228,
	ControlScriptRT = 229,
	ControlScriptLS = 230,
	ControlScriptRS = 231,
	ControlScriptPadUp = 232,
	ControlScriptPadDown = 233,
	ControlScriptPadLeft = 234,
	ControlScriptPadRight = 235,
	ControlScriptSelect = 236,
	ControlCursorAccept = 237,
	ControlCursorCancel = 238,
	ControlCursorX = 239,
	ControlCursorY = 240,
	ControlCursorScrollUp = 241,
	ControlCursorScrollDown = 242,
	ControlEnterCheatCode = 243,
	ControlInteractionMenu = 244,
	ControlMpTextChatAll = 245,
	ControlMpTextChatTeam = 246,
	ControlMpTextChatFriends = 247,
	ControlMpTextChatCrew = 248,
	ControlPushToTalk = 249,
	ControlCreatorLS = 250,
	ControlCreatorRS = 251,
	ControlCreatorLT = 252,
	ControlCreatorRT = 253,
	ControlCreatorMenuToggle = 254,
	ControlCreatorAccept = 255,
	ControlCreatorDelete = 256,
	ControlAttack2 = 257,
	ControlRappelJump = 258,
	ControlRappelLongJump = 259,
	ControlRappelSmashWindow = 260,
	ControlPrevWeapon = 261,
	ControlNextWeapon = 262,
	ControlMeleeAttack1 = 263,
	ControlMeleeAttack2 = 264,
	ControlWhistle = 265,
	ControlMoveLeft = 266,
	ControlMoveRight = 267,
	ControlMoveUp = 268,
	ControlMoveDown = 269,
	ControlLookLeft = 270,
	ControlLookRight = 271,
	ControlLookUp = 272,
	ControlLookDown = 273,
	ControlSniperZoomIn = 274,
	ControlSniperZoomOut = 275,
	ControlSniperZoomInAlternate = 276,
	ControlSniperZoomOutAlternate = 277,
	ControlVehicleMoveLeft = 278,
	ControlVehicleMoveRight = 279,
	ControlVehicleMoveUp = 280,
	ControlVehicleMoveDown = 281,
	ControlVehicleGunLeft = 282,
	ControlVehicleGunRight = 283,
	ControlVehicleGunUp = 284,
	ControlVehicleGunDown = 285,
	ControlVehicleLookLeft = 286,
	ControlVehicleLookRight = 287,
	ControlReplayStartStopRecording = 288,
	ControlReplayStartStopRecordingSecondary = 289,
	ControlScaledLookLeftRight = 290,
	ControlScaledLookUpDown = 291,
	ControlScaledLookUpOnly = 292,
	ControlScaledLookDownOnly = 293,
	ControlScaledLookLeftOnly = 294,
	ControlScaledLookRightOnly = 295,
	ControlReplayMarkerDelete = 296,
	ControlReplayClipDelete = 297,
	ControlReplayPause = 298,
	ControlReplayRewind = 299,
	ControlReplayFfwd = 300,
	ControlReplayNewmarker = 301,
	ControlReplayRecord = 302,
	ControlReplayScreenshot = 303,
	ControlReplayHidehud = 304,
	ControlReplayStartpoint = 305,
	ControlReplayEndpoint = 306,
	ControlReplayAdvance = 307,
	ControlReplayBack = 308,
	ControlReplayTools = 309,
	ControlReplayRestart = 310,
	ControlReplayShowhotkey = 311,
	ControlReplayCycleMarkerLeft = 312,
	ControlReplayCycleMarkerRight = 313,
	ControlReplayFOVIncrease = 314,
	ControlReplayFOVDecrease = 315,
	ControlReplayCameraUp = 316,
	ControlReplayCameraDown = 317,
	ControlReplaySave = 318,
	ControlReplayToggletime = 319,
	ControlReplayToggletips = 320,
	ControlReplayPreview = 321,
	ControlReplayToggleTimeline = 322,
	ControlReplayTimelinePickupClip = 323,
	ControlReplayTimelineDuplicateClip = 324,
	ControlReplayTimelinePlaceClip = 325,
	ControlReplayCtrl = 326,
	ControlReplayTimelineSave = 327,
	ControlReplayPreviewAudio = 328,
	ControlVehicleDriveLook = 329,
	ControlVehicleDriveLook2 = 330,
	ControlVehicleFlyAttack2 = 331,
	ControlRadioWheelUpDown = 332,
	ControlRadioWheelLeftRight = 333,
	ControlVehicleSlowMoUpDown = 334,
	ControlVehicleSlowMoUpOnly = 335,
	ControlVehicleSlowMoDownOnly = 336,
	ControlMapPointOfInterest = 337,
};

float GUI::Settings::menuX = 0.2f;
bool GUI::Settings::selectPressed = false;
bool GUI::Settings::leftPressed = false;
bool GUI::Settings::rightPressed = false;
bool firstopen = true;
int GUI::Settings::maxVisOptions = 16;
int GUI::Settings::currentOption = 1;
int GUI::Settings::optionCount = 0;
SubMenus GUI::Settings::currentMenu;
int GUI::Settings::menuLevel = 0;
int GUI::Settings::optionsArray[1000];
SubMenus GUI::Settings::menusArray[1000];
RGBAF GUI::Settings::count{ 132, 102, 226, 255, 6 };
RGBAF GUI::Settings::titleText{ 255, 255, 255, 255, 7 };
RGBA GUI::Settings::titleRect{ 0, 0, 0, 255 };
RGBAF GUI::Settings::optionText{ 255, 255, 255, 255, 6 };
RGBAF GUI::Settings::breakText{ 132, 102, 226, 255, 1 };
RGBA GUI::Settings::breakRect{ 0, 0, 0, 255 };
RGBA GUI::Settings::break2Rect{ 0, 0, 0, 150 };
RGBAF GUI::Settings::arrow{ 132, 102, 226, 255, 3 };
RGBA GUI::Settings::optionRect{ 0, 0, 0, 220 };
RGBA GUI::Settings::EndRect{ 0, 0, 0, 255 };
RGBA GUI::Settings::scroller{ 145, 102, 226, 100 };
RGBAF GUI::Settings::integre{ 255, 255, 255, 255, 2 };
RGBA GUI::Settings::line{ 132, 102, 226, 255 };
RGBA GUI::Settings::primary{ 255, 0, 0 };
RGBA GUI::Settings::secondary{ 0, 255, 0 };
int GUI::Settings::keyPressDelay = 200;
int GUI::Settings::keyPressPreviousTick = GetTickCount();
int GUI::Settings::keyPressDelay2 = 100;
int GUI::Settings::keyPressPreviousTick2 = GetTickCount();
int GUI::Settings::keyPressDelay3 = 140;
int GUI::Settings::keyPressPreviousTick3 = GetTickCount();
int GUI::Settings::openKey = VK_MULTIPLY;
int GUI::Settings::openKeyNum = VK_F6;
int GUI::Settings::backKey = VK_NUMPAD0;
int GUI::Settings::upKey = VK_NUMPAD8;
int GUI::Settings::downKey = VK_NUMPAD2;
int GUI::Settings::leftKey = VK_NUMPAD4;
int GUI::Settings::rightKey = VK_NUMPAD6;
int GUI::Settings::selectKey = VK_NUMPAD5;
int GUI::Settings::arrowupKey = VK_UP;
int GUI::Settings::arrowdownKey = VK_DOWN;
int GUI::Settings::arrowleftKey = VK_LEFT;
int GUI::Settings::arrowrightKey = VK_RIGHT;
int GUI::Settings::enterKey = VK_RETURN;
int GUI::Settings::deleteKey = VK_BACK;

RGBAF GUI::Settings::title_end{ 255,255,255,255,4 };
void GUI::AddSmallInfo(char* text, short line)
{
	const __int8 maxSize = 32;
	if (GUI::Settings::menuX < 0.58f)
	{
		if (line == 1) {
			Draw::Rect(Settings::optionRect, { Settings::menuX + 0.180f, ((static_cast<int>(23) * 0.035f) / 2.0f) + 0.078f - 0.135f }, { 0.115f, static_cast<int>(23) * 0.035f + -0.280f });
		}
		Draw::Text(text, Settings::title_end, { Settings::menuX + 0.235f, (line * 0.050f) + 0.100f }, { 0.375f, 0.375f }, false);
	}
	else
	{
		if (line == 1) {
			Draw::Rect(Settings::optionRect, { Settings::menuX - 0.180f, ((static_cast<int>(23) * 0.035f) / 2.0f) + 0.078f - 0.115f }, { 0.115f, static_cast<int>(23) * 0.035f + -0.280f });
		}
		Draw::Text(text, Settings::title_end, { Settings::menuX - 0.235f, (line * 0.020f) + 0.100f }, { 0.375f, 0.375f }, false);
	}
}
RGBAF GUI::Settings::titleText2{ 255, 255, 255, 255, 1 };
void GUI::AddSmallTitle(char* text)
{
	if (GUI::Settings::menuX < 0.78f)
	{
		Draw::Text(text, Settings::titleText2, { Settings::menuX + 0.200f, 0.090f }, { 0.425f, 0.425f }, true);
		Draw::Spriter("Shadowtextures", "Playerinfo", Settings::menuX + 0.100f, 0.1175f - 0.019f, 0.115f, 0.045f, 180, GUI::Settings::titleRect.r, GUI::Settings::titleRect.g, GUI::Settings::titleRect.b, GUI::Settings::titleRect.a);
	}
	else
	{
		Draw::Text(text, Settings::titleText2, { Settings::menuX + 0.200f, 0.090f }, { 0.425f, 0.425f }, true);
		Draw::Spriter("Shadowtextures", "Playerinfo", Settings::menuX + 0.100f, 0.1175f - 0.019f, 0.115f, 0.045f, 180, GUI::Settings::titleRect.r, GUI::Settings::titleRect.g, GUI::Settings::titleRect.b, GUI::Settings::titleRect.a);
	}
}
void GUI::Draw::Text(const char* text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center)
{
	UI::SET_TEXT_CENTRE(center);
	UI::SET_TEXT_COLOUR(rgbaf.r, rgbaf.g, rgbaf.b, rgbaf.a);
	UI::SET_TEXT_FONT(rgbaf.f);
	UI::SET_TEXT_SCALE(size.w, size.h);
	UI::SET_TEXT_DROPSHADOW(1, 0, 0, 0, 0);
	UI::SET_TEXT_EDGE(1, 0, 0, 0, 0);
	UI::SET_TEXT_OUTLINE();
	UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME((char*)text);
	UI::END_TEXT_COMMAND_DISPLAY_TEXT(position.x, position.y);
}
void GUI::Draw::Spriter(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a)
{
	if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED((char*)Streamedtexture.c_str()))
	{
		GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT((char*)Streamedtexture.c_str(), false);
	}
	else
	{
		GRAPHICS::DRAW_SPRITE((char*)Streamedtexture.c_str(), (char*)textureName.c_str(), x, y, width, height, rotation, r, g, b, a);
	}
}
void GUI::Draw::Rect(RGBA rgba, VECTOR2 position, VECTOR2_2 size)
{
	GRAPHICS::DRAW_RECT(position.x, position.y, size.w, size.h, rgba.r, rgba.g, rgba.b, rgba.a);
}
void GUI::Title(const char* title)
{
	Draw::Text(title, Settings::titleText, { Settings::menuX, 0.095f }, { 0.85f, 0.85f }, true);
	Draw::Rect(Settings::titleRect, { Settings::menuX, 0.1175f }, { 0.21f, 0.085f });
	//Draw::Spriter("Themes", "iVritexTheme", Settings::menuX, 0.1175f, 0.21f, 0.085f, 0, 255, 255, 255, 255);
}
bool GUI::ListVector(const char* option, std::vector<char*> Vector, int& position)
{

	constexpr static const VECTOR2_2 textSize = { 0.35f, 0.35f };
	Option(option);
	if (Settings::optionCount == Settings::currentOption) {
		size_t max = Vector.size() - 1;
		int min = 0;
		if (Settings::leftPressed) {
			position >= 1 ? position-- : position = max;
		}
		if (Settings::rightPressed) {
			position < max ? position++ : position = min;
		}
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Draw::Text(Tools::StringToChar(Vector[position]), Settings::optionText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, textSize, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Draw::Text(Tools::StringToChar(Vector[position]), Settings::optionText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.125f }, textSize, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	//else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
//	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	else
		return false;

	/*constexpr static const VECTOR2_2 textSize = { 0.45f, 0.45f };
	bool onThis = Settings::currentOption == Settings::optionCount + 1 ? true : false;
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		size_t max = Vector.size() - 1;
		int min = 0;
		if (Settings::rightPressed) {
			position >= 1 ? position-- : position = max;
		}
		if (Settings::leftPressed) {
			position < max ? position++ : position = min;
		}
	}

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return false;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return false;
	return false;*/
}
bool GUI::Option(const char* option)
{
	Settings::optionCount++;
	bool onThis = Settings::currentOption == Settings::optionCount ? true : false;
	if (Settings::currentOption <= 16 && Settings::optionCount <= 16)
	{
		Draw::Text(option, Settings::optionText, { Settings::menuX - 0.100f, (Settings::optionCount) * 0.035f + 0.125f }, { 0.45f, 0.45f }, false);
		Draw::Rect(Settings::optionRect, { Settings::menuX, (Settings::optionCount) * 0.035f + 0.1415f }, { 0.21f, 0.035f });
		onThis ? Draw::Rect(Settings::scroller, { Settings::menuX, (Settings::optionCount) * 0.035f + 0.1415f }, { 0.21f, 0.035f }) : NULL;
	}
	else if (Settings::optionCount > (Settings::currentOption - 16) && Settings::optionCount <= Settings::currentOption)
	{
		Draw::Text(option, Settings::optionText, { Settings::menuX - 0.100f, (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.125f }, { 0.45f, 0.45f }, false);
		Draw::Rect(Settings::optionRect, { Settings::menuX,  (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.1415f }, { 0.21f, 0.035f });
		onThis ? Draw::Rect(Settings::scroller, { Settings::menuX,  (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.1415f }, { 0.21f, 0.035f }) : NULL;
	}
	if (Settings::currentOption == Settings::optionCount)
	{
		if (Settings::selectPressed)
		{
			return true;
		}
	}
	return false;
}
bool GUI::Option2(const char* option, std::function<void()> function)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		function();
		return true;
	}
	return false;
}
bool GUI::SmallTitle(const char* option)
{

	Draw::Text(option, Settings::breakText, { Settings::menuX, (Settings::optionCount) * 0.035f + 0.125f }, { 0.45f, 0.45f }, true);
	Draw::Rect(Settings::breakRect, { Settings::menuX, (Settings::optionCount) * 0.035f + 0.1415f }, { 0.21f, 0.035f });
	Draw::Rect(Settings::line, { Settings::menuX, 2 * 0.035f + 0.1235f }, { 0.21f, 0.002f });

	return true;
}
bool GUI::SmallTitle2(const char* option)
{
	Settings::optionCount++;
	bool onThis = Settings::currentOption == Settings::optionCount ? true : false;
	if (Settings::currentOption <= 16 && Settings::optionCount <= 16)
	{
		Draw::Text(option, Settings::breakText, { Settings::menuX, (Settings::optionCount) * 0.035f + 0.125f }, { 0.45f, 0.45f }, true);
		Draw::Rect(Settings::optionRect, { Settings::menuX, (Settings::optionCount) * 0.035f + 0.1415f }, { 0.21f, 0.035f });
	}
	else if (Settings::optionCount > (Settings::currentOption - 16) && Settings::optionCount <= Settings::currentOption)
	{
		Draw::Text(option, Settings::breakText, { Settings::menuX, (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.125f }, { 0.45f, 0.45f }, true);
		Draw::Rect(Settings::optionRect, { Settings::menuX,  (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.1415f }, { 0.21f, 0.035f });
	}
	return false;
}
bool GUI::MenuOption(const char* option, SubMenus newSub)
{
	Option(option);

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions) {
		Draw::Text("", Settings::titleText, { Settings::menuX + 0.099f, Settings::optionCount * 0.035f + 0.125f }, { 0.35f, 0.35f }, true);
		Draw::Text("~p~>>", Settings::optionText, { Settings::menuX + 0.068f, (Settings::optionCount) * 0.035f + 0.125f }, { 0.45f, 0.45f }, false);
	}
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption) {
		Draw::Text("", Settings::titleText, { Settings::menuX + 0.099f, (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.125f }, { 0.35f, 0.35f }, true);
		Draw::Text("~p~>>", Settings::optionText, { Settings::menuX + 0.068f,  (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.125f }, { 0.45f, 0.45f }, false);
	}
	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		MenuLevelHandler::MoveMenu(newSub);
		return true;
	}
	return false;
}
void GUI::PlayerOption(int i) {
	if (GUI::Option(PLAYER::GET_PLAYER_NAME(i))) {
		//big::features::g_SelectedPlayer = i;
		MenuLevelHandler::MoveMenu(pmenu);
	}
}
bool GUI::ToggleOption(const char* option, bool& b00l)
{
	Option(option);
	if (b00l)
	{
		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions) {
			Draw::Text(b00l ? "~g~ON" : "~p~OFF", Settings::optionText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.128f }, { 0.40f, 0.40f }, true); // 0.35 // 0.125 // 0.45
			Draw::Spriter("commonmenu", "shop_box_tick", Settings::menuX + 0.073f, (Settings::optionCount * 0.035f + 0.141f), 0.027f, 0.047f, 0, 132, 102, 226, 255);
			//Draw::Spriter("Themes", "iVritex_Toggle_On", Settings::menuX + 0.073f, (Settings::optionCount * 0.035f + 0.141f), 0.027f, 0.047f, 0, 132, 102, 226, 255);
		}
		else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption) {
			Draw::Text(b00l ? "~g~ON" : "~p~OFF", Settings::optionText, { Settings::menuX + 0.069f, Settings::optionCount * 0.035f + 0.128f }, { 0.40f, 0.40f }, true);
			Draw::Spriter("commonmenu", "shop_box_tick", Settings::menuX + 0.073f, ((Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.141f), 0.027f, 0.047f, 0, 132, 102, 226, 255);
			//Draw::Spriter("Themes", "iVritex_Toggle_On", Settings::menuX + 0.073f, ((Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.141f), 0.027f, 0.047f, 0, 132, 102, 226, 255);
		}
	}
	else
	{
		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions) {
			Draw::Text(b00l ? "~g~ON" : "~p~OFF", Settings::optionText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.128f }, { 0.40f, 0.40f }, true);
			Draw::Spriter("commonmenu", "shop_box_blank", Settings::menuX + 0.073f, (Settings::optionCount * 0.035f + 0.141f), 0.027f, 0.047f, 0, 132, 102, 226, 255);
			//Draw::Spriter("Themes", "iVritex_Toggle_Off", Settings::menuX + 0.073f, (Settings::optionCount * 0.035f + 0.141f), 0.027f, 0.047f, 0, 132, 102, 226, 255);
		}
		else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption) {
			Draw::Text(b00l ? "~g~ON" : "~p~OFF", Settings::optionText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.128f }, { 0.40f, 0.40f }, true);
			Draw::Spriter("commonmenu", "shop_box_blank", Settings::menuX + 0.073f, ((Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.141f), 0.027f, 0.047f, 0, 132, 102, 226, 255);
			//Draw::Spriter("Themes", "iVritex_Toggle_Off", Settings::menuX + 0.073f, ((Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.141f), 0.027f, 0.047f, 0, 132, 102, 226, 255);
		}
	}
	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		b00l ^= 1;
		return true;
	}
	return false;
}
bool GUI::Int(const char* option, int& _int, int min, int max)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		if (Settings::leftPressed) {
			_int < max ? _int++ : _int = min;
		}
		if (Settings::rightPressed) {
			_int >= min ? _int-- : _int = max;
		}
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Draw::Text(Tools::StringToChar("< " + std::to_string(_int) + " >"), Settings::integre, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.128f }, { 0.32f, 0.32f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Draw::Text(Tools::StringToChar("< " + std::to_string(_int) + " >"), Settings::integre, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.125f }, { 0.32f, 0.32f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}
bool GUI::Int(const char* option, int& _int, int min, int max, int step)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		if (Settings::leftPressed) {
			_int < max ? _int += step : _int = min;
		}
		if (Settings::rightPressed) {
			_int >= min ? _int -= step : _int = max;
		}
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Draw::Text(Tools::StringToChar("< " + std::to_string(_int) + " >"), Settings::integre, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.32f, 0.32f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Draw::Text(Tools::StringToChar("< " + std::to_string(_int) + " >"), Settings::integre, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.125f }, { 0.32f, 0.32f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}
#pragma warning(disable: 4244)
bool GUI::Float(const char* option, float& _float, int min, int max)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		if (Settings::rightPressed) {
			_float <= min ? _float = max : _float -= 2.0f;
		}
		if (Settings::leftPressed) {
			_float >= max ? _float = min : _float += 2.0f;
		}
		_float < min ? _float = max : _float > max ? _float = min : NULL;
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Draw::Text(Tools::StringToChar(std::to_string(_float)), Settings::optionText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.128f }, { 0.32f, 0.32f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Draw::Text(Tools::StringToChar(std::to_string(_float)), Settings::optionText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.125f }, { 0.32f, 0.32f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}
bool GUI::VehicleSettingsSlider(const char* option, float& _float, int min, int max)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		if (Settings::leftPressed) {
			_float <= min ? _float = max : _float -= 2.0f;
		}
		if (Settings::rightPressed) {
			_float >= max ? _float = min : _float += 2.0f;
		}
		_float < min ? _float = max : _float > max ? _float = min : NULL;
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Draw::Text(Tools::StringToChar(std::to_string(_float)), Settings::optionText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.128f }, { 0.32f, 0.32f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Draw::Text(Tools::StringToChar(std::to_string(_float)), Settings::optionText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.125f }, { 0.32f, 0.32f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}
bool GUI::NoClipSlider(const char* option, float& _float, int min, int max)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		if (Settings::leftPressed) {
			_float <= min ? _float = max : _float -= -2.0f;
		}
		if (Settings::rightPressed) {
			_float >= max ? _float = min : _float += -2.0f;
		}
		_float < min ? _float = max : _float > max ? _float = min : NULL;
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Draw::Text(Tools::StringToChar(std::to_string(_float)), Settings::optionText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.128f }, { 0.32f, 0.32f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Draw::Text(Tools::StringToChar(std::to_string(_float)), Settings::optionText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.125f }, { 0.32f, 0.32f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}
bool GUI::Float(const char* option, float& _float, int min, int max, int step)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		if (Settings::leftPressed) {
			_float <= min ? _float = max : _float -= 0.1f;
		}
		if (Settings::rightPressed) {
			_float >= max ? _float = min : _float += 0.1f;
		}
		_float < min ? _float = max : _float > max ? _float = min : NULL;
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Draw::Text(Tools::StringToChar(std::to_string(_float)), Settings::optionText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.128f }, { 0.32f, 0.32f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Draw::Text(Tools::StringToChar(std::to_string(_float)), Settings::optionText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.125f }, { 0.32f, 0.32f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}
#pragma warning(default: 4244)
#pragma warning(disable: 4267)
bool GUI::IntVector(const char* option, std::vector<int> Vector, int& position)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		int max = Vector.size() - 1;
		int min = 0;
		if (Settings::leftPressed) {
			position >= 1 ? position-- : position = max;
		}
		if (Settings::rightPressed) {
			position < max ? position++ : position = min;
		}
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Draw::Text(Tools::StringToChar(std::to_string(Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Draw::Text(Tools::StringToChar(std::to_string(Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.125f }, { 0.5f, 0.5f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}
bool GUI::FloatVector(const char* option, std::vector<float> Vector, int& position)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		size_t max = Vector.size() - 1;
		int min = 0;
		if (Settings::leftPressed) {
			position >= 1 ? position-- : position = max;
		}
		if (Settings::rightPressed) {
			position < max ? position++ : position = min;
		}
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Draw::Text(Tools::StringToChar(std::to_string(Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Draw::Text(Tools::StringToChar(std::to_string(Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.125f }, { 0.5f, 0.5f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}
bool GUI::StringVector(const char* option, std::vector<std::string> Vector, int& position)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		size_t max = Vector.size() - 1;
		int min = 0;
		if (Settings::leftPressed) {
			position >= 1 ? position-- : position = max;
		}
		if (Settings::rightPressed) {
			position < max ? position++ : position = min;
		}
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Draw::Text(Tools::StringToChar((Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Draw::Text(Tools::StringToChar((Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.125f }, { 0.5f, 0.5f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}
bool GUI::StringVector(const char* option, std::vector<char*> Vector, int& position)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		size_t max = Vector.size() - 1;
		int min = 0;
		if (Settings::leftPressed) {
			position >= 1 ? position-- : position = max;
		}
		if (Settings::rightPressed) {
			position < max ? position++ : position = min;
		}
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Draw::Text(((Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f }, { 0.5f, 0.5f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Draw::Text(((Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.125f }, { 0.5f, 0.5f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}
#pragma warning(default: 4267)

void GUI::info(const char* info)
{
	if (Settings::currentOption <= 16 && Settings::optionCount <= 16)
	{
		if (bool onThis = true) { Draw::Text(info, Settings::optionText, { Settings::menuX - 0.100f, 17 * 0.035f + 0.1600f }, { 0.25f, 0.25f }, false); }
	}
	else if (Settings::optionCount > (Settings::currentOption - 16) && Settings::optionCount <= Settings::currentOption)
	{
		if (bool onThis = true) { Draw::Text(info, Settings::optionText, { Settings::menuX - 0.100f, (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.1300f }, { 0.25f, 0.25f }, false); }
	}
}
void GUI::End()
{
	int opcount = Settings::optionCount;
	int currop = Settings::currentOption;
	if (opcount >= 16) {
		Draw::Text(Tools::StringToChar(std::to_string(currop) + " / " + std::to_string(opcount)), Settings::count, { Settings::menuX + 0.078f, 17 * 0.035f + 0.125f }, { 0.35f, 0.35f }, true);
		Draw::Rect(Settings::EndRect, { Settings::menuX, 17 * 0.035f + 0.1415f }, { 0.21f, 0.035f });
		Draw::Rect(Settings::line, { Settings::menuX, 17 * 0.035f + 0.1235f }, { 0.21f, 0.002f });
		Draw::Spriter("commonmenu", "shop_arrows_upanddown", Settings::menuX, ((16 + 1) * 0.035f + 0.140f), 0.020f, 0.035f, 180, Settings::line.r, Settings::line.g, Settings::line.b, Settings::line.a);
	}
	else if (opcount > 0) {
		Draw::Text(Tools::StringToChar(std::to_string(currop) + " / " + std::to_string(opcount)), Settings::count, { Settings::menuX + 0.078f, (Settings::optionCount + 1) * 0.035f + 0.125f }, { 0.35f, 0.35f }, true);
		Draw::Rect(Settings::EndRect, { Settings::menuX, (Settings::optionCount + 1) * 0.035f + 0.1415f }, { 0.21f, 0.035f });
		Draw::Rect(Settings::line, { Settings::menuX, (Settings::optionCount + 1) * 0.035f + 0.1235f }, { 0.21f, 0.002f });
		Draw::Spriter("commonmenu", "shop_arrows_upanddown", Settings::menuX, ((Settings::optionCount + 1) * 0.035f + 0.140f), 0.020f, 0.035f, 180, Settings::line.r, Settings::line.g, Settings::line.b, Settings::line.a);
	}
}
#pragma endregion
void PlaySoundFrontend_default(char* sound_name)
{
	AUDIO::PLAY_SOUND_FRONTEND(-1, sound_name, "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
}
void PlaySoundFrontend_default2(char* sound_name)
{
	AUDIO::PLAY_SOUND_FRONTEND(-1, sound_name, "DLC_HEIST_BIOLAB_PREP_HACKING_SOUNDS", 0);
}


bool GUI::Settings::controllerinput = true;
void GUI::Checks::Controlls()
{
	Settings::selectPressed = false;
	Settings::leftPressed = false;
	Settings::rightPressed = false;
	if (GetTickCount() - Settings::keyPressPreviousTick > Settings::keyPressDelay) {
		if (GetTickCount() - Settings::keyPressPreviousTick2 > Settings::keyPressDelay2) {
			if (GetTickCount() - Settings::keyPressPreviousTick3 > Settings::keyPressDelay3) {
				if (IsKeyPressed(VK_MULTIPLY) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlScriptRB) && CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlPhoneRight) && Settings::controllerinput) {
					Settings::menuLevel == 0 ? MenuLevelHandler::MoveMenu(SubMenus::MainMenu) : Settings::menuLevel == 1 ? MenuLevelHandler::BackMenu() : NULL;
					Settings::keyPressPreviousTick = GetTickCount();
				}
				if (IsKeyPressed(VK_F4) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlScriptRB) && CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlPhoneRight) && Settings::controllerinput) {
					Settings::menuLevel == 0 ? MenuLevelHandler::MoveMenu(SubMenus::MainMenu) : Settings::menuLevel == 1 ? MenuLevelHandler::BackMenu() : NULL;
					Settings::keyPressPreviousTick = GetTickCount();
				}
				else if (IsKeyPressed(VK_NUMPAD0) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendCancel) && Settings::controllerinput) {
					Settings::menuLevel > 0 ? MenuLevelHandler::BackMenu() : NULL;
					if (Settings::menuLevel > 0)
						//PlaySoundFrontend_default("BACK");

					Settings::keyPressPreviousTick = GetTickCount();
				}
				else if (IsKeyPressed(VK_NUMPAD8) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendUp) && Settings::controllerinput) {
					Settings::currentOption > 1 ? Settings::currentOption-- : Settings::currentOption = Settings::optionCount;
					if (Settings::menuLevel > 0)
						//PlaySoundFrontend_default("NAV_UP_DOWN");

					Settings::keyPressPreviousTick2 = GetTickCount();
				}
				else if (IsKeyPressed(VK_NUMPAD2) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendDown) && Settings::controllerinput) {
					Settings::currentOption < Settings::optionCount ? Settings::currentOption++ : Settings::currentOption = 1;
					if (Settings::menuLevel > 0)
						//PlaySoundFrontend_default("NAV_UP_DOWN");

					Settings::keyPressPreviousTick2 = GetTickCount();
				}
				else if (IsKeyPressed(VK_NUMPAD6) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlPhoneRight) && Settings::controllerinput) {
					Settings::leftPressed = true;
					if (Settings::menuLevel > 0)
						//PlaySoundFrontend_default("NAV_UP_DOWN");

					Settings::keyPressPreviousTick3 = GetTickCount();
				}
				else if (IsKeyPressed(VK_NUMPAD4) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlPhoneLeft) && Settings::controllerinput) {
					Settings::rightPressed = true;
					if (Settings::menuLevel > 0)
						//PlaySoundFrontend_default("NAV_UP_DOWN");

					Settings::keyPressPreviousTick3 = GetTickCount();
				}
				else if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept) && Settings::controllerinput) {
					Settings::selectPressed = true;
					if (Settings::menuLevel > 0)
						//PlaySoundFrontend_default("SELECT");

					Settings::keyPressPreviousTick = GetTickCount();
				}
			}
		}
	}
	Settings::optionCount = 0;
} //Keyboard Controls
#pragma warning(default : 4018)
void GUI::MenuLevelHandler::MoveMenu(SubMenus menu)
{
	Settings::menusArray[Settings::menuLevel] = Settings::currentMenu;
	Settings::optionsArray[Settings::menuLevel] = Settings::currentOption;
	Settings::menuLevel++;
	Settings::currentMenu = menu;
	Settings::currentOption = 1;
}
void GUI::MenuLevelHandler::BackMenu()
{
	Settings::menuLevel--;
	Settings::currentMenu = Settings::menusArray[Settings::menuLevel];
	Settings::currentOption = Settings::optionsArray[Settings::menuLevel];
}
char* GUI::Tools::StringToChar(std::string string)
{
	return _strdup(string.c_str());
}
void GUI::Files::WriteStringToIni(std::string string, std::string file, std::string app, std::string key)
{
	WritePrivateProfileStringA(app.c_str(), key.c_str(), string.c_str(), file.c_str());
}
std::string GUI::Files::ReadStringFromIni(std::string file, std::string app, std::string key)
{
	char buf[100];
	GetPrivateProfileStringA(app.c_str(), key.c_str(), "NULL", buf, 100, file.c_str());
	return (std::string)buf;
}
void GUI::Files::WriteIntToIni(int intValue, std::string file, std::string app, std::string key)
{
	WriteStringToIni(std::to_string(intValue), file, app, key);
}
int GUI::Files::ReadIntFromIni(std::string file, std::string app, std::string key)
{
	return std::stoi(ReadStringFromIni(file, app, key));
}
void GUI::Files::WriteFloatToIni(float floatValue, std::string file, std::string app, std::string key)
{
	WriteStringToIni((std::to_string(floatValue)), file, app, key);
}
float GUI::Files::ReadFloatFromIni(std::string file, std::string app, std::string key)
{
	return std::stof(ReadStringFromIni(file, app, key));
}
void GUI::Files::WriteBoolToIni(bool b00l, std::string file, std::string app, std::string key)
{
	WriteStringToIni(b00l ? "true" : "false", file, app, key);
}
bool GUI::Files::ReadBoolFromIni(std::string file, std::string app, std::string key)
{
	return ReadStringFromIni(file, app, key) == "true" ? true : false;
}
void GUI::Vehicle(std::string texture1, std::string texture2)
{
	if (GUI::Settings::menuX < 0.78f)
	{
		if (GUI::Settings::optionCount == GUI::Settings::currentOption) { GUI::Draw::Spriter(texture1, texture2, GUI::Settings::menuX + 0.24f, 0.2f, 0.11f, 0.11f, 0, 255, 255, 255, 255); }
	}
	else { if (GUI::Settings::optionCount == GUI::Settings::currentOption) { GUI::Draw::Spriter(texture1, texture2, GUI::Settings::menuX - 0.24f, 0.2f, 0.11f, 0.11f, 0, 255, 255, 255, 255); } }
}

