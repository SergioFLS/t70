// Copyright (c) 2017 Vadim Grigoruk @nesbox // grigoruk@gmail.com
// SPDX-License-Identifier: MIT

#include "config.h"
#include "fs.h"
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

static void readConfigVideoLength(Config* config, lua_State* lua)
{
	lua_getglobal(lua, "GIF_LENGTH");

	if(lua_isinteger(lua, -1))
		config->data.gifLength = (s32)lua_tointeger(lua, -1);

	lua_pop(lua, 1);
}

static void readConfigVideoScale(Config* config, lua_State* lua)
{
	lua_getglobal(lua, "GIF_SCALE");

	if(lua_isinteger(lua, -1))
		config->data.gifScale = (s32)lua_tointeger(lua, -1);

	lua_pop(lua, 1);
}

static void readConfigCheckNewVersion(Config* config, lua_State* lua)
{
	lua_getglobal(lua, "CHECK_NEW_VERSION");

	if(lua_isboolean(lua, -1))
		config->data.checkNewVersion = lua_toboolean(lua, -1);

	lua_pop(lua, 1);
}

static void readConfigNoSound(Config* config, lua_State* lua)
{
	lua_getglobal(lua, "NO_SOUND");

	if(lua_isboolean(lua, -1))
		config->data.noSound = lua_toboolean(lua, -1);

	lua_pop(lua, 1);
}

static void readConfigShowSync(Config* config, lua_State* lua)
{
	lua_getglobal(lua, "SHOW_SYNC");

	if(lua_isboolean(lua, -1))
		config->data.showSync = lua_toboolean(lua, -1);

	lua_pop(lua, 1);
}

static void readConfigCrtMonitor(Config* config, lua_State* lua)
{
	lua_getglobal(lua, "CRT_MONITOR");

	if(lua_isboolean(lua, -1))
		config->data.crtMonitor = lua_toboolean(lua, -1);

	lua_pop(lua, 1);
}

static void readConfigUiScale(Config* config, lua_State* lua)
{
	lua_getglobal(lua, "UI_SCALE");

	if(lua_isinteger(lua, -1))
		config->data.uiScale = lua_tointeger(lua, -1);

	lua_pop(lua, 1);
}

static void readConfigCrtShader(Config* config, lua_State* lua)
{
	lua_getglobal(lua, "CRT_SHADER");

	if(lua_isstring(lua, -1))
	{
		if(!config->data.crtShader)
			config->data.crtShader = calloc(1, sizeof(tic_code));

		strcpy((char*)config->data.crtShader, lua_tostring(lua, -1));
	}

	lua_pop(lua, 1);
}

static void readCursorTheme(Config* config, lua_State* lua)
{
	lua_getfield(lua, -1, "CURSOR");

	if(lua_type(lua, -1) == LUA_TTABLE)
	{
		{
			lua_getfield(lua, -1, "ARROW");

			if(lua_isinteger(lua, -1))
			{
				config->data.theme.cursor.arrow = (s32)lua_tointeger(lua, -1);
			}

			lua_pop(lua, 1);
		}

		{
			lua_getfield(lua, -1, "HAND");

			if(lua_isinteger(lua, -1))
			{
				config->data.theme.cursor.hand = (s32)lua_tointeger(lua, -1);
			}

			lua_pop(lua, 1);
		}

		{
			lua_getfield(lua, -1, "IBEAM");

			if(lua_isinteger(lua, -1))
			{
				config->data.theme.cursor.ibeam = (s32)lua_tointeger(lua, -1);
			}

			lua_pop(lua, 1);
		}

		{
			lua_getfield(lua, -1, "PIXEL_PERFECT");
			if(lua_isboolean(lua, -1))
				config->data.theme.cursor.pixelPerfect = lua_toboolean(lua, -1);

			lua_pop(lua, 1);			
		}
	}

	lua_pop(lua, 1);
}

static void readCodeTheme(Config* config, lua_State* lua)
{
	lua_getfield(lua, -1, "CODE");

	if(lua_type(lua, -1) == LUA_TTABLE)
	{

		static const char* Syntax[] = {"STRING", "NUMBER", "KEYWORD", "API", "COMMENT", "SIGN", "VAR", "OTHER"};

		for(s32 i = 0; i < COUNT_OF(Syntax); i++)
		{
			lua_getfield(lua, -1, Syntax[i]);

			if(lua_isinteger(lua, -1))
				((u8*)&config->data.theme.code.syntax)[i] = (u8)lua_tointeger(lua, -1);

			lua_pop(lua, 1);
		}
		
		static const char* Fields[] = {"BG", "SELECT", "CURSOR"};

		for(s32 i = 0; i < COUNT_OF(Fields); i++)
		{
			lua_getfield(lua, -1, Fields[i]);

			if(lua_isinteger(lua, -1))
				((u8*)&config->data.theme.code.bg)[i] = (u8)lua_tointeger(lua, -1);

			lua_pop(lua, 1);
		}

		{
			lua_getfield(lua, -1, "SHADOW");

			if(lua_isboolean(lua, -1))
				config->data.theme.code.shadow = lua_toboolean(lua, -1);

			lua_pop(lua, 1);
		}

		{
			lua_getfield(lua, -1, "ALT_FONT");

			if(lua_isboolean(lua, -1))
				config->data.theme.code.altFont = lua_toboolean(lua, -1);

			lua_pop(lua, 1);
		}
	}

	lua_pop(lua, 1);
}

static void readGamepadTheme(Config* config, lua_State* lua)
{
	lua_getfield(lua, -1, "GAMEPAD");

	if(lua_type(lua, -1) == LUA_TTABLE)
	{
        lua_getfield(lua, -1, "TOUCH");

		if(lua_type(lua, -1) == LUA_TTABLE)
		{
			lua_getfield(lua, -1, "ALPHA");

			if(lua_isinteger(lua, -1))
				config->data.theme.gamepad.touch.alpha = (u8)lua_tointeger(lua, -1);

			lua_pop(lua, 1);
		}

		lua_pop(lua, 1);
	}

	lua_pop(lua, 1);
}

static void readTheme(Config* config, lua_State* lua)
{
	lua_getglobal(lua, "THEME");

	if(lua_type(lua, -1) == LUA_TTABLE)
	{
		readCursorTheme(config, lua);
		readCodeTheme(config, lua);
		readGamepadTheme(config, lua);
	}

	lua_pop(lua, 1);
}

static void readConfig(Config* config)
{
	lua_State* lua = luaL_newstate();

	if(lua)
	{
		if(luaL_loadstring(lua, config->cart.bank0.code.data) == LUA_OK && lua_pcall(lua, 0, LUA_MULTRET, 0) == LUA_OK)
		{
			readConfigVideoLength(config, lua);
			readConfigVideoScale(config, lua);
			readConfigCheckNewVersion(config, lua);
			readConfigNoSound(config, lua);
			readConfigShowSync(config, lua);
			readConfigCrtMonitor(config, lua);
			readConfigUiScale(config, lua);
			readTheme(config, lua);
		}

		if(luaL_loadstring(lua, config->cart.bank1.code.data) == LUA_OK && lua_pcall(lua, 0, LUA_MULTRET, 0) == LUA_OK)
		{
			readConfigCrtShader(config, lua);
		}

		lua_close(lua);
	}
}

static void update(Config* config, const u8* buffer, size_t size)
{
	config->tic->api.load(&config->cart, buffer, size, true);

	readConfig(config);
	studioConfigChanged();
}

static void setDefault(Config* config)
{
	memset(&config->data, 0, sizeof(StudioConfig));

	config->data.cart = &config->cart;

	{
		static const u8 DefaultBiosZip[] = 
		{
			#include "../bin/assets/config.tic.dat"
		};

		u8* embedBios = NULL;
		s32 size = unzip((u8**)&embedBios, DefaultBiosZip, sizeof DefaultBiosZip);

		if(embedBios)
		{
			update(config, embedBios, size);

			free(embedBios);
		}
	}
}

static void saveConfig(Config* config, bool overwrite)
{
	u8* buffer = malloc(sizeof(tic_cartridge));

	if(buffer)
	{
		s32 size = config->tic->api.save(&config->cart, buffer);

		fsSaveRootFile(config->fs, CONFIG_TIC_PATH, buffer, size, overwrite);

		free(buffer);
	}
}

static void reset(Config* config)
{
	setDefault(config);
	saveConfig(config, true);
}

static void save(Config* config)
{
	memcpy(&config->cart, &config->tic->cart, sizeof(tic_cartridge));
	readConfig(config);
	saveConfig(config, true);

	studioConfigChanged();
}

void initConfig(Config* config, tic_mem* tic, FileSystem* fs)
{
	{
		config->tic = tic;
		config->save = save;
		config->reset = reset;
		config->fs = fs;
	}

	setDefault(config);

	s32 size = 0;
	u8* data = (u8*)fsLoadRootFile(fs, CONFIG_TIC_PATH, &size);

	if(data)
	{
		update(config, data, size);

		free(data);
	}
	else saveConfig(config, false);

	tic->api.reset(tic);
}
