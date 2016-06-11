#pragma once

#include "GameTime.h"

namespace Library
{
	/**
	 * WorldState represents the current micro-state of processing, including the current World, 
	 * Sector, Entity, and Action (defined in the next assignment). WorldState serves the role 
	 * of passing data between various layers in the World, so acts like function arguments.
	 */
	class WorldState
	{
	public:
		class World* world;
		class Sector* sector;
		class Entity* entity;
		class Action* action;

		/**
		 * Default constructor for a WorldState.
		 */
		WorldState();

		// Prevent a WorldState from being moved or copied
		WorldState(const WorldState& rhs) = delete;
		WorldState(WorldState&& rhs) = delete;
		WorldState& operator=(const WorldState& rhs) = delete;

		/**
		 * Deconstructor for a WorldState.
		 */
		~WorldState();

		/**
		 * Returns the current GameTime.
		 *
		 * @return the current GameTime
		 */
		GameTime& GetGameTime() const;

		/**
		 * Sets the current GameTime.
		 *
		 * @param gameTime the current GameTime
		 */
		void SetGameTime(GameTime& gameTime);

	private:
		GameTime* mGameTime;			/**< The current GameTime */
	};
}
