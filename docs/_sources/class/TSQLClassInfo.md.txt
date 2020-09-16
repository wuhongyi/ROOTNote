<!-- TSQLClassInfo.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 一 1月  7 14:37:14 2019 (+0800)
;; Last-Updated: 三 9月 16 10:39:53 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TSQLClassInfo*

Contains information about tables specific to one class and
version. It provides names of table for that class. For each version of
class not more than two tables can exists. Normal table has typically
name like TH1\_ver4 and additional table has name like TH1\_raw4.
List of this objects are kept by TSQLFile class.

```cpp
class TSQLClassColumnInfo : public TObject

class TSQLClassInfo : public TObject
```

## class

**TSQLClassColumnInfo**

```cpp
public:
   TSQLClassColumnInfo();
   TSQLClassColumnInfo(const char *name, const char *sqlname, const char *sqltype);
   virtual ~TSQLClassColumnInfo();

   virtual const char *GetName() const { return fName.Data(); }
   const char *GetSQLName() const { return fSQLName.Data(); }
   const char *GetSQLType() const { return fSQLType.Data(); }

protected:
   TString fName;
   TString fSQLName;
   TString fSQLType;
```

----

**TSQLClassInfo**

```cpp
public:
   TSQLClassInfo();
   TSQLClassInfo(Long64_t classid, const char *classname, Int_t version);
/// normal constructor of TSQLClassInfo class
/// Sets names of tables, which are used for that version of class   
   
   virtual ~TSQLClassInfo();

   Long64_t GetClassId() const { return fClassId; }

   virtual const char *GetName() const { return fClassName.Data(); }
   Int_t GetClassVersion() const { return fClassVersion; }

   void SetClassTableName(const char *name) { fClassTable = name; }
   void SetRawTableName(const char *name) { fRawTable = name; }

   const char *GetClassTableName() const { return fClassTable.Data(); }
   const char *GetRawTableName() const { return fRawTable.Data(); }

   void SetTableStatus(TObjArray *columns = 0, Bool_t israwtable = kFALSE);
/// set current status of class tables   
   
   void SetColumns(TObjArray *columns);/// assigns new list of columns
   void SetRawExist(Bool_t on) { fRawtableExist = on; }

   Bool_t IsClassTableExist() const { return GetColumns() != 0; }
   Bool_t IsRawTableExist() const { return fRawtableExist; }

   TObjArray *GetColumns() const { return fColumns; }
   Int_t FindColumn(const char *name, Bool_t sqlname = kFALSE);
/// Search for column of that name
/// Can search either for full column name (sqlname = kFALSE, default)
/// or for name, used as column name (sqlname = kTRUE)
/// Return index of column in list (-1 if not found)

protected:
   TString fClassName;    ///<! class name
   Int_t fClassVersion;   ///<! class version
   Long64_t fClassId;     ///<! sql class id
   TString fClassTable;   ///<! name of table with class data
   TString fRawTable;     ///<! name of table with raw data
   TObjArray *fColumns;   ///<! name and type of columns - array of TNamed
   Bool_t fRawtableExist; ///<! indicate that raw table is exist
```


<!-- TSQLClassInfo.md ends here -->
