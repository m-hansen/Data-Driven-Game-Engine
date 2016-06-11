#include "pch.h"
#include "FooAction.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(ActionTest)
	{
	public:

		TEST_METHOD(ActionTestConstructor)
		{
			const std::string FooActionName = "Foo";
			const std::string ActionListName = "ActionList";

			FooAction fooAction(FooActionName);
			Assert::IsTrue(fooAction.Name() == FooActionName);

			ActionList actionList(ActionListName);
			Assert::IsTrue(actionList.Name() == ActionListName);
		}

		TEST_METHOD(ActionTestUpdate)
		{
			Library::WorldState state;

			// Test action Update()
			FooAction fooAction("FooAction");
			fooAction.Update(state);

			// Test ActionList Update()
			ActionList actionList("ActionList");
			actionList.Update(state);
		}

		TEST_METHOD(ActionTestRtti)
		{
			FooAction fooAction("Foo");
			Assert::IsTrue(fooAction.Is("Action"));
			Assert::IsTrue(fooAction.Is(FooAction::TypeIdClass()));
			Assert::IsNotNull(fooAction.As<Action>());
			Assert::IsTrue(fooAction.TypeName() == "FooAction");

			ActionList actionList("List");
			Assert::IsTrue(actionList.Is("ActionList"));
			Assert::IsTrue(actionList.Is(ActionList::TypeIdClass()));
			Assert::IsNotNull(actionList.As<ActionList>());
			Assert::IsTrue(actionList.TypeName() == "ActionList");
		}

		TEST_METHOD(ActionTestSetEntity)
		{
			Entity e("e");
			FooAction fooAction("Foo");
			Assert::AreEqual(0U, e.Actions().Size());
			fooAction.SetEntity(e);
			Assert::AreEqual(1U, e.Actions().Size());
		}

		TEST_METHOD(ActionTestActionIf)
		{
			Library::WorldState state;

			// Test else
			{
				Scope* thenScope = new Scope();
				Scope* elseScope = new Scope();

				ActionIf actionIf("0");
				actionIf.mThen = thenScope;
				actionIf.mElse = elseScope;
				actionIf.Update(state);
				Assert::IsFalse(actionIf.WasConditionMet());

				delete elseScope;
				delete thenScope;
			}

			// Test then
			{
				Scope* thenScope = new Scope();
				Scope* elseScope = new Scope();

				ActionIf actionIf("1");
				actionIf.mThen = thenScope;
				actionIf.mElse = elseScope;
				actionIf.Update(state);
				Assert::IsTrue(actionIf.WasConditionMet());

				delete elseScope;
				delete thenScope;
			}

		}

	private:
#if defined(DEBUG) | defined(_DEBUG)
		static _CrtMemState sStartMemState;
#endif

	};

#if defined(DEBUG) | defined(_DEBUG)
	_CrtMemState ActionTest::sStartMemState;
#endif

}
