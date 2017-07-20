// ProductDetails.cpp : Defines the entry point for the console application.
// Stephen La Pierre - original SlapWare
#ifdef _DEBUG
    #define _RWCONFIG 15s
#else
    #define _RWCONFIG 12s
#endif

#if defined(_WIN32) || defined (_WIN64)
    #include "stdafx.h"
#endif

#include <iostream>
#include <cstdlib>

#include "cgicc/CgiDefs.h"
#include "cgicc/Cgicc.h"
#include <cgicc/HTTPResponseHeader.h>
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

#include <rw/pointer/RWTOnlyPointer.h>
#include <rw/functor/functor.h>  // for the RWTFunctorR2 family
#include "MsSqlHandle.h"
#include "DbFace.h"
#include <rw/tools/regex.h> // new RegEx
#include "Markup.h"
#include <sstream>
#include <rw/timer.h>   // for timing data
#include "SlapOut.h"

#if HAVE_SYS_UTSNAME_H
    #include <sys/utsname.h>
#endif

#if HAVE_SYS_TIME_H
    #include <sys/time.h>
#endif

////////////////////////////////////
//define to enable timing results.//
////////////////////////////////////
//#define _SLAP_TIMECHECK_ 1  // For timer report

#if !defined(_INC_STRING)
    #include <rw/cstring.h>
#endif

#if defined(_WIN32) || defined (_WIN64)
    #define PATH_SEPARATOR  "\\"
    #include "Windows.h"
    #include <direct.h> 
    #define GetCurrentDir _getcwd 
#else
    #define PATH_SEPARATOR  "/"
    #include <unistd.h> 
    #define GetCurrentDir getcwd 
#endif
///////////////////
//namespace usage//
///////////////////
using namespace std;
using namespace cgicc;
using namespace slapware;
///////////////////////////////////
//Global constants for networking//
///////////////////////////////////
//const int networkMaxWait = 25000;
//const int minBodyLength = 168;
//////////////////////////////////
//Forward declarations are here.//
//////////////////////////////////
bool CheckSqlInsert(const RWCString& pMesg);
RWCString DateCheck(RWCString& pData);
/////////////////////////
//The Main entry point.//
/////////////////////////
int main(int argc, char ** argv[])
{
    try
    {
		////////////////////////////////////////////
		//Start timer if _SLAP_TIMECHECK_ defined.//
		////////////////////////////////////////////
#ifdef _SLAP_TIMECHECK_
		RWTimer slapTime;
		slapTime.start(); // Start the timer
#endif
        Cgicc cgi;
		////////////////////////////////////
		//Get a pointer to the environment//
		////////////////////////////////////
		const CgiEnvironment& env = cgi.getEnvironment();
        RWCString m_isbn;			// parameter to search
        RWCString m_locale;			// parameter to search
        RWCString m_title;			// parameter to search
        RWCString m_productID;     // parameter to search
        std::ostringstream m_strstrm;
		bool AllowSource = false;	 // check http source addr

#ifdef _DEBUG
//		cgi.save("ProductDetails.slp");	// param test
        cgi.restore("D:\\ProductDetails.slp"); // test
#endif
		RWCString m_query = env.getQueryString();

        const_form_iterator isbnIter = cgi.getElement("isbn");
        const_form_iterator localeIter = cgi.getElement("locale");
        const_form_iterator titleIter = cgi.getElement("title");
        const_form_iterator productIDIter = cgi.getElement("productID");

		cout << HTTPContentHeader("text/xml;charset=UTF-8") ;
		//cout << HTTPResponseHeader(env.getServerProtocol(), 200, "OK")
		//	.addHeader("Cache-Control", "max-age=7200")
		//	.addHeader("Content-Type", "text/xml;charset=UTF-8");
		//cout << "\r\n";
        /////////////////////////////////////
        //Read the desired Format to return//
        /////////////////////////////////////
        if (isbnIter != (*cgi).end() && !isbnIter->isEmpty())
        {
            m_isbn = (**isbnIter).c_str();
        }
		if (localeIter != (*cgi).end() && !localeIter->isEmpty())
		{
			m_locale = (**localeIter).c_str();
		}
		if (productIDIter != (*cgi).end() && !productIDIter->isEmpty())
		{
			m_productID = (**productIDIter).c_str();
		}
		if (titleIter != (*cgi).end() && !titleIter->isEmpty())
		{
			m_title = (**titleIter).c_str();
		}
        ////////////////////////////////////////////
        //Check playing nice and not naughty troll//
        ////////////////////////////////////////////
        if (CheckSqlInsert(m_isbn))
        {
            cout << "<Product_Details>" << endl;
            cout << "<NICE>But NO thanks</NICE>";
            cout << "</Product_Details>" << endl;
            return EXIT_FAILURE;
        }
        // Full steam ahead ******
        RWCString dbserver, dbuser, dbpass, dbstore, m_sql, m_error;

		char cCurrentPath[FILENAME_MAX];
		if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath))) 
		{ 
			return false; 
		}
        ///////////////////////////////////////////////////////////
        //Select the name of .config file to load for DB connect.//
        ///////////////////////////////////////////////////////////
		std::string pXmlSetting = cCurrentPath;
		pXmlSetting += PATH_SEPARATOR;
		pXmlSetting += "DDR_Web.config";

        { // scope the life of CMarkup
            CMarkup m_xml;
            if (!m_xml.Load(pXmlSetting.c_str() ) )
            {
                std::cout << "Failed to locate and load XML configuration." << endl;
                return false;
            } 
            else
            {
                m_xml.FindElem();
                m_xml.IntoElem();

                m_xml.FindElem("database");
                m_xml.FindChildElem("server");
                dbserver = (m_xml.GetChildData());
                m_xml.FindChildElem("user");
                dbuser = (m_xml.GetChildData());
                m_xml.FindChildElem("pass");
                dbpass = (m_xml.GetChildData());
				m_xml.FindChildElem("store");
				dbstore = (m_xml.GetChildData());
                m_xml.FindElem("caller");
				if (m_xml.GetData().compare("1") == 0)
				{
					// Check the Referrer for security check
					RWCString m_reqUrl = cgi.getEnvironment().getRemoteAddr();
					RWCString sAttribName = m_xml.GetAttribName(0);
					RWCString sAttribValue = m_xml.GetAttrib(sAttribName.std());
					if(m_reqUrl.contains(sAttribValue, RWCString::ignoreCase))
					{
						AllowSource = true;
					}
					else
					{
						AllowSource = false;
					}
				}
				else
				{
					AllowSource = true;
				}
            }
        } // end scope life of CMarkup

		if (!AllowSource)
		{
			cout << "<Product_Details>" << endl;
			cout << "<NICE>But NO thanks</NICE>";
			cout << "</Product_Details>" << endl;
			return EXIT_FAILURE;
		}

        try
        {
            /////////////////////////////////////////////////////////////
            //Create Smart Pointer for mySql connection in this thread.//
            /////////////////////////////////////////////////////////////
            RWTOnlyPointer<CMsSqlHandle> pdb(new CMsSqlHandle(dbserver, dbuser, 
                                                              dbpass, dbstore));
            if (pdb->check())
            {
                m_error.remove(0);
                m_strstrm << "<ERR>" << pdb->ErrorReport() << "</ERR>";
                m_error = m_strstrm.str();
                m_strstrm.str("");

                cout << "<Product_Details>" << endl;
                cout << m_error;
                cout << "</Product_Details>" << endl;
                return EXIT_FAILURE;
            }
            //////////////////////////////////////////////////////////////////
            //Create Query for url and map to construct return html to user.//
            //////////////////////////////////////////////////////////////////
			m_strstrm << "SELECT Product_Group_ID, Ages,Best_Seller_Flag,Catalog_Name,Editorial_Imprint,CoverImageURL_Large, ";
			m_strstrm << "CoverImageURL_Medium, CoverImageURL_MediumLarge,CoverImageURL_Small,Format, ";
			m_strstrm << "Future_Release_Flag,Grade_End,Grade_Start,Has_Essay,Imprint,ISBN,Locale_Desc, ";
			m_strstrm << "Max_Age,Min_Age,New_Release_Flag,No_of_Reviews,Num_Of_Pages,On_Sale_Date,Price, ";
			m_strstrm << "CAST(Product_Group_SEO_Copy AS varchar(8000)) AS Product_Group_SEO_Copy, Product_Group_Title,Reading_Level,Release_Date,Sales_Marketing_Code, ";
			m_strstrm << "Cas_Business_Unit, Series, Sub_Format, Subtitle,Title,Volume, Product_ID, Locale_ID ";
            m_strstrm << "FROM dbo.v_Product_Detail ";
//			m_strstrm << "WHERE Default_Locale_Flag = 'Y' ";
			if (!m_locale.isNull())
			{
				m_strstrm << "WHERE Locale_Desc = '" << m_locale << "' ";
			}
			else
			{
				m_strstrm << "WHERE Default_Locale_Flag = 'Y' ";
			}
			if (!m_isbn.isNull())
			{
				m_strstrm << "AND ISBN = '" << m_isbn << "' ";
			}
			if (!m_productID.isNull())
			{
				m_strstrm << "AND Product_ID = " << m_productID << " ";
			}
			if (!m_title.isNull())
			{
				m_strstrm << "AND Title LIKE '" << m_title << "%'";
			}
			// 			if (m_locale.compareTo("Y", RWCString::ignoreCase) == 0)

            m_sql = m_strstrm.str();
            m_strstrm.str("");
            /////////////////////////////////
            //Collections for multi row XML//
            /////////////////////////////////
            int m_recs_returned;
            RWTValDlist<CDbFace> detailDb; 
            RWTValDlist<CDbFace>::iterator detailDbIter;
            CDbFace detailDbItem;

			RWTValDlist<CContentDB> pContentDb;
            RWTValDlist<CContentDB>::iterator pContentDbIter;
            CContentDB ContentDbItem;

			RWTValDlist<CContributorDB> pContribDb;
			RWTValDlist<CContributorDB>::iterator pContribDbIter;
			CContributorDB ContribDbItem;

			RWTValDlist<CBisacDB> pBisacDb;
			RWTValDlist<CBisacDB>::iterator pBisacDbIter;
			CBisacDB BisacDbItem;

			RWTValDlist<CCategoryDB> pCategoryDb;
			RWTValDlist<CCategoryDB>::iterator pCategoryDbIter;
			CCategoryDB pCategoryDBItem;

			CSlapOut pSlap;
			RWTFunctor2<RWCString&, RWCString&> sendFunctor
				= rwtMakeFunctor2( (void(*)(RWCString&, RWCString&))NULL, pSlap, &CSlapOut::SendOut);

			RWTFunctor2<RWCString&, RWCString&> sendCdataFunctor
				= rwtMakeFunctor2( (void(*)(RWCString&, RWCString&))NULL, pSlap, &CSlapOut::SendCdataOut);

			RWTFunctor2<RWCString&, RWCString&> sendDateFunctor
				= rwtMakeFunctor2( (void(*)(RWCString&, RWCString&))NULL, pSlap, &CSlapOut::SendDateOut);


			RWCString pTag;

#ifdef _DEBUG
            cout << m_sql.data();
            cout << "\nSQL 1 \n";
#endif
            try
            {
                m_recs_returned = pdb->Get_dbReport(m_sql, detailDb);
            } 
            catch (const RWxmsg& dbmsg)
            {
                m_error.remove(0);
                m_strstrm << "Select Exception: = " << dbmsg.why() << endl;
                m_error = m_strstrm.str();
                m_strstrm.str("");
                m_error.remove(0);
            }
			if (pdb->check())
			{
				m_error.remove(0);
				m_strstrm << "<ERR>" << pdb->ErrorReport() << "</ERR>";
				m_error = m_strstrm.str();
				m_strstrm.str("");

				cout << "<Product_Details>" << endl;
				cout << m_error;
				cout << "</Product_Details>" << endl;
				return EXIT_FAILURE;
			}
            /////////////////////////////////////////////////////////////
            //If no data user and group membership not valid for apiKey//
            /////////////////////////////////////////////////////////////
            if (m_recs_returned == 0)
            {
                cout << "<Product_Details>" << endl;
                cout << "</Product_Details>" << endl;
                return EXIT_FAILURE;
            } 
            else
            {
                RWCString m_line;
				RWCString m_productID, m_localeID;
                cout << "<Product_Details>" << endl;
                detailDbIter = detailDb.begin();
                while (detailDbIter != detailDb.end())
                {
                    detailDbItem = *detailDbIter++;
                    cout << "<Product_Detail>";
                    // Content of db record start
					pTag = "On_Sale_Date";
					sendFunctor(pTag, DateCheck(detailDbItem.On_Sale_Date()));
					// ***********
					pTag = "Release_Date";
					sendFunctor(pTag, DateCheck(detailDbItem.Release_Date()));
					// ***********
					pTag = "Imprint";
					sendFunctor(pTag, detailDbItem.Imprint());
					// ***********
					pTag = "Format";
					sendFunctor(pTag, detailDbItem.Format());
					// ***********
					pTag = "ISBN";
					sendFunctor(pTag, detailDbItem.ISBN());
					// ***********
					pTag = "Product_Group_ID";
					sendFunctor(pTag, detailDbItem.Product_Group_ID());
					// ***********
					pTag = "Series";
					sendFunctor(pTag, detailDbItem.Series());
					// ***********
					pTag = "Sub_Format";
					sendFunctor(pTag, detailDbItem.Sub_Format());
					// ***********
					pTag = "Title";
					sendFunctor(pTag, detailDbItem.Title());
					// ***********
					pTag = "Subtitle";
					sendFunctor(pTag, detailDbItem.Subtitle());
					// ***********
					pTag = "Price";
					sendFunctor(pTag, detailDbItem.Price());
					// ***********
					pTag = "Num_Of_Pages";
					sendFunctor(pTag, detailDbItem.Num_Of_Pages());
					// ***********
					pTag = "Volume";
					sendFunctor(pTag, detailDbItem.Volume());
					// ***********
					pTag = "Ages";
					sendFunctor(pTag, detailDbItem.Ages());
					// ***********
					pTag = "Min_Age";
					sendFunctor(pTag, detailDbItem.Min_Age());
					// ***********
					pTag = "Max_Age";
					sendFunctor(pTag, detailDbItem.Max_Age());
					// ***********
					pTag = "Reading_Level";
					sendFunctor(pTag, detailDbItem.Reading_Level());
					// ***********
					pTag = "Grade_Start";
					sendFunctor(pTag, detailDbItem.Grade_Start());
					// ***********
					pTag = "Grade_End";
					sendFunctor(pTag, detailDbItem.Grade_End());
					// ***********
					pTag = "Editorial_Imprint";
					sendFunctor(pTag, detailDbItem.Editorial_Imprint());
					// ***********
					pTag = "CoverImageURL_Large";
					sendFunctor(pTag, detailDbItem.CoverImageURL_Large());
					// ***********
					pTag = "CoverImageURL_Medium";
					sendFunctor(pTag, detailDbItem.CoverImageURL_Medium());
					// ***********
					pTag = "CoverImageURL_MediumLarge";
					sendFunctor(pTag, detailDbItem.CoverImageURL_MediumLarge());
					// ***********
					pTag = "CoverImageURL_Small";
					sendFunctor(pTag, detailDbItem.CoverImageURL_Small());
					// ***********
					pTag = "Catalog_Name";
					sendFunctor(pTag, detailDbItem.Catalog_Name());
					// ***********
					pTag = "Best_Seller_Flag";
					sendFunctor(pTag, detailDbItem.Best_Seller_Flag());
					// ***********
					pTag = "No_of_Reviews";
					sendFunctor(pTag, detailDbItem.No_of_Reviews());
					// ***********
					pTag = "Sales_Marketing_Code";
					sendFunctor(pTag, detailDbItem.Sales_Marketing_Code());
					// ***********
					pTag = "Cas_Business_Unit";
					sendFunctor(pTag, detailDbItem.Cas_Business_Unit());
					// ***********
					pTag = "New_Release_Flag";
					sendFunctor(pTag, detailDbItem.New_Release_Flag());
					// ***********
					pTag = "Future_Release_Flag";
					sendFunctor(pTag, detailDbItem.Future_Release_Flag());
					// ***********
					pTag = "Has_Essay";
					sendFunctor(pTag, detailDbItem.Has_Essay());
					// ***********
					pTag = "Locale_Desc";
					sendFunctor(pTag, detailDbItem.Locale_Desc());
					// ***********
					pTag = "Product_Group_SEO_Copy";
					sendCdataFunctor(pTag, detailDbItem.Product_Group_SEO_Copy());
					// ***********
					pTag = "Product_Group_Title";
					sendFunctor(pTag, detailDbItem.Product_Group_Title());
					// ***********
					m_productID = detailDbItem.ProductID();
					m_localeID = detailDbItem.LocaleID();
                    // Onto Product Content
                ///////////////////////////////////////////
                //Moved loop to end to correct XML output//
                ///////////////////////////////////////////
 //               } // while
				m_strstrm << "SELECT Content_Type_ID, Content_Area1, Content_Area2, ";
				m_strstrm << "Content_Area3, Description FROM ";
                //////////////////////////////////////////////////////////
                //Call to function object - SLAPPED 09/13/11 works fine.//
                //////////////////////////////////////////////////////////
#ifdef _STDSQL
				m_strstrm << "v_product_Content WHERE Product_ID = ";
				m_strstrm << m_productID << " AND Locale_ID = " << m_localeID;
#else
				m_strstrm << "fn_GetProductContent_Limited(" << m_productID;
				m_strstrm << ", " << m_localeID << ")";
#endif
				m_sql = m_strstrm.str();
				m_strstrm.str("");
#ifdef _DEBUG
				cout << m_sql.data();
				cout << "\nSQL 2 ******** \n";
#endif
				try
				{
					m_recs_returned = pdb->Get_Content(m_sql, pContentDb);
				} 
				catch (const RWxmsg& dbmsg)
				{
					m_error.remove(0);
					m_strstrm << "Select Exception: = " << dbmsg.why() << endl;
					m_error = m_strstrm.str();
					m_strstrm.str("");
					m_error.remove(0);
				}
				cout << "<Product_Contents>" << endl;
				pContentDbIter = pContentDb.begin();
				while (pContentDbIter != pContentDb.end())
				{
					ContentDbItem = *pContentDbIter++;
					cout << "<Product_Content>";
					// Content of db record start
					pTag = "Content_Type_ID";
					sendFunctor(pTag, ContentDbItem.Content_Type_ID());
					// ***********
					pTag = "Content_Area1";
					sendCdataFunctor(pTag, ContentDbItem.Content_Area1());
					// ***********
					pTag = "Content_Area2";
					sendCdataFunctor(pTag, ContentDbItem.Content_Area2());
					// ***********
					pTag = "Content_Area3";
					sendCdataFunctor(pTag, ContentDbItem.Content_Area3());
					// ***********
					pTag = "Content_Type_Desc";
					sendCdataFunctor(pTag, ContentDbItem.Content_Type_Desc());
					// ***********
					cout << "</Product_Content>";
				}
				cout << "</Product_Contents>" << endl;
                ///////////////////////////
                //Contributor XML section//
                ///////////////////////////
				m_strstrm << "SELECT Display_Name, First_Name, Middle_Name, ";
				m_strstrm << "Last_Name, Role, Contributor_Order, ";
				m_strstrm << "Contributor_persona_ID FROM ";
				m_strstrm << "v_product_Contributors WHERE Product_ID = ";
				m_strstrm << m_productID << " AND Locale_ID = " << m_localeID; 
				m_sql = m_strstrm.str();
				m_strstrm.str("");
#ifdef _DEBUG
				cout << m_sql.data();
				cout << "\nSQL 2 \n";
#endif
				try
				{
					m_recs_returned = pdb->Get_Contrib(m_sql, pContribDb);
				} 
				catch (const RWxmsg& dbmsg)
				{
					m_error.remove(0);
					m_strstrm << "Select Exception: = " << dbmsg.why() << endl;
					m_error = m_strstrm.str();
					m_strstrm.str("");
					m_error.remove(0);
				}
				cout << "<Product_Contributors>" << endl;
				pContribDbIter = pContribDb.begin();
				while (pContribDbIter != pContribDb.end())
				{
					ContribDbItem = *pContribDbIter++;
					cout << "<Product_Contributor>";
					// Content of db record start
					pTag = "Display_Name";
					sendFunctor(pTag, ContribDbItem.Display_Name());
					// ***********
					pTag = "First_Name";
					sendFunctor(pTag, ContribDbItem.First_Name());
					// ***********
					pTag = "Middle_Name";
					sendFunctor(pTag, ContribDbItem.Middle_Name());
					// ***********
					pTag = "Last_Name";
					sendFunctor(pTag, ContribDbItem.Last_Name());
					// ***********
					pTag = "Role";
					sendFunctor(pTag, ContribDbItem.Role());
					// ***********
					pTag = "Contributor_Order";
					sendFunctor(pTag, ContribDbItem.Contributor_Order());
					// ***********
					pTag = "Contributor_Persona_ID";
					sendFunctor(pTag, ContribDbItem.Contributor_Persona_ID());
					// ***********
					cout << "</Product_Contributor>";
				}
				cout << "</Product_Contributors>" << endl;
                /////////////////////
                //BISAC XML section//
                /////////////////////
				m_strstrm << "SELECT BISAC_Code, BISAC_Position, ";
				m_strstrm << "BISAC_Revision, BISAC_Desc FROM ";
				m_strstrm << "v_product_BISAC WHERE Product_ID = ";
				m_strstrm << m_productID << " AND Locale_ID = " << m_localeID; 
				m_sql = m_strstrm.str();
				m_strstrm.str("");
#ifdef _DEBUG
				cout << m_sql.data();
				cout << "\nSQL 3 \n";
#endif
				try
				{
					m_recs_returned = pdb->Get_Bisac(m_sql, pBisacDb);
				} 
				catch (const RWxmsg& dbmsg)
				{
					m_error.remove(0);
					m_strstrm << "Select Exception: = " << dbmsg.why() << endl;
					m_error = m_strstrm.str();
					m_strstrm.str("");
					m_error.remove(0);
				}
				cout << "<Product_BISAC_Codes>" << endl;
				pBisacDbIter = pBisacDb.begin();
				while (pBisacDbIter != pBisacDb.end())
				{
					BisacDbItem = *pBisacDbIter++;
					cout << "<Product_BISAC>";
					// Content of db record start
					pTag = "BISAC_Code";
					sendFunctor(pTag, BisacDbItem.BISAC_Code());
					// ***********
					pTag = "BISAC_Position";
					sendFunctor(pTag, BisacDbItem.BISAC_Position());
					// ***********
					pTag = "BISAC_Revision";
					sendFunctor(pTag, BisacDbItem.BISAC_Revision());
					// ***********
					pTag = "BISAC_Desc";
					sendFunctor(pTag, BisacDbItem.BISAC_Desc());
					// ***********
					// ***********
					cout << "</Product_BISAC>";
				}
				cout << "</Product_BISAC_Codes>" << endl;
                //////////////////////////////////
                //PRODUCT_CATEGORIES XML Display//
                //////////////////////////////////
				m_strstrm << "SELECT Category_Desc, Category_Type_Desc ";
				m_strstrm << "FROM v_product_category WHERE Product_ID = ";
				m_strstrm << m_productID << " AND Locale_ID = " << m_localeID; 
				m_sql = m_strstrm.str();
				m_strstrm.str("");
#ifdef _DEBUG
				cout << m_sql.data();
				cout << "\nSQL 4 \n";
#endif
				try
				{
					m_recs_returned = pdb->Get_Category(m_sql, pCategoryDb);
				} 
				catch (const RWxmsg& dbmsg)
				{
					m_error.remove(0);
					m_strstrm << "Select Exception: = " << dbmsg.why() << endl;
					m_error = m_strstrm.str();
					m_strstrm.str("");
					m_error.remove(0);
				}
				cout << "<Product_Categories>" << endl;
				pCategoryDbIter = pCategoryDb.begin();
				while (pCategoryDbIter != pCategoryDb.end())
				{
					pCategoryDBItem = *pCategoryDbIter++;
					cout << "<Product_Category>";
					// Content of db record start
					pTag = "Category_Desc";
					sendFunctor(pTag, pCategoryDBItem.Category_Desc());
					// ***********
					pTag = "Category_Type_Desc";
					sendFunctor(pTag, pCategoryDBItem.Category_Type_Desc());
					// ***********
					cout << "</Product_Category>";
				}
				cout << "</Product_Categories>" << endl;
                ////////////////////////////////////
                //END of XML display *************//
                ////////////////////////////////////
                cout << "</Product_Detail>" << endl;
                } // while - moved from first call
				/////////////////////////////////////////////////////////////
				//Show timer information if defined via _SLAP_TIMECHECK_   //
				/////////////////////////////////////////////////////////////
#ifdef _SLAP_TIMECHECK_
				// Information on this query
				slapTime.stop();
				if (m_query.contains("&", RWCString::ignoreCase))
				{
					RWTRegex<char> qck("&");
					qck.replace(m_query, "&amp;", 0);
				}
				cout << "<!-- The elapsed cgi time report -->" << endl;
				cout << "<Query>" << m_query << "</Query>";
				cout << "<Time>" << endl;

				std::cout << "<System>" 
					<< double (slapTime.time (RWTimer::SYSTEM)) / 1000000.0F 
					<< " seconds</System>";

				std::cout << "<User>" 
					<< double (slapTime.time (RWTimer::USER)) / 1000000.0F 
					<< " seconds</User>";

				std::cout << "<Total>"
					<< double (slapTime.time (RWTimer::USER | RWTimer::SYSTEM)) / 1000000.0F
					<< " seconds</Total>";
				cout << "</Time>" << endl;
#endif
				////////////////////////
				//close main XML node.//
				////////////////////////
                cout << "</Product_Details>" << endl;
                return 0;
            }
        }   // try 
        catch (const RWxmsg& msg)
        {
            RWCString m_thr_error = msg.why();
            return EXIT_FAILURE;
        }
        return 0;
    } 
    catch (const std::exception& e)
    {
        cout << e.what() << endl;
        return EXIT_FAILURE;
    }
} // END int main(int argc, char ** argv[])
/////////////////////////////////////////
//Check parameter for SQL Insert Attack//
/////////////////////////////////////////
bool CheckSqlInsert(const RWCString& pMesg)
{
    if (pMesg.length() > 256)
    {
        return true;
    }

    if ( (pMesg.contains("INSERT ", RWCString::ignoreCase)) ||
         (pMesg.contains("DELETE ", RWCString::ignoreCase)) )
    {
        return true;
    }
    if ( (pMesg.contains("SELECT ", RWCString::ignoreCase)) ||
         (pMesg.contains("UPDATE ", RWCString::ignoreCase)) )
    {
        return true;
    }
    if ( (pMesg.contains("EXEC ", RWCString::ignoreCase)) ||
         (pMesg.contains("CALL ", RWCString::ignoreCase)) )
    {
        return true;
    }
    return false;
}

RWCString DateCheck(RWCString& pData)
{
    std::ostringstream m_strstrm;
    RWCString m_year = (pData.std().substr(0, 4));
    RWCString m_month = pData.std().substr(5, 2);
    RWCString m_day = pData.std().substr(8, 2);
    RWCString m_time = pData.remove(0, 10);

    m_strstrm << m_month << "/" << m_day << "/" << m_year;
    m_strstrm << " " << m_time;
    pData = m_strstrm.str();
    m_strstrm.str("");

    return pData;
}
