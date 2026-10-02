// Copyright (c) 2017 Vadim Grigoruk @nesbox // grigoruk@gmail.com
// SPDX-License-Identifier: MIT

#pragma once

#include "studio.h"

typedef struct Map Map;
typedef struct World World;

struct World
{
	tic_mem* tic;
	Map* map;

	void* preview;

	void(*tick)(World* world);
};

void initWorld(World* world, tic_mem* tic, Map* map);