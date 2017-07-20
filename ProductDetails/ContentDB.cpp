// ContentDB.cpp : database record object class.
// Stephen La Pierre - original SlapWare 8/2/2011 10:48am
#include "ContentDB.h"
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
#define _ThisClass		CContentDB
#define _NumBaseClass	0

//:Custom
using namespace std;

namespace slapware 
{    // begin SlapWare namespace

    // +---------------+
    // |  Constructor  |
    // +---------------+
    CContentDB::CContentDB(void)
    {
    }
    // +--------------+
    // |  Destructor  |
    // +--------------+
    CContentDB::~CContentDB(void)
    {
    }
    // +--------------------+
    // |  Copy Constructor  |
    // +--------------------+
    CContentDB::CContentDB(const _ThisClass& rhs_)                          // Existing object being copied
    {
        //TODO:  Add copy construction code here.
		m_Content_Type_ID = rhs_.m_Content_Type_ID;
		m_Content_Area1 = rhs_.m_Content_Area1;
		m_Content_Area2 = rhs_.m_Content_Area2;
		m_Content_Area3 = rhs_.m_Content_Area3;
		m_Content_Type_Desc = rhs_.m_Content_Type_Desc;
    }
    // +----------------+
    // |  operator =()  |
    // +----------------+
    _ThisClass & CContentDB::operator =(const _ThisClass& rhs_)             // right-hand-side of assignment
    {
        if (&rhs_ != this)      // Always test for assignment to self.
        {
			m_Content_Type_ID = rhs_.m_Content_Type_ID;
			m_Content_Area1 = rhs_.m_Content_Area1;
			m_Content_Area2 = rhs_.m_Content_Area2;
			m_Content_Area3 = rhs_.m_Content_Area3;
			m_Content_Type_Desc = rhs_.m_Content_Type_Desc;
        }
        return *this;           // Return a reference to this object.
    }
    ///////////////////////////////
    //Clean quote's for SQL calls//
    ///////////////////////////////
    RWCString CContentDB::QuoteFix(RWCString& toCheck)
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
    RWCString CContentDB::CheckDate(RWCString& toCheck)
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
