#include "pch.h"

namespace Library
{
	RTTI_DEFINITIONS(ActionList)

	ActionList::ActionList(const std::string& name)
		: mActions(Append("actions")), Action(name)
	{
		mActions.SetType(Datum::DatumType::Table);
	}

	void ActionList::Update(WorldState& state)
	{
		for (std::uint32_t i = 0; i < mActions.Size(); ++i)
		{
			Scope* scope = mActions.Get<Scope*>(i);
			assert(scope);
			Action* action = scope->As<Action>();
			assert(action);
			state.action = action;
			action->Update(state);
		}
	}

	Action& ActionList::CreateAction(const std::string& className, const std::string& instanceName)
	{
		Action* action = Factory<Action>::Create(className);
		assert(action != nullptr);
		action->SetName(instanceName);
		return *action;
	}

}
