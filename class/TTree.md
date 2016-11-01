<!-- TTree.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 六 3月 14 08:35:28 2015 (+0800)
;; Last-Updated: 三 11月  2 00:40:26 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

到 4240

# TTree

继承 TNamed, TAttLine, TAttFill, TAttMarker

A TTree object is a list of TBranch.
To Create a TTree object one must:
 - Create the TTree header via the TTree constructor
 - Call the TBranch constructor for every branch.

To Fill this object, use member function Fill with no parameters. 
The Fill function loops on all defined TBranch.   

## class

```cpp
   // Used as the max value for any TTree range operation.
   static constexpr Long64_t kMaxEntries = TVirtualTreePlayer::kMaxEntries;

   // SetBranchAddress return values
   enum ESetBranchAddressStatus {
      kMissingBranch = -5,
      kInternalError = -4,
      kMissingCompiledCollectionProxy = -3,
      kMismatch = -2,
      kClassMismatch = -1,
      kMatch = 0,
      kMatchConversion = 1,
      kMatchConversionCollection = 2,
      kMakeClass = 3,
      kVoidPtr = 4,
      kNoCheck = 5
   };

   // TTree status bits
   enum {
      kForceRead   = BIT(11),
      kCircular    = BIT(12)
   };

   // Split level modifier
   enum {
      kSplitCollectionOfPointers = 100
   };

   class TClusterIterator
   {
   private:
      TTree    *fTree;        // TTree upon which we are iterating.
      Int_t    fClusterRange; // Which cluster range are we looking at.
      Long64_t fStartEntry;   // Where does the cluster start.
      Long64_t fNextEntry;    // Where does the cluster end (exclusive).

      Long64_t GetEstimatedClusterSize();

   protected:
      friend class TTree;
      TClusterIterator(TTree *tree, Long64_t firstEntry);

   public:
      // Intentionally used the default copy constructor and default destructor
      // as the TClusterIterator does not own the TTree.
      //  TClusterIterator(const TClusterIterator&);
      // ~TClusterIterator();

      // No public constructors, the iterator must be
      // created via TTree::GetClusterIterator

      // Move on to the next cluster and return the starting entry
      // of this next cluster
      Long64_t Next();

      // Return the start entry of the current cluster.
      Long64_t GetStartEntry() {
         return fStartEntry;
      }

      // Return the first entry of the next cluster.
      Long64_t GetNextEntry() {
         return fNextEntry;
      }

      Long64_t operator()() { return Next(); }
   };

   TTree();
   TTree(const char* name, const char* title, Int_t splitlevel = 99);
   virtual ~TTree();

   virtual Int_t           AddBranchToCache(const char *bname, Bool_t subbranches = kFALSE);
   virtual Int_t           AddBranchToCache(TBranch *branch,   Bool_t subbranches = kFALSE);
   virtual Int_t           DropBranchFromCache(const char *bname, Bool_t subbranches = kFALSE);
   virtual Int_t           DropBranchFromCache(TBranch *branch,   Bool_t subbranches = kFALSE);
   virtual TFriendElement *AddFriend(const char* treename, const char* filename = "");
   virtual TFriendElement *AddFriend(const char* treename, TFile* file);
   virtual TFriendElement *AddFriend(TTree* tree, const char* alias = "", Bool_t warn = kFALSE);
   virtual void            AddTotBytes(Int_t tot) { fTotBytes += tot; }
   virtual void            AddZipBytes(Int_t zip) { fZipBytes += zip; }
   virtual Long64_t        AutoSave(Option_t* option = "");
// AutoSave tree header every fAutoSave bytes.
//   When large Trees are produced, it is safe to activate the AutoSave
//   procedure. Some branches may have buffers holding many entries.
//   AutoSave is automatically called by TTree::Fill when the number of bytes
//   generated since the previous AutoSave is greater than fAutoSave bytes.
//   This function may also be invoked by the user, for example every
//   N entries.
//   Each AutoSave generates a new key on the file.
//   Once the key with the tree header has been written, the previous cycle
//   (if any) is deleted.
//   Note that calling TTree::AutoSave too frequently (or similarly calling
//   TTree::SetAutoSave with a small value) is an expensive operation.
//   You should make tests for your own application to find a compromise
//   between speed and the quantity of information you may loose in case of
//   a job crash.
//   In case your program crashes before closing the file holding this tree,
//   the file will be automatically recovered when you will connect the file
//   in UPDATE mode.
//   The Tree will be recovered at the status corresponding to the last AutoSave.
//   if option contains "SaveSelf", gDirectory->SaveSelf() is called.
//   This allows another process to analyze the Tree while the Tree is being filled.
//   if option contains "FlushBaskets", TTree::FlushBaskets is called and all
//   the current basket are closed-out and written to disk individually.
//   By default the previous header is deleted after having written the new header.
//   if option contains "Overwrite", the previous Tree header is deleted
//   before written the new header. This option is slightly faster, but
//   the default option is safer in case of a problem (disk quota exceeded)
//   when writing the new header.
//   The function returns the number of bytes written to the file.
//   if the number of bytes is null, an error has occurred while writing
//   the header to the file.

   virtual Int_t           Branch(TCollection* list, Int_t bufsize = 32000, Int_t splitlevel = 99, const char* name = "");
   virtual Int_t           Branch(TList* list, Int_t bufsize = 32000, Int_t splitlevel = 99);
   virtual Int_t           Branch(const char* folder, Int_t bufsize = 32000, Int_t splitlevel = 99);
   virtual TBranch        *Branch(const char* name, void* address, const char* leaflist, Int_t bufsize = 32000);
           TBranch        *Branch(const char* name, char* address, const char* leaflist, Int_t bufsize = 32000)
   {
      // Overload to avoid confusion between this signature and the template instance.
      return Branch(name,(void*)address,leaflist,bufsize);
   }
   TBranch        *Branch(const char* name, Long_t address, const char* leaflist, Int_t bufsize = 32000)
   {
      // Overload to avoid confusion between this signature and the template instance.
      return Branch(name,(void*)address,leaflist,bufsize);
   }
   TBranch        *Branch(const char* name, int address, const char* leaflist, Int_t bufsize = 32000)
   {
      // Overload to avoid confusion between this signature and the template instance.
      return Branch(name,(void*)(Long_t)address,leaflist,bufsize);
   }
#if !defined(__CINT__)
   virtual TBranch        *Branch(const char* name, const char* classname, void* addobj, Int_t bufsize = 32000, Int_t splitlevel = 99);
#endif
   template <class T> TBranch *Branch(const char* name, const char* classname, T* obj, Int_t bufsize = 32000, Int_t splitlevel = 99)
   {
      // See BranchImpRed for details. Here we __ignore
      return BranchImpRef(name, classname, TBuffer::GetClass(typeid(T)), obj, bufsize, splitlevel);
   }
   template <class T> TBranch *Branch(const char* name, const char* classname, T** addobj, Int_t bufsize = 32000, Int_t splitlevel = 99)
   {
      // See BranchImp for details
      return BranchImp(name, classname, TBuffer::GetClass(typeid(T)), addobj, bufsize, splitlevel);
   }
   template <class T> TBranch *Branch(const char* name, T** addobj, Int_t bufsize = 32000, Int_t splitlevel = 99)
   {
      // See BranchImp for details
      return BranchImp(name, TBuffer::GetClass(typeid(T)), addobj, bufsize, splitlevel);
   }
   template <class T> TBranch *Branch(const char* name, T* obj, Int_t bufsize = 32000, Int_t splitlevel = 99)
   {
      // See BranchImp for details
      return BranchImpRef(name, TBuffer::GetClass(typeid(T)), TDataType::GetType(typeid(T)), obj, bufsize, splitlevel);
   }
   virtual TBranch        *Bronch(const char* name, const char* classname, void* addobj, Int_t bufsize = 32000, Int_t splitlevel = 99);
   virtual TBranch        *BranchOld(const char* name, const char* classname, void* addobj, Int_t bufsize = 32000, Int_t splitlevel = 1);
   virtual TBranch        *BranchRef();
   virtual void            Browse(TBrowser*);
   virtual Int_t           BuildIndex(const char* majorname, const char* minorname = "0");
   TStreamerInfo          *BuildStreamerInfo(TClass* cl, void* pointer = 0, Bool_t canOptimize = kTRUE);
   virtual TFile          *ChangeFile(TFile* file);
   virtual TTree          *CloneTree(Long64_t nentries = -1, Option_t* option = "");
   virtual void            CopyAddresses(TTree*,Bool_t undo = kFALSE);
   virtual Long64_t        CopyEntries(TTree* tree, Long64_t nentries = -1, Option_t *option = "");
   virtual TTree          *CopyTree(const char* selection, Option_t* option = "", Long64_t nentries = kMaxEntries, Long64_t firstentry = 0);
   virtual TBasket        *CreateBasket(TBranch*);
   virtual void            DirectoryAutoAdd(TDirectory *);
   Int_t                   Debug() const { return fDebug; }
   virtual void            Delete(Option_t* option = ""); // *MENU*
   virtual void            Draw(Option_t* opt) { Draw(opt, "", "", kMaxEntries, 0); }
   virtual Long64_t        Draw(const char* varexp, const TCut& selection, Option_t* option = "", Long64_t nentries = kMaxEntries, Long64_t firstentry = 0);
   virtual Long64_t        Draw(const char* varexp, const char* selection, Option_t* option = "", Long64_t nentries = kMaxEntries, Long64_t firstentry = 0); // *MENU*
   virtual void            DropBaskets();/// Remove some baskets from memory.
   virtual void            DropBuffers(Int_t nbytes);/// Drop branch buffers to accommodate nbytes below MaxVirtualsize.
   virtual Int_t           Fill();//填充到buffer中，一定数量之后写入硬盘
/// Fill all branches.
/// This function loops on all the branches of this tree.  For
/// each branch, it copies to the branch buffer (basket) the current
/// values of the leaves data types. If a leaf is a simple data type,
/// a simple conversion to a machine independent format has to be done.
/// This machine independent version of the data is copied into a
/// basket (each branch has its own basket).  When a basket is full
/// (32k worth of data by default), it is then optionally compressed
/// and written to disk (this operation is also called committing or
/// 'flushing' the basket).  The committed baskets are then
/// immediately removed from memory.
/// The function returns the number of bytes committed to the
/// individual branches.
/// If a write error occurs, the number of bytes returned is -1.
/// If no data are written, because, e.g., the branch is disabled,
/// the number of bytes returned is 0.
/// __The baskets are flushed and the Tree header saved at regular intervals__
/// At regular intervals, when the amount of data written so far is
/// greater than fAutoFlush (see SetAutoFlush) all the baskets are flushed to disk.
/// This makes future reading faster as it guarantees that baskets belonging to nearby
/// entries will be on the same disk region.
/// When the first call to flush the baskets happen, we also take this opportunity
/// to optimize the baskets buffers.
/// We also check if the amount of data written is greater than fAutoSave (see SetAutoSave).
/// In this case we also write the Tree header. This makes the Tree recoverable up to this point
/// in case the program writing the Tree crashes.
/// The decisions to FlushBaskets and Auto Save can be made based either on the number
/// of bytes written (fAutoFlush and fAutoSave negative) or on the number of entries
/// written (fAutoFlush and fAutoSave positive).
/// Note that the user can decide to call FlushBaskets and AutoSave in her event loop
/// base on the number of events written instead of the number of bytes written.
/// Note that calling FlushBaskets too often increases the IO time.
/// Note that calling AutoSave too often increases the IO time and also the file size.

   virtual TBranch        *FindBranch(const char* name);
/// Return the branch that correspond to the path 'branchname', which can
/// include the name of the tree or the omitted name of the parent branches.
/// In case of ambiguity, returns the first match.

   virtual TLeaf          *FindLeaf(const char* name);/// Find leaf..
   virtual Int_t           Fit(const char* funcname, const char* varexp, const char* selection = "", Option_t* option = "", Option_t* goption = "", Long64_t nentries = kMaxEntries, Long64_t firstentry = 0); // *MENU*
/// Fit  a projected item(s) from a tree.
/// funcname is a TF1 function.
/// See TTree::Draw() for explanations of the other parameters.
/// By default the temporary histogram created is called htemp.
/// If varexp contains >>hnew , the new histogram created is called hnew
/// and it is kept in the current directory.
/// The function returns the number of selected entries.
/// ## Return status
///  The function returns the status of the histogram fit (see TH1::Fit)
///  If no entries were selected, the function returns -1;
///   (i.e. fitResult is null is the fit is OK)

   virtual Int_t           FlushBaskets() const;
/// Write to disk all the basket that have not yet been individually written.
/// Return the number of bytes written or -1 in case of write error.

   virtual const char     *GetAlias(const char* aliasName) const;/// Returns the expanded value of the alias.  Search in the friends if any.
   virtual Long64_t        GetAutoFlush() const {return fAutoFlush;}
   virtual Long64_t        GetAutoSave()  const {return fAutoSave;}
   virtual TBranch        *GetBranch(const char* name);/// Return pointer to the branch with the given name in this tree or its friends.
   virtual TBranchRef     *GetBranchRef() const { return fBranchRef; };
   virtual Bool_t          GetBranchStatus(const char* branchname) const;
/// Return status of branch with name branchname.
/// - 0 if branch is not activated
/// - 1 if branch is activated

   static  Int_t           GetBranchStyle();
/// Static function returning the current branch style.
/// - style = 0 old Branch
/// - style = 1 new Bronch

   virtual Long64_t        GetCacheSize() const { return fCacheSize; }
   virtual TClusterIterator GetClusterIterator(Long64_t firstentry);
/// Return an iterator over the cluster of baskets starting at firstentry.
/// This iterator is not yet supported for TChain object.

   virtual Long64_t        GetChainEntryNumber(Long64_t entry) const { return entry; }
   virtual Long64_t        GetChainOffset() const { return fChainOffset; }
   TFile                  *GetCurrentFile() const;/// Return pointer to the current file.
           Int_t           GetDefaultEntryOffsetLen() const {return fDefaultEntryOffsetLen;}
           Long64_t        GetDebugMax()  const { return fDebugMax; }
           Long64_t        GetDebugMin()  const { return fDebugMin; }
   TDirectory             *GetDirectory() const { return fDirectory; }
   virtual Long64_t        GetEntries() const   { return fEntries; }//获取entry数
   virtual Long64_t        GetEntries(const char *selection);
/// Return the number of entries matching the selection.
/// Return -1 in case of errors.
/// If the selection uses any arrays or containers, we return the number
/// of entries where at least one element match the selection.
/// GetEntries is implemented using the selector class TSelectorEntries,
/// which can be used directly (see code in TTreePlayer::GetEntries) for
/// additional option.
/// If SetEventList was used on the TTree or TChain, only that subset
/// of entries will be considered.

   virtual Long64_t        GetEntriesFast() const   { return fEntries; }
   virtual Long64_t        GetEntriesFriend() const;
/// Return pointer to the 1st Leaf named name in any Branch of this Tree or
/// any branch in the list of friend trees.

   virtual Long64_t        GetEstimate() const { return fEstimate; }
   virtual Int_t           GetEntry(Long64_t entry = 0, Int_t getall = 0);
/// Read all branches of entry and return total number of bytes read.
/// - getall = 0 : get only active branches
/// - getall = 1 : get all branches
/// The function returns the number of bytes read from the input buffer.
/// If entry does not exist the function returns 0.
/// If an I/O error occurs, the function returns -1.
/// If the Tree has friends, also read the friends entry.
/// ## IMPORTANT NOTE
///
/// By default, GetEntry reuses the space allocated by the previous object
/// for each branch. You can force the previous object to be automatically
/// deleted if you call mybranch.SetAutoDelete(kTRUE) (default is kFALSE).

           Int_t           GetEvent(Long64_t entry = 0, Int_t getall = 0) { return GetEntry(entry, getall); }
   virtual Int_t           GetEntryWithIndex(Int_t major, Int_t minor = 0);
/// Read entry corresponding to major and minor number.
///  The function returns the total number of bytes read.
///  If the Tree has friend trees, the corresponding entry with
///  the index values (major,minor) is read. Note that the master Tree
///  and its friend may have different entry serial numbers corresponding
///  to (major,minor).

   virtual Long64_t        GetEntryNumberWithBestIndex(Long64_t major, Long64_t minor = 0) const;
/// Return entry number corresponding to major and minor number.
/// Note that this function returns only the entry number, not the data
/// To read the data corresponding to an entry number, use TTree::GetEntryWithIndex
/// the BuildIndex function has created a table of Long64_t* of sorted values
/// corresponding to val = major<<31 + minor;
/// The function performs binary search in this sorted table.
/// If it finds a pair that matches val, it returns directly the
/// index in the table.
/// If an entry corresponding to major and minor is not found, the function
/// returns the index of the major,minor pair immediately lower than the
/// requested value, ie it will return -1 if the pair is lower than
/// the first entry in the index.
/// See also GetEntryNumberWithIndex

   virtual Long64_t        GetEntryNumberWithIndex(Long64_t major, Long64_t minor = 0) const;
/// Return entry number corresponding to major and minor number.
/// Note that this function returns only the entry number, not the data
/// To read the data corresponding to an entry number, use TTree::GetEntryWithIndex
/// the BuildIndex function has created a table of Long64_t* of sorted values
/// corresponding to val = major<<31 + minor;
/// The function performs binary search in this sorted table.
/// If it finds a pair that matches val, it returns directly the
/// index in the table, otherwise it returns -1.
/// See also GetEntryNumberWithBestIndex

   TEventList             *GetEventList() const { return fEventList; }
   virtual TEntryList     *GetEntryList();///Returns the entry list, set to this tree
   virtual Long64_t        GetEntryNumber(Long64_t entry) const;
/// Return entry number corresponding to entry.
/// if no TEntryList set returns entry
/// else returns the entry number corresponding to the list index=entry

   virtual Int_t           GetFileNumber() const { return fFileNumber; }
   virtual TTree          *GetFriend(const char*) const;/// Return a pointer to the TTree friend whose name or alias is 'friendname.
   virtual const char     *GetFriendAlias(TTree*) const;
/// If the 'tree' is a friend, this method returns its alias name.
/// This alias is an alternate name for the tree.
/// It can be used in conjunction with a branch or leaf name in a TTreeFormula,
/// to specify in which particular tree the branch or leaf can be found if
/// the friend trees have branches or leaves with the same name as the master
/// tree.
/// It can also be used in conjunction with an alias created using
/// TTree::SetAlias in a TTreeFormula, e.g.:
///      maintree->Draw("treealias.fPx - treealias.myAlias");
/// where fPx is a branch of the friend tree aliased as 'treealias' and 'myAlias'
/// was created using TTree::SetAlias on the friend tree.
/// However, note that 'treealias.myAlias' will be expanded literally,
/// without remembering that it comes from the aliased friend and thus
/// the branch name might not be disambiguated properly, which means
/// that you may not be able to take advantage of this feature.

   TH1                    *GetHistogram() { return GetPlayer()->GetHistogram(); }
   virtual Int_t          *GetIndex() { return &fIndex.fArray[0]; }
   virtual Double_t       *GetIndexValues() { return &fIndexValues.fArray[0]; }
   virtual TIterator      *GetIteratorOnAllLeaves(Bool_t dir = kIterForward);
/// Creates a new iterator that will go through all the leaves on the tree itself and its friend.
   
   virtual TLeaf          *GetLeaf(const char* branchname, const char* leafname);
/// Return pointer to the 1st Leaf named name in any Branch of this
/// Tree or any branch in the list of friend trees.
/// The leaf name can contain the name of a friend tree with the
/// syntax: friend_dir_and_tree.full_leaf_name
/// the friend_dir_and_tree can be of the form:
///     TDirectoryName/TreeName

   virtual TLeaf          *GetLeaf(const char* name);
/// Return pointer to the 1st Leaf named name in any Branch of this
/// Tree or any branch in the list of friend trees.
/// aname may be of the form branchname/leafname

   virtual TList          *GetListOfClones() { return fClones; }
   virtual TObjArray      *GetListOfBranches() { return &fBranches; }
   virtual TObjArray      *GetListOfLeaves() { return &fLeaves; }
   virtual TList          *GetListOfFriends() const { return fFriends; }
   virtual TList          *GetListOfAliases() const { return fAliases; }

   // GetMakeClass is left non-virtual for efficiency reason.
   // Making it virtual affects the performance of the I/O
           Int_t           GetMakeClass() const { return fMakeClass; }

   virtual Long64_t        GetMaxEntryLoop() const { return fMaxEntryLoop; }
   virtual Double_t        GetMaximum(const char* columname);
/// Return maximum of column with name columname.
/// if the Tree has an associated TEventList or TEntryList, the maximum
/// is computed for the entries in this list.

   static  Long64_t        GetMaxTreeSize();/// Static function which returns the tree file size limit in bytes.
   virtual Long64_t        GetMaxVirtualSize() const { return fMaxVirtualSize; }
   virtual Double_t        GetMinimum(const char* columname);
/// Return minimum of column with name columname.
/// if the Tree has an associated TEventList or TEntryList, the minimum
/// is computed for the entries in this list.

   virtual Int_t           GetNbranches() { return fBranches.GetEntriesFast(); }
   TObject                *GetNotify() const { return fNotify; }
   TVirtualTreePlayer     *GetPlayer();/// Load the TTreePlayer (if not already done).
   virtual Int_t           GetPacketSize() const { return fPacketSize; }
   virtual TVirtualPerfStats *GetPerfStats() const { return fPerfStats; }
   virtual Long64_t        GetReadEntry()  const { return fReadEntry; }
   virtual Long64_t        GetReadEvent()  const { return fReadEntry; }
   virtual Int_t           GetScanField()  const { return fScanField; }
   TTreeFormula           *GetSelect()    { return GetPlayer()->GetSelect(); }
   virtual Long64_t        GetSelectedRows() { return GetPlayer()->GetSelectedRows(); }
   virtual Int_t           GetTimerInterval() const { return fTimerInterval; }
           TBuffer*        GetTransientBuffer(Int_t size);
   virtual Long64_t        GetTotBytes() const { return fTotBytes; }
   virtual TTree          *GetTree() const { return const_cast<TTree*>(this); }
   virtual TVirtualIndex  *GetTreeIndex() const { return fTreeIndex; }
   virtual Int_t           GetTreeNumber() const { return 0; }
   virtual Int_t           GetUpdate() const { return fUpdate; }
   virtual TList          *GetUserInfo();
/// Return a pointer to the list containing user objects associated to this tree.
/// The list is automatically created if it does not exist.
/// WARNING: By default the TTree destructor will delete all objects added
/// to this list. If you do not want these objects to be deleted,
/// call:
///     mytree->GetUserInfo()->Clear();
/// before deleting the tree.

   // See TSelectorDraw::GetVar
   TTreeFormula           *GetVar(Int_t i)  { return GetPlayer()->GetVar(i); }
   // See TSelectorDraw::GetVar
   TTreeFormula           *GetVar1() { return GetPlayer()->GetVar1(); }
   // See TSelectorDraw::GetVar
   TTreeFormula           *GetVar2() { return GetPlayer()->GetVar2(); }
   // See TSelectorDraw::GetVar
   TTreeFormula           *GetVar3() { return GetPlayer()->GetVar3(); }
   // See TSelectorDraw::GetVar
   TTreeFormula           *GetVar4() { return GetPlayer()->GetVar4(); }
   // See TSelectorDraw::GetVal
   virtual Double_t       *GetVal(Int_t i)   { return GetPlayer()->GetVal(i); }
   // See TSelectorDraw::GetVal
   virtual Double_t       *GetV1()   { return GetPlayer()->GetV1(); }
   // See TSelectorDraw::GetVal
   virtual Double_t       *GetV2()   { return GetPlayer()->GetV2(); }
   // See TSelectorDraw::GetVal
   virtual Double_t       *GetV3()   { return GetPlayer()->GetV3(); }
   // See TSelectorDraw::GetVal
   virtual Double_t       *GetV4()   { return GetPlayer()->GetV4(); }
   virtual Double_t       *GetW()    { return GetPlayer()->GetW(); }
   virtual Double_t        GetWeight() const   { return fWeight; }
   virtual Long64_t        GetZipBytes() const { return fZipBytes; }
   virtual void            IncrementTotalBuffers(Int_t nbytes) { fTotalBuffers += nbytes; }
   Bool_t                  IsFolder() const { return kTRUE; }
   virtual Int_t           LoadBaskets(Long64_t maxmemory = 2000000000);
/// Read in memory all baskets from all branches up to the limit of maxmemory bytes.
/// If maxmemory is non null and positive SetMaxVirtualSize is called
/// with this value. Default for maxmemory is 2000000000 (2 Gigabytes).
/// The function returns the total number of baskets read into memory
/// if negative an error occurred while loading the branches.
/// This method may be called to force branch baskets in memory
/// when random access to branch entries is required.
/// If random access to only a few branches is required, you should
/// call directly TBranch::LoadBaskets.

   virtual Long64_t        LoadTree(Long64_t entry);
/// Set current entry.
/// Returns -2 if entry does not exist (just as TChain::LoadTree()).
/// Note: This function is overloaded in TChain.

   virtual Long64_t        LoadTreeFriend(Long64_t entry, TTree* T);
/// Load entry on behalf of our master tree, we may use an index.
/// Called by LoadTree() when the masterTree looks for the entry
/// number in a friend tree (us) corresponding to the passed entry
/// number in the masterTree.
/// If we have no index, our entry number and the masterTree entry
/// number are the same.
/// If we *do* have an index, we must find the (major, minor) value pair
/// in masterTree to locate our corresponding entry.

   virtual Int_t           MakeClass(const char* classname = 0, Option_t* option = "");
/// Generate a skeleton analysis class for this tree.
/// The following files are produced: classname.h and classname.C.
/// If classname is 0, classname will be called "nameoftree".
/// The generated code in classname.h includes the following:
/// - Identification of the original tree and the input file name.
/// - Definition of an analysis class (data members and member functions).
/// - The following member functions:
///   - constructor (by default opening the tree file),
///   - GetEntry(Long64_t entry),
///   - Init(TTree* tree) to initialize a new TTree,
///   - Show(Long64_t entry) to read and dump entry.
/// The generated code in classname.C includes only the main
/// analysis function Loop.
/// NOTE: Do not use the code generated for a single TTree which is part
/// of a TChain to process that entire TChain.  The maximum dimensions
/// calculated for arrays on the basis of a single TTree from the TChain
/// might be (will be!) too small when processing all of the TTrees in
/// the TChain.  You must use myChain.MakeClass() to generate the code,
/// not myTree.MakeClass(...).

   virtual Int_t           MakeCode(const char* filename = 0);
/// Generate a skeleton function for this tree.
/// The function code is written on filename.
/// If filename is 0, filename will be called nameoftree.C
/// The generated code includes the following:
/// - Identification of the original Tree and Input file name,
/// - Opening the Tree file,
/// - Declaration of Tree variables,
/// - Setting of branches addresses,
/// - A skeleton for the entry loop.
/// To use this function:
/// - Open your Tree file (eg: TFile f("myfile.root");)
/// - T->MakeCode("MyAnalysis.C");
/// where T is the name of the TTree in file myfile.root
/// and MyAnalysis.C the name of the file created by this function.
/// NOTE: Since the implementation of this function, a new and better
/// function TTree::MakeClass() has been developed.

   virtual Int_t           MakeProxy(const char* classname, const char* macrofilename = 0, const char* cutfilename = 0, const char* option = 0, Int_t maxUnrolling = 3);
/// Generate a skeleton analysis class for this Tree using TBranchProxy.
/// TBranchProxy is the base of a class hierarchy implementing an
/// indirect access to the content of the branches of a TTree.
/// "proxyClassname" is expected to be of the form:
///     [path/]fileprefix
/// The skeleton will then be generated in the file:
///     fileprefix.h
/// located in the current directory or in 'path/' if it is specified.
/// The class generated will be named 'fileprefix'
///
/// "macrofilename" and optionally "cutfilename" are expected to point
/// to source files which will be included by the generated skeleton.
/// Method of the same name as the file(minus the extension and path)
/// will be called by the generated skeleton's Process method as follow:
///     [if (cutfilename())] htemp->Fill(macrofilename());
/// "option" can be used select some of the optional features during
/// the code generation.  The possible options are:
/// - nohist : indicates that the generated ProcessFill should not fill the histogram.
/// 'maxUnrolling' controls how deep in the class hierarchy does the
/// system 'unroll' classes that are not split.  Unrolling a class
/// allows direct access to its data members (this emulates the behavior
/// of TTreeFormula).
///
/// The main features of this skeleton are:
/// * on-demand loading of branches
/// * ability to use the 'branchname' as if it was a data member
/// * protection against array out-of-bounds errors
/// * ability to use the branch data as an object (when the user code is available)
/// If a file name macrofilename.h (or .hh, .hpp, .hxx, .hPP, .hXX) exist
/// it is included before the declaration of the proxy class.  This can
/// be used in particular to insure that the include files needed by
/// the macro file are properly loaded.
/// The default histogram is accessible via the variable named 'htemp'.
/// If the library of the classes describing the data in the branch is
/// loaded, the skeleton will add the needed #include statements and
/// give the ability to access the object stored in the branches.

   virtual Int_t           MakeSelector(const char* selector = 0, Option_t* option = "");//生成要Process()的文件
/// Generate skeleton selector class for this tree.
/// The following files are produced: selector.h and selector.C.
/// If selector is 0, the selector will be called "nameoftree".
/// The option can be used to specify the branches that will have a data member.
///    - If option is "=legacy", a pre-ROOT6 selector will be generated (data
///      members and branch pointers instead of TTreeReaders).
///    - If option is empty, readers will be generated for each leaf.
///    - If option is "@", readers will be generated for the topmost branches.
///    - Individual branches can also be picked by their name:
///       - "X" generates readers for leaves of X.
///       - "@X" generates a reader for X as a whole.
///       - "@X;Y" generates a reader for X as a whole and also readers for the
///         leaves of Y.
///    - For further examples see the figure below.
/// The generated code in selector.h includes the following:
///    - Identification of the original Tree and Input file name
///    - Definition of selector class (data and functions)
///    - The following class functions:
///       - constructor and destructor
///       - void    Begin(TTree *tree)
///       - void    SlaveBegin(TTree *tree)
///       - void    Init(TTree *tree)
///       - Bool_t  Notify()
///       - Bool_t  Process(Long64_t entry)
///       - void    Terminate()
///       - void    SlaveTerminate()
/// The class selector derives from TSelector.
/// The generated code in selector.C includes empty functions defined above.
/// To use this function:
///    - connect your Tree file (eg: `TFile f("myfile.root");`)
///    - `T->MakeSelector("myselect");`
/// where T is the name of the Tree in file myfile.root
/// and myselect.h, myselect.C the name of the files created by this function.
/// In a ROOT session, you can do:
///     root > T->Process("myselect.C")

   Bool_t                  MemoryFull(Int_t nbytes);/// Check if adding nbytes to memory we are still below MaxVirtualsize.
   virtual Long64_t        Merge(TCollection* list, Option_t* option = "");
/// Merge the trees in the TList into this tree.
/// Returns the total number of entries in the merged tree.

   virtual Long64_t        Merge(TCollection* list, TFileMergeInfo *info);
/// Merge the trees in the TList into this tree.
/// If info->fIsFirst is true, first we clone this TTree info the directory
/// info->fOutputDirectory and then overlay the new TTree information onto
/// this TTree object (so that this TTree object is now the appropriate to
/// use for further merging).
/// Returns the total number of entries in the merged tree.

   static  TTree          *MergeTrees(TList* list, Option_t* option = "");
/// Static function merging the trees in the TList into a new tree.
/// Trees in the list can be memory or disk-resident trees.
/// The new tree is created in the current directory (memory if gROOT).

   virtual Bool_t          Notify();/// Function called when loading a new class library.
   virtual void            OptimizeBaskets(ULong64_t maxMemory=10000000, Float_t minComp=1.1, Option_t *option="");
/// This function may be called after having filled some entries in a Tree
/// Using the information in the existing branch buffers, it will reassign
/// new branch buffer sizes to optimize time and memory.
/// The function computes the best values for branch buffer sizes such that
/// the total buffer sizes is less than maxMemory and nearby entries written
/// at the same time.
/// In case the branch compression factor for the data written so far is less
/// than compMin, the compression is disabled.
/// if option ="d" an analysis report is printed.

   TPrincipal             *Principal(const char* varexp = "", const char* selection = "", Option_t* option = "np", Long64_t nentries = kMaxEntries, Long64_t firstentry = 0);
/// Interface to the Principal Components Analysis class.
/// Create an instance of TPrincipal
/// Fill it with the selected variables
/// - if option "n" is specified, the TPrincipal object is filled with
///                 normalized variables.
/// - If option "p" is specified, compute the principal components
/// - If option "p" and "d" print results of analysis
/// - If option "p" and "h" generate standard histograms
/// - If option "p" and "c" generate code of conversion functions
/// - return a pointer to the TPrincipal object. It is the user responsibility
/// - to delete this object.
/// - The option default value is "np"
/// see TTree::Draw for explanation of the other parameters.
/// The created object is  named "principal" and a reference to it
/// is added to the list of specials Root objects.

   virtual void            Print(Option_t* option = "") const; // *MENU*
/// Print a summary of the tree contents.
/// -  If option contains "all" friend trees are also printed.
/// -  If option contains "toponly" only the top level branches are printed.
/// -  If option contains "clusters" information about the cluster of baskets is printed.
/// Wildcarding can be used to print only a subset of the branches, e.g.,
/// T.Print("Elec*") will print all branches with name starting with "Elec".

   virtual void            PrintCacheStats(Option_t* option = "") const;
/// print statistics about the TreeCache for this tree, like
/// if option = "a" the list of blocks in the cache is printed

   virtual Long64_t        Process(const char* filename, Option_t* option = "", Long64_t nentries = kMaxEntries, Long64_t firstentry = 0); // *MENU*
/// Process this tree executing the TSelector code in the specified filename.
/// The return value is -1 in case of error and TSelector::GetStatus() in
/// in case of success.
/// The code in filename is loaded (interpreted or compiled, see below),
/// filename must contain a valid class implementation derived from TSelector,
/// where TSelector has the following member functions:
/// - `Begin()`:         called every time a loop on the tree starts,
///                      a convenient place to create your histograms.
/// - `SlaveBegin()`:    called after Begin(), when on PROOF called only on the
///                      slave servers.
/// - `Process()`:       called for each event, in this function you decide what
///                      to read and fill your histograms.
/// - `SlaveTerminate`:  called at the end of the loop on the tree, when on PROOF
///                      called only on the slave servers.
/// - `Terminate()`:     called at the end of the loop on the tree,
///                      a convenient place to draw/fit your histograms.
/// If filename is of the form file.C, the file will be interpreted.
/// If filename is of the form file.C++, the file file.C will be compiled
/// and dynamically loaded.
/// If filename is of the form file.C+, the file file.C will be compiled
/// and dynamically loaded. At next call, if file.C is older than file.o
/// and file.so, the file.C is not compiled, only file.so is loaded.

#if defined(__CINT__)
#if defined(R__MANUAL_DICT)
   virtual Long64_t        Process(void* selector, Option_t* option = "", Long64_t nentries = kMaxEntries, Long64_t firstentry = 0);
#endif
#else
   virtual Long64_t        Process(TSelector* selector, Option_t* option = "", Long64_t nentries = kMaxEntries, Long64_t firstentry = 0);
/// Process this tree executing the code in the specified selector.
/// The return value is -1 in case of error and TSelector::GetStatus() in
/// in case of success.
///   The TSelector class has the following member functions:
/// - `Begin()`:        called every time a loop on the tree starts,
///                     a convenient place to create your histograms.
/// - `SlaveBegin()`:   called after Begin(), when on PROOF called only on the
///                     slave servers.
/// - `Process()`:      called for each event, in this function you decide what
///                     to read and fill your histograms.
/// - `SlaveTerminate`: called at the end of the loop on the tree, when on PROOF
///                     called only on the slave servers.
/// - `Terminate()`:    called at the end of the loop on the tree,
///                     a convenient place to draw/fit your histograms.
///  If the Tree (Chain) has an associated EventList, the loop is on the nentries
///  of the EventList, starting at firstentry, otherwise the loop is on the
///  specified Tree entries.
#endif
   virtual Long64_t        Project(const char* hname, const char* varexp, const char* selection = "", Option_t* option = "", Long64_t nentries = kMaxEntries, Long64_t firstentry = 0);
/// Make a projection of a tree using selections.
/// Depending on the value of varexp (described in Draw) a 1-D, 2-D, etc.,
/// projection of the tree will be filled in histogram hname.
/// Note that the dimension of hname must match with the dimension of varexp.

   virtual TSQLResult     *Query(const char* varexp = "", const char* selection = "", Option_t* option = "", Long64_t nentries = kMaxEntries, Long64_t firstentry = 0);/// Loop over entries and return a TSQLResult object containing entries following selection.
   virtual Long64_t        ReadFile(const char* filename, const char* branchDescriptor = "", char delimiter = ' ');
/// Create or simply read branches from filename.
/// if branchDescriptor = "" (default), it is assumed that the Tree descriptor
/// is given in the first line of the file with a syntax like
///     A/D:Table[2]/F:Ntracks/I:astring/C
/// otherwise branchDescriptor must be specified with the above syntax.
/// - If the type of the first variable is not specified, it is assumed to be "/F"
/// - If the type of any other variable is not specified, the type of the previous
///   variable is assumed. eg
///     - `x:y:z`      (all variables are assumed of type "F"
///     - `x/D:y:z`    (all variables are of type "D"
///     - `x:y/D:z`    (x is type "F", y and z of type "D"
/// delimiter allows for the use of another delimiter besides whitespace.
/// This provides support for direct import of common data file formats
/// like csv.  If delimiter != ' ' and branchDescriptor == "", then the
/// branch description is taken from the first line in the file, but
/// delimiter is used for the branch names tokenization rather than ':'.
/// Note however that if the values in the first line do not use the
/// /[type] syntax, all variables are assumed to be of type "F".
/// If the filename ends with extensions .csv or .CSV and a delimiter is
/// not specified (besides ' '), the delimiter is automatically set to ','.
/// Lines in the input file starting with "#" are ignored. Leading whitespace
/// for each column data is skipped. Empty lines are skipped.
/// A TBranch object is created for each variable in the expression.
/// The total number of rows read from the file is returned.

   virtual Long64_t        ReadStream(std::istream& inputStream, const char* branchDescriptor = "", char delimiter = ' ');
/// Create or simply read branches from an input stream.
/// See reference information for TTree::ReadFile

   virtual void            Refresh();
///  Refresh contents of this tree and its branches from the current status on disk.
///  One can call this function in case the tree file is being
///  updated by another process.

   virtual void            RecursiveRemove(TObject *obj);
/// Make sure that obj (which is being deleted or will soon be) is no
/// longer referenced by this TTree.

   virtual void            RemoveFriend(TTree*);/// Remove a friend from the list of friends.
   virtual void            Reset(Option_t* option = "");// Reset baskets, buffers and entries count in all branches and leaves.
   virtual void            ResetAfterMerge(TFileMergeInfo *);/// Resets the state of this TTree after a merge (keep the customization but forget the data).
   virtual void            ResetBranchAddress(TBranch *);
/// Tell all of our branches to set their addresses to zero.
/// Note: If any of our branches own any objects, they are deleted.

   virtual void            ResetBranchAddresses();/// Tell all of our branches to drop their current objects and allocate new ones.
   virtual Long64_t        Scan(const char* varexp = "", const char* selection = "", Option_t* option = "", Long64_t nentries = kMaxEntries, Long64_t firstentry = 0); // *MENU*
// Loop over tree entries and print entries passing selection.
// If varexp is 0 (or "") then print only first 8 columns.
// If varexp = "*" print all columns.
// Otherwise a columns selection can be made using "var1:var2:var3".
// See TTreePlayer::Scan for more information

   virtual Bool_t          SetAlias(const char* aliasName, const char* aliasFormula);
/// Set a tree variable alias.
/// Set an alias for an expression/formula based on the tree 'variables'.
/// The content of 'aliasName' can be used in TTreeFormula (i.e. TTree::Draw,
/// TTree::Scan, TTreeViewer) and will be evaluated as the content of
/// 'aliasFormula'.
/// If the content of 'aliasFormula' only contains symbol names, periods and
/// array index specification (for example event.fTracks[3]), then
/// the content of 'aliasName' can be used as the start of symbol.
/// If the alias 'aliasName' already existed, it is replaced by the new value.
/// When being used, the alias can be preceded by an eventual 'Friend Alias'
/// (see TTree::GetFriendAlias)
/// Return true if it was added properly.

   virtual void            SetAutoSave(Long64_t autos = -300000000);
/// This function may be called at the start of a program to change
/// the default value for fAutoSave (and for SetAutoSave) is -300000000, ie 300 MBytes
/// When filling the Tree the branch buffers as well as the Tree header
/// will be flushed to disk when the watermark is reached.
/// If fAutoSave is positive the watermark is reached when a multiple of fAutoSave
/// entries have been written.
/// If fAutoSave is negative the watermark is reached when -fAutoSave bytes
/// have been written to the file.
/// In case of a program crash, it will be possible to recover the data in the Tree
/// up to the last AutoSave point.

   virtual void            SetAutoFlush(Long64_t autof = -30000000);
/// This function may be called at the start of a program to change
/// the default value for fAutoFlush.
/// ### CASE 1 : autof > 0
/// autof is the number of consecutive entries after which TTree::Fill will
/// flush all branch buffers to disk.
/// ### CASE 2 : autof < 0
/// When filling the Tree the branch buffers will be flushed to disk when
/// more than autof bytes have been written to the file. At the first FlushBaskets
/// TTree::Fill will replace fAutoFlush by the current value of fEntries.
/// Calling this function with autof<0 is interesting when it is hard to estimate
/// the size of one entry. This value is also independent of the Tree.
/// The Tree is initialized with fAutoFlush=-30000000, ie that, by default,
/// the first AutoFlush will be done when 30 MBytes of data are written to the file.
/// ### CASE 3 : autof = 0
/// The AutoFlush mechanism is disabled.
/// Flushing the buffers at regular intervals optimize the location of
/// consecutive entries on the disk by creating clusters of baskets.
/// A cluster of baskets is a set of baskets that contains all
/// the data for a (consecutive) set of entries and that is stored
/// consecutively on the disk.   When reading all the branches, this
/// is the minimum set of baskets that the TTreeCache will read.

   virtual void            SetBasketSize(const char* bname, Int_t buffsize = 16000);
/// Set a branch's basket size.
/// bname is the name of a branch.
/// - if bname="*", apply to all branches.
/// - if bname="xxx*", apply to all branches with name starting with xxx
/// see TRegexp for wildcarding options
/// buffsize = branc basket size

#if !defined(__CINT__)
   virtual Int_t           SetBranchAddress(const char *bname,void *add, TBranch **ptr = 0);
/// Change branch address, dealing with clone trees properly.
/// See TTree::CheckBranchAddressType for the semantic of the return value.
/// Note: See the comments in TBranchElement::SetAddress() for the
/// meaning of the addr parameter and the object ownership policy.
#endif
   virtual Int_t           SetBranchAddress(const char *bname,void *add, TClass *realClass, EDataType datatype, Bool_t isptr);
/// Verify the validity of the type of addr before calling SetBranchAddress.
/// See TTree::CheckBranchAddressType for the semantic of the return value.
/// Note: See the comments in TBranchElement::SetAddress() for the
/// meaning of the addr parameter and the object ownership policy.

   virtual Int_t           SetBranchAddress(const char *bname,void *add, TBranch **ptr, TClass *realClass, EDataType datatype, Bool_t isptr);
/// Verify the validity of the type of addr before calling SetBranchAddress.
/// See TTree::CheckBranchAddressType for the semantic of the return value.
/// Note: See the comments in TBranchElement::SetAddress() for the
/// meaning of the addr parameter and the object ownership policy.

   template <class T> Int_t SetBranchAddress(const char *bname, T **add, TBranch **ptr = 0) {
      TClass *cl = TClass::GetClass(typeid(T));
      EDataType type = kOther_t;
      if (cl==0) type = TDataType::GetType(typeid(T));
      return SetBranchAddress(bname,add,ptr,cl,type,true);
   }
#ifndef R__NO_CLASS_TEMPLATE_SPECIALIZATION
   // This can only be used when the template overload resolution can distringuish between
   // T* and T**
   template <class T> Int_t SetBranchAddress(const char *bname, T *add, TBranch **ptr = 0) {
      TClass *cl = TClass::GetClass(typeid(T));
      EDataType type = kOther_t;
      if (cl==0) type = TDataType::GetType(typeid(T));
      return SetBranchAddress(bname,add,ptr,cl,type,false);
   }
#endif
   virtual void            SetBranchStatus(const char* bname, Bool_t status = 1, UInt_t* found = 0);
/// Set branch status to Process or DoNotProcess.
/// When reading a Tree, by default, all branches are read.
/// One can speed up considerably the analysis phase by activating
/// only the branches that hold variables involved in a query.
/// bname is the name of a branch.
/// - if bname="*", apply to all branches.
/// - if bname="xxx*", apply to all branches with name starting with xxx
/// see TRegexp for wildcarding options
/// - status = 1  branch will be processed
/// - = 0  branch will not be processed
/// __WARNING! WARNING! WARNING!__
/// SetBranchStatus is matching the branch based on match of the branch
/// 'name' and not on the branch hierarchy! In order to be able to
/// selectively enable a top level object that is 'split' you need to make
/// sure the name of the top level branch is prefixed to the sub-branches'
/// name (by adding a dot ('.') at the end of the Branch creation and use the
/// corresponding bname.
/// If found is not 0, the number of branch(es) found matching the regular
/// expression is returned in *found AND the error message 'unknown branch'
/// is suppressed.

   static  void            SetBranchStyle(Int_t style = 1);  //style=0 for old branch, =1 for new branch style
   virtual Int_t           SetCacheSize(Long64_t cachesize = -1);
/// Set maximum size of the file cache .
/// - if cachesize = 0 the existing cache (if any) is deleted.
/// - if cachesize = -1 (default) it is set to the AutoFlush value when writing
///    the Tree (default is 30 MBytes).
/// Returns:
/// - 0 size set, cache was created if possible
/// - -1 on error

   virtual Int_t           SetCacheEntryRange(Long64_t first, Long64_t last);
///interface to TTreeCache to set the cache entry range
/// Returns:
/// - 0 entry range set
/// - -1 on error

   virtual void            SetCacheLearnEntries(Int_t n=10);/// Interface to TTreeCache to set the number of entries for the learning phase
   virtual void            SetChainOffset(Long64_t offset = 0) { fChainOffset=offset; }
   virtual void            SetCircular(Long64_t maxEntries);
/// Enable/Disable circularity for this tree.
/// if maxEntries > 0 a maximum of maxEntries is kept in one buffer/basket
/// per branch in memory.
///   Note that when this function is called (maxEntries>0) the Tree
///   must be empty or having only one basket per branch.
/// if maxEntries <= 0 the tree circularity is disabled.
/// #### NOTE 1:
///  Circular Trees are interesting in online real time environments
///  to store the results of the last maxEntries events.
/// #### NOTE 2:
///  Calling SetCircular with maxEntries <= 0 is necessary before
///  merging circular Trees that have been saved on files.
/// #### NOTE 3:
///  SetCircular with maxEntries <= 0 is automatically called
///  by TChain::Merge
/// #### NOTE 4:
///  A circular Tree can still be saved in a file. When read back,
///  it is still a circular Tree and can be filled again.

   virtual void            SetDebug(Int_t level = 1, Long64_t min = 0, Long64_t max = 9999999); // *MENU*
/// Set the debug level and the debug range.
/// For entries in the debug range, the functions TBranchElement::Fill
/// and TBranchElement::GetEntry will print the number of bytes filled
/// or read for each branch.

   virtual void            SetDefaultEntryOffsetLen(Int_t newdefault, Bool_t updateExisting = kFALSE);
/// Update the default value for the branch's fEntryOffsetLen.
/// If updateExisting is true, also update all the existing branches.
/// If newdefault is less than 10, the new default value will be 10.

   virtual void            SetDirectory(TDirectory* dir);
/// Change the tree's directory.
/// Remove reference to this tree from current directory and
/// add reference to new directory dir.  The dir parameter can
/// be 0 in which case the tree does not belong to any directory.

   virtual Long64_t        SetEntries(Long64_t n = -1);
/// Change number of entries in the tree.
/// If n >= 0, set number of entries in the tree = n.
/// If n < 0, set number of entries in the tree to match the
/// number of entries in each branch. (default for n is -1)
/// This function should be called only when one fills each branch
/// independently via TBranch::Fill without calling TTree::Fill.
/// Calling TTree::SetEntries() make sense only if the number of entries
/// in each branch is identical, a warning is issued otherwise.
/// The function returns the number of entries.

   virtual void            SetEstimate(Long64_t nentries = 1000000);
/// Set number of entries to estimate variable limits.
/// If n is -1, the estimate is set to be the current maximum
/// for the tree (i.e. GetEntries() + 1)
/// If n is less than -1, the behavior is undefined.

   virtual void            SetFileNumber(Int_t number = 0);
/// Set fFileNumber to number.
/// fFileNumber is used by TTree::Fill to set the file name
/// for a new file to be created when the current file exceeds fgTreeMaxSize.
///    (see TTree::ChangeFile)
/// if fFileNumber=10, the new file name will have a suffix "_11",
/// ie, fFileNumber is incremented before setting the file name

   virtual void            SetEventList(TEventList* list);
/// This function transfroms the given TEventList into a TEntryList
/// The new TEntryList is owned by the TTree and gets deleted when the tree
/// is deleted. This TEntryList can be returned by GetEntryList() function.

   virtual void            SetEntryList(TEntryList* list, Option_t *opt="");/// Set an EntryList
   virtual void            SetMakeClass(Int_t make);
/// Set all the branches in this TTree to be in decomposed object mode
/// (also known as MakeClass mode).

   virtual void            SetMaxEntryLoop(Long64_t maxev = kMaxEntries) { fMaxEntryLoop = maxev; } // *MENU*
   static  void            SetMaxTreeSize(Long64_t maxsize = 1900000000);
/// Set the maximum size in bytes of a Tree file (static function).
/// The default size is 100000000000LL, ie 100 Gigabytes.
/// In TTree::Fill, when the file has a size > fgMaxTreeSize,
/// the function closes the current file and starts writing into
/// a new file with a name of the style "file_1.root" if the original
/// requested file name was "file.root".

   virtual void            SetMaxVirtualSize(Long64_t size = 0) { fMaxVirtualSize = size; } // *MENU*
   virtual void            SetName(const char* name); // *MENU* /// Change the name of this tree.
   virtual void            SetNotify(TObject* obj) { fNotify = obj; }
   virtual void            SetObject(const char* name, const char* title);/// Change the name and title of this tree.
   virtual void            SetParallelUnzip(Bool_t opt=kTRUE, Float_t RelSize=-1);/// Enable or disable parallel unzipping of Tree buffers.
   virtual void            SetPerfStats(TVirtualPerfStats* perf);/// Set perf stats
   virtual void            SetScanField(Int_t n = 50) { fScanField = n; } // *MENU*
   virtual void            SetTimerInterval(Int_t msec = 333) { fTimerInterval=msec; }
   virtual void            SetTreeIndex(TVirtualIndex* index);
/// The current TreeIndex is replaced by the new index.
/// Note that this function does not delete the previous index.

   virtual void            SetWeight(Double_t w = 1, Option_t* option = "");
/// Set tree weight.
/// The weight is used by TTree::Draw to automatically weight each
/// selected entry in the resulting histogram.
/// This function is redefined by TChain::SetWeight. In case of a
/// TChain, an option "global" may be specified to set the same weight
/// for all trees in the TChain instead of the default behaviour
/// using the weights of each tree in the chain (see TChain::SetWeight).

   virtual void            SetUpdate(Int_t freq = 0) { fUpdate = freq; }
   virtual void            Show(Long64_t entry = -1, Int_t lenmax = 20);
/// Print values of all active leaves for entry.
/// - if entry==-1, print current entry (default)
/// - if a leaf is an array, a maximum of lenmax elements is printed.

   virtual void            StartViewer(); // *MENU*
/// Start the TTreeViewer on this tree.
/// - ww is the width of the canvas in pixels
/// - wh is the height of the canvas in pixels

   virtual Int_t           StopCacheLearningPhase();
/// Stop the cache learning phase
/// Returns:
/// - 0 learning phase stopped or not active
/// - -1 on error

   virtual Int_t           UnbinnedFit(const char* funcname, const char* varexp, const char* selection = "", Option_t* option = "", Long64_t nentries = kMaxEntries, Long64_t firstentry = 0);
/// Unbinned fit of one or more variable(s) from a tree.
/// funcname is a TF1 function.
/// See TTree::Draw for explanations of the other parameters.
/// Fit the variable varexp using the function funcname using the
/// selection cuts given by selection.
/// The list of fit options is given in parameter option.
/// - option = "Q" Quiet mode (minimum printing)
/// - option = "V" Verbose mode (default is between Q and V)
/// - option = "E" Perform better Errors estimation using Minos technique
/// - option = "M" More. Improve fit results
/// With this setup:
/// - Parameters 0->3 can vary freely
/// - Parameter 4 has boundaries [-10,-4] with initial value -8
/// - Parameter 5 is fixed to 100.
/// For the fit to be meaningful, the function must be self-normalized.
/// 1, 2 and 3 Dimensional fits are supported. See also TTree::Fit
/// Return status:
/// - The function return the status of the fit in the following form
///   fitResult = migradResult + 10*minosResult + 100*hesseResult + 1000*improveResult
/// - The fitResult is 0 is the fit is OK.
/// - The fitResult is negative in case of an error not connected with the fit.
/// - The number of entries used in the fit can be obtained via mytree.GetSelectedRows();
/// - If the number of selected entries is null the function returns -1

   void                    UseCurrentStyle();/// Replace current attributes by current style.
   virtual Int_t           Write(const char *name=0, Int_t option=0, Int_t bufsize=0);
/// Write this object to the current directory. For more see TObject::Write
/// If option & kFlushBasket, call FlushBasket before writing the tree.

   virtual Int_t           Write(const char *name=0, Int_t option=0, Int_t bufsize=0) const;
/// Write this object to the current directory. For more see TObject::Write
/// Write calls TTree::FlushBaskets before writing the tree.
```

## code

```cpp
/// You can specify boundary limits for some or all parameters via

func->SetParLimits(p_number, parmin, parmax);

/// if parmin>=parmax, the parameter is fixed

/// Note that you are not forced to fix the limits for all parameters.
/// For example, if you fit a function with 6 parameters, you can do:

func->SetParameters(0,3.1,1.e-6,0.1,-8,100);
func->SetParLimits(4,-10,-4);
func->SetParLimits(5, 1,1);

/// i.e. It must have the same integral regardless of the parameter
/// settings.  Otherwise the fit will effectively just maximize the
/// area.

/// It is mandatory to have a normalization variable
/// which is fixed for the fit.  e.g.

TF1* f1 = new TF1("f1", "gaus(0)/sqrt(2*3.14159)/[2]", 0, 5);
f1->SetParameters(1, 3.1, 0.01);
f1->SetParLimits(0, 1, 1); // fix the normalization parameter to 1
data->UnbinnedFit("f1", "jpsimass", "jpsipt>3.0");
```

```cpp
// This gives the possibility to play with more than one index, e.g.,

TVirtualIndex* oldIndex = tree.GetTreeIndex();
tree.SetTreeIndex(newIndex);
tree.Draw();
tree.SetTreeIndex(oldIndex);
tree.Draw(); etc
```

```cpp
/// Assume a tree T with sub-branches a,b,c,d,e,f,g,etc..
/// when doing T.GetEntry(i) all branches are read for entry i.
/// to read only the branches c and e, one can do

T.SetBranchStatus("*",0); //disable all branches
T.SetBranchStatus("c",1);
T.setBranchStatus("e",1);
T.GetEntry(i);

/// bname is interpreted as a wildcarded TRegexp (see TRegexp::MakeWildcard).
/// Thus, "a*b" or "a.*b" matches branches starting with "a" and ending with
/// "b", but not any other branch with an "a" followed at some point by a
/// "b". For this second behavior, use "*a*b*". Note that TRegExp does not
/// support '|', and so you cannot select, e.g. track and shower branches
/// with "track|shower".

/// I.e If your Tree has been created in split mode with a parent branch "parent."
/// (note the trailing dot).

T.SetBranchStatus("parent",1);

/// will not activate the sub-branches of "parent". You should do:

T.SetBranchStatus("parent*",1);

/// Without the trailing dot in the branch creation you have no choice but to
/// call SetBranchStatus explicitly for each of the sub branches.

/// An alternative to this function is to read directly and only
/// the interesting branches. Example:

TBranch *brc = T.GetBranch("c");
TBranch *bre = T.GetBranch("e");
brc->GetEntry(i);
bre->GetEntry(i);
```

```cpp
tree->SetAlias("x1","(tdc1[1]-tdc1[0])/49");
tree->SetAlias("y1","(tdc1[3]-tdc1[2])/47");
tree->SetAlias("x2","(tdc2[1]-tdc2[0])/49");
tree->SetAlias("y2","(tdc2[3]-tdc2[2])/47");
tree->Draw("y2-y1:x2-x1");

tree->SetAlias("theGoodTrack","event.fTracks[3]");
tree->Draw("theGoodTrack.fPx"); // same as "event.fTracks[3].fPx"
```

```cpp
/// To fill a TTree with multiple input text files, proceed as indicated above
/// for the first input file and omit the second argument for subsequent calls

T.ReadFile("file1.dat","branch descriptor");
T.ReadFile("file2.dat");
```

```cpp
/// ## NOTE1
/// It may be more interesting to invoke directly the other Process function
/// accepting a TSelector* as argument.eg

MySelector *selector = (MySelector*)TSelector::GetSelector(filename);
selector->CallSomeFunction(..);
mytree.Process(selector,..);

/// ## NOTE2
/// One should not call this function twice with the same selector file
/// in the same script. If this is required, proceed as indicated in NOTE1,
/// by getting a pointer to the corresponding TSelector,eg

void stubs1() {
   TSelector *selector = TSelector::GetSelector("h1test.C");
   TFile *f1 = new TFile("stubs_nood_le1.root");
   TTree *h1 = (TTree*)f1->Get("h1");
   h1->Process(selector);
   TFile *f2 = new TFile("stubs_nood_le1_coarse.root");
    TTree *h2 = (TTree*)f2->Get("h1");
    h2->Process(selector);
}

/// or use ACLIC to compile the selector

void stubs2() {
    TFile *f1 = new TFile("stubs_nood_le1.root");
    TTree *h1 = (TTree*)f1->Get("h1");
    h1->Process("h1test.C+");
   TFile *f2 = new TFile("stubs_nood_le1_coarse.root");
   TTree *h2 = (TTree*)f2->Get("h1");
   h2->Process("h1test.C+");
}

```


```cpp
/// you can retrieve a pointer to the created object via:

TPrincipal *principal = (TPrincipal*)gROOT->GetListOfSpecials()->FindObject("principal");
```

```cpp
/// For example with Event.root, if

Double_t somePx = fTracks.fPx[2];

/// is executed by one of the method of the skeleton,
/// somePx will updated with the current value of fPx of the 3rd track.

/// Both macrofilename and the optional cutfilename are expected to be
/// the name of source files which contain at least a free standing
/// function with the signature:

x_t macrofilename(); // i.e function with the same name as the file

/// and

y_t cutfilename();   // i.e function with the same name as the file

/// x_t and y_t needs to be types that can convert respectively to a double
/// and a bool (because the skeleton uses:

if (cutfilename()) htemp->Fill(macrofilename());

/// These two functions are run in a context such that the branch names are
/// available as local variables of the correct (read-only) type.

/// Note that if you use the same 'variable' twice, it is more efficient
/// to 'cache' the value. For example:

Int_t n = fEventNumber; // Read fEventNumber
if (n<10 || n>10) { ... }

/// is more efficient than

if (fEventNumber<10 || fEventNumber>10)

/// Also, optionally, the generated selector will also call methods named
/// macrofilename_methodname in each of 6 main selector methods if the method
/// macrofilename_methodname exist (Where macrofilename is stripped of its
/// extension).

/// To draw px using the file hsimple.root (generated by the
/// hsimple.C tutorial), we need a file named hsimple.cxx:

double hsimple() {
   return px;
}

/// MakeProxy can then be used indirectly via the TTree::Draw interface
/// as follow:

new TFile("hsimple.root")
ntuple->Draw("hsimple.cxx");
```

```cpp
/// To use this function:
/// - Open your tree file (eg: TFile f("myfile.root");)
/// - T->MakeClass("MyClass");

/// where T is the name of the TTree in file myfile.root,
/// and MyClass.h, MyClass.C the name of the files created by this function.
/// In a ROOT session, you can do:

root > .L MyClass.C
root > MyClass* t = new MyClass;
root > t->GetEntry(12); // Fill data members of t with entry number 12.
root > t->Show();       // Show values of entry 12.
root > t->Show(16);     // Read and show values of entry 16.
root > t->Loop();       // Loop on all entries.

```

```cpp
/// To activate/deactivate one or more branches, use TBranch::SetBranchStatus
/// For example, if you have a Tree with several hundred branches, and you
/// are interested only by branches named "a" and "b", do

mytree.SetBranchStatus("*",0); //disable all branches
mytree.SetBranchStatus("a",1);
mytree.SetBranchStatus("b",1);

/// when calling mytree.GetEntry(i); only branches "a" and "b" will be read.

/// __WARNING!!__
/// If your Tree has been created in split mode with a parent branch "parent.",

mytree.SetBranchStatus("parent",1);

/// will not activate the sub-branches of "parent". You should do:

mytree.SetBranchStatus("parent*",1);

/// Without the trailing dot in the branch creation you have no choice but to
/// call SetBranchStatus explicitly for each of the sub branches.

/// An alternative is to call directly

brancha.GetEntry(i)
branchb.GetEntry(i);


/// Consider the example in $ROOTSYS/test/Event.h
/// The top level branch in the tree T is declared with:

Event *event = 0;  //event must be null or point to a valid object
                   //it must be initialized
T.SetBranchAddress("event",&event);

/// When reading the Tree, one can choose one of these 3 options:
///
/// ## OPTION 1

for (Long64_t i=0;i<nentries;i++) {
   T.GetEntry(i);
   // the object event has been filled at this point
}

/// The default (recommended). At the first entry an object of the class
/// Event will be created and pointed by event. At the following entries,
/// event will be overwritten by the new data. All internal members that are
/// TObject* are automatically deleted. It is important that these members
/// be in a valid state when GetEntry is called. Pointers must be correctly
/// initialized. However these internal members will not be deleted if the
/// characters "->" are specified as the first characters in the comment
/// field of the data member declaration.
///
/// If "->" is specified, the pointer member is read via pointer->Streamer(buf).
/// In this case, it is assumed that the pointer is never null (case of
/// pointer TClonesArray *fTracks in the Event example). If "->" is not
/// specified, the pointer member is read via buf >> pointer. In this case
/// the pointer may be null. Note that the option with "->" is faster to
/// read or write and it also consumes less space in the file.
///
/// ## OPTION 2
///
/// The option AutoDelete is set

TBranch *branch = T.GetBranch("event");
branch->SetAddress(&event);
branch->SetAutoDelete(kTRUE);
for (Long64_t i=0;i<nentries;i++) {
   T.GetEntry(i);
   // the object event has been filled at this point
}

/// In this case, at each iteration, the object event is deleted by GetEntry
/// and a new instance of Event is created and filled.

/// ## OPTION 3

/// Same as option 1, but you delete yourself the event.

for (Long64_t i=0;i<nentries;i++) {
   delete event;
   event = 0;  // EXTREMELY IMPORTANT
   T.GetEntry(i);
    // the object event has been filled at this point
}

/// It is strongly recommended to use the default option 1. It has the
/// additional advantage that functions like TTree::Draw (internally calling
/// TTree::GetEntry) will be functional even when the classes in the file are
/// not available.

/// Note: See the comments in TBranchElement::SetAddress() for the
/// object ownership policy of the underlying (user) data.
```


```cpp
TTree::TClusterIterator clusterIter = tree->GetClusterIterator(entry);
Long64_t clusterStart;
while( (clusterStart = clusterIter()) < tree->GetEntries() ) {
   printf("The cluster starts at %lld and ends at %lld (inclusive)\n",clusterStart,clusterIter.GetNextEntry()-1);
}
```

```cpp
tree.Fit(pol4,sqrt(x)>>hsqrt,y>0)

/// will fit sqrt(x) and save the histogram as "hsqrt" in the current
/// directory.

/// See also TTree::UnbinnedFit
```

## example



<!-- TTree.md ends here -->
