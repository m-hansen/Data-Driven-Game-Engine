#include "pch.h"

namespace Library
{
	RTTI_DEFINITIONS(Reaction)

	Reaction::Reaction(const std::string& name) 
		: ActionList(name)
	{
	}
}
