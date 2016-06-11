#include "pch.h"

namespace UnitTestLibraryDesktop
{

	Foo::Foo(const int32_t data) :
		mData(data), mMoreData(new std::int32_t())
	{
	}

	Foo::Foo(const Foo& rhs) :
		mData(0), mMoreData(nullptr)
	{
		operator=(rhs);
	}

	Foo& Foo::operator=(const Foo& rhs)
	{
		if (this != &rhs)
		{
			delete mMoreData;

			mData = rhs.mData;
			mMoreData = new int(*rhs.mMoreData);
		}

		return *this;
	}

	bool Foo::operator==(const Foo& other) const
	{
		return (mData == other.Data() && *mMoreData == *other.mMoreData);
	}

	bool Foo::operator!=(const Foo& other) const
	{
		return !(operator==(other));
	}

	Foo::~Foo()
	{
		delete mMoreData;
		mMoreData = nullptr;
	}

	int32_t Foo::Data() const
	{
		return mData;
	}

}
