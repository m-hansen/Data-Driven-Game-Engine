#include "pch.h"

namespace Library
{

	template<typename T>
	Stack<T>::Stack(const Stack& rhs) :
		mVector(rhs.mVector)
	{
	}

	//template<typename T>
	//Stack<T>& Stack<T>::operator=(const Stack& rhs)
	//{
	//	if (this != &rhs)
	//	{
	//		mVector = rhs.mVector;
	//	}

	//	return *this;
	//}

	template<typename T>
	void Stack<T>::Push(const T& item)
	{
		mVector.PushBack(item);
	}

	template<typename T>
	T Stack<T>::Pop()
	{
		T topItem = mVector.Back();
		mVector.PopBack();
		return topItem;
	}

	template<typename T>
	T& Stack<T>::Top()
	{
		return mVector.Back();
	}

	template<typename T>
	const T& Stack<T>::Top() const
	{
		return mVector.Back();
	}

	template<typename T>
	std::uint32_t Stack<T>::Size() const
	{
		return mVector.Size();
	}

	template<typename T>
	bool Stack<T>::IsEmpty() const
	{
		return mVector.IsEmpty();
	}

	template<typename T>
	void Stack<T>::Clear()
	{
		mVector.Clear();
	}

}
