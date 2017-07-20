#include "MsSqlImp.h"

#define _ThisClass		CMsSqlImp
namespace slapware 
{    // begin SlapWare namespace
    CMsSqlImp::CMsSqlImp(void)
    {
    }

    CMsSqlImp::~CMsSqlImp(void)
    {
    }

    CMsSqlImp::CMsSqlImp(const RWCString& _server, const RWCString _user, const RWCString _pswd, const RWCString _db) :
    m_server(_server), m_user(_user), m_pswd(_pswd), m_db(_db)
    {
        m_inError = false;
        init();
    }

    bool CMsSqlImp::check(void)
    {
        return m_inError;
    }

    RWCString CMsSqlImp::ErrorReport()
    {
        m_inError = false;
        return m_error;
    }

    // make the connection
    void CMsSqlImp::init(void)
    {
        try
        {
            mySql = RWDBManager::database("MS_SQL", m_server, m_user, m_pswd, m_db);
            RWDBStatus status = mySql.status();
            if (status.errorCode() != RWDBStatus::ok)
            {
                m_inError = true;
                m_error = status.vendorMessage2();
            }
        } catch (RWxmsg emsg)
        {
            m_inError = true;
            m_error = emsg.why();
        }
        //m_conn = mySql.connection();
    }

    long CMsSqlImp::Update(RWCString& pSql)
    {
        RWDBConnection conn = mySql.connection();
        RWDBOSql myQuery(pSql);
        myQuery.execute(conn);
        return myQuery.rowsAffected();
    }

    long CMsSqlImp::GetStr(RWCString& pSql, RWCString& param1)
    {
        RWDBConnection conn = mySql.connection();
        RWDBOSql myQuery(pSql);
        myQuery.execute(conn);
        if ( myQuery.isValid(), RWDBOSql::Query )
        {
            RWDBTBuffer<RWCString> szparam1(1);
            myQuery[0] >> szparam1; 
            while (myQuery.fetch(), myQuery.rowsFetched() > 0)
            {
                param1 = szparam1[0];
            }
        }
        return(myQuery.rowsFetched());
    }

    long CMsSqlImp::GetStrStr(RWCString& pSql, RWCString& param1, RWCString& param2)
    {
        RWDBConnection conn = mySql.connection();
        RWDBOSql myQuery(pSql);
        myQuery.execute(conn);
        if ( myQuery.isValid(), RWDBOSql::Query )
        {
            RWDBTBuffer<RWCString> szparam1(1);
            RWDBTBuffer<RWCString> szparam2(1);
            myQuery[0] >> szparam1; 
            myQuery[0] >> szparam2; 
            while (myQuery.fetch(), myQuery.rowsFetched() > 0)
            {
                param1 = szparam1[0];
                param2 = szparam2[0];
            }
        }
        return(myQuery.rowsFetched());
    }

    long CMsSqlImp::GetStrStrStr(RWCString& pSql, RWCString& param1, RWCString& param2, RWCString& param3)
    {
        RWDBConnection conn = mySql.connection();
        RWDBOSql myQuery(pSql);
        myQuery.execute(conn);
        if ( myQuery.isValid(), RWDBOSql::Query )
        {
            RWDBTBuffer<RWCString> szparam1(1);
            RWDBTBuffer<RWCString> szparam2(1);
            RWDBTBuffer<RWCString> szparam3(1);
            myQuery[0] >> szparam1; 
            myQuery[0] >> szparam2; 
            myQuery[0] >> szparam3; 
            while (myQuery.fetch(), myQuery.rowsFetched() > 0)
            {
                param1 = szparam1[0];
                param2 = szparam2[0];
                param3 = szparam3[0];
            }
        }
        return(myQuery.rowsFetched());
    }

    long CMsSqlImp::GetStrStrStrStr(RWCString& pSql, RWCString& param1, RWCString& param2, RWCString& param3, RWCString& param4)
    {
        RWDBConnection conn = mySql.connection();
        RWDBOSql myQuery(pSql);
        myQuery.execute(conn);
        if ( myQuery.isValid(), RWDBOSql::Query )
        {
            RWDBTBuffer<RWCString> szparam1(1);
            RWDBTBuffer<RWCString> szparam2(1);
            RWDBTBuffer<RWCString> szparam3(1);
            RWDBTBuffer<RWCString> szparam4(1);
            myQuery[0] >> szparam1; 
            myQuery[0] >> szparam2; 
            myQuery[0] >> szparam3; 
            myQuery[0] >> szparam4; 
            while (myQuery.fetch(), myQuery.rowsFetched() > 0)
            {
                param1 = szparam1[0];
                param2 = szparam2[0];
                param3 = szparam3[0];
                param4 = szparam4[0];
            }
        }
        return(myQuery.rowsFetched());
    }

    long CMsSqlImp::GetStrStrStrStrStr(RWCString& pSql, RWCString& param1, RWCString& param2, RWCString& param3, RWCString& param4, RWCString& param5)
    {
        RWDBConnection conn = mySql.connection();
        RWDBOSql myQuery(pSql);
        myQuery.execute(conn);
        if ( myQuery.isValid(), RWDBOSql::Query )
        {
            RWDBTBuffer<RWCString> szparam1(1);
            RWDBTBuffer<RWCString> szparam2(1);
            RWDBTBuffer<RWCString> szparam3(1);
            RWDBTBuffer<RWCString> szparam4(1);
            RWDBTBuffer<RWCString> szparam5(1);
            myQuery[0] >> szparam1; 
            myQuery[0] >> szparam2; 
            myQuery[0] >> szparam3; 
            myQuery[0] >> szparam4; 
            myQuery[0] >> szparam5; 
            while (myQuery.fetch(), myQuery.rowsFetched() > 0)
            {
                param1 = szparam1[0];
                param2 = szparam2[0];
                param3 = szparam3[0];
                param4 = szparam4[0];
                param4 = szparam5[0];
            }
        }
        return(myQuery.rowsFetched());
    }

    int CMsSqlImp::GetCount(RWCString& pSql)
    {
        RWDBConnection conn = mySql.connection();
        RWDBOSql myQuery(pSql);
        RWDBTBuffer<unsigned> result(1);
        myQuery.execute(conn);
        int answ = 0;
        if ( myQuery.isValid(), RWDBOSql::Query )
        {
            myQuery[0] >> result;
            while (myQuery.fetch(), myQuery.rowsFetched() > 0)
            {
                answ = result[0];
            }
        }
        return answ;
    }

    int CMsSqlImp::GetInt(RWCString& pSql, int& param1)
    {
        RWDBConnection conn = mySql.connection();
        RWDBOSql myQuery(pSql);
        RWDBTBuffer<unsigned> dresult(1);
        myQuery.execute(conn);
        if ( myQuery.isValid(), RWDBOSql::Query )
        {
            myQuery[0] >> dresult;
            param1 = dresult[0];
            while (myQuery.fetch(), myQuery.rowsFetched() > 0)
            {
                param1 = dresult[0];
            }
        }
        return param1;
    }

    long CMsSqlImp::GetLong(RWCString& pSql, long& param1)
    {
        RWDBConnection conn = mySql.connection();
        RWDBOSql myQuery(pSql);
        RWDBTBuffer<unsigned> dresult(1);
        myQuery.execute(conn);
        if ( myQuery.isValid(), RWDBOSql::Query )
        {
            myQuery[0] >> dresult;
            param1 = dresult[0];
            while (myQuery.fetch(), myQuery.rowsFetched() > 0)
            {
                param1 = dresult[0];
            }
        }
        return param1;
    }

    int CMsSqlImp::GetStrInt(RWCString& pSql, RWCString& param1, int& param2)
    {
        RWDBConnection conn = mySql.connection();
        RWDBOSql myQuery(pSql);
        RWDBTBuffer<RWCString> szparam1(1);
        RWDBTBuffer<unsigned> dresult(1);
        myQuery.execute(conn);
        if ( myQuery.isValid(), RWDBOSql::Query )
        {
            myQuery[0] >> szparam1 >> dresult;
            while (myQuery.fetch(), myQuery.rowsFetched() > 0)
            {
                param1 = szparam1[0];
                param2 = dresult[0];
            }
        }
        return param2;
    }

    long CMsSqlImp::GetStrLong(RWCString& pSql, RWCString& param1, long& param2)
    {
        RWDBConnection conn = mySql.connection();
        RWDBOSql myQuery(pSql);
        RWDBTBuffer<RWCString> szparam1(1);
        RWDBTBuffer<unsigned> dresult(1);
        myQuery.execute(conn);
        if ( myQuery.isValid(), RWDBOSql::Query )
        {
            myQuery[0] >> szparam1 >> dresult;
            while (myQuery.fetch(), myQuery.rowsFetched() > 0)
            {
                param1 = szparam1[0];
                param2 = dresult[0];
            }
        }
        return param2;
    }

	int CMsSqlImp::Get_Category(RWCString& pSql, RWTValDlist<CCategoryDB>&pCategoryDb)
	{
		RWDBConnection conn = mySql.connection();
		RWDBOSql myQuery(pSql);
		myQuery.execute(conn);
		int didFetch = 0;
		if ( myQuery.isValid(), myQuery.hasResult() )
		{
			RWDBTBuffer<RWCString> szCategory_Desc(10);
			RWDBTBuffer<RWCString> szCategory_Type_Desc(10);
			myQuery[0] >> szCategory_Desc >> szCategory_Type_Desc;
			while (myQuery.fetch(), myQuery.rowsFetched() > 0)
			{
				for (int i = 0; i < myQuery.rowsFetched(); i++ )
				{
					CCategoryDB pCategoryDBItem;
					pCategoryDBItem.Category_Desc(szCategory_Desc[i]);
					pCategoryDBItem.Category_Type_Desc(szCategory_Type_Desc[i]);
					// *******************
					pCategoryDb.insert(pCategoryDBItem);
					didFetch++;
				}
			}
		}
		else
		{
			m_inError = true;
			m_error = myQuery.status().vendorMessage2();
		}
		return didFetch;
	}

	int CMsSqlImp::Get_Bisac(RWCString& pSql, RWTValDlist<CBisacDB>&pBisacDb)
	{
		RWDBConnection conn = mySql.connection();
		RWDBOSql myQuery(pSql);
		myQuery.execute(conn);
		int didFetch = 0;
		if ( myQuery.isValid(), myQuery.hasResult() )
		{
			RWDBTBuffer<RWCString> szBISAC_Code(10);
			RWDBTBuffer<RWCString> szBISAC_Position(10);
			RWDBTBuffer<RWCString> szBISAC_Revision(10);
			RWDBTBuffer<RWCString> szBISAC_Desc(10);
			myQuery[0] >> szBISAC_Code >> szBISAC_Position >> 
				szBISAC_Revision >> szBISAC_Desc;
			while (myQuery.fetch(), myQuery.rowsFetched() > 0)
			{
				for (int i = 0; i < myQuery.rowsFetched(); i++ )
				{
					CBisacDB BisacDbItem;
					BisacDbItem.BISAC_Code(szBISAC_Code[i]);
					BisacDbItem.BISAC_Position(szBISAC_Position[i]);
					BisacDbItem.BISAC_Revision(szBISAC_Revision[i]);
					BisacDbItem.BISAC_Desc(szBISAC_Desc[i]);
					// *******************
					pBisacDb.insert(BisacDbItem);
					didFetch++;
				}
			}
		}
		else
		{
			m_inError = true;
			m_error = myQuery.status().vendorMessage2();
		}
		return didFetch;
	}

	int CMsSqlImp::Get_Contrib(RWCString& pSql, RWTValDlist<CContributorDB>&pContribDb)
	{
		RWDBConnection conn = mySql.connection();
		RWDBOSql myQuery(pSql);
		myQuery.execute(conn);
		int didFetch = 0;
		if ( myQuery.isValid(), myQuery.hasResult() )
		{
			RWDBTBuffer<RWCString> szDisplay_Name(10);
			RWDBTBuffer<RWCString> szFirst_Name(10);
			RWDBTBuffer<RWCString> szMiddle_Name(10);
			RWDBTBuffer<RWCString> szLast_Name(10);
			RWDBTBuffer<RWCString> szRole(10);
			RWDBTBuffer<RWCString> szContributor_Order(10);
			RWDBTBuffer<RWCString> szContributor_Persona_ID(10);
			myQuery[0] >> szDisplay_Name >> szFirst_Name >> szMiddle_Name >> 
				szLast_Name >> szRole >> szContributor_Order >> szContributor_Persona_ID;
			while (myQuery.fetch(), myQuery.rowsFetched() > 0)
			{
				for (int i = 0; i < myQuery.rowsFetched(); i++ )
				{
					CContributorDB ContribDbItem;
					ContribDbItem.Display_Name(szDisplay_Name[i]);
					ContribDbItem.First_Name(szFirst_Name[i]);
					ContribDbItem.Middle_Name(szMiddle_Name[i]);
					ContribDbItem.Last_Name(szLast_Name[i]);
					ContribDbItem.Role(szRole[i]);
					ContribDbItem.Contributor_Order(szContributor_Order[i]);
					ContribDbItem.Contributor_Persona_ID(szContributor_Persona_ID[i]);
					// *******************
					pContribDb.insert(ContribDbItem);
					didFetch++;
				}
			}
		}
		else
		{
			m_inError = true;
			m_error = myQuery.status().vendorMessage2();
		}
		return didFetch;
	}


	int CMsSqlImp::Get_Content(RWCString& pSql, RWTValDlist<CContentDB>&pContentDb)
	{
		RWDBConnection conn = mySql.connection();
		RWDBOSql myQuery(pSql);
		myQuery.execute(conn);
		int didFetch = 0;
		if ( myQuery.isValid(), myQuery.hasResult() )
		{
			RWDBTBuffer<RWCString> szContent_Type_ID(10);
			RWDBTBuffer<RWCString> szContent_Area1(10);
			RWDBTBuffer<RWCString> szContent_Area2(10);
			RWDBTBuffer<RWCString> szContent_Area3(10);
			RWDBTBuffer<RWCString> szContent_Type_Desc(10);
			myQuery[0] >> szContent_Type_ID >> szContent_Area1 >> 
				szContent_Area2 >> szContent_Area3 >> szContent_Type_Desc;
			while (myQuery.fetch(), myQuery.rowsFetched() > 0)
			{
				for (int i = 0; i < myQuery.rowsFetched(); i++ )
				{
					CContentDB contentDbItem;
					contentDbItem.Content_Type_ID(szContent_Type_ID[i]);
					contentDbItem.Content_Area1(szContent_Area1[i]);
					contentDbItem.Content_Area2(szContent_Area2[i]);
					contentDbItem.Content_Area3(szContent_Area3[i]);
					contentDbItem.Content_Type_Desc(szContent_Type_Desc[i]);
					// *******************
					pContentDb.insert(contentDbItem);
					didFetch++;
				}
			}
		}
		else
		{
			m_inError = true;
			m_error = myQuery.status().vendorMessage2();
		}
		return didFetch;
	}

    int CMsSqlImp::Get_dbReport(RWCString& pSql, RWTValDlist<CDbFace>&detailDb)
    {
        RWDBConnection conn = mySql.connection();
        RWDBOSql myQuery(pSql);
        myQuery.execute(conn);
        int didFetch = 0;
        if ( myQuery.isValid(), myQuery.hasResult() )
        {
            RWDBTBuffer<RWCString> szProduct_Group_ID(10);
            RWDBTBuffer<RWCString> szAges(10);
            RWDBTBuffer<RWCString> szBest_Seller_Flag(10);
            RWDBTBuffer<RWCString> szCatalog_Name(10);
			RWDBTBuffer<RWCString> szEditorial_Imprint(10);
            RWDBTBuffer<RWCString> szCoverImageURL_Large(10);
            RWDBTBuffer<RWCString> szCoverImageURL_Medium(10);
            RWDBTBuffer<RWCString> szCoverImageURL_MediumLarge(10);
            RWDBTBuffer<RWCString> szCoverImageURL_Small(10);
            RWDBTBuffer<RWCString> szFormat(10);
            RWDBTBuffer<RWCString> szFuture_Release_Flag(10);
            RWDBTBuffer<RWCString> szGrade_End(10);
			RWDBTBuffer<RWCString> szGrade_Start(10);
			RWDBTBuffer<RWCString> szHas_Essay(10);
			RWDBTBuffer<RWCString> szImprint(10);
			RWDBTBuffer<RWCString> szISBN(10);
			RWDBTBuffer<RWCString> szLocale_Desc(10);
			RWDBTBuffer<RWCString> szMax_Age(10);
			RWDBTBuffer<RWCString> szMin_Age(10);
			RWDBTBuffer<RWCString> szNew_Release_Flag(10);
			RWDBTBuffer<RWCString> szNo_of_Reviews(10);
			RWDBTBuffer<RWCString> szNum_Of_Pages(10);
			RWDBTBuffer<RWDateTime> szOn_Sale_Date(10);
			RWDBTBuffer<RWCString> szPrice(10);
			RWDBTBuffer<RWCString> szProduct_Group_SEO_Copy(10); //  
			RWDBTBuffer<RWCString> szProduct_Group_Title(10);
			RWDBTBuffer<RWCString> szReading_Level(10);
			RWDBTBuffer<RWCString> szRelease_Date(10);
			RWDBTBuffer<RWCString> szSales_Marketing_Code(10);
			RWDBTBuffer<RWCString> szCas_Business_Unit(10);
			RWDBTBuffer<RWCString> szSeries(10);
			RWDBTBuffer<RWCString> szSub_Format(10);
			RWDBTBuffer<RWCString> szSubtitle(10);
			RWDBTBuffer<RWCString> szTitle(10);
			RWDBTBuffer<RWCString> szVolume(10);
			RWDBTBuffer<RWCString> szProductID(10);
			RWDBTBuffer<RWCString> szLocaleID(10);

            myQuery[0] >> szProduct_Group_ID >> szAges >> szBest_Seller_Flag >> szCatalog_Name >> szEditorial_Imprint >>
            szCoverImageURL_Large >> szCoverImageURL_Medium >> szCoverImageURL_MediumLarge >>
            szCoverImageURL_Small >> szFormat >> szFuture_Release_Flag >> szGrade_End >> szGrade_Start >>
			szHas_Essay >> szImprint >> szISBN >> szLocale_Desc >> szMax_Age >> szMin_Age >> szNew_Release_Flag >>
			szNo_of_Reviews >> szNum_Of_Pages >> szOn_Sale_Date >> szPrice >> szProduct_Group_SEO_Copy >> szProduct_Group_Title >>
			szReading_Level >> szRelease_Date >> szSales_Marketing_Code >> szCas_Business_Unit >> szSeries >> szSub_Format >>
			szSubtitle >> szTitle >> szVolume >> szProductID >> szLocaleID;

            while (myQuery.fetch(), myQuery.rowsFetched() > 0)
            {
                for (int i = 0; i < myQuery.rowsFetched(); i++ )
                {
					std::string m_tmp;
                    CDbFace detailDbItem;
                    detailDbItem.Product_Group_ID(szProduct_Group_ID[i]);
                    detailDbItem.Ages(szAges[i]);
                    detailDbItem.Best_Seller_Flag(szBest_Seller_Flag[i]);
                    detailDbItem.Catalog_Name(szCatalog_Name[i]);
					detailDbItem.Editorial_Imprint(szEditorial_Imprint[i]);
                    detailDbItem.CoverImageURL_Large(szCoverImageURL_Large[i]);
                    detailDbItem.CoverImageURL_Medium(szCoverImageURL_Medium[i]);
                    detailDbItem.CoverImageURL_MediumLarge(szCoverImageURL_MediumLarge[i]);
                    detailDbItem.CoverImageURL_Small(szCoverImageURL_Small[i]);
                    detailDbItem.Format(szFormat[i]);
                    detailDbItem.Future_Release_Flag(szFuture_Release_Flag[i]);
                    detailDbItem.Grade_End(szGrade_End[i]);
					detailDbItem.Grade_Start(szGrade_Start[i]); //
					detailDbItem.Has_Essay(szHas_Essay[1]);
					detailDbItem.Imprint(szImprint[i]);
					detailDbItem.ISBN(szISBN[i]);
					detailDbItem.Locale_Desc(szLocale_Desc[i]);
					detailDbItem.Max_Age(szMax_Age[i]);
					detailDbItem.Min_Age(szMin_Age[i]);
					detailDbItem.New_Release_Flag(szNew_Release_Flag[i]);
					detailDbItem.No_of_Reviews(szNo_of_Reviews[i]);
					detailDbItem.Num_Of_Pages(szNum_Of_Pages[i]);
					detailDbItem.On_Sale_Date(szOn_Sale_Date[i].asString("%Y-%m-%d"));
					detailDbItem.Price(szPrice[i]);
					detailDbItem.Product_Group_SEO_Copy(szProduct_Group_SEO_Copy[i]);
					detailDbItem.Product_Group_Title(szProduct_Group_Title[i]);
					detailDbItem.Reading_Level(szReading_Level[i]);
					detailDbItem.Release_Date(szRelease_Date[i]);
					detailDbItem.Sales_Marketing_Code(szSales_Marketing_Code[i]);
					detailDbItem.Cas_Business_Unit(szCas_Business_Unit[i]);
					detailDbItem.Series(szSeries[i]);
					detailDbItem.Sub_Format(szSub_Format[i]);
					detailDbItem.Subtitle(szSubtitle[i]);
					detailDbItem.Title(szTitle[i]);
					detailDbItem.Volume(szVolume[i]);
					detailDbItem.ProductID(szProductID[i]);
					detailDbItem.LocaleID(szLocaleID[i]);
                    // *******************
                    detailDb.insert(detailDbItem);
                    didFetch++;
                }
            }
        } 
		else
        {
            m_inError = true;
            m_error = myQuery.status().vendorMessage2();
        }
        return didFetch;
    } // Get_dbReport

}   // end SlapWare namespace

#undef _ThisClass

