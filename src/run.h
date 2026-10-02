// Copyright (c) 2017 Vadim Grigoruk @nesbox // grigoruk@gmail.com
// SPDX-License-Identifier: MIT

#pragma once

#include "studio.h"

typedef struct Run Run;

struct Run
{
	tic_mem* tic;
	struct Console* console;
	tic_tick_data tickData;

	bool exit;
	
	tic_persistent persistent;
	char saveid[TIC_SAVEID_SIZE];

	void(*tick)(Run*);
};

void initRun(Run*, struct Console*, tic_mem*);
