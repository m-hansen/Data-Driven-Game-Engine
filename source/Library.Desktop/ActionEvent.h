#pragma once

#include "RTTI.h"
#include "Action.h"

namespace Library
{
	class World;

	/**
	 * Assists in the creation of attributed events from script.
	 */
	class ActionEvent : public Action
	{
		RTTI_DECLARATIONS(ActionEvent,Action)

	public:
		/**
		 * Constructs an ActionEvent.
		 */
		ActionEvent(const std::string& name = "");

		// Prevent move/copying
		ActionEvent(const ActionEvent& rhs) = delete;
		ActionEvent(ActionEvent&& rhs) = delete;
		ActionEvent& operator=(const ActionEvent rhs) = delete;

		/**
		 * Destructs an ActionEvent.
		 */
		~ActionEvent() = default;

		/**
		 * Create an attributed event, assign its world and subtype, copy all auxiliary parameters into the event and queue the event with the given delay.
		 *
		 * @param state the state of the world
		 */
		virtual void Update(WorldState& state) override;

	private:
		/**
		 * Initializes all of the signatures for ActionEvent.
		 */
		void InitializeSignatures();

		std::string mName;			/**< The name of the ActionEvent. */
		std::string mSubtype;		/**< Indicates the subtype for the event to generate. */
		std::int32_t mDelay;		/**< Indicates the delay associated with the generated event. */
	};

	ActionFactory(ActionEvent)

}
