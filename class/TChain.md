3<!-- TChain.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 一 9月 26 22:08:06 2016 (+0800)
;; Last-Updated: 二 11月  1 21:45:06 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 4
;; URL: http://wuhongyi.cn -->

# TChain

## class

继承 TTree

A chain is a collection of files containg TTree objects.
When the chain is created, the first parameter is the default name for the Tree to be processed later on.

Enter a new element in the chain via the TChain::Add function.
Once a chain is defined, one can use the normal TTree functions to Draw,Scan,etc.

Use TChain::SetBranchStatus to activate one or more branches for all the trees in the chain.



```cpp
public:
   // TChain constants
   enum {
      kGlobalWeight   = BIT(15),
      kAutoDelete     = BIT(16),
      kProofUptodate  = BIT(17),
      kProofLite      = BIT(18)
   };

   // This used to be 1234567890, if user code hardcoded this number, the user code will need to change.
   static constexpr auto kBigNumber = TTree::kMaxEntries;

public:
   TChain();
   TChain(const char* name, const char* title = "");
   virtual ~TChain();

   virtual Int_t     Add(TChain* chain);
/// Add all files referenced by the passed chain to this chain.
/// The function returns the total number of files connected.

   virtual Int_t     Add(const char* name, Long64_t nentries = TTree::kMaxEntries);
/// Add a new file to this chain.
/// If tree_name is missing the chain name will be assumed.
/// Wildcard treatment is triggered by the any of the special characters []*?
/// which may be used in the file name, eg. specifying "xxx*.root" adds
/// all files starting with xxx in the current file system directory.
/// where "query" is to be interpreted by the remote server. Wildcards may be
/// supported in urls, depending on the protocol plugin and the remote server.
/// http or https urls can contain a query identifier without tree_name, but
/// generally urls can not be written with them because of ambiguity with the
/// wildcard character. (Also see the documentaiton for TChain::AddFile,
/// which does not support wildcards but allows the url to contain query)
/// NB. To add all the files of a TChain to a chain, use Add(TChain *chain).
/// A. if nentries <= 0, the file is connected and the tree header read
///    in memory to get the number of entries.
/// B. if (nentries > 0, the file is not connected, nentries is assumed to be
///    the number of entries in the file. In this case, no check is made that
///    the file exists and the Tree existing in the file. This second mode
///    is interesting in case the number of entries in the file is already stored
///    in a run data base for example.
/// C. if (nentries == TTree::kMaxEntries) (default), the file is not connected.
///    the number of entries in each file will be read only when the file
///    will need to be connected to read an entry.
///    This option is the default and very efficient if one process
///    the chain sequentially. Note that in case TChain::GetEntry(entry)
///    is called and entry refers to an entry in the 3rd file, for example,
///    this forces the Tree headers in the first and second file
///    to be read to find the number of entries in these files.
///    Note that if one calls TChain::GetEntriesFast() after having created
///    a chain with this default, GetEntriesFast will return TTree::kMaxEntries!
///    TChain::GetEntries will force of the Tree headers in the chain to be
///    read to read the number of entries in each Tree.
/// D. The TChain data structure
///    Each TChainElement has a name equal to the tree name of this TChain
///    and a title equal to the file name.
/// Return value:
/// - If nentries>0 (including the default of TTree::kMaxEntries) and no
///   wildcarding is used, ALWAYS returns 1 without regard to whether
///   the file exists or contains the correct tree.
/// - If wildcarding is used, regardless of the value of nentries,
///   returns the number of files matching the name without regard to
///   whether they contain the correct tree.
/// - If nentries<=0 and wildcarding is not used, return 1 if the file
///  exists and contains the correct tree and 0 otherwise.

   virtual Int_t     AddFile(const char* name, Long64_t nentries = TTree::kMaxEntries, const char* tname = "");
/// Add a new file to this chain.
/// Filename formats are similar to TChain::Add. Wildcards are not
/// applied. urls may also contain query and fragment identifiers
/// where the tree name can be specified in the url fragment.
/// If tree_name is given as a part of the file name it is used to
/// as the name of the tree to load from the file. Otherwise if tname
/// argument is specified the chain will load the tree named tname from
/// the file, otherwise the original treename specified in the TChain
/// constructor will be used.
/// A. If nentries <= 0, the file is opened and the tree header read
///    into memory to get the number of entries.
/// B. If nentries > 0, the file is not opened, and nentries is assumed
///    to be the number of entries in the file. In this case, no check
///    is made that the file exists nor that the tree exists in the file.
///    This second mode is interesting in case the number of entries in
///    the file is already stored in a run database for example.
/// C. If nentries == TTree::kMaxEntries (default), the file is not opened.
///    The number of entries in each file will be read only when the file
///    is opened to read an entry.  This option is the default and very
///    efficient if one processes the chain sequentially.  Note that in
///    case GetEntry(entry) is called and entry refers to an entry in the
///    third file, for example, this forces the tree headers in the first
///    and second file to be read to find the number of entries in those
///    files.  Note that if one calls GetEntriesFast() after having created
///    a chain with this default, GetEntriesFast() will return TTree::kMaxEntries!
///    Using the GetEntries() function instead will force all of the tree
///    headers in the chain to be read to read the number of entries in
///    each tree.
/// D. The TChain data structure
///    Each TChainElement has a name equal to the tree name of this TChain
///    and a title equal to the file name. 
/// The function returns 1 if the file is successfully connected, 0 otherwise.

   virtual Int_t     AddFileInfoList(TCollection* list, Long64_t nfiles = TTree::kMaxEntries);
/// Add all files referenced in the list to the chain. The object type in the
/// list must be either TFileInfo or TObjString or TUrl .
/// The function return 1 if successful, 0 otherwise.

   virtual TFriendElement *AddFriend(const char* chainname, const char* dummy = "");
/// Add a TFriendElement to the list of friends of this chain.
/// A TChain has a list of friends similar to a tree (see TTree::AddFriend).
/// You can add a friend to a chain with the TChain::AddFriend method, and you
/// can retrieve the list of friends with TChain::GetListOfFriends.
/// The parameter is the name of friend chain (the name of a chain is always
/// the name of the tree from which it was created).
/// The original chain has access to all variable in its friends.
/// We can use the TChain::Draw method as if the values in the friends were
/// in the original chain.
/// If the variable name is enough to uniquely identify the variable, you can
/// leave out the chain and/or branch name.
/// When a TChain::Draw is executed, an automatic call to TTree::AddFriend
/// connects the trees in the chain. When a chain is deleted, its friend
/// elements are also deleted.
/// The number of entries in the friend must be equal or greater to the number
/// of entries of the original chain. If the friend has fewer entries a warning
/// is given and the resulting histogram will have missing entries.
/// For additional information see TTree::AddFriend.

   virtual TFriendElement *AddFriend(const char* chainname, TFile* dummy);
/// Add the whole chain or tree as a friend of this chain.

   virtual TFriendElement *AddFriend(TTree* chain, const char* alias = "", Bool_t warn = kFALSE);
/// Add the whole chain or tree as a friend of this chain.

   virtual void      Browse(TBrowser*);/// Browse the contents of the chain.
   virtual void      CanDeleteRefs(Bool_t flag = kTRUE);
/// When closing a file during the chain processing, the file
/// may be closed with option "R" if flag is set to kTRUE.
/// by default flag is kTRUE.
/// When closing a file with option "R", all TProcessIDs referenced by this
/// file are deleted.
/// Calling TFile::Close("R") might be necessary in case one reads a long list
/// of files having TRef, writing some of the referenced objects or TRef
/// to a new file. If the TRef or referenced objects of the file being closed
/// will not be referenced again, it is possible to minimize the size
/// of the TProcessID data structures in memory by forcing a delete of
/// the unused TProcessID.

   virtual void      CreatePackets();/// Initialize the packet descriptor string.
   virtual void      DirectoryAutoAdd(TDirectory *);/// Override the TTree::DirectoryAutoAdd behavior: we never auto add.
   virtual Long64_t  Draw(const char* varexp, const TCut& selection, Option_t* option = "", Long64_t nentries = kMaxEntries, Long64_t firstentry = 0);
/// Draw expression varexp for selected entries.
/// Returns -1 in case of error or number of selected events in case of success.
/// This function accepts TCut objects as arguments.
/// Useful to use the string operator +, example:
///    ntuple.Draw("x",cut1+cut2+cut3);

   virtual Long64_t  Draw(const char* varexp, const char* selection, Option_t* option = "", Long64_t nentries = kMaxEntries, Long64_t firstentry = 0); // *MENU*
/// Process all entries in this chain and draw histogram corresponding to
/// expression varexp.
/// Returns -1 in case of error or number of selected events in case of success.

   virtual void      Draw(Option_t* opt) { Draw(opt, "", "", kMaxEntries, 0); }
   virtual Int_t     Fill() { MayNotUse("Fill()"); return -1; }
   virtual TBranch  *FindBranch(const char* name);/// See TTree::GetReadEntry().
   virtual TLeaf    *FindLeaf(const char* name);/// See TTree::GetReadEntry().
   virtual TBranch  *GetBranch(const char* name);/// Return pointer to the branch name in the current tree.
   virtual Bool_t    GetBranchStatus(const char* branchname) const;/// See TTree::GetReadEntry().
   virtual Long64_t  GetCacheSize() const { return fTree ? fTree->GetCacheSize() : fCacheSize; }
   virtual Long64_t  GetChainEntryNumber(Long64_t entry) const;
/// Return absolute entry number in the chain.
/// The input parameter entry is the entry number in
/// the current tree of this chain.

   virtual TClusterIterator GetClusterIterator(Long64_t firstentry);
/// Return an iterator over the cluster of baskets starting at firstentry.
/// This iterator is not yet supported for TChain object.

           Int_t     GetNtrees() const { return fNtrees; }
   virtual Long64_t  GetEntries() const;
/// Return the total number of entries in the chain.
/// In case the number of entries in each tree is not yet known,
/// the offset table is computed.

   virtual Long64_t  GetEntries(const char *sel) { return TTree::GetEntries(sel); }
   virtual Int_t     GetEntry(Long64_t entry=0, Int_t getall=0);
/// Get entry from the file to memory.
/// - getall = 0 : get only active branches
/// - getall = 1 : get all branches
/// Return the total number of bytes read,
/// 0 bytes read indicates a failure.

   virtual Long64_t  GetEntryNumber(Long64_t entry) const;
/// Return entry number corresponding to entry.
/// if no TEntryList set returns entry
/// else returns entry #entry from this entry list and
/// also computes the global entry number (loads all tree headers)

   virtual Int_t     GetEntryWithIndex(Int_t major, Int_t minor=0);
/// Return entry corresponding to major and minor number.
/// The function returns the total number of bytes read.
/// If the Tree has friend trees, the corresponding entry with
/// the index values (major,minor) is read. Note that the master Tree
/// and its friend may have different entry serial numbers corresponding
/// to (major,minor).

   TFile            *GetFile() const;
/// Return a pointer to the current file.
/// If no file is connected, the first file is automatically loaded.

   virtual TLeaf    *GetLeaf(const char* branchname, const char* leafname);/// Return a pointer to the leaf name in the current tree.
   virtual TLeaf    *GetLeaf(const char* name);
/// Return a pointer to the leaf name in the current tree.
   
   virtual TObjArray *GetListOfBranches();
   //                Warning, GetListOfFiles returns the list of TChainElements (not the list of files)
/// Return a pointer to the list of branches of the current tree.
/// Warning: If there is no current TTree yet, this routine will open the
/// first in the chain.
/// Returns 0 on failure.

   //                see TChain::AddFile to see how to get the corresponding TFile objects
   TObjArray        *GetListOfFiles() const {return fFiles;}
   virtual TObjArray *GetListOfLeaves();
   virtual const char *GetAlias(const char *aliasName) const;/// Returns the expanded value of the alias.  Search in the friends if any.
   virtual Double_t  GetMaximum(const char *columname);/// Return maximum of column with name columname.
   virtual Double_t  GetMinimum(const char *columname);/// Return minimum of column with name columname.
   virtual Int_t     GetNbranches();/// Return the number of branches of the current tree. Warning: May set the current tree!
   virtual Long64_t  GetReadEntry() const;/// See TTree::GetReadEntry().
   TList            *GetStatus() const { return fStatus; }
   virtual TTree    *GetTree() const { return fTree; }
   virtual Int_t     GetTreeNumber() const { return fTreeNumber; }
           Long64_t *GetTreeOffset() const { return fTreeOffset; }
           Int_t     GetTreeOffsetLen() const { return fTreeOffsetLen; }
   virtual Double_t  GetWeight() const;
/// Return the chain weight.
/// By default the weight is the weight of the current tree.
/// However, if the weight has been set in TChain::SetWeight()
/// with the option "global", then that weight will be returned.
/// Warning: May set the current tree!

   virtual Int_t     LoadBaskets(Long64_t maxmemory);
/// Dummy function.
/// It could be implemented and load all baskets of all trees in the chain.
/// For the time being use TChain::Merge and TTree::LoadBasket
/// on the resulting tree.

   virtual Long64_t  LoadTree(Long64_t entry);
/// Find the tree which contains entry, and set it as the current tree.
/// Returns the entry number in that tree.
/// The input argument entry is the entry serial number in the whole chain.
/// In case of error, LoadTree returns a negative number:
///   1. The chain is empty.
///   2. The requested entry number of less than zero or too large for the chain.
///       or too large for the large TTree.
///   3. The file corresponding to the entry could not be correctly open
///   4. The TChainElement corresponding to the entry is missing or
///       the TTree is missing from the file.
/// Note: This is the only routine which sets the value of fTree to
///       a non-zero pointer.

           void      Lookup(Bool_t force = kFALSE);
/// Check / locate the files in the chain.
/// By default only the files not yet looked up are checked.
/// Use force = kTRUE to check / re-check every file.

   virtual void      Loop(Option_t *option="", Long64_t nentries=kMaxEntries, Long64_t firstentry=0); // *MENU* /// Loop on nentries of this chain starting at firstentry.  (NOT IMPLEMENTED)
   virtual void      ls(Option_t *option="") const;/// List the chain.
   virtual Long64_t  Merge(const char *name, Option_t *option = "");
/// Merge all the entries in the chain into a new tree in a new file.
/// See important note in the following function Merge().
/// If the chain is expecting the input tree inside a directory,
/// this directory is NOT created by this routine.

   virtual Long64_t  Merge(TCollection *list, Option_t *option = "");/// Merge all chains in the collection.  (NOT IMPLEMENTED)
   virtual Long64_t  Merge(TCollection *list, TFileMergeInfo *info);/// Merge all chains in the collection.  (NOT IMPLEMENTED)
   virtual Long64_t  Merge(TFile *file, Int_t basketsize, Option_t *option="");
/// Merge all the entries in the chain into a new tree in the current file.
/// Note: The "file" parameter is *not* the file where the new
///       tree will be inserted.  The new tree is inserted into
///       gDirectory, which is usually the most recently opened
///       file, or the directory most recently cd()'d to.
/// If option = "C" is given, the compression level for all branches
/// in the new Tree is set to the file compression level.  By default,
/// the compression level of all branches is the original compression
/// level in the old trees.
/// If basketsize > 1000, the basket size for all branches of the
/// new tree will be set to basketsize.
/// If 'option' contains the word 'fast' the merge will be done without
/// unzipping or unstreaming the baskets (i.e., a direct copy of the raw
/// bytes on disk).
/// When 'fast' is specified, 'option' can also contains a
/// sorting order for the baskets in the output file.
/// There is currently 3 supported sorting order:
///     SortBasketsByOffset (the default)
///     SortBasketsByBranch
///     SortBasketsByEntry
/// When using SortBasketsByOffset the baskets are written in
/// the output file in the same order as in the original file
/// (i.e. the basket are sorted on their offset in the original
/// file; Usually this also means that the baskets are sorted
/// on the index/number of the _last_ entry they contain)
/// When using SortBasketsByBranch all the baskets of each
/// individual branches are stored contiguously.  This tends to
/// optimize reading speed when reading a small number (1->5) of
/// branches, since all their baskets will be clustered together
/// instead of being spread across the file.  However it might
/// decrease the performance when reading more branches (or the full
/// entry).
/// When using SortBasketsByEntry the baskets with the lowest
/// starting entry are written first.  (i.e. the baskets are
/// sorted on the index/number of the first entry they contain).
/// This means that on the file the baskets will be in the order
/// in which they will be needed when reading the whole tree
/// sequentially.
/// ## IMPORTANT Note 1: AUTOMATIC FILE OVERFLOW
/// When merging many files, it may happen that the resulting file
/// reaches a size > TTree::fgMaxTreeSize (default = 1.9 GBytes).
/// In this case the current file is automatically closed and a new
/// file started.  If the name of the merged file was "merged.root",
/// the subsequent files will be named "merged_1.root", "merged_2.root",
/// etc.  fgMaxTreeSize may be modified via the static function
/// TTree::SetMaxTreeSize.
/// When in fast mode, the check and switch is only done in between each
/// input file.
/// ## IMPORTANT Note 2: The output file is automatically closed and deleted.
/// This is required because in general the automatic file overflow described
/// above may happen during the merge.
/// If only the current file is produced (the file passed as first argument),
/// one can instruct Merge to not close and delete the file by specifying
/// the option "keep".

   virtual void      Print(Option_t *option="") const;
/// Print the header information of each tree in the chain.
/// See TTree::Print for a list of options.

   virtual Long64_t  Process(const char *filename, Option_t *option="", Long64_t nentries=kMaxEntries, Long64_t firstentry=0); // *MENU*
/// Process all entries in this chain, calling functions in filename.
/// The return value is -1 in case of error and TSelector::GetStatus() in
/// in case of success.
/// See TTree::Process.

   virtual Long64_t  Process(TSelector* selector, Option_t* option = "", Long64_t nentries = kMaxEntries, Long64_t firstentry = 0);
/// Process this chain executing the code in selector.
/// The return value is -1 in case of error and TSelector::GetStatus() in
/// in case of success.

   virtual void      RecursiveRemove(TObject *obj);/// Make sure that obj (which is being deleted or will soon be) is no longer referenced by this TTree.
   virtual void      RemoveFriend(TTree*);/// Remove a friend from the list of friends.
   virtual void      Reset(Option_t *option="");/// Resets the state of this chain.
   virtual void      ResetAfterMerge(TFileMergeInfo *);/// Resets the state of this chain after a merge (keep the customization but forget the data).
   virtual void      ResetBranchAddress(TBranch *);/// Reset the addresses of the branch.
   virtual void      ResetBranchAddresses();/// Reset the addresses of the branches.
   virtual Long64_t  Scan(const char *varexp="", const char *selection="", Option_t *option="", Long64_t nentries=kMaxEntries, Long64_t firstentry=0); // *MENU*
/// Loop on tree and print entries passing selection.
/// - If varexp is 0 (or "") then print only first 8 columns.
/// - If varexp = "*" print all columns.
/// - Otherwise a columns selection can be made using "var1:var2:var3".
/// See TTreePlayer::Scan for more information.

   virtual void      SetAutoDelete(Bool_t autodel=kTRUE);
/// Set the global branch kAutoDelete bit.
/// When LoadTree loads a new Tree, the branches for which
/// the address is set will have the option AutoDelete set
/// For more details on AutoDelete, see TBranch::SetAutoDelete.

   virtual Int_t     SetBranchAddress(const char *bname,void *add, TBranch **ptr = 0);
/// Set branch address.
/// \param[in] bname    is the name of a branch.
/// \param[in] add      is the address of the branch.
/// Note: See the comments in TBranchElement::SetAddress() for a more
/// detailed discussion of the meaning of the add parameter.
/// IMPORTANT REMARK:
/// In case TChain::SetBranchStatus is called, it must be called
/// BEFORE calling this function.
/// See TTree::CheckBranchAddressType for the semantic of the return value.

   virtual Int_t     SetBranchAddress(const char *bname,void *add, TBranch **ptr, TClass *realClass, EDataType datatype, Bool_t isptr);
/// Check if bname is already in the status list, and if not, create a TChainElement object and set its address.
/// See TTree::CheckBranchAddressType for the semantic of the return value.
/// Note: See the comments in TBranchElement::SetAddress() for a more
/// detailed discussion of the meaning of the add parameter.

   virtual Int_t     SetBranchAddress(const char *bname,void *add, TClass *realClass, EDataType datatype, Bool_t isptr);
/// Check if bname is already in the status list, and if not, create a TChainElement object and set its address.
/// See TTree::CheckBranchAddressType for the semantic of the return value.
/// Note: See the comments in TBranchElement::SetAddress() for a more
/// detailed discussion of the meaning of the add parameter.

   template <class T> Int_t SetBranchAddress(const char *bname, T **add, TBranch **ptr = 0) {
     return TTree::SetBranchAddress<T>(bname, add, ptr);
   }
#ifndef R__NO_CLASS_TEMPLATE_SPECIALIZATION
   // This can only be used when the template overload resolution can distringuish between
   // T* and T**
   template <class T> Int_t SetBranchAddress(const char *bname, T *add, TBranch **ptr = 0) {
     return TTree::SetBranchAddress<T>(bname, add, ptr);
   }
#endif

   virtual void      SetBranchStatus(const char *bname, Bool_t status=1, UInt_t *found=0);
/// Set branch status to Process or DoNotProcess
/// \param[in] bname     is the name of a branch. if bname="*", apply to all branches.
/// \param[in] status    = 1  branch will be processed,
///                      = 0  branch will not be processed
///  See IMPORTANT REMARKS in TTree::SetBranchStatus and TChain::SetBranchAddress
///  If found is not 0, the number of branch(es) found matching the regular
///  expression is returned in *found AND the error message 'unknown branch'
///  is suppressed.

   virtual Int_t     SetCacheSize(Long64_t cacheSize = -1);
   virtual void      SetDirectory(TDirectory *dir);
/// Remove reference to this chain from current directory and add
/// reference to new directory dir. dir can be 0 in which case the chain
/// does not belong to any directory.

   virtual void      SetEntryList(TEntryList *elist, Option_t *opt="");
/// Set the input entry list (processing the entries of the chain will then be
/// limited to the entries in the list)
/// This function finds correspondance between the sub-lists of the TEntryList
/// and the trees of the TChain
/// By default (opt=""), both the file names of the chain elements and
/// the file names of the TEntryList sublists are expanded to full path name.
/// If opt = "ne", the file names are taken as they are and not expanded

   virtual void      SetEntryListFile(const char *filename="", Option_t *opt="");
/// Set the input entry list (processing the entries of the chain will then be
/// limited to the entries in the list). This function creates a special kind
/// of entry list (TEntryListFromFile object) that loads lists, corresponding
/// to the chain elements, one by one, so that only one list is in memory at a time.
/// If there is an error opening one of the files, this file is skipped and the next file is loaded
/// File naming convention:
/// - by default, filename_elist.root is used, where filename is the
///   name of the chain element
/// - xxx$xxx.root - $ sign is replaced by the name of the chain element
/// If the list name is not specified (by passing filename_elist.root/listname to
/// the TChain::SetEntryList() function, the first object of class TEntryList
/// in the file is taken.
/// It is assumed, that there are as many list files, as there are elements in
/// the chain and they are in the same order

   virtual void      SetEventList(TEventList *evlist);
/// This function transfroms the given TEventList into a TEntryList
/// NOTE, that this function loads all tree headers, because the entry numbers
/// in the TEventList are global and have to be recomputed, taking into account
/// the number of entries in each tree.
/// The new TEntryList is owned by the TChain and gets deleted when the chain
/// is deleted. This TEntryList is returned by GetEntryList() function, and after
/// GetEntryList() function is called, the TEntryList is not owned by the chain
/// any more and will not be deleted with it.

   virtual void      SetMakeClass(Int_t make) { TTree::SetMakeClass(make); if (fTree) fTree->SetMakeClass(make);}
   virtual void      SetPacketSize(Int_t size = 100);/// Set number of entries per packet for parallel root.
   virtual void      SetProof(Bool_t on = kTRUE, Bool_t refresh = kFALSE, Bool_t gettreeheader = kFALSE);
/// Enable/Disable PROOF processing on the current default Proof (gProof).
/// "Draw" and "Processed" commands will be handled by PROOF.
/// The refresh and gettreeheader are meaningfull only if on == kTRUE.
/// If refresh is kTRUE the underlying fProofChain (chain proxy) is always
/// rebuilt (even if already existing).
/// If gettreeheader is kTRUE the header of the tree will be read from the
/// PROOF cluster: this is only needed for browsing and should be used with
/// care because it may take a long time to execute.

   virtual void      SetWeight(Double_t w=1, Option_t *option="");
/// Set chain weight.
/// The weight is used by TTree::Draw to automatically weight each
/// selected entry in the resulting histogram.
/// For example the equivalent of
/// ~~~ {.cpp}
///     chain.Draw("x","w")
/// ~~~
/// is
/// ~~~ {.cpp}
///     chain.SetWeight(w,"global");
///     chain.Draw("x");
/// ~~~
/// By default the weight used will be the weight
/// of each Tree in the TChain. However, one can force the individual
/// weights to be ignored by specifying the option "global".
/// In this case, the TChain global weight will be used for all Trees.

   virtual void      UseCache(Int_t maxCacheSize = 10, Int_t pageSize = 0);
```


## code

```cpp
///  Suppose we have 3 files f1.root, f2.root and f3.root. Each file contains a TTree object named "T".
TChain ch("T");  creates a chain to process a Tree called "T"
ch.Add("f1.root");
ch.Add("f2.root");
ch.Add("f3.root");
ch.Draw("x");
```

```cpp
/// Each TChainElement has a name equal to the tree name of this TChain and a title equal to the file name. So, to loop over the TFiles that have been added to this chain:

TObjArray *fileElements=chain->GetListOfFiles();
TIter next(fileElements);
TChainElement *chEl=0;
while (( chEl=(TChainElement*)next() )) {
   TFile f(chEl->GetTitle());
//   ... do something with f ...
}
```

```cpp
/// Example using the file generated in $ROOTSYS/test/Event
/// merge two copies of Event.root

gSystem.Load("libEvent");
TChain ch("T");
ch.Add("Event1.root");
ch.Add("Event2.root");
ch.Merge("all.root");
```

```cpp
/// If the chain is expecting the input tree inside a directory,
/// this directory is NOT created by this routine.
///
/// So if you do:

TChain ch("mydir/mytree");
ch.Merge("newfile.root");

/// The resulting file will not have subdirectories.  In order to
/// preserve the directory structure do the following instead:

TFile* file = TFile::Open("newfile.root", "RECREATE");
file->mkdir("mydir")->cd();
ch.Merge(file);

/// The function returns the total number of files produced.
/// To check that all files have been merged use something like:

if (newchain->GetEntries()!=oldchain->GetEntries()) {
   ... not all the file have been copied ...
}
```

```cpp
/// This example has four chains each has 20 ROOT trees from 20 ROOT files.

TChain ch("t"); // a chain with 20 trees from 20 files
TChain ch1("t1");
TChain ch2("t2");
TChain ch3("t3");

/// Now we can add the friends to the first chain.

ch.AddFriend("t1")
ch.AddFriend("t2")
ch.AddFriend("t3")

/// For example, this generates a 3-d scatter plot of variable "var" in the
/// TChain ch versus variable v1 in TChain t1 versus variable v2 in TChain t2.

ch.Draw("var:t1.v1:t2.v2");
```



## example






<!-- TChain.md ends here -->
