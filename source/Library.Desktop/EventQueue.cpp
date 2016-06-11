#include "pch.h"

namespace Library
{
	typedef std::chrono::milliseconds Milliseconds;

	EventQueue::EventQueue()
		: mEventQueue()
	{
	}

	void EventQueue::Enqueue(EventPublisher& publisher, const GameTime& gameTime, const Milliseconds& delay)
	{
		if (delay <= Milliseconds(0))
		{
			// There was no delay, bypass the queue
			Send(publisher);
		}
		else
		{
			// The delay is greater than zero, queue the event
			publisher.SetTime(gameTime.CurrentTime(), delay);

			// Wait to lock guard, we want an accurate timestamp on the publisher
			std::lock_guard<std::mutex> lock(mMutex);
			mEventQueue.PushBack(&publisher);
		}
	}

	void EventQueue::Send(const EventPublisher& publisher) const
	{
		publisher.Deliver();
	}

	void EventQueue::Update(const GameTime& gameTime)
	{
		std::vector<std::future<void>> futures;
		{
			std::lock_guard<std::mutex> lock(mMutex);
			for (auto& message : mEventQueue)
			{
				if (message->IsExpired(gameTime.CurrentTime()))
				{
					futures.emplace_back(std::async(std::launch::async, &EventPublisher::Deliver, message));
					mExpiredEvents.emplace_back(message);
				}
			}
		}
		
		// Wait for all messages to be finished processing before trying to remove expired events
		for (auto& f : futures)
		{
			f.get();
		}

		{
			std::lock_guard<std::mutex> lock(mMutex);
			for (auto& message : mExpiredEvents)
			{
				mEventQueue.Remove(message);
			}
			mExpiredEvents.clear();
		}
	}

	void EventQueue::Clear()
	{
		std::lock_guard<std::mutex> lock(mMutex);
		mEventQueue.Clear();
	}

	bool EventQueue::IsEmpty() const
	{
		std::lock_guard<std::mutex> lock(mMutex);
		return mEventQueue.IsEmpty();
	}

	std::uint32_t EventQueue::Size() const
	{
		std::lock_guard<std::mutex> lock(mMutex);
		return mEventQueue.Size();
	}

}
