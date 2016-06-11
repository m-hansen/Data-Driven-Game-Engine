#include "pch.h"
#include "FooEntity.h"

namespace UnitTestLibraryDesktop
{
	RTTI_DEFINITIONS(FooEntity)

	FooEntity::FooEntity()
		: mHasBeenUpdated(false)
	{
	}
	
	void FooEntity::Update(Library::WorldState& state)
	{
		Entity::Update(state);
		mHasBeenUpdated = true;
	}

	bool FooEntity::WasUpdated() const
	{
		return mHasBeenUpdated;
	}

}
