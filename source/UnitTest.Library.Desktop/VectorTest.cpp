#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(VectorTest)
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

		TEST_METHOD(VectorTestConstructor)
		{
			// Test the default constructor with a primitive data type
			Vector<std::int32_t> intVector;
			Assert::AreEqual(0U, intVector.Size());
			Assert::ExpectException<std::exception>([&] { return intVector.Front(); });
			Assert::ExpectException<std::exception>([&] { return intVector.Back(); });

			// Test the default constructor with a pointer
			Vector<std::int32_t*> pointerVector;
			Assert::AreEqual(0U, pointerVector.Size());
			Assert::ExpectException<std::exception>([&] { return pointerVector.Front(); });
			Assert::ExpectException<std::exception>([&] { return pointerVector.Back(); });

			// Test the default constructor with a user-defined data type
			Vector<Foo> fooVector;
			Assert::AreEqual(0U, fooVector.Size());
			Assert::ExpectException<std::exception>([&] { return fooVector.Front(); });
			Assert::ExpectException<std::exception>([&] { return fooVector.Back(); });
		}

		TEST_METHOD(VectorTestCopyConstructor)
		{
			// Test primitive data type
			Vector<std::int32_t> existingIntVector;
			existingIntVector.PushBack(10);
			existingIntVector.PushBack(20);
			existingIntVector.PushBack(30);

			Vector<std::int32_t> intVector = existingIntVector;
			Assert::AreEqual(existingIntVector.Size(), intVector.Size());
			for (std::uint32_t i = 0; i < intVector.Size(); ++i)
			{
				Assert::AreEqual(existingIntVector.At(i), intVector.At(i));
			}

			// Test pointer
			Vector<std::int32_t*> existingPointerVector;
			std::int32_t pointerData[] = { 10, 20, 30 };
			existingPointerVector.PushBack(&pointerData[0]);
			existingPointerVector.PushBack(&pointerData[1]);
			existingPointerVector.PushBack(&pointerData[2]);

			Vector<std::int32_t*> pointerVector = existingPointerVector;
			Assert::AreEqual(existingPointerVector.Size(), pointerVector.Size());
			for (std::uint32_t i = 0; i < pointerVector.Size(); ++i)
			{
				Assert::AreEqual(existingPointerVector.At(i), pointerVector.At(i));
			}

			// Test user-defined data type
			Vector<Foo> existingFooVector;
			Foo fooData[] = { Foo(10), Foo(20), Foo(30) };
			existingFooVector.PushBack(fooData[0]);
			existingFooVector.PushBack(fooData[1]);
			existingFooVector.PushBack(fooData[2]);

			Vector<Foo> fooVector = existingFooVector;
			Assert::AreEqual(existingFooVector.Size(), fooVector.Size());
			for (std::uint32_t i = 0; i < fooVector.Size(); ++i)
			{
				Assert::IsTrue(existingFooVector.At(i) == fooVector.At(i));
			}
		}

		TEST_METHOD(VectorTestAssignmentOperator)
		{
			// Test primitive data type
			Vector<std::int32_t> existingIntVector;
			existingIntVector.PushBack(10);
			existingIntVector.PushBack(20);
			existingIntVector.PushBack(30);

			Vector<std::int32_t> intVector;
			intVector = existingIntVector;
			Assert::AreEqual(existingIntVector.Size(), intVector.Size());
			for (std::uint32_t i = 0; i < intVector.Size(); ++i)
			{
				Assert::AreEqual(existingIntVector.At(i), intVector.At(i));
			}

			// Test pointer
			Vector<std::int32_t*> existingPointerVector;
			std::int32_t pointerData[] = { 10, 20, 30 };
			existingPointerVector.PushBack(&pointerData[0]);
			existingPointerVector.PushBack(&pointerData[1]);
			existingPointerVector.PushBack(&pointerData[2]);

			Vector<std::int32_t*> pointerVector;
			pointerVector = existingPointerVector;
			Assert::AreEqual(existingPointerVector.Size(), pointerVector.Size());
			for (std::uint32_t i = 0; i < pointerVector.Size(); ++i)
			{
				Assert::AreEqual(existingPointerVector.At(i), pointerVector.At(i));
			}

			// Test user-defined data type
			Vector<Foo> existingFooVector;
			Foo fooData[] = { Foo(10), Foo(20), Foo(30) };
			existingFooVector.PushBack(fooData[0]);
			existingFooVector.PushBack(fooData[1]);
			existingFooVector.PushBack(fooData[2]);

			Vector<Foo> fooVector;
			fooVector = existingFooVector;
			Assert::AreEqual(existingFooVector.Size(), fooVector.Size());
			for (std::uint32_t i = 0; i < fooVector.Size(); ++i)
			{
				Assert::IsTrue(existingFooVector.At(i) == fooVector.At(i));
			}
		}

		TEST_METHOD(VectorTestComparisonOperators)
		{
			// Test comparing primitive vectors
			Vector<std::int32_t> vectorA;
			vectorA.PushBack(20);
			vectorA.PushBack(40);
			vectorA.PushBack(60);

			Vector<std::int32_t> vectorB;
			vectorB.PushBack(20);
			vectorB.PushBack(40);
			vectorB.PushBack(60);

			Vector<std::int32_t> vectorC;
			vectorC.PushBack(20);
			vectorC.PushBack(30);
			vectorC.PushBack(60);

			Assert::IsTrue(vectorA == vectorB);
			Assert::IsTrue(vectorB == vectorA);
			Assert::IsTrue(vectorA != vectorC);
			Assert::IsTrue(vectorB != vectorC);

			// Test comparing pointer vectors
			std::int32_t firstPointerData[] = { 20, 40, 60 };
			std::int32_t secondPointerData[] = { 20, 40, 60 };

			Vector<std::int32_t*> pointerVectorA;
			pointerVectorA.PushBack(&firstPointerData[0]);
			pointerVectorA.PushBack(&firstPointerData[1]);
			pointerVectorA.PushBack(&firstPointerData[2]);

			Vector<std::int32_t*> pointerVectorB;
			pointerVectorB.PushBack(&firstPointerData[0]);
			pointerVectorB.PushBack(&firstPointerData[1]);
			pointerVectorB.PushBack(&firstPointerData[2]);

			Vector<std::int32_t*> pointerVectorC;
			pointerVectorC.PushBack(&secondPointerData[0]);
			pointerVectorC.PushBack(&secondPointerData[1]);
			pointerVectorC.PushBack(&secondPointerData[2]);

			Assert::IsTrue(pointerVectorA == pointerVectorB);
			Assert::IsTrue(pointerVectorB == pointerVectorA);
			Assert::IsTrue(pointerVectorA != pointerVectorC);
			Assert::IsTrue(pointerVectorB != pointerVectorC);

			// Test comparing user-defined vectors
			Foo fooDataA[] = { Foo(20), Foo(40), Foo(60) };
			Foo fooDataB[] = { Foo(20), Foo(40), Foo(60) };
			Foo fooDataC[] = { Foo(20), Foo(30), Foo(60) };

			Vector<Foo> fooVectorA;
			fooVectorA.PushBack(fooDataA[0]);
			fooVectorA.PushBack(fooDataA[1]);
			fooVectorA.PushBack(fooDataA[2]);

			Vector<Foo> fooVectorB;
			fooVectorB.PushBack(fooDataB[0]);
			fooVectorB.PushBack(fooDataB[1]);
			fooVectorB.PushBack(fooDataB[2]);

			Vector<Foo> fooVectorC;
			fooVectorC.PushBack(fooDataC[0]);
			fooVectorC.PushBack(fooDataC[1]);
			fooVectorC.PushBack(fooDataC[2]);

			Assert::IsTrue(fooVectorA == fooVectorB);
			Assert::IsTrue(fooVectorB == fooVectorA);
			Assert::IsTrue(fooVectorA != fooVectorC);
			Assert::IsTrue(fooVectorB != fooVectorC);
		}

		TEST_METHOD(VectorTestAt)
		{
			// Test with a primitive data type
			Vector<std::int32_t> intVector;
			intVector.PushBack(20);
			intVector.PushBack(40);
			intVector.PushBack(60);
			Assert::AreEqual(20, intVector.At(0));
			Assert::AreEqual(40, intVector.At(1));
			Assert::AreEqual(60, intVector.At(2));
			Assert::ExpectException<std::exception>([&] { return intVector.At(3); });

			// Test with a pointer
			Vector<std::int32_t*> pointerVector;
			std::int32_t pointerData[] = { 20, 40, 60 };
			pointerVector.PushBack(&pointerData[0]);
			pointerVector.PushBack(&pointerData[1]);
			pointerVector.PushBack(&pointerData[2]);
			Assert::AreEqual(&pointerData[0], pointerVector.At(0));
			Assert::AreEqual(&pointerData[1], pointerVector.At(1));
			Assert::AreEqual(&pointerData[2], pointerVector.At(2));
			Assert::ExpectException<std::exception>([&] { return pointerVector.At(3); });

			// Test with a user-defined data type
			Vector<Foo> fooVector;
			Foo fooData[] = { Foo(20), Foo(40), Foo(60) };
			fooVector.PushBack(fooData[0]);
			fooVector.PushBack(fooData[1]);
			fooVector.PushBack(fooData[2]);
			Assert::IsTrue(fooData[0] == fooVector.At(0));
			Assert::IsTrue(fooData[1] == fooVector.At(1));
			Assert::IsTrue(fooData[2] == fooVector.At(2));
			Assert::ExpectException<std::exception>([&] { return fooVector.At(3); });
		}

		TEST_METHOD(VectorTestFront)
		{
			// Test primitive data types
			Vector<std::int32_t> intVector;
			Assert::ExpectException<std::exception>([&] { return intVector.Front(); });
			intVector.PushBack(20);
			Assert::AreEqual(20, intVector.Front());
			intVector.PushBack(40);
			Assert::AreEqual(20, intVector.Front());
			intVector.PopBack();
			Assert::AreEqual(20, intVector.Front());
			intVector.PopBack();
			Assert::ExpectException<std::exception>([&] { return intVector.Front(); });

			// Test pointers
			Vector<std::int32_t*> pointerVector;
			std::int32_t pointerData[] = { 20, 40 };
			Assert::ExpectException<std::exception>([&] { return pointerVector.Front(); });
			pointerVector.PushBack(&pointerData[0]);
			Assert::AreEqual(&pointerData[0], pointerVector.Front());
			pointerVector.PushBack(&pointerData[1]);
			Assert::AreEqual(&pointerData[0], pointerVector.Front());
			pointerVector.PopBack();
			Assert::AreEqual(&pointerData[0], pointerVector.Front());
			pointerVector.PopBack();
			Assert::ExpectException<std::exception>([&] { return pointerVector.Front(); });

			// Test user-defined data types
			Vector<Foo> fooVector;
			Foo fooData[] = { Foo(20), Foo(40) };
			Assert::ExpectException<std::exception>([&] { return fooVector.Front(); });
			fooVector.PushBack(fooData[0]);
			Assert::IsTrue(fooData[0] == fooVector.Front());
			fooVector.PushBack(fooData[1]);
			Assert::IsTrue(fooData[0] == fooVector.Front());
			fooVector.PopBack();
			Assert::IsTrue(fooData[0] == fooVector.Front());
			fooVector.PopBack();
			Assert::ExpectException<std::exception>([&] { return fooVector.Front(); });
		}

		TEST_METHOD(VectorTestBack)
		{
			// Test primitive data types
			Vector<std::int32_t> intVector;
			Assert::ExpectException<std::exception>([&] { return intVector.Back(); });
			intVector.PushBack(20);
			Assert::AreEqual(20, intVector.Back());
			intVector.PushBack(40);
			Assert::AreEqual(40, intVector.Back());
			intVector.PopBack();
			Assert::AreEqual(20, intVector.Back());
			intVector.PopBack();
			Assert::ExpectException<std::exception>([&] { return intVector.Back(); });

			// Test pointers
			Vector<std::int32_t*> pointerVector;
			std::int32_t pointerData[] = { 20, 40 };
			Assert::ExpectException<std::exception>([&] { return pointerVector.Back(); });
			pointerVector.PushBack(&pointerData[0]);
			Assert::AreEqual(&pointerData[0], pointerVector.Back());
			pointerVector.PushBack(&pointerData[1]);
			Assert::AreEqual(&pointerData[1], pointerVector.Back());
			pointerVector.PopBack();
			Assert::AreEqual(&pointerData[0], pointerVector.Back());
			pointerVector.PopBack();
			Assert::ExpectException<std::exception>([&] { return pointerVector.Back(); });

			// Test user-defined data types
			Vector<Foo> fooVector;
			Foo fooData[] = { Foo(20), Foo(40) };
			Assert::ExpectException<std::exception>([&] { return fooVector.Back(); });
			fooVector.PushBack(fooData[0]);
			Assert::IsTrue(fooData[0] == fooVector.Back());
			fooVector.PushBack(fooData[1]);
			Assert::IsTrue(fooData[1] == fooVector.Back());
			fooVector.PopBack();
			Assert::IsTrue(fooData[0] == fooVector.Back());
			fooVector.PopBack();
			Assert::ExpectException<std::exception>([&] { return fooVector.Back(); });
		}

		TEST_METHOD(VectorTestPushBack)
		{
			// Test pushing a primitive data type
			Vector<std::int32_t> intVector;
			intVector.PushBack(0);							// PushBack before reserve
			Assert::AreEqual(0, intVector.Front());
			Assert::AreEqual(0, intVector.Back());
			intVector.PushBack(1);
			Assert::AreEqual(0, intVector.Front());
			Assert::AreEqual(1, intVector.Back());
			intVector.PushBack(-20);
			Assert::AreEqual(0, intVector.Front());
			Assert::AreEqual(-20, intVector.Back());
			intVector.Clear();
			intVector.Reserve(999);
			intVector.PushBack(0);							// PushBack after reserve
			Assert::AreEqual(0, intVector.Front());
			Assert::AreEqual(0, intVector.Back());
			intVector.PushBack(1);
			Assert::AreEqual(0, intVector.Front());
			Assert::AreEqual(1, intVector.Back());
			intVector.PushBack(-20);						// PushBack after reserve called, but when capacity exceeded
			Assert::AreEqual(0, intVector.Front());
			Assert::AreEqual(-20, intVector.Back());

			// Test pushing a pointer
			Vector<std::int32_t*> pointerVector;
			std::int32_t pointerData[] = { 0, 1, -20 };
			pointerVector.PushBack(&pointerData[0]);							// PushBack before reserve
			Assert::AreEqual(&pointerData[0], pointerVector.Front());
			Assert::AreEqual(&pointerData[0], pointerVector.Back());
			pointerVector.PushBack(&pointerData[1]);
			Assert::AreEqual(&pointerData[0], pointerVector.Front());
			Assert::AreEqual(&pointerData[1], pointerVector.Back());
			pointerVector.PushBack(&pointerData[2]);
			Assert::AreEqual(&pointerData[0], pointerVector.Front());
			Assert::AreEqual(&pointerData[2], pointerVector.Back());
			pointerVector.Clear();
			pointerVector.Reserve(999);
			pointerVector.PushBack(&pointerData[0]);							// PushBack after reserve
			Assert::AreEqual(&pointerData[0], pointerVector.Front());
			Assert::AreEqual(&pointerData[0], pointerVector.Back());
			pointerVector.PushBack(&pointerData[1]);
			Assert::AreEqual(&pointerData[0], pointerVector.Front());
			Assert::AreEqual(&pointerData[1], pointerVector.Back());
			pointerVector.PushBack(&pointerData[2]);							// PushBack after reserve called, but when capacity exceeded
			Assert::AreEqual(&pointerData[0], pointerVector.Front());
			Assert::AreEqual(&pointerData[2], pointerVector.Back());

			// Test pushing a user-defined data type
			Vector<Foo> fooVector;
			Foo fooData[] = { Foo(0), Foo(1), Foo(-20) };
			fooVector.PushBack(fooData[0]);							// PushBack before reserve
			Assert::IsTrue(fooData[0] == fooVector.Front());
			Assert::IsTrue(fooData[0] == fooVector.Back());
			fooVector.PushBack(fooData[1]);
			Assert::IsTrue(fooData[0] == fooVector.Front());
			Assert::IsTrue(fooData[1] == fooVector.Back());
			fooVector.PushBack(fooData[2]);
			Assert::IsTrue(fooData[0] == fooVector.Front());
			Assert::IsTrue(fooData[2] == fooVector.Back());
			fooVector.Clear();
			fooVector.Reserve(999);
			fooVector.PushBack(fooData[0]);							// PushBack after reserve
			Assert::IsTrue(fooData[0] == fooVector.Front());
			Assert::IsTrue(fooData[0] == fooVector.Back());
			fooVector.PushBack(fooData[1]);
			Assert::IsTrue(fooData[0] == fooVector.Front());
			Assert::IsTrue(fooData[1] == fooVector.Back());
			fooVector.PushBack(fooData[2]);							// PushBack after reserve called == but when capacity exceeded
			Assert::IsTrue(fooData[0] == fooVector.Front());
			Assert::IsTrue(fooData[2] == fooVector.Back());
		}

		TEST_METHOD(VectorTestPopBack)
		{
			// Test popping a primitive data type
			Vector<std::int32_t> intVector;
			intVector.PopBack();						// Attempt to pop from an empty list
			intVector.PushBack(0);
			intVector.PushBack(1);
			intVector.PopBack();						// Pop from a populated list
			Assert::AreEqual(0, intVector.Front());
			Assert::AreEqual(0, intVector.Back());
			Assert::AreEqual(1U, intVector.Size());
			intVector.PopBack();						// Pop the last item in the vector
			Assert::AreEqual(0U, intVector.Size());

			// Test popping a pointer
			Vector<std::int32_t*> pointerVector;
			std::int32_t pointerData[] = { 0, 1 };
			pointerVector.PopBack();									// Attempt to pop from an empty list
			pointerVector.PushBack(&pointerData[0]);
			pointerVector.PushBack(&pointerData[1]);
			pointerVector.PopBack();									// Pop from a populated list
			Assert::AreEqual(&pointerData[0], pointerVector.Front());
			Assert::AreEqual(&pointerData[0], pointerVector.Back());
			Assert::AreEqual(1U, pointerVector.Size());
			pointerVector.PopBack();									// Pop the last item in the vector
			Assert::AreEqual(0U, pointerVector.Size());

			// Test popping a primitive data type
			Vector<Foo> fooVector;
			Foo fooData[] = { Foo(0), Foo(1) };
			fooVector.PopBack();								// Attempt to pop from an empty list
			fooVector.PushBack(fooData[0]);
			fooVector.PushBack(fooData[1]);
			fooVector.PopBack();								// Pop from a populated list
			Assert::IsTrue(fooData[0] == fooVector.Front());
			Assert::IsTrue(fooData[0] == fooVector.Back());
			Assert::AreEqual(1U, fooVector.Size());
			fooVector.PopBack();								// Pop the last item in the vector
			Assert::AreEqual(0U, fooVector.Size());
		}

		TEST_METHOD(VectorTestClear)
		{
			// Test clearing primitive data types
			Vector<std::int32_t> intVector;
			intVector.Clear();
			Assert::AreEqual(0U, intVector.Size());
			intVector.PushBack(0);
			intVector.PushBack(0);
			intVector.PushBack(0);
			Assert::AreEqual(3U, intVector.Size());
			intVector.Clear();
			Assert::AreEqual(0U, intVector.Size());

			// Test clearing pointers
			Vector<std::int32_t*> pointerVector;
			std::int32_t pointerData[] = { 0, 1, 2 };
			pointerVector.Clear();
			Assert::AreEqual(0U, pointerVector.Size());
			pointerVector.PushBack(&pointerData[0]);
			pointerVector.PushBack(&pointerData[1]);
			pointerVector.PushBack(&pointerData[2]);
			Assert::AreEqual(3U, pointerVector.Size());
			pointerVector.Clear();
			Assert::AreEqual(0U, pointerVector.Size());

			// Test clearing user-defined data types
			Vector<Foo> fooVector;
			Foo fooData[] = { Foo(0), Foo(1), Foo(2) };
			fooVector.Clear();
			Assert::AreEqual(0U, fooVector.Size());
			fooVector.PushBack(fooData[0]);
			fooVector.PushBack(fooData[1]);
			fooVector.PushBack(fooData[2]);
			Assert::AreEqual(3U, fooVector.Size());
			fooVector.Clear();
			Assert::AreEqual(0U, fooVector.Size());
		}

		TEST_METHOD(VectorTestSize)
		{
			// Test the size of a vector with a primitive data type
			const std::uint32_t intVectorCapacity = 3;
			Vector<std::int32_t> intVector;
			Assert::AreEqual(0U, intVector.Size());						// Check the empty vector
			intVector.Reserve(intVectorCapacity);
			intVector.PushBack(0);
			Assert::AreEqual(1U, intVector.Size());						// Check a vector of one element
			intVector.PushBack(-1);
			Assert::AreEqual(2U, intVector.Size());						// Check a vector with multiple elements
			intVector.PushBack(500);
			Assert::AreEqual(intVectorCapacity, intVector.Size());		// Check a vector with elements at maximum capacity
			intVector.PopBack();
			Assert::AreEqual(2U, intVector.Size());						// Check the size decremented properly
			intVector.Clear();
			Assert::AreEqual(0U, intVector.Size());						// Check the size is zero after being cleared

			// Test the size of a vector with a pointer
			const std::uint32_t pointerVectorCapacity = 3;
			std::int32_t pointerData[] = { 0, -1, 500 };
			Vector<std::int32_t*> pointerVector;
			Assert::AreEqual(0U, pointerVector.Size());						// Check the empty vector
			pointerVector.Reserve(pointerVectorCapacity);
			pointerVector.PushBack(&pointerData[0]);
			Assert::AreEqual(1U, pointerVector.Size());						// Check a vector of one element
			pointerVector.PushBack(&pointerData[1]);
			Assert::AreEqual(2U, pointerVector.Size());						// Check a vector with multiple elements
			pointerVector.PushBack(&pointerData[500]);
			Assert::AreEqual(pointerVectorCapacity, pointerVector.Size());	// Check a vector with elements at maximum capacity
			pointerVector.PopBack();
			Assert::AreEqual(2U, pointerVector.Size());						// Check the size decremented properly
			pointerVector.Clear();
			Assert::AreEqual(0U, pointerVector.Size());						// Check the size is zero after being cleared

			// Test the size of a vector with a user-defined data type
			const std::uint32_t fooVectorCapacity = 3;
			Foo fooData[] = { Foo(0), Foo(-1), Foo(500) };
			Vector<Foo> fooVector;
			Assert::AreEqual(0U, fooVector.Size());						// Check the empty vector
			fooVector.Reserve(fooVectorCapacity);
			fooVector.PushBack(fooData[0]);
			Assert::AreEqual(1U, fooVector.Size());						// Check a vector of one element
			fooVector.PushBack(fooData[1]);
			Assert::AreEqual(2U, fooVector.Size());						// Check a vector with multiple elements
			fooVector.PushBack(fooData[2]);
			Assert::AreEqual(fooVectorCapacity, fooVector.Size());		// Check a vector with elements at maximum capacity
			fooVector.PopBack();
			Assert::AreEqual(2U, fooVector.Size());						// Check the size decremented properly
			fooVector.Clear();
			Assert::AreEqual(0U, fooVector.Size());						// Check the size is zero after being cleared
		}

		TEST_METHOD(VectorTestCapacity)
		{
			// Test primitive data type
			Vector<std::int32_t> intList;
			Assert::AreEqual(0U, intList.Capacity());
			intList.Reserve(20);
			Assert::AreEqual(20U, intList.Capacity());

			// Test pointers
			Vector<std::int32_t*> pointerList;
			Assert::AreEqual(0U, pointerList.Capacity());
			pointerList.Reserve(20);
			Assert::AreEqual(20U, pointerList.Capacity());

			// Test user-defined data type
			Vector<Foo> fooList;
			Assert::AreEqual(0U, fooList.Capacity());
			fooList.Reserve(20);
			Assert::AreEqual(20U, fooList.Capacity());
		}

		TEST_METHOD(VectorTestReserve)
		{
			// Test primitive data type
			Vector<std::int32_t> intVector;
			Assert::AreEqual(0U, intVector.Size());
			Assert::AreEqual(0U, intVector.Capacity());
			intVector.Reserve(5);
			Assert::AreEqual(0U, intVector.Size());
			Assert::AreEqual(5U, intVector.Capacity());
			intVector.Reserve(0);
			Assert::AreEqual(0U, intVector.Size());
			Assert::AreEqual(5U, intVector.Capacity());
			intVector.Reserve(999);
			Assert::AreEqual(0U, intVector.Size());
			Assert::AreEqual(999U, intVector.Capacity());

			// Test pointer
			Vector<std::int32_t*> pointerVector;
			Assert::AreEqual(0U, pointerVector.Size());
			Assert::AreEqual(0U, pointerVector.Capacity());
			pointerVector.Reserve(5);
			Assert::AreEqual(0U, pointerVector.Size());
			Assert::AreEqual(5U, pointerVector.Capacity());
			pointerVector.Reserve(0);
			Assert::AreEqual(0U, pointerVector.Size());
			Assert::AreEqual(5U, pointerVector.Capacity());
			pointerVector.Reserve(999);
			Assert::AreEqual(0U, pointerVector.Size());
			Assert::AreEqual(999U, pointerVector.Capacity());

			// Test user-defined data type
			Vector<Foo> fooVector;
			Assert::AreEqual(0U, fooVector.Size());
			Assert::AreEqual(0U, fooVector.Capacity());
			fooVector.Reserve(5);
			Assert::AreEqual(0U, fooVector.Size());
			Assert::AreEqual(5U, fooVector.Capacity());
			fooVector.Reserve(0);
			Assert::AreEqual(0U, fooVector.Size());
			Assert::AreEqual(5U, fooVector.Capacity());
			fooVector.Reserve(999);
			Assert::AreEqual(0U, fooVector.Size());
			Assert::AreEqual(999U, fooVector.Capacity());

		}

		TEST_METHOD(VectorTestFind)
		{
			// Test a primitive data type
			Vector<std::int32_t> intVector;
			intVector.PushBack(5);
			intVector.PushBack(10);
			intVector.PushBack(15);
			intVector.PushBack(20);
			Vector<std::int32_t>::Iterator intIter = intVector.begin();
			Assert::IsTrue(intIter == intVector.Find(5));
			++intIter;
			Assert::IsTrue(intIter == intVector.Find(10));
			intIter++;
			Assert::IsTrue(intIter == intVector.Find(15));
			++intIter;
			Assert::IsTrue(intIter == intVector.Find(20));

			// Test a pointer
			Vector<std::int32_t*> pointerVector;
			std::int32_t pointerData[] = { 5, 10, 15, 20 };
			pointerVector.PushBack(&pointerData[0]);
			pointerVector.PushBack(&pointerData[1]);
			pointerVector.PushBack(&pointerData[2]);
			pointerVector.PushBack(&pointerData[3]);
			Vector<std::int32_t*>::Iterator pointerIter = pointerVector.begin();
			Assert::IsTrue(pointerIter == pointerVector.Find(&pointerData[0]));
			++pointerIter;
			Assert::IsTrue(pointerIter == pointerVector.Find(&pointerData[1]));
			pointerIter++;
			Assert::IsTrue(pointerIter == pointerVector.Find(&pointerData[2]));
			++pointerIter;
			Assert::IsTrue(pointerIter == pointerVector.Find(&pointerData[3]));

			// Test a user-defined data type
			Vector<Foo> fooVector;
			Foo fooData[] = { Foo(5), Foo(10), Foo(15), Foo(20) };
			fooVector.PushBack(fooData[0]);
			fooVector.PushBack(fooData[1]);
			fooVector.PushBack(fooData[2]);
			fooVector.PushBack(fooData[3]);
			Vector<Foo>::Iterator fooIter = fooVector.begin();
			Assert::IsTrue(fooIter == fooVector.Find(fooData[0]));
			++fooIter;
			Assert::IsTrue(fooIter == fooVector.Find(fooData[1]));
			fooIter++;
			Assert::IsTrue(fooIter == fooVector.Find(fooData[2]));
			++fooIter;
			Assert::IsTrue(fooIter == fooVector.Find(fooData[3]));
		}

		TEST_METHOD(VectorTestRemove)
		{
			// Test removal of a primitive data type
			Vector<std::int32_t> intVector;
			intVector.PushBack(5);
			intVector.PushBack(10);
			intVector.PushBack(15);
			intVector.PushBack(20);
			Assert::AreEqual(4U, intVector.Size());
			Assert::AreEqual(5, intVector.Front());
			Assert::AreEqual(20, intVector.Back());
			intVector.Remove(5);						// Remove from the front of the vector
			Assert::AreEqual(3U, intVector.Size());
			Assert::AreEqual(10, intVector.Front());
			Assert::AreEqual(20, intVector.Back());
			intVector.Remove(15);						// Remove from the middle of the vector
			Assert::AreEqual(2U, intVector.Size());
			Assert::AreEqual(10, intVector.Front());
			Assert::AreEqual(20, intVector.Back());
			intVector.Remove(20);						// Remove from the back of the vector
			Assert::AreEqual(1U, intVector.Size());
			Assert::AreEqual(10, intVector.Front());
			Assert::AreEqual(10, intVector.Back());
			intVector.Remove(999);						// Attempt to remove an item that does not exist
			Assert::AreEqual(1U, intVector.Size());
			Assert::AreEqual(10, intVector.Front());
			Assert::AreEqual(10, intVector.Back());
			intVector.Remove(10);						// Remove the last item in the vector
			Assert::AreEqual(0U, intVector.Size());
			Assert::ExpectException<std::exception>([&] { return intVector.Front(); });
			Assert::ExpectException<std::exception>([&] { return intVector.Back(); });

			// Test removal of a pointer
			Vector<std::int32_t*> pointerVector;
			std::int32_t pointerData[] = { 5, 10, 15, 20, 999 };
			pointerVector.PushBack(&pointerData[0]);
			pointerVector.PushBack(&pointerData[1]);
			pointerVector.PushBack(&pointerData[2]);
			pointerVector.PushBack(&pointerData[3]);
			Assert::AreEqual(4U, pointerVector.Size());
			Assert::AreEqual(&pointerData[0], pointerVector.Front());
			Assert::AreEqual(&pointerData[3], pointerVector.Back());
			pointerVector.Remove(&pointerData[0]);						// Remove from the front of the vector
			Assert::AreEqual(3U, pointerVector.Size());
			Assert::AreEqual(&pointerData[1], pointerVector.Front());
			Assert::AreEqual(&pointerData[3], pointerVector.Back());
			pointerVector.Remove(&pointerData[2]);						// Remove from the middle of the vector
			Assert::AreEqual(2U, pointerVector.Size());
			Assert::AreEqual(&pointerData[1], pointerVector.Front());
			Assert::AreEqual(&pointerData[3], pointerVector.Back());
			pointerVector.Remove(&pointerData[3]);						// Remove from the back of the vector
			Assert::AreEqual(1U, pointerVector.Size());
			Assert::AreEqual(&pointerData[1], pointerVector.Front());
			Assert::AreEqual(&pointerData[1], pointerVector.Back());
			pointerVector.Remove(&pointerData[4]);						// Attempt to remove an item that does not exist
			Assert::AreEqual(1U, pointerVector.Size());
			Assert::AreEqual(&pointerData[1], pointerVector.Front());
			Assert::AreEqual(&pointerData[1], pointerVector.Back());
			pointerVector.Remove(&pointerData[1]);						// Remove the last item in the vector
			Assert::AreEqual(0U, pointerVector.Size());
			Assert::ExpectException<std::exception>([&] { return pointerVector.Front(); });
			Assert::ExpectException<std::exception>([&] { return pointerVector.Back(); });

			// Test removal of a user-defined data type
			Vector<Foo> fooVector;
			Foo fooData[] = { Foo(5), Foo(10), Foo(15), Foo(20), Foo(999) };
			fooVector.PushBack(fooData[0]);
			fooVector.PushBack(fooData[1]);
			fooVector.PushBack(fooData[2]);
			fooVector.PushBack(fooData[3]);
			Assert::AreEqual(4U, fooVector.Size());
			Assert::IsTrue(fooData[0] == fooVector.Front());
			Assert::IsTrue(fooData[3] == fooVector.Back());
			fooVector.Remove(fooData[0]);						// Remove from the front of the vector
			Assert::AreEqual(3U, fooVector.Size());
			Assert::IsTrue(fooData[1] == fooVector.Front());
			Assert::IsTrue(fooData[3] == fooVector.Back());
			fooVector.Remove(fooData[2]);						// Remove from the middle of the vector
			Assert::AreEqual(2U, fooVector.Size());
			Assert::IsTrue(fooData[1] == fooVector.Front());
			Assert::IsTrue(fooData[3] == fooVector.Back());
			fooVector.Remove(fooData[3]);						// Remove from the back of the vector
			Assert::AreEqual(1U, fooVector.Size());
			Assert::IsTrue(fooData[1] == fooVector.Front());
			Assert::IsTrue(fooData[1] == fooVector.Back());
			fooVector.Remove(fooData[4]);						// Attempt to remove an item that does not exist
			Assert::AreEqual(1U, fooVector.Size());
			Assert::IsTrue(fooData[1] == fooVector.Front());
			Assert::IsTrue(fooData[1] == fooVector.Back());
			fooVector.Remove(fooData[1]);						// Remove the last item in the vector
			Assert::AreEqual(0U, fooVector.Size());
			Assert::ExpectException<std::exception>([&] { return fooVector.Front(); });
			Assert::ExpectException<std::exception>([&] { return fooVector.Back(); });
		}

		TEST_METHOD(VectorTestIsEmpty)
		{
			// Test primitive data type
			Vector<std::int32_t> intVector;
			Assert::IsTrue(intVector.IsEmpty());
			intVector.PushBack(0);
			Assert::IsFalse(intVector.IsEmpty());
			intVector.PopBack();
			Assert::IsTrue(intVector.IsEmpty());

			// Test pointer
			Vector<std::int32_t*> pointerVector;
			std::int32_t pointerData[] = { 0 };
			Assert::IsTrue(pointerVector.IsEmpty());
			pointerVector.PushBack(&pointerData[0]);
			Assert::IsFalse(pointerVector.IsEmpty());
			pointerVector.PopBack();
			Assert::IsTrue(pointerVector.IsEmpty());

			// Test user-defined data type
			Vector<Foo> fooVector;
			Assert::IsTrue(fooVector.IsEmpty());
			fooVector.PushBack(Foo(0));
			Assert::IsFalse(fooVector.IsEmpty());
			fooVector.PopBack();
			Assert::IsTrue(fooVector.IsEmpty());
		}

		private:
#if defined(DEBUG) | defined(_DEBUG)
			static _CrtMemState sStartMemState;
#endif

	};

#if defined(DEBUG) | defined(_DEBUG)
	_CrtMemState VectorTest::sStartMemState;
#endif

}