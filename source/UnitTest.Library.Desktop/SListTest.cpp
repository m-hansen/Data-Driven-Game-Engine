#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(SListTest)
	{
	public:

#if defined(DEBUG) | defined(_DEBUG)
		TEST_METHOD_INITIALIZE(Initialize)
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
		}

		TEST_METHOD_CLEANUP(Cleanup)
		{
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
		}
#endif

		TEST_METHOD(SListTestConstructor)
		{
			// Test the default constructor with a primitive data type
			SList<std::int32_t> list;
			Assert::AreEqual(0U, list.Size());
			Assert::ExpectException<std::exception>([&] { return list.Front(); });
			Assert::ExpectException<std::exception>([&] { return list.Back(); });

			// Test the default constructor with a pointer type
			SList<std::int32_t*> listPointerType;
			Assert::AreEqual(0U, listPointerType.Size());
			Assert::ExpectException<std::exception>([&] { return listPointerType.Front(); });
			Assert::ExpectException<std::exception>([&] { return listPointerType.Back(); });

			// Test the default constructor with a user-defined data type
			SList<Foo> fooList;
			Assert::AreEqual(0U, fooList.Size());
			Assert::ExpectException<std::exception>([&] { return fooList.Front(); });
			Assert::ExpectException<std::exception>([&] { return fooList.Back(); });
		}

		TEST_METHOD(SListTestCopyConstructor)
		{
			// Test the deep copy with a primitive data type
			SList<std::int32_t> existingIntList;
			existingIntList.PushBack(0);
			existingIntList.PushBack(1);
			existingIntList.PushBack(2);

			SList<std::int32_t> newIntList = existingIntList;
			Assert::AreEqual(existingIntList.Size(), newIntList.Size());
			for (std::uint32_t i = 0; i < newIntList.Size(); i++)
			{
				Assert::AreEqual(existingIntList.Front(), newIntList.Front());
				existingIntList.PopFront();
				newIntList.PopFront();
			}

			// Test the deep copy with a pointer type
			SList<std::int32_t*> existingIntPointerList;
			std::int32_t pointerData[] = { 0, 1, 2 };
			existingIntPointerList.PushBack(&pointerData[0]);
			existingIntPointerList.PushBack(&pointerData[1]);
			existingIntPointerList.PushBack(&pointerData[2]);

			SList<std::int32_t*> newIntPointerList = existingIntPointerList;
			Assert::AreEqual(existingIntPointerList.Size(), newIntPointerList.Size());
			for (std::uint32_t i = 0; i < newIntPointerList.Size(); i++)
			{
				Assert::AreEqual(existingIntPointerList.Front(), newIntPointerList.Front());
				existingIntPointerList.PopFront();
				newIntPointerList.PopFront();
			}

			// Test the deep copy with a user-defined data type
			SList<Foo> existingFooList;
			Foo fooA(10);
			Foo fooB(20);
			Foo fooC(-80);
			existingFooList.PushBack(fooA.Data());
			existingFooList.PushBack(fooB.Data());
			existingFooList.PushBack(fooC.Data());

			SList<Foo> newFooList = existingFooList;
			Assert::AreEqual(existingFooList.Size(), newFooList.Size());
			for (std::uint32_t i = 0; i < newFooList.Size(); i++)
			{
				Assert::AreEqual(existingFooList.Front().Data(), newFooList.Front().Data());
				existingFooList.PopFront();
				newFooList.PopFront();
			}
		}

		TEST_METHOD(SListTestOperatorAssignment)
		{
			// Test the assignment operator with a primitive data type
			SList<std::int32_t> existingIntList;
			existingIntList.PushBack(0);
			existingIntList.PushBack(1);
			existingIntList.PushBack(2);

			SList<std::int32_t> newIntList;
			newIntList = existingIntList;
			Assert::AreEqual(existingIntList.Size(), newIntList.Size());
			for (std::uint32_t i = 0; i < newIntList.Size(); i++)
			{
				Assert::AreEqual(existingIntList.Front(), newIntList.Front());
				existingIntList.PopFront();
				newIntList.PopFront();
			}

			// Test the assignment operator with a pointer type
			SList<std::int32_t*> existingIntPointerList;
			std::int32_t pointerData[] = { 0, 1, 2 };
			existingIntPointerList.PushBack(&pointerData[0]);
			existingIntPointerList.PushBack(&pointerData[1]);
			existingIntPointerList.PushBack(&pointerData[2]);

			SList<std::int32_t*> newIntPointerList;
			newIntPointerList = existingIntPointerList;
			Assert::AreEqual(existingIntPointerList.Size(), newIntPointerList.Size());
			for (std::uint32_t i = 0; i < newIntPointerList.Size(); i++)
			{
				Assert::AreEqual(existingIntPointerList.Front(), newIntPointerList.Front());
				existingIntPointerList.PopFront();
				newIntPointerList.PopFront();
			}

			// Test the assignment operator with a user-defined data type
			SList<Foo> existingFooList;
			Foo fooA(10);
			Foo fooB(20);
			Foo fooC(-80);
			existingFooList.PushBack(fooA.Data());
			existingFooList.PushBack(fooB.Data());
			existingFooList.PushBack(fooC.Data());

			SList<Foo> newFooList;
			newFooList = existingFooList;
			Assert::AreEqual(existingFooList.Size(), newFooList.Size());
			for (std::uint32_t i = 0; i < newFooList.Size(); i++)
			{
				Assert::AreEqual(existingFooList.Front().Data(), newFooList.Front().Data());
				existingFooList.PopFront();
				newFooList.PopFront();
			}
		}

		TEST_METHOD(SListTestPushFront)
		{
			// Test a primitive data type (integer)
			SList<std::int32_t> list;
			list.PushFront(-1);
			Assert::AreEqual(list.Front(), list.Back());
			list.PushFront(2);
			Assert::AreEqual(2, list.Front());
			Assert::AreEqual(-1, list.Back());
			Assert::AreEqual(2U, list.Size());

			// Test a list of pointers
			SList<std::int32_t*> listOfPointers;
			const uint8_t NUM_DATA_POINTS = 3;
			std::int32_t data[NUM_DATA_POINTS] = { 0, 1, 2 };
			for (std::uint32_t i = 0; i < NUM_DATA_POINTS; i++)
			{ 
				listOfPointers.PushFront(&data[i]);
			}
			Assert::AreEqual(2, *listOfPointers.Front());
			Assert::AreEqual(0, *listOfPointers.Back());
			Assert::AreEqual(3U, listOfPointers.Size());

			// Test a user-defined type (Foo)
			SList<Foo> fooList;
			Foo fooFirst(0);
			Foo fooSecond(10);
			Foo fooThird(35);
			fooList.PushFront(fooFirst.Data());
			fooList.PushFront(fooSecond.Data());
			fooList.PushFront(fooThird.Data());
			Assert::AreEqual(fooThird.Data(), fooList.Front().Data());
			Assert::AreEqual(fooFirst.Data(), fooList.Back().Data());
			Assert::AreEqual(3U, fooList.Size());
		}

		TEST_METHOD(SListTestPopFront)
		{
			// Test primitive type
			SList<std::int32_t> list;
			list.PushBack(1);
			list.PushBack(2);
			Assert::AreEqual(1, list.Front());
			list.PopFront();
			Assert::AreEqual(list.Back(), list.Front());
			list.PopFront();
			list.PushBack(3);
			list.PushBack(4);
			Assert::AreEqual(3, list.Front());
			list.PopFront();
			list.PushBack(5);
			list.PushBack(6);
			Assert::AreEqual(4, list.Front());
			list.PopFront();
			Assert::AreEqual(2U, list.Size());
			Assert::AreEqual(5, list.Front());
			list.PopFront();
			Assert::AreEqual(6, list.Front());
			list.PopFront();
			Assert::ExpectException<std::exception>([&] { return list.PopFront(); });

			// Test pointer type
			SList<std::int32_t*> listPointerType;
			std::int32_t ptrData[] = { 1, 2, 3, 4, 5, 6 };
			listPointerType.PushBack(&ptrData[0]);
			listPointerType.PushBack(&ptrData[1]);
			Assert::AreEqual(ptrData[0], *listPointerType.Front());
			listPointerType.PopFront();
			Assert::AreEqual(ptrData[1], *listPointerType.Front());
			listPointerType.PopFront();
			listPointerType.PushBack(&ptrData[2]);
			listPointerType.PushBack(&ptrData[3]);
			Assert::AreEqual(ptrData[2], *listPointerType.Front());
			listPointerType.PopFront();
			listPointerType.PushBack(&ptrData[4]);
			listPointerType.PushBack(&ptrData[5]);
			Assert::AreEqual(ptrData[3], *listPointerType.Front());
			listPointerType.PopFront();
			Assert::AreEqual(2U, listPointerType.Size());
			Assert::AreEqual(ptrData[4], *listPointerType.Front());
			listPointerType.PopFront();
			Assert::AreEqual(ptrData[5], *listPointerType.Front());
			listPointerType.PopFront();
			Assert::ExpectException<std::exception>([&] { return listPointerType.PopFront(); });

			// Test user-defined type
			SList<Foo> fooList;
			fooList.PushBack(1);
			fooList.PushBack(2);
			Assert::AreEqual(1, fooList.Front().Data());
			fooList.PopFront();
			Assert::AreEqual(2, fooList.Front().Data());
			fooList.PopFront();
			fooList.PushBack(3);
			fooList.PushBack(4);
			Assert::AreEqual(3, fooList.Front().Data());
			fooList.PopFront();
			fooList.PushBack(5);
			fooList.PushBack(6);
			Assert::AreEqual(4, fooList.Front().Data());
			fooList.PopFront();
			Assert::AreEqual(2U, fooList.Size());
			Assert::AreEqual(5, fooList.Front().Data());
			fooList.PopFront();
			Assert::AreEqual(6, fooList.Front().Data());
			fooList.PopFront();
			Assert::ExpectException<std::exception>([&] { return fooList.PopFront(); });
		}

		TEST_METHOD(SListTestPushBack)
		{
			// Test a primitive data type (integer)
			SList<std::int32_t> list;
			list.PushBack(1);
			Assert::AreEqual(list.Front(), list.Back());
			list.PushBack(2);
			Assert::AreEqual(1, list.Front());
			Assert::AreEqual(2, list.Back());
			Assert::AreEqual(2U, list.Size());

			// Test a list of pointers
			SList<std::int32_t*> listOfPointers;
			const std::uint32_t NUM_DATA_POINTS = 3;
			std::int32_t data[NUM_DATA_POINTS] = { 0, 1, 2 };
			for (std::uint32_t i = 0; i < NUM_DATA_POINTS; i++)
			{
				listOfPointers.PushBack(&data[i]);
			}
			Assert::AreEqual(0, *listOfPointers.Front());
			Assert::AreEqual(2, *listOfPointers.Back());
			Assert::AreEqual(3U, listOfPointers.Size());

			// Test a user-defined type (Foo)
			SList<Foo> fooList;
			Foo fooFirst(0);
			Foo fooSecond(10);
			Foo fooThird(35);
			fooList.PushBack(fooFirst.Data());
			fooList.PushBack(fooSecond.Data());
			fooList.PushBack(fooThird.Data());
			Assert::AreEqual(fooFirst.Data(), fooList.Front().Data());
			Assert::AreEqual(fooThird.Data(), fooList.Back().Data());
			Assert::AreEqual(3U, fooList.Size());
		}

		TEST_METHOD(SListTestIsEmpty)
		{
			const std::uint32_t EMPTY_LIST_SIZE = 0;

			// Test the empty list cases
			SList<std::int32_t> emptyList;
			Assert::IsTrue(emptyList.IsEmpty());
			Assert::AreEqual(EMPTY_LIST_SIZE, emptyList.Size());

			SList<std::int32_t*> emptyListOfPointerType;
			Assert::IsTrue(emptyListOfPointerType.IsEmpty());
			Assert::AreEqual(EMPTY_LIST_SIZE, emptyListOfPointerType.Size());

			SList<Foo> emptyFooList;
			Assert::IsTrue(emptyFooList.IsEmpty());
			Assert::AreEqual(EMPTY_LIST_SIZE, emptyFooList.Size());

			// Test the populated list cases
			SList<std::int32_t> populatedList;
			populatedList.PushBack(0);
			Assert::AreNotEqual(EMPTY_LIST_SIZE, populatedList.Size());

			SList<std::int32_t*> populatedListOfPointers;
			populatedListOfPointers.PushBack(0);
			Assert::AreNotEqual(EMPTY_LIST_SIZE, populatedListOfPointers.Size());

			SList<Foo> populatedFooList;
			populatedFooList.PushBack(0);
			Assert::AreNotEqual(EMPTY_LIST_SIZE, populatedFooList.Size());

			// Test against a growing and shrinking list of integers
			SList<std::int32_t> dynamicList;
			dynamicList.PushBack(0);
			dynamicList.PopFront();
			Assert::IsTrue(dynamicList.IsEmpty());
			Assert::AreEqual(EMPTY_LIST_SIZE, dynamicList.Size());
			dynamicList.PushBack(0);
			Assert::AreNotEqual(EMPTY_LIST_SIZE, dynamicList.Size());
		}

		TEST_METHOD(SListTestFront)
		{
			std::int32_t dataPointA = -10;
			std::int32_t dataPointB = 20;

			// Test primitive type
			SList<std::int32_t> list;
			list.PushFront(dataPointA);
			Assert::AreEqual(dataPointA, list.Front());
			list.PushFront(dataPointB);
			Assert::AreEqual(dataPointB, list.Front());
			list.PopFront();
			Assert::AreEqual(dataPointA, list.Front());
			list.PopFront();
			Assert::ExpectException<std::exception>([&] { return list.Front(); });

			// Test pointer type
			SList<std::int32_t*> listOfPointers;
			listOfPointers.PushFront(&dataPointA);
			Assert::AreEqual(dataPointA, *listOfPointers.Front());
			listOfPointers.PushFront(&dataPointB);
			Assert::AreEqual(dataPointB, *listOfPointers.Front());
			listOfPointers.PopFront();
			Assert::AreEqual(dataPointA, *listOfPointers.Front());
			listOfPointers.PopFront();
			Assert::ExpectException<std::exception>([&] { return listOfPointers.Front(); });

			// Test user-defined type
			SList<Foo> fooList;
			fooList.PushFront(dataPointA);
			Assert::AreEqual(dataPointA, fooList.Front().Data());
			fooList.PushFront(dataPointB);
			Assert::AreEqual(dataPointB, fooList.Front().Data());
			fooList.PopFront();
			Assert::AreEqual(dataPointA, fooList.Front().Data());
			fooList.PopFront();
			Assert::ExpectException<std::exception>([&] { return fooList.Front(); });
		}

		TEST_METHOD(SListTestBack)
		{
			std::int32_t dataPointA = -10;
			std::int32_t dataPointB = 20;

			// Test primitive type
			SList<std::int32_t> list;
			list.PushBack(dataPointA);
			Assert::AreEqual(dataPointA, list.Back());
			list.PushBack(dataPointB);
			Assert::AreEqual(dataPointB, list.Back());
			list.PopFront();
			Assert::AreEqual(dataPointB, list.Back());
			list.PopFront();
			Assert::ExpectException<std::exception>([&] { return list.Back(); });

			// Test pointer type
			SList<std::int32_t*> listOfPointers;
			listOfPointers.PushBack(&dataPointA);
			Assert::AreEqual(dataPointA, *listOfPointers.Back());
			listOfPointers.PushBack(&dataPointB);
			Assert::AreEqual(dataPointB, *listOfPointers.Back());
			listOfPointers.PopFront();
			Assert::AreEqual(dataPointB, *listOfPointers.Back());
			listOfPointers.PopFront();
			Assert::ExpectException<std::exception>([&] { return listOfPointers.Back(); });

			// Test user-defined type
			SList<Foo> fooList;
			fooList.PushBack(dataPointA);
			Assert::AreEqual(dataPointA, fooList.Back().Data());
			fooList.PushBack(dataPointB);
			Assert::AreEqual(dataPointB, fooList.Back().Data());
			fooList.PopFront();
			Assert::AreEqual(dataPointB, fooList.Back().Data());
			fooList.PopFront();
			Assert::ExpectException<std::exception>([&] { return fooList.Back(); });
		}

		TEST_METHOD(SListTestClear)
		{
			// Test the default constructor with a primitive data type
			SList<std::int32_t> list;

			// Check that the list is empty
			Assert::AreEqual(0U, list.Size());
			Assert::ExpectException<std::exception>([&] { return list.Front(); });
			Assert::ExpectException<std::exception>([&] { return list.Back(); });

			// Check that the list contains at least one node
			list.PushBack(0);
			Assert::AreNotEqual(0U, list.Size());

			// Clear a non-empty list
			list.Clear();
			Assert::AreEqual(0U, list.Size());
			Assert::ExpectException<std::exception>([&] { return list.Front(); });
			Assert::ExpectException<std::exception>([&] { return list.Back(); });

			// Clear an empty list
			list.Clear();
			Assert::AreEqual(0U, list.Size());
			Assert::ExpectException<std::exception>([&] { return list.Front(); });
			Assert::ExpectException<std::exception>([&] { return list.Back(); });

			// Test the default constructor with a pointer type
			SList<std::int32_t*> listPointerType;

			// Check that the list is empty
			Assert::AreEqual(0U, listPointerType.Size());
			Assert::ExpectException<std::exception>([&] { return listPointerType.Front(); });
			Assert::ExpectException<std::exception>([&] { return listPointerType.Back(); });

			// Check that the list contains at least one node
			listPointerType.PushBack(0);
			Assert::AreNotEqual(0U, listPointerType.Size());

			// Clear a non-empty list
			listPointerType.Clear();
			Assert::AreEqual(0U, listPointerType.Size());
			Assert::ExpectException<std::exception>([&] { return listPointerType.Front(); });
			Assert::ExpectException<std::exception>([&] { return listPointerType.Back(); });

			// Clear an empty list
			listPointerType.Clear();
			Assert::AreEqual(0U, listPointerType.Size());
			Assert::ExpectException<std::exception>([&] { return listPointerType.Front(); });
			Assert::ExpectException<std::exception>([&] { return listPointerType.Back(); });

			// Test the default constructor with a user-defined data type
			SList<Foo> fooList;

			// Check that the list is empty
			Assert::AreEqual(0U, fooList.Size());
			Assert::ExpectException<std::exception>([&] { return fooList.Front(); });
			Assert::ExpectException<std::exception>([&] { return fooList.Back(); });

			// Check that the list contains at least one node
			fooList.PushBack(0);
			Assert::AreNotEqual(0U, fooList.Size());

			// Clear a non-empty list
			fooList.Clear();
			Assert::AreEqual(0U, fooList.Size());
			Assert::ExpectException<std::exception>([&] { return fooList.Front(); });
			Assert::ExpectException<std::exception>([&] { return fooList.Back(); });

			// Clear an empty list
			fooList.Clear();
			Assert::AreEqual(0U, fooList.Size());
			Assert::ExpectException<std::exception>([&] { return fooList.Front(); });
			Assert::ExpectException<std::exception>([&] { return fooList.Back(); });
		}

		TEST_METHOD(SListTestSize)
		{
			// Test primitive type
			SList<std::int32_t> intList;
			Assert::AreEqual(0U, intList.Size());
			intList.PushBack(0);
			Assert::AreEqual(1U, intList.Size());
			intList.PopFront();
			Assert::AreEqual(0U, intList.Size());
			intList.PushBack(0);
			Assert::AreEqual(1U, intList.Size());

			// Test pointer type
			SList<std::int32_t*> pointerList;
			Assert::AreEqual(0U, pointerList.Size());
			pointerList.PushBack(0);
			Assert::AreEqual(1U, pointerList.Size());
			pointerList.PopFront();
			Assert::AreEqual(0U, pointerList.Size());
			pointerList.PushBack(0);
			Assert::AreEqual(1U, pointerList.Size());

			// Test user-defined type
			SList<Foo> fooList;
			Assert::AreEqual(0U, fooList.Size());
			Foo foo(0);
			fooList.PushBack(foo);
			Assert::AreEqual(1U, fooList.Size());
			fooList.PopFront();
			Assert::AreEqual(0U, fooList.Size());
			fooList.PushBack(foo);
			Assert::AreEqual(1U, fooList.Size());
		}

		TEST_METHOD(SListTestBegin)
		{
			SList<std::int32_t> intList;
			Assert::ExpectException<std::exception>([&] { *intList.begin(); });
			intList.PushBack(0);
			intList.PushBack(1);
			intList.PushBack(-2);
			SList<std::int32_t>::Iterator expectedEndIntIter(&intList);
			Assert::AreEqual(0, *intList.begin());

			SList<std::int32_t*> intPointerList;
			std::int32_t pointerData[] = { 0, 1, -2 };
			Assert::ExpectException<std::exception>([&] { *intPointerList.begin(); });
			intPointerList.PushBack(&pointerData[0]);
			intPointerList.PushBack(&pointerData[1]);
			intPointerList.PushBack(&pointerData[2]);
			SList<std::int32_t*>::Iterator expectedEndPtrIter(&intPointerList);
			Assert::AreEqual(&pointerData[0], *intPointerList.begin());

			SList<Foo> fooList;
			Foo fooData[] = { Foo(0), Foo(-1), Foo(-2) };
			Assert::ExpectException<std::exception>([&] { *fooList.begin(); });
			fooList.PushBack(fooData[0]);
			fooList.PushBack(fooData[1]);
			fooList.PushBack(fooData[2]);
			SList<Foo>::Iterator expectedEndFooIter(&fooList);
			Assert::IsTrue(fooData[0] == *fooList.begin());
		}

		TEST_METHOD(SListTestEnd)
		{
			SList<std::int32_t> intList;
			Assert::ExpectException<std::exception>([&] { *intList.end(); });
			intList.PushBack(0);
			intList.PushBack(1);
			intList.PushBack(-2);
			SList<std::int32_t>::Iterator expectedEndIntIter(&intList);

			SList<std::int32_t*> intPointerList;
			std::int32_t pointerData[] = { 0, 1, -2 };
			Assert::ExpectException<std::exception>([&] { *intPointerList.end(); });
			intPointerList.PushBack(&pointerData[0]);
			intPointerList.PushBack(&pointerData[1]);
			intPointerList.PushBack(&pointerData[2]);
			SList<std::int32_t*>::Iterator expectedEndPtrIter(&intPointerList);

			SList<Foo> fooList;
			Foo fooData[] = { Foo(0), Foo(-1), Foo(-2) };
			Assert::ExpectException<std::exception>([&] { *fooList.end(); });
			fooList.PushBack(fooData[0]);
			fooList.PushBack(fooData[1]);
			fooList.PushBack(fooData[2]);
			SList<Foo>::Iterator expectedEndFooIter(&fooList);
		}

		TEST_METHOD(SListTestInsertAfter)
		{
			// Test primitive data type
			SList<std::int32_t> intList;
			SList<std::int32_t>::Iterator intIterator = intList.begin();
			// Insert into an empty list
			intList.InsertAfter(-1, intIterator);
			Assert::AreEqual(-1, intList.Front());
			intList.PushBack(0);
			intList.PushBack(1);
			intList.PushBack(2);
			// Insert between the front and back of the list
			intList.InsertAfter(15, intList.begin());
			Assert::AreEqual(-1, intList.Front());
			intList.PopFront();
			Assert::AreEqual(15, intList.Front());
			intList.PopFront();
			Assert::AreEqual(0, intList.Front());
			intList.PopFront();
			Assert::AreEqual(1, intList.Front());
			Assert::AreEqual(2, intList.Back());

			// Test pointer data type
			SList<std::int32_t*> intPointerList;
			SList<std::int32_t*>::Iterator intPointerIterator = intPointerList.begin();
			std::int32_t pointerData[] = { -1, 0, 1, 2, 15 };
			// Insert into an empty list
			intPointerList.InsertAfter(&pointerData[0], intPointerIterator);
			Assert::AreEqual(&pointerData[0], intPointerList.Front());
			intPointerList.PushBack(&pointerData[1]);
			intPointerList.PushBack(&pointerData[2]);
			intPointerList.PushBack(&pointerData[3]);
			// Insert between the front and back of the list
			intPointerList.InsertAfter(&pointerData[4], intPointerList.begin());
			Assert::AreEqual(&pointerData[0], intPointerList.Front());
			intPointerList.PopFront();
			Assert::AreEqual(&pointerData[4], intPointerList.Front());
			intPointerList.PopFront();
			Assert::AreEqual(&pointerData[1], intPointerList.Front());
			intPointerList.PopFront();
			Assert::AreEqual(&pointerData[2], intPointerList.Front());
			Assert::AreEqual(&pointerData[3], intPointerList.Back());

			// Test user-defined data type
			SList<Foo> fooList;
			SList<Foo>::Iterator fooIterator = fooList.begin();
			Foo fooData[] = { Foo(-1), Foo(0), Foo(1), Foo(2), Foo(15) };
			// Insert into an empty list
			fooList.InsertAfter(fooData[0], fooIterator);
			Assert::IsTrue(fooData[0] == fooList.Front());
			fooList.PushBack(fooData[1]);
			fooList.PushBack(fooData[2]);
			fooList.PushBack(fooData[3]);
			// Insert between the front and back of the list
			fooList.InsertAfter(fooData[4], fooList.begin());
			Assert::IsTrue(fooData[0] == fooList.Front());
			fooList.PopFront();
			Assert::IsTrue(fooData[4] == fooList.Front());
			fooList.PopFront();
			Assert::IsTrue(fooData[1] == fooList.Front());
			fooList.PopFront();
			Assert::IsTrue(fooData[2] == fooList.Front());
			Assert::IsTrue(fooData[3] == fooList.Back());
		}

		TEST_METHOD(SListTestFind)
		{
			// Test find with integers
			SList<std::int32_t> intList;

			// Search an empty list
			Assert::ExpectException<std::exception>([&] { *intList.Find(0); });

			// Search with duplicates
			intList.PushBack(0);
			intList.PushBack(1);
			intList.PushBack(2);
			intList.PushBack(1);
			Assert::AreEqual(1, *intList.Find(1));

			// Search for non-existent value
			Assert::ExpectException<std::exception>([&] { *intList.Find(-1); });

			// Test find with pointers
			SList<std::int32_t*> intPointerList;
			std::int32_t pointerData[] = { 0, 1, 2, 1, -1 };

			// Search an empty list
			Assert::ExpectException<std::exception>([&] { *intPointerList.Find(&pointerData[0]); });

			// Search with duplicates
			intPointerList.PushBack(&pointerData[0]);
			intPointerList.PushBack(&pointerData[1]);
			intPointerList.PushBack(&pointerData[2]);
			intPointerList.PushBack(&pointerData[3]);
			Assert::AreEqual(&pointerData[1], *intPointerList.Find(&pointerData[1]));

			// Search for non-existent value
			Assert::ExpectException<std::exception>([&] { *intPointerList.Find(&pointerData[4]); });

			// Test find with user-defined data type
			SList<Foo> fooList;
			Foo fooData[] = { Foo(0), Foo(1), Foo(2), Foo(1), Foo(-1) };

			// Search an empty list
			Assert::ExpectException<std::exception>([&] { *fooList.Find(fooData[0]); });

			// Search with duplicates
			fooList.PushBack(fooData[0]);
			fooList.PushBack(fooData[1]);
			fooList.PushBack(fooData[2]);
			fooList.PushBack(fooData[3]);
			Assert::IsTrue(fooData[1] == *fooList.Find(fooData[1]));

			// Search for non-existent value
			Assert::ExpectException<std::exception>([&] { *fooList.Find(fooData[4]); });
		}

		TEST_METHOD(SListTestRemove)
		{
			// Test primitive data type
			SList<std::int32_t> intList;
			intList.PushBack(-1);
			intList.PushBack(0);
			intList.PushBack(1);
			// Remove from the front of the list
			intList.Remove(-1);
			Assert::AreEqual(0, intList.Front());
			Assert::AreEqual(1, intList.Back());
			intList.PushFront(-1);
			// Remove from the middle of the list
			intList.Remove(0);
			Assert::AreEqual(-1, intList.Front());
			Assert::AreEqual(1, intList.Back());
			intList.InsertAfter(0, intList.begin());
			// Remove from the back of the list
			intList.Remove(1);
			Assert::AreEqual(-1, intList.Front());
			Assert::AreEqual(0, intList.Back());
			// Attempt to remove non-existent data
			intList.Remove(12345);
			Assert::AreEqual(-1, intList.Front());
			Assert::AreEqual(0, intList.Back());
			Assert::AreEqual(2U, intList.Size());

			// Test pointer data type
			SList<std::int32_t*> intPointerList;
			std::int32_t pointerData[] = { -1, 0, 1, 12345 };
			intPointerList.PushBack(&pointerData[0]);
			intPointerList.PushBack(&pointerData[1]);
			intPointerList.PushBack(&pointerData[2]);
			// Remove from the front of the list
			intPointerList.Remove(&pointerData[0]);
			Assert::AreEqual(&pointerData[1], intPointerList.Front());
			Assert::AreEqual(&pointerData[2], intPointerList.Back());
			intPointerList.PushFront(&pointerData[0]);
			// Remove from the middle of the list
			intPointerList.Remove(&pointerData[1]);
			Assert::AreEqual(&pointerData[0], intPointerList.Front());
			Assert::AreEqual(&pointerData[2], intPointerList.Back());
			intPointerList.InsertAfter(&pointerData[1], intPointerList.begin());
			// Remove from the back of the list
			intPointerList.Remove(&pointerData[2]);
			Assert::AreEqual(&pointerData[0], intPointerList.Front());
			Assert::AreEqual(&pointerData[1], intPointerList.Back());
			// Attempt to remove non-existent data
			intPointerList.Remove(&pointerData[3]);
			Assert::AreEqual(&pointerData[0], intPointerList.Front());
			Assert::AreEqual(&pointerData[1], intPointerList.Back());
			Assert::AreEqual(2U, intPointerList.Size());

			// Test user-defined data type
			SList<Foo> fooList;
			Foo fooData[] = { Foo(-1), Foo(0), Foo(1), Foo(12345) };
			fooList.PushBack(fooData[0]);
			fooList.PushBack(fooData[1]);
			fooList.PushBack(fooData[2]);
			// Remove from the front of the list
			fooList.Remove(fooData[0]);
			Assert::IsTrue(fooData[1] == fooList.Front());
			Assert::IsTrue(fooData[2] == fooList.Back());
			fooList.PushFront(fooData[0]);
			// Remove from the middle of the list
			fooList.Remove(fooData[1]);
			Assert::IsTrue(fooData[0] == fooList.Front());
			Assert::IsTrue(fooData[2] == fooList.Back());
			fooList.InsertAfter(fooData[1], fooList.begin());
			// Remove from the back of the list
			fooList.Remove(fooData[2]);
			Assert::IsTrue(fooData[0] == fooList.Front());
			Assert::IsTrue(fooData[1] == fooList.Back());
			// Attempt to remove non-existent data
			fooList.Remove(fooData[3]);
			Assert::IsTrue(fooData[0] == fooList.Front());
			Assert::IsTrue(fooData[1] == fooList.Back());
			Assert::AreEqual(2U, fooList.Size());
		}

		private:
#if defined(DEBUG) | defined(_DEBUG)
			static _CrtMemState sStartMemState;
#endif

	};

#if defined(DEBUG) | defined(_DEBUG)
	_CrtMemState SListTest::sStartMemState;
#endif

}