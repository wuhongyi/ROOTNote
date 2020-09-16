<!-- TSQLObjectData.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 一 1月  7 15:21:00 2019 (+0800)
;; Last-Updated: 三 9月 16 10:38:43 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TSQLObjectData*

TSQLObjectData is used in TBufferSQL2 class in reading procedure.
It contains data, request from database table for one specific
object for one specific class. For instance, when data for
class TH1 required, requests will be done to
TH1\_ver4 and TH1\_raw4 tables and result of these requests
will be kept in single TSQLObjectData instance.



TSQLObjectDataPool contains list (pool) of data from single class table
for differents objects, all belonging to the same key.
This is typical situation when list of objects stored as single key.
To optimize reading of such data, one query is submitted and results of that
query kept in TSQLObjectDataPool object


```cpp
class TSQLObjectInfo : public TObject

class TSQLObjectData : public TObject

class TSQLObjectDataPool : public TObject
```

## class

**TSQLObjectInfo**

```cpp
public:
   TSQLObjectInfo();
   TSQLObjectInfo(Long64_t objid, const char *classname, Version_t version);
   virtual ~TSQLObjectInfo();

   Long64_t GetObjId() const { return fObjId; }
   const char *GetObjClassName() const { return fClassName.Data(); }
   Version_t GetObjVersion() const { return fVersion; }

protected:
   Long64_t fObjId;
   TString fClassName;
   Version_t fVersion;
```

----

**TSQLObjectData**

```cpp
public:
   TSQLObjectData();

   TSQLObjectData(TSQLClassInfo *sqlinfo, Long64_t objid, TSQLResult *classdata, TSQLRow *classrow,
                  TSQLResult *blobdata, TSQLStatement *blobstmt);

   virtual ~TSQLObjectData();

   Long64_t GetObjId() const { return fObjId; }
   TSQLClassInfo *GetInfo() const { return fInfo; }

   Bool_t LocateColumn(const char *colname, Bool_t isblob = kFALSE);/// locate column of that name in results
   Bool_t IsBlobData() const { return fCurrentBlob || (fUnpack != 0); }
   void ShiftToNextValue();/// shift to next column or next row in blob data

   void AddUnpack(const char *tname, const char *value);
/// add emulated data
/// this used to place version or TObject raw data, read from normal tables   
   
   void AddUnpackInt(const char *tname, Int_t value);/// emulate integer value in raw data

   const char *GetValue() const { return fLocatedValue; }
   const char *GetLocatedField() const { return fLocatedField; }
   const char *GetBlobPrefixName() const { return fBlobPrefixName; }
   const char *GetBlobTypeName() const { return fBlobTypeName; }

   Bool_t VerifyDataType(const char *tname, Bool_t errormsg = kTRUE);/// checks if data type corresponds to that stored in raw table
   Bool_t PrepareForRawData();/// prepare to read data from raw table

protected:
   Bool_t ExtractBlobValues();/// extract from curent blob row value and names identifiers
   Bool_t ShiftBlobRow();/// shift cursor to next blob value

   Int_t GetNumClassFields();/// return number of columns in class table result
   const char *GetClassFieldName(Int_t n);/// get name of class table column

   TSQLClassInfo *fInfo;        //!
   Long64_t fObjId;             //!
   Bool_t fOwner;               //!
   TSQLResult *fClassData;      //!
   TSQLResult *fBlobData;       //!
   TSQLStatement *fBlobStmt;    //!
   Int_t fLocatedColumn;        //!
   TSQLRow *fClassRow;          //!
   TSQLRow *fBlobRow;           //!
   const char *fLocatedField;   //!
   const char *fLocatedValue;   //!
   Bool_t fCurrentBlob;         //!
   const char *fBlobPrefixName; ///<! name prefix in current blob row
   const char *fBlobTypeName;   ///<! name type (without prefix) in current blob row
   TObjArray *fUnpack;          //!
```

----

**TSQLObjectDataPool**

```cpp
public:
   TSQLObjectDataPool();
   TSQLObjectDataPool(TSQLClassInfo *info, TSQLResult *data);
   virtual ~TSQLObjectDataPool();

   TSQLClassInfo *GetSqlInfo() const { return fInfo; }
   TSQLResult *GetClassData() const { return fClassData; }
   TSQLRow *GetObjectRow(Long64_t objid);/// Returns single sql row with object data for that class

protected:
   TSQLClassInfo *fInfo;   ///<!  classinfo, for which pool is created
   TSQLResult *fClassData; ///<!  results with request to selected table
   Bool_t fIsMoreRows;     ///<!  indicates if class data has not yet read rows
   TList *fRowsPool;       ///<!  pool of extrcted, but didnot used rows
```







<!-- TSQLObjectData.md ends here -->
