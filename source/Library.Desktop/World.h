#pragma once

#include "Attributed.h"
#include "EventQueue.h"

namespace Library
{
	class Datum;
	class Sector;
	class WorldState;

	/**
	 * A World defines a global Scope – the Scope that all other objects in the simulation share.
	 */
	class World final : public Attributed
	{
		RTTI_DECLARATIONS(World, Attributed)

	public:
		/**
		* Constructs a World.
		*/
		World();

		/**
		 * Constructs a World.
		 *
		 * @param name the name of the World
		 */
		World(const std::string& name);

		// Prevent a World from being moved or copied
		World(const World& rhs) = delete;
		World (World&& rhs) = delete;
		World& operator=(const World& rhs) = delete;

		/**
		 * Destructs a World.
		 */
		virtual ~World() = default;

		/**
		 * Returns the name of the World.
		 *
		 * @return the name of the World
		 */
		const std::string& Name() const;

		/**
		 * Sets the name of the World.
		 *
		 * @param name the new name of the World
		 */
		void SetName(const std::string& name);

		/**
		 * Returns a Datum that holds the Sectors contained within the World.
		 *
		 * @return a Datum that holds the Sectors contained within the World
		 */
		Datum& Sectors() const;

		/**
		 * Creates a new Sector within the World.
		 *
		 * @param sectorName the name of the new Sector
		 * @return the newly created Sector
		 */
		Sector& CreateSector(const std::string& sectorName);

		/** 
		 * Calls Update for each Sector within the World.
		 *
		 * @param state the state of the world
		 */
		void Update(WorldState& state);

		/**
		 * Returns the address of the world's global event queue.
		 *
		 * @return the EventQueue
		 */
		const Library::EventQueue& EventQueue() const;

		/**
		 * Returns the address of the world's global event queue.
		 *
		 * @return the EventQueue
		 */
		Library::EventQueue& EventQueue();

		/**
		 * Returns the address of the WorldState.
		 *
		 * @return the address of the WorldState
		 */
		const WorldState& GetWorldState() const;

		/**
		 * Sets the WorldState object.
		 *
		 * @param state the WorldState
		 */
		void SetWorldState(WorldState& state);

	private:
		std::string mName;						/**< The name of the World */
		Library::EventQueue mEventQueue;		/**< The global event queue for a world */
		WorldState* mWorldState;				/**< The WorldState. */
	};
}
