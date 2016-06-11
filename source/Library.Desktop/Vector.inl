#include "pch.h"

namespace Library
{

#pragma region Iterator

	template<typename T>
	Vector<T>::Iterator::Iterator() :
		mVector(nullptr), mOffset(0)
	{
	}

	template<typename T>
	Vector<T>::Iterator::Iterator(const Vector* vector, std::uint32_t offset) :
		mVector(vector), mOffset(offset)
	{
	}

	template<typename T>
	Vector<T>::Iterator::Iterator(const Iterator& rhs) :
		Iterator()
	{
		operator=(rhs);
	}

	template<typename T>
	typename Vector<T>::Iterator& Vector<T>::Iterator::operator=(const Iterator& rhs)
	{
		if (this != &rhs)
		{
			mVector = rhs.mVector;
			mOffset = rhs.mOffset;
		}

		return *this;
	}

	template<typename T>
	bool Vector<T>::Iterator::operator==(const Iterator& other) const
	{
		return ((mVector == other.mVector) && (mOffset == other.mOffset));
	}

	template<typename T>
	bool Vector<T>::Iterator::operator!=(const Iterator& other) const
	{
		return !(operator==(other));
	}

	template<typename T>
	typename Vector<T>::Iterator& Vector<T>::Iterator::operator++()
	{
		if (mVector == nullptr || mOffset >= mVector->Size())
		{
			throw std::exception("Cannot increment iterator. The bounds sre invalid.");
		}

		++mOffset;
		return *this;
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::Iterator::operator++(int)
	{
		Iterator it = *this;
		operator++();
		return it;
	}

	template<typename T>
	T& Vector<T>::Iterator::operator*() const
	{
		if (mVector == nullptr)
		{
			throw std::exception("Cannot dereference a nullptr");
		}

		if (mOffset >= mVector->Size())
		{
			throw std::exception("Index out of range.");
		}

		return mVector->mItem[mOffset];
	}

#pragma endregion

#pragma region Vector

	template<typename T>
	Vector<T>::Vector(const std::uint32_t capacity, const bool isFixedSize) :
		mSize(0), mCapacity(0), mItem(nullptr), mIsFixedSize(isFixedSize)
	{
		Reserve(capacity);
	}

	template<typename T>
	Vector<T>::Vector(const Vector& rhs) :
		mSize(0), mCapacity(0), mItem(nullptr), mIsFixedSize(rhs.mIsFixedSize)
	{
		operator=(rhs);
	}

	template<typename T>
	Vector<T>::Vector(Vector&& rhs) :
		mSize(rhs.mSize), mCapacity(rhs.mCapacity), mData(rhs.mData), mIsFixedSize(rhs.mIsFixedSize)
	{
		rhs.mSize = 0;
		rhs.mCapacity = 0;
		rhs.mData = nullptr;
		rhs.mIsFixedSize = false;
	}

	template<typename T>
	Vector<T>& Vector<T>::operator=(const Vector& rhs)
	{
		if (this != &rhs)
		{
			Clear();
			Reserve(rhs.mCapacity);

			for (const auto& value : rhs)
			{
				PushBack(value);
			}
		}

		return *this;
	}

	template<typename T>
	Vector<T>& Vector<T>::operator=(Vector&& rhs)
	{
		if (this != &rhs)
		{
			Clear();

			mSize = rhs.mSize;
			mCapacity = rhs.mCapacity;
			mData = rhs.mData;
			mIsFixedSize = rhs.mIsFixedSize;

			rhs.mSize = 0;
			rhs.mCapacity = 0;
			rhs.mData = nullptr;
		}

		return *this;
	}

	template<typename T>
	bool Vector<T>::operator==(const Vector& other)
	{
		if (mSize != other.mSize)
		{
			return false;
		}

		for (std::uint32_t i = 0; i < mSize; ++i)
		{
			if (mItem[i] != other.mItem[i])
			{
				return false;
			}
		}

		return true;
	}

	template<typename T>
	bool Vector<T>::operator!=(const Vector& other)
	{
		return !(operator==(other));
	}

	template<typename T>
	const T& Vector<T>::operator[](const std::uint32_t index) const
	{
		if (index >= mCapacity)
		{
			throw std::exception("The index is out of range.");
		}
		return mItem[index];
	}

	template<typename T>
	T& Vector<T>::operator[](const std::uint32_t index)
	{
		if (index >= mCapacity)
		{
			throw std::exception("The index is out of range.");
		}
		return mItem[index];
	}

	template<typename T>
	Vector<T>::~Vector()
	{
		Clear();
	}

	template<typename T>
	T& Vector<T>::At(const std::uint32_t index) const
	{
		if (index >= mSize)
		{
			throw std::exception("Invalid index. Index out of range.");
		}

		return mItem[index];
	}

	template<typename T>
	const T& Vector<T>::Front() const
	{
		if (IsEmpty())
		{
			throw std::exception("Cannot access the front of the vector. The vector is empty.");
		}

		return mItem[0];
	}

	template<typename T>
	T& Vector<T>::Front()
	{
		if (IsEmpty())
		{
			throw std::exception("Cannot access the front of the vector. The vector is empty.");
		}

		return mItem[0];
	}

	template<typename T>
	const T& Vector<T>::Back() const
	{
		if (IsEmpty())
		{
			throw std::exception("Cannot access the back of the vector. The vector is empty.");
		}

		return mItem[mSize - 1];
	}
	
	template<typename T>
	T& Vector<T>::Back()
	{
		if (IsEmpty())
		{
			throw std::exception("Cannot access the back of the vector. The vector is empty.");
		}

		return mItem[mSize - 1];
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::PushBack(const T& item)
	{
		if (mSize == mCapacity)
		{
			// Increase the capacity
			Reserve(mCapacity + mCapacityIncrement);
		}

		std::uint32_t backIndex = mSize;
		new(mItem + mSize)T(item);
		++mSize;

		return Iterator(this, backIndex);
	}

	template<typename T>
	void Vector<T>::PopBack()
	{
		if (!IsEmpty())
		{
			mItem[--mSize].~T();
		}
	}

	template<typename T>
	void Vector<T>::Clear()
	{
		for (std::uint32_t i = 0; i < mSize; ++i)
		{
			mItem[i].~T();
		}

		free(mItem);
		mItem = nullptr;
		mSize = 0;
		mCapacity = 0;
	}

	template<typename T>
	inline std::uint32_t Vector<T>::Size() const
	{
		return mSize;
	}

	template<typename T>
	inline std::uint32_t Vector<T>::Capacity() const
	{
		return mCapacity;
	}

	template<typename T>
	void Vector<T>::Reserve(const std::uint32_t capacity)
	{
		if (capacity > mCapacity)
		{
			mItem = reinterpret_cast<T*>(std::realloc(mItem, sizeof(T) * capacity));

			if (mIsFixedSize)
			{
				for (std::uint32_t i = mSize; i < capacity; ++i)
				{
					new(mItem + i)T();
				}
				mSize = capacity;
			}

			mCapacity = capacity;
		}
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::Find(const T& item) const
	{
		Iterator returnValue = end();

		for (auto it = begin(); it != end(); ++it)
		{
			if (*it == item)
			{
				returnValue = it;
				break;
			}
		}

		return returnValue;
	}

	template<typename T>
	void Vector<T>::Remove(const T& item)
	{
		Iterator it = Find(item);
		if (it != end())
		{
			mItem[it.mOffset].~T();

			auto size = (mSize - it.mOffset - 1) * sizeof(T);
			if (size > 0)
			{
				memmove_s(&mItem[it.mOffset], size, &mItem[it.mOffset + 1], size);
			}
			--mSize;
		}
	}

	template<typename T>
	inline bool Vector<T>::IsEmpty() const
	{
		return (mSize == 0);
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::begin() const
	{
		return Iterator(this, 0);
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::end() const
	{
		return Iterator(this, mSize);
	}

#pragma endregion

}
