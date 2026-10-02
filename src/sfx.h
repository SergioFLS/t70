// Copyright (c) 2017 Vadim Grigoruk @nesbox // grigoruk@gmail.com
// SPDX-License-Identifier: MIT

#pragma once

#include "studio.h"

typedef struct Sfx Sfx;

struct Sfx
{
	tic_mem* tic;

	tic_sfx* src;

	u8 index:SFX_COUNT_BITS;

	struct
	{
		bool active;
		s32 note;
	} play;
	
	enum 
	{
		SFX_WAVE_TAB = 0,
		SFX_VOLUME_TAB,
		SFX_ARPEGGIO_TAB,
		SFX_PITCH_TAB,
	}canvasTab;

	struct
	{
		u8 index:4;
	} waveform;

	enum
	{
		SFX_WAVEFORM_TAB, 
		SFX_ENVELOPES_TAB,
	} tab;

	struct History* history;

	void(*tick)(Sfx*);
	void(*event)(Sfx*, StudioEvent);
};

void initSfx(Sfx*, tic_mem*, tic_sfx* src);