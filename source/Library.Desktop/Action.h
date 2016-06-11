#pragma once

#include "RTTI.h"
#include "Attributed.h"
#include "Factory.h"

namespace Library
{
	class Entity;

	class Action : public Attributed
	{
		RTTI_DECLARATIONS(Action, Attributed)

	public:
		/**
		* Default constructor.
		*
		* @param name (optional) the name of the Action
		*/
		Action(const std::string& name = "");

		// Prevent Action from being moved or copied
		Action(const Action& rhs) = delete;
		Action(Action&& rhs) = delete;
		Action& operator=(const Action& rhs) = delete;

		/**
		* Default deconstructor.
		*/
		virtual ~Action() = default;

		/**
		* Updates each Action.
		*
		* @param state the WorldState
		*/
		virtual void Update(WorldState& state) = 0;

		/**
		* Returns the name of the Action.
		*
		* @return the name of the Action
		*/
		const std::string& Name() const;

		/**
		* Sets the name of the Action.
		*
		* @param name the name of the Action
		*/
		void SetName(const std::string& name);

		void SetEntity(Entity& entity);

	private:
		std::string mName;			/**< The name of the Action */
	};

	#define ActionFactory(ConcreteProductT) ConcreteFactory(ConcreteProductT, Action)

}
