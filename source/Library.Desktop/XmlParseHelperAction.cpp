#include "pch.h"

namespace Library
{

#pragma region XmlParseHelperAction

	XmlParseHelperAction::XmlParseHelperAction(const bool isClone)
		: mIsClone(isClone)
	{
	}

	bool XmlParseHelperAction::StartElementHandler(const XmlParseMaster::SharedData& sharedData, const std::string& name,
		const HashMap<std::string, std::string>& attributes)
	{
		SharedData* customSharedData = sharedData.As<SharedData>();

		if (customSharedData != nullptr)
		{
			HashMap<std::string, std::string>::Iterator nameAttribute = attributes.Find("name");
			std::string instanceName = nameAttribute->second;

			// Verify the name attribute exists and is valid
			if (nameAttribute != attributes.end() && !instanceName.empty())
			{
				if (name == "action")
				{
					if (customSharedData->mScope->Is(Entity::TypeIdClass()))
					{
						std::string& className = attributes.Find("class")->second;
						Entity* entity = static_cast<Entity*>(customSharedData->mScope);
						Action& action = entity->CreateAction(className, instanceName);
						customSharedData->mScope = &action;
						return true;
					}
					else
					{
						throw std::exception("Actions can only be created within Entities.");
					}
				}
				else if (name == "reaction")
				{
					if (customSharedData->mScope->Is(Entity::TypeIdClass()))
					{
						std::string& className = attributes.Find("class")->second;
						Entity* entity = static_cast<Entity*>(customSharedData->mScope);
						if (entity)
						{
							Reaction* reaction = Factory<Reaction>::Create(className);
							reaction->SetName(instanceName);
							customSharedData->mScope = reaction;
						}
						return true;
					}
					else
					{
						throw std::exception("Reactions can only be created within Entities.");
					}
				}
				else if (name == "if")
				{
					// Verify an action is nested within an Entity
					Scope* parentScope = customSharedData->mScope->GetParent();
					if (!parentScope->Is("Entity"))
					{
						throw std::exception("The if tag must be nested within an Entity.");
					}
					// TODO: should a Scope be created to contain the then and else tags? This may not be needed 
					// since it will already be contained within a single ActionIf
					return true;
				}
				else if (name == "then")
				{
					Scope* containingActionScope = customSharedData->mScope->GetParent()->GetParent();
					ActionIf* containingAction = containingActionScope->As<ActionIf>();
					assert(containingAction != nullptr);
					std::string actionListName = attributes.Find("name")->second;
					containingAction->mThen->Adopt(*new ActionList(actionListName), actionListName);
					return true;
				}
				else if (name == "else")
				{
					Scope* containingActionScope = customSharedData->mScope->GetParent()->GetParent();
					ActionIf* containingAction = containingActionScope->As<ActionIf>();
					assert(containingAction != nullptr);
					std::string actionListName = attributes.Find("name")->second;
					containingAction->mElse->Adopt(*new ActionList(actionListName), actionListName);
					return true;
				}
			}

		}

		return false;
	}

	bool XmlParseHelperAction::EndElementHandler(const XmlParseMaster::SharedData& sharedData, const std::string& name)
	{
		SharedData* customSharedData = sharedData.As<SharedData>();

		if (customSharedData != nullptr)
		{
			if (name == "action" || name == "if" || name == "then" || name == "else")
			{
				Action* action = customSharedData->mScope->As<Action>();
				customSharedData->mScope = action->GetParent();
				return true;
			}
		}

		return false;
	}

	XmlParseHelperAction* XmlParseHelperAction::Clone()
	{
		return new XmlParseHelperAction(true);
	}

	bool XmlParseHelperAction::IsClone() const
	{
		return mIsClone;
	}

#pragma endregion

#pragma region SharedData

	RTTI_DEFINITIONS(XmlParseHelperAction::SharedData)

		XmlParseHelperAction::SharedData::SharedData(Scope& globalScope, const bool isClone)
		: mScope(&globalScope), mIsClone(isClone)
	{
	}

	XmlParseHelperAction::SharedData* XmlParseHelperAction::SharedData::Clone() const
	{
		assert(mScope != nullptr);
		return new SharedData(*mScope, true);
	}

	bool XmlParseHelperAction::SharedData::IsClone() const
	{
		return mIsClone;
	}

#pragma endregion

}