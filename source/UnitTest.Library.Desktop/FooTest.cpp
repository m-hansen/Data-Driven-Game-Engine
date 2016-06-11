#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLibraryDesktop
{		
	TEST_CLASS(FooTest)
	{
	public:
		
		TEST_METHOD(FooTestConstructor)
		{
			int value = 10;
			Foo foo(value);

			Assert::AreEqual(value, foo.Data());
		}

		TEST_METHOD(FooTestComparisonOperators)
		{
			Foo fooA(1);
			Foo fooB(2);
			Foo fooC(1);

			Assert::IsTrue(fooA == fooC);
			Assert::IsTrue(fooC == fooA);
			Assert::IsTrue(fooA != fooB);
			Assert::IsTrue(fooB != fooA);
			Assert::IsTrue(fooC != fooB);
			Assert::IsTrue(fooB != fooC);
		}

	};
}