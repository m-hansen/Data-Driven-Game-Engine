#include "pch.h"
#include "FooSubscriber.h"

namespace UnitTestLibraryDesktop
{

	FooSubscriber::FooSubscriber()
		: WasMessageReceived(false)
	{
	}

	void FooSubscriber::Notify(const Library::EventPublisher& publisher)
	{
		UNREFERENCED_PARAMETER(publisher);
		WasMessageReceived = true;
	}

}
