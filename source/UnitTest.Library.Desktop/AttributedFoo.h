#pragma once

#include <cstdint>
#include "Attributed.h"

namespace UnitTestLibraryDesktop
{
	class AttributedFoo : public Library::Attributed
	{
		RTTI_DECLARATIONS(AttributedFoo, Attributed)

	public:
		AttributedFoo();
		virtual ~AttributedFoo();
	private:
		std::int32_t mIntData;
		float mFloatData;
		glm::vec4 mVectorData;
		glm::mat4 mMatrixData;
		Scope* mTableData;
		std::string mStringData;
		RTTI* mPointerData;
	};
}
