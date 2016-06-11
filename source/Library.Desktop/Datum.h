#pragma once

#include <cstdint>

namespace Library
{
	class RTTI;
	class Scope;

	/**
	 * @brief A runtime type container that resembles and array of data.
	 *
	 * A Datum object represents an array where all of the elements have the same type. 
	 * Different Datum objects can store values of different types. Datums are polymorphic 
	 * homogenous containers. The Datum type is defined at run time.
	 */
	class Datum
	{
	private:
		union DatumValues
		{
			std::int32_t* i;
			float* f;
			glm::vec4* v;
			glm::mat4* m;
			Scope** t;
			std::string* s;
			RTTI** p;
			void** vp;

			DatumValues() : i(nullptr) {}
		};

	public:
		/**
		 * @brief The types of data that a Datum supports.
		 */
		enum class DatumType
		{
			Unknown,
			Integer,
			Float,
			Vector,
			Matrix,
			Table,
			String,
			Pointer,
			End
		};

		/**
		 * Default constructor to initialize a Datum.
		 */
		Datum();

		/**
		 * Constructor to initialize a Datum with an initial type and capacity.
		 *
		 * @param type the DatumType to assign to the datum
		 * @param capacity the Datum's initial capacity
		 */
		Datum(const DatumType type, const std::uint32_t capacity);

		/**
		 * Copy constructor to perform a deep-copy of a Datum.
		 *
		 * @param rhs a constant reference to a Datum to copy from
		 */
		Datum(const Datum& rhs);

		/**
		 * Deep-copy the contents of the given Datum into this one. Can also copy
		 * scalar values.
		 *
		 * @param rhs the Datum or scalar value to deep-copy
		 * @return a reference to the Datum that contains the new contents
		 */
		Datum& operator=(const Datum& rhs);
		Datum& operator=(const std::int32_t rhs);
		Datum& operator=(const float rhs);
		Datum& operator=(const glm::vec4& rhs);
		Datum& operator=(const glm::mat4& rhs);
		Datum& operator=(const Scope* rhs);
		Datum& operator=(const std::string& rhs);
		Datum& operator=(const RTTI* rhs);

		/**
		* Checks to see if two Datums are equal. Overloads are provided to compare Datums
		* as scalar values.
		*
		* @param other/value the other Datum or scalar value to compare against
		* @return true if two Datums or a Datum and a scalar are equivalent, false otherwise
		*/
		bool operator==(const Datum& other) const;
		bool operator==(const std::int32_t value) const;
		bool operator==(const float value) const;
		bool operator==(const glm::vec4& value) const;
		bool operator==(const glm::mat4& value) const;
		bool operator==(const Scope* value) const;
		bool operator==(const std::string& value) const;
		bool operator==(const RTTI* value) const;

		/**
		* Checks to see if two Datums are not equal. Overloads are provided to compare Datums
		* as scalar values.
		*
		* @param other/value the other Datum or scalar value to compare against
		* @return true if two Datums or a Datum and a scalar are not equivalent, false otherwise
		*/
		bool operator!=(const Datum& other) const;
		bool operator!=(const std::int32_t value) const;
		bool operator!=(const float value) const;
		bool operator!=(const glm::vec4& value) const;
		bool operator!=(const glm::mat4& value) const;
		bool operator!=(const Scope* value) const;
		bool operator!=(const std::string& value) const;
		bool operator!=(const RTTI* value) const;

		/**
		 * Overload the subscript operator. This is a syntactic sugar used to simplify 
		 * dereferencing nested Scopes.
		 *
		 * @param index the index to access
		 * @return a reference to the Scope at a given index
		 */
		Scope& operator[](const std::uint32_t index);

		/**
		 * Default destructor. Clears the datum and all allocated memory, if it contains 
		 * internal storage. External storage is not modified.
		 */
		~Datum();

		/**
		 * Removes a table pointer from the datum.
		 *
		 * @param index the index of the table pointer to remove
		 */
		void RemoveTable(const std::uint32_t index);

		/**
		 * Increases the capacity to the new value specified, if it is larger than the previous capacity.
		 *
		 * @param capacity the new capacity
		 */
		void Datum::Reserve(const std::uint32_t capacity);

		/**
		 * Append data to the back of the container
		 *
		 * @param value the data to append
		 */
		void PushBack(const std::int32_t value);
		void PushBack(const float value);
		void PushBack(const glm::vec4& value);
		void PushBack(const glm::mat4& value);
		void PushBack(Scope& value);
		void PushBack(const std::string& value);
		void PushBack(RTTI& value);

		/**
		 * Returns type enum associated with this object.
		 *
		 * @return the DatumType enum
		 */
		DatumType Type() const;

		/**
		 * Assigns the type of data this object stores.
		 *
		 * @param type the DataType enum to assign
		 */
		void SetType(const DatumType& type);

		/**
		 * Returns the capacity of the container.
		 *
		 * @return an unsigned integer for the capacity
		 */
		std::uint32_t Capacity() const;

		/**
		 * Returns the size of the container.
		 *
		 * @return an unsigned integer for the size
		 */
		std::uint32_t Size() const;

		/**
		 * Clears the datum and all allocated memory, if it contains internal storage. 
		 * External storage is not modified.
		 */
		void Clear();

		/**
		 * Assigns the data to an external array. This is intended to be called before any
		 * other allocations are made.
		 *
		 * @param values the external array that the Datum will point to
		 * @param the size of the external array
		 */
		void SetStorage(std::int32_t* values, const std::uint32_t size);
		void SetStorage(float* values, const std::uint32_t size);
		void SetStorage(glm::vec4* values, const std::uint32_t size);
		void SetStorage(glm::mat4* values, const std::uint32_t size);
		void SetStorage(std::string* values, const std::uint32_t size);
		void SetStorage(RTTI** values, const std::uint32_t size);
		// Note: SetStorage does not apply to DatumType::Table

		/**
		 * Assigns the appropriate element in the values array to the given value. Set increases the
		 * capacity automatically if needed (external storage cannot be resized). If this is the first 
		 * assignment to the Datum then the type should be assigned at this time.
		 *
		 * @param value the value to be assigned to the Datum
		 * @param index an optional parameter to specify which index the value should be placed in (defaults to zero)
		 */
		void Set(const std::int32_t value, std::uint32_t index = 0U);
		void Set(const float value, std::uint32_t index = 0U);
		void Set(const glm::vec4& value, std::uint32_t index = 0U);
		void Set(const glm::mat4& value, std::uint32_t index = 0U);
		void Set(Scope& value, std::uint32_t index = 0U);
		void Set(const std::string& value, std::uint32_t index = 0U);
		void Set(RTTI& value, std::uint32_t index = 0U);

		/**
		 * Assigns the appropriate element in the values array to the given value.
		 * Requires the type to have already been set
		 *
		 * @param str the value to set, as a string
		 * @index the index of the values location
		 */
		void SetFromString(const std::string& str, const std::uint32_t index = 0U);

		/**
		 * Returns a string representing the appropriate element in the values array
		 */
		std::string ToString(const std::uint32_t index = 0U) const;

		/**
		 * Returns a flag specifying if internal or external storage is use.
		 *
		 * @return true if the container is pointing at an external array, false if it is internally stored
		 */
		bool IsExternal() const;

		/**
		 * Returns a value from the Datum array at a specified index.
		 *
	 	 * @param index the index to find a value at
		 * @return the value at a given index
		 */
		template<typename T> const T& Get(const std::uint32_t index) const;
		template<> const std::int32_t& Get<std::int32_t>(const std::uint32_t index) const;
		template<> const float& Get<float>(const std::uint32_t index) const;
		template<> const glm::vec4& Get<glm::vec4>(const std::uint32_t index) const;
		template<> const glm::mat4& Get<glm::mat4>(const std::uint32_t index) const;
		template<> Scope* const & Get<Scope*>(const std::uint32_t index) const;
		template<> const std::string& Get<std::string>(const std::uint32_t index) const;
		template<> RTTI* const & Get<RTTI*>(const std::uint32_t index) const;

	private:
		DatumValues mData;
		DatumType mType;
		std::uint32_t mSize;
		std::uint32_t mCapacity;
		bool mIsExternal;
	};

}
