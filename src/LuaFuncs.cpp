// Lua.c
#include <stdlib.h>
#include <lua.hpp>
#include "LuaFuncs.h"
#include "main.h"
bool init_lua(lua_State *L, const char *InitScript)
{
	printf("luaL_Loadfile(L, %s)", InitScript);
	int s = luaL_loadfile(L, InitScript); 
	if ( s==0 )
	{
		printf("execute Lua script\n");
		// execute Lua program or script
		s = lua_pcall(L, 0, LUA_MULTRET, 0);
		return true;
	}
	else
	{
		printf("ERROR: %s nicht gefunden\n", InitScript);
		return false;
	}
}



const char *lua_GetString(lua_State *L, const char *name)
{
    lua_getglobal(L, name);
    return lua_tostring(L, -1);
}

double lua_GetNumber(lua_State *L, const char *name)
{
    lua_getglobal(L, name);
    return lua_tonumber(L, -1);    
}

double lua_GetNumber(lua_State *L, const char *name, bool *ok)
{
    lua_getglobal(L, name);
    if(lua_isnumber(L, -1))
    {
        *ok=true;
        return lua_tonumber(L, -1);
    }
    *ok=false;
    return 0.0;
}

int lua_GetGlobal(lua_State *L, const char *name, int type, void *destination)
{
	lua_getglobal(L, name);
	switch( type )
	{
	case LUA_TNUMBER:
		*(double *)destination=lua_tonumber(L, -1);
		return 1;
	case LUA_TBOOLEAN:
		*(bool *)destination=lua_toboolean(L, -1);
		return 1;
	case LUA_TSTRING:
		destination = (void *) lua_tostring(L, -1);
		return 1;
	case LUA_TNONE:
	case LUA_TTABLE:
	case LUA_TFUNCTION:
	case LUA_TUSERDATA:
	case LUA_TTHREAD:
	case LUA_TLIGHTUSERDATA:
	case LUA_TNIL:
	default:
		return 0;
	}
}


int lua_LoadConfig (lua_State *L, Config *config)
{
    int state=0;
    
    lua_getglobal(L, "width"); /* load global variable width in stack*/
    if (!lua_isnumber(L, -1))
    {
       printf("ERROR while loading width: Parameter should be Number\n");
       /*   error(L, "`height' should be a number\n");  */
       state=4;
    }
    else
    {
         config->width = (int)lua_tonumber(L, -1); /* get height from stack*/
    }
    
    lua_getglobal(L, "height"); /* load global variable height in stack*/
    if (!lua_isnumber(L, -1)) /* is it a number?*/
    {
       printf("ERROR while loading height: Parameter should be Number\n");
          /* error(L, "`width' should be a number\n");*/
       state=3;
    }
    else
    {
        config->height = (int)lua_tonumber(L, -1);/* // get buffer_width from stack*/
    }
    
    lua_getglobal(L, "fullscreen"); /* load global variable width in stack*/
    if (!lua_isnumber(L, -1))
    {
       printf("ERROR while loading fullscreen: Parameter should be number\n");
       /*   error(L, "`height' should be a number\n");    */ 
       state=2;
    }
    else
    {
         config->fullscreen = (int)lua_tonumber(L, -1); /* get fullscreen from stack*/
    }
    
    lua_getglobal(L, "TerrainFilename");
    if (!lua_isstring(L, -1))
    {
        printf("Warning TerrainFilename does not exist choose default value\n");
        config->TerrainFilename="Lua/terrainconfig.lua";
        state=1;
    }
    else
    {
        config->TerrainFilename = lua_tostring(L, -1);
    }
    
  /*  lua_getglobal(L, "map");
    if (!lua_isstring(L, -1))
    {
       printf("ERROR while loading map: Parameter should be String\n");
       state=1;
    }
    else
    {
        config->map = lua_tostring(L, -1);
    }*/
    
    return state;
}
