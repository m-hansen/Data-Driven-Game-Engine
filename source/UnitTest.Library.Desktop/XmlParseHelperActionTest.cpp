#include "pch.h"
#include "FooAction.h"
#include "FooEntity.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;

namespace UnitTestLibraryDesktop
{
	//ActionFactory(FooAction);
	ConcreteFactory(FooEntity, Library::RTTI)

	TEST_CLASS(XmlParseHelperActionTest)
	{
	public:

		TEST_METHOD(XmlParseHelperActionTestConstructor)
		{
			XmlParseMaster::SharedData* sharedData = new XmlParseMaster::SharedData();
			XmlParseMaster parser(sharedData);
			Assert::IsFalse(parser.IsClone());
			Assert::IsTrue(parser.GetFileName().empty());
			delete sharedData;
		}

		TEST_METHOD(XmlParseHelperActionTestRtti)
		{
			Scope globalScope;
			XmlParseHelperAction::SharedData tableSharedData(globalScope);
			XmlParseMaster parser(&tableSharedData);
			XmlParseHelperAction actionHelper;
			parser.AddHelper(actionHelper);

			Assert::IsTrue(tableSharedData.Is("SharedData"));
			Assert::IsNotNull(tableSharedData.As<XmlParseHelperAction::SharedData>());
			Assert::IsTrue(tableSharedData.TypeName() == "SharedData");
		}

		//TEST_METHOD(XmlParseHelperActionTestParse)
		//{
		//	const std::string XmlFilename = "Content/SimpleAction.xml";
		//	const std::string ParentActionName = "ParentAction";
		//	const std::string EmptyChildActionName = "EmptyChildAction";
		//	const std::string ChildActionName = "ChildAction";
		//	const std::string EmptyGrandchildActionName = "EmptyGrandchildAction";

		//	FooActionFactory actionFactory;
		//	FooEntityFactory entityFactory;

		//	Scope globalScope;
		//	XmlParseHelperAction::SharedData actionSharedData(globalScope);
		//	XmlParseMaster parser(&actionSharedData);

		//	XmlParseHelperEntity entityHelper;
		//	parser.AddHelper(entityHelper);
		//	XmlParseHelperAction actionHelper;
		//	parser.AddHelper(actionHelper);
		//	
		//	parser.ParseFromFile(XmlFilename);
		//	Assert::IsTrue(parser.GetFileName() == XmlFilename);

		//	// Verify the parent action was parsed
		//	Datum* foundParentDatum = globalScope.Find(ParentActionName);
		//	Assert::IsNotNull(foundParentDatum);
		//	Scope* foundParentScope = foundParentDatum->Get<Scope*>(0);
		//	Assert::IsNotNull(foundParentScope);
		//	Action* parentAction = foundParentScope->As<Action>();
		//	Assert::IsNotNull(parentAction);
		//	Assert::IsTrue(parentAction->Name() == ParentActionName);

		//	// Verify the empty child action was parsed
		//	Datum* foundEmptyChildDatum = globalScope.Find(EmptyChildActionName);
		//	Assert::IsNotNull(foundEmptyChildDatum);
		//	Scope* foundEmptyChildScope = foundEmptyChildDatum->Get<Scope*>(0);
		//	Assert::IsNotNull(foundEmptyChildScope);
		//	Action* emptyChildAction = foundEmptyChildScope->As<Action>();
		//	Assert::IsNotNull(emptyChildAction);
		//	Assert::IsTrue(emptyChildAction->Name() == EmptyChildActionName);

		//	// Verify the child action was parsed
		//	Datum* foundChildDatum = globalScope.Find(ChildActionName);
		//	Assert::IsNotNull(foundChildDatum);
		//	Scope* foundChildScope = foundChildDatum->Get<Scope*>(0);
		//	Assert::IsNotNull(foundChildScope);
		//	Action* childAction = foundChildScope->As<Action>();
		//	Assert::IsNotNull(childAction);
		//	Assert::IsTrue(childAction->Name() == ChildActionName);

		//	// Verify the empty grandchild action was parsed
		//	Datum* foundEmptyGrandchildDatum = globalScope.Find(EmptyGrandchildActionName);
		//	Assert::IsNotNull(foundEmptyGrandchildDatum);
		//	Scope* foundEmptyGrandchildScope = foundEmptyChildDatum->Get<Scope*>(0);
		//	Assert::IsNotNull(foundEmptyGrandchildScope);
		//	Action* emptyGrandchildAction = foundEmptyGrandchildScope->As<Action>();
		//	Assert::IsNotNull(emptyGrandchildAction);
		//	Assert::IsTrue(emptyGrandchildAction->Name() == EmptyGrandchildActionName);
		//}

		TEST_METHOD(XmlParseHelperActionTestParseInvalid)
		{
			Scope globalScope;
			XmlParseHelperAction::SharedData tableSharedData(globalScope);
			XmlParseMaster parser(&tableSharedData);
			XmlParseHelperAction actionHelper;

			parser.AddHelper(actionHelper);
			Assert::ExpectException<std::exception>([&] { parser.ParseFromFile("Content/Invalid.xml"); });
		}

		TEST_METHOD(XmlParseHelperActionTestClone)
		{
			Scope globalScope;
			XmlParseHelperAction actionHelper;
			XmlParseHelperAction::SharedData tableSharedData(globalScope);
			XmlParseMaster parser(&tableSharedData);
			parser.AddHelper(actionHelper);

			// Test XmlParseHelperAction Clone()
			XmlParseHelperAction* clonedTable = actionHelper.Clone();
			Assert::IsTrue(clonedTable->IsClone());
			Assert::IsFalse(actionHelper.IsClone());
			delete clonedTable;

			// Test XmlParseHelperAction::SharedData Clone()
			XmlParseHelperAction::SharedData* clonedTableSharedData = tableSharedData.Clone();
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
	_CrtMemState XmlParseHelperActionTest::sStartMemState;
#endif

}