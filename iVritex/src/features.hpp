#pragma once
#include "common.hpp"

namespace big::features
{
	void run_tick();
	void script_func();

	class Menu 
	{
	public:
		void fancyHeader();
	};

	class Game
	{
	public:
		bool Self_Godmode = false;
		bool Self_NeverWanted = false;
		bool Self_NoRagdoll = false;
	public:
		void ToggleMods();
		int Alert(const char* text, const char* text2, const char* Subject);
	};

	class Functions
	{
	public:
		bool fileExists(const std::string& fileName);
	};

	inline Menu menu;
	inline Game game;
	inline Functions functions;
}
