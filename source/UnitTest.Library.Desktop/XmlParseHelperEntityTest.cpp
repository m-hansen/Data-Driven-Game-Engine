#include "pch.h"
#include "FooEntity.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;

namespace UnitTestLibraryDesktop
{
	ConcreteFactory(FooEntity, Library::RTTI)

	TEST_CLASS(XmlParseHelperEntityTest)
	{
	public:

		TEST_METHOD(XmlParseHelperEntityTestConstructor)
		{
			XmlParseMaster::SharedData* sharedData = new XmlParseMaster::SharedData();
			XmlParseMaster parser(sharedData);
			Assert::IsFalse(parser.IsClone());
			Assert::IsTrue(parser.GetFileName() == "");
			delete sharedData;
		}

		TEST_METHOD(XmlParseHelperEntityTestRtti)
		{
			Scope globalScope;
			XmlParseHelperEntity::SharedData tableSharedData(globalScope);
			XmlParseMaster parser(&tableSharedData);
			XmlParseHelperEntity entityHelper;
			parser.AddHelper(entityHelper);

			Assert::IsTrue(tableSharedData.Is("SharedData"));
			Assert::IsNotNull(tableSharedData.As<XmlParseHelperEntity::SharedData>());
			Assert::IsTrue(tableSharedData.TypeName() == "SharedData");
		}

		TEST_METHOD(XmlParseHelperEntityTestParse)
		{
			FooEntityFactory entityFactory;

			Scope globalScope;
			XmlParseHelperEntity::SharedData entitySharedData(globalScope);
			XmlParseMaster parser(&entitySharedData);

			XmlParseHelperEntity entityHelper;
			parser.AddHelper(entityHelper);

			XmlParseHelperTable tableHelper;
			parser.AddHelper(tableHelper);

			parser.ParseFromFile("Content/Entity.xml");
			Assert::IsTrue(parser.GetFileName() == "Content/Entity.xml");

			Datum* foundWorld = globalScope.Find("World1");
			Assert::IsNotNull(foundWorld);
			Scope* worldScope = foundWorld->Get<Scope*>(0);
			Assert::IsTrue(worldScope->As<World>()->Name() == "World1");

			// Sector 1
			Datum* foundFirstSector = worldScope->Find("Sector1");
			Assert::IsNotNull(foundFirstSector);
			Scope* sector1 = foundFirstSector->Get<Scope*>(0);
			Assert::IsTrue(sector1->As<Sector>()->Name() == "Sector1");

			Datum* foundFirstEntity = sector1->Find("Entity1");
			Assert::IsNotNull(foundFirstEntity);
			Scope* entity1 = foundFirstEntity->Get<Scope*>(0);
			Assert::IsTrue(entity1->As<Entity>()->Name() == "Entity1");
			Datum* foundFirstEntityHealth = entity1->Find("Health");
			Assert::IsNotNull(foundFirstEntityHealth);
			Assert::AreEqual(10, foundFirstEntityHealth->Get<std::int32_t>(0));

			// Sector 2
			Datum* foundSecondSector = worldScope->Find("Sector2");
			Assert::IsNotNull(foundSecondSector);
			Scope* sector2 = foundSecondSector->Get<Scope*>(0);
			Assert::IsTrue(sector2->As<Sector>()->Name() == "Sector2");

			Datum* foundSecondEntity = sector2->Find("Entity2");
			Assert::IsNotNull(foundSecondEntity);
			Scope* entity2 = foundSecondEntity->Get<Scope*>(0);
			Assert::IsTrue(entity2->As<Entity>()->Name() == "Entity2");
			
			Datum* foundSecondEntityHealth = entity2->Find("Health");
			Assert::IsNotNull(foundSecondEntityHealth);
			Assert::AreEqual(20, foundSecondEntityHealth->Get<std::int32_t>(0));

			Datum* foundSecondEntityMana = entity2->Find("Mana");
			Assert::IsNotNull(foundSecondEntityMana);
			Assert::AreEqual(50, foundSecondEntityMana->Get<std::int32_t>(0));

			Datum* foundSecondEntityDescription = entity2->Find("Description");
			Assert::IsNotNull(foundSecondEntityDescription);
			Assert::IsTrue(foundSecondEntityDescription->Get<std::string>(0) == "An entity.");
		}

		TEST_METHOD(XmlParseHelperEntityTestParseInvalid)
		{
			Scope globalScope;
			XmlParseHelperEntity::SharedData tableSharedData(globalScope);
			XmlParseMaster parser(&tableSharedData);
			XmlParseHelperEntity entityHelper;

			parser.AddHelper(entityHelper);
			Assert::ExpectException<std::exception>([&] { parser.ParseFromFile("Content/Invalid.xml"); });
		}

		TEST_METHOD(XmlParseHelperEntityTestClone)
		{
			Scope globalScope;
			XmlParseHelperEntity entityHelper;
			XmlParseHelperEntity::SharedData tableSharedData(globalScope);
			XmlParseMaster parser(&tableSharedData);
			parser.AddHelper(entityHelper);

			// Test XmlParseHelperEntity Clone()
			XmlParseHelperEntity* clonedTable = entityHelper.Clone();
			Assert::IsTrue(clonedTable->IsClone());
			Assert::IsFalse(entityHelper.IsClone());
			delete clonedTable;

			// Test XmlParseHelperEntity::SharedData Clone()
			XmlParseHelperEntity::SharedData* clonedTableSharedData = tableSharedData.Clone();
			Assert::IsTrue(clonedTableSharedData->IsClone());
			Assert::IsFalse(tableSharedData.IsClone());
			delete clonedTableSharedData;
		}

	private:
#if defined(DEBUG) | defined(_DEBUG)
		static _CrtMemState sStartMemState;
#endif

	};

#if defined(DEBUG) | defined(_DEBUG)
	_CrtMemState XmlParseHelperEntityTest::sStartMemState;
#endif

}