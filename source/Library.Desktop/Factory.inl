#include "pch.h"

#include "Factory.h"

namespace Library
{
	template<typename AbstractProductT>
	HashMap<std::string, const Factory<AbstractProductT>* const> Factory<AbstractProductT>::sFactoryTable(11);

	template<typename AbstractProductT>
	const Factory<AbstractProductT>* const Factory<AbstractProductT>::Find(const std::string& name)
	{
		Iterator it = sFactoryTable.Find(name);
		if (it != end())
		{
			return it->second;
		}

		return nullptr;
	}

	template<typename AbstractProductT>
	AbstractProductT* Factory<AbstractProductT>::Create(const std::string& name)
	{
		const Factory<AbstractProductT>* factory = Find(name);
		if (!factory)
		{
			throw std::exception("Factory does not exist.");
		}

		return factory->Create();
	}

	template<typename AbstractProductT>
	typename Factory<AbstractProductT>::Iterator Factory<AbstractProductT>::begin()
	{
		return sFactoryTable.begin();
	}

	template<typename AbstractProductT>
	typename Factory<AbstractProductT>::Iterator Factory<AbstractProductT>::end()
	{
		return sFactoryTable.end();
	}

	template<typename AbstractProductT>
	std::uint32_t Factory<AbstractProductT>::Size()
	{
		return sFactoryTable.Size();
	}

	template<typename AbstractProductT>
	bool Factory<AbstractProductT>::IsEmpty()
	{
		return (Size() == 0);
	}

	template<typename AbstractProductT>
	void Factory<AbstractProductT>::Add(Factory& factory)
	{
		sFactoryTable.Insert(std::pair<std::string, const Factory<AbstractProductT>* const>(factory.ClassName(), &factory));
	}

	template<typename AbstractProductT>
	void Factory<AbstractProductT>::Remove(const Factory& factory)
	{
		sFactoryTable.Remove(factory.ClassName());
	}

#define ConcreteFactory(ConcreteProductT, AbstractProductT)							\
	class ConcreteProductT##Factory : public Factory<AbstractProductT>				\
	{																				\
	public:																			\
		ConcreteProductT##Factory()													\
			: mClassName(#ConcreteProductT)											\
		{																			\
			Factory::Add(*this);													\
		}																			\
																					\
		virtual ~ConcreteProductT##Factory()										\
		{																			\
			Factory::Remove(*this);													\
		}																			\
																					\
		virtual AbstractProductT* Create() const override							\
		{																			\
			return new ConcreteProductT();											\
		}																			\
																					\
		virtual const std::string& ClassName() const override						\
		{																			\
			return mClassName;														\
		}																			\
																					\
	private:																		\
		std::string mClassName;														\
	};

}
