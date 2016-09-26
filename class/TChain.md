3<!-- TChain.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 一 9月 26 22:08:06 2016 (+0800)
;; Last-Updated: 一 9月 26 22:30:43 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.github.io -->

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
///
/// Argument name may have either of two formats. The first:
/// ~~~ {.cpp}
///     [//machine]/path/file_name.root[/tree_name]
/// ~~~
/// If tree_name is missing the chain name will be assumed.
/// Wildcard treatment is triggered by the any of the special characters []*?
/// which may be used in the file name, eg. specifying "xxx*.root" adds
/// all files starting with xxx in the current file system directory.
///
/// Alternatively name may have the format of a url, eg.
/// ~~~ {.cpp}
///         root://machine/path/file_name.root
///     or  root://machine/path/file_name.root/tree_name
///     or  root://machine/path/file_name.root/tree_name?query
/// ~~~
/// where "query" is to be interpreted by the remote server. Wildcards may be
/// supported in urls, depending on the protocol plugin and the remote server.
/// http or https urls can contain a query identifier without tree_name, but
/// generally urls can not be written with them because of ambiguity with the
/// wildcard character. (Also see the documentaiton for TChain::AddFile,
/// which does not support wildcards but allows the url to contain query)
///
/// NB. To add all the files of a TChain to a chain, use Add(TChain *chain).
///
/// A. if nentries <= 0, the file is connected and the tree header read
///    in memory to get the number of entries.
///
/// B. if (nentries > 0, the file is not connected, nentries is assumed to be
///    the number of entries in the file. In this case, no check is made that
///    the file exists and the Tree existing in the file. This second mode
///    is interesting in case the number of entries in the file is already stored
///    in a run data base for example.
///
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
///
/// D. The TChain data structure
///    Each TChainElement has a name equal to the tree name of this TChain
///    and a title equal to the file name. So, to loop over the
///    TFiles that have been added to this chain:
/// ~~~ {.cpp}
///        TObjArray *fileElements=chain->GetListOfFiles();
///        TIter next(fileElements);
///        TChainElement *chEl=0;
///        while (( chEl=(TChainElement*)next() )) {
///           TFile f(chEl->GetTitle());
///           ... do something with f ...
///        }
/// ~~~
/// Return value:
///
/// - If nentries>0 (including the default of TTree::kMaxEntries) and no
///   wildcarding is used, ALWAYS returns 1 without regard to whether
///   the file exists or contains the correct tree.
///
/// - If wildcarding is used, regardless of the value of nentries,
///   returns the number of files matching the name without regard to
///   whether they contain the correct tree.
///
/// - If nentries<=0 and wildcarding is not used, return 1 if the file
///  exists and contains the correct tree and 0 otherwise.

   virtual Int_t     AddFile(const char* name, Long64_t nentries = TTree::kMaxEntries, const char* tname = "");
/// Filename formats are similar to TChain::Add. Wildcards are not
/// applied. urls may also contain query and fragment identifiers
/// where the tree name can be specified in the url fragment.

   virtual Int_t     AddFileInfoList(TCollection* list, Long64_t nfiles = TTree::kMaxEntries);
   virtual TFriendElement *AddFriend(const char* chainname, const char* dummy = "");
   virtual TFriendElement *AddFriend(const char* chainname, TFile* dummy);
   virtual TFriendElement *AddFriend(TTree* chain, const char* alias = "", Bool_t warn = kFALSE);
   virtual void      Browse(TBrowser*);
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

   virtual void      CreatePackets();
   virtual void      DirectoryAutoAdd(TDirectory *);
   virtual Long64_t  Draw(const char* varexp, const TCut& selection, Option_t* option = "", Long64_t nentries = kMaxEntries, Long64_t firstentry = 0);
   virtual Long64_t  Draw(const char* varexp, const char* selection, Option_t* option = "", Long64_t nentries = kMaxEntries, Long64_t firstentry = 0); // *MENU*
   virtual void      Draw(Option_t* opt) { Draw(opt, "", "", kMaxEntries, 0); }
   virtual Int_t     Fill() { MayNotUse("Fill()"); return -1; }
   virtual TBranch  *FindBranch(const char* name);
   virtual TLeaf    *FindLeaf(const char* name);
   virtual TBranch  *GetBranch(const char* name);
   virtual Bool_t    GetBranchStatus(const char* branchname) const;
   virtual Long64_t  GetCacheSize() const { return fTree ? fTree->GetCacheSize() : fCacheSize; }
   virtual Long64_t  GetChainEntryNumber(Long64_t entry) const;
/// Return absolute entry number in the chain.
/// The input parameter entry is the entry number in
/// the current tree of this chain.

   virtual TClusterIterator GetClusterIterator(Long64_t firstentry);
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
   TFile            *GetFile() const;
   virtual TLeaf    *GetLeaf(const char* branchname, const char* leafname);
   virtual TLeaf    *GetLeaf(const char* name);
/// Return a pointer to the leaf name in the current tree.
   
   virtual TObjArray *GetListOfBranches();
   //                Warning, GetListOfFiles returns the list of TChainElements (not the list of files)
   //                see TChain::AddFile to see how to get the corresponding TFile objects
   TObjArray        *GetListOfFiles() const {return fFiles;}
   virtual TObjArray *GetListOfLeaves();
   virtual const char *GetAlias(const char *aliasName) const;
   virtual Double_t  GetMaximum(const char *columname);
   virtual Double_t  GetMinimum(const char *columname);
   virtual Int_t     GetNbranches();
   virtual Long64_t  GetReadEntry() const;
   TList            *GetStatus() const { return fStatus; }
   virtual TTree    *GetTree() const { return fTree; }
   virtual Int_t     GetTreeNumber() const { return fTreeNumber; }
           Long64_t *GetTreeOffset() const { return fTreeOffset; }
           Int_t     GetTreeOffsetLen() const { return fTreeOffsetLen; }
   virtual Double_t  GetWeight() const;
   virtual Int_t     LoadBaskets(Long64_t maxmemory);
   virtual Long64_t  LoadTree(Long64_t entry);
           void      Lookup(Bool_t force = kFALSE);
   virtual void      Loop(Option_t *option="", Long64_t nentries=kMaxEntries, Long64_t firstentry=0); // *MENU*
   virtual void      ls(Option_t *option="") const;
   virtual Long64_t  Merge(const char *name, Option_t *option = "");
   virtual Long64_t  Merge(TCollection *list, Option_t *option = "");
   virtual Long64_t  Merge(TCollection *list, TFileMergeInfo *info);
   virtual Long64_t  Merge(TFile *file, Int_t basketsize, Option_t *option="");
   virtual void      Print(Option_t *option="") const;
   virtual Long64_t  Process(const char *filename, Option_t *option="", Long64_t nentries=kMaxEntries, Long64_t firstentry=0); // *MENU*
   virtual Long64_t  Process(TSelector* selector, Option_t* option = "", Long64_t nentries = kMaxEntries, Long64_t firstentry = 0);
   virtual void      RecursiveRemove(TObject *obj);
   virtual void      RemoveFriend(TTree*);
   virtual void      Reset(Option_t *option="");
   virtual void      ResetAfterMerge(TFileMergeInfo *);
   virtual void      ResetBranchAddress(TBranch *);
   virtual void      ResetBranchAddresses();
   virtual Long64_t  Scan(const char *varexp="", const char *selection="", Option_t *option="", Long64_t nentries=kMaxEntries, Long64_t firstentry=0); // *MENU*
   virtual void      SetAutoDelete(Bool_t autodel=kTRUE);
   virtual Int_t     SetBranchAddress(const char *bname,void *add, TBranch **ptr = 0);
   virtual Int_t     SetBranchAddress(const char *bname,void *add, TBranch **ptr, TClass *realClass, EDataType datatype, Bool_t isptr);
   virtual Int_t     SetBranchAddress(const char *bname,void *add, TClass *realClass, EDataType datatype, Bool_t isptr);
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
   virtual Int_t     SetCacheSize(Long64_t cacheSize = -1);
   virtual void      SetDirectory(TDirectory *dir);
   virtual void      SetEntryList(TEntryList *elist, Option_t *opt="");
   virtual void      SetEntryListFile(const char *filename="", Option_t *opt="");
   virtual void      SetEventList(TEventList *evlist);
   virtual void      SetMakeClass(Int_t make) { TTree::SetMakeClass(make); if (fTree) fTree->SetMakeClass(make);}
   virtual void      SetPacketSize(Int_t size = 100);
   virtual void      SetProof(Bool_t on = kTRUE, Bool_t refresh = kFALSE, Bool_t gettreeheader = kFALSE);
   virtual void      SetWeight(Double_t w=1, Option_t *option="");
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


## example






<!-- TChain.md ends here -->
