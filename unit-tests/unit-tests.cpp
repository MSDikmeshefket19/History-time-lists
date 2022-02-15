#include "pch.h"
#include "CppUnitTest.h"
#include "../history-time-lists/back-end.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unittests
{
	TEST_CLASS(unittests)
	{
	public:	
		TEST_METHOD(TestMethod1)
		{
			// Arrange
			int result;

			// Act
			result = codeOfGrey(3);

			// Asser
			Assert::AreEqual(2, result);
		}

		TEST_METHOD(TestMethod2)
		{
			// Arrange
			int result;

			// Act
			result = codeOfGrey(917);

			// Asser
			Assert::AreEqual(1012, result);
		}

		TEST_METHOD(TestMethod3)
		{
			// Arrange
			int result;

			// Act
			result = codeOfGrey(500);

			// Asser
			Assert::AreEqual(112, result);
		}

	};
}
