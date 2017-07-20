// CategoryDB.h : database record object class.
// Stephen La Pierre - original SlapWare 8/2/2011 1:54pm
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
#define _ThisClass		CCategoryDB
#define _NumBaseClass	0

//:Custom
using namespace std;

namespace slapware 
{    // begin SlapWare namespace

    class CCategoryDB
    {
    public:
        CCategoryDB(void);
        CCategoryDB(const _ThisClass& rhs_);            // Existing object being copied
        _ThisClass& operator = (const _ThisClass& rhs_);    // right-hand-side of assignment
        virtual ~CCategoryDB(void);
        RWCString QuoteFix(RWCString& toCheck); // for SQL clean
        RWCString CheckDate(RWCString& toCheck);// for date clean
        // Getter Setter calls *************
		RWCString Category_Desc() const { return m_Category_Desc; }
		void Category_Desc(RWCString val) { m_Category_Desc = val; }
		RWCString Category_Type_Desc() const { return m_Category_Type_Desc; }
		void Category_Type_Desc(RWCString val) { m_Category_Type_Desc = val; }

    private:
		RWCString m_Category_Desc;
		RWCString m_Category_Type_Desc;
	};

}   // end SlapWare namespace
//:Special
#undef _ThisClass
#undef _NumBaseClass
