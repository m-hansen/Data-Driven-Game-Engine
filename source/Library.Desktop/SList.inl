#include "pch.h"

namespace Library
{

#pragma region Node

	template<typename T>
	SList<T>::Node::Node(const T& data, Node* next) :
		mData(data), mNextNode(next)
	{
	}

	template<typename T>
	bool SList<T>::Node::operator==(const Node& other)
	{
		return (mData == other.mData);
	}

	template<typename T>
	bool SList<T>::Node::operator!=(const Node& other)
	{
		return !(operator==(other));
	}

#pragma endregion

#pragma region Iterator

	template<typename T>
	SList<T>::Iterator::Iterator() :
		mList(nullptr), mNode(nullptr)
	{
	}

	template<typename T>
	SList<T>::Iterator::Iterator(const SList<T>* list, Node* node) :
		mList(list), mNode(node)
	{
	}

	template<typename T>
	SList<T>::Iterator::Iterator(const Iterator& rhs) :
		Iterator()
	{
		operator=(rhs);
	}

	template<typename T>
	SList<T>::Iterator::Iterator(Iterator&& rhs) :
		Iterator(rhs.mList, rhs.mNode)
	{
		rhs.mList = nullptr;
		rhs.mNode = nullptr;
	}

	template<typename T>
	typename SList<T>::Iterator& SList<T>::Iterator::operator=(const Iterator& rhs)
	{
		if (this != &rhs)
		{
			mNode = rhs.mNode;
			mList = rhs.mList;
		}

		return *this;
	}
	
	template<typename T>
	bool SList<T>::Iterator::operator==(const Iterator& rhs) const
	{
		return (mList == rhs.mList && mNode == rhs.mNode);
	}

	template<typename T>
	bool SList<T>::Iterator::operator!=(const Iterator& rhs) const
	{
		return !(operator==(rhs));
	}

	// Prefix
	template<typename T>
	typename SList<T>::Iterator& SList<T>::Iterator::operator++()
	{
		if (mList == nullptr)
		{
			std::exception("Cannot get the next iterator. The list is invalid.");
		}

		if (mNode == nullptr)
		{
			std::exception("Cannot get the next iterator. The end of the list was reached or the node was never set.");
		}

		mNode = mNode->mNextNode;
		return *this;
	}

	// Postfix
	template<typename T>
	typename SList<T>::Iterator SList<T>::Iterator::operator++(int)
	{
		SList<T>::Iterator it(*this);
		++(*this);
		return it;
	}
	
	template<typename T>
	T& SList<T>::Iterator::operator*() const
	{
		if (mNode == nullptr)
		{
			throw std::exception("Cannot dereference a nullptr");
		}

		return (mNode->mData);
	}

#pragma endregion

	template<typename T>
	SList<T>::SList() :
		mFront(nullptr), mBack(nullptr), mSize(0)
	{
	}

	template<typename T>
	SList<T>::SList(const SList& rhs) :
		SList()
	{
		operator=(rhs);
	}

	template<typename T>
	SList<T>& SList<T>::operator=(const SList& rhs)
	{
		// Protect against the case where list = list
		if (this != &rhs)
		{
			Clear();

			for (auto& value : rhs)
			{
				PushBack(value);
			}
		}

		return *this;
	}

	template<typename T>
	bool SList<T>::operator==(const SList& other) const
	{
		bool areEqual = true;

		if (mSize != other.mSize)
		{
			areEqual = false;
		}
		else 
		{
			Iterator thisIterator = begin();
			Iterator otherIterator = other.begin();

			for (uint32_t i = 0; i < mSize; ++i)
			{
				if (thisIterator.mNode != otherIterator.mNode)
				{
					areEqual = false;
					break;
				}

				++thisIterator;
				++otherIterator;
			}
		}

		return areEqual;
	}

	template<typename T>
	bool SList<T>::operator!=(const SList& other) const
	{
		return !(*this == other);
	}

	template<typename T>
	SList<T>::~SList()
	{
		Clear();
	}

	template<typename T>
	typename SList<T>::Iterator SList<T>::PushFront(const T& data)
	{
		Node* node = new Node(data);
		node->mNextNode = mFront;
		mFront = node;
		if (mBack == nullptr)
		{
			mBack = mFront;
		}
		++mSize;

		return Iterator(this, node);
	}

	template<typename T>
	void SList<T>::PopFront()
	{
		if (IsEmpty())
		{
			throw std::exception("Cannot pop the front of an empty list");
		}

		Node* newFront = mFront->mNextNode;

		delete mFront;
		mFront = newFront;
		--mSize;

		if (mSize == 0)
		{
			// The last item was removed from the list, tail should point to head, which is a nullptr
			mBack = mFront;
		}
	}

	template<typename T>
	typename SList<T>::Iterator SList<T>::PushBack(const T& data)
	{
		Node* node = new Node(data);

		if (mBack != nullptr)
		{
			// Point the previous tail's next node, if a tail existed, toward the newly created node
			mBack->mNextNode = node;
		}
		mBack = node;

		if (mFront == nullptr)
		{
			// Point the head toward the tail if this is the first node added to the list
			mFront = mBack;
		}

		++mSize;

		return Iterator(this, node);
	}

	template<typename T>
	inline bool SList<T>::IsEmpty() const
	{
		return (mSize == 0);
	}

	template<typename T>
	T& SList<T>::Front()
	{
		if (mFront == nullptr)
		{
			throw std::exception("Cannot get the front of an empty list!");
		}

		return mFront->mData;
	}

	template<typename T>
	T& SList<T>::Back()
	{
		if (mBack == nullptr)
		{
			throw std::exception("Cannot get the back of an empty list!");
		}

		return mBack->mData;
	}

	template<typename T>
	void SList<T>::Clear()
	{
		while (!IsEmpty())
		{
			PopFront();
		}
	}

	template<typename T>
	inline std::uint32_t SList<T>::Size() const
	{
		return mSize;
	}

	template<typename T>
	typename SList<T>::Iterator SList<T>::begin() const
	{
		return Iterator(this, mFront);
	}

	template<typename T>
	typename SList<T>::Iterator SList<T>::end() const
	{
		return Iterator(this);
	}

	template<typename T>
	void SList<T>::InsertAfter(const T& value, const Iterator& it)
	{
		if (it.mList != this)
		{
			throw std::exception("Iterator does not belong to this list.");
		}

		if (it.mNode == mBack || it.mNode == nullptr)
		{
			PushBack(value);
		}
		else
		{
			Node* newNode = new Node(value, it.mNode->mNextNode);
			it.mNode->mNextNode = newNode;
			++mSize;
		}
	}

	template<typename T>
	typename SList<T>::Iterator SList<T>::Find(const T& value) const
	{
		Iterator it = begin();

		while ((it != end()) && (*it.mNode != value))
		{
			++it;
		}

		return it;
	}

	template<typename T>
	typename SList<T>::Iterator SList<T>::FindPrevious(const T& value) const
	{
		Iterator it = begin();
		Iterator previousIter = end(); // Set the list and null out the node

		if (*it == value)
		{
			// Special case: the first node is the target value
			previousIter = it;
		}
		else
		{
			bool wasFound = false;

			while (it != end())
			{
				if (*it == value)
				{
					wasFound = true;
					break;
				}

				previousIter = it;
				++it;
			}

			if (!wasFound)
			{
				previousIter = end();
			}
		}

		return previousIter;
	}
	
	template<typename T>
	void SList<T>::Remove(const T& value)
	{
		Iterator previousIter = FindPrevious(value);

		// Only remove when the value is found
		if (previousIter != end())
		{
			if (*previousIter == value)
			{
				// Handle the special case where we are removing the front of the list
				PopFront();
			}
			else
			{
				Node* deleteNode = previousIter.mNode->mNextNode;

				// Point past the node we are about to delete
				previousIter.mNode->mNextNode = deleteNode->mNextNode;

				if (deleteNode == mBack)
				{
					// Set the new back node since we are deleting the current one
					mBack = previousIter.mNode;
				}

				delete deleteNode;
				deleteNode = nullptr;
				--mSize;

				if (IsEmpty())
				{
					mFront = mBack = nullptr;
				}

			}
		}
	}
}
