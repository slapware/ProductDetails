#include "DbFace.h"
#include <rw/tools/regex.h>

//:Special
#define _ThisClass		CDbFace
#define _NumBaseClass	0

//:Custom
using namespace std;

namespace slapware 
{    // begin SlapWare namespace

    // +---------------+
    // |  Constructor  |
    // +---------------+
    CDbFace::CDbFace(void)
    {
    }
    // +--------------+
    // |  Destructor  |
    // +--------------+
    CDbFace::~CDbFace(void)
    {
    }
    // +--------------------+
    // |  Copy Constructor  |
    // +--------------------+
    CDbFace::CDbFace(const _ThisClass& rhs_)                            // Existing object being copied
    {
        m_Product_Group_ID = rhs_.m_Product_Group_ID;
        m_Ages = rhs_.m_Ages;
        m_Best_Seller_Flag = rhs_.m_Best_Seller_Flag;
        m_Catalog_Name = rhs_.m_Catalog_Name;
        m_Editorial_Imprint = rhs_.m_Editorial_Imprint;
        m_CoverImageURL_Large = rhs_.m_CoverImageURL_Large;
        m_CoverImageURL_Medium = rhs_.m_CoverImageURL_Medium;
        m_CoverImageURL_MediumLarge = rhs_.m_CoverImageURL_MediumLarge;
        m_CoverImageURL_Small = rhs_.m_CoverImageURL_Small;
        m_Format = rhs_.m_Format;
        m_Future_Release_Flag = rhs_.m_Future_Release_Flag;
        m_Grade_End = rhs_.m_Grade_End;

		m_Grade_Start = rhs_.m_Grade_Start; 
		m_Has_Essay = rhs_.m_Has_Essay;
		m_Imprint = rhs_.m_Imprint;
		m_ISBN = rhs_.m_ISBN;
		m_Locale_Desc = rhs_.m_Locale_Desc;
		m_Max_Age = rhs_.m_Max_Age;
		m_Min_Age = rhs_.m_Min_Age;
		m_New_Release_Flag = rhs_.m_New_Release_Flag;
		m_No_of_Reviews = rhs_.m_No_of_Reviews;
		m_Num_Of_Pages = rhs_.m_Num_Of_Pages;
		m_On_Sale_Date = rhs_.m_On_Sale_Date;
		m_Price = rhs_.m_Price;
		m_Product_Group_SEO_Copy = rhs_.m_Product_Group_SEO_Copy;
		m_Product_Group_Title = rhs_.m_Product_Group_Title;
		m_Reading_Level = rhs_.m_Reading_Level;
		m_Release_Date = rhs_.m_Release_Date;
		m_Sales_Marketing_Code = rhs_.m_Sales_Marketing_Code;
		m_Cas_Business_Unit = rhs_.m_Cas_Business_Unit;
		m_Series = rhs_.m_Series;
		m_Sub_Format = rhs_.m_Sub_Format;
		m_Subtitle = rhs_.m_Subtitle;
		m_Title = rhs_.m_Title;
		m_Volume = rhs_.m_Volume;
		m_ProductID = rhs_.m_ProductID;
		m_LocaleID = rhs_.m_LocaleID;
    }
    // +----------------+
    // |  operator =()  |
    // +----------------+
    _ThisClass & CDbFace::operator =(const _ThisClass& rhs_)             // right-hand-side of assignment
    {
        if (&rhs_ != this)      // Always test for assignment to self.
        {
            m_Product_Group_ID = rhs_.m_Product_Group_ID;
            m_Ages = rhs_.m_Ages;
            m_Best_Seller_Flag = rhs_.m_Best_Seller_Flag;
            m_Catalog_Name = rhs_.m_Catalog_Name;
            m_Editorial_Imprint = rhs_.m_Editorial_Imprint;
            m_CoverImageURL_Large = rhs_.m_CoverImageURL_Large;
            m_CoverImageURL_Medium = rhs_.m_CoverImageURL_Medium;
            m_CoverImageURL_MediumLarge = rhs_.m_CoverImageURL_MediumLarge;
            m_CoverImageURL_Small = rhs_.m_CoverImageURL_Small;
            m_Format = rhs_.m_Format;
            m_Future_Release_Flag = rhs_.m_Future_Release_Flag;
            m_Grade_End = rhs_.m_Grade_End;

			m_Grade_Start = rhs_.m_Grade_Start; 
			m_Has_Essay = rhs_.m_Has_Essay;
			m_Imprint = rhs_.m_Imprint;
			m_ISBN = rhs_.m_ISBN;
			m_Locale_Desc = rhs_.m_Locale_Desc;
			m_Max_Age = rhs_.m_Max_Age;
			m_Min_Age = rhs_.m_Min_Age;
			m_New_Release_Flag = rhs_.m_New_Release_Flag;
			m_No_of_Reviews = rhs_.m_No_of_Reviews;
			m_Num_Of_Pages = rhs_.m_Num_Of_Pages;
			m_On_Sale_Date = rhs_.m_On_Sale_Date;
			m_Price = rhs_.m_Price;
			m_Product_Group_SEO_Copy = rhs_.m_Product_Group_SEO_Copy;
			m_Product_Group_Title = rhs_.m_Product_Group_Title;
			m_Reading_Level = rhs_.m_Reading_Level;
			m_Release_Date = rhs_.m_Release_Date;
			m_Sales_Marketing_Code = rhs_.m_Sales_Marketing_Code;
			m_Cas_Business_Unit = rhs_.m_Cas_Business_Unit;
			m_Series = rhs_.m_Series;
			m_Sub_Format = rhs_.m_Sub_Format;
			m_Subtitle = rhs_.m_Subtitle;
			m_Title = rhs_.m_Title;
			m_Volume = rhs_.m_Volume;
			m_ProductID = rhs_.m_ProductID;
			m_LocaleID = rhs_.m_LocaleID;
        }
        return *this;           // Return a reference to this object.
    }

    RWCString CDbFace::XmlFix(RWCString& toCheck)
    {
        if (toCheck.contains("&", RWCString::ignoreCase))
        {
            RWTRegex<char> qck("&");
            qck.replace(toCheck, "&amp;", 0);
        }
        return toCheck;
    }

    RWCString CDbFace::QuoteFix(RWCString& toCheck)
    {
        if (toCheck.contains("'", RWCString::ignoreCase))
        {
            RWTRegex<char> qck("'");
            qck.replace(toCheck, "''", 0);
        }
        return toCheck;
    }

    RWCString CDbFace::CheckDate(RWCString& toCheck)
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
