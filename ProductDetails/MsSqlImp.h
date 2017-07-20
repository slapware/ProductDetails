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

#include <rw/rstream.h>
#include <rw/db/db.h>
#include <rw/db/dbmgr.h>
#include <rw/db/tbuffer.h>
#include <rw/tvdlist.h>
#include "DbFace.h"
#include "ContentDB.h"
#include "ContributorDB.h"
#include "BisacDB.h"
#include "CategoryDB.h"

#define _ThisClass		CMsSqlImp
using namespace std;

namespace slapware 
{    // begin SlapWare namespace
    class CMsSqlImp :
    public RWBodyBase
    {
    public:
        friend class CMsSqlHandle;
    protected:
        virtual ~CMsSqlImp(void);
    private:
        CMsSqlImp(void);
        CMsSqlImp(const RWCString& _server, const RWCString _user, const RWCString _pswd, const RWCString _db);
        RWCString m_server;
        RWCString m_user;
        RWCString m_pswd;
        RWCString m_db;
        RWCString m_url;
        RWCString m_type;
        RWCString m_error;
        bool m_inError;

        RWDBDatabase mySql;
        //RWDBConnection m_conn;
        // is connection valid
    public:
        // Is in error condition
        bool check(void);
        // make the connection
        void init(void);
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
	};
}   // end SlapWare namespace
#undef _ThisClass
