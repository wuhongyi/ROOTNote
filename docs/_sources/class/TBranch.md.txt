<!-- TBranch.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 9月 13 20:58:30 2016 (+0800)
;; Last-Updated: 三 9月 16 12:44:12 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 5
;; URL: http://wuhongyi.cn -->

# TBranch*

继承 TNamed , TAttFill

A TTree object is a list of TBranchs.  
A TBranch describes the branch data structure and supports :
 - the list of TBaskets (branch buffers) associated to this branch.
 - the list of TLeaves (branch description) 




## class

```cpp
   TBranch();
   TBranch(TTree *tree, const char *name, void *address, const char *leaflist, Int_t basketsize=32000, Int_t compress=-1);
/// Create a Branch as a child of a Tree
///       * address is the address of the first item of a structure
///         or the address of a pointer to an object (see example in TTree.cxx).
///       * leaflist is the concatenation of all the variable names and types
///         separated by a colon character :
///         The variable name and the variable type are separated by a
///         slash (/). The variable type must be 1 character. (Characters
///         after the first are legal and will be appended to the visible
///         name of the leaf, but have no effect.) If no type is given, the
///         type of the variable is assumed to be the same as the previous
///         variable. If the first variable does not have a type, it is
///         assumed of type F by default. The list of currently supported
///         types is given below:
///            - C : a character string terminated by the 0 character
///            - B : an 8 bit signed integer (Char_t)
///            - b : an 8 bit unsigned integer (UChar_t)
///            - S : a 16 bit signed integer (Short_t)
///            - s : a 16 bit unsigned integer (UShort_t)
///            - I : a 32 bit signed integer (Int_t)
///            - i : a 32 bit unsigned integer (UInt_t)
///            - F : a 32 bit floating point (Float_t)
///            - D : a 64 bit floating point (Double_t)
///            - L : a 64 bit signed integer (Long64_t)
///            - l : a 64 bit unsigned integer (ULong64_t)
///            - O : [the letter 'o', not a zero] a boolean (Bool_t)
///         Arrays of values are supported with the following syntax:
///         - If leaf name has the form var[nelem], where nelem is alphanumeric, then
///              if nelem is a leaf name, it is used as the variable size of the array,
///              otherwise return 0.
///              The leaf referred to by nelem **MUST** be an int (/I),
///         - If leaf name has the form var[nelem], where nelem is a non-negative integers, then
///              it is used as the fixed size of the array.
///         - If leaf name has the form of a multi dimension array (e.g. var[nelem][nelem2])
///              where nelem and nelem2 are non-negative integers) then
///              it is used as a 2 dimensional array of fixed size.
///         - Any of other form is not supported.
///    Note that the TTree will assume that all the item are contiguous in memory.
///    On some platform, this is not always true of the member of a struct or a class,
///    due to padding and alignment.  Sorting your data member in order of decreasing
///    sizeof usually leads to their being contiguous in memory.
///       * bufsize is the buffer size in bytes for this branch
///         The default value is 32000 bytes and should be ok for most cases.
///         You can specify a larger value (e.g. 256000) if your Tree is not split
///         and each entry is large (Megabytes)
///         A small value for bufsize is optimum if you intend to access
///         the entries in the Tree randomly and your Tree is in split mode.
///   Note that in case the data type is an object, this branch can contain
///   only this object.
///    Note that this function is invoked by TTree::Branch

   TBranch(TBranch *parent, const char *name, void *address, const char *leaflist, Int_t basketsize=32000, Int_t compress=-1);
   virtual ~TBranch();

   virtual void      AddBasket(TBasket &b, Bool_t ondisk, Long64_t startEntry);/// Add the basket to this branch.
   virtual void      AddLastBasket(Long64_t startEntry);/// Add the start entry of the write basket (not yet created)
   virtual void      Browse(TBrowser *b);/// Browser interface.
   virtual void      DeleteBaskets(Option_t* option="");
 /// Loop on all branch baskets. If the file where branch buffers reside is
 /// writable, free the disk space associated to the baskets of the branch,
 /// then call Reset(). If the option contains "all", delete also the baskets
 /// for the subbranches.
 /// The branch is reset.
 /// NOTE that this function must be used with extreme care. Deleting branch baskets
 /// fragments the file and may introduce inefficiencies when adding new entries
 /// in the Tree or later on when reading the Tree.

   virtual void      DropBaskets(Option_t *option = "");
/// Loop on all branch baskets. Drop all baskets from memory except readbasket.
/// If the option contains "all", drop all baskets including
/// read- and write-baskets (unless they are not stored individually on disk).
/// The option "all" also lead to DropBaskets being called on the sub-branches.

           void      ExpandBasketArrays();
/// Increase BasketEntry buffer of a minimum of 10 locations
/// and a maximum of 50 per cent of current size.

   virtual Int_t     Fill();
/// Loop on all leaves of this branch to fill Basket buffer.
/// The function returns the number of bytes committed to the memory basket.
/// If a write error occurs, the number of bytes returned is -1.
/// If no data are written, because e.g. the branch is disabled,
/// the number of bytes returned is 0.

   virtual TBranch  *FindBranch(const char *name);/// Find the immediate sub-branch with passed name.
   virtual TLeaf    *FindLeaf(const char *name);/// Find the leaf corresponding to the name 'searchname'.
           Int_t     FlushBaskets();
/// Flush to disk all the baskets of this branch and any of subbranches.
/// Return the number of bytes written or -1 in case of write error.

           Int_t     FlushOneBasket(UInt_t which);
/// If we have a write basket in memory and it contains some entries and
/// has not yet been written to disk, we write it and delete it from memory.
/// Return the number of bytes written;

   virtual char     *GetAddress() const {return fAddress;}
           TBasket  *GetBasket(Int_t basket);/// Return pointer to basket basketnumber in this Branch
           Int_t    *GetBasketBytes() const {return fBasketBytes;}
           Long64_t *GetBasketEntry() const {return fBasketEntry;}
   virtual Long64_t  GetBasketSeek(Int_t basket) const;/// Return address of basket in the file
   virtual Int_t     GetBasketSize() const {return fBasketSize;}
   virtual TList    *GetBrowsables();
/// Returns (and, if 0, creates) browsable objects for this branch
/// See TVirtualBranchBrowsable::FillListOfBrowsables.

   virtual const char* GetClassName() const;
           Int_t     GetCompressionAlgorithm() const;
           Int_t     GetCompressionLevel() const;
           Int_t     GetCompressionSettings() const;
   TDirectory       *GetDirectory() const {return fDirectory;}
   virtual Int_t     GetEntry(Long64_t entry=0, Int_t getall = 0);
/// Read all leaves of entry and return total number of bytes read.
/// The input argument "entry" is the entry number in the current tree.
/// In case of a TChain, the entry number in the current Tree must be found
/// before calling this function. 
/// The function returns the number of bytes read from the input buffer.
/// If entry does not exist, the function returns 0.
/// If an I/O error occurs, the function returns -1.
/// See IMPORTANT REMARKS in TTree::GetEntry.

   virtual Int_t     GetEntryExport(Long64_t entry, Int_t getall, TClonesArray *list, Int_t n);
/// Read all leaves of an entry and export buffers to real objects in a TClonesArray list.
/// Returns total number of bytes read.

           Int_t     GetEntryOffsetLen() const { return fEntryOffsetLen; }
           Int_t     GetEvent(Long64_t entry=0) {return GetEntry(entry);}
   const char       *GetIconName() const;/// Return icon name depending on type of branch.
   virtual Int_t     GetExpectedType(TClass *&clptr,EDataType &type);
/// Fill expectedClass and expectedType with information on the data type of the
/// object/values contained in this branch (and thus the type of pointers
/// expected to be passed to Set[Branch]Address
/// return 0 in case of success and > 0 in case of failure.

   virtual TLeaf    *GetLeaf(const char *name) const;/// Return pointer to the 1st Leaf named name in thisBranch
   virtual TFile    *GetFile(Int_t mode=0);
/// Return pointer to the file where branch buffers reside, returns 0
/// in case branch buffers reside in the same file as tree header.
/// If mode is 1 the branch buffer file is recreated.

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
/// Return all elements of one row unpacked in internal array fValues
/// [Actually just returns 1 (?)]

   virtual Bool_t    GetMakeClass() const;
/// Return whether this branch is in a mode where the object are decomposed
/// or not (Also known as MakeClass mode).

   TBranch          *GetMother() const;/// Get our top-level parent branch in the tree.
   TBranch          *GetSubBranch(const TBranch *br) const;
/// Find the parent branch of child.
/// Return 0 if child is not in this branch hierarchy.

   Bool_t            IsAutoDelete() const;/// Return kTRUE if an existing object in a TBranchObject must be deleted.
   Bool_t            IsFolder() const;/// Return kTRUE if more than one leaf or browsables, kFALSE otherwise.
   virtual void      KeepCircular(Long64_t maxEntries);/// keep a maximum of fMaxEntries in memory

   virtual Int_t     LoadBaskets();
///  Baskets associated to this branch are forced to be in memory.
///  You can call TTree::SetMaxVirtualSize(maxmemory) to instruct
///  the system that the total size of the imported baskets does not
///  exceed maxmemory bytes.
///  The function returns the number of baskets that have been put in memory.
///  This method may be called to force all baskets of one or more branches
///  in memory when random access to entries in this branch is required.
///  See also TTree::LoadBaskets to load all baskets of all branches in memory.

   virtual void      Print(Option_t *option="") const;/// Print TBranch parameters
   
   virtual void      ReadBasket(TBuffer &b);
   virtual void      Refresh(TBranch *b);
/// Refresh this branch using new information in b
/// This function is called by TTree::Refresh

   virtual void      Reset(Option_t *option="");
/// Reset a Branch.
/// - Existing buffers are deleted.
/// - Entries, max and min are reset.

   virtual void      ResetAfterMerge(TFileMergeInfo *);
/// Reset a Branch.
/// - Existing buffers are deleted.
/// - Entries, max and min are reset.

   virtual void      ResetAddress();/// Reset the address of the branch.

   virtual void      ResetReadEntry() {fReadEntry = -1;}
   virtual void      SetAddress(void *add);/// Set address of this branch.

   virtual void      SetObject(void *objadd);/// Set object this branch is pointing to.
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
/// Set the basket size
/// The function makes sure that the basket size is greater than fEntryOffsetlen

   virtual void      SetBufferAddress(TBuffer *entryBuffer);
/// Set address of this branch directly from a TBuffer to avoid streaming.
/// Note: We do not take ownership of the buffer.

   void              SetCompressionAlgorithm(Int_t algorithm=0);/// Set compression algorithm.
   void              SetCompressionLevel(Int_t level=1);/// Set compression level.
   void              SetCompressionSettings(Int_t settings=1);/// Set compression settings.
   virtual void      SetEntries(Long64_t entries);/// Set the number of entries in this branch.
   virtual void      SetEntryOffsetLen(Int_t len, Bool_t updateSubBranches = kFALSE);
/// Update the default value for the branch's fEntryOffsetLen if and only if
/// it was already non zero (and the new value is not zero)
/// If updateExisting is true, also update all the existing branches.

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
/// Set the branch in a mode where the object are decomposed
/// (Also known as MakeClass mode).
/// Return whether the setting was possible (it is not possible for
/// TBranch and TBranchObject).

   virtual void      SetOffset(Int_t offset=0) {fOffset=offset;}
   virtual void      SetStatus(Bool_t status=1);/// Set branch status to Process or DoNotProcess.
   virtual void      SetTree(TTree *tree) { fTree = tree;}
   virtual void      SetupAddresses();
/// If the branch address is not set,  we set all addresses starting with
/// the top level parent branch.

   virtual void      UpdateAddress() {;}
   virtual void      UpdateFile();
/// Refresh the value of fDirectory (i.e. where this branch writes/reads its buffers)
/// with the current value of fTree->GetCurrentFile unless this branch has been
/// redirected to a different file.  Also update the sub-branches.

   static  void      ResetCount();/// Static function resetting fgCount
```


## code

```cpp
TChain* chain = ...;
Long64_t localEntry = chain->LoadTree(entry);
branch->GetEntry(localEntry);
```



## example



<!-- TBranch.md ends here -->
