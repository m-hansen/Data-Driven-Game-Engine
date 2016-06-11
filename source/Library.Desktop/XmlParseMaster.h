#pragma once

#include <cstdint>
#include <string>
#include <fstream>
#include "Vector.h"
#include "expat.h"

namespace Library
{
	class IXmlParseHelper;

	/**
	 * Manages XmlParseHelpers and passes data down the chain to them.
	 */
	class XmlParseMaster final
	{
	public:
		/**
		 * This class will represent data that all helpers share with each other and 
		 * with the master parser. This is a base class. You will likely extend this 
		 * class depending on the kind of XML file you parse. You should use the 
		 * lightweight homebrew RTTI schemes covered in lecture, to verify the object 
		 * type on each access.
		 */
		class SharedData : public RTTI
		{
			RTTI_DECLARATIONS(SharedData, RTTI)
		public:
			/**
			 * Default constructor.
			 */
			SharedData();

			/**
			 * Prevent the use of a SharedData copy-constructor.
			 *
			 * @param rhs the SharedData to prevent copying from
			 */
			SharedData(const SharedData& rhs) = delete;

			/**
			 * Prevent the use of a SharedData from being directly copied.
			 *
			 * @param rhs the SharedData to prevent copying from
			 * @return a SharedData
			 */
			SharedData& operator=(const SharedData& rhs) = delete;

			/**
			 * Default destructor.
			 */
			virtual ~SharedData() = default;

			/**
			 * Initializes the SharedData to its default state.
			 */
			void Initialize();

			/**
			 * "Virtual Constructor" which returns the address of a SharedData object
			 * which has the same internal state as "this" except ready for a fresh file.
			 *
			 * @return pointer to the cloned SharedData
			 */
			virtual SharedData* Clone() const;

			/**
			 * Given the address of an XmlParseMaster, assign it to a private member.
			 *
			 * @param parser the XmlParseMaster address
			 */
			void SetXmlParseMaster(XmlParseMaster& parser);

			/**
			 * Returns the address of the XmlParseMaster associated with this object.
			 *
			 * @param return the address of the XmlParseMaster associated with this object
			 */
			XmlParseMaster* GetXmlParseMaster() const;

			/**
			 * Increments a "nesting depth" counter. This gets incremented upon the start of each element.
			 */
			void IncrementDepth();

			/**
			 * Decrements a "nesting depth" counter. This gets decremented upon the start of each element.
			 */
			void DecrementDepth();

			/**
			 * Returns the current nesting depth.
			 *
			 * @return the current nesting depth
			 */
			std::uint32_t Depth() const;

		private:
			XmlParseMaster* mParser;
			std::uint32_t mDepth;
		};

		/**
		 * Default constructor to initialize members.
		 *
		 * @param sharedData the shared data
		 * @param encoding optional parameter to specify the encoding to use for parsing (defaults to UTF-8)
		 */
		explicit XmlParseMaster(SharedData* sharedData, const XML_Char* encoding = nullptr);

		/**
		 * Prevent the use of an XmlParseMaster copy-constructor.
		 *
		 * @param rhs the XmlParseMaster to prevent copying from
		 */
		XmlParseMaster(const XmlParseMaster& rhs) = delete;

		/**
		 * Prevent the use of an XmlParseMaster from being directly copied.
		 *
		 * @param rhs the XmlParseMaster to prevent copying from
		 * @return an XmlParseMaster
		 */
		XmlParseMaster& operator=(const XmlParseMaster& rhs) = delete;

		/**
		 * Default destructor.
		 */
		virtual ~XmlParseMaster();

		/**
		 * Duplicated this object and returns its address.
		 *
		 * @return an address of the cloned XmlParseMaster
		 */
		XmlParseMaster* Clone() const;

		/**
		 * Returns whether the XmlParseMaster is a clone.
		 *
		 * @return true if the XmlParseMaster is a clone, false otherwise
		 */
		bool IsClone() const;

		/**
		 * Given a reference to an IXmlParseHelper object, add it to the list.
		 *
		 * @param helper the IXmlParseHelper to add
		 */
		void AddHelper(IXmlParseHelper& helper);

		/**
		 * Given a reference to an IXmlParseHelper object, remove it from the list.
		 *
		 * @param helper reference to the IXmlParseHelper to remove.
		 */
		void RemoveHelper(IXmlParseHelper& helper);

		/**
		 * Wrapper to parse the XML text.
		 *
		 * @param buffer the buffer to parse
		 * @param bufferSize the size of the buffer
		 * @param isFirstChunk flag indicating the first chunk of data in a document, if true calls Reset
		 * @param isLastChunk flag indicating that the last chunk of data is being read from the document
		 */
		void Parse(const char* buffer, const std::uint32_t bufferSize, const bool isFirstChunk, const bool isLastChunk);

		/**
		 * Given a filename, read in the file and parse it.
		 *
		 * @param fileName the name of the file to parse
		 */
		void ParseFromFile(const std::string& fileName);

		/**
		 * Returns the name of the file being parsed.
		 *
		 * @return the name of the file being parsed
		 */
		const std::string& GetFileName() const;

		/**
		 * Returns the address of the SharedData associated with this object.
		 *
		 * @return the address of the SharedData associated with this object
		 */
		const SharedData* GetSharedData() const;

		/**
		 * Given the address of a SharedData object, associate it with this object.
		 *
		 * @param data the address of a SharedData object
		 */
		void SetSharedData(SharedData& data);

	private:
		static void StartElementHandler(void* userData, const XML_Char* name, const XML_Char** attributes);
		static void EndElementHandler(void* userData, const XML_Char* name);
		static void CharDataHandler(void* userData, const char* buffer, int32_t length);
		void Reset();
		Vector<IXmlParseHelper*> mHelpers;
		SharedData* mSharedData;
		XML_Parser mParser;
		std::string mParsedFileName;
		bool mIsClone;
	};
}
