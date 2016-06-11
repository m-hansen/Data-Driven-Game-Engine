#include "pch.h"
#include "AttributedFoo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(XmlParseHelperTableTest)
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

		TEST_METHOD(XmlParseHelperTableTestConstructor)
		{
			XmlParseMaster::SharedData* sharedData = new XmlParseMaster::SharedData();
			XmlParseMaster parser(sharedData);
			Assert::IsFalse(parser.IsClone());
			Assert::IsTrue(parser.GetFileName() == "");
			delete sharedData;
		}

		TEST_METHOD(XmlParseHelperTableTestRtti)
		{
			Scope globalScope;
			XmlParseHelperTable::SharedData tableSharedData(globalScope);
			XmlParseMaster parser(&tableSharedData);
			XmlParseHelperTable tableHelper;
			parser.AddHelper(tableHelper);

			Assert::IsTrue(tableSharedData.Is("SharedData"));
			Assert::IsNotNull(tableSharedData.As<XmlParseHelperTable::SharedData>());
			Assert::IsTrue(tableSharedData.TypeName() == "SharedData");
		}

		TEST_METHOD(XmlParseHelperTableTestParse)
		{
			Scope globalScope;
			XmlParseHelperTable::SharedData tableSharedData(globalScope);
			XmlParseMaster parser(&tableSharedData);
			XmlParseHelperTable tableHelper;

			parser.AddHelper(tableHelper);
			parser.ParseFromFile("Content/Scope.xml");
			Assert::IsTrue(parser.GetFileName() == "Content/Scope.xml");

			// Expected global values
			std::int32_t expectedGlobalIntValue = 5;
			float expectedGlobalFloatValue = 10.0f;
			glm::vec4 expectedGlobalVectorValue = glm::vec4(0.0f);
			glm::mat4 expectedGlobalMatrixValue = glm::mat4(0.0f);
			std::string expectedGlobalStringValue = "MyGlobalString";

			// Check that the expected global values are found in the global scope
			Scope* topLevelXmlScope = globalScope.Find("GlobalScope")->Get<Scope*>(0);
			Assert::AreEqual(expectedGlobalIntValue, topLevelXmlScope->Find("globalInt")->Get<std::int32_t>(0));
			Assert::AreEqual(expectedGlobalFloatValue, topLevelXmlScope->Find("globalFloat")->Get<float>(0));
			Assert::IsTrue(expectedGlobalVectorValue == topLevelXmlScope->Find("globalVector")->Get<glm::vec4>(0));
			Assert::IsTrue(expectedGlobalMatrixValue == topLevelXmlScope->Find("globalMatrix")->Get<glm::mat4>(0));
			Assert::IsTrue(expectedGlobalStringValue == topLevelXmlScope->Find("globalString")->Get<std::string>(0));
		}

		TEST_METHOD(XmlParseHelperTableTestParseInvalid)
		{
			Scope globalScope;
			XmlParseHelperTable::SharedData tableSharedData(globalScope);
			XmlParseMaster parser(&tableSharedData);
			XmlParseHelperTable tableHelper;

			parser.AddHelper(tableHelper);
			Assert::ExpectException<std::exception>([&] { parser.ParseFromFile("Content/Invalid.xml"); });
		}

		TEST_METHOD(XmlParseHelperTableTestClone)
		{
			Scope globalScope;
			XmlParseHelperTable tableHelper;
			XmlParseHelperTable::SharedData tableSharedData(globalScope);
			XmlParseMaster parser(&tableSharedData);
			parser.AddHelper(tableHelper);

			// Test XmlParseHelperTable Clone()
			XmlParseHelperTable* clonedTable = tableHelper.Clone();
			Assert::IsTrue(clonedTable->IsClone());
			Assert::IsFalse(tableHelper.IsClone());
			delete clonedTable;

			// Test XmlParseHelperTable::SharedData Clone()
			XmlParseHelperTable::SharedData* clonedTableSharedData = tableSharedData.Clone();
			Assert::IsTrue(clonedTableSharedData->IsClone());
			Assert::IsFalse(tableSharedData.IsClone());
			delete clonedTableSharedData;
		}

	private:
#if defined(DEBUG) | defined(_DEBUG)
		static _CrtMemState sStartMemState;
#endif

	};

#if defined(DEBUG) | defined(_DEBUG)
	_CrtMemState XmlParseHelperTableTest::sStartMemState;
#endif

}