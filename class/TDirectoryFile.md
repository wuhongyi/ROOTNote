<!-- TDirectoryFile.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 六 8月 13 19:18:13 2016 (+0800)
;; Last-Updated: 六 8月 13 20:28:28 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# TDirectoryFile

TDirectory

Describe directory structure in a ROOT file.

A ROOT file is structured in Directories (like a file system).  
Each Directory has a list of Keys (see TKeys) and a list of objects in memory. A Key is a small object that describes the type and location of a persistent object in a file. The persistent object may be a directory.


## class

```cpp
   virtual void        Append(TObject *obj, Bool_t replace = kFALSE);
           void        Add(TObject *obj, Bool_t replace = kFALSE) { Append(obj,replace); }
           Int_t       AppendKey(TKey *key);
   virtual void        Browse(TBrowser *b);
           void        Build(TFile* motherFile = 0, TDirectory* motherDir = 0);
   virtual TObject    *CloneObject(const TObject *obj, Bool_t autoadd = kTRUE);
   virtual void        Close(Option_t *option="");
   virtual void        Copy(TObject &) const { MayNotUse("Copy(TObject &)"); }
   virtual Bool_t      cd(const char *path = 0);
   virtual void        Delete(const char *namecycle="");
   virtual void        FillBuffer(char *&buffer);
   virtual TKey       *FindKey(const char *keyname) const;
   virtual TKey       *FindKeyAny(const char *keyname) const;
   virtual TObject    *FindObjectAny(const char *name) const;
   virtual TObject    *FindObjectAnyFile(const char *name) const;
   virtual TObject    *Get(const char *namecycle);
   virtual TDirectory *GetDirectory(const char *apath, Bool_t printError = false, const char *funcname = "GetDirectory");
   template <class T> inline void GetObject(const char* namecycle, T*& ptr) // See TDirectory::Get for information
      {
         ptr = (T*)GetObjectChecked(namecycle,TBuffer::GetClass(typeid(T)));
      }
   virtual void       *GetObjectChecked(const char *namecycle, const char* classname);
   virtual void       *GetObjectChecked(const char *namecycle, const TClass* cl);
   virtual void       *GetObjectUnchecked(const char *namecycle);
   virtual Int_t       GetBufferSize() const;
   const TDatime      &GetCreationDate() const { return fDatimeC; }
   virtual TFile      *GetFile() const { return fFile; }
   virtual TKey       *GetKey(const char *name, Short_t cycle=9999) const;
   virtual TList      *GetListOfKeys() const { return fKeys; }
   const TDatime      &GetModificationDate() const { return fDatimeM; }
   virtual Int_t       GetNbytesKeys() const { return fNbytesKeys; }
   virtual Int_t       GetNkeys() const { return fKeys->GetSize(); }
   virtual Long64_t    GetSeekDir() const { return fSeekDir; }
   virtual Long64_t    GetSeekParent() const { return fSeekParent; }
   virtual Long64_t    GetSeekKeys() const { return fSeekKeys; }
   Bool_t              IsModified() const { return fModified; }
   Bool_t              IsWritable() const { return fWritable; }
   virtual void        ls(Option_t *option="") const;
   virtual TDirectory *mkdir(const char *name, const char *title="");
   virtual TFile      *OpenFile(const char *name, Option_t *option= "",
                            const char *ftitle = "", Int_t compress = 1,
                            Int_t netopt = 0);
   virtual void        Purge(Short_t nkeep=1);
   virtual void        ReadAll(Option_t *option="");
   virtual Int_t       ReadKeys(Bool_t forceRead=kTRUE);
   virtual Int_t       ReadTObject(TObject *obj, const char *keyname);
   virtual void        ResetAfterMerge(TFileMergeInfo *);
   virtual void        rmdir(const char *name);
   virtual void        Save();
   virtual void        SaveSelf(Bool_t force = kFALSE);
   virtual Int_t       SaveObjectAs(const TObject *obj, const char *filename="", Option_t *option="") const;
   virtual void        SetBufferSize(Int_t bufsize);
   void                SetModified() {fModified = kTRUE;}
   void                SetSeekDir(Long64_t v) { fSeekDir = v; }
   virtual void        SetTRefAction(TObject *ref, TObject *parent);
   void                SetWritable(Bool_t writable=kTRUE);
   virtual Int_t       Sizeof() const;
   virtual Int_t       Write(const char *name=0, Int_t opt=0, Int_t bufsize=0);
   virtual Int_t       Write(const char *name=0, Int_t opt=0, Int_t bufsize=0) const ;
   virtual Int_t       WriteTObject(const TObject *obj, const char *name=0, Option_t *option="", Int_t bufsize=0);
   virtual Int_t       WriteObjectAny(const void *obj, const char *classname, const char *name, Option_t *option="", Int_t bufsize=0);
   virtual Int_t       WriteObjectAny(const void *obj, const TClass *cl, const char *name, Option_t *option="", Int_t bufsize=0);
   virtual void        WriteDirHeader();
   virtual void        WriteKeys();
```

<!-- TDirectoryFile.md ends here -->
