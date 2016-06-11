#include "pch.h"

namespace Library
{

	void IXmlParseHelper::Initialize()
	{
	}

	bool IXmlParseHelper::CharDataHandler(const XmlParseMaster::SharedData& sharedData, const char* buffer, const std::uint32_t bufferSize)
	{
		UNREFERENCED_PARAMETER(sharedData);
		UNREFERENCED_PARAMETER(buffer);
		UNREFERENCED_PARAMETER(bufferSize);
		return false;
	}

}
