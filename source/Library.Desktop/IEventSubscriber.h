#pragma once

namespace Library
{
	class EventPublisher;

	/**
	 * An EventSubscriber is an abstract base class intentded to be used as an interface
	 * for other Subscriber classes. All EvenSubscribers should implement how to handle 
	 * receiving events.
	 */
	class IEventSubscriber
	{
	public:
		/**
		 * Default constructor.
		 */
		IEventSubscriber() = default;

		/**
		 * Default deconstructor.
		 */
		virtual ~IEventSubscriber() = default;

		/**
		 * handles a message being received.
		 *
		 * @param publisher the address of the EventPublisher that sent the message
		 */
		virtual void Notify(const EventPublisher& publisher) = 0;
	};
}
