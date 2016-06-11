#pragma once

#include "RTTI.h"

namespace UnitTestLibraryDesktop
{
	class BarRTTI final : public Library::RTTI
	{
		RTTI_DECLARATIONS(BarRTTI, Library::RTTI)
	public:
		BarRTTI() = default;
		~BarRTTI() = default;
	};
}
