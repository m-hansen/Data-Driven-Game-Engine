#include "pch.h"
#include "XmlParseHelperFoo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(XmlParseMasterTest)
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

		TEST_METHOD(XmlParseMasterTestConstructor)
		{
			XmlParseMaster::SharedData* sharedData = new XmlParseMaster::SharedData();
			XmlParseMaster parser(sharedData);
			Assert::IsFalse(parser.IsClone());
			Assert::IsTrue(parser.GetFileName() == "");
			delete sharedData;
		}

		TEST_METHOD(XmlParseMasterTestClone)
		{
			XmlParseMaster::SharedData* sharedData = new XmlParseMaster::SharedData();
			XmlParseMaster parser(sharedData);

			XmlParseMaster* newClone = parser.Clone();
			Assert::IsTrue(newClone->IsClone());

			delete newClone;
			delete sharedData;
		}

		TEST_METHOD(XmlParseMasterTestAddHelper)
		{
			XmlParseMaster::SharedData* sharedData = new XmlParseMaster::SharedData();
			XmlParseMaster parser(sharedData);
			XmlParseHelperFoo* fooHelper = new XmlParseHelperFoo();
			parser.AddHelper(*fooHelper);

			delete fooHelper;
			delete sharedData;
		}

		TEST_METHOD(XmlParseMasterTestRemoveHelper)
		{
			XmlParseMaster::SharedData* sharedData = new XmlParseMaster::SharedData();
			XmlParseMaster parser(sharedData);
			XmlParseHelperFoo* fooHelper = new XmlParseHelperFoo();
			parser.AddHelper(*fooHelper);
			parser.RemoveHelper(*fooHelper);

			delete fooHelper;
			delete sharedData;
		}

		TEST_METHOD(XmlParseMasterTestParseFromFile)
		{
			XmlParseMaster::SharedData* sharedData = new XmlParseMaster::SharedData();
			XmlParseMaster parser(sharedData);
			XmlParseHelperFoo* fooHelper = new XmlParseHelperFoo();
			parser.AddHelper(*fooHelper);
			parser.ParseFromFile("Content/Foo.xml");
			Assert::IsTrue(parser.GetFileName() == "Content/Foo.xml");

			delete fooHelper;
			delete sharedData;
		}

	private:
#if defined(DEBUG) | defined(_DEBUG)
		static _CrtMemState sStartMemState;
#endif

	};

#if defined(DEBUG) | defined(_DEBUG)
	_CrtMemState XmlParseMasterTest::sStartMemState;
#endif

}
