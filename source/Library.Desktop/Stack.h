#pragma once

#include <cstdint>

namespace Library
{
	/**
	 * A Last In, First Out adaptive container that builds off of a Vector.
	 */
	template<typename T>
	class Stack
	{
	public:

		/**
		 * Default constructor.
		 */
		Stack() = default;

		/**
		 * Copy constructor.
		 *
		 * @param rhs the Stack to copy from
		 */
		Stack(const Stack& rhs);

		/**
		 * Overloads the assignment operator.
	 	 *
		 * @param rhs the Stack to assign from
		 */
		Stack& operator=(const Stack& rhs) = default;

		/**
		 * Deconstructor to free memory.
		 */
		~Stack() = default;

		/**
		 * Increases the size of the stack by 1 and assigns the top of the stack to a given value.
		 *
		 * @param item the item to push on the Stack
		 */
		void Push(const T& item);

		/**
		 * Removes and returns the top element of the Stack.
		 *
		 * @return the element on top of the Stack
		 */
		T Pop();

		/**
		 * Returns the item that is on top of the Stack.
		 *
		 * @return the element on top of the Stack
		 */
		T& Top();

		/**
		 * Returns the item that is on top of the Stack.
		 *
		 * @return the element on top of the Stack
		 */
		const T& Top() const;

		/**
		 * Returns the number of items in the Stack.
		 *
		 * @return the number of elements in the Stack
		 */
		std::uint32_t Size() const;

		/**
		 * Returns whether the Stack is empty.
		 *
		 * @return true if the Stack is empty, false otherwise
		 */
		bool IsEmpty() const;

		/**
		 * Clears the contents of the Stack.
		 */
		void Clear();
	private:
		Vector<T> mVector;				/**< The data structure that the Stack builds off of. */
	};
}

#include "Stack.inl"
