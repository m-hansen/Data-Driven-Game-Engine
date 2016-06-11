#include "pch.h"

namespace Library
{

#pragma region Iterator

	template<typename TKey, typename TData, typename HashFunctor>
	HashMap<TKey, TData, HashFunctor>::Iterator::Iterator() :
		mOwner(nullptr), mNodeInChain(nullptr), mIndex(0)
	{
	}

	template<typename TKey, typename TData, typename HashFunctor>
	HashMap<TKey, TData, HashFunctor>::Iterator::Iterator(const HashMap* owner, typename ChainType::Iterator chainIterator, const std::uint32_t index) :
		mOwner(owner), mNodeInChain(chainIterator), mIndex(index)
	{
	}

	template<typename TKey, typename TData, typename HashFunctor>
	HashMap<TKey, TData, HashFunctor>::Iterator::Iterator(const Iterator& rhs) :
		mOwner(rhs.mOwner), mNodeInChain(rhs.mNodeInChain), mIndex(rhs.mIndex)
	{
	}

	template<typename TKey, typename TData, typename HashFunctor>
	typename HashMap<TKey, TData, HashFunctor>::Iterator& HashMap<TKey, TData, HashFunctor>::Iterator::operator=(const Iterator& rhs)
	{
		if (this != &rhs)
		{
			mOwner = rhs.mOwner;
			mIndex = rhs.mIndex;
			mNodeInChain = rhs.mNodeInChain;
		}

		return *this;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	typename HashMap<TKey, TData, HashFunctor>::Iterator& HashMap<TKey, TData, HashFunctor>::Iterator::operator++()
	{
		if (mOwner == nullptr || mIndex == mOwner->mBuckets.Size())
		{
			throw std::exception("Cannot increment iterator.");
		}

		if (++mNodeInChain == mOwner->mBuckets[mIndex].end())
		{
			// We reached the end of a chain, so search for the next populated bucket
			while (++mIndex < mOwner->mBuckets.Size() && mOwner->mBuckets[mIndex].IsEmpty())
			{
				// Intentionally left blank
				// Searching for the next populated bucket
			}

			if (mIndex == mOwner->mBuckets.Size())
			{
				// No additional populated buckets were found, set the node to the end of the last bucket
				mNodeInChain = mOwner->mBuckets[mIndex - 1].end();
			}
			else
			{
				// Get the beginning of the next populated bucket
				mNodeInChain = mOwner->mBuckets[mIndex].begin();
			}
		}

		return *this;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	typename HashMap<TKey, TData, HashFunctor>::Iterator HashMap<TKey, TData, HashFunctor>::Iterator::operator++(int)
	{
		Iterator it = *this;
		operator++();
		return it;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	typename HashMap<TKey, TData, HashFunctor>::PairType& HashMap<TKey, TData, HashFunctor>::Iterator::operator*() const
	{
		if (mOwner == nullptr)
		{
			throw std::exception("Cannot reference a nullptr.");
		}

		return *mNodeInChain;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	typename HashMap<TKey, TData, HashFunctor>::PairType* HashMap<TKey, TData, HashFunctor>::Iterator::operator->() const
	{
		return &(*mNodeInChain);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	bool HashMap<TKey, TData, HashFunctor>::Iterator::operator==(const Iterator& other) const
	{
		return ((mOwner == other.mOwner) && (mNodeInChain == other.mNodeInChain) && (mIndex == other.mIndex));
	}

	template<typename TKey, typename TData, typename HashFunctor>
	bool HashMap<TKey, TData, HashFunctor>::Iterator::operator!=(const Iterator& other) const
	{
		return !(operator==(other));
	}

#pragma endregion

#pragma region HashMap

	template<typename TKey, typename TData, typename HashFunctor>
	HashMap<TKey, TData, HashFunctor>::HashMap(std::uint32_t sizeOfTable) :
		mSize(0), mBuckets(BucketType(sizeOfTable, true))
	{
		if (sizeOfTable == 0)
		{
			throw std::exception("The size of the table cannot be zero.");
		}
	}

	template<typename TKey, typename TData, typename HashFunctor>
	typename HashMap<TKey, TData, HashFunctor>::Iterator HashMap<TKey, TData, HashFunctor>::Find(const TKey& key) const
	{
		std::uint32_t index = 0;
		return Find(key, index);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	typename HashMap<TKey, TData, HashFunctor>::Iterator HashMap<TKey, TData, HashFunctor>::Find(const TKey& key, std::uint32_t& hashIndex) const
	{
		hashIndex = HashFunctor()(key) % mBuckets.Size();
		for (auto it = mBuckets[hashIndex].begin(); it != mBuckets[hashIndex].end(); ++it)
		{
			if ((*it).first == key)
			{
				return Iterator(this, it, hashIndex);
			}
		}

		return end();
	}

	template<typename TKey, typename TData, typename HashFunctor>
	typename HashMap<TKey, TData, HashFunctor>::Iterator HashMap<TKey, TData, HashFunctor>::Insert(const PairType& entry)
	{
		bool trashVariable = false; // this is just a dummy variable
		return Insert(entry, trashVariable);
	}

	template<typename TKey, typename TData, typename HashFunctor>
	typename HashMap<TKey, TData, HashFunctor>::Iterator HashMap<TKey, TData, HashFunctor>::Insert(const PairType& entry, bool& wasInserted)
	{
		wasInserted = false;
		std::uint32_t index = 0;
		Iterator foundIter = Find(entry.first, index);
		if (foundIter == end())
		{
			// The key wasn't found, create a new entry
			auto chainIter = mBuckets[index].PushBack(PairType(entry.first, entry.second));
			foundIter = Iterator(this, chainIter, index);
			++mSize;
			wasInserted = true;
		}
		return foundIter;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	TData& HashMap<TKey, TData, HashFunctor>::operator[](const TKey& key)
	{
		Iterator it = Insert(PairType(key, TData()));
		return it->second;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	void HashMap<TKey, TData, HashFunctor>::Remove(const TKey& key)
	{
		Iterator it = Find(key);
		if (it != end())
		{
			mBuckets[it.mIndex].Remove(*it);
			--mSize;
		}
	}

	template<typename TKey, typename TData, typename HashFunctor>
	void HashMap<TKey, TData, HashFunctor>::Clear()
	{
		for (std::uint32_t i = 0; i < mBuckets.Size(); ++i)
		{
			mBuckets[i].Clear();
		}
		mSize = 0;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	std::uint32_t HashMap<TKey, TData, HashFunctor>::Size() const
	{
		return mSize;
	}

	template<typename TKey, typename TData, typename HashFunctor>
	bool HashMap<TKey, TData, HashFunctor>::ContainsKey(const TKey& key) const
	{
		return (Find(key) != end());
	}

	template<typename TKey, typename TData, typename HashFunctor>
	typename HashMap<TKey, TData, HashFunctor>::Iterator HashMap<TKey, TData, HashFunctor>::begin() const
	{
		for (std::uint32_t i = 0; i < mBuckets.Size(); ++i)
		{
			if (!mBuckets[i].IsEmpty())
			{
				return Iterator(this, mBuckets[i].begin(), i);
			}
		}

		return end();
	}

	template<typename TKey, typename TData, typename HashFunctor>
	typename HashMap<TKey, TData, HashFunctor>::Iterator HashMap<TKey, TData, HashFunctor>::end() const
	{
		return Iterator(this, mBuckets[mBuckets.Size() - 1].end(), mBuckets.Size());
	}

#pragma endregion

}