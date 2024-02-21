/*
	Copyright (c) 2024 Mark Narain Enzinger

	MIT License (https://github.com/marknarain/grint/blob/main/LICENSE)
*/

#include "grint.h"

/// <summary>
/// This function compares two grints
/// </summary>
/// <param name="x">First parameter for comparison</param>
/// <param name="y">Second parameter for comparison</param>
/// <returns>Returns a value &gt;0 if the first parameter is bigger than the second, &lt;0 if the second one is bigger and 0 if they are same</returns>
int grint_cmp(grint x, grint y)
{
	//If x and y have a different sign, we don't need to compare the numbers and can return immediately.
	if (x->sign != y->sign)
	{
		if (x->sign < y->sign)
		{
			return -1;
		}
		else
		{
			return 1;
		}
	}

	//exchange x and y if both are negative -> -90, -80 -> here '8' is bigger than '9' and a longer number is smaller than the shorter.
	if (x->sign == -1)
	{
		grint temp = x;
		x = y;
		y = temp;
	}

	unsigned long lenX = x->lenNumber;
	unsigned long lenY = y->lenNumber;


	//Now we now that both have the same sign.
	if (lenX != lenY)
	{
		return lenX - lenY;
	}

	//Now we now that both numbers have the same number of digits, let us compare all of them till we find a diffrence
	//We start with the last entry, because that one has the highest value


	int cmpValue;

	while (lenX)
	{
		lenX--;
		cmpValue = x->pData[lenX] - y->pData[lenX];
		if (cmpValue != 0)
		{
			return cmpValue;
		}
	}
	return 0;
}

/// <summary>
/// Adds two grints and writes the result into the first parameter.
/// </summary>
/// <param name="sum">: The result is written into 'sum'</param>
/// <param name="x">: First addend</param>
/// <param name="y">: Second addend</param>
/// <returns>Returns an error code if an error occours, otherwise 0</returns>
int grint_add(grint sum, grint x, grint y)
{
	//if one is negative and the other is positive grint_sub is called
	if ((x->sign + y->sign) == 0)
	{
		int err;

		if (x->sign == -1)
		{
			x->sign = 1;
			err = grint_sub(sum, y, x);
			x->sign = -1;
		}
		else
		{
			y->sign = 1;
			err = grint_sub(sum, x, y);
			y->sign = -1;
		}

		return err;
	}

	//The grints are exchanged in case the first one is longer than the second one, because this is needed for the further adding process.
	if (x->lenNumber < y->lenNumber)
	{
		grint xTemp = x;
		x = y;
		y = xTemp;
	}

	unsigned long lenX = x->lenNumber;
	unsigned long lenY = y->lenNumber;

	sum->sign = 1;
	sum->lenNumber = x->lenNumber;

	char* xData = x->pData;
	char* yData = y->pData;

	int newLen = 0;
	char* pDst = sum->pData;

	if ((lenX + 1) > sum->lenData)
	{
		// we need more memory ... increase size of pDst
		newLen = sum->lenData + DIGIT_BLOCKSIZE;

		pDst = (char*)malloc(newLen * sizeof(char));
		if (sum->pData == 0)
		{
			return GRINT_ERR_OUTOFMEM;
		}

		sum->lenData += DIGIT_BLOCKSIZE;
	}
	else
	{
		// requirement for sum is less than 1/2 of available memory, reallocate to reduce memory consumption
		if ((lenX + 1) < (sum->lenData / 2) && (sum->lenData / 2) > 1000)
		{
			newLen = sum->lenData / 2;

			pDst = (char*)malloc(newLen * sizeof(char));
			if (sum->pData == 0)
			{
				return GRINT_ERR_OUTOFMEM;
			}

			sum->lenData /= 2;
		}
	}

	int transfer = 0;
	char writeDigit;
	int addSol;
	unsigned long i = 0;

	//First the digits are added until all digits of the shorter number have been added to the first ones of the longer.
	while (i < lenY)
	{
		addSol = transfer + (int)xData[i] + (int)yData[i];

		writeDigit = (char)(addSol % 10);

		pDst[i] = writeDigit;
		transfer = addSol / 10;

		i++;
	}

	//Now that the shorter number has been added we continue using the transfer and the digits of the longer number.
	while (i < lenX)
	{
		addSol = transfer + (int)xData[i];

		writeDigit = (char)(addSol % 10);

		pDst[i] = writeDigit;
		transfer = addSol / 10;

		i++;
	}

	//If there is still transfer, we need an extra digit...
	if (transfer != 0)
	{
		pDst[i] = transfer;
		sum->lenNumber++;
	}

	//If both numbers were negative, the solution also needs to be negative.
	if ((x->sign == -1) && (y->sign == -1))
	{
		sum->sign = -1;
	}

	//In case the lenData of the sum was changed we need to write the solution into the grint sum
	if (newLen)
	{
		free(sum->pData);
		sum->lenData = newLen;
		sum->pData = pDst;
	}

	return 0;
}

/// <summary>
/// Subtracts one grint from another and writes the result into the first parameter 'difference'.
/// </summary>
/// <param name="difference">: As the name says: the difference between the two grints (x and y)</param>
/// <param name="x">: The minuend</param>
/// <param name="y">: The subtrahend</param>
/// <returns>Returns an error code if an error occours, otherwise 0</returns>
int grint_sub(grint difference, grint x, grint y)
{
	//In certain cases it is easier to do the subtraction in a addition by changing the sign.
	if ((x->sign + y->sign) <= 0)
	{
		int err;

		if ((x->sign + y->sign) == -2)
		{
			y->sign = 1;
			err = grint_add(difference, x, y);
			y->sign = -1;
		}
		else if (x->sign == -1)
		{
			y->sign = -1;
			err = grint_add(difference, x, y);
			y->sign = 1;
		}
		else
		{
			x->sign = 1;
			err = grint_add(difference, x, y);
			x->sign = -1;
		}

		return err;
	}

	difference->sign = 1;

	//if the result will be smaller than 1, x and y are switched. (Because for example: -12 + 3 = -9 and 3 - 12 = -9)
	if ((x->lenNumber < y->lenNumber) || (x->lenNumber == y->lenNumber) && (grint_cmp(x, y) < 0))
	{
		difference->sign = -1;
		grint xTemp = x;
		x = y;
		y = xTemp;
	}

	//If y = 0 then there is no difference.
	if (y->pData[0] == 0 && y->lenNumber == 1)
	{
		grint_copy(x, difference);
		return 0;
	}

	difference->lenNumber = x->lenNumber;

	unsigned long lenX = x->lenNumber;
	unsigned long lenY = y->lenNumber;
	char* xData = x->pData;
	char* yData = y->pData;

	int transfer = 0;
	char writeDigit;
	int subSol;
	unsigned long i = 0;

	//First the digits are subtracted until all digits of the shorter number have been subtracted from first ones of the longer.
	while (i < lenY)
	{
		subSol = (int)xData[i] + 10 - (int)yData[i] + transfer;

		writeDigit = (char)(subSol % 10);

		if (writeDigit < 0)
		{
			writeDigit *= -1;
		}

		difference->pData[i] = writeDigit;
		transfer = subSol / 10 - 1;

		i++;
	}

	//Now that the shorter number has been subtracted we continue using the transfer and the digits of the longer number.
	while (i < lenX)
	{
		subSol = (int)xData[i] + transfer;

		writeDigit = (char)(subSol % 10);

		difference->pData[i] = writeDigit;
		transfer = subSol / 10;

		i++;
	}

	//If the subtraction caused digits to get freed, the len needs to get shortened
	while (difference->pData[i - 1] == 0 && difference->lenNumber > 1)
	{
		difference->lenNumber--;
		i--;
	}

	return 0;
}

/// <summary>
/// Multiplies two grints with each other and writes the solution into the first parameter.
/// </summary>
/// <param name="product">: The solution is written into here.</param>
/// <param name="x">: The multiplicand</param>
/// <param name="y">: The multiplier</param>
/// <returns>Returns an error code if an error occurs, otherwise 0</returns>
int grint_mul(grint product, grint x, grint y)
{
	const unsigned long lenX = x->lenNumber;
	const unsigned long lenY = y->lenNumber;
	const unsigned long lenRes = lenX + lenY;

	int newLen = 0;
	char* pDst = product->pData;
	if (pDst == 0)
	{
		return GRINT_ERR_OUTOFMEM;
	}

	//If either the multiplier or the multiplicand has the same address as the product, a temporary array has to be allocated for the solution to not destroy x or y.
	if (product == x || product == y)
	{
		newLen = product->lenData;
		pDst = (char*)malloc(newLen * sizeof(char));
		if (pDst == 0)
		{
			return GRINT_ERR_OUTOFMEM;
		}
	}

	if (lenRes > product->lenData)
	{
		if (newLen != 0)
		{
			free(pDst);
		}

		// we need more memory ... increase size of pDst
		newLen = lenRes + DIGIT_BLOCKSIZE;

		pDst = (char*)malloc(newLen * sizeof(char));
		if (pDst == 0)
		{
			return GRINT_ERR_OUTOFMEM;
		}

		product->lenData = newLen;
	}

	// requirement for sum is less than 1/2 of available memory, reallocate to reduce memory consumption
	if (lenRes < (product->lenData / 2) && (product->lenData / 2) > DIGIT_BLOCKSIZE)
	{
		newLen = product->lenData / 2;

		pDst = (char*)malloc(newLen * sizeof(char));
		if (pDst == 0)
		{
			return GRINT_ERR_OUTOFMEM;
		}

		product->lenData /= 2;
	}


	product->sign = 1;
	int transfer = 0;
	char writeDigit;
	int mulSol;
	int mulAdd = 0;
	product->lenNumber = 0;

	memset(pDst, 0, (size_t)lenRes);

	//check if either x or y are 0
	if 
	(
		(x->lenNumber == 1 && x->pData[0] == 0)		//x == 0
		|| 
		(y->lenNumber == 1 && y->pData[0] == 0)		//y == 0
	)
	{
		pDst[0] = 0;
		product->lenNumber = 1;
		return GRINT_OK;
	}

	//length of result can only be lenRes or lenRes-1, assume the second case and fix it later incase we see, we also need the last digit
	product->lenNumber = lenRes - 1;

	for (unsigned long a = 0; a < lenY; a++)
	{
		unsigned long b = 0;
		transfer = 0;

		while (b < lenX)
		{
			mulSol = (y->pData[a] * x->pData[b]) + pDst[b + a] + transfer;
			writeDigit = mulSol % 10;

			pDst[b + a] = writeDigit;

			transfer = mulSol / 10;

			b++;
		}

		
		if (transfer != 0)
		{
			pDst[b + a] += transfer;
			if (a == (lenY - 1))
			{
				product->lenNumber++;
			}
			transfer = 0;
		}
	}

	if ((x->sign + y->sign) == 0)
	{
		product->sign = -1;
	}

	int i = 1;

	if (newLen)
	{
		free(product->pData);
		product->pData = pDst;
	}

	return 0;
}

/// <summary>
/// Divides one grint by another and writes the solution into the first parameter.
/// </summary>
/// <param name="quotient">: The solution is written into here.</param>
/// <param name="x">: The dividend</param>
/// <param name="y">: The divisor</param>
/// <returns>Returns an error code if an error occurs, otherwise 0</returns>
int grint_div(grint quotient, grint x, grint y)
{
	int err = 0;
	unsigned long lenX = x->lenNumber;
	unsigned long lenY = y->lenNumber;
	//both signs are stored, because they are changed in the process of division and need to be changed back at the end.
	int xSign = x->sign;
	int ySign = y->sign;

	grint quotientTemp = grint_from_int(0);
	
	quotient->sign = 1;
	//If x->sign + y->sign = 0 --> one of them is 1 and the other -1
	if ((x->sign + y->sign) == 0)
	{
		quotientTemp->sign = -1;
	}

	//both signs are changed, to make enable the program to compare without the signs.
	x->sign = 1;
	y->sign = 1;

	quotientTemp->lenNumber = 1;

	//check if y->pData is 0 --> division by 0 isn't possible.
	if (y->pData[0] == 0 && y->lenNumber == 1)
	{
		return GRINT_ERR_DIV0;
	}

	//If the divisor is bigger than the dividend, the result of the division is 0.
	if (lenY > lenX)
	{
		quotientTemp->pData[0] = 0;
		quotientTemp->lenNumber = 1;
		return 0;
	}

	grint doublingNumber = grint_from_int(0);
	grint temp = grint_from_int(0);
	//y is saved in temp, so that it can get changed during the process and doesn't get destroyed.
	grint_copy(y, doublingNumber);
	grint counter = grint_from_int(1);

	//While doublingNumber is smaller or equal to x, it keeps getting doubled. Temp also gets doubled.
	while (grint_cmp(x, doublingNumber) >= 0)
	{
		err = grint_add(temp, doublingNumber, doublingNumber);
		doublingNumber = grint_make_next(doublingNumber, temp);

		err = grint_add(temp, counter, counter);
		counter = grint_make_next(counter, temp);
	}

	//x gets saved to temp, so that it can get changed.
	grint_copy(x, temp);

	//as soon as doublingNumber gets bigger than x, the previous doubled number (/2) is subtracted from temp. This happens untill temp == 0.
	while (counter->prev != 0)
	{
		counter = clear_get_prev(counter);
		doublingNumber = clear_get_prev(doublingNumber);

		if (grint_cmp(doublingNumber, temp) <= 0)
		{
			err = grint_sub(temp, temp, doublingNumber);

			err = grint_add(quotientTemp, quotientTemp, counter);
		}
	}

	if (quotientTemp->pData[lenX - lenY] == 0 && quotientTemp->lenNumber > 1)
	{
		quotientTemp->lenNumber--;
	}

	grint_copy(quotientTemp, quotient);
	grint_clear(quotientTemp);

	x->sign = xSign;
	y->sign = ySign;

	return err;
}