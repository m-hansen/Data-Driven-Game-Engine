#include "pch.h"

namespace Library
{

#pragma region XmlParseMaster

	XmlParseMaster::XmlParseMaster(SharedData* sharedData, const XML_Char* encoding)
		: mHelpers(), mSharedData(sharedData), mParser(XML_ParserCreate(encoding)), mParsedFileName(""), mIsClone(false)
	{
		mSharedData->SetXmlParseMaster(*this);
	}

	XmlParseMaster::~XmlParseMaster()
	{
		if (mIsClone)
		{
			for (const auto& helper : mHelpers)
			{
				delete helper;
			}

			delete mSharedData;
		}

		mSharedData = nullptr;
		XML_ParserFree(mParser);
	}

	XmlParseMaster* XmlParseMaster::Clone() const
	{
		XmlParseMaster* newParser = new XmlParseMaster(mSharedData->Clone());
		newParser->mIsClone = true;

		for (const auto& helper : mHelpers)
		{
			newParser->AddHelper(*helper->Clone());
		}

		return newParser;
	}

	bool XmlParseMaster::IsClone() const
	{
		return mIsClone;
	}

	void XmlParseMaster::AddHelper(IXmlParseHelper& helper)
	{
		if (mIsClone)
		{
			throw std::exception("Connot add helpers to clones.");
		}

		mHelpers.PushBack(&helper);
	}

	void XmlParseMaster::RemoveHelper(IXmlParseHelper& helper)
	{
		if (mIsClone)
		{
			throw std::exception("Connot remove helpers from clones.");
		}

		mHelpers.Remove(&helper);
	}

	void XmlParseMaster::Parse(const char* buffer, const std::uint32_t bufferSize, const bool isFirstChunk, const bool isLastChunk)
	{
		if (buffer == nullptr)
		{
			throw std::exception("Invalid buffer.");
		}

		if (isFirstChunk)
		{
			Reset();
		}

		XML_Status parseStatus = XML_Parse(mParser, buffer, bufferSize, isLastChunk);
		if (parseStatus == XML_STATUS_ERROR)
		{
			throw std::exception("There was an error parsing the XML file.");
		}
	}

	void XmlParseMaster::ParseFromFile(const std::string& fileName)
	{
		std::ifstream file(fileName);
		if (file.bad())
		{
			throw std::exception("The file could not be opened.");
		}

		std::string line;
		bool isFirstRun = true;
		while (std::getline(file, line))
		{
			Parse(line.c_str(), static_cast<std::uint32_t>(line.length()), isFirstRun, file.eof());
			isFirstRun = false;
		}

		mParsedFileName = fileName;
		file.close();
	}

	const std::string& XmlParseMaster::GetFileName() const
	{
		return mParsedFileName;
	}

	const XmlParseMaster::SharedData* XmlParseMaster::GetSharedData() const
	{
		return mSharedData;
	}

	void XmlParseMaster::SetSharedData(SharedData& data)
	{
		if (mIsClone)
		{
			throw std::exception("Connot set shared data for clones.");
		}

		mSharedData = &data;
		mSharedData->SetXmlParseMaster(*this);
	}

	void XmlParseMaster::StartElementHandler(void* userData, const XML_Char* name, const XML_Char** attributes)
	{
		assert(userData != nullptr);

		// Build the HashMap of attributes before making calls to each helper
		HashMap<std::string, std::string> attributeMap(10U);
		for (std::uint32_t i = 0; attributes[i] != nullptr; i += 2)
		{
			attributeMap.Insert(std::make_pair(attributes[i], attributes[i + 1]));
		}
		
		SharedData* sharedData = reinterpret_cast<SharedData*>(userData);
		sharedData->IncrementDepth();
		XmlParseMaster* parser = sharedData->GetXmlParseMaster();
		if (parser == nullptr)
		{
			throw std::exception("Invalid parser.");
		}

		for (const auto& helper : parser->mHelpers)
		{
			if (helper->StartElementHandler(*sharedData, name, attributeMap))
			{
				break;
			}
		}

	}

	void XmlParseMaster::EndElementHandler(void* userData, const XML_Char* name)
	{
		assert(userData != nullptr);

		SharedData* sharedData = reinterpret_cast<SharedData*>(userData);
		XmlParseMaster* parser = sharedData->GetXmlParseMaster();
		if (parser == nullptr)
		{
			throw std::exception("Invalid parser.");
		}

		for (const auto& helper : parser->mHelpers)
		{
			if (helper->EndElementHandler(*sharedData, name))
			{
				break;
			}
		}

		sharedData->DecrementDepth();
	}

	void XmlParseMaster::CharDataHandler(void* userData, const char* buffer, int32_t length)
	{
		assert(userData != nullptr);

		SharedData* sharedData = reinterpret_cast<SharedData*>(userData);
		XmlParseMaster* parser = sharedData->GetXmlParseMaster();
		if (parser == nullptr)
		{
			throw std::exception("Invalid parser.");
		}

		for (const auto& helper : parser->mHelpers)
		{
			if (helper->CharDataHandler(*sharedData, buffer, length))
			{
				break;
			}
		}
	}

	void XmlParseMaster::Reset()
	{
		mSharedData->Initialize();
		for (const auto& helper : mHelpers)
		{
			helper->Initialize();
		}

		XML_ParserReset(mParser, nullptr);
		XML_SetUserData(mParser, mSharedData);
		XML_SetElementHandler(mParser, StartElementHandler, EndElementHandler);
		XML_SetCharacterDataHandler(mParser, CharDataHandler);
		mParsedFileName = "";
	}

#pragma endregion

#pragma region SharedData

	RTTI_DEFINITIONS(XmlParseMaster::SharedData)

	XmlParseMaster::SharedData::SharedData()
		: mParser(nullptr), mDepth(0)
	{
	}

	void XmlParseMaster::SharedData::Initialize()
	{
		mDepth = 0;
	}

	XmlParseMaster::SharedData* XmlParseMaster::SharedData::Clone() const
	{
		return new SharedData();
	}

	void XmlParseMaster::SharedData::SetXmlParseMaster(XmlParseMaster& parser)
	{
		mParser = &parser;
	}

	XmlParseMaster* XmlParseMaster::SharedData::GetXmlParseMaster() const
	{
		return mParser;
	}

	void XmlParseMaster::SharedData::IncrementDepth()
	{
		if (mDepth == (std::numeric_limits<std::uint32_t>::max)())
		{
			throw std::exception("Maximum depth exceeded.");
		}
		++mDepth;
	}

	void XmlParseMaster::SharedData::DecrementDepth()
	{
		if (mDepth > 0)
		{
			--mDepth;
		}
		else
		{
			throw std::exception("Attempting to decrement depth below zero. Something may be out of sync.");
		}
	}

	std::uint32_t XmlParseMaster::SharedData::Depth() const
	{
		return mDepth;
	}

#pragma endregion

}
