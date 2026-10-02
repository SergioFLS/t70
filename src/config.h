// Copyright (c) 2017 Vadim Grigoruk @nesbox // grigoruk@gmail.com
// SPDX-License-Identifier: MIT

#pragma once

#include "studio.h"

typedef struct Config Config;

struct Config
{
	tic_mem* tic;
	struct FileSystem* fs;

	StudioConfig data;
	tic_cartridge cart;

	void(*save)(Config*);
	void(*reset)(Config*);
};

void initConfig(Config* config, tic_mem* tic, struct FileSystem* fs);