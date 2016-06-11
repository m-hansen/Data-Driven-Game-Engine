#pragma once

#include <mutex>
#include "EventPublisher.h"
#include "Vector.h"

namespace Library
{
	class IEventSubscriber;

	/**
	 * An Event represents the message payload that can be sent immediately or queued for future delivery.
	 */
	template<typename MessageT>
	class Event final : public EventPublisher
	{
		RTTI_DECLARATIONS(Event<MessageT>, EventPublisher)

	public:
		/**
		 * Constructs an Event.
		 *
		 * @param messageObject the message contained within an event
		 */
		explicit Event(const MessageT& messageObject);

		// Prevent events from being copied or moved
		Event(const Event& rhs) = delete;
		Event(Event&& rhs) = delete;
		Event& operator=(const Event& rhs) = delete;

		/**
		 * Destructor.
		 */
		virtual ~Event() = default;

		/**
		 * Given the address of an EventSubscriber, add it to the list of subscribers for this event type.
		 *
		 * @param subscriber the subscriber to add to the subscription list
		 */
		static void Subscribe(IEventSubscriber& subscriber);

		/**
		 * Given the address of an EventSubscriber, remove it from the list of subscribers for this event type.
		 *
		 * @param subscriber the subscriber to remove from the subscription list
		 */
		static void Unsubscribe(IEventSubscriber& subscriber);

		/**
		 * Unsubscribe all subscribers to this event type.
		 */
		static void UnsubscribeAll();

		/**
		 * Returns the message object.
		 *
		 * @return the message object
		 */
		const MessageT& Message() const;

	private:
		MessageT mMessage;								/**< Message payload */
		static Vector<IEventSubscriber*> mSubscribers;	/**< The list of subscribers */
		static std::mutex mMutex;
	};
}

#include "Event.inl"
