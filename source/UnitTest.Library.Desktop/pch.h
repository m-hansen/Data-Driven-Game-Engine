#pragma once

// Headers for CppUnitTest
#include "CppUnitTest.h"

#include <windows.h>
#include <chrono>
#include <thread>

// Headers needed for memory leak testing
#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#include "glm/glm.hpp"

#include "SList.h"
#include "Vector.h"
#include "Stack.h"
#include "HashMap.h"

#include "Datum.h"
#include "XmlParseMaster.h"

#include "Entity.h"
#include "Sector.h"
#include "World.h"
#include "WorldState.h"

#include "Action.h"
#include "ActionList.h"

#include "EventPublisher.h"
#include "IEventSubscriber.h"
#include "Event.h"
#include "EventQueue.h"

#include "Foo.h"
#include "FooAction.h"
#include "FooSubscriber.h"
