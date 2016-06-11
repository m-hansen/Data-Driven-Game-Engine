#pragma once

#include "RTTI.h"

namespace UnitTestLibraryDesktop
{
	class FooRTTI final : public Library::RTTI
	{
		RTTI_DECLARATIONS(FooRTTI, Library::RTTI)
	public:
		FooRTTI() = default;
		~FooRTTI() = default;
	};
}
