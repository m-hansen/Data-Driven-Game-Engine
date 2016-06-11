#pragma once

#include <cstdint>

namespace Library
{
	/**
	 * @brief A singly-linked list.
	 *
	 * A list of nodes containing data that can be pushed to the front or
	 * back of the list. Data in the front or back of the list can be
	 * accessed and the first element in the list may be popped off.
	 */
	template<typename T>
	class SList
	{
	private:
		/**
		 * @brief Node that contains data to make up an SList.
		 */
		class Node
		{
		public:
			/**
			 * Construct a Node.
			 * 
			 * @param data the data the Node contains
			 * @param next an optional pointer to the next node
			 */
			Node(const T& data, Node* next = nullptr);

			/**
			 * Overloads the comparison operator.
			 *
			 * @param other the other node to compare against
			 * @return true if the two nodes are equal, false otherwise
			 */
			bool operator==(const Node& other);

			/**
			 * Overloads the comparison operator.
			 *
			 * @param other the other node to compare against.
			 * @return returns true if the two nodes are not equal, false otherwise
			 */
			bool operator!=(const Node& other);

			Node* mNextNode;			/**< Pointer to the next Node in the list. */
			T mData;					/**< The data the Node contains. */
		};

		Node* mFront;				/**< Pointer to the Node at the front of the list. */
		Node* mBack;				/**< Pointer to the Node at the back of the list. */
		std::uint32_t mSize;		/**< The number of nodes in the list */

	public:
		/**
		 * @brief A custom iterator for the SList class.
		 */
		class Iterator final
		{
		private:
			friend class SList;
			const SList* mList;		/**< Pointer to the SList the iterator belongs to. */
			Node* mNode;			/**< Pointer to the current Node. */

		public:
			/**
			 * Default constructor.
			 */
			Iterator();

			/**
			 * Used to construct an iterator that points to a list and an optional node.
			 *
			 * @param list the pointer to the SList
			 * @param node an optional parameter that points to the current Node
			 */
			Iterator(const SList<T>* list, Node* node = nullptr);

			/**
			 * Copy constructor.
			 *
			 * @param rhs the other Iterator to copy from
			 */
			Iterator(const Iterator& rhs);

			/**
			* Move constructor.
			*
			* @param rhs the other iterator to move data from
			*/
			Iterator(Iterator&& rhs);

			/**
			 * Overloads the assignment operator.
			 *
			 * @param rhs the other iterator to assign from
			 * @return a reference to an Iterator
			 */
			Iterator& operator=(const Iterator& rhs);
			
			/**
			 * Overloads the comparison operator to check if two SLists are equal.
			 *
			 * @param other the other SList to compare against
			 * @return returns true if two SLists are equivalent, false otherwise
			 */
			bool operator==(const Iterator& other) const;

			/**
			* Overloads the comparison operator to check if two SLists are not equal.
			*
			* @param other the other SList to compare against
			* @return returns true if two SLists are not equivalent, false otherwise
			*/
			bool operator!=(const Iterator& other) const;

			/**
			 * Overloads the prefix increment operator that reassigns the iterator to the next node.
			 *
			 * @return a reference to the next iterator
			 */
			Iterator& operator++();

			/**
			 * Overloads the postfix increment operator that reassigns the iterator to the next node.
			 *
			 * @param int a dummy parameter to distinguish between the prefix and postfix increment operators
			 * @return a reference to the next iterator
			 */
			Iterator operator++(int);

			/**
			 * Overload the dereference operator
			 *
			 * @return the data contained in the type
			 */
			T& operator*() const;
		};

		/**
		 * Constructor that initializes the list.
		 */
		SList();

		/**
		 * Copy-constructor that does a deep copy.
		 *
		 * @param rhs a singly-linked list to be copied
		 */
		SList(const SList& rhs);

		/**
		 * Overloads the assignment operator to check for equality between two singly-linked lists.
		 *
		 * @param rhs the right-hand side argument in the equals operation
		 * @return a reference to the SList
		 */
		SList& operator=(const SList& rhs);

		/**
		 * Overloads the comparison operator to check for equality between two SLists
		 *
		 * @param other the other SList to compare against
		 * @return true if the two lists have the same number of identical Nodes in the same order, false otherwise
		 */
		bool operator==(const SList& other) const;

		/**
		 * Overloads the comparison operator to check for equality between two SLists
		 *
		 * @param other the other SList to compare against
		 * @return true if the two lists do not have the same number of identical Nodes in the same order, false otherwise
		 */
		bool operator!=(const SList& other) const;

		/**
		 * The destructor that clears out the list and removes it from memory.
		 */
		~SList();

		/**
		 * Insert an item before the front of the list.
		 *
		 * @param data the data to add at the beginning of the list
		 * @return an Iterator pointing at the new Node
		 */
		Iterator PushFront(const T& data);

		/**
		 * Remove the first item of the list.
		 */
		void PopFront();

		/**
		 * Append an item after the end of the list.
		 *
		 * @param data the data to add at the end of the list
		 * @return an Iterator pointing at the new Node
		 */
		Iterator PushBack(const T& data);

		/**
		 * Returns a boolean indicating whether the lsit contains any items.
		 *
		 * @return Returns true if the list is empty, false otherwise.
		 */
		bool IsEmpty() const;

		/**
		 * Returns a reference to the first item in the list.
		 *
		 * @return the data at the front of the list
		 */
		T& Front();

		/**
		 * Returns a reference to the last item in the list.
		 *
		 * @return the data at the back of the list
		 */
		T& Back();

		/**
		 * Removes all items in the list.
		 */
		void Clear();

		/**
		 * Returns an unsigned integer, indicating how many nodes are in the list.
		 *
		 * @return the number of nodes the list contains
		 */
		std::uint32_t Size() const;

		/**
		 * Returns an iterator that points to the front of the list.
		 *
		 * @return an iterator that points to the front of the list
		 */
		Iterator begin() const;

		/**
		 * Returns an iterator that points past the end of the list.
		 *
		 * @return an iterator that points past the end of the list
		 */
		Iterator end() const;

		/**
		 * Appends an item after another item that the specified iterator points to.
		 *
		 * @param value a reference to the value to insert into the SList
		 * @param it a reference to the iterator immediately before the desired insert location 
		 */
		void InsertAfter(const T& value, const Iterator& it);

		/**
		 * Searches the list for a given Value. The iterator for the first found value will be returned.
		 *
		 * @param value the value to search for
		 * @return an iterator that points to the first found value in the SList
		 */
		Iterator Find(const T& value) const;

		/**
		 * Searches the list for a given value. The iterator immediately before the found value will be returned 
		 * (not the iterator that points to the found value).
		 *
		 * @param value the value to search for
		 * @return an iterator that points to the iterator before the found value in the SList
		 */
		Iterator FindPrevious(const T& value) const;

		/**
		 * Removes an item with the specified value from the SList. Only the first instance will be removed.
		 * 
		 * @param value the value to search for and remove
		 */
		void Remove(const T& value);
	};
}

#include "SList.inl"
