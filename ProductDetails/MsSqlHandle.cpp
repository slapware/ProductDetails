#include "MsSqlHandle.h"

#define _ThisClass		CMsSqlHandle
namespace slapware 
{    // begin SlapWare namespace
    CMsSqlHandle::CMsSqlHandle(void)
    {
    }

    CMsSqlHandle::~CMsSqlHandle(void)
    {
    }

    CMsSqlHandle::CMsSqlHandle(const RWCString& _server, const RWCString _user, const RWCString _pswd, const RWCString _db) :
    RWHandleBase(new CMsSqlImp(_server, _user, _pswd, _db))
    {
        //
    }

    CMsSqlImp& CMsSqlHandle::body() const
    {
        return(CMsSqlImp &)RWHandleBase::body();
    }

    bool CMsSqlHandle::check(void)
    {
        return(body().check());
    }

    RWCString CMsSqlHandle::ErrorReport()
    {
        return(body().ErrorReport());
    }

    long CMsSqlHandle::Update(RWCString& pSql)
    {
        return(body().Update(pSql));
    }

    long CMsSqlHandle::GetStr(RWCString& pSql, RWCString& param1)
    {
        return(body().GetStr(pSql, param1));
    }

    long CMsSqlHandle::GetStrStr(RWCString& pSql, RWCString& param1, RWCString& param2)
    {
        return(body().GetStrStr(pSql, param1, param2));
    }

    long CMsSqlHandle::GetStrStrStr(RWCString& pSql, RWCString& param1, RWCString& param2, RWCString& param3)
    {
        return(body().GetStrStrStr(pSql, param1, param2, param3));
    }

    long CMsSqlHandle::GetStrStrStrStr(RWCString& pSql, RWCString& param1, RWCString& param2, RWCString& param3, RWCString& param4)
    {
        return(body().GetStrStrStrStr(pSql, param1, param2, param3, param4));
    }

    long CMsSqlHandle::GetStrStrStrStrStr(RWCString& pSql, RWCString& param1, RWCString& param2, RWCString& param3, RWCString& param4, RWCString& param5)
    {
        return(body().GetStrStrStrStrStr(pSql, param1, param2, param3, param4, param5));
    }

    int CMsSqlHandle::GetCount(RWCString& pSql)
    {
        return(body().GetCount(pSql));
    }

    int CMsSqlHandle::GetInt(RWCString& pSql, int& param1)
    {
        return(body().GetInt(pSql, param1));
    }

    long CMsSqlHandle::GetLong(RWCString& pSql, long& param1)
    {
        return(body().GetLong(pSql, param1));
    }

    int CMsSqlHandle::GetStrInt(RWCString& pSql, RWCString& param1, int& param2)
    {
        return(body().GetStrInt(pSql, param1, param2));
    }

    long CMsSqlHandle::GetStrLong(RWCString& pSql, RWCString& param1, long& param2)
    {
        return(body().GetStrLong(pSql, param1, param2));
    }

    int CMsSqlHandle::Get_dbReport(RWCString& pSql, RWTValDlist<CDbFace>&pDashDb)
    {
        return(body().Get_dbReport(pSql, pDashDb));
    }

	int CMsSqlHandle::Get_Content(RWCString& pSql, RWTValDlist<CContentDB>&pContentDb)
	{
		return(body().Get_Content(pSql, pContentDb));
	}

	int CMsSqlHandle::Get_Contrib(RWCString& pSql, RWTValDlist<CContributorDB>&pContribDb)
	{
		return(body().Get_Contrib(pSql, pContribDb));
	}

	int CMsSqlHandle::Get_Bisac(RWCString& pSql, RWTValDlist<CBisacDB>&pBisacDb)
	{
		return(body().Get_Bisac(pSql, pBisacDb));
	}

	int CMsSqlHandle::Get_Category(RWCString& pSql, RWTValDlist<CCategoryDB>&pCategoryDb)
	{
		return(body().Get_Category(pSql, pCategoryDb));
	}
}   // end SlapWare namespace

#undef _ThisClass

