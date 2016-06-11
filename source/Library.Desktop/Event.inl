#include "pch.h"

namespace Library
{
	template<typename MessageT>
	RTTI_DEFINITIONS(Event<MessageT>)

	template<typename MessageT>
	Vector<IEventSubscriber*> Event<MessageT>::mSubscribers = Vector<IEventSubscriber*>();

	template<typename MessageT>
	std::mutex Event<MessageT>::mMutex;

	template<typename MessageT>
	Event<MessageT>::Event(const MessageT& message)
		: mMessage(message), EventPublisher(mSubscribers)
	{
	}

	template<typename MessageT>
	void Event<MessageT>::Subscribe(IEventSubscriber& subscriber)
	{
		std::lock_guard<std::mutex> lock(mMutex);
		mSubscribers.PushBack(&subscriber);
	}

	template<typename MessageT>
	void Event<MessageT>::Unsubscribe(IEventSubscriber& subscriber)
	{
		std::lock_guard<std::mutex> lock(mMutex);
		mSubscribers.Remove(&subscriber);
	}

	template<typename MessageT>
	void Event<MessageT>::UnsubscribeAll()
	{
		std::lock_guard<std::mutex> lock(mMutex);
		mSubscribers.Clear();
	}

	template<typename MessageT>
	const MessageT& Event<MessageT>::Message() const
	{
		std::lock_guard<std::mutex> lock(mMutex);
		return mMessage;
	}

}
