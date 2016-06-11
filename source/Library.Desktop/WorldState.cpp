#include "pch.h"

namespace Library
{

	WorldState::WorldState()
		: mGameTime(new GameTime()), world(nullptr), sector(nullptr), entity(nullptr), action(nullptr)
	{
	}

	WorldState::~WorldState()
	{
		delete mGameTime;
	}

	GameTime& WorldState::GetGameTime() const
	{
		assert(mGameTime != nullptr);
		return *mGameTime;
	}

	void WorldState::SetGameTime(GameTime& gameTime)
	{
		mGameTime = &gameTime;
	}

}
