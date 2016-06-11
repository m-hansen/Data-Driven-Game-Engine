#include "pch.h"

namespace Library
{
	RTTI_DEFINITIONS(Sector)

	Sector::Sector()
		: mName(), mWorld(nullptr)
	{
		AddExternalSignature("name", 1, &mName);
		CreateTableDatum("entities");
		Populate();
	}

	Sector::Sector(const std::string& name)
		: mName(name), mWorld(nullptr)
	{
		AddExternalSignature("name", 1, &mName);
		CreateTableDatum("entities");
		Populate();
	}

	const std::string& Sector::Name() const
	{
		return mName;
	}

	void Sector::SetName(const std::string& name)
	{
		mName = name;
	}

	Datum& Sector::Entities()
	{
		Datum* foundEntities = Find("entities");
		assert(foundEntities != nullptr);
		return *foundEntities;
	}

	Entity& Sector::CreateEntity(const std::string& className, const std::string& instanceName)
	{
		RTTI* rtti = Factory<RTTI>::Create(className);
		if (rtti == nullptr)
		{
			throw std::exception("Factory is not registered.");
		}

		Entity* newEntity = rtti->As<Entity>();
		if (newEntity == nullptr)
		{
			delete rtti;
			throw std::exception("Type specified is not an Entity.");
		}

		newEntity->SetName(instanceName);
		newEntity->SetSector(*this);

		return *newEntity;
	}

	World* Sector::GetWorld() const
	{
		Scope* parentScope = GetParent();
		if (parentScope != nullptr)
		{
			return parentScope->As<World>();
		}

		return nullptr;
	}

	void Sector::SetWorld(World& world)
	{
		world.Adopt(*this, "sectors");
	}

	void Sector::Update(WorldState& state)
	{
		Datum& cachedEntities = Entities();
		for (std::uint32_t i = 0; i < cachedEntities.Size(); ++i)
		{
			Entity* entity = cachedEntities[i].As<Entity>();
			assert(entity != nullptr);

			state.entity = entity;
			entity->Update(state);
		}

		state.entity = nullptr;
	}

}
