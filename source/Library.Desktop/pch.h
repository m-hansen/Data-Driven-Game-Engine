#pragma once

#include <windows.h>
#include <cstdint>
#include <cstring>
#include <vector>
#include <stdexcept>
#include <new>
#include <mutex>
#include <future>

#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"

#include "RTTI.h"

#include "SList.h"
#include "Vector.h"
#include "HashMap.h"

#include "Datum.h"
#include "Scope.h"

#include "IXmlParseHelper.h"
#include "XmlParseMaster.h"
#include "XmlParseHelperTable.h"
#include "XmlParseHelperEntity.h"
#include "XmlParseHelperAction.h"

#include "Factory.h"

#include "Entity.h"
#include "Sector.h"
#include "WorldState.h"
#include "World.h"

#include "Action.h"
#include "ActionList.h"
#include "ActionIf.h"

#include "EventPublisher.h"
#include "IEventSubscriber.h"
#include "EventQueue.h"
#include "Event.h"

#include "Reaction.h"
#include "ReactionAttributed.h"
#include "EventMessageAttributed.h"
#include "ActionEvent.h"
