#pragma once

#include <string>
#include <cstdint>
#include "XmlParseMaster.h"

namespace Library
{
	/**
	 * Class to handle the parsing of Scopes and the contained Datums within a Scope.
	 */
	class XmlParseHelperTable final : public IXmlParseHelper
	{
	public:
		/**
		 * Specialized SharedData class for Scopes (Tables).
		 */
		class SharedData final : public XmlParseMaster::SharedData
		{
			friend class XmlParseHelperTable;
			RTTI_DECLARATIONS(SharedData, XmlParseMaster::SharedData)
		public:
			/**
			 * Constructs a SharedData object for Tables. 
			 *
			 * @param globalScope the containing Scope for the SharedData
			 * @param isClone a flag to determine if the SharedData object is a clone
			 */

			explicit SharedData(Scope& globalScope, const bool isClone = false);
			/**
			 * Prevent direct copying of SharedData.
			 *
			 * @param rhs the other SharedData object to prevent copying from
			 */
			SharedData(const SharedData& rhs) = delete;

			/**
			* Prevent direct copying of SharedData.
			*
			* @param rhs the other SharedData object to prevent copying from
			* @return SharedData object
			*/
			SharedData& operator=(const SharedData& rhs) = delete;

			/**
			 * Deconstruct the SharedData object.
			 */
			virtual ~SharedData() = default;

			/**
			 * Creates a new SharedData object.
			 *
			 * @return the newly created SharedData object
			 */
			virtual SharedData* Clone() const override;

			/**
			 * Returns whether the SharedData object is a clone.
			 *
			 * @return true if it is a clone, false otherwise
			 */
			bool IsClone() const;

		private:
			Scope* mScope;				/**< The Scope being parsed. */
			bool mIsClone;				/**< Flag to determine if the SharedData is a clone. */
		};

		/**
		 * Instantiates a new XmlParseHelperTable.
		 *
		 * @param isClone optional flag for specifying whether this object is a clone.
		 */
		explicit XmlParseHelperTable(const bool isClone = false);

		/**
		 * Deconstruct the XmlParseHelperTable object.
		 */
		virtual ~XmlParseHelperTable() = default;

		/**
		 * Given a string for the element name and a hashmap of attribute name-value pairs, attempt to
		 * handle the element start.
		 *
		 * @param sharedData reference to the shared data
		 * @param name the name of the element
		 * @param attributes the name-value pairs of Attributed classes
		 * @return returns true if this routine handles the element, false otherwise
		 */
		virtual bool StartElementHandler(const XmlParseMaster::SharedData& sharedData, const std::string& name, const HashMap<std::string, std::string>& attributes) override;
		
		/**
		 * Given a string for the element name, attempt to handle the element end. If this routine does
		 * indeed handle the element, return true, otherwise return false.
		 *
		 * @param sharedData reference to the shared data
		 * @param name
		 */
		virtual bool EndElementHandler(const XmlParseMaster::SharedData& sharedData, const std::string& name) override;

		/**
		 * Creates a new XmlParseHelperTable object.
		 *
		 * @return the newly created XmlParseHelperTable object
		 */
		virtual XmlParseHelperTable* Clone() override;

		/**
		 * Returns whether the XmlParseHelperTable object is a clone.
		 *
		 * @return true if it is a clone, false otherwise
		 */
		bool IsClone() const;

	private:
		bool mIsClone;					/**< Flag to determine whether the helper is a clone */
	};

}
