// Copyright (c) 2017 Vadim Grigoruk @nesbox // grigoruk@gmail.com
// SPDX-License-Identifier: MIT

#pragma once

#include "studio.h"

typedef struct Map Map;

struct Map
{
	tic_mem* tic;

	tic_map* src;
	
	s32 tickCounter;

	enum
	{
		MAP_DRAW_MODE = 0,
		MAP_DRAG_MODE,
		MAP_SELECT_MODE,
		MAP_FILL_MODE,
	} mode;

	struct
	{
		bool grid;
		bool draw;
		tic_point start;
	} canvas;

	struct
	{
		bool show;
		tic_rect rect;
		tic_point start;
		bool drag;
	} sheet;

	struct
	{
		s32 x;
		s32 y;

		tic_point start;

		bool active;
		bool gesture;

	} scroll;

	struct
	{
		tic_rect rect;
		tic_point start;
		bool drag;
	} select;

	u8* paste;

	struct History* history;

	void (*tick)(Map*);
	void (*event)(Map*, StudioEvent);
	void (*scanline)(tic_mem* tic, s32 row, void* data);
	void (*overline)(tic_mem* tic, void* data);
};

void initMap(Map*, tic_mem*, tic_map* src);
