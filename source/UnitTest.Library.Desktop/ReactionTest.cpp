#include "pch.h"
#include "FooAction.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(ReactionTest)
	{
	public:
		TEST_METHOD(ReactionTestConstructor)
		{
			ActionEvent actionEvent;
			EventMessageAttributed eventMessageAttributed;
			ReactionAttributed reactionAttributed("Test");
			Assert::IsTrue(reactionAttributed.Name() == "Test");
		}
		
		TEST_METHOD(ReactionTestRtti)
		{
			ReactionAttributed reactionAttributed("Test");
			Assert::IsTrue(reactionAttributed.Is("ReactionAttributed"));
			Assert::IsNotNull(reactionAttributed.As<ReactionAttributed>());
			Assert::IsTrue(reactionAttributed.TypeName() == "ReactionAttributed");

			ActionEvent actionEvent;
			Assert::IsTrue(actionEvent.Is("ActionEvent"));
			Assert::IsNotNull(actionEvent.As<ActionEvent>());
			Assert::IsTrue(actionEvent.TypeName() == "ActionEvent");

			EventMessageAttributed eventMessageAttributed;
			Assert::IsTrue(eventMessageAttributed.Is("EventMessageAttributed"));
			Assert::IsNotNull(eventMessageAttributed.As<EventMessageAttributed>());
			Assert::IsTrue(eventMessageAttributed.TypeName() == "EventMessageAttributed");
		}

		TEST_METHOD(ReactionTestCreate)
		{
			// Action Events
			const std::string ActionEventClassName = "ActionEvent";
			const std::string ActionEventInstanceName = "MyActionEvent";

			ReactionAttributedFactory raFactory;
			ActionEventFactory factory;

			Entity entity("Entity");
			Action& factoryAction = entity.CreateAction(ActionEventClassName, ActionEventInstanceName);
			Assert::IsTrue(factoryAction.Name() == ActionEventInstanceName);

			// Reactions
			const std::string ReactionAttributedClassName = "ReactionAttributed";
			const std::string ReactionAttributedInstanceName = "MyReactionAttributed";
			
			Action& reaction = entity.CreateAction(ReactionAttributedClassName, ReactionAttributedInstanceName);
			Assert::IsTrue(reaction.Name() == ReactionAttributedInstanceName);
		}

		TEST_METHOD(ReactionTestUpdate)
		{
			World w("World");
			Library::WorldState state;
			state.world = &w;
			ActionEvent actionEvent;
			actionEvent.Update(state);
		}

	private:
#if defined(DEBUG) | defined(_DEBUG)
		static _CrtMemState sStartMemState;
#endif

	};

#if defined(DEBUG) | defined(_DEBUG)
	_CrtMemState ReactionTest::sStartMemState;
#endif

}
