#include "pch.h"
#include "EventMessageAttributed.h"

namespace Library
{
	RTTI_DEFINITIONS(EventMessageAttributed)

	EventMessageAttributed::EventMessageAttributed(const std::string& subtype, World* world)
		: mSubtype(subtype), mWorld(world)
	{
	}

	const std::string& EventMessageAttributed::GetSubtype() const
	{
		return mSubtype;
	}

	void EventMessageAttributed::SetSubtype(const std::string& subtype)
	{
		mSubtype = subtype;
	}

	const World& EventMessageAttributed::GetWorld() const
	{
		assert(mWorld);
		return *mWorld;
	}

	void EventMessageAttributed::SetWorld(World& world)
	{
		mWorld = &world;
	}

}