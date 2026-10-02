// Copyright (c) 2017 Vadim Grigoruk @nesbox // grigoruk@gmail.com
// SPDX-License-Identifier: MIT

#pragma once

#include "tic.h"

inline void tic_tool_poke4(void* addr, u32 index, u8 value)
{
	u8* val = (u8*)addr + (index >> 1);

	if(index & 1)
	{
		*val &= 0x0f;
		*val |= (value << 4);
	}
	else
	{
		*val &= 0xf0;
		*val |= value & 0x0f;
	}
}

inline u8 tic_tool_peek4(const void* addr, u32 index)
{
	u8 val = ((u8*)addr)[index >> 1];

	return index & 1 ? val >> 4 : val & 0xf;
}

bool tic_tool_parse_note(const char* noteStr, s32* note, s32* octave);
s32 tic_tool_get_pattern_id(const tic_track* track, s32 frame, s32 channel);
void tic_tool_set_pattern_id(tic_track* track, s32 frame, s32 channel, s32 id);
u32 tic_tool_find_closest_color(const tic_rgb* palette, const tic_rgb* color);
u32* tic_palette_blit(const tic_palette* src);
