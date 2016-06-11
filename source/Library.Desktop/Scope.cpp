#include "pch.h"

namespace Library
{
	RTTI_DEFINITIONS(Scope)

#pragma region Scope

	Scope::Scope(const std::uint32_t initialCapacity) :
		mData(DefaultNumberOfBuckets), mOrderedData(initialCapacity), mParent(nullptr)
	{
	}

	Scope::Scope(const Scope& rhs) :
		mData(DefaultNumberOfBuckets), mOrderedData(), mParent(nullptr)
	{
		operator=(rhs);
	}

#pragma region Operator Overloads

	Scope& Scope::operator=(const Scope& rhs)
	{
		if (this != &rhs)
		{
			Clear();

			mParent = rhs.mParent;

			// Rebuild the HashMap
			for (const auto& data : rhs.mOrderedData)
			{
				// This does not preserve the old HashMap order
				auto it = mData.Insert(std::pair<std::string, Datum>(data->first, data->second));
				mOrderedData.PushBack(&*it);
			}
		}

		return *this;
	}

	bool Scope::operator==(const Scope& other) const
	{
		if (this == &other)
		{
			return true;
		}

		const std::uint32_t Size = this->Size();
		if (Size != other.Size())
		{
			return false;
		}

		for (std::uint32_t i = 0; i < Size; ++i)
		{
			if (*mOrderedData[i] != *other.mOrderedData[i])
			{
				return false;
			}
		}

		return true;
	}

	bool Scope::operator!=(const Scope& other) const
	{
		return !(operator==(other));
	}

	Datum& Scope::operator[](const std::string& name)
	{
		return Append(name);
	}

	Datum& Scope::operator[](const std::uint32_t index)
	{
		if (index >= mOrderedData.Size())
		{
			throw std::exception("Index out of bounds.");
		}

		return Append(mOrderedData[index]->first);
	}

#pragma endregion

	Scope::~Scope()
	{
		Clear();
	}

	void Scope::Clear(const bool skipOrphan)
	{
		if (!skipOrphan)
		{
			Orphan();
		}

		for (const auto& pair : mOrderedData)
		{
			Datum& datum = pair->second;
			if (datum.Type() == Datum::DatumType::Table)
			{
				for (std::uint32_t i = datum.Size(); i > 0; --i)
				{
					Scope* scope = datum.Get<Scope*>(i - 1);
					if (scope != nullptr && scope->mParent == this)
					{
						delete scope;
					}
				}
			}
		}

		mOrderedData.Clear();
		mData.Clear();
	}

	void Scope::Orphan()
	{
		if (mParent != nullptr)
		{
			Datum* foundDatum = mParent->FindContainedScope(*this);
			assert(foundDatum != nullptr);

			for (std::uint32_t i = 0; i < foundDatum->Size(); ++i)
			{
				if (foundDatum[i] == this)
				{
					foundDatum->RemoveTable(i);
					break;
				}
			}

			mParent = nullptr;
		}
	}

	Datum* Scope::Find(const std::string& name) const
	{
		if (name.empty())
		{
			return nullptr;
		}

		auto foundValue = mData.Find(name);
		if (foundValue != mData.end())
		{
			return &foundValue->second;
		}

		return nullptr;
	}

	Datum* Scope::Search(const std::string& name, Scope** scope) const
	{
		if (scope != nullptr)
		{
			*scope = const_cast<Scope*>(this);
		}

		Datum* foundDatum = Find(name);
		if ((foundDatum == nullptr) && (mParent != nullptr))
		{
			// Keep searching
			return mParent->Search(name, scope);
		}

		return foundDatum;
	}

	Datum& Scope::Append(const std::string& name)
	{
		if (name.empty())
		{
			throw std::exception("Cannot append an empty name.");
		}

		bool wasInserted = false;
		HashMap<std::string, Datum>::Iterator value = mData.Insert(TablePair(name, Datum()), wasInserted);
		if (wasInserted)
		{
			// Only add to the table if a new value was added to the HashMap
			mOrderedData.PushBack(&*value);
		}

		return value->second;
	}

	Scope& Scope::AppendScope(const std::string& name)
	{
		Datum& newDatum = Append(name);
		bool isValidType = ((newDatum.Type() == Datum::DatumType::Table) || (newDatum.Type() == Datum::DatumType::Unknown));
		if (!isValidType)
		{
			throw std::exception("Cannot append scope. The datum is not a table.");
		}

		assert(!newDatum.IsExternal());

		Scope* newScope = new Scope();
		newScope->mParent = this;
		newDatum.SetType(Datum::DatumType::Table);
		newDatum.PushBack(*newScope);

		return *newScope;
	}

	void Scope::Adopt(Scope& child, const std::string& childName)
	{
		Datum& datum = Append(childName);
		datum.SetType(Datum::DatumType::Table);
		datum.PushBack(child);
		child.Orphan();
		child.mParent = this;
	}

	Scope* Scope::GetParent() const
	{
		return mParent;
	}

	Datum* Scope::FindContainedScope(const Scope& scope) const
	{
		// Iterate over each entry in the ordered data set
		for (auto& pair : mOrderedData)
		{
			Datum& datum = pair->second;
			// Check if a scope was found
			if (datum.Type() == Datum::DatumType::Table)
			{
				// Search each scope in the datum array
				for (std::uint32_t i = 0; i < datum.Size(); ++i)
				{
					if (datum[i] == scope)
					{
						return &datum;
					}
				}
			}
		}

		// No match found
		return nullptr;
	}

	std::string Scope::FindName(const Scope& searchScope) const
	{
		if (searchScope.mParent != this)
		{
			throw std::exception("The search scope is not a child of this scope.");
		}

		for (const auto& pair : mOrderedData)
		{
			Datum* datum = Find(pair->first);
			if ((datum != nullptr) && (datum->Type() == Datum::DatumType::Table))
			{
				return pair->first;
			}
		}

		return std::string();
	}

	bool Scope::FindName(const Scope& searchScope, std::string& foundName) const
	{
		foundName = FindName(searchScope);
		return !(foundName.empty());
	}

	std::uint32_t Scope::Size() const
	{
		return mOrderedData.Size();
	}

#pragma endregion

}
