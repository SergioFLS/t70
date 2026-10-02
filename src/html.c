// Copyright (c) 2017 Vadim Grigoruk @nesbox // grigoruk@gmail.com
// SPDX-License-Identifier: MIT

#include <tic80_types.h>

const u8 EmbedIndexZip[] = 
{
	#include "../bin/assets/index.html.dat"
};

const s32 EmbedIndexZipSize = sizeof EmbedIndexZip;

const u8 EmbedTicJsZip[] = 
{
	#include "../bin/assets/tic.js.dat"
};

const s32 EmbedTicJsZipSize = sizeof EmbedTicJsZip;
