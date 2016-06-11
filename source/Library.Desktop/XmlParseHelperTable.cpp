#include "pch.h"

namespace Library
{

#pragma region XmlParseHelperTable

	XmlParseHelperTable::XmlParseHelperTable(const bool isClone)
		: mIsClone(isClone)
	{
	}

	bool XmlParseHelperTable::StartElementHandler(const XmlParseMaster::SharedData& sharedData, const std::string& name, 
		const HashMap<std::string, std::string>& attributes)
	{
		// TODO: How to handle different SharedData types
		// Currently having an issue when mixing parse helpers (ie: XmlParseHelperTable and XmlParseHelperEntity)
		// see XmlParseHelperEntityTestParse unit test for more info
		// the sharedData is being passed to the XmlParseMaster as an entity shared data object which may be causing 
		// the As<SharedData> call in this class to return nullptr.
		// The current workaround is to static cast the data and that appears to have solved the issue (ie: entity1's health value was verified to be 10)
		// Why does this work? Why doesn't the As call work? Should this be changed in every parse helper? This doesn't seem safe.
		//SharedData* customSharedData = sharedData.As<SharedData>();
		SharedData* customSharedData = static_cast<SharedData*>(&const_cast<XmlParseMaster::SharedData&>(sharedData));

		if (customSharedData != nullptr)
		{	
			HashMap<std::string, std::string>::Iterator nameAttribute = attributes.Find("name");
			std::string datumName = nameAttribute->second;

			// Verify the name attribute exists and is valid
			if (nameAttribute != attributes.end() && !datumName.empty())
			{
				if (name == "scope")
				{
					// Get the name of the new Scope to create
					std::string scopeName = attributes.Find("name")->second;

					if (customSharedData->mScope != nullptr)
					{
						customSharedData->mScope = &customSharedData->mScope->AppendScope(scopeName);
					}

					return true;
				}
				else
				{
					HashMap<std::string, std::string>::Iterator valueAttribute = attributes.Find("value");
					std::string datumValueAsString = valueAttribute->second;

					// Check if we have another type of datum
					if (valueAttribute != attributes.end() && !datumValueAsString.empty())
					{
						if (name == "int")
						{
							Datum* newIntDatum = &customSharedData->mScope->Append(datumName);
							Datum::DatumType datumType = newIntDatum->Type();
							if (datumType == Datum::DatumType::Unknown)
							{
								newIntDatum->SetType(Datum::DatumType::Integer);
							}
							else if (datumType != Datum::DatumType::Integer)
							{
								throw std::exception("Cannot change a pre-existing Datum to a new type. Expected DatumType::Integer");
							}

							// Set the datum value
							std::int32_t datumValue = 0;
							sscanf_s(datumValueAsString.c_str(), "%d", &datumValue);
							newIntDatum->PushBack(datumValue);

							return true;
						}
						else if (name == "float")
						{
							Datum* newFloatDatum = &customSharedData->mScope->Append(datumName);
							Datum::DatumType datumType = newFloatDatum->Type();
							if (datumType == Datum::DatumType::Unknown)
							{
								newFloatDatum->SetType(Datum::DatumType::Float);
							}
							else if (datumType != Datum::DatumType::Float)
							{
								throw std::exception("Cannot change a pre-existing Datum to a new type. Expected DatumType::Float");
							}

							// Set the datum value
							float datumValue = 0.0f;
							sscanf_s(datumValueAsString.c_str(), "%f", &datumValue);
							newFloatDatum->PushBack(datumValue);

							return true;
						}
						else if (name == "vector")
						{
							Datum* newVectorDatum = &customSharedData->mScope->Append(datumName);
							Datum::DatumType datumType = newVectorDatum->Type();
							if (datumType == Datum::DatumType::Unknown)
							{
								newVectorDatum->SetType(Datum::DatumType::Vector);
							}
							else if (datumType != Datum::DatumType::Vector)
							{
								throw std::exception("Cannot change a pre-existing Datum to a new type. Expected DatumType::Vector");
							}

							// Set the datum value
							glm::vec4 datumValue;
							sscanf_s(datumValueAsString.c_str(), "(%f,%f,%f,%f)", &datumValue.x, &datumValue.y, &datumValue.z, &datumValue.w);
							newVectorDatum->PushBack(datumValue);

							return true;
						}
						else if (name == "matrix")
						{
							Datum* newMatrixDatum = &customSharedData->mScope->Append(datumName);
							Datum::DatumType datumType = newMatrixDatum->Type();
							if (datumType == Datum::DatumType::Unknown)
							{
								newMatrixDatum->SetType(Datum::DatumType::Matrix);
							}
							else if (datumType != Datum::DatumType::Matrix)
							{
								throw std::exception("Cannot change a pre-existing Datum to a new type. Expected DatumType::Matrix");
							}

							// Set the datum value
							glm::mat4 datumValue;
							sscanf_s(datumValueAsString.c_str(), "[(%f,%f,%f,%f),(%f,%f,%f,%f),(%f,%f,%f,%f),(%f,%f,%f,%f)]",
								&datumValue[0].x, &datumValue[0].y, &datumValue[0].z, &datumValue[0].w,
								&datumValue[1].x, &datumValue[1].y, &datumValue[1].z, &datumValue[1].w,
								&datumValue[2].x, &datumValue[2].y, &datumValue[2].z, &datumValue[2].w,
								&datumValue[3].x, &datumValue[3].y, &datumValue[3].z, &datumValue[3].w);
							newMatrixDatum->PushBack(datumValue);

							return true;
						}
						else if (name == "string")
						{
							Datum* newStringDatum = &customSharedData->mScope->Append(datumName);
							Datum::DatumType datumType = newStringDatum->Type();
							if (datumType == Datum::DatumType::Unknown)
							{
								newStringDatum->SetType(Datum::DatumType::String);
							}
							else if (datumType != Datum::DatumType::String)
							{
								throw std::exception("Cannot change a pre-existing Datum to a new type. Expected DatumType::String");
							}

							// Set the datum value
							newStringDatum->PushBack(datumValueAsString);

							return true;
						}
					}
				}
			}
		}

		return false;
	}

	bool XmlParseHelperTable::EndElementHandler(const XmlParseMaster::SharedData& sharedData, const std::string& name)
	{
		SharedData* customSharedData = sharedData.As<SharedData>();

		if (customSharedData != nullptr)
		{
			if (name == "scope")
			{
				// End a scope element
				customSharedData->mScope = customSharedData->mScope->GetParent();
				return true;
			}
			else if (name == "int" || name == "float" || name == "vector" || name == "matrix" || name == "string")
			{
				// End a non-scope datum element
				return true;
			}
		}

		return false;
	}

	XmlParseHelperTable* XmlParseHelperTable::Clone()
	{
		return new XmlParseHelperTable(true);
	}

	bool XmlParseHelperTable::IsClone() const
	{
		return mIsClone;
	}

#pragma endregion

#pragma region SharedData

	RTTI_DEFINITIONS(XmlParseHelperTable::SharedData)

	XmlParseHelperTable::SharedData::SharedData(Scope& globalScope, const bool isClone)
		: mScope(&globalScope), mIsClone(isClone)
	{
	}

	XmlParseHelperTable::SharedData* XmlParseHelperTable::SharedData::Clone() const
	{
		assert(mScope != nullptr);
		return new SharedData(*mScope, true);
	}

	bool XmlParseHelperTable::SharedData::IsClone() const
	{
		return mIsClone;
	}

#pragma endregion

}