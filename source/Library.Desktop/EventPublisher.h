#pragma once

#include <chrono>
#include <mutex>
#include "RTTI.h"

namespace Library
{
	class IEventSubscriber;

	/**
	 * Responsible for delivering events to a list of subscribers.
	 */
	class EventPublisher : public RTTI
	{
		RTTI_DECLARATIONS(EventPublisher, RTTI)

		typedef std::chrono::high_resolution_clock::time_point TimePoint;
		typedef std::chrono::milliseconds Milliseconds;

	public:
		/**
		 * Constructs an EventPublisher with a list of subscribers.
		 */
		explicit EventPublisher(Vector<IEventSubscriber*>& subscribers);

		// Prevent publisher from being copied or moved
		EventPublisher(const EventPublisher& rhs) = delete;
		EventPublisher(EventPublisher&& rhs) = delete;
		EventPublisher& operator=(const EventPublisher& rhs) = delete;

		/**
		 * Default destructor.
		 */
		~EventPublisher() = default;

		/**
		 * Takes the current time and returns true if the event has expired.
		 *
		 * @param currentTime the current time
		 * @return true if the event has expired, false otherwise
		 */
		bool IsExpired(const TimePoint& currentTime) const;

		/**
		 * Notify all subscribers of this event.
		 */
		void Deliver() const;

		/**
		 *Returns the amount of time after being enqueued that this event expires.
		 *
		 * @return the amount of time after being enqueued that this event expires
		 */
		const Milliseconds& Delay() const;

		/**
		 * Returns the time when this event was enqueued.
		 *
		 * @return the time when this event was enqueued
		 */
		const TimePoint& TimeEnqueued() const;

		/**
		 * Sets the current time and optionally, the delay.
		 *
		 * @param currentTime the current time
		 * @param delay optional param for the delay
		 */
		void SetTime(const TimePoint& currentTime, const Milliseconds& delay = Milliseconds(0));

	private:
		Vector<IEventSubscriber*>* mSubscribers;	/**< Points to an Event's subscribers. */
		TimePoint mEnqueuedTime;					/**< Time the event was enqueued. */
		Milliseconds mDelay;						/**< Amount of time after being enqueued that an event expires. */
		mutable std::mutex mMutex;					/**< The mutex used to lock the EventPublisher. */
	};
}
