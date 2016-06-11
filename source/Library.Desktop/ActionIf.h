#pragma once

#include "Action.h"

namespace Library
{
	class WorldState;

	/**
	 * Implements if/then conditional logic for Actions.
	 */
	class ActionIf : public Action
	{
		RTTI_DECLARATIONS(ActionIf, Action)

	public:
		/**
		 * Default constructor.
		 */
		ActionIf() = default;

		/**
		* Construct an ActionIf.
		*
		* @param conditionDatum a Datum that contains the condition as an integer
		*/
		explicit ActionIf(const std::string& conditionDatum);

		// Prevent copying
		ActionIf(const ActionIf& rhs) = delete;
		ActionIf& operator=(const ActionIf& rhs) = delete;

		/**
		* Default destructor.
		*/
		virtual ~ActionIf();

		/**
		* Evaluates and Updates the ActionIf.
		*
		* @param state the WorldState
		*/
		virtual void Update(WorldState& state) override;

		/**
		* Return whether or not the condition was met.
		* 
		* @return true if the consition was greater than zero, false otherwise
		*/
		bool WasConditionMet() const;

		Datum* mCondition;		/**< The datum that holds the condition to be evaluated. */
		Scope* mThen;			/**< The Scope that holds the then Actions */
		Scope* mElse;			/**< The Scope that holds the else Actions */

	private:
		bool mConditionMet;		/**< Holds a flag to determie if the condition was met */
	};

	ActionFactory(ActionIf)

}
