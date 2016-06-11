#pragma once

#include "Reaction.h"

namespace Library
{
	class EventPublisher;

	/**
	 * Allows for Reaction notifications. This may be specialised for specific types of Reactions.
	 */
	class ReactionAttributed final : public Reaction
	{
		RTTI_DECLARATIONS(ReactionAttributed, Reaction)

	public:
		/**
		 * Constructor.
		 *
		 * @param name specifies the name of this reaction
		 */
		explicit ReactionAttributed(const std::string& name = "");

		/** 
		 * Destructor.
		 */
		virtual ~ReactionAttributed();

		/**
		 * Notification to trigger when an event is received. Generally will invoke
		 * ActionList::Update()
		 *
		 * @param the event from a publisher
		 */
		virtual void Notify(const EventPublisher& publisher) override;

		/**
		 * Initializes internal and external attributes.
		 */
		void InitializeSignatures();

	private:
		std::string mSubtype;		/**< The subtype. */
	};

	ActionFactory(ReactionAttributed)

}
