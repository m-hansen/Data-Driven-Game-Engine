#include "pch.h"
#include "ActionIf.h"

namespace Library
{
	RTTI_DEFINITIONS(ActionIf)

	ActionIf::ActionIf(const std::string& conditionAsString)
		: mThen(nullptr), mElse(nullptr), mConditionMet(false)
	{
		mCondition = new Datum();
		mCondition->SetType(Datum::DatumType::Integer);
		mCondition->SetFromString(conditionAsString);
	}

	ActionIf::~ActionIf()
	{
		delete mCondition;
	}

	void ActionIf::Update(WorldState& state)
	{
		UNREFERENCED_PARAMETER(state);

		if (mCondition->Get<std::int32_t>(0) > 0)
		{
			mConditionMet = true;

			// The condition is true if it is a positive, non-zero number
			for (std::uint32_t i = 0; i < mThen->Size(); ++i)
			{
				// Update each action in the then scope
				Action* action = mThen->As<Action>();
				assert(action != nullptr);

				state.action = action;
				action->Update(state);
			}
			state.action = nullptr;
		}
		else
		{
			mConditionMet = false;

			// The condition is false when it is negative or zero
			for (std::uint32_t i = 0; i < mElse->Size(); ++i)
			{
				// Update each action in the else scope
				Action* action = mElse->As<Action>();
				assert(action != nullptr);

				state.action = action;
				action->Update(state);
			}
			state.action = nullptr;
		}
	}

	bool ActionIf::WasConditionMet() const
	{
		return mConditionMet;
	}

}
