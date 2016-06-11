#include "pch.h"
#include "Attributed.h"

namespace Library
{
	RTTI_DEFINITIONS(Attributed)

#pragma region Signature

	Attributed::Signature::Signature()
		: mName(), mType(Datum::DatumType::Unknown), mInitialValue(nullptr), mSize(0), mStorage(nullptr)
	{
	}

#pragma region Signature constructors for internal data
	Attributed::Signature::Signature(const std::string& name, std::int32_t* initialValue, const std::uint32_t size)
		: mName(name), mType(Datum::DatumType::Integer), mInitialValue(new StorageType(initialValue)), mSize(size), mStorage(nullptr)
	{
	}

	Attributed::Signature::Signature(const std::string& name, float* initialValue, const std::uint32_t size)
		: mName(name), mType(Datum::DatumType::Float), mInitialValue(new StorageType(initialValue)), mSize(size), mStorage(nullptr)
	{
	}

	Attributed::Signature::Signature(const std::string& name, glm::vec4* initialValue, const std::uint32_t size)
		: mName(name), mType(Datum::DatumType::Vector), mInitialValue(new StorageType(initialValue)), mSize(size), mStorage(nullptr)
	{
	}

	Attributed::Signature::Signature(const std::string& name, glm::mat4* initialValue, const std::uint32_t size)
		: mName(name), mType(Datum::DatumType::Matrix), mInitialValue(new StorageType(initialValue)), mSize(size), mStorage(nullptr)
	{
	}

	Attributed::Signature::Signature(const std::string& name, Scope** initialValue, const std::uint32_t size)
		: mName(name), mType(Datum::DatumType::Table), mInitialValue(new StorageType(initialValue)), mSize(size), mStorage(nullptr)
	{
	}

	Attributed::Signature::Signature(const std::string& name, std::string* initialValue, const std::uint32_t size)
		: mName(name), mType(Datum::DatumType::String), mInitialValue(new StorageType(initialValue)), mSize(size), mStorage(nullptr)
	{
	}

	Attributed::Signature::Signature(const std::string& name, RTTI** initialValue, const std::uint32_t size)
		: mName(name), mType(Datum::DatumType::Pointer), mInitialValue(new StorageType(initialValue)), mSize(size), mStorage(nullptr)
	{
	}
#pragma endregion

#pragma region Signature constructors for external data
	Attributed::Signature::Signature(const std::string& name, const std::uint32_t size, std::int32_t* storage)
		: mName(name), mType(Datum::DatumType::Integer), mStorage(new StorageType(storage)), mSize(size), mInitialValue(nullptr)
	{
	}

	Attributed::Signature::Signature(const std::string& name, const std::uint32_t size, float* storage)
		: mName(name), mType(Datum::DatumType::Float), mStorage(new StorageType(storage)), mSize(size), mInitialValue(nullptr)
	{
	}

	Attributed::Signature::Signature(const std::string& name, const std::uint32_t size, glm::vec4* storage)
		: mName(name), mType(Datum::DatumType::Vector), mStorage(new StorageType(storage)), mSize(size), mInitialValue(nullptr)
	{
	}

	Attributed::Signature::Signature(const std::string& name, const std::uint32_t size, glm::mat4* storage)
		: mName(name), mType(Datum::DatumType::Matrix), mStorage(new StorageType(storage)), mSize(size), mInitialValue(nullptr)
	{
	}

	Attributed::Signature::Signature(const std::string& name, const std::uint32_t size, std::string* storage)
		: mName(name), mType(Datum::DatumType::String), mStorage(new StorageType(storage)), mSize(size), mInitialValue(nullptr)
	{
	}

	Attributed::Signature::Signature(const std::string& name, const std::uint32_t size, RTTI** storage)
		: mName(name), mType(Datum::DatumType::Pointer), mStorage(new StorageType(storage)), mSize(size), mInitialValue(nullptr)
	{
	}
#pragma endregion

	// Copy constructor
	Attributed::Signature::Signature(const Signature& rhs)
		: mName(rhs.mName), mInitialValue(rhs.mInitialValue), mSize(rhs.mSize), mStorage(rhs.mStorage)
	{
	}

	Attributed::Signature& Attributed::Signature::operator=(const Signature& rhs)
	{
		if (this != &rhs)
		{
			this->~Signature();

			mName = rhs.mName;
			mInitialValue = rhs.mInitialValue;
			mSize = rhs.mSize;
			mStorage = rhs.mStorage;
		}

		return *this;
	}

	Attributed::Signature::~Signature()
	{
		/*delete mInitialValue;
		mInitialValue = nullptr;

		delete mStorage;
		mStorage = nullptr;*/
	}

#pragma endregion

#pragma region Attributed

	Attributed::Attributed()
		: mSignatures(), Scope()
	{
	}

	Attributed::Attributed(const Attributed& rhs)
		: mSignatures(rhs.mSignatures), Scope(rhs)
	{
	}

	Attributed& Attributed::operator=(const Attributed& rhs)
	{
		if (this != &rhs)
		{
			Scope::operator=(rhs);
			mSignatures = rhs.mSignatures;
		}

		return *this;
	}

	Attributed::~Attributed()
	{
		/*for (std::uint32_t i = 0; i < mSignatures.Size(); ++i)
		{
			
			switch (mSignatures[i].mType)
			{
			case Datum::DatumType::Integer:
				delete mSignatures[i].mInitialValue->i;
				break;
			case Datum::DatumType::Float:
				delete mSignatures[i].mInitialValue->f;
				break;
			case Datum::DatumType::Vector:
				delete mSignatures[i].mInitialValue->v;
				break;
			case Datum::DatumType::Matrix:
				delete mSignatures[i].mInitialValue->m;
				break;
			case Datum::DatumType::Table:
				delete mSignatures[i].mInitialValue->t;
				break;
			case Datum::DatumType::String:
				delete mSignatures[i].mInitialValue->s;
				break;
			case Datum::DatumType::Pointer:
				delete mSignatures[i].mInitialValue->p;
				break;
			default:
				break;
			}
		}*/
		//mSignatures.Clear(); // TODO: this seems unnecessary, wouldnt the dtor for vector call this?
	}

	void Attributed::Populate()
	{
		Append("this").Set(*static_cast<RTTI*>(this));

		for (std::uint32_t i = 0; i < mSignatures.Size(); ++i)
		{
			Datum& datum = Append(mSignatures[i].mName);
			switch (mSignatures[i].mType)
			{
				case Datum::DatumType::Integer:
					for (std::uint32_t index = 0; index < mSignatures[i].mSize; ++index)
					{
						if (mSignatures[i].mStorage == nullptr)
						{
							Signature::StorageType* initialValue = mSignatures[i].mInitialValue;

							// Internal storage
							if (initialValue == nullptr)
							{
								// Defualt value if none provided
								datum.Set(0, index);
							}
							else
							{
								// Default value if provided
								datum.Set(*(initialValue->i), index);
							}
						}
						else
						{
							// External storage
							datum.SetStorage(mSignatures[i].mStorage->i, mSignatures[i].mSize);
						}
					}
					break;
				case Datum::DatumType::Float:
					for (std::uint32_t index = 0; index < mSignatures[i].mSize; ++index)
					{
						if (mSignatures[i].mStorage == nullptr)
						{
							Signature::StorageType* initialValue = mSignatures[i].mInitialValue;

							// Internal storage
							if (initialValue == nullptr)
							{
								// Defualt value if none provided
								datum.Set(0.0f, index);
							}
							else
							{
								// Default value if provided
								datum.Set(*(initialValue->f), index);
							}
						}
						else
						{
							datum.SetStorage(mSignatures[i].mStorage->f, mSignatures[i].mSize);
						}
					}
					break;
				case Datum::DatumType::Vector:
					for (std::uint32_t index = 0; index < mSignatures[i].mSize; ++index)
					{
						if (mSignatures[i].mStorage == nullptr)
						{
							Signature::StorageType* initialValue = mSignatures[i].mInitialValue;

							// Internal storage
							if (initialValue == nullptr)
							{
								// Defualt value if none provided
								datum.Set(glm::vec4(0.0f), index);
							}
							else
							{
								// Default value if provided
								datum.Set(*(initialValue->v), index);
							}
						}
						else
						{
							datum.SetStorage(mSignatures[i].mStorage->v, mSignatures[i].mSize);
						}
					}
					break;
				case Datum::DatumType::Matrix:
					for (std::uint32_t index = 0; index < mSignatures[i].mSize; ++index)
					{
						if (mSignatures[i].mStorage == nullptr)
						{
							Signature::StorageType* initialValue = mSignatures[i].mInitialValue;

							// Internal storage
							if (initialValue == nullptr)
							{
								// Defualt value if none provided
								datum.Set(glm::mat4(0.0f), index);
							}
							else
							{
								// Default value if provided
								datum.Set(*(initialValue->m), index);
							}
						}
						else
						{
							datum.SetStorage(mSignatures[i].mStorage->m, mSignatures[i].mSize);
						}
					}
					break;
				case Datum::DatumType::Table:
					for (std::uint32_t index = 0; index < mSignatures[i].mSize; ++index)
					{
						if (mSignatures[i].mStorage == nullptr)
						{
							AppendScope(mSignatures[i].mName);
						}
						else
						{
							mSignatures[i].mStorage->t[index]->AppendScope(mSignatures[i].mName);
						}
					}
					break;
				case Datum::DatumType::String:
					for (std::uint32_t index = 0; index < mSignatures[i].mSize; ++index)
					{
						if (mSignatures[i].mStorage == nullptr)
						{
							Signature::StorageType* initialValue = mSignatures[i].mInitialValue;

							// Internal storage
							if (initialValue == nullptr)
							{
								// Defualt value if none provided
								datum.Set("", index);
							}
							else
							{
								// Default value if provided
								datum.Set(*(initialValue->s), index);
							}
						}
						else
						{
							datum.SetStorage(mSignatures[i].mStorage->s, mSignatures[i].mSize);
						}
					}
					break;
				case Datum::DatumType::Pointer:
					for (std::uint32_t index = 0; index < mSignatures[i].mSize; ++index)
					{
						if (mSignatures[i].mStorage == nullptr)
						{
							Signature::StorageType* initialValue = mSignatures[i].mInitialValue;

							// Internal storage
							if (initialValue == nullptr)
							{
								// Defualt value if none provided
								datum.Set(nullptr, index);
							}
							else
							{
								// Default value if provided
								datum.Set(**(initialValue->p), index);
							}
						}
						else
						{
							datum.SetStorage(mSignatures[i].mStorage->p, mSignatures[i].mSize);
						}
					}
					break;
				default:
					break;
			}
		}
	}

	bool Attributed::IsPrescribedAttribute(const std::string& name) const
	{
		if (name == "this")
		{
			return true;
		}

		for (std::uint32_t i = 0; i < AuxiliaryBegin() - 1; ++i)
		{
			if (mSignatures[i].mName == name)
			{
				return true;
			}
		}

		return false;
	}

	bool Attributed::IsAuxiliaryAttribute(const std::string& name) const
	{
		return ((IsAttribute(name)) && (!IsPrescribedAttribute(name)));
	}

	bool Attributed::IsAttribute(const std::string& name) const
	{
		return (Find(name) != nullptr);
	}

	Datum& Attributed::AppendAuxiliaryAttribute(const std::string& name)
	{
		if (IsPrescribedAttribute(name))
		{
			throw std::exception("Error: The attribute is already a prescribed attribute.");
		}

		return Append(name);
	}

#pragma region AddInternalSignature

	void Attributed::AddInternalSignature(const std::string& name, std::int32_t* initialValue, const std::uint32_t size)
	{
		Signature* signature = new Signature(name, initialValue, size);
		assert(signature != nullptr);
		mSignatures.PushBack(*signature);
	}

	void Attributed::AddInternalSignature(const std::string& name, float* initialValue, const std::uint32_t size)
	{
		Signature* signature = new Signature(name, initialValue, size);
		assert(signature != nullptr);
		mSignatures.PushBack(*signature);
	}

	void Attributed::AddInternalSignature(const std::string& name, glm::vec4* initialValue, const std::uint32_t size)
	{
		Signature* signature = new Signature(name, initialValue, size);
		assert(signature != nullptr);
		mSignatures.PushBack(*signature);
	}

	void Attributed::AddInternalSignature(const std::string& name, glm::mat4* initialValue, const std::uint32_t size)
	{
		Signature* signature = new Signature(name, initialValue, size);
		assert(signature != nullptr);
		mSignatures.PushBack(*signature);
	}

	void Attributed::AddInternalSignature(const std::string& name, Scope** initialValue, const std::uint32_t size)
	{
		Signature* signature = new Signature(name, initialValue, size);
		assert(signature != nullptr);
		mSignatures.PushBack(*signature);
	}

	void Attributed::AddInternalSignature(const std::string& name, std::string* initialValue, const std::uint32_t size)
	{
		Signature* signature = new Signature(name, initialValue, size);
		assert(signature != nullptr);
		mSignatures.PushBack(*signature);
	}

	void Attributed::AddInternalSignature(const std::string& name, RTTI** initialValue, const std::uint32_t size)
	{
		Signature* signature = new Signature(name, initialValue, size);
		assert(signature != nullptr);
		mSignatures.PushBack(*signature);
	}

#pragma endregion

#pragma region AddExternalSignature

	void Attributed::AddExternalSignature(const std::string& name, const std::uint32_t size, std::int32_t* storage)
	{
		Signature* signature = new Signature(name, size, storage);
		assert(signature != nullptr);
		mSignatures.PushBack(*signature);
	}

	void Attributed::AddExternalSignature(const std::string& name, const std::uint32_t size, float* storage)
	{
		Signature* signature = new Signature(name, size, storage);
		assert(signature != nullptr);
		mSignatures.PushBack(*signature);
	}

	void Attributed::AddExternalSignature(const std::string& name, const std::uint32_t size, glm::vec4* storage)
	{
		Signature* signature = new Signature(name, size, storage);
		assert(signature != nullptr);
		mSignatures.PushBack(*signature);
	}

	void Attributed::AddExternalSignature(const std::string& name, const std::uint32_t size, glm::mat4* storage)
	{
		Signature* signature = new Signature(name, size, storage);
		assert(signature != nullptr);
		mSignatures.PushBack(*signature);
	}

	void Attributed::AddExternalSignature(const std::string& name, const std::uint32_t size, std::string* storage)
	{
		Signature* signature = new Signature(name, size, storage);
		assert(signature != nullptr);
		mSignatures.PushBack(*signature);
	}

	void Attributed::AddExternalSignature(const std::string& name, const std::uint32_t size, RTTI** storage)
	{
		Signature* signature = new Signature(name, size, storage);
		assert(signature != nullptr);
		mSignatures.PushBack(*signature);
	}

#pragma endregion

	std::uint32_t Attributed::AuxiliaryBegin() const
	{
		return (mSignatures.Size() + 1);
	}

	Attributed::Signature* Attributed::GetSignature(const std::string& name) const
	{
		for (std::uint32_t i = 0; i < mSignatures.Size(); ++i)
		{
			if (mSignatures[i].mName == name)
			{
				return const_cast<Signature*>(&mSignatures[i]);
			}
		}

		return nullptr;
	}

	Datum& Attributed::CreateTableDatum(const std::string& name)
	{
		Datum* datum = new Datum();
		assert(datum != nullptr);
		datum->SetType(Datum::DatumType::Table);
		Signature* signature = new Signature(name, static_cast<Scope**>(nullptr), 1);
		assert(signature != nullptr);
		mSignatures.PushBack(*signature);
		return *datum;
	}

#pragma endregion

}
