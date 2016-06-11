#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(EventTest)
	{
	public:

		TEST_METHOD(EventTestConstructor)
		{
			FooSubscriber fooSubscriber;
			Assert::IsFalse(fooSubscriber.WasMessageReceived);

			Vector<IEventSubscriber*> subscribers;
			subscribers.PushBack(&fooSubscriber);
			Assert::IsTrue(subscribers.Find(&fooSubscriber) != subscribers.end());
			EventPublisher publisher(subscribers);

			Foo f;
			Event<Foo> fooEvent(f);
			Assert::AreEqual(f.Data(), fooEvent.Message().Data());

			EventQueue eventQueue;
			Assert::AreEqual(0U, eventQueue.Size());
		}

		TEST_METHOD(EventTestRtti)
		{
			Vector<IEventSubscriber*> subscribers;
			EventPublisher publisher(subscribers);
			Assert::IsTrue(publisher.Is("EventPublisher"));
			Assert::IsNotNull(publisher.As<EventPublisher>());
			Assert::IsTrue(publisher.TypeName() == "EventPublisher");

			Foo f;
			Event<Foo> fooEvent(f);
			Assert::IsTrue(fooEvent.Is(fooEvent.TypeIdInstance()));
			Assert::IsNotNull(fooEvent.As<Event<Foo>>());
			Assert::IsTrue(fooEvent.TypeName() == "Event<MessageT>");
		}

		TEST_METHOD(EventTestEventSubscriberNotify)
		{
			Vector<IEventSubscriber*> subscribers;
			EventPublisher publisher(subscribers);

			FooSubscriber fooSubscriber;
			Assert::IsFalse(fooSubscriber.WasMessageReceived);
			fooSubscriber.Notify(publisher);
			Assert::IsTrue(fooSubscriber.WasMessageReceived);
		}

#pragma region EventQueue Tests
		TEST_METHOD(EventTestEventQueueEnqueue)
		{
			Library::WorldState worldState;
			Vector<IEventSubscriber*> subscribers;
			EventPublisher publisher(subscribers);
			EventPublisher publisher2(subscribers);

			EventQueue queue;
			queue.Enqueue(publisher, worldState.GetGameTime(), Milliseconds(1));
			Assert::IsFalse(queue.IsEmpty());
			queue.Enqueue(publisher2, worldState.GetGameTime(), Milliseconds(0));
			Assert::IsFalse(queue.IsEmpty());
		}

		TEST_METHOD(EventTestEventQueueSend)
		{
			Library::WorldState worldState;
			Vector<IEventSubscriber*> subscribers;
			EventPublisher publisher(subscribers);

			EventQueue queue;
			Assert::IsTrue(queue.IsEmpty());
			queue.Send(publisher);
			Assert::IsTrue(queue.IsEmpty());
		}

		TEST_METHOD(EventTestEventQueueUpdate)
		{
			Library::WorldState worldState;
			Vector<IEventSubscriber*> subscribers;
			EventPublisher publisher(subscribers);
			EventPublisher publisher2(subscribers);

			EventQueue queue;
			queue.Enqueue(publisher, worldState.GetGameTime(), Milliseconds(1));
			Assert::IsFalse(queue.IsEmpty());
			queue.Send(publisher);
			queue.Update(worldState.GetGameTime());
			
			queue.Enqueue(publisher2, worldState.GetGameTime(), Milliseconds(9999999));
			queue.Update(worldState.GetGameTime());
		}

		TEST_METHOD(EventTestEventQueueClear)
		{
			Library::WorldState worldState;
			Vector<IEventSubscriber*> subscribers;
			EventPublisher publisher(subscribers);

			EventQueue queue;
			Assert::AreEqual(0U, queue.Size());
			Assert::IsTrue(queue.IsEmpty());
			queue.Enqueue(publisher, worldState.GetGameTime(), Milliseconds(1000));
			Assert::AreEqual(1U, queue.Size());
			Assert::IsFalse(queue.IsEmpty());
			queue.Clear();
			Assert::AreEqual(0U, queue.Size());
			Assert::IsTrue(queue.IsEmpty());
		}
#pragma endregion

#pragma region Event Tests
		TEST_METHOD(EventTestEventSubscribe)
		{
			FooSubscriber fooSubscriber;
			Foo f;
			Event<Foo> fooEvent(f);
			fooEvent.Subscribe(fooSubscriber);
		}

		TEST_METHOD(EventTestEventUnsubscribe)
		{
			FooSubscriber fooSubscriber;
			Foo f;
			Event<Foo> fooEvent(f);
			fooEvent.Subscribe(fooSubscriber);
			fooEvent.Unsubscribe(fooSubscriber);
		}

		TEST_METHOD(EventTestEventUnsubscribeAll)
		{
			FooSubscriber fooSubscriber;
			FooSubscriber fooSubscriber2;

			Foo f;
			Event<Foo> fooEvent(f);
			fooEvent.Subscribe(fooSubscriber);
			fooEvent.Subscribe(fooSubscriber2);
			fooEvent.UnsubscribeAll();
		}

		TEST_METHOD(EventTestEventMessage)
		{
			Foo f;
			Event<Foo> fooEvent(f);
			Assert::IsTrue(f.Data() == fooEvent.Message().Data());
		}
#pragma endregion

#pragma region EventPublisher Tests
		TEST_METHOD(EventTestEventPublisherDelay)
		{
			Library::WorldState worldState;
			Vector<IEventSubscriber*> subscribers;
			EventPublisher publisher(subscribers);

			EventQueue queue;
			queue.Enqueue(publisher, worldState.GetGameTime(), Milliseconds(1000));
			Assert::IsFalse(queue.IsEmpty());

			Assert::IsTrue(publisher.Delay() == Milliseconds(1000));
		}

		TEST_METHOD(EventTestEventPublisherIsExpired)
		{
			Library::WorldState worldState;
			Vector<IEventSubscriber*> subscribers;
			EventPublisher publisher(subscribers);
			Assert::IsTrue(publisher.IsExpired(worldState.GetGameTime().CurrentTime()));
			publisher.SetTime(worldState.GetGameTime().CurrentTime(), Milliseconds(99999999999));
			Assert::IsFalse(publisher.IsExpired(worldState.GetGameTime().CurrentTime()));
		}

		TEST_METHOD(EventTestEventPublisherDeliver)
		{
			Library::WorldState worldState;
			Vector<IEventSubscriber*> subscribers;
			FooSubscriber f;
			subscribers.PushBack(&f);
			EventPublisher publisher(subscribers);
			Assert::IsFalse(f.WasMessageReceived);
			publisher.Deliver();
			Assert::IsTrue(f.WasMessageReceived);
		}

		TEST_METHOD(EventTestEventPublisherTimeEnqueued)
		{
			Library::WorldState worldState;
			Vector<IEventSubscriber*> subscribers;
			EventPublisher publisher(subscribers);
			GameTime enqueueTime = worldState.GetGameTime();

			EventQueue queue;
			queue.Enqueue(publisher, enqueueTime, Milliseconds(1000));
			Assert::IsFalse(queue.IsEmpty());

			Assert::IsTrue(publisher.TimeEnqueued() == enqueueTime.CurrentTime());
		}
#pragma endregion

		TEST_METHOD(EventTestMultithreaded)
		{
			const std::uint32_t NumberOfFooSubscribers = 500;

			World world("World");

			Foo foo;
			Event<Foo>* fooEvent = new Event<Foo>(foo);

			FooSubscriber subscriber;
			Library::WorldState worldState;
			Vector<IEventSubscriber*> subscribers;
			for (std::uint32_t i = 0; i < NumberOfFooSubscribers; ++i)
			{
				Event<Foo>::Subscribe(subscriber);
			}

			EventPublisher publisher(subscribers);
			GameTime enqueueTime = worldState.GetGameTime();

			EventQueue queue;
			for (std::uint32_t i = 0; i < 500; ++i)
			{
				queue.Enqueue(publisher, enqueueTime, Milliseconds(100));
			}
			Assert::AreEqual(500U, queue.Size());
			std::this_thread::sleep_for(static_cast<Milliseconds>(150));
			world.Update(worldState);

			Assert::IsTrue(publisher.TimeEnqueued() == enqueueTime.CurrentTime());

			delete fooEvent;
		}

	private:
#if defined(DEBUG) | defined(_DEBUG)
		static _CrtMemState sStartMemState;
#endif

	};

#if defined(DEBUG) | defined(_DEBUG)
	_CrtMemState EventTest::sStartMemState;
#endif

}
