#pragma once

#include <cstdint>
#include <chrono>
#include <mutex>

namespace Library
{
	class EventPublisher;
	class GameTime;

	typedef std::chrono::milliseconds Milliseconds;

	/**
	 * Handles the sending of Events. Supports both immediate and delayed sending.
	 */
	class EventQueue final
	{
	public:
		/**
		 * Default constructor.
		 */
		EventQueue();

		// Prevent copying
		EventQueue(const EventQueue& rhs) = delete;
		EventQueue& operator=(const EventQueue& rhs) = delete;

		/**
		 * Default destructor.
		 */
		~EventQueue() = default;

		/**
		 * Add the Event to a queue.
		 *
		 * @param publisher the event publisher
		 * @param gameTime used to get the current time
		 * @param delay optional parameter for the delay time
		 */
		void Enqueue(EventPublisher& publisher, const GameTime& gameTime, const Milliseconds& delay = Milliseconds(0));

		/**
		 * Immediately sends an Event.
		 *
		 * @publisher the event publisher
		 */
		void Send(const EventPublisher& publisher) const;

		/**
		 * Publishes any expired events.
		 *
		 * @gameTime used to ge the time
		 */
		void Update(const GameTime& gameTime);

		/**
		 * Clears the event queue.
		 */
		void Clear();

		/**
		 * Returns a boolean indicating the emptiness of the queue.
		 */
		bool IsEmpty() const;

		/**
		 * Returns the number of events in the queue.
		 *
		 * @return the number of events in the queue
		 */
		std::uint32_t Size() const;

	private:
		SList<EventPublisher*> mEventQueue;					/**< The queue of Events */
		std::vector<EventPublisher*> mExpiredEvents;		/**< The list of expired events */
		mutable std::mutex mMutex;							/**< The mutex used to lock the EventQueue. */
	};
}
