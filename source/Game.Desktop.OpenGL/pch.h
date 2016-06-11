#pragma once

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

// Include additional OpenGL headers
#include "GL/gl3w.h"			// This must be included before any other OpenGL files
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
