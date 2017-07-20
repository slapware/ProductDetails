#ifdef WIN32
    #pragma once
    #pragma warning( disable : 4267 )  // Disable warning messages
#endif

#ifdef _DEBUG
    #define _RWCONFIG 15s
#else
    #define _RWCONFIG 12s
#endif

#include <rw/pointer/RWBodyBase.h>
#include <rw/pointer/RWHandleBase.h>
#include "MsSqlImp.h"

#define _ThisClass		CMsSqlHandle
using namespace std;

namespace slapware // begin SlapWare namespace
{
    class CMsSqlHandle :
    public RWHandleBase
    {
    public:
        CMsSqlHandle(void);
        ~CMsSqlHandle(void);
        CMsSqlHandle(const RWCString& _server, const RWCString _user, const RWCString _pswd, const RWCString _db);
        // Is in error condition
        bool check(void);
        // return vendorMessage2 and reset m_inError to false.
        RWCString ErrorReport();
        // Perform insert or update SQL, not query result
        long Update(RWCString& pSql);
        long GetStr(RWCString& pSql, RWCString& param1);
        long GetStrStr(RWCString& pSql, RWCString& param1, RWCString& param2);
        long GetStrStrStr(RWCString& pSql, RWCString& param1, RWCString& param2, RWCString& param3);
        long GetStrStrStrStr(RWCString& pSql, RWCString& param1, RWCString& param2, RWCString& param3, RWCString& param4);
        long GetStrStrStrStrStr(RWCString& pSql, RWCString& param1, RWCString& param2, RWCString& param3, RWCString& param4, RWCString& param5);
        int GetCount(RWCString& pSql);
        int GetInt(RWCString& pSql, int& param1);
        long GetLong(RWCString& pSql, long& param1);
        int GetStrInt(RWCString& pSql, RWCString& param1, int& param2);
        long GetStrLong(RWCString& pSql, RWCString& param1, long& param2);
        // Perform query to return variable collection of db results
        int Get_dbReport(RWCString& pSql, RWTValDlist<CDbFace>&pDashDb);
		int Get_Content(RWCString& pSql, RWTValDlist<CContentDB>&pContentDb);
		int Get_Contrib(RWCString& pSql, RWTValDlist<CContributorDB>&pContribDb);
		int Get_Bisac(RWCString& pSql, RWTValDlist<CBisacDB>&pBisacDb);
		int Get_Category(RWCString& pSql, RWTValDlist<CCategoryDB>&pCategoryDb);
    protected:
        CMsSqlImp & body() const;
    };
}   // end SlapWare namespace
#undef _ThisClass

