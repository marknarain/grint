/*
	Copyright (c) 2024 Mark Narain Enzinger

	MIT License (https://github.com/marknarain/grint/blob/main/LICENSE)
*/

#include "pch.h"
#include "CppUnitTest.h"
#include "../grint/grint.h"

//(char(*)[10])y->pData -> syntax to show a pointer in the watch window as array of characters

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BigNumberTests
{
	TEST_CLASS(bigIntCrTests)
	{
	public:

		TEST_METHOD(bigIntCrTest1)
		{

			grint myBigInt = grint_from_int(12345);

			Assert::AreEqual(5ul, myBigInt->lenNumber);
			Assert::AreEqual(1, myBigInt->sign);

			Assert::AreEqual((char)5, myBigInt->pData[0]);
			Assert::AreEqual((char)4, myBigInt->pData[1]);
			Assert::AreEqual((char)3, myBigInt->pData[2]);
			Assert::AreEqual((char)2, myBigInt->pData[3]);
			Assert::AreEqual((char)1, myBigInt->pData[4]);
		}

		TEST_METHOD(bigIntCrTest2)
		{
			grint myBigInt = grint_from_int(0);

			Assert::AreEqual(1ul, myBigInt->lenNumber);
			Assert::AreEqual(1, myBigInt->sign);

			Assert::AreEqual((char)0, myBigInt->pData[0]);
		}

		TEST_METHOD(bigIntCrTest3)
		{
			grint myBigInt = grint_from_int(-123);

			Assert::AreEqual(3ul, myBigInt->lenNumber);
			Assert::AreEqual(-1, myBigInt->sign);

			Assert::AreEqual((char)3, myBigInt->pData[0]);
			Assert::AreEqual((char)2, myBigInt->pData[1]);
			Assert::AreEqual((char)1, myBigInt->pData[2]);
		}
	};

	TEST_CLASS(copyTests)
	{
	public:

		TEST_METHOD(copyTest1)
		{
			grint myBigInt1 = grint_from_int(1234);
			grint myBigInt2 = grint_from_int(3716);

			grint_copy(myBigInt1, myBigInt2);

			myBigInt1->sign = myBigInt2->sign;
			myBigInt1->lenNumber = myBigInt2->lenNumber;
			myBigInt1->lenData = myBigInt2->lenData;

			Assert::AreEqual((char)4, myBigInt1->pData[0]);
			Assert::AreEqual((char)3, myBigInt1->pData[1]);
			Assert::AreEqual((char)2, myBigInt1->pData[2]);
			Assert::AreEqual((char)1, myBigInt1->pData[3]);
		}

		TEST_METHOD(copyTest2)
		{
			grint myBigInt1 = grint_from_int(1234);
			grint myBigInt2 = grint_from_int(716);

			grint_copy(myBigInt1, myBigInt2);

			myBigInt1->sign = myBigInt2->sign;
			myBigInt1->lenNumber = myBigInt2->lenNumber;
			myBigInt1->lenData = myBigInt2->lenData;

			Assert::AreEqual((char)4, myBigInt1->pData[0]);
			Assert::AreEqual((char)3, myBigInt1->pData[1]);
			Assert::AreEqual((char)2, myBigInt1->pData[2]);
			Assert::AreEqual((char)1, myBigInt1->pData[3]);
		}
	};

	TEST_CLASS(cmpTests)
	{
	public:

		TEST_METHOD(cmpTest1)
		{
			grint myBigInt1 = grint_from_int(1234);
			grint myBigInt2 = grint_from_int(-123);

			int compared = grint_cmp(myBigInt1, myBigInt2);

			Assert::IsTrue(compared > 0);
		}

		TEST_METHOD(cmpTest2)
		{
			grint myBigInt1 = grint_from_int(-1234);
			grint myBigInt2 = grint_from_int(123);

			int compared = grint_cmp(myBigInt1, myBigInt2);

			Assert::IsTrue(compared < 0);
		}

		TEST_METHOD(cmpTest3)
		{
			grint myBigInt1 = grint_from_int(1234);
			grint myBigInt2 = grint_from_int(123);

			int compared = grint_cmp(myBigInt1, myBigInt2);

			Assert::IsTrue(compared > 0);
		}

		TEST_METHOD(cmpTest4)
		{
			grint myBigInt1 = grint_from_int(-1234);
			grint myBigInt2 = grint_from_int(-123);

			int compared = grint_cmp(myBigInt1, myBigInt2);

			Assert::IsTrue(compared < 0);
		}

		TEST_METHOD(cmpTest5)
		{
			grint myBigInt1 = grint_from_int(123);
			grint myBigInt2 = grint_from_int(-1234);

			int compared = grint_cmp(myBigInt1, myBigInt2);

			Assert::IsTrue(compared > 0);
		}

		TEST_METHOD(cmpTest6)
		{
			grint myBigInt1 = grint_from_int(-123);
			grint myBigInt2 = grint_from_int(1234);

			int compared = grint_cmp(myBigInt1, myBigInt2);

			Assert::IsTrue(compared < 0);
		}

		TEST_METHOD(cmpTest7)
		{
			grint myBigInt1 = grint_from_int(123);
			grint myBigInt2 = grint_from_int(1234);

			int compared = grint_cmp(myBigInt1, myBigInt2);

			Assert::IsTrue(compared < 0);
		}

		TEST_METHOD(cmpTest8)
		{
			grint myBigInt1 = grint_from_int(1235);
			grint myBigInt2 = grint_from_int(-1234);

			int compared = grint_cmp(myBigInt1, myBigInt2);

			Assert::IsTrue(compared > 0);
		}

		TEST_METHOD(cmpTest9)
		{
			grint myBigInt1 = grint_from_int(1233);
			grint myBigInt2 = grint_from_int(-1234);

			int compared = grint_cmp(myBigInt1, myBigInt2);

			Assert::IsTrue(compared > 0);
		}

		TEST_METHOD(cmpTest10)
		{
			grint myBigInt1 = grint_from_int(1234);
			grint myBigInt2 = grint_from_int(-1234);

			int compared = grint_cmp(myBigInt1, myBigInt2);

			Assert::IsTrue(compared > 0);
		}

		TEST_METHOD(cmpTest11)
		{
			grint myBigInt1 = grint_from_int(-1235);
			grint myBigInt2 = grint_from_int(1234);

			int compared = grint_cmp(myBigInt1, myBigInt2);

			Assert::IsTrue(compared < 0);
		}

		TEST_METHOD(cmpTest12)
		{
			grint myBigInt1 = grint_from_int(-1233);
			grint myBigInt2 = grint_from_int(1234);

			int compared = grint_cmp(myBigInt1, myBigInt2);

			Assert::IsTrue(compared < 0);
		}

		TEST_METHOD(cmpTest13)
		{
			grint myBigInt1 = grint_from_int(-1234);
			grint myBigInt2 = grint_from_int(1234);

			int compared = grint_cmp(myBigInt1, myBigInt2);

			Assert::IsTrue(compared < 0);
		}

		TEST_METHOD(cmpTest14)
		{
			grint myBigInt1 = grint_from_int(1235);
			grint myBigInt2 = grint_from_int(1234);

			int compared = grint_cmp(myBigInt1, myBigInt2);

			Assert::IsTrue(compared > 0);
		}

		TEST_METHOD(cmpTest15)
		{
			grint myBigInt1 = grint_from_int(1233);
			grint myBigInt2 = grint_from_int(1234);

			int compared = grint_cmp(myBigInt1, myBigInt2);

			Assert::IsTrue(compared < 0);
		}

		TEST_METHOD(cmpTest16)
		{
			grint myBigInt1 = grint_from_int(1234);
			grint myBigInt2 = grint_from_int(1234);

			int compared = grint_cmp(myBigInt1, myBigInt2);

			Assert::IsTrue(compared == 0);
		}

		TEST_METHOD(cmpTest17)
		{
			grint myBigInt1 = grint_from_int(-1235);
			grint myBigInt2 = grint_from_int(-1234);

			int compared = grint_cmp(myBigInt1, myBigInt2);

			Assert::IsTrue(compared < 0);
		}

		TEST_METHOD(cmpTest18)
		{
			grint myBigInt1 = grint_from_int(-1233);
			grint myBigInt2 = grint_from_int(-1234);

			int compared = grint_cmp(myBigInt1, myBigInt2);

			Assert::IsTrue(compared > 0);
		}

		TEST_METHOD(cmpTest19)
		{
			grint myBigInt1 = grint_from_int(-1234);
			grint myBigInt2 = grint_from_int(-1234);

			int compared = grint_cmp(myBigInt1, myBigInt2);

			Assert::IsTrue(compared == 0);
		}
	};

	TEST_CLASS(addTests)
	{
	public:

		TEST_METHOD(addTest1)
		{
			grint myBigInt1 = grint_from_int(1234);
			grint myBigInt2 = grint_from_int(-3716);
			grint solution = grint_from_int(0);

			grint_add(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(4ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(-1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("-2482", stringFromGrint));
		}

		TEST_METHOD(addTest2)
		{
			grint myBigInt1 = grint_from_int(12345);
			grint myBigInt2 = grint_from_int(3716);
			grint solution = grint_from_int(0);

			grint_add(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(5ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("16061", stringFromGrint));
		}

		TEST_METHOD(addTest3)
		{
			grint myBigInt1 = grint_from_int(-12345);
			grint myBigInt2 = grint_from_int(3716);
			grint solution = grint_from_int(0);

			grint_add(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(4ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(-1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("-8629", stringFromGrint));
		}

		TEST_METHOD(addTest4)
		{
			grint myBigInt1 = grint_from_int(-12345);
			grint myBigInt2 = grint_from_int(-3716);
			grint solution = grint_from_int(0);

			grint_add(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(5ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(-1, solution->sign);
			
			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("-16061", stringFromGrint));
		}

		TEST_METHOD(addTest5)
		{
			grint myBigInt1 = grint_from_int(67890);
			grint myBigInt2 = grint_from_int(78935);
			grint solution = grint_from_int(0);

			grint_add(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(6ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("146825", stringFromGrint));
		}

		TEST_METHOD(addTest6)
		{
			grint myBigInt1 = grint_from_int(-67890);
			grint myBigInt2 = grint_from_int(-78935);
			grint solution = grint_from_int(0);

			grint_add(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(6ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(-1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("-146825", stringFromGrint));
		}

		TEST_METHOD(addTest7)
		{
			grint myBigInt1 = grint_from_int(-67890);
			grint myBigInt2 = grint_from_int(78935);
			grint solution = grint_from_int(0);

			grint_add(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(5ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("11045", stringFromGrint));
		}

		TEST_METHOD(addTest8)
		{
			grint myBigInt1 = grint_from_int(78935);
			grint myBigInt2 = grint_from_int(-67890);
			grint solution = grint_from_int(0);

			grint_add(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(5ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("11045", stringFromGrint));
		}

		TEST_METHOD(addTest9)
		{
			grint myBigInt1 = grint_from_int(78935);
			grint myBigInt2 = grint_from_int(0);
			grint solution = grint_from_int(0);

			grint_add(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(5ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("78935", stringFromGrint));
		}

		TEST_METHOD(addTest10)
		{
			grint myBigInt1 = grint_from_int(0);
			grint myBigInt2 = grint_from_int(0);
			grint solution = grint_from_int(0);

			grint_add(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(1ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("0", stringFromGrint));
		}

		TEST_METHOD(addTest11)
		{
			grint myBigInt2 = grint_from_int(64);
			grint solution = grint_from_int(0);

			grint_add(solution, solution, myBigInt2);

			Assert::AreEqual(2ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("64", stringFromGrint));
		}

		TEST_METHOD(addTest12)
		{
			grint myBigInt2 = grint_from_int(64);
			grint solution = grint_from_int(4);

			grint_add(solution, solution, myBigInt2);

			Assert::AreEqual(2ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("68", stringFromGrint));
		}
	};

	TEST_CLASS(subTests)
	{
	public:

		TEST_METHOD(subTest1)
		{
			grint myBigInt1 = grint_from_int(1234);
			grint myBigInt2 = grint_from_int(3716);
			grint solution = grint_from_int(0);

			grint_sub(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(4ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(-1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("-2482", stringFromGrint));
		}

		TEST_METHOD(subTest2)
		{
			grint myBigInt1 = grint_from_int(12345);
			grint myBigInt2 = grint_from_int(3716);
			grint solution = grint_from_int(0);

			grint_sub(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(4ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(1, solution->sign);
			
			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("8629", stringFromGrint));
		}

		TEST_METHOD(subTest3)
		{
			grint myBigInt1 = grint_from_int(-12345);
			grint myBigInt2 = grint_from_int(3716);
			grint solution = grint_from_int(0);

			grint_sub(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(5ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(-1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("-16061", stringFromGrint));
		}

		TEST_METHOD(subTest4)
		{
			grint myBigInt1 = grint_from_int(-12345);
			grint myBigInt2 = grint_from_int(-3716);
			grint solution = grint_from_int(0);

			grint_sub(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(4ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(-1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("-8629", stringFromGrint));
		}

		TEST_METHOD(subTest5)
		{
			grint myBigInt1 = grint_from_int(67890);
			grint myBigInt2 = grint_from_int(78935);
			grint solution = grint_from_int(0);

			grint_sub(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(5ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(-1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("-11045", stringFromGrint));
		}

		TEST_METHOD(subTest6)
		{
			grint myBigInt1 = grint_from_int(-67890);
			grint myBigInt2 = grint_from_int(-78935);
			grint solution = grint_from_int(0);

			grint_sub(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(5ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("11045", stringFromGrint));
		}

		TEST_METHOD(subTest7)
		{
			grint myBigInt1 = grint_from_int(-67890);
			grint myBigInt2 = grint_from_int(78935);
			grint solution = grint_from_int(0);

			grint_sub(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(6ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(-1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("-146825", stringFromGrint));
		}

		TEST_METHOD(subTest8)
		{
			grint myBigInt1 = grint_from_int(78935);
			grint myBigInt2 = grint_from_int(-67890);
			grint solution = grint_from_int(0);

			grint_sub(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(5ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("11045", stringFromGrint));
		}

		TEST_METHOD(subTest9)
		{
			grint myBigInt1 = grint_from_int(78935);
			grint myBigInt2 = grint_from_int(0);
			grint solution = grint_from_int(0);

			grint_sub(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(5ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("78935", stringFromGrint));
		}

		TEST_METHOD(subTest10)
		{
			grint myBigInt1 = grint_from_int(0);
			grint myBigInt2 = grint_from_int(0);
			grint solution = grint_from_int(0);

			grint_sub(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(1ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("0", stringFromGrint));
		}

		//Zeros were not getting removed properly

		TEST_METHOD(subTest11)
		{
			grint myBigInt1 = grint_from_int(100);
			grint myBigInt2 = grint_from_int(64);

			grint_sub(myBigInt1, myBigInt1, myBigInt2);

			Assert::AreEqual(2ul, myBigInt1->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, myBigInt1->lenData);

			Assert::AreEqual(1, myBigInt1->sign);

			char* stringFromGrint = grint_to_string(myBigInt1);

			Assert::AreEqual(0, strcmp("36", stringFromGrint));
		}

		TEST_METHOD(subTest12)
		{
			grint myBigInt1 = grint_from_int(4);
			grint myBigInt2 = grint_from_int(4);

			grint_sub(myBigInt1, myBigInt1, myBigInt2);

			Assert::AreEqual(1ul, myBigInt1->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, myBigInt1->lenData);

			Assert::AreEqual(1, myBigInt1->sign);

			char* stringFromGrint = grint_to_string(myBigInt1);

			Assert::AreEqual(0, strcmp("0", stringFromGrint));
		}
	};

	TEST_CLASS(mulTests)
	{
	public:

		TEST_METHOD(mulTest1)
		{
			grint myBigInt1 = grint_from_int(123456);
			grint myBigInt2 = grint_from_int(123);
			grint solution = grint_from_int(0);

			grint_mul(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(8ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(1, solution->sign);

			Assert::AreEqual("15185088", grint_to_string(solution));
		}

		TEST_METHOD(mulTest2)
		{
			grint myBigInt1 = grint_from_int(-123456);
			grint myBigInt2 = grint_from_int(123);
			grint solution = grint_from_int(0);

			grint_mul(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(8ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(-1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("-15185088", stringFromGrint));
		}

		TEST_METHOD(mulTest3)
		{
			grint myBigInt1 = grint_from_int(123456);
			grint myBigInt2 = grint_from_int(-123);
			grint solution = grint_from_int(0);

			grint_mul(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(8ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(-1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("-15185088", stringFromGrint));
		}

		TEST_METHOD(mulTest4)
		{
			grint myBigInt1 = grint_from_int(-123456);
			grint myBigInt2 = grint_from_int(-123);
			grint solution = grint_from_int(0);

			grint_mul(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(8ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("15185088", stringFromGrint));
		}
#
		TEST_METHOD(mulTest5)
		{
			grint myBigInt1 = grint_from_int(0);
			grint myBigInt2 = grint_from_int(-123);
			grint solution = grint_from_int(0);

			grint_mul(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(1ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("0", stringFromGrint));
		}

		TEST_METHOD(mulTest6)
		{
			grint myBigInt1 = grint_from_int(0);
			grint myBigInt2 = grint_from_int(123);
			grint solution = grint_from_int(0);

			grint_mul(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(1ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(1, solution->sign);

			char* stringFromGrint = grint_to_string(myBigInt1);

			Assert::AreEqual(0, strcmp("0", stringFromGrint));
		}

		TEST_METHOD(mulTest7)
		{
			grint myBigInt1 = grint_from_int(123);
			grint myBigInt2 = grint_from_int(143);

			grint_mul(myBigInt1, myBigInt1, myBigInt2);

			Assert::AreEqual(5ul, myBigInt1->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, myBigInt1->lenData);

			Assert::AreEqual(1, myBigInt1->sign);

			char* stringFromGrint = grint_to_string(myBigInt1);

			Assert::AreEqual(0, strcmp("17589", stringFromGrint));
		}

		TEST_METHOD(mulTest8)
		{
			grint myBigInt1 = grint_from_int(34);
			grint myBigInt2 = grint_from_int(3);

			grint_mul(myBigInt1, myBigInt1, myBigInt2);

			Assert::AreEqual(3ul, myBigInt1->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, myBigInt1->lenData);

			Assert::AreEqual(1, myBigInt1->sign);

			char* stringFromGrint = grint_to_string(myBigInt1);

			Assert::AreEqual(0, strcmp("102", stringFromGrint));
		}

		TEST_METHOD(mulTest9)
		{
			grint myBigInt1 = grint_from_int(34);
			grint myBigInt2 = grint_from_int(3);
			grint solution = grint_from_int(0);

			grint_mul(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(3ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("102", stringFromGrint));
		}

		TEST_METHOD(mulTest10)
		{
			grint myBigInt1 = grint_from_int(408);
			grint myBigInt2 = grint_from_int(5);
			grint solution = grint_from_int(0);

			grint_mul(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(4ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("2040", stringFromGrint));
		}

		TEST_METHOD(mulTest11)
		{
			grint myBigInt1 = grint_from_int(208);
			grint myBigInt2 = grint_from_int(5);
			grint solution = grint_from_int(0);

			grint_mul(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(4ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("1040", stringFromGrint));
		}

		TEST_METHOD(mulTest12)
		{
			grint myBigInt1 = grint_from_int(123);
			grint myBigInt2 = grint_from_int(9);
			grint solution = grint_from_int(0);

			grint_mul(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(4ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("1107", stringFromGrint));
		}

		TEST_METHOD(mulTest13)
		{
			grint myBigInt1 = grint_from_int(40);
			grint myBigInt2 = grint_from_int(4);
			grint solution = grint_from_int(0);

			grint_mul(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(3ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("160", stringFromGrint));
		}

		/// <summary>
		/// [154b4f5] Multiplication generates wrong length
		/// </summary>
		TEST_METHOD(mulTest14)
		{
			grint myBigInt1 = grint_from_string("678585600");
			grint myBigInt2 = grint_from_int(12);

			grint_mul(myBigInt1, myBigInt1, myBigInt2);

			Assert::AreEqual(10ul, myBigInt1->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, myBigInt1->lenData);

			Assert::AreEqual(1, myBigInt1->sign);

			Assert::AreEqual("8143027200", grint_to_string(myBigInt1));
		}
	};


	TEST_CLASS(divTests)
	{
	public:

		TEST_METHOD(divTest1)
		{
			grint myBigInt1 = grint_from_int(1234);
			grint myBigInt2 = grint_from_int(1234);
			grint solution = grint_from_int(0);

			grint_div(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(1ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("1", stringFromGrint));
		}

		TEST_METHOD(divTest2)
		{
			grint myBigInt1 = grint_from_int(-1234);
			grint myBigInt2 = grint_from_int(1234);
			grint solution = grint_from_int(0);

			grint_div(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(1ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(-1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("-1", stringFromGrint));
		}

		TEST_METHOD(divTest3)
		{
			grint myBigInt1 = grint_from_int(1234);
			grint myBigInt2 = grint_from_int(-1234);
			grint solution = grint_from_int(0);

			grint_div(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(1ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(-1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("-1", stringFromGrint));
		}

		TEST_METHOD(divTest4)
		{
			grint myBigInt1 = grint_from_int(-1234);
			grint myBigInt2 = grint_from_int(-1234);
			grint solution = grint_from_int(0);

			grint_div(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(1ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("1", stringFromGrint));
		}

		TEST_METHOD(divTest5)
		{
			grint myBigInt1 = grint_from_int(1234);
			grint myBigInt2 = grint_from_int(123);
			grint solution = grint_from_int(0);

			grint_div(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(2ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("10", stringFromGrint));
		}

		TEST_METHOD(divTest6)
		{
			grint myBigInt1 = grint_from_int(123);
			grint myBigInt2 = grint_from_int(1234);
			grint solution = grint_from_int(0);

			grint_div(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(1ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("0", stringFromGrint));
		}

		TEST_METHOD(divTest7)
		{
			grint myBigInt1 = grint_from_int(1234);
			grint myBigInt2 = grint_from_int(1235);
			grint solution = grint_from_int(0);

			grint_div(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(1ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("0", stringFromGrint));
		}

		TEST_METHOD(divTest8)
		{
			grint myBigInt1 = grint_from_int(1235);
			grint myBigInt2 = grint_from_int(1234);
			grint solution = grint_from_int(0);

			grint_div(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(1ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("1", stringFromGrint));
		}

		TEST_METHOD(divTest9)
		{
			grint myBigInt1 = grint_from_int(1234);
			grint myBigInt2 = grint_from_int(0);
			grint solution = grint_from_int(0);

			int err = grint_div(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(2, err);
		}

		TEST_METHOD(divTest10)
		{
			grint myBigInt1 = grint_from_int(0);
			grint myBigInt2 = grint_from_int(1234);
			grint solution = grint_from_int(0);

			grint_div(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(1ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("0", stringFromGrint));
		}

		TEST_METHOD(divTest11)
		{
			grint myBigInt1 = grint_from_int(1234);
			grint myBigInt2 = grint_from_int(1);
			grint solution = grint_from_int(0);

			grint_div(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(4ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("1234", stringFromGrint));
		}

		TEST_METHOD(divTest12)
		{
			grint myBigInt1 = grint_from_int(51408);
			grint myBigInt2 = grint_from_int(6);
			grint solution = grint_from_int(0);

			grint_div(solution, myBigInt1, myBigInt2);

			Assert::AreEqual(4ul, solution->lenNumber);
			Assert::AreEqual(DIGIT_BLOCKSIZE, solution->lenData);

			Assert::AreEqual(1, solution->sign);

			char* stringFromGrint = grint_to_string(solution);

			Assert::AreEqual(0, strcmp("8568", stringFromGrint));
		}
	};
	
	TEST_CLASS(arbTests)
	{
	public:
		
		TEST_METHOD(arbTest1)
		{
			grint g = grint_from_int(17);

			for (int i = 2; i < 22; i++)
			{
				grint grintMul = grint_from_int(i);
				grint_mul(g, g, grintMul);
				grint_clear(grintMul);
			}

			for (int i = 2; i < 22; i++)
			{
				grint grintMul = grint_from_int(i);
				grint_div(g, g, grintMul);
				grint_clear(grintMul);
			}

			Assert::AreEqual((char)7, g->pData[0]);
			Assert::AreEqual((char)1, g->pData[1]);

		}


		TEST_METHOD(arbTest2)
		{
			grint g = grint_from_int(17);

			for (int i = 2; i < 23; i++)
			{
				grint grintMul = grint_from_int(i);
				grint_mul(g, g, grintMul);
				grint_clear(grintMul);
			}

			grint problemNum = grint_from_string("19108012372219330560000");

			for (int i = 2; i < 23; i++)
			{
				grint grintMul = grint_from_int(i);
				grint_div(g, g, grintMul);
				grint_clear(grintMul);
			}

			Assert::AreEqual((char)7, g->pData[0]);
			Assert::AreEqual((char)1, g->pData[1]);
			
		}

		TEST_METHOD(arbTest3)
		{
			grint problemNum = grint_from_string("19108012372219330560000");
			grint divider = grint_from_int(2);

			grint_div(problemNum, problemNum, divider);

			char* stringFromGrint = grint_to_string(problemNum);
			char* expected = "9554006186109665280000";

			Assert::AreEqual(0, strncmp(expected, stringFromGrint, 22));
		}

		/// <summary>
		/// Testing upto 999 digits!
		/// </summary>
		TEST_METHOD(arbTest4)
		{
			const int towerHeight = 450; 
			grint g = grint_from_int(17);

			for (int i = 2; i < towerHeight; i++)
			{
				grint grintMul = grint_from_int(i);
				grint_mul(g, g, grintMul);
				grint_clear(grintMul);
			}

			for (int i = 2; i < towerHeight; i++)
			{
				grint grintMul = grint_from_int(i);
				grint_div(g, g, grintMul);
				grint_clear(grintMul);
			}

			Assert::AreEqual((char)7, g->pData[0]);
			Assert::AreEqual((char)1, g->pData[1]);

		}

		TEST_METHOD(arbTest5)
		{
			const int towerHeight = 10000;
			grint g = grint_from_int(17);

			for (int i = 2; i < towerHeight; i++)
			{
				grint grintMul = grint_from_int(i);
				grint_mul(g, g, grintMul);
				grint_clear(grintMul);
			}

			grint problemNum = grint_from_string("19108012372219330560000");

			for (int i = 2; i < towerHeight; i++)
			{
				grint grintMul = grint_from_int(i);
				grint_div(g, g, grintMul);
				grint_clear(grintMul);
			}

			Assert::AreEqual((char)7, g->pData[0]);
			Assert::AreEqual((char)1, g->pData[1]);

		}
	};

	TEST_CLASS(grintFromStringTests)
	{
	public:

		TEST_METHOD(gfsTest1)
		{
			char* string = "12345";
			
			grint myBigInt = grint_from_string(string);

			Assert::AreEqual(5ul, myBigInt->lenNumber);
			Assert::AreEqual(1, myBigInt->sign);

			char* stringFromGrint = grint_to_string(myBigInt);

			Assert::AreEqual(0, strcmp(string, stringFromGrint));
		}

		TEST_METHOD(gfsTest2)
		{
			char* string = "0";
			
			grint myBigInt = grint_from_string("0");

			Assert::AreEqual(1ul, myBigInt->lenNumber);
			Assert::AreEqual(1, myBigInt->sign);

			char* stringFromGrint = grint_to_string(myBigInt);

			Assert::AreEqual(0, strcmp(string, stringFromGrint));
		}

		TEST_METHOD(gfsTest4)
		{
			char string[2001];
			memset(string, 1, 2000);
			string[2000] = '\0';

			grint myBigInt = grint_from_string(string);

			Assert::AreEqual(2000ul, myBigInt->lenNumber);
			Assert::AreEqual(1, myBigInt->sign);
		}
	};

	TEST_CLASS(grintToStringTests)
	{
	public:

		TEST_METHOD(gtsTest1)
		{
			char* string = "12345";

			grint myBigInt = grint_from_string(string);

			char* stringFromGrint = grint_to_string(myBigInt);

			Assert::AreEqual(0, strcmp(string, stringFromGrint));
		}

		TEST_METHOD(gtsTest2)
		{
			char* string = "-12345";

			grint myBigInt = grint_from_string(string);

			char* stringFromGrint = grint_to_string(myBigInt);

			Assert::AreEqual(0, strcmp(string, stringFromGrint));
		}

		TEST_METHOD(gtsTest3)
		{
			char* string = "1345456123457245724572457245745645";

			grint myBigInt = grint_from_string(string);

			char* stringFromGrint = grint_to_string(myBigInt);

			Assert::AreEqual(0, strcmp(string, stringFromGrint));
		}

		TEST_METHOD(gtsTest4)
		{
			char* string = "-4";

			grint myBigInt = grint_from_string(string);

			char* stringFromGrint = grint_to_string(myBigInt);

			Assert::AreEqual(0, strcmp(string, stringFromGrint));
		}
	};
}

