// BisacDB.cpp : database record object class.
// Stephen La Pierre - original SlapWare 8/2/2011 1:22pm
#include "BisacDB.h"
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
#define _ThisClass		CBisacDB
#define _NumBaseClass	0

//:Custom
using namespace std;

namespace slapware 
{    // begin SlapWare namespace

    // +---------------+
    // |  Constructor  |
    // +---------------+
    CBisacDB::CBisacDB(void)
    {
    }
    // +--------------+
    // |  Destructor  |
    // +--------------+
    CBisacDB::~CBisacDB(void)
    {
    }
    // +--------------------+
    // |  Copy Constructor  |
    // +--------------------+
    CBisacDB::CBisacDB(const _ThisClass& rhs_)                          // Existing object being copied
    {
        //TODO:  Add copy construction code here.
		m_BISAC_Code = rhs_.m_BISAC_Code;
		m_BISAC_Position = rhs_.m_BISAC_Position;
		m_BISAC_Revision = rhs_.m_BISAC_Revision;
		m_BISAC_Desc = rhs_.m_BISAC_Desc;
    }
    // +----------------+
    // |  operator =()  |
    // +----------------+
    _ThisClass & CBisacDB::operator =(const _ThisClass& rhs_)             // right-hand-side of assignment
    {
        if (&rhs_ != this)      // Always test for assignment to self.
        {
			m_BISAC_Code = rhs_.m_BISAC_Code;
			m_BISAC_Position = rhs_.m_BISAC_Position;
			m_BISAC_Revision = rhs_.m_BISAC_Revision;
			m_BISAC_Desc = rhs_.m_BISAC_Desc;
        }
        return *this;           // Return a reference to this object.
    }
    ///////////////////////////////
    //Clean quote's for SQL calls//
    ///////////////////////////////
    RWCString CBisacDB::QuoteFix(RWCString& toCheck)
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
    RWCString CBisacDB::CheckDate(RWCString& toCheck)
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
