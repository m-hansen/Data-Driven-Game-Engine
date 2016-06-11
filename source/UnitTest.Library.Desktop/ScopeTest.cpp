#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(ScopeTest)
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

		TEST_METHOD(ScopeTestConstructor)
		{
			Scope scope;
			Assert::AreEqual(0U, scope.Size());
			Assert::IsTrue(scope.GetParent() == nullptr);

			Scope scopeWithCapacity(10);
			Assert::AreEqual(0U, scopeWithCapacity.Size());
			Assert::IsTrue(scopeWithCapacity.GetParent() == nullptr);
		}

		TEST_METHOD(ScopeTestCopyConstructor)
		{
			Scope existingScope;
			existingScope.Append("first");
			Assert::AreEqual(1U, existingScope.Size());

			Scope newScope = existingScope;
			Assert::AreEqual(existingScope.Size(), newScope.Size());
			Assert::IsTrue(existingScope.GetParent() == newScope.GetParent());
		}

		TEST_METHOD(ScopeTestAssignmentOperator)
		{
			Scope existingScope;
			existingScope.Append("first");
			Assert::AreEqual(1U, existingScope.Size());

			Scope newScope;
			newScope = existingScope;
			Assert::AreEqual(existingScope.Size(), newScope.Size());
			Assert::IsTrue(existingScope.GetParent() == newScope.GetParent());
		}

		TEST_METHOD(ScopeTestSubscriptOperator)
		{
			Scope scope;
			Datum* datum = &scope["test"];
			*datum = "value";
			Assert::ExpectException<std::exception>([&] { scope[999]; });
			Assert::IsTrue(datum->Get<std::string>(0) == "value");
			Assert::IsTrue(datum[0] == "value");
			Assert::IsTrue(scope[0] == "value");
		}

		TEST_METHOD(ScopeTestComparisonOperator)
		{
			// Test comparison of single scopes
			Scope scopeA;
			scopeA.Append("apple");
			scopeA.Append("banana");

			Scope* scopeB = &scopeA;
			Scope scopeACopy = scopeA;

			Scope scopeC;
			scopeC.Append("apple");
			scopeC.Append("cat");

			Scope scopeD;
			scopeD.Append("cat");
			scopeC.Append("apple");

			Scope scopeE;
			scopeE.Append("dog");

			Assert::IsTrue(scopeA == *scopeB);
			Assert::IsTrue(*scopeB == scopeA);
			Assert::IsTrue(scopeA == scopeACopy);
			Assert::IsFalse(scopeA == scopeC);
			Assert::IsFalse(scopeA == scopeD);
			Assert::IsFalse(scopeC == scopeD);
			Assert::IsFalse(scopeD == scopeE);

			Assert::IsFalse(scopeA != *scopeB);
			Assert::IsFalse(*scopeB != scopeA);
			Assert::IsFalse(scopeA != scopeACopy);
			Assert::IsTrue(scopeA != scopeC);
			Assert::IsTrue(scopeA != scopeD);
			Assert::IsTrue(scopeC != scopeD);
			Assert::IsTrue(scopeD != scopeE);

			// Test comparison of nested scopes
			Scope parentScopeA;
			Scope* childScopeA = &parentScopeA.AppendScope("ChildScope");
			Datum* intDatumA = &childScopeA->Append("IntegerData");
			*intDatumA = 5;

			Scope* parentScopeB = &parentScopeA;
			Scope parentScopeACopy = parentScopeA;

			Assert::IsTrue(parentScopeA == *parentScopeB);
			Assert::IsTrue(parentScopeA == parentScopeACopy);

			Assert::IsFalse(parentScopeA != *parentScopeB);
			Assert::IsFalse(parentScopeA != parentScopeACopy);
		}

		TEST_METHOD(ScopeTestClear)
		{
			Scope scope;
			Scope& nestedScope = scope.AppendScope("NestedScope");
			Datum& intDatum = scope.Append("Integer");
			intDatum = 1;
			Datum& floatDatum = nestedScope.Append("Float");
			floatDatum = 2.0f;
			Assert::AreEqual(2U, scope.Size());
			Assert::AreEqual(1U, nestedScope.Size());
			scope.Clear();
			Assert::AreEqual(0U, scope.Size());
		}

		TEST_METHOD(ScopeTestOrphan)
		{
			Scope parentScope;
			Assert::AreEqual(0U, parentScope.Size());
			parentScope.Append("Integer");
			Assert::AreEqual(1U, parentScope.Size());

			Scope childScope;
			Assert::AreEqual(0U, childScope.Size());
			childScope.Append("Float");
			Assert::AreEqual(1U, childScope.Size());

			parentScope.Adopt(childScope, "ChildScope");
			Assert::AreEqual(2U, parentScope.Size());

			childScope.Orphan();
			Assert::AreEqual(1U, childScope.Size());
			Assert::IsNull(childScope.GetParent());
		}

		TEST_METHOD(ScopeTestFind)
		{
			Scope scope;
			Assert::IsNull(scope.Find(""));
			Assert::IsTrue(scope.Find("Expecting nullptr") == nullptr);
			Datum& datum = scope.Append("Test");
			datum = 5;
			Datum* foundScope = scope.Find("Test");
			Assert::IsNotNull(foundScope);
			Datum& foundDatum = *foundScope;
			Assert::IsTrue(foundDatum == datum);
		}

		TEST_METHOD(ScopeTestSearch)
		{
			// Search through a scope
			Scope scope;
			Datum& floatDatum = scope.Append("Float");
			floatDatum = 1.0f;
			Assert::IsNull(scope.Search("NotFound"));
			Scope& nestedScope = scope.AppendScope("NestedScope");
			Datum& intDatum = nestedScope.Append("Integer");
			intDatum.Set(0, 0);
			intDatum.Set(1, 1);
			intDatum.Set(2, 2);
			Scope* foundScope = nullptr;
			Datum* foundDatum = nestedScope.Search("Integer", &foundScope);
			Assert::IsNotNull(foundDatum);
			Assert::IsTrue(*foundDatum == intDatum);
			Assert::IsTrue(*foundScope == nestedScope);

			// Search through a nested scope
			Scope* foundInNestedScope = nullptr;
			Datum* foundNestedDatum = nestedScope.Search("Float", &foundInNestedScope);
			Assert::IsTrue(*foundNestedDatum == floatDatum);
			Assert::IsTrue(foundInNestedScope == &scope);
		}

		TEST_METHOD(ScopeTestAppend)
		{
			Scope scope;
			Assert::ExpectException<std::exception>([&] { scope.Append(""); });

			// Append to create a new entry
			scope.Append("test");
			Assert::AreEqual(1U, scope.Size());
			Datum* foundDatum = scope.Find("test");
			Assert::IsNotNull(foundDatum);
			foundDatum->Set(0, 0);
			Assert::IsTrue(foundDatum[0] == scope.Find("test")->Get<std::int32_t>(0));

			// Append with an existing entry
			scope.Append("test");
			Assert::AreEqual(1U, scope.Size());
			Assert::IsTrue(foundDatum[0] == scope.Find("test")->Get<std::int32_t>(0));
		}

		TEST_METHOD(ScopeTestAppendScope)
		{
			Scope scope;
			Assert::ExpectException<std::exception>([&] { scope.AppendScope(""); });

			// Attempt to append an integer as a scope
			Datum& intDatum = scope.Append("Integer");
			intDatum = 5;
			Assert::ExpectException<std::exception>([&] { scope.AppendScope("Integer"); });

			// Append to create a new entry
			Scope& scopeA = scope.AppendScope("test");
			Assert::IsTrue(scopeA.GetParent() == &scope);
			Assert::AreEqual(2U, scope.Size());
			Datum* foundDatum = scope.Find("test");
			Assert::IsNotNull(foundDatum);

			// Append with an existing entry
			scope.AppendScope("test");
			Assert::AreEqual(2U, scope.Size());
		}

		TEST_METHOD(ScopeTestAdopt)
		{
			Scope parentScope;

			Scope scope;
			Assert::IsNull(scope.GetParent());
			parentScope.Adopt(scope, "MyScope");
			Assert::IsTrue(scope.GetParent() == &parentScope);
			Assert::IsNotNull(parentScope.Find("MyScope"));
		}

		TEST_METHOD(ScopeTestGetParent)
		{
			Scope scope;
			Assert::IsNull(scope.GetParent());
			Scope& newScope = scope.AppendScope("NewScope");
			Assert::IsTrue(*newScope.GetParent() == scope);
		}

		TEST_METHOD(ScopeTestFindContainedScope)
		{
			Scope topLevelScope;
			Datum& intDatum = topLevelScope.Append("Integer");
			intDatum = 1;
			Scope& nestedScope = topLevelScope.AppendScope("NestedeScope");
			Datum& floatDatum = nestedScope.Append("Float");
			floatDatum = 5.0f;
			Assert::IsTrue(*nestedScope.GetParent() == topLevelScope);

			Datum* foundDatum = topLevelScope.FindContainedScope(nestedScope);
			Assert::IsNotNull(foundDatum);

			Scope emptyScope;
			Assert::IsNull(emptyScope.FindContainedScope(nestedScope));
		}

		TEST_METHOD(ScopeTestFindName)
		{
			Scope scope;
			Scope& nestedScope = scope.AppendScope("NestedScope");
			Datum& intDatum = nestedScope.Append("Integer");
			intDatum = 5;
			Assert::IsTrue(scope.FindName(nestedScope) == "NestedScope");

			Scope invalidParent;
			Assert::ExpectException<std::exception>([&] {invalidParent.FindName(nestedScope); });

			Scope emptyParent;
			Scope& emptyNestedScope = emptyParent.AppendScope("EmptyNestedScope");
			Assert::ExpectException<std::exception>([&] {invalidParent.FindName(emptyNestedScope); });
		}

		TEST_METHOD(ScopeTestSize)
		{
			Scope scopeWithCapacity(5);
			Assert::AreEqual(0U, scopeWithCapacity.Size());

			Scope scope;
			Assert::AreEqual(0U, scope.Size());
			scope.Append("one");
			Assert::AreEqual(1U, scope.Size());
			scope.Append("two");
			Assert::AreEqual(2U, scope.Size());
			scope.Append("one");
			Assert::AreEqual(2U, scope.Size());
			scope["three"];
			Assert::AreEqual(3U, scope.Size());
			scope["one"];
			Assert::AreEqual(3U, scope.Size());
			scope.Clear();
			Assert::AreEqual(0U, scope.Size());
			scope.Append("one");
			Assert::AreEqual(1U, scope.Size());
			scope["one"];
			Assert::AreEqual(1U, scope.Size());
			scope.Append("new");
			Assert::AreEqual(2U, scope.Size());
		}

	private:
#if defined(DEBUG) | defined(_DEBUG)
		static _CrtMemState sStartMemState;
#endif

	};

#if defined(DEBUG) | defined(_DEBUG)
	_CrtMemState ScopeTest::sStartMemState;
#endif

}