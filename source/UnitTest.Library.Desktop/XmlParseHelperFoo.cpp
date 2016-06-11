#include "pch.h"
#include "XmlParseHelperFoo.h"

namespace UnitTestLibraryDesktop
{
	RTTI_DEFINITIONS(XmlParseHelperFoo::SharedData)

	bool XmlParseHelperFoo::StartElementHandler(const XmlParseMaster::SharedData& sharedData, 
		const std::string& name, const HashMap<std::string, std::string>& attributes)
	{
		XmlParseHelperFoo::SharedData* customSharedData = sharedData.As<XmlParseHelperFoo::SharedData>();
		if (customSharedData != nullptr && name == "foo")
		{
			customSharedData->mXmlString += "<" + name + " type=\"" + attributes.Find("type")->second + "\">";
			return true;
		}
		
		return false;
	}

	bool XmlParseHelperFoo::EndElementHandler(const XmlParseMaster::SharedData& sharedData, const std::string& name)
	{
		XmlParseHelperFoo::SharedData* customSharedData = sharedData.As<XmlParseHelperFoo::SharedData>();
		if (customSharedData != nullptr && name == "foo")
		{
			customSharedData->mXmlString += "<//" + name + ">";
			return true;
		}

		return false;
	}

	bool XmlParseHelperFoo::CharDataHandler(const XmlParseMaster::SharedData& sharedData, const char* buffer, const std::uint32_t bufferSize)
	{
		UNREFERENCED_PARAMETER(bufferSize);

		XmlParseHelperFoo::SharedData* customSharedData = sharedData.As<XmlParseHelperFoo::SharedData>();
		if (customSharedData != nullptr)
		{
			customSharedData->mXmlString += buffer;
			customSharedData->mData = atoi(buffer);
			return true;
		}

		return false;
	}

	XmlParseHelperFoo* XmlParseHelperFoo::Clone()
	{
		return new XmlParseHelperFoo();
	}

#pragma region SharedData

	const std::string& XmlParseHelperFoo::SharedData::GetXmlString() const
	{
		return mXmlString;
	}

#pragma endregion

}
