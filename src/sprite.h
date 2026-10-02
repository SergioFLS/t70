// Copyright (c) 2017 Vadim Grigoruk @nesbox // grigoruk@gmail.com
// SPDX-License-Identifier: MIT

#pragma once

#include "studio.h"

typedef struct Sprite Sprite;

struct Sprite
{
	tic_mem* tic;

	tic_tiles* src;

	u32 tickCounter;

	u16 index;
	u8 color;
	u8 color2;
	u8 size;
	u8 brushSize;

	bool editPalette;

	struct
	{
		tic_rect rect;
		tic_point start;
		bool drag;
		u8* back;
		u8* front;
	}select;

	enum
	{
		SPRITE_DRAW_MODE,
		SPRITE_PICK_MODE,
		SPRITE_SELECT_MODE,
		SPRITE_FILL_MODE,
	}mode;

	struct History* history;

	void (*tick)(Sprite*);
	void (*event)(Sprite*, StudioEvent);
	void (*scanline)(tic_mem* tic, s32 row, void* data);
	void (*overline)(tic_mem* tic, void* data);
};

void initSprite(Sprite*, tic_mem*, tic_tiles* src);