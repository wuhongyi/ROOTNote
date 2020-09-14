<!-- TSQLFile.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 一 1月  7 14:41:27 2019 (+0800)
;; Last-Updated: 一 1月  7 15:20:26 2019 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 3
;; URL: http://wuhongyi.cn -->

# TSQLFile

```
Access an SQL db via the TFile interface.

The main motivation for the TSQLFile development is to have
"transparent" access to SQL data base via standard TFile interface.
The main approach that each class (but not each object) has one or two tables
with names like $(CLASSNAME)_ver$(VERSION) and $(CLASSNAME)_raw$(VERSION)
For example: TAxis_ver8 or TList_raw5
Second kind of tables appears, when some of class members can not be converted to
normalized form or when class has custom streamer.
For instance, for TH1 class two tables are required: TH1_ver4 and TH1_raw4
Most of members are stored in TH1_ver4 table column-wise, and only member:
    Double_t*  fBuffer;  //[fBufferSize]
can not be represented as column while size of array is not fixed.
Therefore, fBuffer will be written as list of values in TH1_raw4 table.
All objects, stored in the DB, will be registered in table "ObjectsTable".
In this there are following columns:
| Name | Description |
|------|-------------|
| "key:id"  | key identifier to which belong object |
| "obj:id"  | object identifier |
| "Class"   | object class name |
| "Version" | object class version |

 Data in each "ObjectsTable" row uniquely identify, in which table
 and which column object is stored.

In normal situation all class data should be sorted column-wise.
Up to now following member are supported:
  -# Basic data types. Here is everything clear. Column SQL type will be as much as possible
    close to the original type of value.
  -# Fixed array of basic data types. In this case n columns like fArr[0],
    fArr[1] and so on will be created.
    If there is multidimensional array, names will be fArr2[1][2][1] and so on
  -# Parent class. In this case version of parent class is stored and
    data of parent class will be stored with the same obj:id in correspondent table.
    There is a special case, when parent store nothing (this is for instance TQObject).
    In that case just -1 is written to avoid any extra checks if table exist or not.
  -# Object as data member. In that case object is saved in normal way to data base and column
    will contain id of this object.
  -# Pointer on object. Same as before. In case if object was already stored, just its id
    will be placed in the column. For NULL pointer 0 is used.
  -# TString. Now column with limited width like VARCAHR(255) in MySQL is used.
    Later this will be improved to support maximum possible strings
  -# Anything else. Data will be converted to raw format and saved in _streamer_ table.
    Each row supplied with obj:id and row:id, where row:id indicates
    data, corresponding to this particular data member, and column
    will contain this raw:id

All conversion to SQL statements are done with help of TSQLStructure class.
This is special hierarchical structure wich internally is very similar
to XML structures. TBufferSQL2 creates these structures, when object
data is streamed by ROOT and only afterwards all SQL statements will be produced
and applied all together.
When data is reading, TBufferSQL2 will produce requests to database
during unstreaming of object data.
Optionally (default this options on) name of column includes
suffix which indicates type of column. For instance:
| Name | Description |
|------|-------------|
|  *:parent  | parent class, column contain class version |
|  *:object  | other object, column contain object id |
|  *:rawdata | raw data, column contains id of raw data from _streamer_ table |
|  *:Int_t   | column with integer value |

Use TSQLFile::SetUseSuffixes(kFALSE) to disable suffixes usage.
This and several other options can be changed only when
TSQLFile created with options "CREATE" or "RECREATE" and only before
first write operation. These options are:
| Name | Description |
|------|-------------|
| SetUseSuffixes() | suffix usage in column names (default - on) |
| SetArrayLimit()  | defines maximum array size, which can has column for each element (default 21) |
| SetTablesType()  | table type name in MySQL database (default "InnoDB") |
| SetUseIndexes()  | usage of indexes in database (default kIndexesBasic) |

Normally these functions should be called immediately after TSQLFile constructor.
When objects data written to database, by default START TRANSACTION/COMMIT
SQL commands are used before and after data storage. If TSQLFile detects
any problems, ROLLBACK command will be used to restore
previous state of data base. If transactions not supported by SQL server,
they can be disabled by SetUseTransactions(kTransactionsOff). Or user
can take responsibility to use transactions function himself.
By default only indexes for basic tables are created.
In most cases usage of indexes increase performance to data reading,
but it also can increase time of writing data to database.
There are several modes of index usage available in SetUseIndexes() method
There is MakeSelectQuery(TClass*) method, which
produces SELECT statement to get objects data of specified class.
Difference from simple statement like:
    mysql> SELECT * FROM TH1I_ver1
that not only data for that class, but also data from parent classes
will be extracted from other tables and combined in single result table.
Such select query can be useful for external access to objects data.

Up to now MySQL 4.1 and Oracle 9i were tested.
Some extra work is required for other SQL databases.
Hopefully, this should be straightforward.

Known problems and open questions.
  -# TTree is not supported by TSQLFile. There is independent development
   of TTreeSQL class, which allows to store trees directly in SQL database
  -# TClonesArray is store objects in raw format,
   which can not be accessed outside ROOT.
   This will be changed later.
  -# TDirectory cannot work. Hopefully, will (changes in ROOT basic I/O is required)
  -# Streamer infos are not written to file, therefore schema evolution
   is not yet supported. All eforts are done to enable this feature in
   the near future
```

- MySQL
- Oracle
- ODBC



- "READ / OPEN"
- "UPDATE"
- "NEW / CREATE"
- "BREAKLOCK"
- "RECREATE"


```cpp
class TSQLFile : public TFile
```

## class

```cpp
   friend class TBufferSQL2;
   friend class TKeySQL;
   friend class TSQLStructure;
   friend class TSQLTableData;
   friend class TSqlRegistry;
   friend class TSqlRawBuffer;
   friend class TSqlCmdsBuffer;

protected:
   enum ELockingKinds { kLockFree = 0, kLockBusy = 1 };

   // Interface to basic system I/O routines, suppressed
   virtual Int_t SysOpen(const char *, Int_t, UInt_t) { return 0; }
   virtual Int_t SysClose(Int_t) { return 0; }
   virtual Int_t SysRead(Int_t, void *, Int_t) { return 0; }
   virtual Int_t SysWrite(Int_t, const void *, Int_t) { return 0; }
   virtual Long64_t SysSeek(Int_t, Long64_t, Int_t) { return 0; }
   virtual Int_t SysStat(Int_t, Long_t *, Long64_t *, Long_t *, Long_t *) { return 0; }
   virtual Int_t SysSync(Int_t) { return 0; }

   // Overwrite methods for directory I/O
   virtual Long64_t DirCreateEntry(TDirectory *);/// Create entry for directory in database
   virtual Int_t DirReadKeys(TDirectory *);/// Read directory list of keys from database
   virtual void DirWriteKeys(TDirectory *);/// Write directory keys list to database
   virtual void DirWriteHeader(TDirectory *);/// Update dir header in the file

   // functions to manipulate basic tables (Configurations, Objects, Keys) in database
   void SaveToDatabase();
/// save data which is not yet in Database
/// Typically this is streamerinfos structures or   
   
   Bool_t ReadConfigurations();/// read table configurations as special table
   Bool_t IsTablesExists();/// Checks if main keys table is existing
   void InitSqlDatabase(Bool_t create);
/// initialize sql database and correspondent structures
/// identical to TFile::Init() function   
   
   void CreateBasicTables();
/// Creates initial tables in database
/// This is table with configurations and table with keys
/// Function called once when first object is stored to the file.   
   
   void IncrementModifyCounter();
/// Update value of modify counter in config table
/// Modify counter used to indicate that something was changed in database.
/// It will be used when multiple instances of TSQLFile for the same data base
/// will be connected.   
   
   void SetLocking(Int_t mode);/// Set locking mode for current database
   Int_t GetLocking();/// Return current locking mode for that file

   // function for read/write access infos
   Bool_t IsWriteAccess();/// Checkis, if lock is free in configuration tables
   Bool_t IsReadAccess();/// dummy, in future should check about read access to database

   // generic sql functions
   TSQLResult *SQLQuery(const char *cmd, Int_t flag = 0, Bool_t *res = 0);
/// Submits query to SQL server.
/// | Flag Value | Effect|
/// |------------|-------|
/// | 0 | result is not interesting and will be deleted|
/// | 1 | return result of submitted query
/// | 2 | results is may be necessary for long time Oracle plugin do not support working with several TSQLResult
/// objects, therefore explicit deep copy will be produced|
/// If ok!=0, it will contains kTRUE is Query was successfull, otherwise kFALSE   
   
   Bool_t SQLCanStatement();/// Test if DB support statement and number of open statements is not exceeded
   TSQLStatement *SQLStatement(const char *cmd, Int_t bufsize = 1000);/// Produces SQL statement for currently conected DB server
   void SQLDeleteStatement(TSQLStatement *stmt);/// delete statement and decrease counter
   Bool_t SQLApplyCommands(TObjArray *cmds);
/// supplies set of commands to server
/// Commands is stored as array of TObjString   
   
   Bool_t SQLTestTable(const char *tablename);/// Test, if table of specified name exists
   Long64_t SQLMaximumValue(const char *tablename, const char *columnname);
/// Returns maximum value, found in specified columnname of table tablename
/// Column type should be numeric   
   
   void SQLDeleteAllTables();/// Delete all tables in database
   Bool_t SQLStartTransaction();/// Start SQL transaction.
   Bool_t SQLCommit();/// Commit SQL transaction
   Bool_t SQLRollback();/// Rollback all SQL operations, done after start transaction
   Int_t SQLMaxIdentifierLength();/// returns maximum allowed length of identifiers

   // operation with keys structures in database
   void DeleteKeyFromDB(Long64_t keyid);
/// Remove key with specified id from keys table
/// also removes all objects data, related to this table   
   
   Bool_t WriteKeyData(TKeySQL *key);/// Add entry into keys table
   Bool_t UpdateKeyData(TKeySQL *key);/// Updates (overwrites) key data in KeysTable
   TKeySQL *FindSQLKey(TDirectory *dir, Long64_t keyid);/// Search for TKeySQL object with specified keyid
   Long64_t DefineNextKeyId();/// Returns next possible key identifier
   Int_t StreamKeysForDirectory(TDirectory *dir, Bool_t doupdate, Long64_t specialkeyid = -1, TKeySQL **specialkey = 0);
/// read keys for specified directory (when update == kFALSE)
/// or update value for modified keys when update == kTRUE
/// Returns number of successfully read keys or -1 if error

   // handling SQL class info structures
   TSQLClassInfo *FindSQLClassInfo(const char *clname, Int_t version);/// Return (if exists) TSQLClassInfo for specified class name and version
   TSQLClassInfo *FindSQLClassInfo(const TClass *cl);/// return (if exists) TSQLClassInfo for specified class
   TSQLClassInfo *RequestSQLClassInfo(const char *clname, Int_t version);/// Search in database tables for specified class and return TSQLClassInfo object
   TSQLClassInfo *RequestSQLClassInfo(const TClass *cl);/// Search in database tables for specified class and return TSQLClassInfo object
   Bool_t CreateClassTable(TSQLClassInfo *sqlinfo, TObjArray *colinfos);/// Create normal class table if required
   Bool_t CreateRawTable(TSQLClassInfo *sqlinfo);/// Create the raw table

   Bool_t ProduceClassSelectQuery(TVirtualStreamerInfo *info, TSQLClassInfo *sqlinfo, TString &columns, TString &tables,
                                  Int_t &tablecnt);
/// used by MakeClassSelectQuery method to add columns from table of
/// class, specified by TVirtualStreamerInfo structure

   void AddIdEntry(Long64_t tableid, Int_t subid, Int_t type, const char *name, const char *sqlname, const char *info);
/// Add entry into IdsTable, where all tables names and columns names are listed   
   
   void ReadSQLClassInfos();/// Read all class infos from IdsTable
   TString DefineTableName(const char *clname, Int_t version, Bool_t rawtable);/// Proposes table name for class
   Bool_t HasTable(const char *name);/// Test if table name exists

   // operations with long string table
   TString CodeLongString(Long64_t objid, Int_t strid);
/// Produces id which will be placed in column instead of string itself   
   
   Int_t IsLongStringCode(Long64_t objid, const char *value);
/// Checks if this is long string code
/// returns 0, if not or string id

   Bool_t VerifyLongStringTable();
/// Checks that table for big strings is exists
/// If not, will be created   
   
   Bool_t GetLongString(Long64_t objid, Int_t strid, TString &value);
/// Returns value of string, extracted from special table,
/// where long strings are stored

   // operation with object tables in database
   Long64_t VerifyObjectTable();
/// Checks that objects table is exists
/// If not, table will be created
/// Returns maximum value for existing objects id   
   
   Bool_t SQLObjectInfo(Long64_t objid, TString &clname, Version_t &version);
/// Read from objects table data for specified objectid   
   
   TObjArray *SQLObjectsInfo(Long64_t keyid);
/// Produce array of TSQLObjectInfo objects for all objects, belong to that key
/// Array should be deleted by calling function afterwards   
   
   TSQLResult *GetNormalClassData(Long64_t objid, TSQLClassInfo *sqlinfo);
/// Method return request result for specified objid from normal classtable   
   
   TSQLResult *GetNormalClassDataAll(Long64_t minobjid, Long64_t maxobjid, TSQLClassInfo *sqlinfo);
/// Return data for several objects from the range from normal class table   
   
   TSQLResult *GetBlobClassData(Long64_t objid, TSQLClassInfo *sqlinfo);
/// Method return request results for specified objid from _streamer_ classtable   
   
   TSQLStatement *GetBlobClassDataStmt(Long64_t objid, TSQLClassInfo *sqlinfo);
/// Method return request results for specified objid from _streamer_ classtable
/// Data returned in form of statement, where direct access to values are possible   
   
   Long64_t StoreObjectInTables(Long64_t keyid, const void *obj, const TClass *cl);
/// Store object in database. Return stored object id or -1 if error   
   
   Bool_t WriteSpecialObject(Long64_t keyid, TObject *obj, const char *name, const char *title);
/// write special kind of object like streamer infos or file itself
/// keys for that objects should exist in tables but not indicated in list of keys,
/// therefore users can not get them with TDirectoryFile::Get() method   
   
   TObject *ReadSpecialObject(Long64_t keyid, TObject *obj = 0);/// Read data of special kind of objects

   // sql specific types
   const char *SQLCompatibleType(Int_t typ) const;
/// Returns sql type name which is most closer to ROOT basic type.
/// typ should be from TVirtualStreamerInfo:: constansts like TVirtualStreamerInfo::kInt   
   
   const char *SQLIntType() const;/// return SQL integer type
   const char *SQLSmallTextType() const { return fOtherTypes[0]; }
   Int_t SQLSmallTextTypeLimit() const { return atoi(fOtherTypes[1]); }
   const char *SQLBigTextType() const { return fOtherTypes[2]; }
   const char *SQLDatetimeType() const { return fOtherTypes[3]; }
   const char *SQLIdentifierQuote() const { return fOtherTypes[4]; }
   const char *SQLDirIdColumn() const { return fOtherTypes[5]; }
   const char *SQLKeyIdColumn() const { return fOtherTypes[6]; }
   const char *SQLObjectIdColumn() const { return fOtherTypes[7]; }
   const char *SQLRawIdColumn() const { return fOtherTypes[8]; }
   const char *SQLStrIdColumn() const { return fOtherTypes[9]; }
   const char *SQLNameSeparator() const { return fOtherTypes[10]; }
   const char *SQLValueQuote() const { return fOtherTypes[11]; }
   const char *SQLDefaultTableType() const { return fOtherTypes[12]; }

   TSQLServer *fSQL; ///<! interface to SQL database

   TList *fSQLClassInfos; ///<! list of SQL class infos

   Bool_t fUseSuffixes;     ///<! use suffixes in column names like fValue:Int_t or fObject:pointer
   Int_t fSQLIOversion;     ///<! version of SQL I/O which is stored in configurations
   Int_t fArrayLimit;       ///<! limit for array size. when array bigger, its content converted to raw format
   Bool_t fCanChangeConfig; ///<! variable indicates can be basic configuration changed or not
   TString fTablesType;     ///<! type, used in CREATE TABLE statements
   Int_t fUseTransactions;  ///<! use transaction statements for writing data into the tables
   Int_t fUseIndexes;    ///<! use indexes for tables: 0 - off, 1 - only for basic tables, 2  + normal class tables, 3 -
                         ///all tables
   Int_t fModifyCounter; ///<! indicates how many changes was done with database tables
   Int_t fQuerisCounter; ///<! how many query was applied

   const char **fBasicTypes; ///<! pointer on list of basic types specific for currently connected SQL server
   const char **fOtherTypes; ///<! pointer on list of other SQL types like TEXT or blob

   TString fUserName; ///<! user name, used to access objects from database

   std::ofstream *fLogFile; ///<! log file with SQL statements

   Bool_t fIdsTableExists; ///<! indicate if IdsTable exists
   Int_t fStmtCounter;     ///<! count numbers of active statements

private:
   // let the compiler do the job. gcc complains when the following line is activated
   // TSQLFile(const TSQLFile &) {}            //Files cannot be copied
   void operator=(const TSQLFile &);

public:
   enum ETransactionKinds { kTransactionsOff = 0, kTransactionsAuto = 1, kTransactionsUser = 2 };

   enum EIndexesKinds { kIndexesNone = 0, kIndexesBasic = 1, kIndexesClass = 2, kIndexesAll = 3 };

   TSQLFile();
   TSQLFile(const char *dbname, Option_t *option = "read", const char *user = "user", const char *pass = "pass");
/// Connects to SQL server with provided arguments.
/// If the constructor fails in any way IsZombie() will
/// return true. Use IsOpen() to check if the file is (still) open.
/// | Option | Description |
/// |--------|-------------|
/// | NEW or CREATE  | Create a ROOT tables in database if the tables already exists connection is not opened.|
/// | RECREATE       | Create completely new tables. Any existing table will be deleted.|
/// | UPDATE         | Open an existing database for writing. If data base open by other TSQLFile instance for writing,
/// write access will be rejected.|
/// | BREAKLOCK      | Special case when lock was not correctly released by TSQLFile instance. This may happen if
/// program crashed when TSQLFile was open with write access mode.|
/// | READ / OPEN    | Open an existing data base for reading.|
/// For more details see comments for TFile::TFile() constructor.
/// For a moment TSQLFile does not support TTree objects and subdirectories.   
   
   virtual ~TSQLFile();

   // configuration of SQL
   Bool_t GetUseSuffixes() const { return fUseSuffixes; }
   void SetUseSuffixes(Bool_t on = kTRUE);
/// enable/disable uasge of suffixes in columns names
/// can be changed before first object is saved into file   
   
   Int_t GetArrayLimit() const { return fArrayLimit; }
   void SetArrayLimit(Int_t limit = 20);
/// Defines maximum number of columns for array representation
/// If array size bigger than limit, array data will be converted to raw format
/// This is usefull to prevent tables with very big number of columns
/// If limit==0, all arrays will be stored in raw format
/// If limit<0, all array values will be stored in column form
/// Default value is 21   
   
   void SkipArrayLimit() { SetArrayLimit(-1); }
   void SetTablesType(const char *table_type);
/// Defines tables type, which is used in CREATE TABLE statements
/// Now is only used for MySQL database, where following types are supported:
///     "BDB", "HEAP", "ISAM", "InnoDB", "MERGE", "MRG_MYISAM", "MYISAM"
/// Default for TSQLFile is "InnoDB". For more detailes see MySQL docs.   
   
   const char *GetTablesType() const { return fTablesType.Data(); }
   void SetUseTransactions(Int_t mode = kTransactionsAuto);
/// Defines usage of transactions statements for writing objects data to database.
/// | Index | Description |
/// |-------|-------------|
/// | kTransactionsOff=0   - no transaction operation are allowed |
/// | kTransactionsAuto=1  - automatic mode. Each write operation, produced by TSQLFile, will be supplied by START
/// TRANSACTION and COMMIT calls. If any error happen, ROLLBACK will returns database to previous state |
/// | kTransactionsUser=2  - transactions are delegated to user. Methods StartTransaction(), Commit() and Rollback()
/// should be called by user. |
/// Default UseTransactions option is kTransactionsAuto   
   
   Int_t GetUseTransactions() const { return fUseTransactions; }
   void SetUseIndexes(Int_t use_type = kIndexesBasic);
/// Specify usage of indexes for data tables
/// | Index | Description |
/// |-------|-------------|
/// | kIndexesNone = 0  | no indexes are used|
/// | kIndexesBasic = 1 | indexes used only for keys list and objects list tables (default)|
/// | kIndexesClass = 2 | index also created for every normal class table|
/// | kIndexesAll = 3   | index created for every table, including _streamer_ tables|
/// Indexes in general should increase speed of access to objects data,
/// but they required more operations and more disk space on server side
      
   Int_t GetUseIndexes() const { return fUseIndexes; }
   Int_t GetQuerisCounter() const { return fQuerisCounter; }

   TString MakeSelectQuery(TClass *cl);
/// Produce \b SELECT statement which can be used to get all data
/// of class cl in one \b SELECT statement.
/// This statement also can be used to create \b VIEW by command like
///     mysql> CREATE VIEW TH1I_view AS $CLASSSELECT$
/// Where \b $CLASSSELECT$ argument should be produced by call
///     f->MakeSelectQuery(TH1I::Class());
/// \b VIEWs supported by latest MySQL 5 and Oracle   
   
   Bool_t StartTransaction();
/// Start user transaction.
/// This can be usesful, when big number of objects should be stored in
/// data base and commitment required only if all operations were successful.
/// In that case in the end of all operations method Commit() should be
/// called. If operation on user-level is looks like not successful,
/// method Rollback() will return database data and TSQLFile instance to
/// previous state.
/// In MySQL not all tables types support transaction mode of operation.
/// See SetTablesType() method for details .   
   
   Bool_t Commit();
/// Commit transaction, started by StartTransaction() call.
/// Only after that call data will be written and visible on database side.   
   
   Bool_t Rollback();
/// Rollback all operations, done after StartTransaction() call.
/// Database should return to initial state.

   // log file for SQL statements
   void StartLogFile(const char *fname); // *MENU* /// start logging of all SQL statements in specified file
   void StopLogFile();                   // *MENU* /// close logging file

   virtual void Close(Option_t *option = ""); // *MENU*
/// Close a SQL file
/// For more comments see TFile::Close() function   
   
   virtual TKey *CreateKey(TDirectory *mother, const TObject *obj, const char *name, Int_t bufsize);/// create SQL key, which will store object in data base
   virtual TKey *CreateKey(TDirectory *mother, const void *obj, const TClass *cl, const char *name, Int_t bufsize);/// create SQL key, which will store object in data base
   virtual void DrawMap(const char * = "*", Option_t * = "") {}
   virtual void FillBuffer(char *&) {}
   virtual void Flush() {}

   virtual Long64_t GetEND() const { return 0; }
   virtual Int_t GetErrno() const { return 0; }
   virtual void ResetErrno() const {}

   const char *GetDataBaseName() const;
/// Return name of data base on the host
/// For Oracle always return 0   
   
   virtual Int_t GetNfree() const { return 0; }
   virtual Int_t GetNbytesInfo() const { return 0; }
   virtual Int_t GetNbytesFree() const { return 0; }
   virtual Long64_t GetSeekFree() const { return 0; }
   virtual Long64_t GetSeekInfo() const { return 0; }
   virtual Long64_t GetSize() const { return 0; }
   virtual TList *GetStreamerInfoList();
/// Read back streamer infos from database
/// List of streamer infos is always stored with key:id 0,
/// which is not shown in normal keys list

   Bool_t IsMySQL() const;/// checks, if MySQL database
   virtual Bool_t IsOpen() const;/// return kTRUE if file is opened and can be accessed
   Bool_t IsOracle() const;/// checks, if Oracle database
   Bool_t IsODBC() const;/// checks, if ODBC driver used for database connection

   virtual void MakeFree(Long64_t, Long64_t) {}
   virtual void MakeProject(const char *, const char * = "*", Option_t * = "new") {} // *MENU*
   virtual void Map(Option_t *) {}                                                   //
   virtual void Map() {}                                                             //
   virtual void Paint(Option_t * = "") {}
   virtual void Print(Option_t * = "") const {}
   virtual Bool_t ReadBuffer(char *, Int_t) { return kFALSE; }
   virtual Bool_t ReadBuffer(char *, Long64_t, Int_t) { return kFALSE; }
   virtual void ReadFree() {}
   virtual Int_t Recover() { return 0; }
   virtual Int_t ReOpen(Option_t *mode);
/// Reopen a file with a different access mode, like from READ to
/// See TFile::Open() for details   
   
   virtual void Seek(Long64_t, ERelativeTo = kBeg) {}

   virtual void SetEND(Long64_t) {}
   virtual Int_t Sizeof() const { return 0; }

   virtual Bool_t WriteBuffer(const char *, Int_t) { return kFALSE; }
   virtual Int_t Write(const char * = 0, Int_t = 0, Int_t = 0) { return 0; }
   virtual Int_t Write(const char * = 0, Int_t = 0, Int_t = 0) const { return 0; }
   virtual void WriteFree() {}
   virtual void WriteHeader();/// Write file info like configurations, title, UUID and other
   virtual void WriteStreamerInfo();/// Store all TVirtualStreamerInfo, used in file, in sql database
```

## code

```cpp
// A session saving data to a SQL data base

auto dbname = "mysql://host.domain:3306/dbname";
auto username = "username";
auto userpass = "userpass";

// Clean data base and create primary tables
auto f = new TSQLFile(dbname, "recreate", username, userpass);
// Write with standard I/O functions
arr->Write("arr", TObject::kSingleKey);
h1->Write("histo");
// Close connection to DB
delete f;
```


```cpp
// A session read data from SQL data base
// Open database again in read-only mode
auto f = new TSQLFile(dbname, "open", username, userpass);
// Show list of keys
f->ls();
// Read stored object, again standard ROOT I/O
auto h1 = (TH1*) f->Get("histo");
if (h1!=0) { h1->SetDirectory(0); h1->Draw(); }
auto obj = f->Get("arr");
if (obj!=0) obj->Print("*");
// close connection to DB
delete f;
```





<!-- TSQLFile.md ends here -->
