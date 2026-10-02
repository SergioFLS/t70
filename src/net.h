// Copyright (c) 2017 Vadim Grigoruk @nesbox // grigoruk@gmail.com
// SPDX-License-Identifier: MIT

#pragma once

#include "fs.h"

typedef struct Net Net;

Net* createNet();
void* netGetRequest(Net* net, const char* path, s32* size);
void closeNet(Net* net);