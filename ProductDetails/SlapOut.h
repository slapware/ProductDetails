#pragma once
#pragma warning( disable : 4267 4305 4309)  // Disable warning messages

#ifdef _DEBUG
    #define _RWCONFIG 15s
#else
    #define _RWCONFIG 12s
#endif

#include <iostream>
#include <rw/cstring.h>
#include <rw/tools/regex.h> // new RegEx
#include "Markup.h"
#include <rw/i18n/RWUToUnicodeConverter.h>
#include <rw/i18n/RWUFromUnicodeConverter.h>
#include <rw/i18n/RWUString.h>

// Custom XML encode or FirstObject encode
//#define _USE_FO_ENCODE_

//:Custom
using namespace std;

namespace slapware 
{    // begin SlapWare namespace

    class CSlapOut
    {
    public:
		inline void SendOut(RWCString& pTag, RWCString& pData)
		{
			std::ostringstream m_strstrm;
			pTag = pTag.strip( RWCString::both, ' ' );
			pData = pData.strip( RWCString::both, ' ' );
			RWCString m_line;
			if (pData.length() == 0)
			{
				m_strstrm << "<" << pTag << " />";
				m_line = m_strstrm.str();
				m_strstrm.str("");
			} 
			else
			{
				m_strstrm << "<" << pTag << ">";
				m_strstrm << XmlCheck(pData, false);
				m_strstrm << "</" << pTag << ">" << endl;
				m_line = m_strstrm.str();
				m_strstrm.str("");
			}
			cout << m_line;
		}

		inline void SendCdataOut(RWCString& pTag, RWCString& pData)
		{
			std::ostringstream m_strstrm;
			pTag = pTag.strip( RWCString::both, ' ' );
			pData = pData.strip( RWCString::both, ' ' );
			RWCString m_line;
			if (pData.length() <= 1)
			{
				m_strstrm << "<" << pTag << " />" << endl;
				m_line = m_strstrm.str();
				m_strstrm.str("");
			} 
			else
			{
				m_strstrm << "<" << pTag << "><![CDATA[";
				m_strstrm << XmlCheck(pData, true);
				m_strstrm << "]]></" << pTag << ">" << endl;
				m_line = m_strstrm.str();
				m_strstrm.str("");
			}
			cout << m_line;
		}

		RWCString XmlCheck(RWCString& pRecord, bool isCdata)
		{
			if (pRecord.length() > 0)
			{
				pRecord = pRecord.strip( RWCString::both, ' ' );

				size_t pLen = 0;
				size_t hloc = 0;
				int nFlags = CMarkup::MNF_WITHREFS | CMarkup::MNF_ESCAPEQUOTES;
				RWUString m_escaped;
				std::ostringstream m_strstrm;

				if (!isCdata)
				{
					m_escaped = CMarkup::EscapeText(pRecord.std(), nFlags);
					m_strstrm << m_escaped;
					pRecord = m_strstrm.str();
					m_strstrm.str("");
					m_escaped.remove(0);
				}

				size_t fidx = 0;
				std::string::size_type indexins = 0;

				// ]]>
				RWCRegexp rCdata("]]>");
				hloc = rCdata.index(pRecord, &pLen, 0);
				while (hloc != RW_NPOS)
				{
					pRecord(rCdata) = "&#x93;&#x93;&gt;";
					hloc = rCdata.index(pRecord, &pLen, hloc + 1);
				}

				char rNull = 0x00;
				indexins = 0;
				while ((indexins = pRecord.std().find ( rNull, indexins ) ) != string::npos) // 0x00 Fix
				{
					pRecord.remove(indexins, 1);
					indexins = 0;
				}

				m_escaped = pRecord.std();
				// Convert from UTF-16 to US-ASCII again, replacing
				// illegals with an escape sequence suitable for use in
				// an XML or HTML file.
				RWUFromUnicodeConverter toUsAscii("US-ASCII");
				toUsAscii.setErrorResponse(
					RWUFromUnicodeConverter::EscapeXmlHexadecimal);
				m_strstrm << m_escaped.toBytes(toUsAscii);
				pRecord = m_strstrm.str();
				m_strstrm.str("");
			} // if (pRecord.length() > 0)

			return pRecord;	
	    } // RWCString XmlCheck(RWCString& pRecord, bool isCdata)

		inline void SendDateOut(RWCString& pTag, RWCString& pData)
		{
			std::ostringstream m_strstrm;
			pTag = pTag.strip( RWCString::both, ' ' );
			pData = pData.strip( RWCString::both, ' ' );
			RWCString m_line;
			if (pData.length() == 0)
			{
				m_strstrm << "<" << pTag << " />";
				m_line = m_strstrm.str();
				m_strstrm.str("");
			} 
			else
			{
				m_strstrm << "<" << pTag << ">";
				m_strstrm << DateCheck(pData);
				m_strstrm << "</" << pTag << ">" << endl;
				m_line = m_strstrm.str();
				m_strstrm.str("");
			}
			cout << m_line;
		}

		RWCString DateCheck(RWCString& pData)
		{
			std::ostringstream m_strstrm;
			RWCString m_year = "20";
			m_year.append(pData.std().substr(6, 2));
			RWCString m_month = pData.std().substr(3, 2);
			RWCString m_day = pData.std().substr(0, 2);
			RWCString m_time = pData.remove(0, 9);

			m_strstrm << m_year << "-" << m_month << "-" << m_day;
			m_strstrm << "T" << m_time;
			pData = m_strstrm.str();
			m_strstrm.str("");

			return pData;
		}
    };

}   // end SlapWare namespace
//:Special
#undef _ThisClass
#undef _NumBaseClass
