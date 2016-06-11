#include "pch.h"
#include "FooEntity.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(FooEntityTest)
	{
	public:
		TEST_METHOD(FooEntityTestConstructor)
		{
			FooEntity entity;
			Assert::IsFalse(entity.WasUpdated());
		}

		TEST_METHOD(FooEntityTestUpdate)
		{
			Library::WorldState state;

			FooEntity entity;
			Assert::IsFalse(entity.WasUpdated());
			entity.Update(state);
			Assert::IsTrue(entity.WasUpdated());
		}
	};
}
