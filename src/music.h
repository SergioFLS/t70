// Copyright (c) 2017 Vadim Grigoruk @nesbox // grigoruk@gmail.com
// SPDX-License-Identifier: MIT

#pragma once

#include "studio.h"

typedef struct Music Music;

struct Music
{
	tic_mem* tic;

	tic_music* src;

	u8 track:MUSIC_TRACKS_BITS;

	struct
	{
		bool follow;
		s32 patternCol;

		s32 frame;
		s32 col;
		s32 row;
		s32 scroll;
		s32 note;

		struct
		{
			s32 octave;
			s32 sfx;
			s32 volume;
		} last;

		struct
		{
			tic_point start;
			tic_rect rect;
			bool drag;
		} select;

		bool patterns[TIC_SOUND_CHANNELS];

	} tracker;

	enum
	{
		MUSIC_TRACKER_TAB,
		MUSIC_PIANO_TAB,
	} tab;

	struct History* history;
	
	void(*tick)(Music*);
	void(*event)(Music*, StudioEvent);
};

void initMusic(Music*, tic_mem*, tic_music* src);