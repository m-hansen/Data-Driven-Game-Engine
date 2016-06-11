#pragma once

#include <cstdint>
#include "RTTI.h"

namespace Library
{
	/**
	 * Scope objects are tables that create dictionary of name-value pairs 
	 * where Datum objects are the values. Each entry in a Scope table has 
	 * a name and a Datum, where the Datum represents an array of values of 
	 * a single type.
	 */
	class Scope : public RTTI
	{
		RTTI_DECLARATIONS(Scope, RTTI)
	public:
		/**
		 * Default constructor.
		 *
		 * @param initialCapacity the capacity of the order vector
		 */
		explicit Scope(std::uint32_t initialCapacity = 0U);

		/**
		 * Copy-constructor.
		 *
		 * @param rhs the other scope to copy from
		 */
		Scope(const Scope& rhs);

		/**
		 * Assignment operator.
		 *
		 * @param rhs the other scope to copy from.
		 * @return a reference to the deep copied scope
		 */
		Scope& operator=(const Scope& rhs);

		/**
		 * Equal comparison operator.
		 *
		 * @param other the other scope to compare against
		 * @return true if two scopes are equal, false otherwise
		 */
		bool operator==(const Scope& other) const;

		/**
		 * Not equal comparison operator.
		 *
		 * @param other the other scope to compare against
		 * @return true if two scopes are not equal, false otherwise
		 */
		bool operator!=(const Scope& other) const;

		/**
		 * Subscript operator for syntatic convenience.
		 *
		 * @param name string to append to the scope
		 * @return the address of the Datum
		 */
		Datum& operator[](const std::string& name);

		/**
		 * Returns a reference to a Datum at the given index. The index 
		 * values correspond to the order in which items were appended.
		 *
		 * @param index the index of the Datum
		 * @return the address of the Datum
		 */
		Datum& operator[](const std::uint32_t index);

		/**
		 * Deconstructor.
		 */
		virtual ~Scope();

		/**
		 * Deletes all memory allocated by this object.
		 *
		 * @param skipOrphan optional parameter that skips orphaning 
		 * when set to true
		 */
		void Clear(const bool skipOrphan = false);

		/**
		 * Breaks the link between parent and child scopes.
		 */
		void Orphan();

		/**
		 * Returns the address of the Datum associated with the given name in 
		 * this Scope, if it exists, and nullptr otherwise.
		 *
		 * @param name the name associated with the datum
		 * @return an address to the datum with the associated name in the scope
		 */
		Datum* Find(const std::string& name) const;

		/**
		 * Takes a constant string and an optional address of a Scope double pointer
		 * which returns the address of a Datum. This should return the address of 
		 * the most-closely nested Datum associated with the given name in this Scope 
		 * or its ancestors, if it exists, and nullptr otherwise.
		 *
		 * @param name the name to search for
		 * @param scope contains the address of the Scope object which contains the match
		 * @return the found Datum
		 */
		Datum* Search(const std::string& name, Scope** scope = nullptr) const;

		/**
		 * Return a reference to a Datum with the associated name.
		 *
		 * @param name the name to append
		 * @return a reference to a Datum with the associated name
		 */
		Datum& Append(const std::string& name);

		/**
		 * Returns a reference to a Scope with the associated name.
		 * 
		 * @param name the name to search for
		 * @return the address of the scope 
		 */
		Scope& AppendScope(const std::string& name);

		/**
		 * Places a child into a table with a given name.
		 *
		 * @param child the child scope
		 * @param childName the name of the child
		 */
		void Adopt(Scope& child, const std::string& childName);

		/**
		 * Returns the address of the scope that contains this one.
		 *
		 * @return the address of the scope that contains this one
		 */
		Scope* GetParent() const;

		/**
		 * Search the current scope for a specified nested scope. Returns the 
		 * address of the datum the scope resides in.
		 *
		 * @param scope the scope to search for
		 * @return the address of the Datum that contains the nested scope
		 */
		Datum* FindContainedScope(const Scope& scope) const;

		/**
		 * Returns the name of the corresponding member.
		 * 
		 * @param scopeAddress the address of a scope
		 * @return the name of the corresponding member
		 */
		std::string FindName(const Scope& scopeAddress) const;

		/**
		 * Returns true if a name was found in a search scope. Modifies the foundName
		 * reference with the string that was found.
		 *
		 * @param searchScope the scope to search
		 * @param foundName the returned (by reference) name that was found
		 * @return true if found, false otherwise
		 */
		bool FindName(const Scope& searchScope, std::string& foundName) const;

		/**
		 * The size of the order vector.
		 *
		 * @return the size of the order vector
		 */
		std::uint32_t Size() const;
	protected:
		typedef std::pair<std::string, Datum> TablePair;
	private:
		const std::uint32_t DefaultNumberOfBuckets = 10;
		HashMap<std::string, Datum> mData;
		Vector<TablePair*> mOrderedData;
		Scope* mParent;
	};

}
