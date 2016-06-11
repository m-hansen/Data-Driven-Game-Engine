#include "pch.h"
#include "AttributedFoo.h"

using namespace Library;

namespace UnitTestLibraryDesktop
{
	RTTI_DEFINITIONS(AttributedFoo)

	AttributedFoo::AttributedFoo()
		: mIntData(0), mFloatData(0.0f), mVectorData(), mMatrixData(), mStringData(""), mPointerData(nullptr)
	{
		glm::vec4 zeroVec4 = glm::vec4(0.0f);
		glm::mat4 zeroMat4 = glm::mat4(0.0f);
		std::string str = "DefaultString";

		AddInternalSignature("Internal Integer", &mIntData, 1);
		AddInternalSignature("Internal Float", &mFloatData, 1);
		AddInternalSignature("Internal Vector", &mVectorData, 1);
		AddInternalSignature("Internal Matrix", &mMatrixData, 1);
		AddInternalSignature("Internal Table", &mTableData, 1);
		AddInternalSignature("Internal String", &mStringData, 1);
		AddInternalSignature("Internal Pointer", &mPointerData, 1);

		AddExternalSignature("External Integer", 1, &mIntData);
		AddExternalSignature("External Float", 1, &mFloatData);
		AddExternalSignature("External Vector", 1, &mVectorData);
		AddExternalSignature("External Matrix", 1, &mMatrixData);
		AddExternalSignature("External String", 1, &mStringData);
		AddExternalSignature("External Pointer", 1, &mPointerData);

		Populate();
	}

	AttributedFoo::~AttributedFoo()
	{
		delete mPointerData;
	}
}