<!-- TNtuple.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  1 22:45:16 2016 (+0800)
;; Last-Updated: 三 9月 16 12:44:19 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TNtuple*

继承 TTree

A simple tree with branches of floats.

A simple TTree restricted to a list of float variables only.

Each variable goes to a separate branch.


## class

```cpp
   TNtuple();
   TNtuple(const char *name,const char *title, const char *varlist, Int_t bufsize=32000);
/// Create an Ntuple.
/// The parameter varlist describes the list of the ntuple variables
/// separated by a colon:
/// Example:  `x:y:z:energy`
/// For each variable in the list a separate branch is created.
/// NOTE:
///  - Use TTree to create branches with variables of different data types.
///  - Use TTree when the number of branches is large (> 100).

   virtual ~TNtuple();

   virtual void      Browse(TBrowser *b);/// Browse content of the ntuple
   virtual TTree    *CloneTree(Long64_t nentries = -1, Option_t* option = "");
/// Create a clone of this tree and copy nentries.
/// By default copy all entries.
/// Note that only active branches are copied.
/// The compression level of the cloned tree is set to the destination file's
/// compression level.
/// See TTree::CloneTree for more details.

   virtual Int_t     Fill(const Float_t *x);/// Fill a Ntuple with an array of floats
           Int_t     Fill(Int_t x0) { return Fill((Float_t)x0); }
           Int_t     Fill(Double_t x0) { return Fill((Float_t)x0); }
   virtual Int_t     Fill(Float_t x0, Float_t x1=0, Float_t x2=0, Float_t x3=0,
                          Float_t x4=0, Float_t x5=0, Float_t x6=0, Float_t x7=0,
                          Float_t x8=0, Float_t x9=0, Float_t x10=0,
                          Float_t x11=0, Float_t x12=0, Float_t x13=0,
                          Float_t x14=0);/// Fill a Ntuple: Each Ntuple item is an argument
   virtual Int_t     GetNvar() const { return fNvar; }
           Float_t  *GetArgs() const { return fArgs; }
   virtual Long64_t  ReadStream(std::istream& inputStream, const char *branchDescriptor="", char delimiter = ' ');
/// Read from filename as many columns as variables in the ntuple
/// the function returns the number of rows found in the file
/// The second argument "branchDescriptor" is currently not used.
/// Lines in the input file starting with "#" are ignored.

   virtual void      ResetBranchAddress(TBranch *);
/// Reset the branch addresses to the internal fArgs array. Use this
/// method when the addresses were changed via calls to SetBranchAddress().

           void      ResetBranchAddresses();
/// Reset the branch addresses to the internal fArgs array. Use this
/// method when the addresses were changed via calls to SetBranchAddress().
```

## code

```cpp
// A Ntuple is created via

TNtuple(name,title,varlist,bufsize)

// It is filled via:

TNtuple::Fill(*x)  or
TNtuple::Fill(v1,v2,v3.....)
```
	
## example




<!-- TNtuple.md ends here -->
