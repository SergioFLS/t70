// Copyright (c) 2017 Vadim Grigoruk @nesbox // grigoruk@gmail.com
// SPDX-License-Identifier: MIT

#pragma once

#include "studio.h"

typedef struct Surf Surf;

struct Surf
{
	tic_mem* tic;
	struct FileSystem* fs;
	struct Console* console;
	struct Movie* state;

	bool init;
	s32 ticks;

	struct
	{
		s32 pos;
		s32 anim;
		struct MenuItem* items;
		s32 count;
	} menu;

	void(*tick)(Surf* surf);
	void(*resume)(Surf* surf);
};

void initSurf(Surf* surf, tic_mem* tic, struct Console* console);
