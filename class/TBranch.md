<!-- TBranch.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 9月 13 20:58:30 2016 (+0800)
;; Last-Updated: 二 9月 13 22:34:29 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# TBranch

继承 TNamed , TAttFill

A TTree object is a list of TBranchs.  
A TBranch describes the branch data structure and supports :
 - the list of TBaskets (branch buffers) associated to this branch.
 - the list of TLeaves (branch description) 




## class

```cpp
   TBranch();
   TBranch(TTree *tree, const char *name, void *address, const char *leaflist, Int_t basketsize=32000, Int_t compress=-1);
   TBranch(TBranch *parent, const char *name, void *address, const char *leaflist, Int_t basketsize=32000, Int_t compress=-1);
   virtual ~TBranch();

   virtual void      AddBasket(TBasket &b, Bool_t ondisk, Long64_t startEntry);
   virtual void      AddLastBasket(Long64_t startEntry);
   virtual void      Browse(TBrowser *b);
   virtual void      DeleteBaskets(Option_t* option="");
   virtual void      DropBaskets(Option_t *option = "");
           void      ExpandBasketArrays();
   virtual Int_t     Fill();
   virtual TBranch  *FindBranch(const char *name);
   virtual TLeaf    *FindLeaf(const char *name);
           Int_t     FlushBaskets();
           Int_t     FlushOneBasket(UInt_t which);

   virtual char     *GetAddress() const {return fAddress;}
           TBasket  *GetBasket(Int_t basket);
           Int_t    *GetBasketBytes() const {return fBasketBytes;}
           Long64_t *GetBasketEntry() const {return fBasketEntry;}
   virtual Long64_t  GetBasketSeek(Int_t basket) const;
   virtual Int_t     GetBasketSize() const {return fBasketSize;}
   virtual TList    *GetBrowsables();
   virtual const char* GetClassName() const;
           Int_t     GetCompressionAlgorithm() const;
           Int_t     GetCompressionLevel() const;
           Int_t     GetCompressionSettings() const;
   TDirectory       *GetDirectory() const {return fDirectory;}
   virtual Int_t     GetEntry(Long64_t entry=0, Int_t getall = 0);
   virtual Int_t     GetEntryExport(Long64_t entry, Int_t getall, TClonesArray *list, Int_t n);
           Int_t     GetEntryOffsetLen() const { return fEntryOffsetLen; }
           Int_t     GetEvent(Long64_t entry=0) {return GetEntry(entry);}
   const char       *GetIconName() const;
   virtual Int_t     GetExpectedType(TClass *&clptr,EDataType &type);
   virtual TLeaf    *GetLeaf(const char *name) const;
   virtual TFile    *GetFile(Int_t mode=0);
   const char       *GetFileName()    const {return fFileName.Data();}
           Int_t     GetOffset()      const {return fOffset;}
           Int_t     GetReadBasket()  const {return fReadBasket;}
           Long64_t  GetReadEntry()   const {return fReadEntry;}
           Int_t     GetWriteBasket() const {return fWriteBasket;}
           Long64_t  GetTotalSize(Option_t *option="")   const;
           Long64_t  GetTotBytes(Option_t *option="")    const;
           Long64_t  GetZipBytes(Option_t *option="")    const;
           Long64_t  GetEntryNumber() const {return fEntryNumber;}
           Long64_t  GetFirstEntry()  const {return fFirstEntry; }
         TObjArray  *GetListOfBaskets()  {return &fBaskets;}
         TObjArray  *GetListOfBranches() {return &fBranches;}
         TObjArray  *GetListOfLeaves()   {return &fLeaves;}
           Int_t     GetMaxBaskets()  const  {return fMaxBaskets;}
           Int_t     GetNleaves()     const {return fNleaves;}
           Int_t     GetSplitLevel()  const {return fSplitLevel;}
           Long64_t  GetEntries()     const {return fEntries;}
           TTree    *GetTree()        const {return fTree;}
   virtual Int_t     GetRow(Int_t row);
   virtual Bool_t    GetMakeClass() const;
   TBranch          *GetMother() const;
   TBranch          *GetSubBranch(const TBranch *br) const;
   Bool_t            IsAutoDelete() const;
   Bool_t            IsFolder() const;
   virtual void      KeepCircular(Long64_t maxEntries);
   virtual Int_t     LoadBaskets();
   virtual void      Print(Option_t *option="") const;
   virtual void      ReadBasket(TBuffer &b);
   virtual void      Refresh(TBranch *b);
   virtual void      Reset(Option_t *option="");
   virtual void      ResetAfterMerge(TFileMergeInfo *);
   virtual void      ResetAddress();
   virtual void      ResetReadEntry() {fReadEntry = -1;}
   virtual void      SetAddress(void *add);
   virtual void      SetObject(void *objadd);
   virtual void      SetAutoDelete(Bool_t autodel=kTRUE);
   virtual void      SetBasketSize(Int_t buffsize);
   virtual void      SetBufferAddress(TBuffer *entryBuffer);
   void              SetCompressionAlgorithm(Int_t algorithm=0);
   void              SetCompressionLevel(Int_t level=1);
   void              SetCompressionSettings(Int_t settings=1);
   virtual void      SetEntries(Long64_t entries);
   virtual void      SetEntryOffsetLen(Int_t len, Bool_t updateSubBranches = kFALSE);
   virtual void      SetFirstEntry( Long64_t entry );
   virtual void      SetFile(TFile *file=0);
   virtual void      SetFile(const char *filename);
   virtual Bool_t    SetMakeClass(Bool_t decomposeObj = kTRUE);
   virtual void      SetOffset(Int_t offset=0) {fOffset=offset;}
   virtual void      SetStatus(Bool_t status=1);
   virtual void      SetTree(TTree *tree) { fTree = tree;}
   virtual void      SetupAddresses();
   virtual void      UpdateAddress() {;}
   virtual void      UpdateFile();

   static  void      ResetCount();
```


## code



## example



<!-- TBranch.md ends here -->
