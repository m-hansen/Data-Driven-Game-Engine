#pragma once

#include "RTTI.h"

namespace Library
{
	class WorldState;
	class EventPublisher;

	/**
	 * An Event/Action in response to another action. Ties the Action and Event systems together.
	 */
	class Reaction : public ActionList, public IEventSubscriber
	{
		RTTI_DECLARATIONS(Reaction, ActionList)

	public:
		/**
		 * Constructor.
		 *
		 * @param name the name of the Reaction
		 */
		explicit Reaction(const std::string& name);
			
		/**
		 * Destructor.
		 */
		virtual ~Reaction() = default;
	};
}
