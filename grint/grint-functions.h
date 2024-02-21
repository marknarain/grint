/*
    Copyright (c) 2024 Mark Narain Enzinger

    MIT License (https://github.com/marknarain/grint/blob/main/LICENSE)
*/

#pragma once
#include "grint-types.h"

grint grint_from_int(int x);

grint grint_from_string(const char* pStr);

char* grint_to_string(grint x);

int grint_copy(grint src, grint dst);

int grint_clear(grint x);

grint grint_make_next(grint x, grint y);

grint clear_get_prev(grint x);