#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(StackTest)
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

		TEST_METHOD(StackTestConstructor)
		{
			// Test primitive dasta type
			Stack<std::int32_t> intStack;
			Assert::AreEqual(0U, intStack.Size());
			Assert::ExpectException<std::exception>([&] { intStack.Top(); });

			// Test pointer
			Stack<std::int32_t*> pointerStack;
			Assert::AreEqual(0U, pointerStack.Size());
			Assert::ExpectException<std::exception>([&] { pointerStack.Top(); });

			// Test user-defined data type
			Stack<Foo> fooStack;
			Assert::AreEqual(0U, fooStack.Size());
			Assert::ExpectException<std::exception>([&] { fooStack.Top(); });
		}

		TEST_METHOD(StackTestCopy)
		{
			// Test primitive data type
			Stack<std::int32_t> existingIntStack;
			existingIntStack.Push(0);
			existingIntStack.Push(1);
			existingIntStack.Push(2);

			Stack<std::int32_t> intStack = existingIntStack;
			Assert::AreEqual(existingIntStack.Size(), intStack.Size());
			while (!intStack.IsEmpty())
			{
				Assert::AreEqual(existingIntStack.Pop(), intStack.Pop());
			}

			// Test pointer
			Stack<std::int32_t*> existingPointerStack;
			std::int32_t pointerData[] = { 0, 1, 2 };
			existingPointerStack.Push(&pointerData[0]);
			existingPointerStack.Push(&pointerData[1]);
			existingPointerStack.Push(&pointerData[2]);

			Stack<std::int32_t*> pointerStack = existingPointerStack;
			Assert::AreEqual(existingPointerStack.Size(), pointerStack.Size());
			while (!pointerStack.IsEmpty())
			{
				Assert::AreEqual(existingPointerStack.Pop(), pointerStack.Pop());
			}

			// Test user-defined data type
			Stack<Foo> existingFooStack;
			Foo fooData[] = { Foo(0), Foo(1), Foo(2) };
			existingFooStack.Push(fooData[0]);
			existingFooStack.Push(fooData[1]);
			existingFooStack.Push(fooData[2]);

			Stack<Foo> fooStack = existingFooStack;
			Assert::AreEqual(existingFooStack.Size(), fooStack.Size());
			while (!fooStack.IsEmpty())
			{
				Assert::IsTrue(existingFooStack.Pop() == fooStack.Pop());
			}
		}

		TEST_METHOD(StackTestPush)
		{
			// Test pushing with a primitive data type
			Stack<std::int32_t> intStack;
			intStack.Push(0);
			Assert::AreEqual(1U, intStack.Size());
			Assert::AreEqual(0, intStack.Top());
			intStack.Push(1);
			Assert::AreEqual(2U, intStack.Size());
			Assert::AreEqual(1, intStack.Top());
			intStack.Push(2);
			Assert::AreEqual(3U, intStack.Size());
			Assert::AreEqual(2, intStack.Top());

			// Test pushing with a pointer
			Stack<std::int32_t*> pointerStack;
			std::int32_t pointerData[] = { 0, 1, 2 };
			pointerStack.Push(&pointerData[0]);
			Assert::AreEqual(1U, pointerStack.Size());
			Assert::AreEqual(&pointerData[0], pointerStack.Top());
			pointerStack.Push(&pointerData[1]);
			Assert::AreEqual(2U, pointerStack.Size());
			Assert::AreEqual(&pointerData[1], pointerStack.Top());
			pointerStack.Push(&pointerData[2]);
			Assert::AreEqual(3U, pointerStack.Size());
			Assert::AreEqual(&pointerData[2], pointerStack.Top());

			// Test pushing with a user-defined data typepointerStack
			Stack<Foo> fooStack;
			Foo fooData[] = { Foo(0), Foo(1), Foo(2) };
			fooStack.Push(fooData[0]);
			Assert::AreEqual(1U, fooStack.Size());
			Assert::IsTrue(fooData[0] == fooStack.Top());
			fooStack.Push(fooData[1]);
			Assert::AreEqual(2U, fooStack.Size());
			Assert::IsTrue(fooData[1] == fooStack.Top());
			fooStack.Push(fooData[2]);
			Assert::AreEqual(3U, fooStack.Size());
			Assert::IsTrue(fooData[2] == fooStack.Top());
		}

		TEST_METHOD(StackTestPop)
		{
			// Test popping a primitive data type
			Stack<std::int32_t> intStack;
			intStack.Push(0);
			intStack.Push(1);
			intStack.Push(2);
			Assert::AreEqual(2, intStack.Pop());
			Assert::AreEqual(2U, intStack.Size());
			Assert::AreEqual(1, intStack.Pop());
			Assert::AreEqual(1U, intStack.Size());
			Assert::AreEqual(0, intStack.Pop());
			Assert::AreEqual(0U, intStack.Size());
			Assert::ExpectException<std::exception>([&] { intStack.Pop(); });

			// Test popping a pointer
			Stack<std::int32_t*> pointerStack;
			std::int32_t pointerData[] = { 0, 1, 2 };
			pointerStack.Push(&pointerData[0]);
			pointerStack.Push(&pointerData[1]);
			pointerStack.Push(&pointerData[2]);
			Assert::AreEqual(&pointerData[2], pointerStack.Pop());
			Assert::AreEqual(2U, pointerStack.Size());
			Assert::AreEqual(&pointerData[1], pointerStack.Pop());
			Assert::AreEqual(1U, pointerStack.Size());
			Assert::AreEqual(&pointerData[0], pointerStack.Pop());
			Assert::AreEqual(0U, pointerStack.Size());
			Assert::ExpectException<std::exception>([&] { pointerStack.Pop(); });

			// Test popping a user-defined data type
			Stack<Foo> fooStack;
			Foo fooData[] = { 0, 1, 2 };
			fooStack.Push(fooData[0]);
			fooStack.Push(fooData[1]);
			fooStack.Push(fooData[2]);
			Assert::IsTrue(fooData[2] == fooStack.Pop());
			Assert::AreEqual(2U, fooStack.Size());
			Assert::IsTrue(fooData[1] == fooStack.Pop());
			Assert::AreEqual(1U, fooStack.Size());
			Assert::IsTrue(fooData[0] == fooStack.Pop());
			Assert::AreEqual(0U, fooStack.Size());
			Assert::ExpectException<std::exception>([&] { fooStack.Pop(); });
		}

		TEST_METHOD(StackTestTop)
		{
			// Test primitive data type
			Stack<std::int32_t> intStack;
			Assert::ExpectException<std::exception>([&] { intStack.Top(); });
			intStack.Push(0);
			Assert::AreEqual(0, intStack.Top());
			intStack.Push(1);
			Assert::AreEqual(1, intStack.Top());
			intStack.Push(2);
			Assert::AreEqual(2, intStack.Top());
			intStack.Pop();
			Assert::AreEqual(1, intStack.Top());

			// Test pointer
			Stack<std::int32_t*> pointerStack;
			std::int32_t pointerData[] = { 0, 1, 2 };
			Assert::ExpectException<std::exception>([&] { pointerStack.Top(); });
			pointerStack.Push(&pointerData[0]);
			Assert::AreEqual(&pointerData[0], pointerStack.Top());
			pointerStack.Push(&pointerData[1]);
			Assert::AreEqual(&pointerData[1], pointerStack.Top());
			pointerStack.Push(&pointerData[2]);
			Assert::AreEqual(&pointerData[2], pointerStack.Top());
			pointerStack.Pop();
			Assert::AreEqual(&pointerData[1], pointerStack.Top());

			// Test user-defined data type
			Stack<Foo> fooStack;
			Foo fooData[] = { Foo(0), Foo(1), Foo(2) };
			Assert::ExpectException<std::exception>([&] { fooStack.Top(); });
			fooStack.Push(fooData[0]);
			Assert::IsTrue(fooData[0] == fooStack.Top());
			fooStack.Push(fooData[1]);
			Assert::IsTrue(fooData[1] == fooStack.Top());
			fooStack.Push(fooData[2]);
			Assert::IsTrue(fooData[2] == fooStack.Top());
			fooStack.Pop();
			Assert::IsTrue(fooData[1] == fooStack.Top());
		}

		TEST_METHOD(StackTestSize)
		{
			// Test popping a primitive data type
			Stack<std::int32_t> intStack;
			Assert::AreEqual(0U, intStack.Size());
			intStack.Push(0);
			Assert::AreEqual(1U, intStack.Size());
			intStack.Push(1);
			Assert::AreEqual(2U, intStack.Size());
			intStack.Push(2);
			Assert::AreEqual(3U, intStack.Size());
			intStack.Pop();
			Assert::AreEqual(2U, intStack.Size());
			intStack.Pop();
			Assert::AreEqual(1U, intStack.Size());
			intStack.Pop();
			Assert::AreEqual(0U, intStack.Size());

			// Test popping a pointer
			Stack<std::int32_t*> pointerStack;
			std::int32_t pointerData[] = { 0, 1, 2 };
			Assert::AreEqual(0U, pointerStack.Size());
			pointerStack.Push(&pointerData[0]);
			Assert::AreEqual(1U, pointerStack.Size());
			pointerStack.Push(&pointerData[1]);
			Assert::AreEqual(2U, pointerStack.Size());
			pointerStack.Push(&pointerData[2]);
			Assert::AreEqual(3U, pointerStack.Size());
			pointerStack.Pop();
			Assert::AreEqual(2U, pointerStack.Size());
			pointerStack.Pop();
			Assert::AreEqual(1U, pointerStack.Size());
			pointerStack.Pop();
			Assert::AreEqual(0U, pointerStack.Size());

			// Test popping a user-defined data type
			Stack<Foo> fooStack;
			Foo fooData[] = { 0, 1, 2 };
			Assert::AreEqual(0U, fooStack.Size());
			fooStack.Push(fooData[0]);
			Assert::AreEqual(1U, fooStack.Size());
			fooStack.Push(fooData[1]);
			Assert::AreEqual(2U, fooStack.Size());
			fooStack.Push(fooData[2]);
			Assert::AreEqual(3U, fooStack.Size());
			fooStack.Pop();
			Assert::AreEqual(2U, fooStack.Size());
			fooStack.Pop();
			Assert::AreEqual(1U, fooStack.Size());
			fooStack.Pop();
			Assert::AreEqual(0U, fooStack.Size());
		}

		TEST_METHOD(StackTestIsEmpty)
		{
			// Test a primitive data type
			Stack<std::int32_t> intStack;
			Assert::IsTrue(intStack.IsEmpty());
			intStack.Push(0);
			Assert::IsFalse(intStack.IsEmpty());
			intStack.Pop();
			Assert::IsTrue(intStack.IsEmpty());

			// Test a pointer
			Stack<std::int32_t*> pointerStack;
			std::int32_t pointerData[] = { 0 };
			Assert::IsTrue(pointerStack.IsEmpty());
			pointerStack.Push(&pointerData[0]);
			Assert::IsFalse(pointerStack.IsEmpty());
			pointerStack.Pop();
			Assert::IsTrue(pointerStack.IsEmpty());

			// Test a user-defined data type
			Stack<Foo> fooStack;
			Foo fooData[] = { Foo(0) };
			Assert::IsTrue(fooStack.IsEmpty());
			fooStack.Push(fooData[0]);
			Assert::IsFalse(fooStack.IsEmpty());
			fooStack.Pop();
			Assert::IsTrue(fooStack.IsEmpty());
		}

		TEST_METHOD(StackTestClear)
		{
			// Test a primitive data type
			Stack<std::int32_t> intStack;
			intStack.Clear();													// Clear an empty stack
			Assert::AreEqual(0U, intStack.Size());
			Assert::ExpectException<std::exception>([&] { intStack.Top(); });
			intStack.Push(0);
			intStack.Clear();													// Clear a stack with one element
			Assert::AreEqual(0U, intStack.Size());
			Assert::ExpectException<std::exception>([&] { intStack.Top(); });
			intStack.Push(0);
			intStack.Push(0);
			intStack.Push(0);
			intStack.Clear();													// Clear a stack with multiple elements
			Assert::AreEqual(0U, intStack.Size());
			Assert::ExpectException<std::exception>([&] { intStack.Top(); });

			// Test a pointer
			Stack<std::int32_t*> pointerStack;
			std::int32_t pointerData[] = { 0 };
			pointerStack.Clear();													// Clear an empty stack
			Assert::AreEqual(0U, pointerStack.Size());
			Assert::ExpectException<std::exception>([&] { pointerStack.Top(); });
			pointerStack.Push(&pointerData[0]);
			pointerStack.Clear();													// Clear a stack with one element
			Assert::AreEqual(0U, pointerStack.Size());
			Assert::ExpectException<std::exception>([&] { pointerStack.Top(); });
			pointerStack.Push(&pointerData[0]);
			pointerStack.Push(&pointerData[0]);
			pointerStack.Push(&pointerData[0]);
			pointerStack.Clear();													// Clear a stack with multiple elements
			Assert::AreEqual(0U, pointerStack.Size());
			Assert::ExpectException<std::exception>([&] { pointerStack.Top(); });

			// Test a user-defined data type
			Stack<Foo> fooStack;
			Foo fooData[] = { 0 };
			fooStack.Clear();													// Clear an empty stack
			Assert::AreEqual(0U, fooStack.Size());
			Assert::ExpectException<std::exception>([&] { fooStack.Top(); });
			fooStack.Push(fooData[0]);
			fooStack.Clear();													// Clear a stack with one element
			Assert::AreEqual(0U, fooStack.Size());
			Assert::ExpectException<std::exception>([&] { fooStack.Top(); });
			fooStack.Push(fooData[0]);
			fooStack.Push(fooData[0]);
			fooStack.Push(fooData[0]);
			fooStack.Clear();													// Clear a stack with multiple elements
			Assert::AreEqual(0U, fooStack.Size());
			Assert::ExpectException<std::exception>([&] { fooStack.Top(); });
		}

		private:
#if defined(DEBUG) | defined(_DEBUG)
			static _CrtMemState sStartMemState;
#endif

	};

#if defined(DEBUG) | defined(_DEBUG)
	_CrtMemState StackTest::sStartMemState;
#endif

}
