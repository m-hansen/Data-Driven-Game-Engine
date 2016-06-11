#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;

namespace UnitTestLibraryDesktop
{
	/**
	 * @brief The default hash function to use for a HashMap that uses std::string as a key.
	 */
	class FooHash
	{
	public:
		/**
		 * Overloads operator() to return a hash index.
		 *
		 * @param key the key to hash
		 * @param size the number of buckets
		 * @return the newly hashed index
		 */
		std::uint32_t operator()(const Foo& key)
		{
			std::uint32_t hash = 0;
			for (std::uint32_t i = 0; i < sizeof(key); ++i)
			{
				hash = hash << 1 ^ key.Data();
			}
			return hash;
		}
	};

	TEST_CLASS(HashMapTest)
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

		TEST_METHOD(HashMapTestConstructor)
		{
			// Test construction of a HashMap with a table (bucket) size of zero
			Assert::ExpectException<std::exception>([&]
			{
				HashMap<std::int32_t, std::int32_t> intKeyHashMap(0);
			});

			// Test construction of a HashMap with an integer as a key
			HashMap<std::int32_t, std::int32_t> intKeyHashMap(10);
			Assert::AreEqual(0U, intKeyHashMap.Size());

			// Test construction of a HashMap with a pointer as a key
			HashMap<std::int32_t*, std::int32_t> pointerKeyHashMap(10);
			Assert::AreEqual(0U, pointerKeyHashMap.Size());

			// Test construction of a HashMap with a char* as a key
			HashMap<char*, std::int32_t> charKeyHashMap(10);
			Assert::AreEqual(0U, charKeyHashMap.Size());

			// Test construction of a HashMap with a string as a key
			HashMap<std::string, std::int32_t> stringKeyHashMap(10);
			Assert::AreEqual(0U, stringKeyHashMap.Size());

			// Test construction of a HashMap with Foo as a key
			HashMap<Foo, std::int32_t, FooHash> fooKeyHashMap(10);
			Assert::AreEqual(0U, fooKeyHashMap.Size());
		}

		TEST_METHOD(HashMapTestIncrementOperator)
		{
			// Test a HashMap that uses an integer as a key
			HashMap<std::int32_t, std::int32_t> intKeyHashMap(10);
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(0, 0));
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(1, 1));
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(2, 2));

			std::uint32_t elementCount = 0;
			for (auto it = intKeyHashMap.begin(); it != intKeyHashMap.end(); ++it)
			{
				++elementCount;
			}
			Assert::AreEqual(intKeyHashMap.Size(), elementCount);

			auto intIter = intKeyHashMap.begin();
			++intIter;
			intIter++;
			++intIter;
			Assert::ExpectException<std::exception>([&] { ++intIter; });

			// Test a HashMap that uses a pointer as a key
			HashMap<std::int32_t*, std::int32_t> pointerKeyHashMap(10);
			std::int32_t pointerKeyData[] = { 0, 1, 2 };
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[0], 0));
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[1], 1));
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[2], 2));

			elementCount = 0;
			for (auto it = pointerKeyHashMap.begin(); it != pointerKeyHashMap.end(); ++it)
			{
				++elementCount;
			}
			Assert::AreEqual(pointerKeyHashMap.Size(), elementCount);

			auto pointerIter = pointerKeyHashMap.begin();
			++pointerIter;
			pointerIter++;
			++pointerIter;
			Assert::ExpectException<std::exception>([&] { ++pointerIter; });

			// Test a HashMap that uses a char* as a key
			HashMap<char*, std::int32_t> charKeyHashMap(10);
			char* charKeyData[] = { "one", "two", "three" };
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType(charKeyData[0], 0));
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType(charKeyData[1], 1));
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType(charKeyData[2], 2));

			elementCount = 0;
			for (auto it = charKeyHashMap.begin(); it != charKeyHashMap.end(); ++it)
			{
				++elementCount;
			}
			Assert::AreEqual(charKeyHashMap.Size(), elementCount);

			auto charIter = charKeyHashMap.begin();
			++charIter;
			charIter++;
			++charIter;
			Assert::ExpectException<std::exception>([&] { ++charIter; });

			// Test a HashMap that uses a string as a key
			HashMap<std::string, std::int32_t> stringKeyHashMap(10);
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType("one", 0));
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType("two", 1));
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType("three", 2));

			elementCount = 0;
			for (auto it = stringKeyHashMap.begin(); it != stringKeyHashMap.end(); ++it)
			{
				++elementCount;
			}
			Assert::AreEqual(stringKeyHashMap.Size(), elementCount);

			auto stringIter = stringKeyHashMap.begin();
			++stringIter;
			stringIter++;
			++stringIter;
			Assert::ExpectException<std::exception>([&] { ++stringIter; });
			
			// Test a HashMap that uses Foo as a key
			HashMap<Foo, std::int32_t, FooHash> fooKeyHashMap(10);
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(Foo(0), 0));
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(Foo(1), 1));
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(Foo(2), 2));

			elementCount = 0;
			for (auto it = fooKeyHashMap.begin(); it != fooKeyHashMap.end(); ++it)
			{
				++elementCount;
			}
			Assert::AreEqual(fooKeyHashMap.Size(), elementCount);

			auto fooIter = fooKeyHashMap.begin();
			++fooIter;
			fooIter++;
			++fooIter;
			Assert::ExpectException<std::exception>([&] { ++fooIter; });
		}

		TEST_METHOD(HashMapTestFind)
		{
			// Test using an integer as the key type
			HashMap<std::int32_t, std::int32_t> intKeyHashMap(10);
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(0, 0));
			Assert::AreEqual(0, (*intKeyHashMap.Find(0)).first);
			Assert::AreEqual(0, (*intKeyHashMap.Find(0)).second);
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(1, 2));
			Assert::AreEqual(1, (*intKeyHashMap.Find(1)).first);
			Assert::AreEqual(2, (*intKeyHashMap.Find(1)).second);
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(2, 2));
			Assert::AreEqual(2, (*intKeyHashMap.Find(2)).first);
			Assert::AreEqual(2, (*intKeyHashMap.Find(2)).second);
			intKeyHashMap.Find(200);

			// Test using a pointer as the key type
			HashMap<std::int32_t*, std::int32_t> pointerKeyHashMap(10);
			std::int32_t pointerKeyData[] = { 0, 1, 2, 200 };
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[0], 0));
			Assert::AreEqual(&pointerKeyData[0], (*pointerKeyHashMap.Find(&pointerKeyData[0])).first);
			Assert::AreEqual(0, (*pointerKeyHashMap.Find(&pointerKeyData[0])).second);
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[1], 2));
			Assert::AreEqual(&pointerKeyData[1], (*pointerKeyHashMap.Find(&pointerKeyData[1])).first);
			Assert::AreEqual(2, (*pointerKeyHashMap.Find(&pointerKeyData[1])).second);
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[2], 2));
			Assert::AreEqual(&pointerKeyData[2], (*pointerKeyHashMap.Find(&pointerKeyData[2])).first);
			Assert::AreEqual(2, (*pointerKeyHashMap.Find(&pointerKeyData[2])).second);
			pointerKeyHashMap.Find(&pointerKeyData[3]);

			// Test using a char* as the key type
			HashMap<char*, std::int32_t> charKeyHashMap(10);
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType("one", 0));
			Assert::AreEqual("one", (*charKeyHashMap.Find("one")).first);
			Assert::AreEqual(0, (*charKeyHashMap.Find("one")).second);
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType("two", 2));
			Assert::AreEqual("two", (*charKeyHashMap.Find("two")).first);
			Assert::AreEqual(2, (*charKeyHashMap.Find("two")).second);
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType("three", 2));
			Assert::AreEqual("three", (*charKeyHashMap.Find("three")).first);
			Assert::AreEqual(2, (*charKeyHashMap.Find("three")).second);
			charKeyHashMap.Find("invalid");

			// Test using a string as the key type
			HashMap<std::string, std::int32_t> stringKeyHashMap(10);
			std::string stringVals[] = { "one", "two", "three", "invalid" };
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType(stringVals[0], 0));
			Assert::AreEqual(stringVals[0], (*stringKeyHashMap.Find(stringVals[0])).first);
			Assert::AreEqual(0, (*stringKeyHashMap.Find(stringVals[0])).second);
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType(stringVals[1], 2));
			Assert::AreEqual(stringVals[1], (*stringKeyHashMap.Find(stringVals[1])).first);
			Assert::AreEqual(2, (*stringKeyHashMap.Find(stringVals[1])).second);
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType(stringVals[2], 2));
			Assert::AreEqual(stringVals[2], (*stringKeyHashMap.Find(stringVals[2])).first);
			Assert::AreEqual(2, (*stringKeyHashMap.Find(stringVals[2])).second);
			stringKeyHashMap.Find(stringVals[3]);

			// Test using a string as the key type
			HashMap<Foo, std::int32_t, FooHash> fooKeyHashMap(10);
			Foo fooData[] = { Foo(0), Foo(1), Foo(2), Foo(3) };
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(fooData[0], 0));
			Assert::IsTrue(fooData[0] == (*fooKeyHashMap.Find(fooData[0])).first);
			Assert::AreEqual(0, (*fooKeyHashMap.Find(fooData[0])).second);
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(fooData[1], 2));
			Assert::IsTrue(fooData[1] == (*fooKeyHashMap.Find(fooData[1])).first);
			Assert::AreEqual(2, (*fooKeyHashMap.Find(fooData[1])).second);
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(fooData[2], 2));
			Assert::IsTrue(fooData[2] == (*fooKeyHashMap.Find(fooData[2])).first);
			Assert::AreEqual(2, (*fooKeyHashMap.Find(fooData[2])).second);
			fooKeyHashMap.Find(fooData[3]);
		}

		TEST_METHOD(HashMapTestInsert)
		{
			// Test a HashMap with an integer key
			HashMap<std::int32_t, std::int32_t> intKeyHashMap(3);
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(0, 0));
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(1, 1));
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(2, 2));
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(3, 3));
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(4, 0));
			Assert::AreEqual(5U, intKeyHashMap.Size());
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(0, 0));
			Assert::AreEqual(5U, intKeyHashMap.Size());
			intKeyHashMap.Remove(0);
			Assert::AreEqual(4U, intKeyHashMap.Size());
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(0, 0));
			Assert::AreEqual(5U, intKeyHashMap.Size());
			intKeyHashMap.Clear();
			Assert::AreEqual(0U, intKeyHashMap.Size());
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(0, 0));
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(1, 1));
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(5, 5));
			Assert::AreEqual(3U, intKeyHashMap.Size());
			Assert::AreEqual(5, (*intKeyHashMap.Find(5)).second);
			Assert::IsTrue(intKeyHashMap.end() == intKeyHashMap.Find(2));

			// Test a HashMap with a pointer key
			HashMap<std::int32_t*, std::int32_t> pointerKeyHashMap(3);
			std::int32_t pointerKeyData[] = { 0, 1, 2, 3, 4, 5 };
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[0], 0));
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[1], 1));
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[2], 2));
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[3], 3));
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[4], 0));
			Assert::AreEqual(5U, pointerKeyHashMap.Size());
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[0], 0));
			Assert::AreEqual(5U, pointerKeyHashMap.Size());
			pointerKeyHashMap.Remove(&pointerKeyData[0]);
			Assert::AreEqual(4U, pointerKeyHashMap.Size());
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[0], 0));
			Assert::AreEqual(5U, pointerKeyHashMap.Size());
			pointerKeyHashMap.Clear();
			Assert::AreEqual(0U, pointerKeyHashMap.Size());
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[0], 0));
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[1], 1));
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[5], 5));
			Assert::AreEqual(3U, pointerKeyHashMap.Size());
			Assert::AreEqual(5, (*pointerKeyHashMap.Find(&pointerKeyData[5])).second);
			Assert::IsTrue(pointerKeyHashMap.end() == pointerKeyHashMap.Find(&pointerKeyData[2]));

			// Test a HashMap with a char* key
			HashMap<char*, std::int32_t> charKeyHashMap(3);
			char* charKeyData[] = { "zero", "one", "two", "three", "four", "five" };
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType(charKeyData[0], 0));
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType(charKeyData[1], 1));
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType(charKeyData[2], 2));
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType(charKeyData[3], 3));
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType(charKeyData[4], 0));
			Assert::AreEqual(5U, charKeyHashMap.Size());
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType(charKeyData[0], 0));
			Assert::AreEqual(5U, charKeyHashMap.Size());
			charKeyHashMap.Remove(charKeyData[0]);
			Assert::AreEqual(4U, charKeyHashMap.Size());
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType(charKeyData[0], 0));
			Assert::AreEqual(5U, charKeyHashMap.Size());
			charKeyHashMap.Clear();
			Assert::AreEqual(0U, charKeyHashMap.Size());
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType(charKeyData[0], 0));
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType(charKeyData[1], 1));
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType(charKeyData[5], 5));
			Assert::AreEqual(3U, charKeyHashMap.Size());
			Assert::AreEqual(5, (*charKeyHashMap.Find(charKeyData[5])).second);
			Assert::IsTrue(charKeyHashMap.end() == charKeyHashMap.Find(charKeyData[2]));

			// Test a HashMap with a string key
			HashMap<std::string, std::int32_t> stringKeyHashMap(3);
			std::string stringKeyData[] = { "zero", "one", "two", "three", "four", "five" };
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType(stringKeyData[0], 0));
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType(stringKeyData[1], 1));
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType(stringKeyData[2], 2));
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType(stringKeyData[3], 3));
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType(stringKeyData[4], 0));
			Assert::AreEqual(5U, stringKeyHashMap.Size());
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType(stringKeyData[0], 0));
			Assert::AreEqual(5U, stringKeyHashMap.Size());
			stringKeyHashMap.Remove(stringKeyData[0]);
			Assert::AreEqual(4U, stringKeyHashMap.Size());
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType(stringKeyData[0], 0));
			Assert::AreEqual(5U, stringKeyHashMap.Size());
			stringKeyHashMap.Clear();
			Assert::AreEqual(0U, stringKeyHashMap.Size());
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType(stringKeyData[0], 0));
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType(stringKeyData[1], 1));
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType(stringKeyData[5], 5));
			Assert::AreEqual(3U, stringKeyHashMap.Size());
			Assert::AreEqual(5, (*stringKeyHashMap.Find(stringKeyData[5])).second);
			Assert::IsTrue(stringKeyHashMap.end() == stringKeyHashMap.Find(stringKeyData[2]));

			// Test a HashMap with a Foo key
			HashMap<Foo, std::int32_t, FooHash> fooKeyHashMap(3);
			Foo fooKeyData[] = { Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5) };
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(fooKeyData[0], 0));
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(fooKeyData[1], 1));
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(fooKeyData[2], 2));
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(fooKeyData[3], 3));
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(fooKeyData[4], 0));
			Assert::AreEqual(5U, fooKeyHashMap.Size());
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(fooKeyData[0], 0));
			Assert::AreEqual(5U, fooKeyHashMap.Size());
			fooKeyHashMap.Remove(fooKeyData[0]);
			Assert::AreEqual(4U, fooKeyHashMap.Size());
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(fooKeyData[0], 0));
			Assert::AreEqual(5U, fooKeyHashMap.Size());
			fooKeyHashMap.Clear();
			Assert::AreEqual(0U, fooKeyHashMap.Size());
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(fooKeyData[0], 0));
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(fooKeyData[1], 1));
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(fooKeyData[5], 5));
			Assert::AreEqual(3U, fooKeyHashMap.Size());
			Assert::AreEqual(5, (*fooKeyHashMap.Find(fooKeyData[5])).second);
			Assert::IsTrue(fooKeyHashMap.end() == fooKeyHashMap.Find(fooKeyData[2]));
		}

		TEST_METHOD(HashMapTestIndexOperator)
		{
			// Test using an integer as the key type
			HashMap<std::int32_t, std::int32_t> intKeyHashMap(10);
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(0, 0));
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(1, 0));
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(2, 1));
			Assert::AreEqual(0, intKeyHashMap[0]);
			Assert::AreEqual(0, intKeyHashMap[1]);
			Assert::AreEqual(1, intKeyHashMap[2]);
			intKeyHashMap[200];
			Assert::IsTrue(intKeyHashMap.ContainsKey(200));

			// Test using a pointer as the key type
			HashMap<std::int32_t*, std::int32_t> pointerKeyHashMap(10);
			std::int32_t pointerKeyData[] = { 0, 1, 2, 3 };
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[0], 0));
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[1], 0));
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[2], 1));
			Assert::AreEqual(0, pointerKeyHashMap[&pointerKeyData[0]]);
			Assert::AreEqual(0, pointerKeyHashMap[&pointerKeyData[1]]);
			Assert::AreEqual(1, pointerKeyHashMap[&pointerKeyData[2]]);
			pointerKeyHashMap[&pointerKeyData[3]];
			Assert::IsTrue(pointerKeyHashMap.ContainsKey(&pointerKeyData[3]));

			// Test using a char* as the key type
			HashMap<char*, std::int32_t> charKeyHashMap(10);
			char* charKeyData[] = { "zero", "one", "two", "three" };
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType(charKeyData[0], 0));
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType(charKeyData[1], 0));
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType(charKeyData[2], 1));
			Assert::AreEqual(0, charKeyHashMap[charKeyData[0]]);
			Assert::AreEqual(0, charKeyHashMap[charKeyData[1]]);
			Assert::AreEqual(1, charKeyHashMap[charKeyData[2]]);
			charKeyHashMap[charKeyData[3]];
			Assert::IsTrue(charKeyHashMap.ContainsKey(charKeyData[3]));

			// Test using a string as the key type
			HashMap<std::string, std::int32_t> stringKeyHashMap(10);
			std::string stringKeyData[] = { "zero", "one", "two", "three" };
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType(stringKeyData[0], 0));
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType(stringKeyData[1], 0));
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType(stringKeyData[2], 1));
			Assert::AreEqual(0, stringKeyHashMap[stringKeyData[0]]);
			Assert::AreEqual(0, stringKeyHashMap[stringKeyData[1]]);
			Assert::AreEqual(1, stringKeyHashMap[stringKeyData[2]]);
			stringKeyHashMap[stringKeyData[3]];
			Assert::IsTrue(stringKeyHashMap.ContainsKey(stringKeyData[3]));

			// Test using Foo as the key type
			HashMap<Foo, std::int32_t, FooHash> fooKeyHashMap(10);
			Foo fooKeyData[] = { Foo(0), Foo(1), Foo(2), Foo(3) };
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(fooKeyData[0], 0));
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(fooKeyData[1], 0));
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(fooKeyData[2], 1));
			Assert::AreEqual(0, fooKeyHashMap[fooKeyData[0]]);
			Assert::AreEqual(0, fooKeyHashMap[fooKeyData[1]]);
			Assert::AreEqual(1, fooKeyHashMap[fooKeyData[2]]);
			fooKeyHashMap[fooKeyData[3]];
			Assert::IsTrue(fooKeyHashMap.ContainsKey(fooKeyData[3]));
		}

		TEST_METHOD(HashMapTestRemove)
		{
			// Test a HashMap with an integer key
			HashMap<std::int32_t, std::int32_t> intKeyHashMap(3);
			Assert::AreEqual(0U, intKeyHashMap.Size());
			intKeyHashMap.Remove(0);
			Assert::AreEqual(0U, intKeyHashMap.Size());
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(0, 0));
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(1, 1));
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(2, 2));
			Assert::AreEqual(3U, intKeyHashMap.Size());
			intKeyHashMap.Remove(1);
			Assert::AreEqual(2U, intKeyHashMap.Size());
			intKeyHashMap.Remove(0);
			Assert::AreEqual(1U, intKeyHashMap.Size());
			intKeyHashMap.Remove(2);
			Assert::AreEqual(0U, intKeyHashMap.Size());
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(0, 0));
			Assert::AreEqual(1U, intKeyHashMap.Size());
			intKeyHashMap.Remove(0);
			Assert::AreEqual(0U, intKeyHashMap.Size());
			intKeyHashMap.Clear();
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(5, 5));
			Assert::AreEqual(1U, intKeyHashMap.Size());
			Assert::AreEqual(5, (*intKeyHashMap.Find(5)).second);
			intKeyHashMap.Remove(5);
			Assert::IsTrue(intKeyHashMap.end() == intKeyHashMap.Find(5));

			// Test a HashMap with a pointer key
			HashMap<std::int32_t*, std::int32_t> pointerKeyHashMap(3);
			std::int32_t pointerKeyData[] = { 0, 1, 2, 5 };
			Assert::AreEqual(0U, pointerKeyHashMap.Size());
			pointerKeyHashMap.Remove(&pointerKeyData[0]);
			Assert::AreEqual(0U, pointerKeyHashMap.Size());
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[0], 0));
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[1], 1));
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[2], 2));
			Assert::AreEqual(3U, pointerKeyHashMap.Size());
			pointerKeyHashMap.Remove(&pointerKeyData[1]);
			Assert::AreEqual(2U, pointerKeyHashMap.Size());
			pointerKeyHashMap.Remove(&pointerKeyData[0]);
			Assert::AreEqual(1U, pointerKeyHashMap.Size());
			pointerKeyHashMap.Remove(&pointerKeyData[2]);
			Assert::AreEqual(0U, pointerKeyHashMap.Size());
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[0], 0));
			Assert::AreEqual(1U, pointerKeyHashMap.Size());
			pointerKeyHashMap.Remove(&pointerKeyData[0]);
			Assert::AreEqual(0U, pointerKeyHashMap.Size());
			pointerKeyHashMap.Clear();
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[3], 5));
			Assert::AreEqual(1U, pointerKeyHashMap.Size());
			Assert::AreEqual(5, (*pointerKeyHashMap.Find(&pointerKeyData[3])).second);
			pointerKeyHashMap.Remove(&pointerKeyData[3]);
			Assert::IsTrue(pointerKeyHashMap.end() == pointerKeyHashMap.Find(&pointerKeyData[3]));

			// Test a HashMap with a char* key
			HashMap<char*, std::int32_t> charKeyHashMap(3);
			char* charKeyData[] = { "zero", "one", "two", "five" };
			Assert::AreEqual(0U, charKeyHashMap.Size());
			charKeyHashMap.Remove(charKeyData[0]);
			Assert::AreEqual(0U, charKeyHashMap.Size());
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType(charKeyData[0], 0));
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType(charKeyData[1], 1));
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType(charKeyData[2], 2));
			Assert::AreEqual(3U, charKeyHashMap.Size());
			charKeyHashMap.Remove(charKeyData[1]);
			Assert::AreEqual(2U, charKeyHashMap.Size());
			charKeyHashMap.Remove(charKeyData[0]);
			Assert::AreEqual(1U, charKeyHashMap.Size());
			charKeyHashMap.Remove(charKeyData[2]);
			Assert::AreEqual(0U, charKeyHashMap.Size());
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType(charKeyData[0], 0));
			Assert::AreEqual(1U, charKeyHashMap.Size());
			charKeyHashMap.Remove(charKeyData[0]);
			Assert::AreEqual(0U, charKeyHashMap.Size());
			charKeyHashMap.Clear();
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType(charKeyData[3], 5));
			Assert::AreEqual(1U, charKeyHashMap.Size());
			Assert::AreEqual(5, (*charKeyHashMap.Find(charKeyData[3])).second);
			charKeyHashMap.Remove(charKeyData[3]);
			Assert::IsTrue(charKeyHashMap.end() == charKeyHashMap.Find(charKeyData[3]));

			// Test a HashMap with a string key
			HashMap<std::string, std::int32_t> stringKeyHashMap(3);
			std::string stringKeyData[] = { "zero", "one", "two", "five" };
			Assert::AreEqual(0U, stringKeyHashMap.Size());
			stringKeyHashMap.Remove(stringKeyData[0]);
			Assert::AreEqual(0U, stringKeyHashMap.Size());
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType(stringKeyData[0], 0));
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType(stringKeyData[1], 1));
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType(stringKeyData[2], 2));
			Assert::AreEqual(3U, stringKeyHashMap.Size());
			stringKeyHashMap.Remove(stringKeyData[1]);
			Assert::AreEqual(2U, stringKeyHashMap.Size());
			stringKeyHashMap.Remove(stringKeyData[0]);
			Assert::AreEqual(1U, stringKeyHashMap.Size());
			stringKeyHashMap.Remove(stringKeyData[2]);
			Assert::AreEqual(0U, stringKeyHashMap.Size());
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType(stringKeyData[0], 0));
			Assert::AreEqual(1U, stringKeyHashMap.Size());
			stringKeyHashMap.Remove(stringKeyData[0]);
			Assert::AreEqual(0U, stringKeyHashMap.Size());
			stringKeyHashMap.Clear();
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType(stringKeyData[3], 5));
			Assert::AreEqual(1U, stringKeyHashMap.Size());
			Assert::AreEqual(5, (*stringKeyHashMap.Find(stringKeyData[3])).second);
			stringKeyHashMap.Remove(stringKeyData[3]);
			Assert::IsTrue(stringKeyHashMap.end() == stringKeyHashMap.Find(stringKeyData[3]));

			// Test a HashMap with a Foo key
			HashMap<Foo, std::int32_t, FooHash> fooKeyHashMap(3);
			Foo fooKeyData[] = { Foo(0), Foo(1), Foo(2), Foo(5) };
			Assert::AreEqual(0U, fooKeyHashMap.Size());
			fooKeyHashMap.Remove(fooKeyData[0]);
			Assert::AreEqual(0U, fooKeyHashMap.Size());
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(fooKeyData[0], 0));
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(fooKeyData[1], 1));
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(fooKeyData[2], 2));
			Assert::AreEqual(3U, fooKeyHashMap.Size());
			fooKeyHashMap.Remove(fooKeyData[1]);
			Assert::AreEqual(2U, fooKeyHashMap.Size());
			fooKeyHashMap.Remove(fooKeyData[0]);
			Assert::AreEqual(1U, fooKeyHashMap.Size());
			fooKeyHashMap.Remove(fooKeyData[2]);
			Assert::AreEqual(0U, fooKeyHashMap.Size());
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(fooKeyData[0], 0));
			Assert::AreEqual(1U, fooKeyHashMap.Size());
			fooKeyHashMap.Remove(fooKeyData[0]);
			Assert::AreEqual(0U, fooKeyHashMap.Size());
			fooKeyHashMap.Clear();
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(fooKeyData[3], 5));
			Assert::AreEqual(1U, fooKeyHashMap.Size());
			Assert::AreEqual(5, (*fooKeyHashMap.Find(fooKeyData[3])).second);
			fooKeyHashMap.Remove(fooKeyData[3]);
			Assert::IsTrue(fooKeyHashMap.end() == fooKeyHashMap.Find(fooKeyData[3]));
		}

		TEST_METHOD(HashMapTestClear)
		{
			// Test a HashMap with an integer key
			HashMap<std::int32_t, std::int32_t> intKeyHashMap(3);
			intKeyHashMap.Clear();
			Assert::AreEqual(0U, intKeyHashMap.Size());
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(0, 0));
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(1, 1));
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(2, 2));
			Assert::AreEqual(3U, intKeyHashMap.Size());
			intKeyHashMap.Clear();
			Assert::AreEqual(0U, intKeyHashMap.Size());
			Assert::IsTrue(intKeyHashMap.end() == intKeyHashMap.Find(0));

			// Test a HashMap with a pointer key
			HashMap<std::int32_t*, std::int32_t> pointerKeyHashMap(3);
			std::int32_t pointerKeyData[] = { 0, 1, 2 };
			pointerKeyHashMap.Clear();
			Assert::AreEqual(0U, pointerKeyHashMap.Size());
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[0], 0));
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[1], 1));
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[2], 2));
			Assert::AreEqual(3U, pointerKeyHashMap.Size());
			pointerKeyHashMap.Clear();
			Assert::AreEqual(0U, pointerKeyHashMap.Size());
			Assert::IsTrue(pointerKeyHashMap.end() == pointerKeyHashMap.Find(&pointerKeyData[0]));

			// Test a HashMap with a char* key
			HashMap<char*, std::int32_t> charKeyHashMap(3);
			char* charKeyData[] = { "zero", "one", "two", "three", "four", "five" }; 
			charKeyHashMap.Clear();
			Assert::AreEqual(0U, charKeyHashMap.Size());
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType(charKeyData[0], 0));
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType(charKeyData[1], 1));
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType(charKeyData[2], 2));
			Assert::AreEqual(3U, charKeyHashMap.Size());
			charKeyHashMap.Clear();
			Assert::AreEqual(0U, charKeyHashMap.Size());
			Assert::IsTrue(charKeyHashMap.end() == charKeyHashMap.Find(charKeyData[0]));

			// Test a HashMap with a string key
			HashMap<std::string, std::int32_t> stringKeyHashMap(3);
			std::string stringKeyData[] = { "zero", "one", "two", "three", "four", "five" };
			stringKeyHashMap.Clear();
			Assert::AreEqual(0U, stringKeyHashMap.Size());
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType(stringKeyData[0], 0));
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType(stringKeyData[1], 1));
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType(stringKeyData[2], 2));
			Assert::AreEqual(3U, stringKeyHashMap.Size());
			stringKeyHashMap.Clear();
			Assert::AreEqual(0U, stringKeyHashMap.Size());
			Assert::IsTrue(stringKeyHashMap.end() == stringKeyHashMap.Find(stringKeyData[0]));

			// Test a HashMap with a Foo key
			HashMap<Foo, std::int32_t, FooHash> fooKeyHashMap(3);
			Foo fooKeyData[] = { Foo(0), Foo(1), Foo(2) };
			fooKeyHashMap.Clear();
			Assert::AreEqual(0U, fooKeyHashMap.Size());
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(fooKeyData[0], 0));
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(fooKeyData[1], 1));
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(fooKeyData[2], 2));
			Assert::AreEqual(3U, fooKeyHashMap.Size());
			fooKeyHashMap.Clear();
			Assert::AreEqual(0U, fooKeyHashMap.Size());
			Assert::IsTrue(fooKeyHashMap.end() == fooKeyHashMap.Find(fooKeyData[0]));
		}

		TEST_METHOD(HashMapTestSize)
		{
			// Test a HashMap with an integer key
			HashMap<std::int32_t, std::int32_t> intKeyHashMap(3);
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(0, 0));
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(1, 1));
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(2, 2));
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(3, 3));
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(4, 0));
			Assert::AreEqual(5U, intKeyHashMap.Size());
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(0, 0));
			Assert::AreEqual(5U, intKeyHashMap.Size());
			intKeyHashMap.Remove(0);
			Assert::AreEqual(4U, intKeyHashMap.Size());
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(0, 0));
			Assert::AreEqual(5U, intKeyHashMap.Size());
			intKeyHashMap.Clear();
			Assert::AreEqual(0U, intKeyHashMap.Size());
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(0, 0));
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(1, 1));
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(5, 5));
			Assert::AreEqual(3U, intKeyHashMap.Size());

			// Test a HashMap with a pointer key
			HashMap<std::int32_t*, std::int32_t> pointerKeyHashMap(3);
			std::int32_t pointerKeyData[] = { 0, 1, 2, 3, 4, 5 };
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[0], 0));
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[1], 1));
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[2], 2));
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[3], 3));
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[4], 0));
			Assert::AreEqual(5U, pointerKeyHashMap.Size());
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[0], 0));
			Assert::AreEqual(5U, pointerKeyHashMap.Size());
			pointerKeyHashMap.Remove(&pointerKeyData[0]);
			Assert::AreEqual(4U, pointerKeyHashMap.Size());
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[0], 0));
			Assert::AreEqual(5U, pointerKeyHashMap.Size());
			pointerKeyHashMap.Clear();
			Assert::AreEqual(0U, pointerKeyHashMap.Size());
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[0], 0));
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[1], 1));
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[5], 5));
			Assert::AreEqual(3U, pointerKeyHashMap.Size());

			// Test a HashMap with a char* key
			HashMap<char*, std::int32_t> charKeyHashMap(3);
			char* charKeyData[] = { "zero", "one", "two", "three", "four", "five" };
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType(charKeyData[0], 0));
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType(charKeyData[1], 1));
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType(charKeyData[2], 2));
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType(charKeyData[3], 3));
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType(charKeyData[4], 0));
			Assert::AreEqual(5U, charKeyHashMap.Size());
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType(charKeyData[0], 0));
			Assert::AreEqual(5U, charKeyHashMap.Size());
			charKeyHashMap.Remove(charKeyData[0]);
			Assert::AreEqual(4U, charKeyHashMap.Size());
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType(charKeyData[0], 0));
			Assert::AreEqual(5U, charKeyHashMap.Size());
			charKeyHashMap.Clear();
			Assert::AreEqual(0U, charKeyHashMap.Size());
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType(charKeyData[0], 0));
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType(charKeyData[1], 1));
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType(charKeyData[5], 5));
			Assert::AreEqual(3U, charKeyHashMap.Size());

			// Test a HashMap with a string key
			HashMap<std::string, std::int32_t> stringKeyHashMap(3);
			std::string stringKeyData[] = { "zero", "one", "two", "three", "four", "five" };
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType(stringKeyData[0], 0));
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType(stringKeyData[1], 1));
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType(stringKeyData[2], 2));
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType(stringKeyData[3], 3));
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType(stringKeyData[4], 0));
			Assert::AreEqual(5U, stringKeyHashMap.Size());
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType(stringKeyData[0], 0));
			Assert::AreEqual(5U, stringKeyHashMap.Size());
			stringKeyHashMap.Remove(stringKeyData[0]);
			Assert::AreEqual(4U, stringKeyHashMap.Size());
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType(stringKeyData[0], 0));
			Assert::AreEqual(5U, stringKeyHashMap.Size());
			stringKeyHashMap.Clear();
			Assert::AreEqual(0U, stringKeyHashMap.Size());
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType(stringKeyData[0], 0));
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType(stringKeyData[1], 1));
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType(stringKeyData[5], 5));
			Assert::AreEqual(3U, stringKeyHashMap.Size());

			// Test a HashMap with a Foo key
			HashMap<Foo, std::int32_t, FooHash> fooKeyHashMap(3);
			Foo fooKeyData[] = { Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5) };
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(fooKeyData[0], 0));
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(fooKeyData[1], 1));
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(fooKeyData[2], 2));
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(fooKeyData[3], 3));
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(fooKeyData[4], 0));
			Assert::AreEqual(5U, fooKeyHashMap.Size());
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(fooKeyData[0], 0));
			Assert::AreEqual(5U, fooKeyHashMap.Size());
			fooKeyHashMap.Remove(fooKeyData[0]);
			Assert::AreEqual(4U, fooKeyHashMap.Size());
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(fooKeyData[0], 0));
			Assert::AreEqual(5U, fooKeyHashMap.Size());
			fooKeyHashMap.Clear();
			Assert::AreEqual(0U, fooKeyHashMap.Size());
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(fooKeyData[0], 0));
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(fooKeyData[1], 1));
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(fooKeyData[5], 5));
			Assert::AreEqual(3U, fooKeyHashMap.Size());
		}

		TEST_METHOD(HashMapTestContansKey)
		{
			// Test with an integer key
			HashMap<std::int32_t, std::int32_t> intKeyHashMap(10);
			Assert::IsFalse(intKeyHashMap.ContainsKey(0));
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(0, 0));
			Assert::IsTrue(intKeyHashMap.ContainsKey(0));

			// Test with a pointer key
			HashMap<std::int32_t*, std::int32_t> pointerKeyHashMap(10);
			std::int32_t* pointer = 0;
			Assert::IsFalse(pointerKeyHashMap.ContainsKey(pointer));
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(pointer, 0));
			Assert::IsTrue(pointerKeyHashMap.ContainsKey(pointer));

			// Test with a char* key
			HashMap<char*, std::int32_t> charKeyHashMap(10);
			Assert::IsFalse(charKeyHashMap.ContainsKey("key"));
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType("key", 0));
			Assert::IsTrue(charKeyHashMap.ContainsKey("key"));

			// Test with a string key
			HashMap<std::string, std::int32_t> stringKeyHashMap(10);
			Assert::IsFalse(stringKeyHashMap.ContainsKey("key"));
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType("key", 0));
			Assert::IsTrue(stringKeyHashMap.ContainsKey("key"));

			// Test with a Foo key
			HashMap<Foo, std::int32_t, FooHash> fooKeyHashMap(10);
			Foo f(0);
			Assert::IsFalse(fooKeyHashMap.ContainsKey(f));
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(f, 0));
			Assert::IsTrue(fooKeyHashMap.ContainsKey(f));
		}

		TEST_METHOD(HashMapTestBegin)
		{
			// Test with an integer key
			HashMap<std::int32_t, std::int32_t> intKeyHashMap(10);
			Assert::IsTrue(intKeyHashMap.end() == intKeyHashMap.begin());
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(0, 0));
			Assert::AreEqual(0, (*intKeyHashMap.begin()).first);
			Assert::AreEqual(0, (*intKeyHashMap.begin()).second);
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(1, 1));
			Assert::IsFalse(intKeyHashMap.end() == intKeyHashMap.begin());

			// Test with a pointer key
			HashMap<std::int32_t*, std::int32_t> pointerKeyHashMap(10);
			std::int32_t pointerKeyData[] = { 0, 1 };
			Assert::IsTrue(pointerKeyHashMap.end() == pointerKeyHashMap.begin());
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[0], 0));
			Assert::AreEqual(&pointerKeyData[0], (*pointerKeyHashMap.begin()).first);
			Assert::AreEqual(0, (*pointerKeyHashMap.begin()).second);
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[0], 1));
			Assert::IsFalse(pointerKeyHashMap.end() == pointerKeyHashMap.begin());

			// Test with a char* key
			HashMap<char*, std::int32_t> charKeyHashMap(10);
			char* charKeyData[] = { "zero", "one" };
			Assert::IsTrue(charKeyHashMap.end() == charKeyHashMap.begin());
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType(charKeyData[0], 0));
			Assert::AreEqual(charKeyData[0], (*charKeyHashMap.begin()).first);
			Assert::AreEqual(0, (*charKeyHashMap.begin()).second);
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType(charKeyData[0], 1));
			Assert::IsFalse(charKeyHashMap.end() == charKeyHashMap.begin());

			// Test with a string key
			HashMap<std::string, std::int32_t> stringKeyHashMap(10);
			std::string stringKeyData[] = { "zero", "one" };
			Assert::IsTrue(stringKeyHashMap.end() == stringKeyHashMap.begin());
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType(stringKeyData[0], 0));
			Assert::AreEqual(stringKeyData[0], (*stringKeyHashMap.begin()).first);
			Assert::AreEqual(0, (*stringKeyHashMap.begin()).second);
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType(stringKeyData[0], 1));
			Assert::IsFalse(stringKeyHashMap.end() == stringKeyHashMap.begin());

			// Test with a Foo key
			HashMap<Foo, std::int32_t, FooHash> fooKeyHashMap(10);
			Foo fooKeyData[] = { Foo(0), Foo(1) };
			Assert::IsTrue(fooKeyHashMap.end() == fooKeyHashMap.begin());
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(fooKeyData[0], 0));
			Assert::IsTrue(fooKeyData[0] == (*fooKeyHashMap.begin()).first);
			Assert::AreEqual(0, (*fooKeyHashMap.begin()).second);
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(fooKeyData[0], 1));
			Assert::IsFalse(fooKeyHashMap.end() == fooKeyHashMap.begin());
		}

		TEST_METHOD(HashMapTestEnd)
		{
			// Test with an integer key
			HashMap<std::int32_t, std::int32_t> intKeyHashMap(10);
			Assert::IsTrue(intKeyHashMap.end() == intKeyHashMap.begin());
			intKeyHashMap.Insert(HashMap<std::int32_t, std::int32_t>::PairType(0, 0));
			Assert::IsFalse(intKeyHashMap.end() == intKeyHashMap.begin());

			// Test with a pointer key
			HashMap<std::int32_t*, std::int32_t> pointerKeyHashMap(10);
			std::int32_t pointerKeyData[] = { 0, 1 };
			Assert::IsTrue(pointerKeyHashMap.end() == pointerKeyHashMap.begin());
			pointerKeyHashMap.Insert(HashMap<std::int32_t*, std::int32_t>::PairType(&pointerKeyData[0], 0));
			Assert::IsFalse(pointerKeyHashMap.end() == pointerKeyHashMap.begin());

			// Test with a char* key
			HashMap<char*, std::int32_t> charKeyHashMap(10);
			char* charKeyData[] = { "zero", "one" };
			Assert::IsTrue(charKeyHashMap.end() == charKeyHashMap.begin());
			charKeyHashMap.Insert(HashMap<char*, std::int32_t>::PairType(charKeyData[0], 0));
			Assert::IsFalse(charKeyHashMap.end() == charKeyHashMap.begin());

			// Test with a string key
			HashMap<std::string, std::int32_t> stringKeyHashMap(10);
			std::string stringKeyData[] = { "zero", "one" };
			Assert::IsTrue(stringKeyHashMap.end() == stringKeyHashMap.begin());
			stringKeyHashMap.Insert(HashMap<std::string, std::int32_t>::PairType(stringKeyData[0], 0));
			Assert::IsFalse(stringKeyHashMap.end() == stringKeyHashMap.begin());

			// Test with a Foo key
			HashMap<Foo, std::int32_t, FooHash> fooKeyHashMap(10);
			Foo fooKeyData[] = { Foo(0), Foo(1) };
			Assert::IsTrue(fooKeyHashMap.end() == fooKeyHashMap.begin());
			fooKeyHashMap.Insert(HashMap<Foo, std::int32_t>::PairType(fooKeyData[0], 0));
			Assert::IsFalse(fooKeyHashMap.end() == fooKeyHashMap.begin());
		}

	private:
#if defined(DEBUG) | defined(_DEBUG)
		static _CrtMemState sStartMemState;
#endif

	};

#if defined(DEBUG) | defined(_DEBUG)
	_CrtMemState HashMapTest::sStartMemState;
#endif

}