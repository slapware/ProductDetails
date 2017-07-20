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


//:Custom
using namespace std;

namespace slapware 
{    // begin SlapWare namespace

    class CSlapOut
    {
    public:
		inline void SendOut(RWCString pTag, RWCString pData)
		{
			std::ostringstream m_strstrm;
			pTag = pTag.strip( RWCString::both, ' ' );
			pData = pData.strip( RWCString::both, ' ' );
			RWCString m_line;
			if (pData.length() == 0)
			{
				m_strstrm << "<" << pTag << " />" << endl;
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

		inline void SendCdataOut(RWCString pTag, RWCString pData)
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

				if (!isCdata)
				{
					RWCRegexp rlt("<");
					hloc = 0;
					hloc = rlt.index(pRecord, &pLen, 0);
					while (hloc != RW_NPOS)
					{
						pRecord(rlt) = "&lt;";
						hloc = rlt.index(pRecord, &pLen, hloc + 1);
					}
	
					RWCRegexp rgt(">");
					hloc = 0;
					hloc = rgt.index(pRecord, &pLen, 0);
					while (hloc != RW_NPOS)
					{
						pRecord(rgt) = "&gt;";
						hloc = rgt.index(pRecord, &pLen, hloc + 1);
					}
				}

				RWCRegexp ramp("& ");
				pRecord(ramp) = "&amp; ";

				// ]]>
				RWCRegexp rCdata("]]>");
				hloc = rCdata.index(pRecord, &pLen, 0);
				while (hloc != RW_NPOS)
				{
					pRecord(rCdata) = "&93;&93;&gt;";
					hloc = rCdata.index(pRecord, &pLen, hloc + 1);
				}

				char p3tx = 0xE280;
				std::string::size_type indexins = pRecord.std().find(p3tx);

				indexins = 0;
				while ((indexins = pRecord.std().find ( p3tx, indexins ) ) != string::npos) // 0x04 Fix
				{
					pRecord.std().replace(indexins - 1, 2, " ");
					indexins++;      
				}

				RWCRegexp r84R("\x084");
				hloc = r84R.index(pRecord, &pLen, 0);
				while (hloc != RW_NPOS)
				{
					pRecord(r84R) = "\"";
					hloc = r84R.index(pRecord, &pLen, hloc + 1);
				}

				RWCRegexp r85amp("\x085");
				hloc = r85amp.index(pRecord, &pLen, 0);
				while (hloc != RW_NPOS)
				{
					pRecord(r85amp) = "-";
					hloc = r85amp.index(pRecord, &pLen, hloc + 1);
				}

				RWCRegexp r91amp("\x091");
				hloc = r91amp.index(pRecord, &pLen, 0);
				while (hloc != RW_NPOS)
				{
					pRecord(r91amp) = "&apos;";
					hloc = r91amp.index(pRecord, &pLen, hloc + 1);
				}

				RWCRegexp r6amp("\x092");
				hloc = r6amp.index(pRecord, &pLen, 0);
				while (hloc != RW_NPOS)
				{
					pRecord(r6amp) = "&apos;";
					hloc = r6amp.index(pRecord, &pLen, hloc + 1);
				}

				RWCRegexp r93amp("\x093");
				hloc = r93amp.index(pRecord, &pLen, 0);
				while (hloc != RW_NPOS)
				{
					pRecord(r93amp) = "&apos;";
					hloc = r93amp.index(pRecord, &pLen, hloc + 1);
				}

				RWCRegexp r94amp("\x094");
				hloc = r94amp.index(pRecord, &pLen, 0);
				while (hloc != RW_NPOS)
				{
					pRecord(r94amp) = "&apos;";
					hloc = r94amp.index(pRecord, &pLen, hloc + 1);
				}

				RWCRegexp r7amp("\x096");
				hloc = 0;
				hloc = r7amp.index(pRecord, &pLen, 0);
				while (hloc != RW_NPOS)
				{
					pRecord(r7amp) = "-";
					hloc = r7amp.index(pRecord, &pLen, hloc + 1);
				}

				RWCRegexp r8amp("\x097");
				hloc = 0;
				hloc = r8amp.index(pRecord, &pLen, 0);
				while (hloc != RW_NPOS)
				{
					pRecord(r8amp) = "-";
					hloc = r8amp.index(pRecord, &pLen, hloc + 1);
				}

				RWCRegexp r98amp("\x098");
				hloc = r98amp.index(pRecord, &pLen, 0);
				while (hloc != RW_NPOS)
				{
					pRecord(r98amp) = "&apos;";
					hloc = r98amp.index(pRecord, &pLen, hloc + 1);
				}

				RWCRegexp r99amp("\x099");
				hloc = r99amp.index(pRecord, &pLen, 0);
				while (hloc != RW_NPOS)
				{
					pRecord(r99amp) = "&apos;";
					hloc = r99amp.index(pRecord, &pLen, hloc + 1);
				}

				RWCRegexp r9Camp("\x09C");
				hloc = r9Camp.index(pRecord, &pLen, 0);
				while (hloc != RW_NPOS)
				{
					pRecord(r9Camp) = "-";
					hloc = r9Camp.index(pRecord, &pLen, hloc + 1);
				}

				RWCRegexp r9Damp("\x09D");
				hloc = r9Damp.index(pRecord, &pLen, 0);
				while (hloc != RW_NPOS)
				{
					pRecord(r9Damp) = "-";
					hloc = r9Damp.index(pRecord, &pLen, hloc + 1);
				}

				RWCRegexp rA0("\x0A0");
				hloc = 0;
				hloc = rA0.index(pRecord, &pLen, 0);
				while (hloc != RW_NPOS)
				{
					pRecord(rA0) = "-";
					hloc = rA0.index(pRecord, &pLen, hloc + 1);
				}

				RWCRegexp rA2("\x0A2");
				hloc = 0;
				hloc = rA2.index(pRecord, &pLen, 0);
				while (hloc != RW_NPOS)
				{
					pRecord(rA2) = "-";
					hloc = rA2.index(pRecord, &pLen, hloc + 1);
				}

				RWCRegexp rA6("\x0A6");
				hloc = 0;
				hloc = rA6.index(pRecord, &pLen, 0);
				while (hloc != RW_NPOS)
				{
					pRecord(rA6) = "-";
					hloc = rA6.index(pRecord, &pLen, hloc + 1);
				}

				RWCRegexp rE2("\x0E2");
				hloc = 0;
				hloc = rE2.index(pRecord, &pLen, 0);
				while (hloc != RW_NPOS)
				{
					pRecord(rE2) = "-";
					hloc = rE2.index(pRecord, &pLen, hloc + 1);
				}

				RWCRegexp rE9("\x0E9");
				hloc = 0;
				hloc = rE9.index(pRecord, &pLen, 0);
				while (hloc != RW_NPOS)
				{
					pRecord(rE9) = "-";
					hloc = rE9.index(pRecord, &pLen, hloc + 1);
				}

				RWCRegexp rDD("''");
				hloc = 0;
				hloc = rDD.index(pRecord, &pLen, 0);
				while (hloc != RW_NPOS)
				{
					pRecord(rDD) = "'";
					hloc = rDD.index(pRecord, &pLen, hloc + 1);
				}

				RWCRegexp rC2("\x0C2");
				hloc = 0;
				hloc = rC2.index(pRecord, &pLen, 0);
				while (hloc != RW_NPOS)
				{
					pRecord(rC2) = " ";
					hloc = rC2.index(pRecord, &pLen, hloc + 1);
				}


			}
			return pRecord;	
}
    };

}   // end SlapWare namespace
//:Special
#undef _ThisClass
#undef _NumBaseClass
