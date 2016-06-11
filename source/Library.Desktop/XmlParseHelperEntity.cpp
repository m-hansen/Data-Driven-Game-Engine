#include "pch.h"

namespace Library
{

#pragma region XmlParseHelperEntity

	XmlParseHelperEntity::XmlParseHelperEntity(const bool isClone)
		: mIsClone(isClone)
	{
	}

	bool XmlParseHelperEntity::StartElementHandler(const XmlParseMaster::SharedData& sharedData, const std::string& name,
		const HashMap<std::string, std::string>& attributes)
	{
		SharedData* customSharedData = static_cast<SharedData*>(&const_cast<XmlParseMaster::SharedData&>(sharedData));
			// TODO: fix this sharedData.As<SharedData>();

		if (customSharedData != nullptr)
		{
			HashMap<std::string, std::string>::Iterator nameAttribute = attributes.Find("name");
			std::string instanceName = nameAttribute->second;

			// Verify the name attribute exists and is valid
			if (nameAttribute != attributes.end() && !instanceName.empty())
			{
				if (name == "entity")
				{
					HashMap<std::string, std::string>::Iterator classAttribute = attributes.Find("class");
					std::string entityClassName = classAttribute->second;

					if (classAttribute != attributes.end() && !entityClassName.empty())
					{
						Sector* sector = customSharedData->mScope->As<Sector>();
						assert(sector != nullptr);

						Entity& entity = sector->CreateEntity(entityClassName, instanceName);
						Scope* entityAsScope = entity.As<Scope>();
						assert(entityAsScope != nullptr);

						customSharedData->mScope->Adopt(*entityAsScope, instanceName);
						customSharedData->mScope = static_cast<Scope*>(&entity);

						return true;
					}
				}
				else if (name == "sector")
				{
					World* world = customSharedData->mScope->As<World>();
					assert(world != nullptr);

					Sector& sector = world->CreateSector(instanceName);
					Scope* sectorAsScope = sector.As<Scope>();
					assert(sectorAsScope != nullptr);

					customSharedData->mScope->Adopt(*sectorAsScope, instanceName);
					customSharedData->mScope = sectorAsScope;

					return true;
				}
				else if (name == "world")
				{
					World* world = new World(instanceName);
					assert(world != nullptr);

					Scope* worldAsScope = world->As<Scope>();
					assert(worldAsScope != nullptr);

					customSharedData->mScope->Adopt(*worldAsScope, instanceName);
					customSharedData->mScope = worldAsScope;

					// TODO: Remove this
					/*World* world = new World(instanceName);
					assert(world != nullptr);
					Scope* rootScope = static_cast<Scope*>(world);
					customSharedData->mScope = rootScope;*/

					//World* world = new World(instanceName);
					//customSharedData->mScope = &customSharedData->mScope->AppendScope(instanceName); //static_cast<Scope*>(world);
					//customSharedData->mScope->
					return true;
				}
			}

		}

		return false;
	}

	bool XmlParseHelperEntity::EndElementHandler(const XmlParseMaster::SharedData& sharedData, const std::string& name)
	{
		SharedData* customSharedData = sharedData.As<SharedData>();

		if (customSharedData != nullptr)
		{
			if ((name == "entity") || (name == "sector"))
			{
				customSharedData->mScope = customSharedData->mScope->GetParent();
				return true;
			}
			/*if (name == "entity")
			{
				Entity* entity = customSharedData->mScope->As<Entity>();
				customSharedData->mScope = &entity->GetSector();
				return true;
			}
			else if (name == "sector")
			{
				Sector* sector = customSharedData->mScope->As<Sector>();
				customSharedData->mScope = sector->GetWorld();
				return true;
			}*/
			else if (name == "world")
			{
				return true;
			}
		}

		return false;
	}

	XmlParseHelperEntity* XmlParseHelperEntity::Clone()
	{
		return new XmlParseHelperEntity(true);
	}

	bool XmlParseHelperEntity::IsClone() const
	{
		return mIsClone;
	}

#pragma endregion

#pragma region SharedData

	RTTI_DEFINITIONS(XmlParseHelperEntity::SharedData)

		XmlParseHelperEntity::SharedData::SharedData(Scope& globalScope, const bool isClone)
		: mScope(&globalScope), mIsClone(isClone)
	{
	}

	XmlParseHelperEntity::SharedData* XmlParseHelperEntity::SharedData::Clone() const
	{
		assert(mScope != nullptr);
		return new SharedData(*mScope, true);
	}

	bool XmlParseHelperEntity::SharedData::IsClone() const
	{
		return mIsClone;
	}

#pragma endregion

}