#pragma once

#include <cstdint>

using namespace Library;

namespace UnitTestLibraryDesktop
{
	class XmlParseHelperFoo final : public IXmlParseHelper
	{
	public:
		class SharedData : public XmlParseMaster::SharedData
		{
			friend class XmlParseHelperFoo;
			RTTI_DECLARATIONS(SharedData, XmlParseMaster::SharedData)
		public:
			const std::string& GetXmlString() const;
		private:
			std::uint32_t mData;
			std::string mXmlString;
		};

		XmlParseHelperFoo() = default;
		virtual ~XmlParseHelperFoo() = default;

	private:
		virtual bool StartElementHandler(const XmlParseMaster::SharedData& sharedData,
			const std::string& name, const HashMap<std::string, std::string>& attributes) override;

		virtual bool EndElementHandler(const XmlParseMaster::SharedData& sharedData,
			const std::string& name) override;

		virtual bool CharDataHandler(const XmlParseMaster::SharedData& sharedData,
			const char* buffer, const std::uint32_t bufferSize) override;

		virtual XmlParseHelperFoo* Clone() override;
	};
}
