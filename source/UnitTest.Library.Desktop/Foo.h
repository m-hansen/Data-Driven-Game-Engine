/**
 * @brief A test class.
 *
 * This class exists only to verify the initial project configuration
 * by verifying that multiple projects and libraries can be linked.
 */

#pragma once
namespace UnitTestLibraryDesktop
{
	class Foo
	{
	public:
		/**
			* Used to instantiate a Foo object.
			*
			* @param data the integer data that will initialize our member data
			*/
		Foo(const int32_t data = 0);

		/**
		* Performs a deep copy of Foo.
		*
		* @param rhs the old Foo object used to instantiate the new Foo object
		*/
		Foo(const Foo& rhs);

		/**
		* Overloads the assignment operator to perform a deep copy.
		*
		* @param rhs reference to the original Foo object
		* @return a reference to the new Foo object
		*/
		Foo& operator=(const Foo& rhs);

		/**
			* Overloads the comparison operator.
			*
			* @param other the other Foo to compare against
			* @return true if two Foos are equal, false otherwise
			*/
		bool operator==(const Foo& other) const;

		/**
		* Overloads the comparison operator.
		*
		* @param other the other Foo to compare against
		* @return true if two Foos are not equal, false otherwise
		*/
		bool operator!=(const Foo& other) const;

		/**
		* Deconstructor to free memory.
		*/
		~Foo();

		/**
		* Returns mData.
		*
		* @return The data
		*/
		int32_t Data() const;
	private:
		int32_t mData;			/**< Local data represented as an integer (for testing) */
		int32_t* mMoreData;		/**< Local data represented as a pointer to an integer (for testing) */
	};
}
