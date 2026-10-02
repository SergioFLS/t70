// Copyright (c) 2017 Vadim Grigoruk @nesbox // grigoruk@gmail.com
// SPDX-License-Identifier: MIT

#pragma once

#include "studio.h"

typedef struct Dialog Dialog;

struct Dialog
{
	tic_mem* tic;

	bool init;
	void* bg;
	DialogCallback callback;
	void* data;
	const char** text;
	s32 rows;

	u32 focus;

	tic_point pos;

	struct
	{
		tic_point start;
		bool active;
	} drag;
	
	void(*tick)(Dialog* Dialog);
	void(*escape)(Dialog* Dialog);
};

void initDialog(Dialog* dialog, tic_mem* tic, const char** text, s32 rows, DialogCallback callback, void* data);
