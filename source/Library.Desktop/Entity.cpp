#include "pch.h"

namespace Library
{
	RTTI_DEFINITIONS(Entity)

	Entity::Entity()
		: mName()
	{
		AddExternalSignature("name", 1, &mName);
		CreateTableDatum("actions");
		Populate();
	}

	Entity::Entity(const std::string& name)
		: mName(name)
	{
		AddExternalSignature("name", 1, &mName);
		CreateTableDatum("actions");
		Populate();
	}

	Entity::Entity(const Entity& rhs)
		: Entity(rhs.mName)
	{
	}

	Entity& Entity::operator=(const Entity& rhs)
	{
		if (rhs != *this)
		{
			Attributed::operator=(rhs);
			mName = rhs.mName;
		}

		return *this;
	}

	Datum& Entity::Actions()
	{
		Datum* foundActions = Find("actions");
		assert(foundActions != nullptr);
		return *foundActions;
	}

	Action& Entity::CreateAction(const std::string& className, const std::string& instanceName)
	{
		Action* action = Factory<Action>::Create(className);
		assert(action != nullptr);
		action->SetName(instanceName);
		action->SetEntity(*this);
		return *action;
	}

	const std::string& Entity::Name() const
	{
		return mName;
	}

	void Entity::SetName(const std::string& name)
	{
		mName = name;
	}

	Sector& Entity::GetSector()
	{
		Scope* parentScope = GetParent();
		if (parentScope == nullptr)
		{
			throw std::exception("Entity does not belong to a Sector.");
		}

		assert(parentScope->Is(Sector::TypeIdClass()));
		return static_cast<Sector&>(*parentScope);
	}

	void Entity::SetSector(Sector& sector)
	{
		sector.Adopt(*this, "entities");
	}

	void Entity::Update(WorldState& state)
	{
		Datum& cachedActions = Actions();
		for (std::uint32_t i = 0; i < cachedActions.Size(); ++i)
		{
			Action* action = cachedActions[i].As<Action>();
			assert(action != nullptr);

			state.action = action;
			action->Update(state);
		}

		state.action = nullptr;
	}

}
