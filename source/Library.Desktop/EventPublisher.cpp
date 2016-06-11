#include "pch.h"

namespace Library
{
	RTTI_DEFINITIONS(EventPublisher)

	typedef std::chrono::high_resolution_clock::time_point TimePoint;
	typedef std::chrono::milliseconds Milliseconds;

	EventPublisher::EventPublisher(Vector<IEventSubscriber*>& subscribers)
		: mSubscribers(&subscribers)
	{
	}

	bool EventPublisher::IsExpired(const TimePoint& currentTime) const
	{
		std::lock_guard<std::mutex> lock(mMutex);
		return (currentTime > (mEnqueuedTime + mDelay));
	}

	void EventPublisher::Deliver() const
	{
		std::vector<std::future<void>> futures;
		{
			std::lock_guard<std::mutex> lock(mMutex);
			for (auto& subscriber : *mSubscribers)
			{
				futures.emplace_back(std::async(&IEventSubscriber::Notify, subscriber, std::ref(*this)));
			}
		}

		for (auto& f : futures)
		{
			f.get();
		}
	}

	const Milliseconds& EventPublisher::Delay() const
	{
		std::lock_guard<std::mutex> lock(mMutex);
		return mDelay;
	}

	const TimePoint& EventPublisher::TimeEnqueued() const
	{
		std::lock_guard<std::mutex> lock(mMutex);
		return mEnqueuedTime;
	}

	void EventPublisher::SetTime(const TimePoint& currentTime, const Milliseconds& delay)
	{
		std::lock_guard<std::mutex> lock(mMutex);
		mEnqueuedTime = currentTime;
		mDelay = delay;
	}

}
