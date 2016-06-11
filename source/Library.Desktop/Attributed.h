#pragma once

#include <cstdint>

namespace Library
{
	/**
	 * This class associates a Scope class with a native class/object and provides 
	 * some utility facilities such as prescribing the contents of a Scope table 
	 * at compile time, which is useful when you want to associate the members of 
	 * a class with a Scope (which is the point of the Attributed class). 
	 * Reciprocally, one of the uses of the Scope and Datum classes is to mediate 
	 * access to data from script, i.e. to provide access to C++ data via game 
	 * engine configuration scripts.
	 */
	class Attributed : public Scope
	{
		RTTI_DECLARATIONS(Attributed, Scope)
	protected:
		/** 
		 * Internal class that represents prescribed attributes.
		 */
		class Signature
		{
		public:
			union StorageType
			{
				std::int32_t* i;
				float* f;
				glm::vec4* v;
				glm::mat4* m;
				Scope** t;
				std::string* s;
				RTTI** p;
				void** vp;

				explicit StorageType() : vp(nullptr) {}
				explicit StorageType(std::int32_t* data) : i(data) {}
				explicit StorageType(float* data) : f(data) {}
				explicit StorageType(glm::vec4* data) : v(data) {}
				explicit StorageType(glm::mat4* data) : m(data) {}
				explicit StorageType(Scope** data) : t(&*data) {}
				explicit StorageType(std::string* data) : s(data) {}
				explicit StorageType(RTTI** data) : p(&*data) {}
			};

			/**
			 * Default constructor.
			 */
			Signature();

			/**
			 * Constructor overload to populate a Signature with internal data.
			 *
			 * @param name string indicating the key to use for a Datum in its scope
			 * @param initialValue the default value
			 * @param size the number of elements in this Datum
			 */
			Signature(const std::string& name, std::int32_t* initialValue, const std::uint32_t size);
			Signature(const std::string& name, float* initialValue, const std::uint32_t size);
			Signature(const std::string& name, glm::vec4* initialValue, const std::uint32_t size);
			Signature(const std::string& name, glm::mat4* initialValue, const std::uint32_t size);
			Signature(const std::string& name, Scope** initialValue, const std::uint32_t size);
			Signature(const std::string& name, std::string* initialValue, const std::uint32_t size);
			Signature(const std::string& name, RTTI** storage, const std::uint32_t size);

			/**
			* Constructor overload to populate a Signature with external data.
			*
			* @param name string indicating the key to use for a Datum in its scope
			* @param size the number of elements in this Datum
			* @param storage address of values external storage
			*/
			Signature(const std::string& name, const std::uint32_t size, std::int32_t* storage);
			Signature(const std::string& name, const std::uint32_t size, float* storage);
			Signature(const std::string& name, const std::uint32_t size, glm::vec4* storage);
			Signature(const std::string& name, const std::uint32_t size, glm::mat4* storage);
			Signature(const std::string& name, const std::uint32_t size, std::string* storage);
			Signature(const std::string& name, const std::uint32_t size, RTTI** storage);

			/**
			 * Copy constructor to perform a deep copy.
			 *
			 * @param rhs the other Signature to copy from
			 */
			Signature(const Signature& rhs);

			/**
			 * The assignment operator to perform a deep copy between two Signatures.
			 *
			 * @param rhs the Signature to copy from
			 * @return address of the new Signature
			 */
			Signature& operator=(const Signature& rhs);

			/**
			 * Default deconstructor for a Signature.
			 */
			~Signature();

			std::string mName;				/**< A string indicating key to use for Datum in its Scope */
			Datum::DatumType mType;			/**< The type of Datum enumeration */
			StorageType* mInitialValue;		/**< The default value */
			std::uint32_t mSize;			/**< The number of elements in this Datum */
			StorageType* mStorage;			/**< Address of values external storage, if provided */
		};
	public:
		/**
		 * Default constructor.
		 */
		Attributed();

		/**
		 * Copy constructor.
		 *
		 * @param rhs the other Attributed class to copy from
		 */
		Attributed(const Attributed& rhs);

		/**
		 * Move constructor.
		 *
		 * @param rhs the other Attributed class to move from
		 */
		Attributed(Attributed&& rhs);

		/**
		 * Assignment operator to perform a deep-copy between two Attributed classes.
		 *
		 * @param rhs the Attributed class to deep-copy from
		 */
		Attributed& operator=(const Attributed& rhs);

		/**
		 * Assignment operator to move data between two Attributed classes.
		 *
		 * @param rhs the Attributed class to move data from
		 */
		Attributed& operator=(Attributed&& rhs);

		/**
		 * Default virtual destructor.
		 */
		virtual ~Attributed();

		/**
		 * Populates the Scope with prescribed attributes.
		 */
		void Populate();

		/**
		 * Indicates whether an attribute is a prescribed attribute.
		 *
		 * @param name the name of the attribute to search for
		 * @return returns true if the attribute is a prescribed attribute, false otherwise
		 */
		bool IsPrescribedAttribute(const std::string& name) const;

		/**
		 * Indicates whether an attribute is an auxiliary attribute.
		 *
		 * @param name the name of the attribute to search for
		 * @return returns true if the attribute is an auxiliary attribute, false otherwise
		 */
		bool IsAuxiliaryAttribute(const std::string& name) const;

		/**
		 * Indicates whether a given name is associated with an attribute.
		 *
		 * @param name the name of the attribute to search for
		 * @return returns true if the name is an attribute, false otherwise
		 */
		bool IsAttribute(const std::string& name) const;

		/**
		 * Given a string, that is not be the name of a prescribed attribute, 
		 * append a Datum to this Scope with the given name, and return a 
		 * reference to that Datum. If the Datum already existed, return it. 
		 *
		 * @param name the name to search for
		 * @return a reference to the Datum that was created or previously existed
		 */
		Datum& AppendAuxiliaryAttribute(const std::string& name);

		/**
		 * Adds an internal signature to the Attributed class.
		 *
		 * @param name the name of the signature (the key for a Datum in a Scope)
		 * @param initialValue the value of the Datum
		 * @param size the number of elements in this Datum
		 */
		void AddInternalSignature(const std::string& name, std::int32_t* initialValue, const std::uint32_t size);
		void AddInternalSignature(const std::string& name, float* initialValue, const std::uint32_t size);
		void AddInternalSignature(const std::string& name, glm::vec4* initialValue, const std::uint32_t size);
		void AddInternalSignature(const std::string& name, glm::mat4* initialValue, const std::uint32_t size);
		void AddInternalSignature(const std::string& name, Scope** initialValue, const std::uint32_t size);
		void AddInternalSignature(const std::string& name, std::string* initialValue, const std::uint32_t size);
		void AddInternalSignature(const std::string& name, RTTI** initialValue, const std::uint32_t size);

		/**
		 * Adds an external signature to the Attributed class.
		 *
		 * @param name the name of the signature (the key for a Datum in a Scope)
		 * @param size the number of elements in this Datum
		 * @param storage the address of external storage values
		 */
		void AddExternalSignature(const std::string& name, const std::uint32_t size, std::int32_t* storage);
		void AddExternalSignature(const std::string& name, const std::uint32_t size, float* storage);
		void AddExternalSignature(const std::string& name, const std::uint32_t size, glm::vec4* storage);
		void AddExternalSignature(const std::string& name, const std::uint32_t size, glm::mat4* storage);
		void AddExternalSignature(const std::string& name, const std::uint32_t size, std::string* storage);
		void AddExternalSignature(const std::string& name, const std::uint32_t size, RTTI** storage);
		// Note: Scopes do not have an AddExternalSignature

		/**
		 * Returns an unsigned integer which is the index of the first auxiliary attribute.
		 *
		 * @return an unsigned integer which is the index of the first auxiliary attribute
		 */
		std::uint32_t AuxiliaryBegin() const;

		/**
		 * Returns a reference to a newly created table Datum.
		 * Datums passed in should be null. If they are not, they will be cleared first.
		 *
		 * @return reference to a Datum
		 */
		Datum& CreateTableDatum(const std::string& name);

	private:
		Signature* GetSignature(const std::string& name) const;
		Vector<Signature> mSignatures;
	};
}
