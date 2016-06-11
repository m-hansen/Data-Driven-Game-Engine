#pragma once

#include "IEventSubscriber.h"

namespace UnitTestLibraryDesktop
{
	class Library::EventPublisher;

	class FooSubscriber final : public Library::IEventSubscriber
	{
	public:
		FooSubscriber();
		virtual ~FooSubscriber() = default;
		virtual void Notify(const Library::EventPublisher& publisher);
		bool WasMessageReceived;
	};
}
