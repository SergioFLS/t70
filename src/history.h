// Copyright (c) 2017 Vadim Grigoruk @nesbox // grigoruk@gmail.com
// SPDX-License-Identifier: MIT

#pragma once

#include <tic80_types.h>

typedef struct History History;

History* history_create(void* data, u32 size);
bool history_add(History* history);
void history_undo(History* history);
void history_redo(History* history);
void history_delete(History* history);