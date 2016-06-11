#pragma once

#include "HashMap.h"
#include "Attributed.h"
#include "XmlParseMaster.h"

namespace Library
{
	/**
	 * Helper class for all XML parse handlers.
	 */
	class IXmlParseHelper
	{
	public:
		/**
		 * Default constructor.
		 */
		IXmlParseHelper() = default;

		/**
		 * Prevent the use of an IXmlParseHelper copy-constructor.
		 *
		 * @param rhs the IXmlParseHelper to prevent copying from
		 */
		IXmlParseHelper(const IXmlParseHelper& rhs) = delete;

		/**
		 * Prevent the use of an IXmlParseHelper from being directly copied.
		 *
		 * @param rhs the IXmlParseHelper to prevent copying from
		 * @return an IXmlParseHelper
		 */
		IXmlParseHelper& operator=(const IXmlParseHelper& rhs) = delete;

		/**
		 * Default destructor.
		 */
		virtual ~IXmlParseHelper() = default;

		/**
		 * Initialize the helper.
		 */
		virtual void Initialize();

		/**
		 * Given a string for the element name and a hashmap of attribute name-value pairs, attempt to
		 * handle the element start.
		 *
		 * @param sharedData reference to the shared data
		 * @param name the name of the element
		 * @param attributes the name-value pairs of Attributed classes
		 * @return returns true if this routine handles the element, false otherwise
		 */
		virtual bool StartElementHandler(const XmlParseMaster::SharedData& sharedData, const std::string& name, const HashMap<std::string, std::string>& attributes) = 0;

		/**
		 * Given a string for the element name, attempt to handle the element end. If this routine does 
		 * indeed handle the element, return true, otherwise return false.
		 *
		 * @param sharedData reference to the shared data
		 * @param name 
		 */
		virtual bool EndElementHandler(const XmlParseMaster::SharedData& sharedData, const std::string& name) = 0;

		/**
		 * Attempts to handle character data in a buffer.
		 *
		 * @param buffer the character buffer to process
		 * @param the size of the character buffer (in bytes)
		 */
		virtual bool CharDataHandler(const XmlParseMaster::SharedData& sharedData, const char* buffer, const std::uint32_t bufferSize);

		/**
		 * Duplicates an XmlParseHelper.
		 */
		virtual IXmlParseHelper* Clone() = 0;
	};
}
