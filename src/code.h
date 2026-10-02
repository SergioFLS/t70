// Copyright (c) 2017 Vadim Grigoruk @nesbox // grigoruk@gmail.com
// SPDX-License-Identifier: MIT

#pragma once

#include "studio.h"

typedef struct Code Code;
typedef struct OutlineItem OutlineItem;

struct Code
{
	tic_mem* tic;

	char* src;

	struct
	{
		struct
		{
			char* position;
			char* selection;
			s32 column;
		};

		char* mouseDownPosition;
		s32 delay;
	} cursor;

	tic_rect rect;

	struct
	{
		s32 x;
		s32 y;

		tic_point start;

		bool active;
		bool gesture;

	} scroll;

	u8 colorBuffer[TIC_CODE_SIZE];

	char status[STUDIO_TEXT_BUFFER_WIDTH+1];

	u32 tickCounter;

	struct History* history;
	struct History* cursorHistory;

	enum
	{
		TEXT_RUN_CODE,
		TEXT_EDIT_MODE,
		TEXT_FIND_MODE,
		TEXT_GOTO_MODE,
		TEXT_OUTLINE_MODE,
	} mode;

	struct
	{
		char text[STUDIO_TEXT_BUFFER_WIDTH - sizeof "FIND:"];

		char* prevPos;
		char* prevSel;
	} popup;

	struct
	{
		s32 line;
	} jump;

	struct
	{
		OutlineItem* items;

		s32 index;
	} outline;

	bool altFont;

	void(*tick)(Code*);
	void(*escape)(Code*);
	void(*event)(Code*, StudioEvent);
	void(*update)(Code*);
};

void initCode(Code*, tic_mem*, tic_code* src);
