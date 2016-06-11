#include "pch.h"

namespace Library
{
	RTTI_DEFINITIONS(ReactionAttributed)

	ReactionAttributed::ReactionAttributed(const std::string& name)
		: Reaction(name)
	{
		InitializeSignatures();
		Event<EventMessageAttributed>::Subscribe(*this);
	}

	ReactionAttributed::~ReactionAttributed()
	{
		// Remove ourself from the subscription list before destroying
		Event<EventMessageAttributed>::Unsubscribe(*this);
	}

	void ReactionAttributed::Notify(const EventPublisher& publisher)
	{
		Event<EventMessageAttributed>* newEvent = publisher.As<Event<EventMessageAttributed>>();
		assert(newEvent);

		EventMessageAttributed& message = const_cast<EventMessageAttributed&>(newEvent->Message());
		if (message.GetSubtype() == mSubtype)
		{
			// Copy the attribute arguments to this instance
			for (std::uint32_t i = message.AuxiliaryBegin(); i < message.Size(); ++i)
			{
				// TODO: Copy each attribute
				AppendAuxiliaryAttribute(message.GetSubtype());
			}
		}

		Update(const_cast<WorldState&>(message.GetWorld().GetWorldState()));
	}

	void ReactionAttributed::InitializeSignatures()
	{
		AddExternalSignature("subtype", 1, &mSubtype);
		Populate();
	}

}
