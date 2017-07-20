// BisacDB.h : database record object class.
// Stephen La Pierre - original SlapWare 8/2/2011 1:22pm
#pragma once
#pragma warning( disable : 4267 )  // Disable warning messages

#ifdef _DEBUG
    #define _RWCONFIG 15s
#else
    #define _RWCONFIG 12s
#endif

#include <iostream>
#include "Markup.h" // define MARKUP_STL
#include <rw/cstring.h>

//:Special
#define _ThisClass		CBisacDB
#define _NumBaseClass	0

//:Custom
using namespace std;

namespace slapware 
{    // begin SlapWare namespace

    class CBisacDB
    {
    public:
        CBisacDB(void);
        CBisacDB(const _ThisClass& rhs_);           // Existing object being copied
        _ThisClass& operator = (const _ThisClass& rhs_);    // right-hand-side of assignment
        virtual ~CBisacDB(void);
        RWCString QuoteFix(RWCString& toCheck); // for SQL clean
        RWCString CheckDate(RWCString& toCheck);// for date clean
        // Getter Setter calls *************
		RWCString BISAC_Code() const { return m_BISAC_Code; }
		void BISAC_Code(RWCString val) { m_BISAC_Code = val; }
		RWCString BISAC_Position() const { return m_BISAC_Position; }
		void BISAC_Position(RWCString val) { m_BISAC_Position = val; }
		RWCString BISAC_Revision() const { return m_BISAC_Revision; }
		void BISAC_Revision(RWCString val) { m_BISAC_Revision = val; }
		RWCString BISAC_Desc() const { return m_BISAC_Desc; }
		void BISAC_Desc(RWCString val) { m_BISAC_Desc = val; }

    private:
		RWCString m_BISAC_Code;
		RWCString m_BISAC_Position;
		RWCString m_BISAC_Revision;
		RWCString m_BISAC_Desc;
	};

}   // end SlapWare namespace
//:Special
#undef _ThisClass
#undef _NumBaseClass
