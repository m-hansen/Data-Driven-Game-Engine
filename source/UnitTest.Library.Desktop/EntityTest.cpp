#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Library;

namespace UnitTestLibraryDesktop
{
	ConcreteFactory(Entity, RTTI)

	TEST_CLASS(EntityTest)
	{
	public:
		TEST_METHOD(EntityTestConstructor)
		{
			World world1("World1");
			Assert::IsTrue(world1.Name() == "World1");
			Assert::AreEqual(0U, world1.EventQueue().Size());

			Sector sector1("Sector1");
			Assert::IsTrue(sector1.Name() == "Sector1");

			Entity entity1("Entity1");
			Assert::IsTrue(entity1.Name() == "Entity1");

			// Test copy constructor and assignment operator
			Entity entity2(entity1);
			Assert::IsTrue(entity2.Name() == "Entity1");

			Entity entity3("Entity3");
			entity3 = entity1;
			Assert::IsTrue(entity3.Name() == "Entity1");
		}

		TEST_METHOD(ActionTestRtti)
		{
			World world1("World1");
			Assert::IsTrue(world1.Is("World"));
			Assert::IsTrue(world1.Is(World::TypeIdClass()));
			Assert::IsNotNull(world1.As<World>());
			Assert::IsTrue(world1.TypeName() == "World");

			Sector sector1("Sector1");
			Assert::IsTrue(sector1.Is("Sector"));
			Assert::IsTrue(sector1.Is(Sector::TypeIdClass()));
			Assert::IsNotNull(sector1.As<Sector>());
			Assert::IsTrue(sector1.TypeName() == "Sector");

			Entity entity1("Entity1");
			Assert::IsTrue(entity1.Is("Entity"));
			Assert::IsTrue(entity1.Is(Entity::TypeIdClass()));
			Assert::IsNotNull(entity1.As<Entity>());
			Assert::IsTrue(entity1.TypeName() == "Entity");
		}

		TEST_METHOD(EntityTestName)
		{
			// Test the get/set name for entities
			std::string entityName = "Monster";
			std::string entityName2 = "Monster2";
			Entity entity(entityName);
			Assert::IsTrue(entity.Name() == entityName);
			entity.SetName(entityName2);
			Assert::IsTrue(entity.Name() == entityName2);

			// Test the get/set name for sectors
			std::string sectorName = "Sector1";
			std::string newSectorName = "NewSector1";
			Sector sector(sectorName);
			Assert::IsTrue(sector.Name() == sectorName);
			sector.SetName(newSectorName);
			Assert::IsTrue(sector.Name() == newSectorName);

			// Test the get/set name for worlds
			std::string worldName = "World1";
			std::string newWorldName = "newWorld1";
			World world(worldName);
			Assert::IsTrue(world.Name() == worldName);
			world.SetName(newWorldName);
			Assert::IsTrue(world.Name() == newWorldName);
		}

		TEST_METHOD(EntityTestSector)
		{
			Sector sector("Sector1");

			Entity entity("Entity1");
			entity.SetSector(sector);
			Assert::IsTrue(entity.GetSector().Name() == sector.Name());

			Entity entityNoSector("InvalidEntity");
			Assert::ExpectException<std::exception>([&] { entityNoSector.GetSector().Name(); });
		}

		TEST_METHOD(EntityTestActions)
		{
			FooActionFactory fooActionFactory;
			EntityFactory factory;
			Entity entity("Entity1");
			Assert::AreEqual(0U, entity.Actions().Size());
			Assert::IsTrue(entity.CreateAction("FooAction", "FooAction_1").Name() == "FooAction_1");
			Assert::AreEqual(1U, entity.Actions().Size());
			Assert::IsTrue(entity.CreateAction("FooAction", "FooAction_2").Name() == "FooAction_2");
			Assert::AreEqual(2U, entity.Actions().Size());

			std::uint32_t actionCount = 0;
			for (; actionCount < entity.Actions().Size(); ++actionCount)
			{
				// Intentionally left blank
			}
			Assert::AreEqual(entity.Actions().Size(), actionCount);
		}

		TEST_METHOD(EntityTestCreateAction)
		{
			FooActionFactory actionFactory;
			Entity entity("Entity1");
			Assert::AreEqual(0U, entity.Actions().Size());
			Assert::IsTrue(entity.CreateAction("FooAction", "FooAction_1").Name() == "FooAction_1");
			Assert::AreEqual(1U, entity.Actions().Size());
		}

		TEST_METHOD(EntityTestCreateSector)
		{
			//SectorFactory sectorFactory;
			World world1("World1");
			world1.CreateSector("NewSector");
		}

		TEST_METHOD(EntityTestUpdate)
		{
			Library::WorldState state;

			Entity entity("Monster");
			entity.Update(state);
		
			Sector sector("Sector1");
			sector.Update(state);

			World world("World1");
			world.Update(state);
		}

		TEST_METHOD(EntityTestSectorGetSetWorld)
		{
			World world("World1");
			Sector sector("Sector1");
			sector.SetWorld(world);
			Assert::IsTrue(sector.GetWorld()->Name() == world.Name());
		}

		TEST_METHOD(EntityTestSectorEntities)
		{
			EntityFactory entityFactory;
			Sector sector("Sector1");

			Entity entity1("Entity1");
			Entity entity2("Entity2");
			Entity entity3("Entity3");

			entity1.SetSector(sector);
			entity2.SetSector(sector);
			entity3.SetSector(sector);

			Assert::AreEqual(3U, sector.Entities().Size());

			Sector sector2("Sector2");
			sector2.CreateEntity("Entity", "EntityInSector2");
			Assert::AreEqual(1U, sector2.Entities().Size());
		}

		TEST_METHOD(EntityTestSectorCreateEntity)
		{
			EntityFactory entityFactory;
			Sector sector("Sector1");
			Entity& entity = sector.CreateEntity("Entity", "NewFooEntity");
			Assert::IsTrue(entity.GetSector().Name() == "Sector1");
			Assert::IsTrue(entity.Name() == "NewFooEntity");
		}

		TEST_METHOD(EntityTestWorldSectors)
		{
			World world("World1");

			Sector sector1("Sector1");
			Sector sector2("Sector2");
			Sector sector3("Sector3");

			sector1.SetWorld(world);
			sector2.SetWorld(world);
			sector3.SetWorld(world);

			Assert::AreEqual(3U, world.Sectors().Size());

			World world2("World2");
			world2.CreateSector("SectorForWorld2");
			Assert::AreEqual(1U, world2.Sectors().Size());
		}

		TEST_METHOD(EntityTestWorldCreateSector)
		{
			//SectorFactory sectorFactory;
			World world("World1");
			Sector& sector = world.CreateSector("NewSector");
			Assert::IsTrue(sector.Name() == "NewSector");
		}

	private:
#if defined(DEBUG) | defined(_DEBUG)
		static _CrtMemState sStartMemState;
#endif

	};

#if defined(DEBUG) | defined(_DEBUG)
	_CrtMemState EntityTest::sStartMemState;
#endif

}
