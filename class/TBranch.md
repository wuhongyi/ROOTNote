<!-- TBranch.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 9月 13 20:58:30 2016 (+0800)
;; Last-Updated: 六 10月 29 19:59:28 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 3
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
/// Read all leaves of entry and return total number of bytes read.
///
/// The input argument "entry" is the entry number in the current tree.
/// In case of a TChain, the entry number in the current Tree must be found
/// before calling this function. For example:
///~~~ {.cpp}
///     TChain* chain = ...;
///     Long64_t localEntry = chain->LoadTree(entry);
///     branch->GetEntry(localEntry);
///~~~
/// The function returns the number of bytes read from the input buffer.
/// If entry does not exist, the function returns 0.
/// If an I/O error occurs, the function returns -1.
///
/// See IMPORTANT REMARKS in TTree::GetEntry.

   virtual Int_t     GetEntryExport(Long64_t entry, Int_t getall, TClonesArray *list, Int_t n);
/// Read all leaves of an entry and export buffers to real objects in a TClonesArray list.
/// Returns total number of bytes read.

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
/// Return total number of bytes in the branch (including current buffer)
		   
           Long64_t  GetTotBytes(Option_t *option="")    const;
/// Return total number of bytes in the branch (excluding current buffer)
/// if option ="*" includes all sub-branches of this branch too

           Long64_t  GetZipBytes(Option_t *option="")    const;
/// Return total number of zip bytes in the branch
/// if option ="*" includes all sub-branches of this branch too

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
/// keep a maximum of fMaxEntries in memory

   virtual Int_t     LoadBaskets();
///  Baskets associated to this branch are forced to be in memory.
///  You can call TTree::SetMaxVirtualSize(maxmemory) to instruct
///  the system that the total size of the imported baskets does not
///  exceed maxmemory bytes.
///  The function returns the number of baskets that have been put in memory.
///  This method may be called to force all baskets of one or more branches
///  in memory when random access to entries in this branch is required.
///  See also TTree::LoadBaskets to load all baskets of all branches in memory.

   virtual void      Print(Option_t *option="") const;
/// Print TBranch parameters
   
   virtual void      ReadBasket(TBuffer &b);
   virtual void      Refresh(TBranch *b);
   virtual void      Reset(Option_t *option="");
   virtual void      ResetAfterMerge(TFileMergeInfo *);
/// Reset a Branch.
/// - Existing buffers are deleted.
/// - Entries, max and min are reset.

   virtual void      ResetAddress();
/// Reset the address of the branch.

   virtual void      ResetReadEntry() {fReadEntry = -1;}
   virtual void      SetAddress(void *add);
/// Set address of this branch.

   virtual void      SetObject(void *objadd);
   virtual void      SetAutoDelete(Bool_t autodel=kTRUE);
/// Set the automatic delete bit.
/// This bit is used by TBranchObject::ReadBasket to decide if an object
/// referenced by a TBranchObject must be deleted or not before reading
/// a new entry.
/// If autodel is kTRUE, this existing object will be deleted, a new object
/// created by the default constructor, then read from disk by the streamer.
/// If autodel is kFALSE, the existing object is not deleted.  Root assumes
/// that the user is taking care of deleting any internal object or array
/// (this can be done in the streamer).

   virtual void      SetBasketSize(Int_t buffsize);
   virtual void      SetBufferAddress(TBuffer *entryBuffer);
   void              SetCompressionAlgorithm(Int_t algorithm=0);
   void              SetCompressionLevel(Int_t level=1);
   void              SetCompressionSettings(Int_t settings=1);
   virtual void      SetEntries(Long64_t entries);
   virtual void      SetEntryOffsetLen(Int_t len, Bool_t updateSubBranches = kFALSE);
   virtual void      SetFirstEntry( Long64_t entry );
///set the first entry number (case of TBranchSTL)

   virtual void      SetFile(TFile *file=0);
/// Set file where this branch writes/reads its buffers.
/// By default the branch buffers reside in the file where the
/// Tree was created.
/// If the file name where the tree was created is an absolute
/// path name or an URL (e.g. /castor/... or root://host/...)
/// and if the fname is not an absolute path name or an URL then
/// the path of the tree file is prepended to fname to make the
/// branch file relative to the tree file. In this case one can
/// move the tree + all branch files to a different location in
/// the file system and still access the branch files.
/// The ROOT file will be connected only when necessary.
/// If called by TBranch::Fill (via TBasket::WriteFile), the file
/// will be created with the option "recreate".
/// If called by TBranch::GetEntry (via TBranch::GetBasket), the file
/// will be opened in read mode.
/// To open a file in "update" mode or with a certain compression
/// level, use TBranch::SetFile(TFile *file).

   virtual void      SetFile(const char *filename);
/// Set file where this branch writes/reads its buffers.
/// By default the branch buffers reside in the file where the
/// Tree was created.
/// If the file name where the tree was created is an absolute
/// path name or an URL (e.g. /castor/... or root://host/...)
/// and if the fname is not an absolute path name or an URL then
/// the path of the tree file is prepended to fname to make the
/// branch file relative to the tree file. In this case one can
/// move the tree + all branch files to a different location in
/// the file system and still access the branch files.
/// The ROOT file will be connected only when necessary.
/// If called by TBranch::Fill (via TBasket::WriteFile), the file
/// will be created with the option "recreate".
/// If called by TBranch::GetEntry (via TBranch::GetBasket), the file
/// will be opened in read mode.
/// To open a file in "update" mode or with a certain compression
/// level, use TBranch::SetFile(TFile *file).

   virtual Bool_t    SetMakeClass(Bool_t decomposeObj = kTRUE);
   virtual void      SetOffset(Int_t offset=0) {fOffset=offset;}
   virtual void      SetStatus(Bool_t status=1);
   virtual void      SetTree(TTree *tree) { fTree = tree;}
   virtual void      SetupAddresses();
   virtual void      UpdateAddress() {;}
   virtual void      UpdateFile();
/// Refresh the value of fDirectory (i.e. where this branch writes/reads its buffers)
/// with the current value of fTree->GetCurrentFile unless this branch has been
/// redirected to a different file.  Also update the sub-branches.

   static  void      ResetCount();
```


## code



## example



<!-- TBranch.md ends here -->
