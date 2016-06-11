#pragma once

#include <cstdint>
#include <string>
#include "HashMap.h"

namespace Library
{
	/**
	 * The Factory class is both an interface and a manager. Our configuration language allows us to express 
	 * the intention of creating objects, based on the name of their type. The Abstract Factory design pattern 
	 * accomplishes this goal.
	 */
	template<typename AbstractProductT>
	class Factory
	{
	public:
		typedef typename HashMap<std::string, const Factory* const>::Iterator Iterator;

		/**
		 * Deconstructor.
		 */
		virtual ~Factory() = default;

		/**
		 * Return the address of a concrete product associated with this concrete factory class.
		 *
		 * @return the address of a concrete product
		 */
		virtual AbstractProductT* Create() const = 0;

		/**
		 * Return a string representing the name of the class the factory instantiates.
		 *
		 * @return a string representing the name of the class the factory instantiates
		 */
		virtual const std::string& ClassName() const = 0;

		/**
		 * Given a class name as a string, return the associated concrete factory.
		 *
		 * @param name string representing the class name
		 * @return the associated concrete Factory
		 */
		static const Factory* const Find(const std::string& name);

		/**
		 * Given a class name as a string, return a new object of that type.
		 *
		 * @param name string representing the class name
		 * @return address of a new abstract product
		 */
		static AbstractProductT* Create(const std::string& name);

		/**
		 * Return an iterator for the container of factories.
		 *
		 * @return an iterator for the container of factories
		 */
		static Iterator begin();

		/**
		 * Return an iterator one past the last factory in the container.
		 *
		 * @return an iterator one past the last factory in the container
		 */
		static Iterator end();

		/**
		 * Return the number of contained factories.
		 * 
		 * @return the number of contained factories
		 */
		static std::uint32_t Size();

		/**
		 * Return whether there are no contained factories.
		 *
		 * @return true if there are no contained factories, false otherwise.
		 */
		static bool IsEmpty();

	protected:
		/**
		 * Given a reference to a concrete factory, add it to the list of factories for this abstract factory.
		 *
		 * @param factory the factory to add
		 */
		static void Add(Factory& factory);

		/**
		 * Given a reference to a concrete factory, remove it from the list of factories for this abstract factory.
		 *
		 * @parama factory the factory to remove
		 */
		static void Remove(const Factory& factory);

	private:
		static HashMap<std::string, const Factory* const> sFactoryTable; /**< The static table of factories */
	};
}

#include "Factory.inl"
