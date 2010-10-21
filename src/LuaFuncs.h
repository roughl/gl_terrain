// LuaFuncs.h


#ifndef __LUAFUNCS_H
#define __LUAFUNCS_H


#include <lua.hpp>
#include "main.h"
lua_State *init_lua(const char *InitScript);
int lua_LoadConfig (lua_State *L, Config *config);
const char *lua_GetString(lua_State *L, const char *name);
double lua_GetNumber(lua_State *L, const char *name);
double lua_GetNumber(lua_State *L, const char *name, bool *ok);
int lua_GetGlobal(lua_State *L, const char *name, int type, void *destination);
#endif // __LUAFUNCS_H
