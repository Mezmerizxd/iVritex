/*
Code from: https://www.unknowncheats.me/forum/members/263636.html (AceStryker)
*/
#include <Windows.h>
#include <stdio.h>

extern "C"
{
	#include "lauxlib.h"
	#include "lua.h"
	#include "lualib.h"
}
#pragma comment(lib, "lua53.lib")

#define CloseLUA(L)  lua_close(L)

void AddLUAFunction(lua_State* L, char* FuncName, lua_CFunction Func)
{
	lua_pushcclosure(L, Func, 0);
	lua_setglobal(L, FuncName);
}
void ExecuteLUAFunction(lua_State* L, char* FuncName)
{
	int iErr;
	if ((iErr = lua_pcall(L, 0, LUA_MULTRET, 0)) == 0)
	{
		lua_pushstring(L, "render");
		lua_gettable(L, LUA_GLOBALSINDEX);
		lua_pcall(L, 0, 0, 0);
	}
}
void ExecuteLUAFunctionWithParam(lua_State* L, char* FuncName, char* Param)
{
	lua_getglobal(L, FuncName);
	lua_pushstring(L, Param);
	lua_pcall(L, 1, 1, 0);
}
lua_State* InitLUA(char* Filename)
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	int status = luaL_loadfile(L, Filename);
	if (status) {
		printf("ERROR ON LUA CREATION: %s \n", lua_tostring(L, -1));
	}
	return L;
}

//API CALLS
static int printMessage(lua_State* L)
{
	const char* msg = lua_tostring(L, 1);
	printf(msg);
	return 0;
}

void AddAllFuncsToLUA(lua_State* L)
{
	AddLUAFunction(L, "printMessage", printMessage);
}


//FILL VARIABLES
void FillMe(lua_State* L)
{
	lua_newtable(L);
	lua_pushstring(L, "name");
	lua_pushstring(L, "AceStryker");
	lua_settable(L, -3);

	lua_pushstring(L, "hp");
	lua_pushvalue(L, 100);
	lua_settable(L, -3);

	lua_pushstring(L, "armor");
	lua_pushvalue(L, 100);
	lua_settable(L, -3);

	lua_pushstring(L, "dead");
	lua_pushvalue(L, 0);
	lua_settable(L, -3);

	lua_setglobal(L, "pLocal");

}

void FillAll(lua_State* L)
{
	FillMe(L);
}