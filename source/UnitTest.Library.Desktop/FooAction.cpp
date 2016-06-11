#include "pch.h"
#include "FooAction.h"

namespace UnitTestLibraryDesktop
{
	RTTI_DEFINITIONS(FooAction)

	FooAction::FooAction(const std::string& name)
		: Action(name)
	{
	}

	void FooAction::Update(Library::WorldState& state)
	{
		UNREFERENCED_PARAMETER(state);
	}

}
