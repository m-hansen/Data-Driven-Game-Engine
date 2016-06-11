#pragma once

#include "RTTI.h"
#include "Entity.h"
#include "Factory.h"

using namespace Library;

namespace UnitTestLibraryDesktop
{
	class Library::WorldState;

	class FooEntity : public Entity
	{
		RTTI_DECLARATIONS(FooEntity, Entity)

	public:
		FooEntity();
		virtual ~FooEntity() = default;
		virtual void Update(Library::WorldState& state);
		bool WasUpdated() const;

	private:
		bool mHasBeenUpdated;
	};

	//ConcreteFactory(FooEntity, RTTI)

}
