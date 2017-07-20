// ContributorDB.cpp : database record object class.
// Stephen La Pierre - original SlapWare 8/2/2011 12:11pm
#include "ContributorDB.h"
#include <rw/tools/regex.h>

#ifdef WIN32
    #include "Windows.h"
    #include <direct.h> 
    #define GetCurrentDir _getcwd 
#else 
    #include <unistd.h> 
    #define GetCurrentDir getcwd 
#endif

//:Special
#define _ThisClass		CContributorDB
#define _NumBaseClass	0

//:Custom
using namespace std;

namespace slapware 
{    // begin SlapWare namespace

    // +---------------+
    // |  Constructor  |
    // +---------------+
    CContributorDB::CContributorDB(void)
    {
    }
    // +--------------+
    // |  Destructor  |
    // +--------------+
    CContributorDB::~CContributorDB(void)
    {
    }
    // +--------------------+
    // |  Copy Constructor  |
    // +--------------------+
    CContributorDB::CContributorDB(const _ThisClass& rhs_)                          // Existing object being copied
    {
        //TODO:  Add copy construction code here.
		m_Display_Name = rhs_.m_Display_Name;
		m_First_Name = rhs_.m_First_Name;
		m_Middle_Name = rhs_.m_Middle_Name;
		m_Last_Name = rhs_.m_Last_Name;
		m_Role = rhs_.m_Role;
		m_Contributor_Order = rhs_.m_Contributor_Order;
		m_Contributor_Persona_ID = rhs_.m_Contributor_Persona_ID;
    }
    // +----------------+
    // |  operator =()  |
    // +----------------+
    _ThisClass & CContributorDB::operator =(const _ThisClass& rhs_)             // right-hand-side of assignment
   {
        if (&rhs_ != this)      // Always test for assignment to self.
        {
			m_Display_Name = rhs_.m_Display_Name;
			m_First_Name = rhs_.m_First_Name;
			m_Middle_Name = rhs_.m_Middle_Name;
			m_Last_Name = rhs_.m_Last_Name;
			m_Role = rhs_.m_Role;
			m_Contributor_Order = rhs_.m_Contributor_Order;
			m_Contributor_Persona_ID = rhs_.m_Contributor_Persona_ID;
        }
        return *this;           // Return a reference to this object.
    }
    ///////////////////////////////
    //Clean quote's for SQL calls//
    ///////////////////////////////
    RWCString CContributorDB::QuoteFix(RWCString& toCheck)
    {
        if (toCheck.contains("'", RWCString::ignoreCase))
        {
            RWTRegex<char> qck("'");
            qck.replace(toCheck, "''", 0);
        }
        return toCheck;
    }
    /////////////////////////////
    //Clean dates for MySql SQL//
    /////////////////////////////
    RWCString CContributorDB::CheckDate(RWCString& toCheck)
    { 
        if (toCheck.contains("INVALID", RWCString::ignoreCase))
        {
            toCheck = "1900-01-01";
        }

        if (toCheck.isNull())
        {
            toCheck = "1900-01-01";
        }

        return toCheck; 
    }

}   // end SlapWare namespace
//:Special
#undef _ThisClass
#undef _NumBaseClass
