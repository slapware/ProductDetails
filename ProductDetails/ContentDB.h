// ContentDB.h : database record object class.
// Stephen La Pierre - original SlapWare 8/2/2011 10:48am
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
#define _ThisClass		CContentDB
#define _NumBaseClass	0

//:Custom
using namespace std;

namespace slapware 
{    // begin SlapWare namespace

    class CContentDB
    {
    public:
        CContentDB(void);
        CContentDB(const _ThisClass& rhs_);         // Existing object being copied
        _ThisClass& operator = (const _ThisClass& rhs_);    // right-hand-side of assignment
        virtual ~CContentDB(void);
        RWCString QuoteFix(RWCString& toCheck); // for SQL clean
        RWCString CheckDate(RWCString& toCheck);// for date clean
        // Getter Setter calls *************
		RWCString Content_Type_ID() const { return m_Content_Type_ID; }
		void Content_Type_ID(RWCString val) { m_Content_Type_ID = val; }
		RWCString Content_Area1() const { return m_Content_Area1; }
		void Content_Area1(RWCString val) { m_Content_Area1 = val; }
		RWCString Content_Area2() const { return m_Content_Area2; }
		void Content_Area2(RWCString val) { m_Content_Area2 = val; }
		RWCString Content_Area3() const { return m_Content_Area3; }
		void Content_Area3(RWCString val) { m_Content_Area3 = val; }
		RWCString Content_Type_Desc() const { return m_Content_Type_Desc; }
		void Content_Type_Desc(RWCString val) { m_Content_Type_Desc = val; }

    private:
		RWCString m_Content_Type_ID;
		RWCString m_Content_Area1;
		RWCString m_Content_Area2;
		RWCString m_Content_Area3;
		RWCString m_Content_Type_Desc;
	};

}   // end SlapWare namespace
//:Special
#undef _ThisClass
#undef _NumBaseClass
