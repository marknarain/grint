/*
	Copyright (c) 2024 Mark Narain Enzinger

	MIT License (https://github.com/marknarain/grint/blob/main/LICENSE)
*/

#pragma once

struct grint_type
{
	int sign;
	unsigned long lenNumber;
	unsigned long lenData;
	char* pData;
	grint_type* prev;

};

typedef grint_type* grint;