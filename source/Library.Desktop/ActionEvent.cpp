#include "pch.h"

namespace Library
{
	RTTI_DEFINITIONS(ActionEvent)

	ActionEvent::ActionEvent(const std::string& name)
		: mName(name)
	{
		InitializeSignatures();
	}

	void ActionEvent::Update(WorldState& state)
	{
		EventMessageAttributed message;
		assert(state.world);
		World& world = *state.world;
		message.SetWorld(world);
		message.SetSubtype(mSubtype);

		Event<EventMessageAttributed>* newEvent = new Event<EventMessageAttributed>(message);
		assert(newEvent);

		// Copy all auxiliary parameters into the event
		for (std::uint32_t i = AuxiliaryBegin(); i < Size(); ++i)
		{
			message.AppendAuxiliaryAttribute(this[i].Name());
		}

		world.EventQueue().Enqueue(*newEvent, state.GetGameTime(), Milliseconds(mDelay));
	}

	void ActionEvent::InitializeSignatures()
	{
		AddExternalSignature("name", 1, &mName);
		AddExternalSignature("subtype", 1, &mSubtype);
		AddExternalSignature("delay", 1, &mDelay);
		Populate();
	}

}
