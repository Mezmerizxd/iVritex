#pragma once 

// This uses Nano42

enum SubMenus { //Add Sub Menus in here
	//Main
	NOMENU,
	pmenu,
	MainMenu,
	//Self
	SelfMenu,
	SelfAnimations,
	SelfModelChanger,
	//Network
	NetworkMenu,
	NetworkPlayerlist,
	NetworkLobby,
	NetworkLobbyTroll,
	NetworkLobbyNice,
	NetworkLobbyTeleport,
	NetworkLobbyInfect,
	NetworkPlayerTroll,
	NetworkPlayerNice,
	NetworkPlayerInfect,
	NetworkPlayerTeleport,
	NetworkPlayerTrollKick,
	NetworkLobbySessionWeather,
	NetworkPlayerTrollEvent,
	//Weapon
	WeaponMenu,
	WeaponObjectGun,
	//Vehicle Spawn
	VehicleSpawnMenu,
	Super,
	Sports,
	Sportss,
	SportClassic,
	Offroad,
	Sedans,
	Coupes,
	Muscle,
	Boats,
	Commercial,
	Compacts,
	Cycles,
	Emergency,
	Helicopters,
	Industrial,
	Military,
	Motorcycles,
	Planes,
	Service,
	SUV,
	Trailer,
	Trains,
	Utility,
	Vans,
	//Vehicle
	VehicleMenu,
	VehicleHornboostMenu,
	VehicleWeaponsMenu,
	VehicleAcrobaticMenu,
	VehicleCustomizeMenu,
	VehicleCustomizePaint,
	VehicleCustomizePaintCustom,
	//Teleport
	TeleportMenu,
	TeleportSafehouses,
	TeleportLandmarks,
	TeleportIPL,
	//Misc
	MiscMenu,
	WeatherMenu,
	//Bypass 
	BypassMenu,
	//Recovery
	RecoveryMenu,
	RecoverySingleplayer,
	RecoveryMoneyDropObjects,
	RecoveryOutfitEditor,
	//Protections
	ProtectionMenu,
	RecoveryMoneyDrop,
	RecoveryUnlocks,
	RecoveryRankOptions,
	//Credit
	CreditMenu,
	//Settings
	SettingsMenu
};
extern enum SubMenus;

typedef struct VECTOR2 {
	float x, y;
};
typedef struct VECTOR2_2 {
	float w, h;
};
typedef struct RGBAF {
	int r, g, b, a, f;
};
typedef struct RGBA {
	int r, g, b, a;
};
typedef struct RGB {
	int r, g, b;
};

namespace GUI {

	void Nano42();

	typedef struct
	{
		float x;
		DWORD _paddingx;
		float y;
		DWORD _paddingy;
		float z;
		DWORD _paddingz;
	} Vector3;
	namespace Draw {
		void Text(const char* text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center);
		void pmenuText(const char* text, char* info, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center);
		void Title(const char* text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center);
		void Rect(RGBA rgba, VECTOR2 position, VECTOR2_2 size);
		void Spriter(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a);
	}
	namespace Settings {
		extern bool selectPressed;
		extern bool leftPressed;
		extern bool rightPressed;
		extern int optionsArray[1000];
		extern SubMenus menusArray[1000];
		extern float menuX;
		extern RGBA MainColourForMenu;
		extern RGBAF count;
		extern RGBAF titleText;
		extern RGBA titleRect;
		extern RGBAF titleText2;
		extern RGBAF breakText;
		extern RGBA breakRect;
		extern RGBA break2Rect;
		extern RGBAF title_end;
		extern RGBAF optionText;
		extern RGBA EndRect;
		extern RGBA selectedText;
		extern RGBAF arrow;
		extern RGBAF integre;
		extern bool center;
		extern bool controllerinput;
		extern int maxVisOptions;
		extern int currentOption;
		extern int optionCount;
		extern SubMenus currentMenu;
		extern int menuLevel;
		extern int backpress;
		extern int click;
		extern int leftpress;
		extern int rightpress;
		extern int backKey;
		extern int openKeyNum;
		extern RGBA optionRect;
		extern RGBA scroller;
		extern RGBA line;
		extern RGBA primary;
		extern RGBA secondary;
		extern int keyPressDelay;
		extern int keyPressPreviousTick;
		extern int keyPressDelay2;
		extern int keyPressPreviousTick2;
		extern int keyPressDelay3;
		extern int keyPressPreviousTick3;
		extern int openKey;
		extern int arrowrightKey;
		extern int enterKey;
		extern int deleteKey;
		extern int openpress;
		extern int downpress;
		extern int uppress;
		extern int upKey;
		extern int downKey;
		extern int leftKey;
		extern int rightKey;
		extern int selectKey;
		extern int arrowupKey;
		extern int arrowdownKey;
		extern int arrowleftKey;

	}
	namespace MenuLevelHandler {
		void MoveMenu(SubMenus menu);
		void BackMenu();
	}
	namespace Checks {
		void Controlls();
	}
	namespace Tools {
		char* StringToChar(std::string string);
	}
	namespace Files {
		void WriteStringToIni(std::string string, std::string file, std::string app, std::string key);
		std::string ReadStringFromIni(std::string file, std::string app, std::string key);
		void WriteIntToIni(int intValue, std::string file, std::string app, std::string key);
		int ReadIntFromIni(std::string file, std::string app, std::string key);
		void WriteFloatToIni(float floatValue, std::string file, std::string app, std::string key);
		float ReadFloatFromIni(std::string file, std::string app, std::string key);
		void WriteBoolToIni(bool b00l, std::string file, std::string app, std::string key);
		bool ReadBoolFromIni(std::string file, std::string app, std::string key);
	}
	void YTD();
	void AddSmallInfo(char* text, short line);
	void AddSmallTitle(char* text);
	void Title(const char* title);
	void info(const char* title);
	void Vehicle(std::string texture1, std::string texture2);
	bool SmallTitle2(const char* option);
	bool SmallTitle(const char* option);
	bool Option(const char* option);
	bool Option(const char* option, std::function<void()> function);
	bool Option2(const char* option, std::function<void()> function);
	bool MenuOption(const char* option, SubMenus newSub);
	void PlayerOption(int i);
	bool MenuOption(const char* option, SubMenus newSub, std::function<void()> function);
	bool ToggleOption(const char* option, bool& b00l);
	bool ToggleOption(const char* option, bool& b00l, std::function<void()> function);
	bool Int(const char* option, int& _int, int min, int max);
	bool Int(const char* option, int& _int, int min, int max, int step);
	bool Int(const char* option, int& _int, int min, int max, std::function<void()> function);
	bool Int(const char* option, int& _int, int min, int max, int step, std::function<void()> function);
	bool Float(const char* option, float& _float, int min, int max);
	bool NoClipSlider(const char* option, float& _float, int min, int max);
	bool VehicleSettingsSlider(const char* option, float& _float, int min, int max);
	bool Float(const char* option, float& _float, int min, int max, int step);
	bool Float(const char* option, float& _float, int min, int max, std::function<void()> function);
	bool Float(const char* option, float& _float, int min, int max, int step, std::function<void()> function);
	bool IntVector(const char* option, std::vector<int> Vector, int& position);
	bool IntVector(const char* option, std::vector<int> Vector, int& position, std::function<void()> function);
	bool FloatVector(const char* option, std::vector<float> Vector, int& position);
	bool FloatVector(const char* option, std::vector<float> Vector, int& position, std::function<void()> function);
	bool StringVector(const char* option, std::vector<std::string> Vector, int& position);
	bool StringVector(const char* option, std::vector<std::string> Vector, int& position, std::function<void()> function);
	bool StringVector(const char* option, std::vector<char*> Vector, int& position);
	bool StringVector(const char* option, std::vector<char*> Vector, int& position, std::function<void()> function);
	bool ListVector(const char* option, std::vector<char*> Vector, int& position);
	bool Teleport(const char* option, Vector3 coords);
	bool Teleport(const char* option, Vector3 coords, std::function<void()> function);
	void End();
}
