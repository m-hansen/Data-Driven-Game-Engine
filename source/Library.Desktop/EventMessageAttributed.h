#pragma once

#include "RTTI.h"
#include "Attributed.h"

namespace Library
{
	class World;

	/**
	 * Attributed container for the world and subtype for the Reaction system.
	 */
	class EventMessageAttributed : public Attributed
	{
		RTTI_DECLARATIONS(EventMessageAttributed, Attributed)

	public:
		/**
		 * Constructor.
		 */
		explicit EventMessageAttributed(const std::string& subtype = "", World* world = nullptr);

		/**
		 * Destructor.
		 */
		~EventMessageAttributed() = default;

		/**
		 * Returns the subtype of the event message.
		 *
		 * @return a string containing the subtype
		 */
		const std::string& GetSubtype() const;

		/**
		 * Sets the subtype string.
		 *
		 * @param subtype the name of the subtype as a string
		 */
		void SetSubtype(const std::string& subtype);

		/**
		 * Returns the World.
		 *
		 * @return the World
		 */
		const World& GetWorld() const;

		/**
		 * Sets the World.
		 *
		 * @param world the new World to assign
		 */
		void SetWorld(World& world);

	private:
		std::string mSubtype;	/**< The subtype as a string */
		World* mWorld;			/**< The World */
	};
}
