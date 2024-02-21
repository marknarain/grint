/*
    Copyright (c) 2024 Mark Narain Enzinger

    MIT License (https://github.com/marknarain/grint/blob/main/LICENSE)
*/

#pragma once
#include "grint-types.h"

int grint_cmp(grint x, grint y);

int grint_add(grint sum, grint summand1, grint summand2);

int grint_sub(grint difference, grint minuend, grint subtrahend1);

int grint_mul(grint product, grint x, grint y);

int grint_div(grint quotient, grint x, grint y);