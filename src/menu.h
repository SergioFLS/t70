// Copyright (c) 2017 Vadim Grigoruk @nesbox // grigoruk@gmail.com
// SPDX-License-Identifier: MIT

#pragma once

#include "studio.h"

typedef struct Menu Menu;

struct Menu
{
	tic_mem* tic;
	struct FileSystem* fs;

	bool init;
	void* bg;
	s32 ticks;

	struct
	{
		s32 focus;
	} main;

	struct
	{
		u32 tab;
		s32 selected;
	} gamepad;

	tic_point pos;

	struct
	{
		tic_point start;
		bool active;
	} drag;

	enum
	{
		MAIN_MENU_MODE,
		GAMEPAD_MENU_MODE,
	} mode;
	
	void(*tick)(Menu* Menu);
};

void initMenu(Menu* menu, tic_mem* tic, struct FileSystem* fs);
