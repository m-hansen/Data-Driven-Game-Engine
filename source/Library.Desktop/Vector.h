#pragma once

#include <cstdint>

namespace Library
{
	/**
	 * A container class that allocated contiguous memory to store any data type.
	 */
	template<typename T>
	class Vector
	{
	public:
		/**
		 * A custom Iterator for the Vector class.
		 */
		class Iterator final
		{
		public:
			/**
			 * Default constructor.
			 */
			Iterator();

			/**
			 * Copy constructor.
			 *
			 * @param rhs the other Iterator to copy from
			 */
			Iterator(const Iterator& rhs);

			/**
			 * Overloads the assignment operator.
			 *
			 * @param rhs the other Iterator to assign from
			 * @return a reference to an Iterator
			 */
			Iterator& operator=(const Iterator& rhs);

			/**
			 * Overloads the comparison operator to check if two Vector iterators are equal.
			 *
			 * @param other the other Vector iterator to compare against
			 * @return returns true if two Vector iterators are equivalent, false otherwise
			 */
			bool operator==(const Iterator& other) const;

			/**
			 * Overloads the comparison operator to check if two Vector iterators are equal.
			 *
			 * @param other the other Vector iterator to compare against
			 * @return returns true if two Vector iterators are not equivalent, false otherwise
			 */
			bool operator!=(const Iterator& other) const;

			/**
			 * Overloads the prefix increment operator that reassigns the Iterator to the next item.
			 *
			 * @return a reference to the next Iterator
			 */
			Iterator& operator++();

			/**
			 * Overloads the postfix increment operator that reassigns the Iterator to the next item.
			 *
			 * @param int a dummy parameter to distinguish between the prefix and postfix increment operators
			 * @return a reference to the next Iterator
			 */
			Iterator operator++(int);

			/**
			 * Overload the dereference operator
			 *
			 * @return the data contained in the type
			 */
			T& operator*() const;
		private:

			/**
			* Used to construct an iterator that points to a Vector and an offset.
			*
			* @param vector the pointer to the Vector
			* @param offset the position in the Vector
			*/
			Iterator(const Vector* vector, std::uint32_t offset);

			friend class Vector;
			const Vector<T>* mVector;		/**< Pointer to the Vector the Iterator belongs to. */
			std::uint32_t mOffset;			/**< The position offset in the Vector. */
		};

		/**
		 * Default constructor to initialize the vector to be empty.
		 */
		Vector(std::uint32_t capacity = 0, const bool isFixedSize = false);

		/**
		 * Copy constructor that performs a deep copy.
		 *
		 * @param rhs the other Vector to copy from
		 */
		Vector(const Vector& rhs);

		/**
		 * Move constructor.
		 * 
		 * @param rhs the Vector to move
		 */
		Vector(Vector&& rhs);

		/**
		 * Deconstructor to free memory.
		 */
		~Vector();

		/**
		 * Assignment operator to perform a deep copy.
		 *
		 * @param rhs the other Vector to copy from
		 * @return a reference to the new Vector
		 */
		Vector& operator=(const Vector& rhs);

		/**
		 * Assignment operator that moves a Vector
		 *
		 * @param rhs the Vector to move
		 */
		Vector& operator=(Vector&& rhs);

		/**
		 * Overloads the comparison operator to check if two Vectors are equal.
		 *
		 * @param other the other Vector to compare against
		 * @return returns true if two Vectors are equivalent, false otherwise
		 */
		bool operator==(const Vector& other);

		/**
		 * Overloads the comparison operator to check if two Vectors are not equal.
		 *
		 * @param other the other Vector to compare against
		 * @return returns true if two Vectors are not equivalent, false otherwise
		 */
		bool operator!=(const Vector& other);

		/**
		 * Returns a reference to the item at a given index.
		 *
		 * @param index the index of the item
		 * @return the item at a given index
		 */
		const T& operator[](const std::uint32_t index) const;

		/**
		 * Returns a reference to the item at a given index.
		 *
		 * @param index the index of the item
		 * @return the item at a given index
		 */
		T& operator[](const std::uint32_t index);

		/**
		 * Returns a reference to the item at a given index.
		 *
		 * @param index the index of the item
		 * @return the item at a given index
		 */
		T& At(const std::uint32_t index) const;

		/**
		 * Returns the first item in the container.
		 *
		 * @return reference to the first item in the container
		 */
		const T& Front() const;

		/**
		 * Returns the first item in the container.
		 *
		 * @return reference to the first item in the container
		 */
		T& Front();

		/**
		 * Returns the last item in the container.
		 *
		 * @return reference to the last item in the container
		 */
		const T& Back() const;

		/**
		 * Returns the last item in the container.
		 *
		 * @return reference to the last item in the container
		 */
		T& Back();

		/**
		 * Append an item to the back of the Vector
		 *
		 * @param item the item to append
		 * @return an Iterator pointing at the new item
		 */
		Iterator PushBack(const T& item);

		/**
		 * Removes the last item in the container without changing the capacity.
		 */
		void PopBack();

		/**
		 * Empties the container.
		 */
		void Clear();

		/**
		 * Returns the number of items in the container as an unsigned integer.
		 *
		 * @return the number of items in the container
		 */
		std::uint32_t Size() const;

		/**
		 * Returns the number of items allocated in the container as an unsigned integer.
		 *
		 * @return the number of items allocated in the container
		 */
		std::uint32_t Capacity() const;

		/**
		 * Increases the capacity to the new value specified, if it is larger than the previous capacity.
		 *
		 * @param capacity the new capacity of the vector
		 */
		void Reserve(const std::uint32_t capacity);

		/**
		 * Search the list for a specified item.
		 *
		 * @param item the item to search for
		 * @return and Iterator pointing at an item in the Vector
		 */
		Iterator Find(const T& item) const;

		/**
		 * Removes an item from the Vector.
		 *
		 * @param item the item to remove from the Vector
		 */
		void Remove(const T& item);

		/**
		 * Determines if the Vector is empty or not.
		 *
		 * @return true if the Vector is empty, false otherwise
		 */
		bool IsEmpty() const;

		/**
		 * Returns an Iterator pointing at the first element in the container.
		 *
		 * @return an Iterator pointing at the first element in the container
		 */
		Iterator begin() const;

		/**
		 * Returns an Iterator indicating that it is not in the container.
		 *
		 * @return an Iterator indicating that it is not in the container
		 */
		Iterator end() const;
	private:
		const std::uint32_t mCapacityIncrement = 1;			/**< The amount to increment capacity by when the user does not specify through Reserve() */
		std::uint32_t mCapacity;							/**< The space allocated for the Vector */
		std::uint32_t mSize;								/**< The number of items in the Vector */
		T* mItem;											/**< The data contained within the Vector */
		bool mIsFixedSize;									/**< Flag to set the Vector's size is always equal to its capacity */
	};
}

#include "Vector.inl"
