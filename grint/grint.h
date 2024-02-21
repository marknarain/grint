/*
    Copyright (c) 2024 Mark Narain Enzinger

    MIT License (https://github.com/marknarain/grint/blob/main/LICENSE)
*/

#pragma once
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "grint-arithmetic.h"
#include "grint-functions.h"
#include "grint-types.h"

#define DIGIT_BLOCKSIZE		1000ul

#define GRINT_OK			0 
#define GRINT_ERR_OUTOFMEM	1
#define GRINT_ERR_DIV0		2
#define GRINT_PREV_NULL		3
#define GRINT_ERR_COPY_SIZE 4