#pragma once

#include "Attributed.h"

namespace Library
{
	class Action;
	class Sector;
	class WorldState;

	/**
	 * An AttributedScope that wraps a table. Entities automatically populate
	 * their tables based on information known at compile time.
	 */
	class Entity : public Attributed
	{
		RTTI_DECLARATIONS(Entity, Attributed)

	public:
		/**
		 * Default constructor.
		 */
		Entity();

		/**
		 * Construct an Entity with a name.
		 *
		 * @param name the name of the Entity
		 */
		Entity(const std::string& name);

		/**
		 * Deep-copy an Entity.
		 *
		 * @param rhs the Entity to copy from
		 */
		Entity(const Entity& rhs);

		/**
		 * Deep-copy an Entity.
		 *
		 * @param rhs the Entity to copy from
		 */
		Entity& operator=(const Entity& rhs);

		/**
		 * Prevent an Entity from being moved, can re-enable when Attributed 
		 * (and supporting containers) all support move semantics.
		 */
		Entity(Entity&& rhs) = delete;

		/**
		 * Default decnstructor.
		 */
		virtual ~Entity() = default;

		/**
		 * Returns a Datum of Actions.
		 *
		 * @return the Datum of Actions
		 */
		Datum& Actions();

		/**
		 * Takes a class name and an instance name to instantiate a new Action object and adopt it into the Actions datum.
		 *
		 * @param className the name of the class to be created
		 * @param instanceName the name of the specific instance of a class
		 * @return the reference to a newly created Action
		 */
		Action& CreateAction(const std::string& className, const std::string& instanceName);

		/**
		 * Get the name of an Entity.
		 *
		 * @return the name of the Entity
		 */
		const std::string& Name() const;

		/**
		 * Sets the name of an Entity.
		 *
		 * @param name the new name of the Entity
		 */
		void SetName(const std::string& name);

		/**
		 * Gets the current Sector the Entity resides in.
		 *
		 * @return the current Sector
		 */
		Sector& GetSector();

		/**
		 * Sets the current Sector for an Entity.
		 *
		 * @param sector the new Sector for the Entity
		 */
		void SetSector(Sector& sector);

		/**
		 * Updates the Entitie's logic.
		 *
		 * @param state the state of the current world
		 */
		virtual void Update(WorldState& state);

	private:
		std::string mName;			/**< The name of the Entity */
	};

	ConcreteFactory(Entity, RTTI)
}
