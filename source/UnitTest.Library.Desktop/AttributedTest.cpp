#include "pch.h"
#include "AttributedFoo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(AttributedTest)
	{
	public:

//#if defined(DEBUG) | defined(_DEBUG)
//		TEST_METHOD_INITIALIZE(Initialize)
//		{
//			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
//			_CrtMemCheckpoint(&sStartMemState);
//		}
//		
//		TEST_METHOD_CLEANUP(Cleanup)
//		{
//			_CrtMemState endMemState, diffMemState;
//			_CrtMemCheckpoint(&endMemState);
//			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
//			{
//				_CrtMemDumpStatistics(&diffMemState);
//				Assert::Fail(L"Memory Leaks!");
//			}
//		}
//#endif

		TEST_METHOD(AttributedTestConstructor)
		{
			AttributedFoo foo;
			Assert::AreEqual(14U, foo.Size());
		}

		TEST_METHOD(AttributedTestCopy)
		{
			AttributedFoo existingFoo;
			Assert::AreEqual(14U, existingFoo.Size());

			AttributedFoo newConstructorFoo = existingFoo;
			Assert::AreEqual(existingFoo.Size(), newConstructorFoo.Size());

			AttributedFoo newAssignmentFoo;
			newAssignmentFoo = existingFoo;
			Assert::AreEqual(existingFoo.Size(), newAssignmentFoo.Size());
		}

		TEST_METHOD(AttributedTestPopulate)
		{
			AttributedFoo foo;
			// Note: AttributedFoo calls Populate on each type (for both internal and external) in the constructor
			Assert::AreEqual(14U, foo.Size());
		}

		TEST_METHOD(AttributedTestIsPrescribedAttribute)
		{
			AttributedFoo foo;
			Assert::IsTrue(foo.IsPrescribedAttribute("this"));
			Assert::IsTrue(foo.IsPrescribedAttribute("Internal Integer"));
			Assert::IsTrue(foo.IsPrescribedAttribute("Internal Float"));
			Assert::IsTrue(foo.IsPrescribedAttribute("Internal Vector"));
			Assert::IsTrue(foo.IsPrescribedAttribute("Internal Matrix"));
			Assert::IsTrue(foo.IsPrescribedAttribute("Internal Table"));
			Assert::IsTrue(foo.IsPrescribedAttribute("Internal String"));
			Assert::IsTrue(foo.IsPrescribedAttribute("Internal Pointer"));
			Assert::IsTrue(foo.IsPrescribedAttribute("External Integer"));
			Assert::IsTrue(foo.IsPrescribedAttribute("External Float"));
			Assert::IsTrue(foo.IsPrescribedAttribute("External Vector"));
			Assert::IsTrue(foo.IsPrescribedAttribute("External Matrix"));
			Assert::IsTrue(foo.IsPrescribedAttribute("External String"));
			Assert::IsTrue(foo.IsPrescribedAttribute("External Pointer"));
			Assert::IsFalse(foo.IsPrescribedAttribute("DoesNotExist"));
		}

		TEST_METHOD(AttributedTestIsAuxiliaryAttribute)
		{
			AttributedFoo foo;
			Assert::IsFalse(foo.IsAuxiliaryAttribute("this"));
			Assert::IsFalse(foo.IsAuxiliaryAttribute("Internal Integer"));
			Assert::IsFalse(foo.IsAuxiliaryAttribute("Internal Float"));
			Assert::IsFalse(foo.IsAuxiliaryAttribute("Internal Vector"));
			Assert::IsFalse(foo.IsAuxiliaryAttribute("Internal Matrix"));
			Assert::IsFalse(foo.IsAuxiliaryAttribute("Internal Table"));
			Assert::IsFalse(foo.IsAuxiliaryAttribute("Internal String"));
			Assert::IsFalse(foo.IsAuxiliaryAttribute("Internal Pointer"));
			Assert::IsFalse(foo.IsAuxiliaryAttribute("External Integer"));
			Assert::IsFalse(foo.IsAuxiliaryAttribute("External Float"));
			Assert::IsFalse(foo.IsAuxiliaryAttribute("External Vector"));
			Assert::IsFalse(foo.IsAuxiliaryAttribute("External Matrix"));
			Assert::IsFalse(foo.IsAuxiliaryAttribute("External String"));
			Assert::IsFalse(foo.IsAuxiliaryAttribute("External Pointer"));
			Assert::IsFalse(foo.IsAuxiliaryAttribute("DoesNotExist"));
			foo.AppendAuxiliaryAttribute("NewAuxAttrib");
			Assert::IsTrue(foo.IsAuxiliaryAttribute("NewAuxAttrib"));
		}

		TEST_METHOD(AttributedTestIsAttribute)
		{
			AttributedFoo foo;
			Assert::IsTrue(foo.IsAttribute("this"));
			Assert::IsTrue(foo.IsAttribute("Internal Integer"));
			Assert::IsTrue(foo.IsAttribute("Internal Float"));
			Assert::IsTrue(foo.IsAttribute("Internal Vector"));
			Assert::IsTrue(foo.IsAttribute("Internal Matrix"));
			Assert::IsTrue(foo.IsAttribute("Internal Table"));
			Assert::IsTrue(foo.IsAttribute("Internal String"));
			Assert::IsTrue(foo.IsAttribute("Internal Pointer"));
			Assert::IsTrue(foo.IsAttribute("External Integer"));
			Assert::IsTrue(foo.IsAttribute("External Float"));
			Assert::IsTrue(foo.IsAttribute("External Vector"));
			Assert::IsTrue(foo.IsAttribute("External Matrix"));
			Assert::IsTrue(foo.IsAttribute("External String"));
			Assert::IsTrue(foo.IsAttribute("External Pointer"));
			Assert::IsFalse(foo.IsAttribute("DoesNotExist"));
			foo.AppendAuxiliaryAttribute("NewAuxAttrib");
			Assert::IsTrue(foo.IsAuxiliaryAttribute("NewAuxAttrib"));
		}

		TEST_METHOD(AttributedTestAppendAuxiliaryAttribute)
		{
			AttributedFoo foo;
			Assert::AreEqual(14U, foo.Size());
			foo.AppendAuxiliaryAttribute("NewAuxAttrib");
			Assert::AreEqual(15U, foo.Size());
			Assert::IsTrue(foo.IsAuxiliaryAttribute("NewAuxAttrib"));
		}

		TEST_METHOD(AttributedTestAuxiliaryBegin)
		{
			AttributedFoo foo;
			Assert::AreEqual(14U, foo.Size());
			Assert::AreEqual(14U, foo.AuxiliaryBegin());
			foo.AppendAuxiliaryAttribute("NewAuxAttrib");
			Assert::AreEqual(15U, foo.Size());
			Assert::AreEqual(14U, foo.AuxiliaryBegin());
			foo.AppendAuxiliaryAttribute("NewAuxAttrib2");
			Assert::AreEqual(16U, foo.Size());
			Assert::AreEqual(14U, foo.AuxiliaryBegin());
		}

	private:
#if defined(DEBUG) | defined(_DEBUG)
		static _CrtMemState sStartMemState;
#endif

	};

#if defined(DEBUG) | defined(_DEBUG)
	_CrtMemState AttributedTest::sStartMemState;
#endif

}
