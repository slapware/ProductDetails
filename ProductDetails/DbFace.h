#pragma once

#ifdef _DEBUG
    #define _RWCONFIG 15s
#else
    #define _RWCONFIG 12s
#endif

#include <rw/cstring.h>

//:Special
#define _ThisClass		CDbFace
#define _NumBaseClass	0

//:Custom
using namespace std;

namespace slapware 
{    // begin SlapWare namespace

    class CDbFace
    {
    public:
        CDbFace(void);
        CDbFace(const _ThisClass& rhs_);                    // Existing object being copied
        _ThisClass& operator = (const _ThisClass& rhs_);    // right-hand-side of assignment
        virtual ~CDbFace(void);
        RWCString QuoteFix(RWCString& toCheck);
        RWCString XmlFix(RWCString& toCheck);
        RWCString CheckDate(RWCString& toCheck);
        // Getter Setter calls *************
        RWCString Product_Group_ID() const { return m_Product_Group_ID;}
        void Product_Group_ID(RWCString val) { m_Product_Group_ID = XmlFix(val);}
        RWCString Ages() const { return m_Ages;}
        void Ages(RWCString val) { m_Ages = val;}
        RWCString Best_Seller_Flag() const { return m_Best_Seller_Flag;}
        void Best_Seller_Flag(RWCString val) { m_Best_Seller_Flag = val;}
        RWCString Catalog_Name() const { return m_Catalog_Name;}
        void Catalog_Name(RWCString val) { m_Catalog_Name = val;}
        RWCString Editorial_Imprint() const { return m_Editorial_Imprint;}
        void Editorial_Imprint(RWCString val) { m_Editorial_Imprint = val;}
        RWCString CoverImageURL_Large() const { return m_CoverImageURL_Large;}
        void CoverImageURL_Large(RWCString val) { m_CoverImageURL_Large = val;}
        RWCString CoverImageURL_Medium() const { return m_CoverImageURL_Medium;}
        void CoverImageURL_Medium(RWCString val) { m_CoverImageURL_Medium = val;}
        RWCString CoverImageURL_MediumLarge() const { return m_CoverImageURL_MediumLarge;}
        void CoverImageURL_MediumLarge(RWCString val) { m_CoverImageURL_MediumLarge = val;}
        RWCString CoverImageURL_Small() const { return m_CoverImageURL_Small;}
        void CoverImageURL_Small(RWCString val) { m_CoverImageURL_Small = val;}
        RWCString Format() const { return m_Format;}
        void Format(RWCString val) { m_Format = val;}
        RWCString Future_Release_Flag() const { return m_Future_Release_Flag;}
        void Future_Release_Flag(RWCString val) { m_Future_Release_Flag = val;}
        RWCString Grade_End() const { return m_Grade_End;}
        void Grade_End(RWCString val) { m_Grade_End = val;}
		RWCString Grade_Start() const { return m_Grade_Start; }
		void Grade_Start(RWCString val) { m_Grade_Start = val; }
		RWCString Has_Essay() const { return m_Has_Essay; }
		void Has_Essay(RWCString val) { m_Has_Essay = val; }
		RWCString Imprint() const { return m_Imprint; }
		void Imprint(RWCString val) { m_Imprint = val; }
		RWCString ISBN() const { return m_ISBN; }
		void ISBN(RWCString val) { m_ISBN = val; }
		RWCString Locale_Desc() const { return m_Locale_Desc; }
		void Locale_Desc(RWCString val) { m_Locale_Desc = val; }
		RWCString Max_Age() const { return m_Max_Age; }
		void Max_Age(RWCString val) { m_Max_Age = val; }
		RWCString Min_Age() const { return m_Min_Age; }
		void Min_Age(RWCString val) { m_Min_Age = val; }
		RWCString New_Release_Flag() const { return m_New_Release_Flag; }
		void New_Release_Flag(RWCString val) { m_New_Release_Flag = val; }
		RWCString No_of_Reviews() const { return m_No_of_Reviews; }
		void No_of_Reviews(RWCString val) { m_No_of_Reviews = val; }
		RWCString Num_Of_Pages() const { return m_Num_Of_Pages; }
		void Num_Of_Pages(RWCString val) { m_Num_Of_Pages = val; }
		RWCString On_Sale_Date() const { return m_On_Sale_Date; }
		void On_Sale_Date(RWCString val) { m_On_Sale_Date = CheckDate(val); }
		RWCString Price() const { return m_Price; }
		void Price(RWCString val) { m_Price = val; }
		RWCString Product_Group_SEO_Copy() const { return m_Product_Group_SEO_Copy; }
		void Product_Group_SEO_Copy(RWCString val) { m_Product_Group_SEO_Copy = val; }
		RWCString Product_Group_Title() const { return m_Product_Group_Title; }
		void Product_Group_Title(RWCString val) { m_Product_Group_Title = val; }
		RWCString Reading_Level() const { return m_Reading_Level; }
		void Reading_Level(RWCString val) { m_Reading_Level = val; }
		RWCString Release_Date() const { return m_Release_Date; }
		void Release_Date(RWCString val) { m_Release_Date = CheckDate(val); }
		RWCString Sales_Marketing_Code() const { return m_Sales_Marketing_Code; }
		void Sales_Marketing_Code(RWCString val) { m_Sales_Marketing_Code = val; }
		RWCString Cas_Business_Unit() const { return m_Cas_Business_Unit; }
		void Cas_Business_Unit(RWCString val) { m_Cas_Business_Unit = val; }
		RWCString Series() const { return m_Series; }
		void Series(RWCString val) { m_Series = val; }
		RWCString Sub_Format() const { return m_Sub_Format; }
		void Sub_Format(RWCString val) { m_Sub_Format = val; }
		RWCString Subtitle() const { return m_Subtitle; }
		void Subtitle(RWCString val) { m_Subtitle = val; }
		RWCString Title() const { return m_Title; }
		void Title(RWCString val) { m_Title = val; }
		RWCString Volume() const { return m_Volume; }
		void Volume(RWCString val) { m_Volume = val; }
		RWCString ProductID() const { return m_ProductID; }
		void ProductID(RWCString val) { m_ProductID = val; }
		void LocaleID(RWCString val) { m_LocaleID = val; }
		RWCString LocaleID() const { return m_LocaleID; }
    private:
        RWCString m_Product_Group_ID;
        RWCString m_Ages;
        RWCString m_Best_Seller_Flag;
        RWCString m_Catalog_Name;
        RWCString m_Editorial_Imprint;
        RWCString m_CoverImageURL_Large;
        RWCString m_CoverImageURL_Medium;
        RWCString m_CoverImageURL_MediumLarge;
        RWCString m_CoverImageURL_Small;
        RWCString m_Format;
        RWCString m_Future_Release_Flag;
        RWCString m_Grade_End;
		RWCString m_Grade_Start; //
		RWCString m_Has_Essay;
		RWCString m_Imprint;
		RWCString m_ISBN;
		RWCString m_Locale_Desc;
		RWCString m_Max_Age;
		RWCString m_Min_Age;
		RWCString m_New_Release_Flag;
		RWCString m_No_of_Reviews;
		RWCString m_Num_Of_Pages;
		RWCString m_On_Sale_Date;
		RWCString m_Price;
		RWCString m_Product_Group_SEO_Copy;
		RWCString m_Product_Group_Title;
		RWCString m_Reading_Level;
		RWCString m_Release_Date;
		RWCString m_Sales_Marketing_Code;
		RWCString m_Cas_Business_Unit;
		RWCString m_Series;
		RWCString m_Sub_Format;
		RWCString m_Subtitle;
		RWCString m_Title;
		RWCString m_Volume;
		RWCString m_ProductID;
		RWCString m_LocaleID;
	};

}   // end SlapWare namespace
//:Special
#undef _ThisClass
#undef _NumBaseClass
