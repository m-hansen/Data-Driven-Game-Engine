#pragma once

#include "Action.h"
#include "Vector.h"

namespace Library
{
	class WorldState;

	class ActionList : public Action
	{
		RTTI_DECLARATIONS(ActionList, Action)
	public:
		/**
		 * Default constructor.
		 *
		 * @param name (optional) the name of the ActionList
		 */
		ActionList(const std::string& name = "");

		/**
		 * Default dtor.
		 */
		virtual ~ActionList() = default;

		/**
	 	 * Updates each Action in the ActionList.
		 *
		 * @param state the WorldState
		 */
		virtual void Update(WorldState& state) override;

		/**
		 * Creates an Action in the ActionList.
		 *
		 * @param className the name of the class
		 * @param instanceName the name of the specific instance
		 * @return the newly created Action reference
		 */
		Action& CreateAction(const std::string& className, const std::string& instanceName);

	private:
		Datum& mActions;			/**< List of Actions as datums*/
	};

	ActionFactory(ActionList)

}
