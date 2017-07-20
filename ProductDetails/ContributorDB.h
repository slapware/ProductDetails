// ContributorDB.h : database record object class.
// Stephen La Pierre - original SlapWare 8/2/2011 12:11pm
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
#define _ThisClass		CContributorDB
#define _NumBaseClass	0

//:Custom
using namespace std;

namespace slapware 
{    // begin SlapWare namespace

    class CContributorDB
    {
    public:
        CContributorDB(void);
//        CContributorDB(const CContributorDB& rhs_);         // Existing object being copied
        CContributorDB(const _ThisClass& rhs_);         // Existing object being copied
        _ThisClass& operator = (const _ThisClass& rhs_);    // right-hand-side of assignment
//        CContributorDB& operator = (const CContributorDB& rhs_);    // right-hand-side of assignment
        virtual ~CContributorDB(void);
        RWCString QuoteFix(RWCString& toCheck); // for SQL clean
        RWCString CheckDate(RWCString& toCheck);// for date clean
        // Getter Setter calls *************
		RWCString Display_Name() const { return m_Display_Name; }
		void Display_Name(RWCString val) { m_Display_Name = val; }
		RWCString First_Name() const { return m_First_Name; }
		void First_Name(RWCString val) { m_First_Name = val; }
		RWCString Middle_Name() const { return m_Middle_Name; }
		void Middle_Name(RWCString val) { m_Middle_Name = val; }
		RWCString Last_Name() const { return m_Last_Name; }
		void Last_Name(RWCString val) { m_Last_Name = val; }
		RWCString Role() const { return m_Role; }
		void Role(RWCString val) { m_Role = val; }
		RWCString Contributor_Order() const { return m_Contributor_Order; }
		void Contributor_Order(RWCString val) { m_Contributor_Order = val; }
		RWCString Contributor_Persona_ID() const { return m_Contributor_Persona_ID; }
		void Contributor_Persona_ID(RWCString val) { m_Contributor_Persona_ID = val; }

    private:
		RWCString m_Display_Name;
		RWCString m_First_Name;
		RWCString m_Middle_Name;
		RWCString m_Last_Name;
		RWCString m_Role;
		RWCString m_Contributor_Order;
		RWCString m_Contributor_Persona_ID;
	};

}   // end SlapWare namespace
//:Special
#undef _ThisClass
#undef _NumBaseClass
