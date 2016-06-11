#include "pch.h"
#include "Factory.h"
#include "FooRTTI.h"
#include "BarRTTI.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;

namespace UnitTestLibraryDesktop
{
	ConcreteFactory(FooRTTI, Library::RTTI)
	ConcreteFactory(BarRTTI, Library::RTTI)

	TEST_CLASS(FactoryTest)
	{
	public:

#if defined(DEBUG) | defined(_DEBUG)
		TEST_METHOD_INITIALIZE(Initialize)
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
		}

		TEST_METHOD_CLEANUP(Cleanup)
		{
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
		}
#endif

		TEST_METHOD(FactoryTestFind)
		{
			Assert::IsNull(Factory<RTTI>::Find("ExpectingNull"));

			FooRTTIFactory fooFactory;
			auto rttiFactory = Factory<RTTI>::Create("FooRTTI");
			Assert::IsNotNull(Factory<RTTI>::Find("FooRTTI"));
			
			delete rttiFactory;
		}

		TEST_METHOD(FactoryTestCreate)
		{
			FooRTTIFactory fooFactory;
			Assert::AreEqual(1U, Factory<RTTI>::Size());
			RTTI* rttiFactory = Factory<RTTI>::Create("FooRTTI");
			Assert::IsTrue(rttiFactory->Is("FooRTTI"));

			Assert::ExpectException<std::exception>([&] { Factory<RTTI>::Create("Invalid"); });

			delete rttiFactory;
		}

		TEST_METHOD(FactoryTestMultiple)
		{
			FooRTTIFactory fooFactory;
			Assert::AreEqual(1U, Factory<RTTI>::Size());
			auto foundFactory = Factory<RTTI>::Find("FooRTTI");
			Assert::IsTrue(const_cast<const FooRTTIFactory*>(&fooFactory) == static_cast<const FooRTTIFactory*>(foundFactory));

			BarRTTIFactory barFactory;
			Assert::AreEqual(2U, Factory<RTTI>::Size());
			foundFactory = Factory<RTTI>::Find("BarRTTI");
			Assert::IsTrue(const_cast<const BarRTTIFactory*>(&barFactory) == static_cast<const BarRTTIFactory*>(foundFactory));
		}

		TEST_METHOD(FactoryTestIterators)
		{
			FooRTTIFactory fooFactory;
			Assert::AreEqual(1U, Factory<RTTI>::Size());
			auto rttiFactory = Factory<RTTI>::Create("FooRTTI");

			std::uint32_t count = 0;
			for (auto it = fooFactory.begin(); it != fooFactory.end(); ++it)
			{
				++count;
			}
			Assert::AreEqual(fooFactory.Size(), count);

			delete rttiFactory;
		}

		TEST_METHOD(FactoryTestIsEmpty)
		{
			Assert::AreEqual(0U, Factory<RTTI>::Size());
			Assert::IsTrue(Factory<RTTI>::IsEmpty());

			FooRTTIFactory fooFactory;
			Assert::AreEqual(1U, Factory<RTTI>::Size());
			Assert::IsFalse(Factory<RTTI>::IsEmpty());
		}

		TEST_METHOD(FactoryTestClassName)
		{
			FooRTTIFactory fooFactory;
			Assert::IsTrue(fooFactory.ClassName() == "FooRTTI");
		}

	private:
#if defined(DEBUG) | defined(_DEBUG)
		static _CrtMemState sStartMemState;
#endif

	};

#if defined(DEBUG) | defined(_DEBUG)
	_CrtMemState FactoryTest::sStartMemState;
#endif

}
