#pragma once

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

// DirectX Header Files
#include <d3d11_1.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>

#include "SList.h"
#include "GameException.h"

#define ReleaseObject(object) if((object) != nullptr) { object->Release(); object = nullptr; }