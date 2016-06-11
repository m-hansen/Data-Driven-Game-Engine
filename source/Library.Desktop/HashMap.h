#pragma once

#include <cstdint>

namespace Library
{
	/**
	 * @brief The default hash function to use for a HashMap.
	 */
	template<typename TKey>
	class DefaultHash
	{
	public:
		/**
		 * Overloads operator() to return a hash index.
		 *
		 * @param key the key to hash
		 * @param size the number of buckets
		 * @return the newly hashed index
		 */
		std::uint32_t operator()(const TKey& key)
		{
			const char* byte = reinterpret_cast<const char*>(&key);
			std::uint32_t hash = 0;
			for (std::uint32_t i = 0; i < sizeof(key); ++i)
			{
				hash = hash << 1 ^ byte[i];
			}
			return hash;
		}
	};

	/**
	* @brief The default hash function to use for a HashMap that uses char* as a key.
	*/
	template<>
	class DefaultHash<char*>
	{
	public:
		/**
		 * Overloads operator() to return a hash index.
		 *
		 * @param key the key to hash
		 * @param size the number of buckets
		 * @return the newly hashed index
		 */
		std::uint32_t operator()(const char* key)
		{
			std::uint32_t hash = 0;
			while (*key)
			{
				hash = hash << 1 ^ *key++;
			}
			return hash;
		}
	};

	/**
	* @brief The default hash function to use for a HashMap that uses std::string as a key.
	*/
	template<>
	class DefaultHash<std::string>
	{
	public:
		/**
		 * Overloads operator() to return a hash index.
		 *
		 * @param key the key to hash
		 * @param size the number of buckets
		 * @return the newly hashed index
		 */
		std::uint32_t operator()(const std::string& key)
		{
			std::uint32_t hash = 0;
			for (std::uint32_t i = 0; i < key.length(); ++i)
			{
				hash = hash << 1 ^ key[i];
			}
			return hash;
		}
	};

	/**
	 * A container that holds key/value pairs. The key is used as a unique identifier
	 * while the value (or data) is what the container is looking to retrieve efficiently.
	 */
	template<typename TKey, typename TData, typename HashFunctor = DefaultHash<TKey>>
	class HashMap
	{
	public:
		typedef std::pair<TKey, TData> PairType;							/**< The key/value pair for a HashMap */

	private:
		typedef SList<PairType> ChainType;
		typedef Vector<ChainType> BucketType;
		typedef typename ChainType::Iterator ChainIterator;

		BucketType mBuckets;
		std::uint32_t mSize;

	public:
		/**
		 * @brief A custom iterator for the HashMap class.
		 */
		class Iterator final
		{
		public:
			/**
			 * Default constructor.
			 */
			Iterator();

			/**
			 * Copy constructor.
			 *
			 * @param rhs the other Iterator to copy from
			 */
			Iterator(const Iterator& rhs);

			/**
			 * Overloads the assignment operator.
			 *
			 * @param rhs the other iterator to assign from
			 * @return a reference to an Iterator
			 */
			Iterator& operator=(const Iterator& rhs);

			/**
			 * Overloads the prefix increment operator that reassigns the iterator to the next node.
			 *
			 * @return a reference to the next iterator
			 */
			Iterator& operator++();

			/**
			 * Overloads the postfix increment operator that reassigns the iterator to the next node.
			 *
			 * @param int a dummy parameter to distinguish between the prefix and postfix increment operators
			 * @return a reference to the next iterator
			 */
			Iterator operator++(int);

			/**
			 * Overload the dereference operator
		 	 *
			 * @return the data contained in the type
			 */
			PairType& operator*() const;

			/**
			 * Overload the dereference operator
			 *
			 * @return the pointer to data contained in the type
			 */
			PairType* operator->() const;

			/**
			 * Overload the comparison operator.
			 *
			 * @param other the other iterator to compare against
			 * @return returns true if two iterators are equal, false otherwise
			 */
			bool operator==(const Iterator& other) const;

			/**
			 * Overload the comparison operator.
			 *
			 * @param other the other iterator to compare against
			 * @return returns true if two iterators are not equal, false otherwise
			 */
			bool operator!=(const Iterator& other) const;

			/**
			 * The default constructor.
			 */
			~Iterator() = default;
		private:
			friend class HashMap;
			Iterator(const HashMap* owner, typename ChainType::Iterator chainIterator, const std::uint32_t index);
			const HashMap* mOwner;
			typename ChainType::Iterator mNodeInChain;
			std::uint32_t mIndex;
		};

		/**
		 * Default constructor that sets the size of the hash table array.
		 *
		 * @param size the size (number of buckets) of the hash table array
		 */
		HashMap(std::uint32_t sizeOfTable = 0);

		/**
		 * Destruct the object and free all memory associated with it.
		 */
		~HashMap() = default;

		/**
		* Returns an Iterator associated with the TKey provided.
		*
		* @param key a reference to the TKey being searched for
		* @return an Iterator associated with the TKey provided
		*/
		Iterator Find(const TKey& key) const;

		/**
		 * Returns an Iterator associated with the TKey provided.
		 *
		 * @param key a reference to the TKey being searched for
		 * @param hashIndex reference to an unsigned integer index
		 * @return an Iterator associated with the TKey provided
		 */
		Iterator Find(const TKey& key, std::uint32_t& hashIndex) const;

		/**
		 * Inserts an entry (TKey, TData) into the table. If the table already contains
		 * an entry with a matching TKey, it will not be modified.
		 *
		 * @param entry the PairType to insert into the table
		 * @return an Iterator associated with the new entry
		 */
		Iterator Insert(const PairType& entry);

		/**
		 * Inserts an entry (TKey, TData) into the table. If the table already contains
		 * an entry with a matching TKey, it will not be modified.
		 *
		 * @param entry the PairType to insert into the table
		 * @param wasInserted a boolean, passed by reference, to determine if insert created a new entry
		 *		  or simply returned an existing value
		 * @return an Iterator associated with the new entry
		 */
		Iterator Insert(const PairType& entry, bool& wasInserted);

		/**
		 * Returns a reference to the value of a given key. Creates an entry with the associated TKey if one does not exist.
		 *
		 * @param key the TKey to look up
		 * @return the value associated with the given key
		 */
		TData& operator[](const TKey& key);

		/**
		 * Removes an entry if it exists.
		 *
		 * @param key the TKey used to search for an associated entry to remove
		 */
		void Remove(const TKey& key);

		/**
		 * Empties the table and deletes any memory it allocated.
		 */
		void Clear();

		/**
		 * Returns the number of entries in the table.
		 *
		 * @return the number of entries in the table
		 */
		std::uint32_t Size() const;

		/**
		 * Returns a boolean indicating the presence of a specified key within the hash map.
		 *
		 * @param key the key to search for
		 * @return true if the table contains any keys, false otherwise
		 */
		bool ContainsKey(const TKey& key) const;

		/**
		 * Returns an Iterator that points to the beginning of the table's contents.
		 *
		 * @return an ITerator that points to the beginning of the table's contents
		 */
		Iterator begin() const;

		/**
		 * Returns an Iterator that can be used to determine when a loop is done.
		 *
		 * @return an Iterator that can be used to determine when a loop is done
		 */
		Iterator end() const;
	};
}

#include "HashMap.inl"
