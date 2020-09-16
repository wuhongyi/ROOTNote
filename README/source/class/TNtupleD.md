<!-- TNtupleD.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  1 22:55:16 2016 (+0800)
;; Last-Updated: 三 9月 16 12:44:25 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 3
;; URL: http://wuhongyi.cn -->

# TNtupleD*

继承 TTree

A simple tree with branches of doubles.

## class

```cpp
   TNtupleD();
   TNtupleD(const char *name,const char *title, const char *varlist, Int_t bufsize=32000);
/// Create an Ntuple.
/// The parameter varlist describes the list of the ntuple variables
/// separated by a colon:
/// Example:  `x:y:z:energy`
/// For each variable in the list a separate branch is created.
/// NOTE:
///  - Use TTree to create branches with variables of different data types.
///  - Use TTree when the number of branches is large (> 100).

   virtual ~TNtupleD();

   virtual void      Browse(TBrowser *b);/// Browse content.
   virtual Int_t     Fill(const Double_t *x);/// Fill a Ntuple with an array of floats.
   virtual Int_t     Fill(Double_t x0, Double_t x1, Double_t x2=0, Double_t x3=0,
                          Double_t x4=0, Double_t x5=0, Double_t x6=0, Double_t x7=0,
                          Double_t x8=0, Double_t x9=0, Double_t x10=0,
                          Double_t x11=0, Double_t x12=0, Double_t x13=0,
                          Double_t x14=0);/// Fill a Ntuple: Each Ntuple item is an argument.
   virtual Int_t     GetNvar() const { return fNvar; }
           Double_t *GetArgs() const { return fArgs; }
   virtual Long64_t  ReadStream(std::istream& inputstream, const char *branchDescriptor="", char delimiter = ' ');
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



## example



<!-- TNtupleD.md ends here -->
