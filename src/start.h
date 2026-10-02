// Copyright (c) 2017 Vadim Grigoruk @nesbox // grigoruk@gmail.com
// SPDX-License-Identifier: MIT

#pragma once

#include "studio.h"

typedef struct Start Start;

struct Start
{
	tic_mem* tic;

	bool initialized;

	u32 phase;
	u32 ticks;
	bool play;

	void (*tick)(Start*);
};

void initStart(Start* start, tic_mem* tic);