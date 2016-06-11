#pragma once

#include "Attributed.h"

namespace Library
{
	class World;
	class WorldState;

	/**
	 * A Sector exists to partition code and data into pieces that we can manage in isolation. 
	 * A Sector is another container, but it is one which does not introduce a namespace.
	 */
	class Sector final : public Attributed
	{
		RTTI_DECLARATIONS(Sector, Attributed)

	public:
		/**
		 * Default constructor.
		 */
		Sector();

		/**
		 * Constructs a Sector.
		 *
		 * @param name the name of the Sector
		 */
		Sector(const std::string& name);

		/**
		 * Default deconstructor.
		 */
		virtual ~Sector() = default;

		/**
		 * Returns the name of the Sector.
		 *
		 * @return the name of the Sector
		 */
		const std::string& Name() const;

		/**
		 * Sets the name of the Sector.
		 *
		 * @param name the new name of the Sector
		 */
		void SetName(const std::string& name);

		/**
		 * Return the Datum that holds the entities withing this Sector.
		 *
		 * @retun the addredd of a Datum that contains the entities in the sector
		 */
		Datum& Entities();

		/**
		 * Creates a new Entity within this Sector.
		 *
		 * @param className the name of the class to be created
		 * @param instanceName the name of the instance of the created class
		 * @return the address of the newly created Entity
		 */
		Entity& CreateEntity(const std::string& className, const std::string& instanceName);

		/**
		 * Returns the World that this Sector belongs to.
		 * 
		 * @return address of the World that contains this Sector
		 */
		World* GetWorld() const;

		/** 
		 * Sets the wWorld this Sector belongs to.
		 *
		 * @param world the new world to assign the Sector to
		 */
		void SetWorld(World& world);

		/**
		 * Update logic for a Sector. Calls Update for each Entity contained within the Sector.
		 *
		 * @param state the state of the world
		 */
		void Update(WorldState& state);

	private:
		std::string mName;			/**< Name of the Sector */
		World* mWorld;				/**< The World this Sector belongs to */
	};
}
