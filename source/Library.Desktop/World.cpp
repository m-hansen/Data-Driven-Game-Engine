#include "pch.h"

namespace Library
{
	RTTI_DEFINITIONS(World)

	World::World()
		: mName(), mEventQueue(), mWorldState(nullptr), Attributed()
	{
		AddExternalSignature("name", 1, &mName);
		CreateTableDatum("sectors");
		Populate();
	}

	World::World(const std::string& name)
		: mName(name), mEventQueue(), mWorldState(nullptr), Attributed()
	{
		AddExternalSignature("name", 1, &mName);
		CreateTableDatum("sectors");
		Populate();
	}

	const std::string& World::Name() const
	{
		return mName;
	}

	void World::SetName(const std::string& name)
	{
		mName = name;
	}

	Datum& World::Sectors() const
	{
		Datum* foundSectors = Find("sectors");
		assert(foundSectors != nullptr);
		return *foundSectors;
	}

	Sector& World::CreateSector(const std::string& sectorName)
	{
		Sector* sector = new Sector(sectorName);
		assert(sector != nullptr);
		sector->SetWorld(*this);
		return *sector;
		/*RTTI* rtti = Factory<RTTI>::Create("Sector");
		assert(rtti != nullptr);

		Sector* sector = rtti->As<Sector>();
		assert(sector != nullptr);

		sector->SetName(sectorName);
		sector->SetWorld(*this);

		return *sector;*/
	}

	void World::Update(WorldState& state)
	{
		// TODO: Should the event queue be updated here?
		// eventQueue.Update(state);

		Datum& cachedSectors = Sectors();
		for (std::uint32_t i = 0; i < cachedSectors.Size(); ++i)
		{
			Sector* sector = cachedSectors[i].As<Sector>(); 
			assert(sector != nullptr);

			state.sector = sector;
			sector->Update(state);
		}

		state.sector = nullptr;
	}

	const Library::EventQueue& World::EventQueue() const
	{
		return *&mEventQueue;
	}

	Library::EventQueue& World::EventQueue()
	{
		return *&mEventQueue;
	}

	const WorldState& World::GetWorldState() const
	{
		assert(mWorldState);
		return *mWorldState;
	}

	void World::SetWorldState(WorldState& state)
	{
		mWorldState = &state;
	}

}
