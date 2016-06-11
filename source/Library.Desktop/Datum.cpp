#include "pch.h"

namespace Library
{

#pragma region Datum

	Datum::Datum() :
		mData(), mType(DatumType::Unknown), mSize(0), mCapacity(0), mIsExternal(false)
	{
	}

	Datum::Datum(const DatumType type, const std::uint32_t capacity) :
		mData(), mType(type), mSize(0), mCapacity(capacity), mIsExternal(false)
	{
	}

	Datum::Datum(const Datum& rhs) :
		Datum()
	{
		operator=(rhs);
	}

#pragma region Assignment Operator Overloads

	Datum& Datum::operator=(const Datum& rhs)
	{
		if (this != &rhs)
		{
			Clear();

			mType = rhs.mType;
			mSize = rhs.mSize;
			mCapacity = rhs.mCapacity;
			mIsExternal = rhs.mIsExternal;

			if (mIsExternal)
			{
				// The lhs is external
				mData.i = rhs.mData.i;
			}
			else
			{
				// The lhs is internal
				switch (mType)
				{
					case DatumType::Integer:
						mData.i = new std::int32_t[rhs.mCapacity];
						for (uint32_t i = 0; i < rhs.mSize; ++i)
						{
							mData.i[i] = rhs.mData.i[i];
						}
						break;
					case DatumType::Float:
						mData.f = new float[rhs.mCapacity];
						for (uint32_t i = 0; i < rhs.mSize; ++i)
						{
							mData.f[i] = rhs.mData.f[i];
						}
						break;
					case DatumType::Vector:
						mData.v = new glm::vec4[rhs.mCapacity];
						for (uint32_t i = 0; i < rhs.mSize; ++i)
						{
							mData.v[i] = rhs.mData.v[i];
						}
						break;
					case DatumType::Matrix:
						mData.m = new glm::mat4[rhs.mCapacity];
						for (uint32_t i = 0; i < rhs.mSize; ++i)
						{
							mData.m[i] = rhs.mData.m[i];
						}
						break;
					case DatumType::Table:
						mData.t = new Scope*[rhs.mCapacity];
						for (uint32_t i = 0; i < rhs.mSize; ++i)
						{
							mData.t[i] = rhs.mData.t[i];
						}
						break;
					case DatumType::String:
						mData.s = new std::string[rhs.mCapacity];
						for (uint32_t i = 0; i < rhs.mSize; ++i)
						{
							mData.s[i] = rhs.mData.s[i];
						}
						break;
					case DatumType::Pointer:
						mData.p = new RTTI*[rhs.mCapacity];
						for (uint32_t i = 0; i < rhs.mSize; ++i)
						{
							mData.p[i] = rhs.mData.p[i];
						}
						break;
					default: 
						break;
				}
			}
		}

		return *this;
	}

	Datum& Datum::operator=(const std::int32_t rhs)
	{
		if (mType == DatumType::Unknown)
		{
			mType = DatumType::Integer;
		}
		else if (mType != DatumType::Integer)
		{
			throw std::exception("Cannot change the Datum's type. It has been previously defined.");
		}
		
		Reserve(1);
		mData.i[0] = rhs;
		mSize = 1;

		return *this;
	}

	Datum& Datum::operator=(const float rhs)
	{
		if (mType == DatumType::Unknown)
		{
			mType = DatumType::Float;
		}
		else if (mType != DatumType::Float)
		{
			throw std::exception("Cannot change the Datum's type. It has been previously defined.");
		}

		Reserve(1);
		mData.f[0] = rhs;
		mSize = 1;

		return *this;
	}

	Datum& Datum::operator=(const glm::vec4& rhs)
	{
		if (mType == DatumType::Unknown)
		{
			mType = DatumType::Vector;
		}
		else if (mType != DatumType::Vector)
		{
			throw std::exception("Cannot change the Datum's type. It has been previously defined.");
		}

		Reserve(1);
		mData.v[0] = rhs;
		mSize = 1;

		return *this;
	}

	Datum& Datum::operator=(const glm::mat4& rhs)
	{
		if (mType == DatumType::Unknown)
		{
			mType = DatumType::Matrix;
		}
		else if (mType != DatumType::Matrix)
		{
			throw std::exception("Cannot change the Datum's type. It has been previously defined.");
		}

		Reserve(1);
		mData.m[0] = rhs;
		mSize = 1;

		return *this;
	}

	Datum& Datum::operator=(const Scope* rhs)
	{
		if (mType == DatumType::Unknown)
		{
			mType = DatumType::Table;
		}
		else if (mType != DatumType::Table)
		{
			throw std::exception("Cannot change the Datum's type. It has been previously defined.");
		}

		Reserve(1);
		mData.t[0] = const_cast<Scope*>(rhs);
		mSize = 1;

		return *this;
	}

	Datum& Datum::operator=(const std::string& rhs)
	{
		if (mType == DatumType::Unknown)
		{
			mType = DatumType::String;
		}
		else if (mType != DatumType::String)
		{
			throw std::exception("Cannot change the Datum's type. It has been previously defined.");
		}

		Reserve(1);
		mData.s[0] = rhs;
		mSize = 1;

		return *this;
	}

	Datum& Datum::operator=(const RTTI* rhs)
	{
		if (mType == DatumType::Unknown)
		{
			mType = DatumType::Pointer;
		}
		else if (mType != DatumType::Pointer)
		{
			throw std::exception("Cannot change the Datum's type. It has been previously defined.");
		}

		Reserve(1);
		mData.p[0] = const_cast<RTTI*>(rhs);
		mSize = 1;

		return *this;
	}

#pragma endregion

#pragma region Comparison Operator Overloads

	bool Datum::operator==(const Datum& other) const
	{
		if (mType != other.mType || mSize != other.mSize)
		{
			return false;
		}

		switch (mType)
		{
		case DatumType::Unknown:
			return true;
		case DatumType::Integer:
			for (std::uint32_t i = 0; i < mSize; ++i)
			{
				if (mData.i[i] != other.mData.i[i])
				{
					return false;
				}
			}
			break;

		case DatumType::Float:
			for (std::uint32_t i = 0; i < mSize; ++i)
			{
				if (mData.f[i] != other.mData.f[i])
				{
					return false;
				}
			}
			break;

		case DatumType::Vector:
			for (std::uint32_t i = 0; i < mSize; ++i)
			{
				if (mData.v[i] != other.mData.v[i])
				{
					return false;
				}
			}
			break;

		case DatumType::Matrix:
			for (std::uint32_t i = 0; i < mSize; ++i)
			{
				if (mData.m[i] != other.mData.m[i])
				{
					return false;
				}
			}
			break;

		case DatumType::Table:
			for (std::uint32_t i = 0; i < mSize; ++i)
			{
				if (mData.t[i] != other.mData.t[i])
				{
					RTTI* table = mData.t[i];
					if ((table != nullptr) && (!table->Equals(other.mData.t[i])))
					{
						return false;
					}
					return false;
				}
			}
			break;

		case DatumType::String:
			for (std::uint32_t i = 0; i < mSize; ++i)
			{
				if (mData.s[i].compare(other.mData.s[i]) != 0)
				{
					return false;
				}
			}
			break;

		case DatumType::Pointer:
			for (std::uint32_t i = 0; i < mSize; ++i)
			{
				RTTI* rtti = mData.p[i];
				if ((rtti != nullptr) && (!rtti->Equals(other.mData.p[i])))
				{
					return false;
				}
			}
			break;

		default:
			return false;
		}

		return true;
	}

	bool Datum::operator==(const std::int32_t value) const
	{
		return ((mSize == 1) && (mType == DatumType::Integer) && (mData.i[0] == value));
	}

	bool Datum::operator==(const float value) const
	{
		return ((mSize == 1) && (mType == DatumType::Float) && (mData.f[0] == value));
	}

	bool Datum::operator==(const glm::vec4& value) const
	{
		return ((mSize == 1) && (mType == DatumType::Vector) && (mData.v[0] == value));
	}

	bool Datum::operator==(const glm::mat4& value) const
	{
		return ((mSize == 1) && (mType == DatumType::Matrix) && (mData.m[0] == value));
	}

	bool Datum::operator==(const Scope* value) const
	{
		return ((mSize == 1) && (mType == DatumType::Table) && (mData.t[0] == value));
	}

	bool Datum::operator==(const std::string& value) const
	{
		return ((mSize == 1) && (mType == DatumType::String) && (mData.s[0] == value));
	}

	bool Datum::operator==(const RTTI* value) const
	{
		return ((mSize == 1) && (mType == DatumType::Pointer) && (mData.p[0]->Equals(value)));
	}

	bool Datum::operator!=(const Datum& other) const
	{
		return !(operator==(other));
	}

	bool Datum::operator!=(const std::int32_t value) const
	{
		return !(operator==(value));
	}

	bool Datum::operator!=(const float value) const
	{
		return !(operator==(value));
	}

	bool Datum::operator!=(const glm::vec4& value) const
	{
		return !(operator==(value));
	}

	bool Datum::operator!=(const glm::mat4& value) const
	{
		return !(operator==(value));
	}

	bool Datum::operator!=(const Scope* value) const
	{
		return !(operator==(value));
	}

	bool Datum::operator!=(const std::string& value) const
	{
		return !(operator==(value));
	}

	bool Datum::operator!=(const RTTI* value) const
	{
		return !(operator==(value));
	}

#pragma endregion

	Scope& Datum::operator[](const std::uint32_t index)
	{
		Scope* foundScope = Get<Scope*>(index);
		if (foundScope == nullptr)
		{
			throw std::exception("Index out of bounds.");
		}
		return *Get<Scope*>(index);
	}

	Datum::~Datum()
	{
		Clear();
	}

	void Datum::RemoveTable(const std::uint32_t index)
	{
		if (index >= mSize)
		{
			throw std::exception("Index out of bounds.");
		}

		if (mType != DatumType::Table)
		{
			throw std::exception("Can only remove tables.");
		}

		mData.t[index] = nullptr;
		for (std::uint32_t i = index; i < mSize - 1; ++i)
		{
			mData.t[i] = mData.t[i + 1];
		}
		--mSize;
	}

	void Datum::Reserve(const std::uint32_t capacity)
	{
		if (capacity > mCapacity)
		{
			DatumValues newDatum;

			switch (mType)
			{
			case DatumType::Integer:
				newDatum.i = new std::int32_t[capacity];
				if (mCapacity > 0)
				{
					for (std::uint32_t i = 0; i < mCapacity; ++i)
					{
						// Copy the old values into the new container
						newDatum.i[i] = mData.i[i];
					}
					delete[] mData.i;
				}
				mData.i = newDatum.i;
				break;
			case DatumType::Float:
				newDatum.f = new float[capacity];
				if (mCapacity > 0)
				{
					for (std::uint32_t i = 0; i < mCapacity; ++i)
					{
						// Copy the old values into the new container
						newDatum.f[i] = mData.f[i];
					}
					delete[] mData.f;
				}
				mData.f = newDatum.f;
				break;
			case DatumType::Vector:
				newDatum.v = new glm::vec4[capacity];
				if (mCapacity > 0)
				{
					for (std::uint32_t i = 0; i < mCapacity; ++i)
					{
						// Copy the old values into the new container
						newDatum.v[i] = mData.v[i];
					}
					delete[] mData.v;
				}
				mData.v = newDatum.v;
				break;
			case DatumType::Matrix:
				newDatum.m = new glm::mat4[capacity];
				if (mCapacity > 0)
				{
					for (std::uint32_t i = 0; i < mCapacity; ++i)
					{
						// Copy the old values into the new container
						newDatum.m[i] = mData.m[i];
					}
					delete[] mData.m;
				}
				mData.m = newDatum.m;
				break;
			case DatumType::Table:
				newDatum.t = new Scope*[capacity];
				if (mCapacity > 0)
				{
					for (std::uint32_t i = 0; i < mCapacity; ++i)
					{
						// Copy the old values into the new container
						newDatum.t[i] = mData.t[i];
					}
					delete[] mData.t;
				}
				mData.t = newDatum.t;
				break;
			case DatumType::String:
				newDatum.s = new std::string[capacity];
				if (mCapacity > 0)
				{
					for (std::uint32_t i = 0; i < mCapacity; ++i)
					{
						// Copy the old values into the new container
						newDatum.s[i] = mData.s[i];
					}
					delete[] mData.s;
				}
				mData.s = newDatum.s;
				break;
			case DatumType::Pointer:
				newDatum.p = new RTTI*[capacity];
				if (mCapacity > 0)
				{
					for (std::uint32_t i = 0; i < mCapacity; ++i)
					{
						// Copy the old values into the new container
						newDatum.p[i] = mData.p[i];
					}
					delete[] mData.p;
				}
				mData.p = newDatum.p;
				break;
			default:
				throw std::exception("Cannot Reserve an unknown Datum type.");
			}

			mCapacity = capacity;
		}
	}

#pragma region PushBack()

	void Datum::PushBack(const std::int32_t value)
	{
		if (++mSize > mCapacity)
		{
			// Capacity exceeded, we must allocate more memory
			Reserve(mSize);
		}

		mData.i[mSize - 1] = value;
	}

	void Datum::PushBack(const float value)
	{
		if (++mSize > mCapacity)
		{
			// Capacity exceeded, we must allocate more memory
			Reserve(mSize);
		}

		mData.f[mSize - 1] = value;
	}

	void Datum::PushBack(const glm::vec4& value)
	{
		if (++mSize > mCapacity)
		{
			// Capacity exceeded, we must allocate more memory
			Reserve(mSize);
		}

		mData.v[mSize - 1] = value;
	}

	void Datum::PushBack(const glm::mat4& value)
	{
		if (++mSize > mCapacity)
		{
			// Capacity exceeded, we must allocate more memory
			Reserve(mSize);
		}

		mData.m[mSize - 1] = value;
	}

	void Datum::PushBack(Scope& value)
	{
		if (++mSize > mCapacity)
		{
			// Capacity exceeded, we must allocate more memory
			Reserve(mSize);
		}

		mData.t[mSize - 1] = &value;
	}

	void Datum::PushBack(const std::string& value)
	{
		if (++mSize > mCapacity)
		{
			// Capacity exceeded, we must allocate more memory
			Reserve(mSize);
		}

		mData.s[mSize - 1] = value;
	}

	void Datum::PushBack(RTTI& value)
	{
		if (++mSize > mCapacity)
		{
			// Capacity exceeded, we must allocate more memory
			Reserve(mSize);
		}

		mData.p[mSize - 1] = &value;
	}

#pragma endregion

	Datum::DatumType Datum::Type() const
	{
		return mType;
	}

	void Datum::SetType(const DatumType& type)
	{
		if (type != mType)
		{
			if (mType != DatumType::Unknown)
			{
				throw std::exception("Cannot change the type of an already defined Datum.");
			}
			mType = type;
		}
	}

	std::uint32_t Datum::Capacity() const
	{
		return mCapacity;
	}

	std::uint32_t Datum::Size() const
	{
		return mSize;
	}

	void Datum::Clear()
	{
		if (!mIsExternal)
		{
			switch (mType)
			{
				case DatumType::Integer:
					delete[] mData.i;
					break;
				case DatumType::Float:
					delete[] mData.f;
					break;
				case DatumType::Vector:
					delete[] mData.v;
					break;
				case DatumType::Matrix:
					delete[] mData.m;
					break;
				case DatumType::Table:
					delete[] mData.t;
					break;
				case DatumType::String:
					delete[] mData.s;
					break;
				case DatumType::Pointer:
					delete[] mData.p;
					break;
			}
		}
		else
		{
			mData.i = nullptr;
			mIsExternal = false;
		}

		mCapacity = 0;
		mSize = 0;
		mType = DatumType::Unknown;
	}

#pragma region SetStorage()

	void Datum::SetStorage(std::int32_t* values, const std::uint32_t size)
	{
		if (mType != DatumType::Unknown && !mIsExternal)
		{
			throw std::exception("Cannot set storage for a Datum with allocated data.");
		}

		if (mType != DatumType::Integer && mIsExternal)
		{
			// Note: The Datum should never be in the situation where it is marked as external and unknown
			throw std::exception("Cannot change the Datum's type. It has been previously defined.");
		}

		mIsExternal = true;
		mData.i = values;
		mType = DatumType::Integer;
		mSize = size;
		mCapacity = mSize;
	}

	void Datum::SetStorage(float* values, const std::uint32_t size)
	{
		if (mType != DatumType::Unknown && !mIsExternal)
		{
			throw std::exception("Cannot set storage for a Datum with allocated data.");
		}

		if (mType != DatumType::Float && mIsExternal)
		{
			// Note: The Datum should never be in the situation where it is marked as external and unknown
			throw std::exception("Cannot change the Datum's type. It has been previously defined.");
		}

		mIsExternal = true;
		mData.f = values;
		mType = DatumType::Float;
		mSize = size;
		mCapacity = mSize;
	}

	void Datum::SetStorage(glm::vec4* values, const std::uint32_t size)
	{
		if (mType != DatumType::Unknown && !mIsExternal)
		{
			throw std::exception("Cannot set storage for a Datum with allocated data.");
		}

		if (mType != DatumType::Vector && mIsExternal)
		{
			// Note: The Datum should never be in the situation where it is marked as external and unknown
			throw std::exception("Cannot change the Datum's type. It has been previously defined.");
		}

		mIsExternal = true;
		mData.v = values;
		mType = DatumType::Vector;
		mSize = size;
		mCapacity = mSize;
	}

	void Datum::SetStorage(glm::mat4* values, const std::uint32_t size)
	{
		if (mType != DatumType::Unknown && !mIsExternal)
		{
			throw std::exception("Cannot set storage for a Datum with allocated data.");
		}

		if (mType != DatumType::Matrix && mIsExternal)
		{
			// Note: The Datum should never be in the situation where it is marked as external and unknown
			throw std::exception("Cannot change the Datum's type. It has been previously defined.");
		}

		mIsExternal = true;
		mData.m = values;
		mType = DatumType::Matrix;
		mSize = size;
		mCapacity = mSize;
	}

	void Datum::SetStorage(std::string* values, const std::uint32_t size)
	{
		if (mType != DatumType::Unknown && !mIsExternal)
		{
			throw std::exception("Cannot set storage for a Datum with allocated data.");
		}

		if (mType != DatumType::String && mIsExternal)
		{
			// Note: The Datum should never be in the situation where it is marked as external and unknown
			throw std::exception("Cannot change the Datum's type. It has been previously defined.");
		}

		mIsExternal = true;
		mData.s = values;
		mType = DatumType::String;
		mSize = size;
		mCapacity = mSize;
	}

	void Datum::SetStorage(RTTI** values, const std::uint32_t size)
	{
		if (mType != DatumType::Unknown && !mIsExternal)
		{
			throw std::exception("Cannot set storage for a Datum with allocated data.");
		}

		if (mType != DatumType::Pointer && mIsExternal)
		{
			// Note: The Datum should never be in the situation where it is marked as external and unknown
			throw std::exception("Cannot change the Datum's type. It has been previously defined.");
		}

		mIsExternal = true;
		mData.p = values;
		mType = DatumType::Pointer;
		mSize = size;
		mCapacity = mSize;
	}

#pragma endregion

#pragma region Set()
	
	void Datum::Set(const std::int32_t value, const std::uint32_t index)
	{
		if (mType == DatumType::Unknown)
		{
			// Set the type if it was not previously set
			mType = DatumType::Integer;
		}
		else if (mType != DatumType::Integer)
		{
			// The type was already set (and it doesn't match the value passed in)
			throw std::exception("Cannot change the Datum's type to an integer.");
		}

		if (index >= mSize)
		{
			if (mIsExternal)
			{
				throw std::exception("Index out of bounds. External Datums cannot be resized.");
			}

			// The user requested an index larger than the size. Instead of allocating too much
			// additional memory (and leaving uninitialized data in the structure) we will
			// simply call push back and add the element to the end of the array instead.
			PushBack(value);
		}
		else
		{
			Reserve(1);
			mData.i[index] = value;
		}
	}

	void Datum::Set(const float value, const std::uint32_t index)
	{
		if (mType == DatumType::Unknown)
		{
			// Set the type if it was not previously set
			mType = DatumType::Float;
		}
		else if (mType != DatumType::Float)
		{
			// The type was already set (and it doesn't match the value passed in)
			throw std::exception("Cannot change the Datum's type to a float.");
		}

		if (index >= mSize)
		{
			if (mIsExternal)
			{
				throw std::exception("Index out of bounds. External Datums cannot be resized.");
			}

			// The user requested an index larger than the size. Instead of allocating too much
			// additional memory (and leaving uninitialized data in the structure) we will
			// simply call push back and add the element to the end of the array instead.
			PushBack(value);
		}
		else
		{
			Reserve(1);
			mData.f[index] = value;
		}
	}

	void Datum::Set(const glm::vec4& value, const std::uint32_t index)
	{
		if (mType == DatumType::Unknown)
		{
			// Set the type if it was not previously set
			mType = DatumType::Vector;
		}
		else if (mType != DatumType::Vector)
		{
			// The type was already set (and it doesn't match the value passed in)
			throw std::exception("Cannot change the Datum's type to a 4-dimensional vector.");
		}

		if (index >= mSize)
		{
			if (mIsExternal)
			{
				throw std::exception("Index out of bounds. External Datums cannot be resized.");
			}

			// The user requested an index larger than the size. Instead of allocating too much
			// additional memory (and leaving uninitialized data in the structure) we will
			// simply call push back and add the element to the end of the array instead.
			PushBack(value);
		}
		else
		{
			Reserve(1);
			mData.v[index] = value;
		}
	}

	void Datum::Set(const glm::mat4& value, const std::uint32_t index)
	{
		if (mType == DatumType::Unknown)
		{
			// Set the type if it was not previously set
			mType = DatumType::Matrix;
		}
		else if (mType != DatumType::Matrix)
		{
			// The type was already set (and it doesn't match the value passed in)
			throw std::exception("Cannot change the Datum's type to a 4x4 matrix.");
		}

		if (index >= mSize)
		{
			if (mIsExternal)
			{
				throw std::exception("Index out of bounds. External Datums cannot be resized.");
			}

			// The user requested an index larger than the size. Instead of allocating too much
			// additional memory (and leaving uninitialized data in the structure) we will
			// simply call push back and add the element to the end of the array instead.
			PushBack(value);
		}
		else
		{
			Reserve(1);
			mData.m[index] = value;
		}
	}

	void Datum::Set(Scope& value, const std::uint32_t index)
	{
		if (mType == DatumType::Unknown)
		{
			// Set the type if it was not previously set
			mType = DatumType::Table;
		}
		else if (mType != DatumType::Table)
		{
			// The type was already set (and it doesn't match the value passed in)
			throw std::exception("Cannot change the Datum's type to a table.");
		}

		if (index >= mSize)
		{
			if (mIsExternal)
			{
				throw std::exception("Index out of bounds. External Datums cannot be resized.");
			}

			// The user requested an index larger than the size. Instead of allocating too much
			// additional memory (and leaving uninitialized data in the structure) we will
			// simply call push back and add the element to the end of the array instead.
			PushBack(value);
		}
		else
		{
			Reserve(1);
			mData.t[index] = &value;
		}
	}

	void Datum::Set(const std::string& value, const std::uint32_t index)
	{
		if (mType == DatumType::Unknown)
		{
			// Set the type if it was not previously set
			mType = DatumType::String;
		}
		else if (mType != DatumType::String)
		{
			// The type was already set (and it doesn't match the value passed in)
			throw std::exception("Cannot change the Datum's type to a string.");
		}

		if (index >= mSize)
		{
			if (mIsExternal)
			{
				throw std::exception("Index out of bounds. External Datums cannot be resized.");
			}

			// The user requested an index larger than the size. Instead of allocating too much
			// additional memory (and leaving uninitialized data in the structure) we will
			// simply call push back and add the element to the end of the array instead.
			PushBack(value);
		}
		else
		{
			Reserve(1);
			mData.s[index] = value;
		}
	}

	void Datum::Set(RTTI& value, const std::uint32_t index)
	{
		if (mType == DatumType::Unknown)
		{
			// Set the type if it was not previously set
			mType = DatumType::Pointer;
		}
		else if (mType != DatumType::Pointer)
		{
			// The type was already set (and it doesn't match the value passed in)
			throw std::exception("Cannot change the Datum's type to a pointer.");
		}

		if (index >= mSize)
		{
			if (mIsExternal)
			{
				throw std::exception("Index out of bounds. External Datums cannot be resized.");
			}

			// The user requested an index larger than the size. Instead of allocating too much
			// additional memory (and leaving uninitialized data in the structure) we will
			// simply call push back and add the element to the end of the array instead.
			PushBack(value);
		}
		else
		{
			Reserve(1);
			mData.p[index] = &value;
		}
	}

#pragma endregion

	void Datum::SetFromString(const std::string& str, const std::uint32_t index)
	{
		switch (mType)
		{
			case DatumType::Unknown:
			{
				throw std::exception("Cannot set values of an unknown datum type.");
				break;
			}
			case DatumType::Integer:
			{
				const std::uint32_t expectedArgCount = 1;
				std::int32_t value = 0;
				if (sscanf_s(str.c_str(), "%d", &value) != expectedArgCount)
				{
					throw std::exception("Failed to convert string to integer.");
				}
				Set(value, index);
				break;
			}
			case DatumType::Float:
			{
				const std::uint32_t expectedArgCount = 1;
				float value = 0.0f;
				if (sscanf_s(str.c_str(), "%f", &value) != expectedArgCount)
				{
					throw std::exception("Failed to convert string to float.");
				}
				Set(value, index);
				break;
			}
			case DatumType::Vector:
			{
				const std::uint32_t expectedArgCount = 4;
				glm::vec4 value;
				if (sscanf_s(str.c_str(), "(%f %f %f %f)",
					&value.x, &value.y, &value.z, &value.w) != expectedArgCount)
				{
					throw std::exception("Failed to convert string to 4-dimensional vector.");
				}
				Set(value, index);
				break;
			}
			case DatumType::Matrix:
			{
				const std::uint32_t expectedArgCount = 16;
				glm::mat4 value;
				if (sscanf_s(str.c_str(), "[(%f %f %f %f),(%f %f %f %f),(%f %f %f %f),(%f %f %f %f)]",
					&value[0].x, &value[0].y, &value[0].z, &value[0].w,
					&value[1].x, &value[1].y, &value[1].z, &value[1].w,
					&value[2].x, &value[2].y, &value[2].z, &value[2].w,
					&value[3].x, &value[3].y, &value[3].z, &value[3].w) != expectedArgCount)
				{
					throw std::exception("Failed to convert string to 4x4 matrix.");
				}
				Set(value, index);
				break;
			}
			case DatumType::String:
			{
				Set(str, index);
				break;
			}
			default:
			{
				throw std::exception("Cannot set an unknown type.");
			}
		}
	}

	std::string Datum::ToString(const std::uint32_t index) const
	{
		char buffer[256] = "\0";

		switch (mType)
		{
			case DatumType::Integer:
			{
				sprintf_s(buffer, sizeof(buffer), "%d", Get<std::int32_t>(index));
				break;
			}
			case DatumType::Float:
			{
				sprintf_s(buffer, sizeof(buffer), "%f", Get<float>(index));
				break;
			}
			case DatumType::Vector:
			{
				glm::vec4 vector = Get<glm::vec4>(index);
				sprintf_s(buffer, sizeof(buffer), "(%f %f %f %f)", vector.x, vector.y, vector.z, vector.w);
				break;
			}
			case DatumType::Matrix:
			{
				glm::mat4 matrix = Get<glm::mat4>(index);
				sprintf_s(buffer, sizeof(buffer), "[(%f %f %f %f),(%f %f %f %f),(%f %f %f %f),(%f %f %f %f)]",
					matrix[0].x, matrix[0].y, matrix[0].z, matrix[0].w,
					matrix[1].x, matrix[1].y, matrix[1].z, matrix[1].w,
					matrix[2].x, matrix[2].y, matrix[2].z, matrix[2].w,
					matrix[3].x, matrix[3].y, matrix[3].z, matrix[3].w);
				break;
			}
			case DatumType::String:
			{
				sprintf_s(buffer, sizeof(buffer), "%s", Get<std::string>(index).c_str());
				break;
			}
			default:
			{
				throw std::exception("Invalid type. Unable to convert to a string.");
			}
		}

		return buffer;
	}

	bool Datum::IsExternal() const
	{
		return mIsExternal;
	}

#pragma region Get()

	template<>
	const std::int32_t& Datum::Get<std::int32_t>(const std::uint32_t index) const
	{
		if (index >= mSize)
		{
			throw std::exception("Index out of bounds.");
		}

		if (mType != DatumType::Integer)
		{
			throw std::exception("The Datum's type does not match the return type.");
		}

		return mData.i[index];
	}

	template<>
	const float& Datum::Get<float>(const std::uint32_t index) const
	{
		if (index >= mSize)
		{
			throw std::exception("Index out of bounds.");
		}

		if (mType != DatumType::Float)
		{
			throw std::exception("The Datum's type does not match the return type.");
		}

		return mData.f[index];
	}

	template<>
	const glm::vec4& Datum::Get<glm::vec4>(const std::uint32_t index) const
	{
		if (index >= mSize)
		{
			throw std::exception("Index out of bounds.");
		}

		if (mType != DatumType::Vector)
		{
			throw std::exception("The Datum's type does not match the return type.");
		}

		return mData.v[index];
	}

	template<>
	const glm::mat4& Datum::Get<glm::mat4>(const std::uint32_t index) const
	{
		if (index >= mSize)
		{
			throw std::exception("Index out of bounds.");
		}

		if (mType != DatumType::Matrix)
		{
			throw std::exception("The Datum's type does not match the return type.");
		}

		return mData.m[index];
	}

	template<>
	Scope* const & Datum::Get<Scope*>(const std::uint32_t index) const
	{
		if (index >= mSize)
		{
			throw std::exception("Index out of bounds.");
		}

		if (mType != DatumType::Table)
		{
			throw std::exception("The Datum's type does not match the return type.");
		}

		return mData.t[index];
	}

	template<>
	const std::string& Datum::Get<std::string>(const std::uint32_t index) const
	{
		if (index >= mSize)
		{
			throw std::exception("Index out of bounds.");
		}

		if (mType != DatumType::String)
		{
			throw std::exception("The Datum's type does not match the return type.");
		}

		return mData.s[index];
	}

	template<>
	RTTI* const & Datum::Get<RTTI*>(const std::uint32_t index) const
	{
		if (index >= mSize)
		{
			throw std::exception("Index out of bounds.");
		}

		if (mType != DatumType::Pointer)
		{
			throw std::exception("The Datum's type does not match the return type.");
		}

		return mData.p[index];
	}

#pragma endregion

#pragma endregion

}
