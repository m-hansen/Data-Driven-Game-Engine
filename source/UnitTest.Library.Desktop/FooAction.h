#pragma once

#include <string>
#include "Action.h"
#include "Factory.h"

using namespace Library;

namespace UnitTestLibraryDesktop
{
	class WorldState;

	class FooAction final : public Action
	{
		RTTI_DECLARATIONS(FooAction, Action)
	public:
		FooAction(const std::string& name = "");
		virtual ~FooAction() = default;
		virtual void Update(Library::WorldState& state) override;
	};

	ActionFactory(FooAction)
}
