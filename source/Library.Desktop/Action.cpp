#include "pch.h"

namespace Library
{
	RTTI_DEFINITIONS(Action)

	Action::Action(const std::string& name)
		: mName(name)
	{
		AddExternalSignature("name", 1, &mName);
		Populate();
	}

	const std::string& Action::Name() const
	{
		return mName;
	}

	void Action::SetName(const std::string& name)
	{
		mName = name;
	}

	void Action::SetEntity(Entity& entity)
	{
		entity.Adopt(*this, "actions");
	}

}
