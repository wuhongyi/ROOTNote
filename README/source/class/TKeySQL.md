<!-- TKeySQL.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 一 1月  7 14:30:00 2019 (+0800)
;; Last-Updated: 三 9月 16 10:38:09 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TKeySQL*

TKeySQL represents meta-inforamtion about object, which was written to
SQL database. It keeps object id, which used to locate object data
from database tables.

```cpp
class TKeySQL : public TKey
```

## class

```cpp
private:
   TKeySQL(const TKeySQL &);            // TKeySQL objects are not copiable.
   TKeySQL &operator=(const TKeySQL &); // TKeySQL objects are not copiable.

protected:
   TKeySQL();

   virtual Int_t Read(const char *name) { return TKey::Read(name); }
   void StoreKeyObject(const void *obj, const TClass *cl);
/// Stores object, associated with key, into data tables   
   
   void *ReadKeyObject(void *obj, const TClass *expectedClass);
/// Read object, associated with key, from database

   Long64_t fKeyId; ///<!  key identifier in KeysTables
   Long64_t fObjId; ///<!  stored object identifer

public:
   TKeySQL(TDirectory *mother, const TObject *obj, const char *name, const char *title = 0);
/// Creates TKeySQL and convert obj data to TSQLStructure via TBufferSQL2   
   
   TKeySQL(TDirectory *mother, const void *obj, const TClass *cl, const char *name, const char *title = 0);
/// Creates TKeySQL and convert obj data to TSQLStructure via TBufferSQL2   
   
   TKeySQL(TDirectory *mother, Long64_t keyid, Long64_t objid, const char *name, const char *title,
           const char *keydatetime, Int_t cycle, const char *classname);
/// Create TKeySQL object, which corresponds to single entry in keys table		   
		   
   virtual ~TKeySQL();

   Bool_t
   IsKeyModified(const char *keyname, const char *keytitle, const char *keydatime, Int_t cycle, const char *classname);
/// Compares keydata with provided and return kTRUE if key was modified
/// Used in TFile::StreamKeysForDirectory() method to verify data for that keys
/// should be updated

   Long64_t GetDBKeyId() const { return fKeyId; }
   Long64_t GetDBObjId() const { return fObjId; }
   Long64_t GetDBDirId() const;/// return sql id of parent directory

   // redefined TKey Methods
   virtual void Delete(Option_t *option = "");
/// Removes key from current directory
/// Note: TKeySQL object is not deleted. You still have to call "delete key"
   
   
   virtual void DeleteBuffer() {}
   virtual void FillBuffer(char *&) {}
   virtual char *GetBuffer() const { return 0; }
   virtual Long64_t GetSeekKey() const { return GetDBObjId() > 0 ? GetDBObjId() : 0; }
   virtual Long64_t GetSeekPdir() const { return GetDBDirId() > 0 ? GetDBDirId() : 0; }
   virtual void Keep() {}

   virtual Int_t Read(TObject *obj);
/// To read an object from the file.
/// The object associated to this key is read from the file into memory.
/// Before invoking this function, obj has been created via the
/// default constructor.   
   
   virtual TObject *ReadObj();
/// Read object derived from TObject class
/// If it is not TObject or in case of error, return 0   
   
   virtual TObject *ReadObjWithBuffer(char *bufferRead);
/// Read object derived from TObject class
/// If it is not TObject or in case of error, return 0   
   
   virtual void *ReadObjectAny(const TClass *expectedClass);
/// Read object of any type from SQL database

   virtual void ReadBuffer(char *&) {}
   virtual Bool_t ReadFile() { return kTRUE; }
   virtual void SetBuffer() { fBuffer = 0; }
   virtual Int_t WriteFile(Int_t = 1, TFile * = 0) { return 0; }
```

<!-- TKeySQL.md ends here -->
