/*
	Copyright (c) 2024 Mark Narain Enzinger

	MIT License (https://github.com/marknarain/grint/blob/main/LICENSE)
*/

#include "grint.h"

/// <summary>
/// Generates a grint from an integer value.
/// </summary>
/// <param name="x">: Integer to be converted to a grint</param>
/// <returns>Returns a pointer to the generated grint</returns>
grint grint_from_int(int x)
{
	grint pBig;
	pBig = (grint)malloc(sizeof(grint_type));
	if (pBig == 0)
	{
		return 0;
	}

	pBig->sign = 1;

	if (x < 0)
	{
		pBig->sign = -1;
		x *= -1;
	}

	int x2 = x;

	pBig->pData = (char*)malloc(DIGIT_BLOCKSIZE * sizeof(char));
	if (pBig->pData == 0)
	{
		return 0;
	}

	pBig->lenData = DIGIT_BLOCKSIZE;

	int len = 0;

	for (int xTemp = x; xTemp > 0; len++, xTemp /= 10);

	pBig->lenNumber = len;

	char* pData = pBig->pData;

	if (x == 0)
	{
		*pData = 0;
		pBig->lenNumber = 1;
	}

	while (x > 0)
	{
		*pData++ = (x % 10);
		x = x / 10;
	}

	pBig->prev = 0;

	return pBig;
}

/// <summary>
/// Generates a grint from a string
/// </summary>
/// <param name="pStr">: A pointer to the string that should be written into the grint</param>
/// <returns>Returns a pointer to the generated grint</returns>
grint grint_from_string(const char* pStr)
{
	grint pBig;
	pBig = (grint)malloc(sizeof(grint_type));
	if (pBig == 0)
	{
		return 0;
	}

	pBig->pData = (char*)malloc(DIGIT_BLOCKSIZE * sizeof(char));
	if (pBig->pData == 0)
	{
		return 0;
	}

	int stringLen = strlen(pStr);
	char* pData = pBig->pData;
	pBig->lenNumber = stringLen;
	pBig->lenData = DIGIT_BLOCKSIZE;
	pBig->prev = 0;

	int negative = 0;
	pBig->sign = 1;
	if (pStr[0] == '-')
	{
		pBig->sign = -1;
		pBig->lenNumber--;
		negative = 1;
	}

	//>= negative, because if the first element of the string = '-', we dont want to put it in our grint
	for (int i = 0; (stringLen - (i + 1)) >= negative; i++)
	{
		pData[i] = pStr[stringLen - (i + 1)] - '1' + 1;
	}

	return pBig;
}

/// <summary>
/// Converts a grint into a string
/// </summary>
/// <param name="x">: The grint, which is supposed to be converted to a string</param>
/// <returns>Returns a pointer, pointing to the string created</returns>
char* grint_to_string(grint x)
{
	int grintLen = x->lenNumber;
	int sign = 0; //set to zero because the offset created by the '-' symbol doesnt exist when positive
	if (x->sign == -1)
	{
		sign = 1; //offset for the loop is one and we have to allocate 1 char more
	}

	char* pStr = (char*)malloc((x->lenNumber + sign + 1) * sizeof(char));
	if (pStr == 0)
	{
		return 0;
	}

	pStr[x->lenNumber + sign] = 0;

	if (sign)
	{
		pStr[0] = '-';
	}

	for (int i = 0; (grintLen - (i + 1)) >= 0; i++)
	{
		pStr[i + sign] = x->pData[grintLen - (i + 1)] + 48;
	}

	return pStr;
}

/// <summary>
/// Frees all memory of a grint and clears it
/// </summary>
/// <param name="x">: The grint to be cleared</param>
/// <returns>Returns an error code if an error occours, otherwise 0</returns>
int grint_clear(grint x)
{
	free(x->pData);
	free(x);

	return 0;
}

/// <summary>
/// Copies a grint from a source grint to a destination grint.
/// </summary>
/// <param name="src">: The source from where to copy</param>
/// <param name="dst">: The destination where to write</param>
/// <returns>Returns an error code if an error occours, otherwise 0</returns>
int grint_copy(grint src, grint dst)
{
	if (src->lenData != dst->lenData)
	{
		free(dst->pData);
		dst->pData = (char*)malloc(src->lenData * sizeof(char));
		dst->lenData = src->lenData;
		if (dst->pData == 0)
		{
			return GRINT_ERR_OUTOFMEM;
		}
	}
	memcpy_s(dst->pData, dst->lenData, src->pData, src->lenData);
	dst->sign = src->sign;
	dst->lenNumber = src->lenNumber;

	return 0;
}

/// <summary>
/// Makes a new grint which holds the pointer to a previous one.
/// </summary>
/// <param name="x">: Is the old grint.</param>
/// <param name="y">: Is the new grint that holds the old grints pointer</param>
/// <returns>Returns a pointer to the next grint</returns>
grint grint_make_next(grint x, grint y)
{
	grint next = grint_from_int(0);

	next->prev = x;

	grint_copy(y, next);

	return next;
}

/// <summary>
/// Clears a grint and returns a pointer to the previous
/// </summary>
/// <param name="x">: The grint referring to</param>
/// <returns>Returns the address inside the 'prev' and clears the given x</returns>
grint clear_get_prev(grint x)
{
	grint prev = x->prev;
	grint_clear(x);

	return prev;
}

