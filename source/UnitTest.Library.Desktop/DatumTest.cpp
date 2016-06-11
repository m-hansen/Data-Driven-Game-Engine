#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(DatumTest)
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

		TEST_METHOD(DatumTestConstructor)
		{
			Datum datum;
			Assert::IsTrue(datum.Type() == Datum::DatumType::Unknown);
			Assert::AreEqual(0U, datum.Size());
			Assert::AreEqual(0U, datum.Capacity());
			Assert::IsFalse(datum.IsExternal());

			Datum datum2(Datum::DatumType::Integer, 10);
			Assert::IsTrue(datum2.Type() == Datum::DatumType::Integer);
			Assert::AreEqual(0U, datum2.Size());
			Assert::AreEqual(10U, datum2.Capacity());
			Assert::IsFalse(datum2.IsExternal());
		}

		TEST_METHOD(DatumTestCopyConstructor)
		{
			Datum existingIntDatum;
			existingIntDatum.Set(0, 0);
			existingIntDatum.Set(1, 1);
			existingIntDatum.Set(2, 2);

			Datum intDatum = existingIntDatum;
			Assert::AreEqual(existingIntDatum.Size(), intDatum.Size());
			Assert::AreEqual(existingIntDatum.Capacity(), intDatum.Capacity());
			Assert::IsTrue(existingIntDatum.Type() == intDatum.Type());
			Assert::AreEqual(existingIntDatum.IsExternal(), intDatum.IsExternal());
			for (uint32_t i = 0; i < intDatum.Size(); ++i)
			{
				Assert::AreEqual(existingIntDatum.Get<std::int32_t>(i), intDatum.Get<std::int32_t>(i));
			}
		}

		TEST_METHOD(DatumTestAssignmentOperator)
		{
			// Test external datum
			std::int32_t intArray[] = { 0, 1, 2 };
			Datum existingExternalIntDatum;
			existingExternalIntDatum.SetStorage(intArray, 3);
			Assert::IsTrue(existingExternalIntDatum.IsExternal());

			Datum internalToExternalDatum;
			internalToExternalDatum = existingExternalIntDatum;
			Assert::AreEqual(existingExternalIntDatum.Size(), internalToExternalDatum.Size());
			Assert::AreEqual(existingExternalIntDatum.Capacity(), internalToExternalDatum.Capacity());
			Assert::IsTrue(existingExternalIntDatum.Type() == internalToExternalDatum.Type());
			Assert::AreEqual(existingExternalIntDatum.IsExternal(), internalToExternalDatum.IsExternal());
			for (uint32_t i = 0; i < internalToExternalDatum.Size(); ++i)
			{
				Assert::AreEqual(existingExternalIntDatum.Get<std::int32_t>(i), internalToExternalDatum.Get<std::int32_t>(i));
			}
			internalToExternalDatum = 2;
			Assert::AreEqual(1U, internalToExternalDatum.Size());
			Assert::AreEqual(3U, internalToExternalDatum.Capacity());
			Assert::IsTrue(internalToExternalDatum.Type() == Datum::DatumType::Integer);
			Assert::IsTrue(internalToExternalDatum.IsExternal());
			Assert::AreEqual(2, internalToExternalDatum.Get<std::int32_t>(0));

			// Test integer datum to datum assignment
			Datum existingIntDatum;
			existingIntDatum.Set(0, 0);
			existingIntDatum.Set(1, 1);
			existingIntDatum.Set(2, 2);

			Datum intDatum;
			intDatum = existingIntDatum;
			Assert::AreEqual(existingIntDatum.Size(), intDatum.Size());
			Assert::AreEqual(existingIntDatum.Capacity(), intDatum.Capacity());
			Assert::IsTrue(existingIntDatum.Type() == intDatum.Type());
			Assert::AreEqual(existingIntDatum.IsExternal(), intDatum.IsExternal());
			for (uint32_t i = 0; i < intDatum.Size(); ++i)
			{
				Assert::AreEqual(existingIntDatum.Get<std::int32_t>(i), intDatum.Get<std::int32_t>(i));
			}
			intDatum = 2;
			Assert::AreEqual(1U, intDatum.Size());
			Assert::AreEqual(3U, intDatum.Capacity());
			Assert::IsTrue(intDatum.Type() == Datum::DatumType::Integer);
			Assert::IsFalse(intDatum.IsExternal());
			Assert::AreEqual(2, intDatum.Get<std::int32_t>(0));

			// Test float datum to datum assignment
			Datum existingFloatDatum;
			existingFloatDatum.Set(0.0f, 0);
			existingFloatDatum.Set(1.0f, 1);
			existingFloatDatum.Set(2.0f, 2);

			Datum floatDatum;
			floatDatum = existingFloatDatum;
			Assert::AreEqual(existingFloatDatum.Size(), floatDatum.Size());
			Assert::AreEqual(existingFloatDatum.Capacity(), floatDatum.Capacity());
			Assert::IsTrue(existingFloatDatum.Type() == floatDatum.Type());
			Assert::AreEqual(existingFloatDatum.IsExternal(), floatDatum.IsExternal());
			for (uint32_t i = 0; i < floatDatum.Size(); ++i)
			{
				Assert::AreEqual(existingFloatDatum.Get<float>(i), floatDatum.Get<float>(i));
			}
			floatDatum = 2.0f;
			Assert::AreEqual(1U, floatDatum.Size());
			Assert::AreEqual(3U, floatDatum.Capacity());
			Assert::IsTrue(floatDatum.Type() == Datum::DatumType::Float);
			Assert::IsFalse(floatDatum.IsExternal());
			Assert::AreEqual(2.0f, floatDatum.Get<float>(0));

			// Test vector datum to datum assignment
			Datum existingVectorDatum;
			existingVectorDatum.Set(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), 0);
			existingVectorDatum.Set(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1);
			existingVectorDatum.Set(glm::vec4(2.0f, 2.0f, 2.0f, 2.0f), 2);

			Datum vectorDatum;
			vectorDatum = existingVectorDatum;
			Assert::AreEqual(existingVectorDatum.Size(), vectorDatum.Size());
			Assert::AreEqual(existingVectorDatum.Capacity(), vectorDatum.Capacity());
			Assert::IsTrue(existingVectorDatum.Type() == vectorDatum.Type());
			Assert::AreEqual(existingVectorDatum.IsExternal(), vectorDatum.IsExternal());
			for (uint32_t i = 0; i < vectorDatum.Size(); ++i)
			{
				Assert::IsTrue(existingVectorDatum.Get<glm::vec4>(i) == vectorDatum.Get<glm::vec4>(i));
			}
			vectorDatum = glm::vec4(2.0f, 2.0f, 2.0f, 2.0f);
			Assert::AreEqual(1U, vectorDatum.Size());
			Assert::AreEqual(3U, vectorDatum.Capacity());
			Assert::IsTrue(vectorDatum.Type() == Datum::DatumType::Vector);
			Assert::IsFalse(vectorDatum.IsExternal());
			Assert::IsTrue(glm::vec4(2.0f, 2.0f, 2.0f, 2.0f) == vectorDatum.Get<glm::vec4>(0));

			// Test matrix datum to datum assignment
			Datum existingMatrixDatum;
			existingMatrixDatum.Set(glm::mat4(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f), 0);
			existingMatrixDatum.Set(glm::mat4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f), 1);
			existingMatrixDatum.Set(glm::mat4(2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f), 2);

			Datum matrixDatum;
			matrixDatum = existingMatrixDatum;
			Assert::AreEqual(existingMatrixDatum.Size(), matrixDatum.Size());
			Assert::AreEqual(existingMatrixDatum.Capacity(), matrixDatum.Capacity());
			Assert::IsTrue(existingMatrixDatum.Type() == matrixDatum.Type());
			Assert::AreEqual(existingMatrixDatum.IsExternal(), matrixDatum.IsExternal());
			for (uint32_t i = 0; i < matrixDatum.Size(); ++i)
			{
				Assert::IsTrue(existingMatrixDatum.Get<glm::mat4>(i) == matrixDatum.Get<glm::mat4>(i));
			}
			matrixDatum = glm::mat4(2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f);
			Assert::AreEqual(1U, matrixDatum.Size());
			Assert::AreEqual(3U, matrixDatum.Capacity());
			Assert::IsTrue(matrixDatum.Type() == Datum::DatumType::Matrix);
			Assert::IsFalse(matrixDatum.IsExternal());
			Assert::IsTrue(glm::mat4(2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f) 
				== matrixDatum.Get<glm::mat4>(0));

			// Test table datum to datum assignment
			Scope* scopeA = nullptr;
			Scope* scopeB = nullptr;
			Scope* scopeC = nullptr;
			Scope* scopeD = nullptr;

			Datum existingTableDatum;
			existingTableDatum.Set(*scopeA, 0);
			existingTableDatum.Set(*scopeB, 1);
			existingTableDatum.Set(*scopeC, 2);

			Datum tableDatum;
			tableDatum = existingTableDatum;
			Assert::AreEqual(existingTableDatum.Size(), tableDatum.Size());
			Assert::AreEqual(existingTableDatum.Capacity(), tableDatum.Capacity());
			Assert::IsTrue(existingTableDatum.Type() == tableDatum.Type());
			Assert::AreEqual(existingTableDatum.IsExternal(), tableDatum.IsExternal());
			for (uint32_t i = 0; i < tableDatum.Size(); ++i)
			{
				Assert::IsTrue(existingTableDatum.Get<Scope*>(i) == tableDatum.Get<Scope*>(i));
			}
			tableDatum = scopeD;
			Assert::AreEqual(1U, tableDatum.Size());
			Assert::AreEqual(3U, tableDatum.Capacity());
			Assert::IsTrue(tableDatum.Type() == Datum::DatumType::Table);
			Assert::IsFalse(tableDatum.IsExternal());
			Assert::IsTrue(scopeD == tableDatum.Get<Scope*>(0));

			// Test string datum to datum assignment
			Datum existingStringDatum;
			existingStringDatum.Set("A", 0);
			existingStringDatum.Set("B", 1);
			existingStringDatum.Set("C", 2);

			Datum stringDatum;
			stringDatum = existingStringDatum;
			Assert::AreEqual(existingStringDatum.Size(), stringDatum.Size());
			Assert::AreEqual(existingStringDatum.Capacity(), stringDatum.Capacity());
			Assert::IsTrue(existingStringDatum.Type() == stringDatum.Type());
			Assert::AreEqual(existingStringDatum.IsExternal(), stringDatum.IsExternal());
			for (uint32_t i = 0; i < stringDatum.Size(); ++i)
			{
				Assert::IsTrue(existingStringDatum.Get<std::string>(i) == stringDatum.Get<std::string>(i));
			}
			stringDatum = "new";
			Assert::AreEqual(1U, stringDatum.Size());
			Assert::AreEqual(3U, stringDatum.Capacity());
			Assert::IsTrue(stringDatum.Type() == Datum::DatumType::String);
			Assert::IsFalse(stringDatum.IsExternal());
			Assert::IsTrue("new" == stringDatum.Get<std::string>(0));
		}

		TEST_METHOD(DatumTestAssignmentOperatorScalar)
		{
			std::int32_t integerValue = 1;
			float floatValue = 1;

			// Test datum to int scalar assignment
			Datum intDatum;
			intDatum = 5;
			Assert::ExpectException<std::exception>([&] { intDatum = floatValue; });
			Assert::AreEqual(1U, intDatum.Size());
			Assert::AreEqual(1U, intDatum.Capacity());
			Assert::IsTrue(intDatum.Type() == Datum::DatumType::Integer);
			Assert::IsFalse(intDatum.IsExternal());
			Assert::AreEqual(5, intDatum.Get<std::int32_t>(0));
			intDatum.Set(0, 0);
			intDatum.Set(0, 1);
			intDatum.Set(0, 2);
			Assert::AreEqual(3U, intDatum.Size());
			intDatum = 1;
			Assert::AreEqual(1U, intDatum.Size());
			Assert::AreEqual(3U, intDatum.Capacity());
			Assert::IsTrue(intDatum.Type() == Datum::DatumType::Integer);
			Assert::IsFalse(intDatum.IsExternal());
			Assert::AreEqual(1, intDatum.Get<std::int32_t>(0));
			Assert::ExpectException<std::exception>([&] { intDatum = 1.0f; });

			// Test datum to float scalar assignment
			Datum floatDatum;
			floatDatum = 5.0f;
			Assert::ExpectException<std::exception>([&] { floatDatum = integerValue; });
			Assert::AreEqual(1U, floatDatum.Size());
			Assert::AreEqual(1U, floatDatum.Capacity());
			Assert::IsTrue(floatDatum.Type() == Datum::DatumType::Float);
			Assert::IsFalse(floatDatum.IsExternal());
			Assert::AreEqual(5.0f, floatDatum.Get<float>(0));
			floatDatum.Set(0.0f, 0);
			floatDatum.Set(0.0f, 1);
			floatDatum.Set(0.0f, 2);
			Assert::AreEqual(3U, floatDatum.Size());
			floatDatum = 1.0f;
			Assert::AreEqual(1U, floatDatum.Size());
			Assert::AreEqual(3U, floatDatum.Capacity());
			Assert::IsTrue(floatDatum.Type() == Datum::DatumType::Float);
			Assert::IsFalse(floatDatum.IsExternal());
			Assert::AreEqual(1.0f, floatDatum.Get<float>(0));
			Assert::ExpectException<std::exception>([&] { floatDatum = 1; });

			// Test datum to vector scalar assignment
			glm::vec4 zeroVec = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
			glm::vec4 oneVec = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			Datum vectorDatum;
			vectorDatum = zeroVec;
			Assert::ExpectException<std::exception>([&] { vectorDatum = integerValue; });
			Assert::AreEqual(1U, vectorDatum.Size());
			Assert::AreEqual(1U, vectorDatum.Capacity());
			Assert::IsTrue(vectorDatum.Type() == Datum::DatumType::Vector);
			Assert::IsFalse(vectorDatum.IsExternal());
			Assert::IsTrue(zeroVec == vectorDatum.Get<glm::vec4>(0));
			vectorDatum.Set(zeroVec, 0);
			vectorDatum.Set(zeroVec, 1);
			vectorDatum.Set(zeroVec, 2);
			Assert::AreEqual(3U, vectorDatum.Size());
			vectorDatum = oneVec;
			Assert::AreEqual(1U, vectorDatum.Size());
			Assert::AreEqual(3U, vectorDatum.Capacity());
			Assert::IsTrue(vectorDatum.Type() == Datum::DatumType::Vector);
			Assert::IsFalse(vectorDatum.IsExternal());
			Assert::IsTrue(oneVec == vectorDatum.Get<glm::vec4>(0));
			Assert::ExpectException<std::exception>([&] { vectorDatum = 1; });

			// Test datum to matrix scalar assignment
			glm::mat4 zeroMat = glm::mat4(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			glm::mat4 oneMat = glm::mat4(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
			Datum matrixDatum;
			matrixDatum = zeroMat;
			Assert::ExpectException<std::exception>([&] { matrixDatum = integerValue; });
			Assert::AreEqual(1U, matrixDatum.Size());
			Assert::AreEqual(1U, matrixDatum.Capacity());
			Assert::IsTrue(matrixDatum.Type() == Datum::DatumType::Matrix);
			Assert::IsFalse(matrixDatum.IsExternal());
			Assert::IsTrue(zeroMat == matrixDatum.Get<glm::mat4>(0));
			matrixDatum.Set(zeroMat, 0);
			matrixDatum.Set(zeroMat, 1);
			matrixDatum.Set(zeroMat, 2);
			Assert::AreEqual(3U, matrixDatum.Size());
			matrixDatum = oneMat;
			Assert::AreEqual(1U, matrixDatum.Size());
			Assert::AreEqual(3U, matrixDatum.Capacity());
			Assert::IsTrue(matrixDatum.Type() == Datum::DatumType::Matrix);
			Assert::IsFalse(matrixDatum.IsExternal());
			Assert::IsTrue(oneMat == matrixDatum.Get<glm::mat4>(0));
			Assert::ExpectException<std::exception>([&] { matrixDatum = 1; });

			// Test datum to string scalar assignment
			std::string stringA = "String A";
			std::string stringB = "String B";
			Datum stringDatum;
			stringDatum = stringA;
			Assert::ExpectException<std::exception>([&] { stringDatum = integerValue; });
			Assert::AreEqual(1U, stringDatum.Size());
			Assert::AreEqual(1U, stringDatum.Capacity());
			Assert::IsTrue(stringDatum.Type() == Datum::DatumType::String);
			Assert::IsFalse(stringDatum.IsExternal());
			Assert::IsTrue(stringA == stringDatum.Get<std::string>(0));
			stringDatum.Set(stringA, 0);
			stringDatum.Set(stringA, 1);
			stringDatum.Set(stringA, 2);
			Assert::AreEqual(3U, stringDatum.Size());
			stringDatum = stringB;
			Assert::AreEqual(1U, stringDatum.Size());
			Assert::AreEqual(3U, stringDatum.Capacity());
			Assert::IsTrue(stringDatum.Type() == Datum::DatumType::String);
			Assert::IsFalse(stringDatum.IsExternal());
			Assert::IsTrue(stringB == stringDatum.Get<std::string>(0));
			Assert::ExpectException<std::exception>([&] { stringDatum = 1; });
		}

		TEST_METHOD(DatumTestReserve)
		{
			Datum datum;
			Assert::ExpectException<std::exception>([&] { datum.Reserve(1); });
			datum.SetType(Datum::DatumType::Integer);
			datum.Reserve(1);
			Assert::AreEqual(0U, datum.Size());
			Assert::AreEqual(1U, datum.Capacity());
			datum.Reserve(10);
			Assert::AreEqual(0U, datum.Size());
			Assert::AreEqual(10U, datum.Capacity());
			datum.Reserve(5);
			Assert::AreEqual(0U, datum.Size());
			Assert::AreEqual(10U, datum.Capacity());
			datum.Reserve(20);
			Assert::AreEqual(0U, datum.Size());
			Assert::AreEqual(20U, datum.Capacity());
		}

		TEST_METHOD(DatumTestPushBackInteger)
		{
			Datum datum;
			Assert::ExpectException<std::exception>([&] {datum.PushBack(0); });
			datum.Set(0, 0);
			Assert::AreEqual(1U, datum.Size());
			datum.PushBack(0);
			Assert::AreEqual(2U, datum.Size());
			datum.PushBack(0);
			Assert::AreEqual(3U, datum.Size());
			Assert::IsTrue(datum.Get<std::int32_t>(0) == 0);
			Assert::IsTrue(datum.Get<std::int32_t>(1) == 0);
			Assert::IsTrue(datum.Get<std::int32_t>(2) == 0);
		}

		TEST_METHOD(DatumTestPushBackFloat)
		{
			Datum datum;
			Assert::ExpectException<std::exception>([&] {datum.PushBack(0); });
			datum.Set(0.0f, 0);
			Assert::AreEqual(1U, datum.Size());
			datum.PushBack(0.0f);
			Assert::AreEqual(2U, datum.Size());
			datum.PushBack(0.0f);
			Assert::AreEqual(3U, datum.Size());
		}

		TEST_METHOD(DatumTestTypeAndSetType)
		{
			Datum intDatum;
			Assert::IsTrue(intDatum.Type() == Datum::DatumType::Unknown);
			intDatum.SetType(Datum::DatumType::Integer);
			Assert::IsTrue(intDatum.Type() == Datum::DatumType::Integer);
			intDatum.SetType(Datum::DatumType::Integer);
			Assert::IsTrue(intDatum.Type() == Datum::DatumType::Integer);
			Assert::ExpectException<std::exception>([&] { intDatum.SetType(Datum::DatumType::Float); });

			Datum floatDatum;
			Assert::IsTrue(floatDatum.Type() == Datum::DatumType::Unknown);
			floatDatum.SetType(Datum::DatumType::Float);
			Assert::IsTrue(floatDatum.Type() == Datum::DatumType::Float);
			floatDatum.SetType(Datum::DatumType::Float);
			Assert::IsTrue(floatDatum.Type() == Datum::DatumType::Float);
			Assert::ExpectException<std::exception>([&] { floatDatum.SetType(Datum::DatumType::Integer); });

			Datum vectorDatum;
			Assert::IsTrue(vectorDatum.Type() == Datum::DatumType::Unknown);
			vectorDatum.SetType(Datum::DatumType::Vector);
			Assert::IsTrue(vectorDatum.Type() == Datum::DatumType::Vector);
			vectorDatum.SetType(Datum::DatumType::Vector);
			Assert::IsTrue(vectorDatum.Type() == Datum::DatumType::Vector);
			Assert::ExpectException<std::exception>([&] { vectorDatum.SetType(Datum::DatumType::Integer); });

			Datum matrixDatum;
			Assert::IsTrue(matrixDatum.Type() == Datum::DatumType::Unknown);
			matrixDatum.SetType(Datum::DatumType::Matrix);
			Assert::IsTrue(matrixDatum.Type() == Datum::DatumType::Matrix);
			matrixDatum.SetType(Datum::DatumType::Matrix);
			Assert::IsTrue(matrixDatum.Type() == Datum::DatumType::Matrix);
			Assert::ExpectException<std::exception>([&] { matrixDatum.SetType(Datum::DatumType::Integer); });

			Datum stringDatum;
			Assert::IsTrue(stringDatum.Type() == Datum::DatumType::Unknown);
			stringDatum.SetType(Datum::DatumType::String);
			Assert::IsTrue(stringDatum.Type() == Datum::DatumType::String);
			stringDatum.SetType(Datum::DatumType::String);
			Assert::IsTrue(stringDatum.Type() == Datum::DatumType::String);
			Assert::ExpectException<std::exception>([&] { stringDatum.SetType(Datum::DatumType::Integer); });

			Datum pointerDatum;
			Assert::IsTrue(pointerDatum.Type() == Datum::DatumType::Unknown);
			pointerDatum.SetType(Datum::DatumType::Pointer);
			Assert::IsTrue(pointerDatum.Type() == Datum::DatumType::Pointer);
			pointerDatum.SetType(Datum::DatumType::Pointer);
			Assert::IsTrue(pointerDatum.Type() == Datum::DatumType::Pointer);
			Assert::ExpectException<std::exception>([&] { pointerDatum.SetType(Datum::DatumType::Integer); });
		}

		TEST_METHOD(DatumTestSize)
		{
			std::int32_t intArray[] = { -1, 0, 1 };
			Datum intDatum;
			Assert::AreEqual(0U, intDatum.Size());
			intDatum.Set(0, 0);
			Assert::AreEqual(1U, intDatum.Size());
			intDatum.SetFromString("1", 1);
			Assert::AreEqual(2U, intDatum.Size());
			intDatum.Set(20);
			Assert::AreEqual(2U, intDatum.Size());
			intDatum.Set(40, 1);
			Assert::AreEqual(2U, intDatum.Size());
			intDatum.Clear();
			Assert::AreEqual(0U, intDatum.Size());
			intDatum.SetStorage(intArray, 3);
			Assert::AreEqual(3U, intDatum.Size());
		}

		TEST_METHOD(DatumTestClear)
		{
			std::int32_t intArray[] = { 0, 1, 2 };

			Datum internalDatum;
			internalDatum.Set(0, 0);
			internalDatum.Set(1, 1);
			internalDatum.Set(2, 2);
			Assert::AreEqual(3U, internalDatum.Size());
			Assert::IsTrue(internalDatum.Type() == Datum::DatumType::Integer);
			internalDatum.Clear();
			Assert::AreEqual(0U, internalDatum.Size());
			Assert::IsTrue(internalDatum.Type() == Datum::DatumType::Unknown);

			Datum externalDatum;
			externalDatum.SetStorage(intArray, ((sizeof(intArray) / sizeof(intArray[0]))));
			Assert::AreEqual(3U, externalDatum.Size());
			Assert::IsTrue(externalDatum.Type() == Datum::DatumType::Integer);
			externalDatum.Clear();
			Assert::AreEqual(0U, externalDatum.Size());
			Assert::IsTrue(externalDatum.Type() == Datum::DatumType::Unknown);
		}

		TEST_METHOD(DatumTestSetStorageInteger)
		{
			std::int32_t intArrayA[] = { -1, 0, 1 };
			std::int32_t intArrayB[] = { 2, 3, 4, 5, 6 };

			Datum intDatum;
			Assert::IsFalse(intDatum.IsExternal());
			intDatum.SetStorage(intArrayA, (sizeof(intArrayA) / sizeof(intArrayA[0])));
			Assert::IsTrue(intDatum.IsExternal());
			Assert::AreEqual(3U, intDatum.Size());
			Assert::AreEqual(3U, intDatum.Capacity());
			Assert::IsTrue(intDatum.Type() == Datum::DatumType::Integer);
			intDatum.SetStorage(intArrayB, (sizeof(intArrayB) / sizeof(intArrayB[0])));
			Assert::IsTrue(intDatum.IsExternal());
			Assert::AreEqual(5U, intDatum.Size());
			Assert::AreEqual(5U, intDatum.Capacity());
			Assert::IsTrue(intDatum.Type() == Datum::DatumType::Integer);
		}

		TEST_METHOD(DatumTestSetStorageFloat)
		{
			float floatArrayA[] = { -1.0f, 0.6f, 1.234f };
			float floatArrayB[] = { 2.0f, 3.0f, 4.0f, 5.1f, 6.234f };

			Datum floatDatum;
			Assert::IsFalse(floatDatum.IsExternal());
			floatDatum.SetStorage(floatArrayA, (sizeof(floatArrayA) / sizeof(floatArrayA[0])));
			Assert::IsTrue(floatDatum.IsExternal());
			Assert::AreEqual(3U, floatDatum.Size());
			Assert::AreEqual(3U, floatDatum.Capacity());
			Assert::IsTrue(floatDatum.Type() == Datum::DatumType::Float);
			floatDatum.SetStorage(floatArrayB, (sizeof(floatArrayB) / sizeof(floatArrayB[0])));
			Assert::IsTrue(floatDatum.IsExternal());
			Assert::AreEqual(5U, floatDatum.Size());
			Assert::AreEqual(5U, floatDatum.Capacity());
			Assert::IsTrue(floatDatum.Type() == Datum::DatumType::Float);
		}

		TEST_METHOD(DatumTestSetStorageVector)
		{
			glm::vec4 vectorArrayA[] = {
				glm::vec4(0.0f, 0.0f, 0.0f, 0.0f),
				glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) };

			glm::vec4 vectorArrayB[] = {
				glm::vec4(2.0f, 1.0f, 0.0f, 3.0f),
				glm::vec4(1.0f, 2.0f, 3.0f, 0.0f),
				glm::vec4(0.0f, 3.0f, 2.0f, 1.0f) };

			Datum vectorDatum;
			Assert::IsFalse(vectorDatum.IsExternal());
			vectorDatum.SetStorage(vectorArrayA, (sizeof(vectorArrayA) / sizeof(vectorArrayA[0])));
			Assert::IsTrue(vectorDatum.IsExternal());
			Assert::AreEqual(2U, vectorDatum.Size());
			Assert::AreEqual(2U, vectorDatum.Capacity());
			Assert::IsTrue(vectorDatum.Type() == Datum::DatumType::Vector);
			vectorDatum.SetStorage(vectorArrayB, (sizeof(vectorArrayB) / sizeof(vectorArrayB[0])));
			Assert::IsTrue(vectorDatum.IsExternal());
			Assert::AreEqual(3U, vectorDatum.Size());
			Assert::AreEqual(3U, vectorDatum.Capacity());
			Assert::IsTrue(vectorDatum.Type() == Datum::DatumType::Vector);
		}

		TEST_METHOD(DatumTestSetStorageMatrix)
		{
			glm::mat4 matrixArrayA[] = {
				glm::mat4(
					0.0f, 0.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 0.0f) };

			glm::mat4 matrixArrayB[] = {
				glm::mat4(
					2.0f, 2.0f, 2.0f, 2.0f,
					2.0f, 2.0f, 2.0f, 2.0f,
					2.0f, 2.0f, 2.0f, 2.0f,
					2.0f, 2.0f, 2.0f, 2.0f), 
				glm::mat4(
					1.0f, 1.0f, 1.0f, 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f) };

			Datum matrixDatum;
			Assert::IsFalse(matrixDatum.IsExternal());
			matrixDatum.SetStorage(matrixArrayA, (sizeof(matrixArrayA) / sizeof(matrixArrayA[0])));
			Assert::IsTrue(matrixDatum.IsExternal());
			Assert::AreEqual(1U, matrixDatum.Size());
			Assert::AreEqual(1U, matrixDatum.Capacity());
			Assert::IsTrue(matrixDatum.Type() == Datum::DatumType::Matrix);
			matrixDatum.SetStorage(matrixArrayB, (sizeof(matrixArrayB) / sizeof(matrixArrayB[0])));
			Assert::IsTrue(matrixDatum.IsExternal());
			Assert::AreEqual(2U, matrixDatum.Size());
			Assert::AreEqual(2U, matrixDatum.Capacity());
			Assert::IsTrue(matrixDatum.Type() == Datum::DatumType::Matrix);
		}

		TEST_METHOD(DatumTestSetStorageString)
		{
			std::string stringArrayA[] = { "oneA", "twoA" };
			std::string stringArrayB[] = { "oneB", "twoB", "threeB" };

			Datum stringDatum;
			Assert::IsFalse(stringDatum.IsExternal());
			stringDatum.SetStorage(stringArrayA, (sizeof(stringArrayA) / sizeof(stringArrayA[0])));
			Assert::IsTrue(stringDatum.IsExternal());
			Assert::AreEqual(2U, stringDatum.Size());
			Assert::AreEqual(2U, stringDatum.Capacity());
			Assert::IsTrue(stringDatum.Type() == Datum::DatumType::String);
			stringDatum.SetStorage(stringArrayB, (sizeof(stringArrayB) / sizeof(stringArrayB[0])));
			Assert::IsTrue(stringDatum.IsExternal());
			Assert::AreEqual(3U, stringDatum.Size());
			Assert::AreEqual(3U, stringDatum.Capacity());
			Assert::IsTrue(stringDatum.Type() == Datum::DatumType::String);
		}

		TEST_METHOD(DatumTestComparisonOperatorDatum)
		{
			Datum intDatumA;
			intDatumA.Set(0, 0);
			intDatumA.Set(1, 1);
			intDatumA.Set(2, 2);

			Datum intDatumB;
			intDatumB.Set(0, 0);
			intDatumB.Set(1, 1);
			intDatumB.Set(2, 2);

			Datum intDatumC;
			intDatumC.Set(0, 0);
			intDatumC.Set(5, 1);
			intDatumC.Set(2, 2);

			Datum intDatumD;
			intDatumD.Set(0, 0);
			intDatumD.Set(5, 1);

			Datum floatDatumA;
			floatDatumA.Set(0.0f, 0);
			floatDatumA.Set(1.0f, 1);
			floatDatumA.Set(2.0f, 2);

			Datum floatDatumB;
			floatDatumA.Set(1.0f, 0);
			floatDatumA.Set(1.0f, 1);
			floatDatumA.Set(2.0f, 2);

			Assert::IsTrue(intDatumA == intDatumB);
			Assert::IsTrue(intDatumB == intDatumA);
			Assert::IsFalse(intDatumA == intDatumC);
			Assert::IsFalse(intDatumC == intDatumD);
			Assert::IsFalse(intDatumA == floatDatumA);
			Assert::IsFalse(floatDatumA == floatDatumB);

			Assert::IsFalse(intDatumA != intDatumB);
			Assert::IsFalse(intDatumB != intDatumA);
			Assert::IsTrue(intDatumA != intDatumC);
			Assert::IsTrue(intDatumC != intDatumD);
			Assert::IsTrue(intDatumA != floatDatumA);
			Assert::IsTrue(floatDatumA != floatDatumB);

			Datum vectorDatumA;
			vectorDatumA.Set(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), 0);
			vectorDatumA.Set(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f), 1);

			Datum vectorDatumB;
			vectorDatumA.Set(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), 0);
			vectorDatumA.Set(glm::vec4(1.0f, 1.0f, 0.0f, 0.0f), 1);

			Datum vectorDatumC;
			vectorDatumA.Set(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), 0);
			vectorDatumA.Set(glm::vec4(1.0f, 1.0f, 0.0f, 0.0f), 1);

			Assert::IsTrue(vectorDatumB == vectorDatumC);
			Assert::IsFalse(vectorDatumA == vectorDatumB);

			Assert::IsFalse(vectorDatumB != vectorDatumC);
			Assert::IsTrue(vectorDatumA != vectorDatumB);

			Datum matrixDatumA;
			matrixDatumA.Set(glm::mat4(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f), 0);
			matrixDatumA.Set(glm::mat4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f), 1);

			Datum matrixDatumB;
			matrixDatumB.Set(glm::mat4(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f), 0);
			matrixDatumB.Set(glm::mat4(1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f), 1);

			Datum matrixDatumC;
			matrixDatumC.Set(glm::mat4(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f), 0);
			matrixDatumC.Set(glm::mat4(1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f), 1);

			Assert::IsTrue(matrixDatumB == matrixDatumC);
			Assert::IsFalse(matrixDatumA == matrixDatumB);

			Assert::IsFalse(matrixDatumB != matrixDatumC);
			Assert::IsTrue(matrixDatumA != matrixDatumB);

			Datum stringDatumA;
			stringDatumA.Set("one", 0);
			stringDatumA.Set("two", 1);
			stringDatumA.Set("three", 2);

			Datum stringDatumB;
			stringDatumB.Set("one", 0);
			stringDatumB.Set("two", 1);
			stringDatumB.Set("four", 2);

			Datum stringDatumC;
			stringDatumC.Set("one", 0);
			stringDatumC.Set("two", 1);
			stringDatumC.Set("four", 2);

			Assert::IsTrue(stringDatumB == stringDatumC);
			Assert::IsFalse(stringDatumA == stringDatumB);

			Assert::IsFalse(stringDatumB != stringDatumC);
			Assert::IsTrue(stringDatumA != stringDatumB);
		}

		TEST_METHOD(DatumTestComparisonOperatorIntegerScalar)
		{
			Datum datum;
			datum.Set(0, 0);
			Assert::IsTrue(datum == 0);
			Assert::IsTrue(datum != 1);
		}

		TEST_METHOD(DatumTestComparisonOperatorFloatScalar)
		{
			Datum datum;
			datum.Set(0.0f, 0);
			Assert::IsTrue(datum == 0.0f);
			Assert::IsTrue(datum != 1.0f);
		}

		TEST_METHOD(DatumTestComparisonOperatorVectorScalar)
		{
			glm::vec4 vectorA = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
			glm::vec4 vectorB = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

			Datum datum;
			datum.Set(vectorA, 0);
			Assert::IsTrue(datum == vectorA);
			Assert::IsTrue(datum != vectorB);
		}

		TEST_METHOD(DatumTestComparisonOperatorMatrixScalar)
		{
			glm::mat4 matrixA = glm::mat4(
				0.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f );

			glm::mat4 matrixB = glm::mat4(
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f);

			Datum datum;
			datum.Set(matrixA, 0);
			Assert::IsTrue(datum == matrixA);
			Assert::IsTrue(datum != matrixB);
		}

		TEST_METHOD(DatumTestComparisonOperatorStringScalar)
		{
			std::string stringA = "stringA";
			std::string stringB = "stringB";

			Datum datum;
			datum.Set(stringA, 0);
			Assert::IsTrue(datum == stringA);
			Assert::IsTrue(datum != stringB);
		}

		TEST_METHOD(DatumTestSetInteger)
		{
			Datum datum;
			datum.Set(0, 0);
			Assert::AreEqual(1U, datum.Size());
			Assert::IsTrue(datum.Type() == Datum::DatumType::Integer);
			Assert::AreEqual(0, datum.Get<std::int32_t>(0));
		}

		TEST_METHOD(DatumTestSetFloat)
		{
			Datum datum;
			datum.Set(0.0f, 0);
			Assert::AreEqual(1U, datum.Size());
			Assert::IsTrue(datum.Type() == Datum::DatumType::Float);
			Assert::AreEqual(0.0f, datum.Get<float>(0));
		}

		TEST_METHOD(DatumTestSetVector)
		{
			glm::vec4 vector = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);

			Datum datum;
			datum.Set(vector, 0);
			Assert::AreEqual(1U, datum.Size());
			Assert::IsTrue(datum.Type() == Datum::DatumType::Vector);
			Assert::IsTrue(vector == datum.Get<glm::vec4>(0));
		}

		TEST_METHOD(DatumTestSetMatrix)
		{
			glm::mat4 matrix = glm::mat4(
				0.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f );

			Datum datum;
			datum.Set(matrix, 0);
			Assert::AreEqual(1U, datum.Size());
			Assert::IsTrue(datum.Type() == Datum::DatumType::Matrix);
			Assert::IsTrue(matrix == datum.Get<glm::mat4>(0));
		}

		TEST_METHOD(DatumTestSetString)
		{
			std::string str = "string";

			Datum datum;
			datum.Set(str, 0);
			Assert::AreEqual(1U, datum.Size());
			Assert::IsTrue(datum.Type() == Datum::DatumType::String);
			Assert::AreEqual(str, datum.Get<std::string>(0));
		}

		TEST_METHOD(DatumTestSetFromString)
		{
			Datum intDatum;
			Assert::ExpectException<std::exception>([&] { intDatum.SetFromString("5"); });
			intDatum.SetType(Datum::DatumType::Integer);
			intDatum.SetFromString("5");
			Assert::AreEqual(1U, intDatum.Size());
			Assert::AreEqual(5, intDatum.Get<std::int32_t>(0));
			intDatum.SetFromString("2", 1);
			Assert::AreEqual(2U, intDatum.Size());
			Assert::AreEqual(2, intDatum.Get<std::int32_t>(1));

			Datum floatDatum;
			Assert::ExpectException<std::exception>([&] { floatDatum.SetFromString("5.0"); });
			floatDatum.SetType(Datum::DatumType::Float);
			floatDatum.SetFromString("5.0");
			Assert::AreEqual(1U, floatDatum.Size());
			Assert::AreEqual(5.0f, floatDatum.Get<float>(0));
			floatDatum.SetFromString("2.2", 1);
			Assert::AreEqual(2U, floatDatum.Size());
			Assert::AreEqual(2.2f, floatDatum.Get<float>(1));

			glm::vec4 vectorA = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
			glm::vec4 vectorB = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			Datum vectorDatum;
			Assert::ExpectException<std::exception>([&] { vectorDatum.SetFromString("(0 0 0 0)"); });
			vectorDatum.SetType(Datum::DatumType::Vector);
			Assert::ExpectException<std::exception>([&] { vectorDatum.SetFromString("(0,0,0,0)"); });
			vectorDatum.SetFromString("(0 0 0 0)");
			Assert::AreEqual(1U, vectorDatum.Size());
			Assert::IsTrue(vectorA == vectorDatum.Get<glm::vec4>(0));
			vectorDatum.SetFromString("(1 1 1 1)", 1);
			Assert::AreEqual(2U, vectorDatum.Size());
			Assert::IsTrue(vectorB == vectorDatum.Get<glm::vec4>(1));

			glm::mat4 matrixA = glm::mat4(
				0.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f );
			glm::mat4 matrixB = glm::mat4(
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f );
			Datum matrixDatum;
			Assert::ExpectException<std::exception>([&] { matrixDatum.SetFromString("[(0 0 0 0),(0 0 0 0),(0 0 0 0),(0 0 0 0)]"); });
			matrixDatum.SetType(Datum::DatumType::Matrix);
			Assert::ExpectException<std::exception>([&] { matrixDatum.SetFromString("[(0 0 0 0)(0 0 0 0)(0 0 0 0)(0 0 0 0)]"); });
			matrixDatum.SetFromString("[(0 0 0 0),(0 0 0 0),(0 0 0 0),(0 0 0 0)]");
			Assert::AreEqual(1U, matrixDatum.Size());
			Assert::IsTrue(matrixA == matrixDatum.Get<glm::mat4>(0));
			matrixDatum.SetFromString("[(1 1 1 1),(1 1 1 1),(1 1 1 1),(1 1 1 1)]", 1);
			Assert::AreEqual(2U, matrixDatum.Size());
			Assert::IsTrue(matrixB == matrixDatum.Get<glm::mat4>(1));

			std::string hello = "hello";
			std::string world = "world";
			Datum stringDatum;
			Assert::ExpectException<std::exception>([&] { stringDatum.SetFromString(hello); });
			stringDatum.SetType(Datum::DatumType::String);
			stringDatum.SetFromString(hello);
			Assert::AreEqual(1U, stringDatum.Size());
			Assert::IsTrue(hello == stringDatum.Get<std::string>(0));
			stringDatum.SetFromString(world, 1);
			Assert::AreEqual(2U, stringDatum.Size());
			Assert::IsTrue(world == stringDatum.Get<std::string>(1));
		}

		TEST_METHOD(DatumTestToString)
		{
			Datum intDatum;
			intDatum.Set(0, 0);
			intDatum.Set(1, 1);
			Assert::IsTrue(intDatum.ToString(0) == "0");
			Assert::IsTrue(intDatum.ToString(1) == "1");

			Datum floatDatum;
			floatDatum.Set(0.0f, 0);
			floatDatum.Set(1.0f, 1);
			Assert::IsTrue(floatDatum.ToString(0) == "0.000000");
			Assert::IsTrue(floatDatum.ToString(1) == "1.000000");

			Datum vectorDatum;
			vectorDatum.Set(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f), 0);
			Assert::IsTrue(vectorDatum.ToString() == "(0.000000 0.000000 0.000000 0.000000)");

			Datum matrixDatum;
			matrixDatum.Set(glm::mat4(
				0.0f, 0.0f, 0.0f, 0.0f, 
				0.0f, 0.0f, 0.0f, 0.0f, 
				0.0f, 0.0f, 0.0f, 0.0f, 
				0.0f, 0.0f, 0.0f, 0.0f), 0);
			Assert::IsTrue(matrixDatum.ToString() == 
				"[(0.000000 0.000000 0.000000 0.000000),"
				"(0.000000 0.000000 0.000000 0.000000),"
				"(0.000000 0.000000 0.000000 0.000000),"
				"(0.000000 0.000000 0.000000 0.000000)]");

			Datum stringDatum;
			stringDatum.Set("test_string", 0);
			Assert::IsTrue(stringDatum.ToString() == "test_string");
		}

	private:
#if defined(DEBUG) | defined(_DEBUG)
		static _CrtMemState sStartMemState;
#endif

	};

#if defined(DEBUG) | defined(_DEBUG)
	_CrtMemState DatumTest::sStartMemState;
#endif

}
