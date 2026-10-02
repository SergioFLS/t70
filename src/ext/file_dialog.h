// Copyright (c) 2017 Vadim Grigoruk @nesbox // grigoruk@gmail.com
// SPDX-License-Identifier: MIT

#pragma once

#include <tic80_types.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void(*file_dialog_load_callback)(const char* name, const u8* buffer, s32 size, void* data, u32 mode);
typedef void(*file_dialog_save_callback)(bool result, void* data);

void file_dialog_load(file_dialog_load_callback callback, void* data);
void file_dialog_save(file_dialog_save_callback callback, const char* name, const u8* buffer, size_t size, void* data, u32 mode);

#ifdef __cplusplus
}
#endif