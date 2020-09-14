<!-- TTreePlayer.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 一 11月 28 09:10:00 2016 (+0800)
;; Last-Updated: 一 6月  4 03:03:27 2018 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TTreePlayer

A TTree object is a list of TBranch.                                 
  To Create a TTree object one must:                                 
   - Create the TTree header via the TTree constructor               
   - Call the TBranch constructor for every branch.                  
                                                                     
  To Fill this object, use member function Fill with no parameters.  
    The Fill function loops on all defined TBranch.

Implement some of the functionality of the class TTree requiring access to
extra libraries (Histogram, display, etc).

TTreePlayer 继承 TVirtualTreePlayer

## class

```cpp
   TTreePlayer();/// Default Tree constructor.
   virtual ~TTreePlayer();/// Tree destructor.
   virtual TVirtualIndex *BuildIndex(const TTree *T, const char *majorname, const char *minorname);
/// Build the index for the tree (see TTree::BuildIndex)

   virtual TTree    *CopyTree(const char *selection, Option_t *option
                              ,Long64_t nentries, Long64_t firstentry);
/// Copy a Tree with selection, make a clone of this Tree header, then copy the
/// selected entries.
/// -  selection is a standard selection expression (see TTreePlayer::Draw)
/// -  option is reserved for possible future use
/// -  nentries is the number of entries to process (default is all)
/// -  first is the first entry to process (default is 0)
/// IMPORTANT: The copied tree stays connected with this tree until this tree
/// is deleted.  In particular, any changes in branch addresses
/// in this tree are forwarded to the clone trees.  Any changes
/// made to the branch addresses of the copied trees are over-ridden
/// anytime this tree changes its branch addresses.
/// Once this tree is deleted, all the addresses of the copied tree
/// are reset to their default values.

   virtual Long64_t  DrawScript(const char* wrapperPrefix,
                                const char *macrofilename, const char *cutfilename,
                                Option_t *option, Long64_t nentries, Long64_t firstentry);
/// Draw the result of a C++ script.
/// The macrofilename and optionally cutfilename are assumed to contain
/// at least a method with the same name as the file.  The method
/// should return a value that can be automatically cast to
/// respectively a double and a boolean.
/// Both methods will be executed in a context such that the
/// branch names can be used as C++ variables. This is
/// accomplished by generating a TTreeProxy (see MakeProxy)
/// and including the files in the proper location.
/// If the branch name can not be used a proper C++ symbol name,
/// it will be modified as follow:
///    - white spaces are removed
///    - if the leading character is not a letter, an underscore is inserted
///    - < and > are replace by underscores
///    - * is replaced by st
///    - & is replaced by rf
/// If a cutfilename is specified, for each entry, we execute
/// ~~~{.cpp}
///   if (cutfilename()) htemp->Fill(macrofilename());
/// ~~~
/// If no cutfilename is specified, for each entry we execute
/// ~~~{.cpp}
///   htemp(macrofilename());
/// ~~~
/// The default for the histogram are the same as for
/// TTreePlayer::DrawSelect

   virtual Long64_t  DrawSelect(const char *varexp, const char *selection, Option_t *option
                                ,Long64_t nentries, Long64_t firstentry);
/// Draw expression varexp for specified entries that matches the selection.
/// Returns -1 in case of error or number of selected events in case of succss.
/// See the documentation of TTree::Draw for the complete details.

   virtual Int_t     Fit(const char *formula ,const char *varexp, const char *selection,Option_t *option ,
                         Option_t *goption ,Long64_t nentries, Long64_t firstentry);
/// Fit  a projected item(s) from a Tree.
/// Returns -1 in case of error or number of selected events in case of success.
///  The formula is a TF1 expression.
///  See TTree::Draw for explanations of the other parameters.
///  By default the temporary histogram created is called htemp.
///  If varexp contains >>hnew , the new histogram created is called hnew
///  and it is kept in the current directory.
/// The function returns the status of the histogram fit (see TH1::Fit)
/// If no entries were selected, the function returns -1;
///   (i.e. fitResult is null if the fit is OK)

   virtual Int_t     GetDimension() const {return fDimension;}
   TH1              *GetHistogram() const {return fHistogram;}
   virtual Long64_t  GetEntries(const char *selection);
/// Return the number of entries matching the selection.
/// Return -1 in case of errors.
/// If the selection uses any arrays or containers, we return the number
/// of entries where at least one element match the selection.
/// GetEntries is implemented using the selector class TSelectorEntries,
/// which can be used directly (see code in TTreePlayer::GetEntries) for
/// additional option.
/// If SetEventList was used on the TTree or TChain, only that subset
/// of entries will be considered.

   virtual Long64_t  GetEntriesToProcess(Long64_t firstentry, Long64_t nentries) const;
/// return the number of entries to be processed
/// this function checks that nentries is not bigger than the number
/// of entries in the Tree or in the associated TEventlist

   virtual Int_t     GetNfill() const {return fSelector->GetNfill();}
   const char       *GetScanFileName() const {return fScanFileName;}
   TTreeFormula     *GetSelect() const    {return fSelector->GetSelect();}
   virtual Long64_t  GetSelectedRows() const {return fSelectedRows;}
   TSelector        *GetSelector() const {return fSelector;}
   TSelector        *GetSelectorFromFile() const {return fSelectorFromFile;}
   // See TSelectorDraw::GetVar
   TTreeFormula     *GetVar(Int_t i) const {return fSelector->GetVar(i);};
   // See TSelectorDraw::GetVar
   TTreeFormula     *GetVar1() const {return fSelector->GetVar1();}
   // See TSelectorDraw::GetVar
   TTreeFormula     *GetVar2() const {return fSelector->GetVar2();}
   // See TSelectorDraw::GetVar
   TTreeFormula     *GetVar3() const {return fSelector->GetVar3();}
   // See TSelectorDraw::GetVar
   TTreeFormula     *GetVar4() const {return fSelector->GetVar4();}
   // See TSelectorDraw::GetVal
   virtual Double_t *GetVal(Int_t i) const {return fSelector->GetVal(i);};
   // See TSelectorDraw::GetVal
   virtual Double_t *GetV1() const   {return fSelector->GetV1();}
   // See TSelectorDraw::GetVal
   virtual Double_t *GetV2() const   {return fSelector->GetV2();}
   // See TSelectorDraw::GetVal
   virtual Double_t *GetV3() const   {return fSelector->GetV3();}
   // See TSelectorDraw::GetVal
   virtual Double_t *GetV4() const   {return fSelector->GetV4();}
   virtual Double_t *GetW() const    {return fSelector->GetW();}
   virtual Int_t     MakeClass(const char *classname, Option_t *option);
/// Generate skeleton analysis class for this Tree.
/// The following files are produced: classname.h and classname.C
/// If classname is 0, classname will be called "nameoftree.
/// The generated code in classname.h includes the following:
///    - Identification of the original Tree and Input file name
///    - Definition of analysis class (data and functions)
///    - the following class functions:
///       - constructor (connecting by default the Tree file)
///       - GetEntry(Long64_t entry)
///       - Init(TTree *tree) to initialize a new TTree
///       - Show(Long64_t entry) to read and Dump entry
/// The generated code in classname.C includes only the main
/// analysis function Loop.
/// To use this function:
///    - connect your Tree file (eg: TFile f("myfile.root");)
///    - T->MakeClass("MyClass");
/// where T is the name of the Tree in file myfile.root
/// and MyClass.h, MyClass.C the name of the files created by this function.
/// In a ROOT session, you can do:
///    root> .L MyClass.C
///    root> MyClass t
///    root> t.GetEntry(12); // Fill t data members with entry number 12
///    root> t.Show();       // Show values of entry 12
///    root> t.Show(16);     // Read and show values of entry 16
///    root> t.Loop();       // Loop on all entries
///  NOTE: Do not use the code generated for one Tree in case of a TChain.
///        Maximum dimensions calculated on the basis of one TTree only
///        might be too small when processing all the TTrees in one TChain.
///        Instead of myTree.MakeClass(..,  use myChain.MakeClass(..

   virtual Int_t     MakeCode(const char *filename);
/// Generate skeleton function for this Tree
/// The function code is written on filename.
/// If filename is 0, filename will be called nameoftree.C
/// The generated code includes the following:
///    - Identification of the original Tree and Input file name
///    - Connection of the Tree file
///    - Declaration of Tree variables
///    - Setting of branches addresses
///    - A skeleton for the entry loop
/// To use this function:
///    - connect your Tree file (eg: TFile f("myfile.root");)
///    - T->MakeCode("anal.C");
/// where T is the name of the Tree in file myfile.root
/// and anal.C the name of the file created by this function.
/// NOTE: Since the implementation of this function, a new and better
///       function TTree::MakeClass() has been developed.

   virtual Int_t     MakeProxy(const char *classname,
                               const char *macrofilename = 0, const char *cutfilename = 0,
                               const char *option = 0, Int_t maxUnrolling = 3);
/// Generate a skeleton analysis class for this Tree using TBranchProxy.
/// TBranchProxy is the base of a class hierarchy implementing an
/// indirect access to the content of the branches of a TTree.
/// "proxyClassname" is expected to be of the form:
///    [path/]fileprefix
/// The skeleton will then be generated in the file:
///    fileprefix.h
/// located in the current directory or in 'path/' if it is specified.
/// The class generated will be named 'fileprefix'.
/// If the fileprefix contains a period, the right side of the period
/// will be used as the extension (instead of 'h') and the left side
/// will be used as the classname.
/// "macrofilename" and optionally "cutfilename" are expected to point
/// to source file which will be included in by the generated skeletong.
/// Method of the same name as the file(minus the extension and path)
/// will be called by the generated skeleton's Process method as follow:
///    [if (cutfilename())] htemp->Fill(macrofilename());
/// "option" can be used select some of the optional features during
/// the code generation.  The possible options are:
/// -  nohist : indicates that the generated ProcessFill should not
///             fill the histogram.
/// 'maxUnrolling' controls how deep in the class hierarchy does the
/// system 'unroll' class that are not split.  'unrolling' a class
/// will allow direct access to its data members a class (this
/// emulates the behavior of TTreeFormula).
/// The main features of this skeleton are:
/// *  on-demand loading of branches
/// *  ability to use the 'branchname' as if it was a data member
/// *  protection against array out-of-bound
/// *  ability to use the branch data as object (when the user code is available)
/// For example with Event.root, if
///    Double_t somepx = fTracks.fPx[2];
/// is executed by one of the method of the skeleton,
/// somepx will be updated with the current value of fPx of the 3rd track.
/// Both macrofilename and the optional cutfilename are expected to be
/// the name of source files which contain at least a free standing
/// function with the signature:
/// ~~~{.cpp}
///     x_t macrofilename(); // i.e function with the same name as the file
/// ~~~
/// and
/// ~~~{.cpp}
///     y_t cutfilename();   // i.e function with the same name as the file
/// ~~~
/// x_t and y_t needs to be types that can convert respectively to a double
/// and a bool (because the skeleton uses:
/// ~~~{.cpp}
///     if (cutfilename()) htemp->Fill(macrofilename());
/// ~~~
/// This 2 functions are run in a context such that the branch names are
/// available as local variables of the correct (read-only) type.
///
/// Note that if you use the same 'variable' twice, it is more efficient
/// to 'cache' the value. For example
/// ~~~{.cpp}
///   Int_t n = fEventNumber; // Read fEventNumber
///   if (n<10 || n>10) { ... }
/// ~~~
/// is more efficient than
/// ~~~{.cpp}
///   if (fEventNumber<10 || fEventNumber>10)
/// ~~~
/// Access to TClonesArray.
/// If a branch (or member) is a TClonesArray (let's say fTracks), you
/// can access the TClonesArray itself by using ->:
/// ~~~{.cpp}
///    fTracks->GetLast();
/// ~~~
/// However this will load the full TClonesArray object and its content.
/// To quickly read the size of the TClonesArray use (note the dot):
/// ~~~{.cpp}
///    fTracks.GetEntries();
/// ~~~
/// This will read only the size from disk if the TClonesArray has been
/// split.
/// To access the content of the TClonesArray, use the [] operator:
/// ~~~
///    float px = fTracks[i].fPx; // fPx of the i-th track
/// ~~~
/// Warning:
/// The variable actually use for access are 'wrapper' around the
/// real data type (to add autoload for example) and hence getting to
/// the data involves the implicit call to a C++ conversion operator.
/// This conversion is automatic in most case.  However it is not invoked
/// in a few cases, in particular in variadic function (like printf).
/// So when using printf you should either explicitly cast the value or
/// use any intermediary variable:
/// ~~~{.cpp}
///      fprintf(stdout,"trs[%d].a = %d\n",i,(int)trs.a[i]);
/// ~~~
/// Also, optionally, the generated selector will also call methods named
/// macrofilename_methodname in each of 6 main selector methods if the method
/// macrofilename_methodname exist (Where macrofilename is stripped of its
/// extension).
///
/// Concretely, with the script named h1analysisProxy.C,
///
/// -  The method         calls the method (if it exist)
/// -  Begin           -> void h1analysisProxy_Begin(TTree*);
/// -  SlaveBegin      -> void h1analysisProxy_SlaveBegin(TTree*);
/// -  Notify          -> Bool_t h1analysisProxy_Notify();
/// -  Process         -> Bool_t h1analysisProxy_Process(Long64_t);
/// -  SlaveTerminate  -> void h1analysisProxy_SlaveTerminate();
/// -  Terminate       -> void h1analysisProxy_Terminate();
///
/// If a file name macrofilename.h (or .hh, .hpp, .hxx, .hPP, .hXX) exist
/// it is included before the declaration of the proxy class.  This can
/// be used in particular to insure that the include files needed by
/// the macro file are properly loaded.
///
/// The default histogram is accessible via the variable named 'htemp'.
///
/// If the library of the classes describing the data in the branch is
/// loaded, the skeleton will add the needed #include statements and
/// give the ability to access the object stored in the branches.
///
/// To draw px using the file hsimple.root (generated by the
/// hsimple.C tutorial), we need a file named hsimple.cxx:
/// ~~~{.cpp}
///     double hsimple() {
///        return px;
///     }
/// ~~~
/// MakeProxy can then be used indirectly via the TTree::Draw interface
/// as follow:
/// ~~~{.cpp}
///     new TFile("hsimple.root")
///     ntuple->Draw("hsimple.cxx");
/// ~~~
/// A more complete example is available in the tutorials directory:
/// h1analysisProxy.cxx , h1analysProxy.h and h1analysisProxyCut.C
/// which reimplement the selector found in h1analysis.C

   virtual Int_t     MakeReader(const char *classname, Option_t *option);
/// Generate skeleton selector class for this tree.
/// The following files are produced: classname.h and classname.C.
/// If classname is 0, the selector will be called "nameoftree".
/// The option can be used to specify the branches that will have a data member.
///    - If option is empty, readers will be generated for each leaf.
///    - If option is "@", readers will be generated for the topmost branches.
///    - Individual branches can also be picked by their name:
///       - "X" generates readers for leaves of X.
///       - "@X" generates a reader for X as a whole.
///       - "@X;Y" generates a reader for X as a whole and also readers for the
///         leaves of Y.
///    - For further examples see the figure below.
/// The generated code in classname.h includes the following:
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
/// The selector derives from TSelector.
/// The generated code in classname.C includes empty functions defined above.
/// To use this function:
///    - connect your Tree file (eg: TFile f("myfile.root");)
///    - T->MakeSelector("myselect");
/// where T is the name of the Tree in file myfile.root
/// and myselect.h, myselect.C the name of the files created by this function.
/// In a ROOT session, you can do:
///    root > T->Process("myselect.C")

   TPrincipal       *Principal(const char *varexp, const char *selection, Option_t *option
                               ,Long64_t nentries, Long64_t firstentry);
/// Interface to the Principal Components Analysis class.
/// Create an instance of TPrincipal
/// Fill it with the selected variables
/// -  if option "n" is specified, the TPrincipal object is filled with
///                 normalized variables.
/// -  If option "p" is specified, compute the principal components
/// -  If option "p" and "d" print results of analysis
/// -  If option "p" and "h" generate standard histograms
/// -  If option "p" and "c" generate code of conversion functions
/// return a pointer to the TPrincipal object. It is the user responsibility
/// to delete this object.
/// The option default value is "np"
/// See TTreePlayer::DrawSelect for explanation of the other parameters.

   virtual Long64_t  Process(const char *filename,Option_t *option, Long64_t nentries, Long64_t firstentry);
/// Process this tree executing the TSelector code in the specified filename.
/// The return value is -1 in case of error and TSelector::GetStatus() in
/// in case of success.
/// The code in filename is loaded (interpreted or compiled, see below),
/// filename must contain a valid class implementation derived from TSelector,
/// where TSelector has the following member functions:
/// -  Begin():        called every time a loop on the tree starts,
///                    a convenient place to create your histograms.
/// -  SlaveBegin():   called after Begin(), when on PROOF called only on the
///                    slave servers.
/// -  Process():      called for each event, in this function you decide what
///                    to read and fill your histograms.
/// -  SlaveTerminate: called at the end of the loop on the tree, when on PROOF
///                    called only on the slave servers.
/// -  Terminate():    called at the end of the loop on the tree,
///                    a convenient place to draw/fit your histograms.
/// If filename is of the form file.C, the file will be interpreted.
/// If filename is of the form file.C++, the file file.C will be compiled
/// and dynamically loaded.
/// If filename is of the form file.C+, the file file.C will be compiled
/// and dynamically loaded. At next call, if file.C is older than file.o
/// and file.so, the file.C is not compiled, only file.so is loaded.

   virtual Long64_t  Process(TSelector *selector,Option_t *option,  Long64_t nentries, Long64_t firstentry);
/// Process this tree executing the code in the specified selector.
/// The return value is -1 in case of error and TSelector::GetStatus() in
/// in case of success.
///   The TSelector class has the following member functions:
/// -  Begin():        called every time a loop on the tree starts,
///                    a convenient place to create your histograms.
/// -  SlaveBegin():   called after Begin(), when on PROOF called only on the
///                    slave servers.
/// -  Process():      called for each event, in this function you decide what
///                    to read and fill your histograms.
/// -  SlaveTerminate: called at the end of the loop on the tree, when on PROOF
///                    called only on the slave servers.
/// -  Terminate():    called at the end of the loop on the tree,
///                    a convenient place to draw/fit your histograms.
///  If the Tree (Chain) has an associated EventList, the loop is on the nentries
///  of the EventList, starting at firstentry, otherwise the loop is on the
///  specified Tree entries.

   virtual void      RecursiveRemove(TObject *obj);/// cleanup pointers in the player pointing to obj
   virtual Long64_t  Scan(const char *varexp, const char *selection, Option_t *option
                          ,Long64_t nentries, Long64_t firstentry);
/// Loop on Tree and print entries passing selection. If varexp is 0 (or "")
/// then print only first 8 columns. If varexp = "*" print all columns.
/// Otherwise a columns selection can be made using "var1:var2:var3".
/// The function returns the number of entries passing the selection.
/// By default 50 rows are shown and you are asked for <CR>
/// to see the next 50 rows.
/// You can change the default number of rows to be shown before <CR>
/// via  mytree->SetScanField(maxrows) where maxrows is 50 by default.
/// if maxrows is set to 0 all rows of the Tree are shown.
/// This option is interesting when dumping the contents of a Tree to
/// an ascii file, eg from the command line
/// ~~~{.cpp}
///   tree->SetScanField(0);
///   tree->Scan("*"); >tree.log
/// ~~~
///  will create a file tree.log
/// Arrays (within an entry) are printed in their linear forms.
/// If several arrays with multiple dimensions are printed together,
/// they will NOT be synchronized.  For example print
///   arr1[4][2] and arr2[2][3] will results in a printing similar to:
/// ~~~{.cpp}
/// ***********************************************
/// *    Row   * Instance *      arr1 *      arr2 *
/// ***********************************************
/// *        x *        0 * arr1[0][0]* arr2[0][0]*
/// *        x *        1 * arr1[0][1]* arr2[0][1]*
/// *        x *        2 * arr1[1][0]* arr2[0][2]*
/// *        x *        3 * arr1[1][1]* arr2[1][0]*
/// *        x *        4 * arr1[2][0]* arr2[1][1]*
/// *        x *        5 * arr1[2][1]* arr2[1][2]*
/// *        x *        6 * arr1[3][0]*           *
/// *        x *        7 * arr1[3][1]*           *
/// ~~~
/// However, if there is a selection criterion which is an array, then
/// all the formulas will be synchronized with the selection criterion
/// (see TTreePlayer::DrawSelect for more information).
/// The options string can contains the following parameters:
/// -  lenmax=dd
///       Where 'dd' is the maximum number of elements per array that should
///       be printed.  If 'dd' is 0, all elements are printed (this is the
///       default)
/// -  colsize=ss
///       Where 'ss' will be used as the default size for all the column
///       If this options is not specified, the default column size is 9
/// -  precision=pp
///       Where 'pp' will be used as the default 'precision' for the
///       printing format.
/// -  col=xxx
///       Where 'xxx' is colon (:) delimited list of printing format for
///       each column. The format string should follow the printf format
///       specification.  The value given will be prefixed by % and, if no
///       conversion specifier is given, will be suffixed by the letter g.
///       before being passed to fprintf.  If no format is specified for a
///       column, the default is used  (aka ${colsize}.${precision}g )

   Bool_t            ScanRedirected() {return fScanRedirect;}
   virtual TSQLResult *Query(const char *varexp, const char *selection, Option_t *option
                             ,Long64_t nentries, Long64_t firstentry);
/// Loop on Tree and return TSQLResult object containing entries passing
/// selection. If varexp is 0 (or "") then print only first 8 columns.
/// If varexp = "*" print all columns. Otherwise a columns selection can
/// be made using "var1:var2:var3". In case of error 0 is returned otherwise
/// a TSQLResult object which must be deleted by the user.

   virtual void      SetEstimate(Long64_t n);/// Set number of entries to estimate variable limits.
   void              SetScanRedirect(Bool_t on=kFALSE) {fScanRedirect = on;}
   void              SetScanFileName(const char *name) {fScanFileName=name;}
   virtual void      SetTree(TTree *t) {fTree = t;}
   virtual void      StartViewer(Int_t ww, Int_t wh);
/// Start the TTreeViewer on this TTree.
/// -  ww is the width of the canvas in pixels
/// -  wh is the height of the canvas in pixels

   virtual Int_t     UnbinnedFit(const char *formula ,const char *varexp, const char *selection,Option_t *option
                                 ,Long64_t nentries, Long64_t firstentry);
/// Unbinned fit of one or more variable(s) from a Tree.
/// funcname is a TF1 function.
/// See TTree::Draw for explanations of the other parameters.
/// Fit the variable varexp using the function funcname using the
/// selection cuts given by selection.
/// The list of fit options is given in parameter option.
/// -  option = "Q" Quiet mode (minimum printing)
/// -  option = "V" Verbose mode (default is between Q and V)
/// -  option = "E" Perform better Errors estimation using Minos technique
/// -  option = "M" More. Improve fit results
/// -  option = "D" Draw the projected histogram with the fitted function
///             normalized to the number of selected rows
///             and multiplied by the bin width
/// You can specify boundary limits for some or all parameters via
/// ~~~{.cpp}
///        func->SetParLimits(p_number, parmin, parmax);
/// ~~~
/// if parmin>=parmax, the parameter is fixed
/// Note that you are not forced to fix the limits for all parameters.
/// For example, if you fit a function with 6 parameters, you can do:
/// ~~~{.cpp}
///     func->SetParameters(0,3.1,1.e-6,0.1,-8,100);
///     func->SetParLimits(4,-10,-4);
///     func->SetParLimits(5, 1,1);
/// ~~~
/// With this setup, parameters 0->3 can vary freely
/// -  Parameter 4 has boundaries [-10,-4] with initial value -8
/// -  Parameter 5 is fixed to 100.
///   For the fit to be meaningful, the function must be self-normalized.
/// i.e. It must have the same integral regardless of the parameter
/// settings.  Otherwise the fit will effectively just maximize the
/// area.
/// It is mandatory to have a normalization variable
/// which is fixed for the fit.  e.g.
/// ~~~{.cpp}
///     TF1* f1 = new TF1("f1", "gaus(0)/sqrt(2*3.14159)/[2]", 0, 5);
///     f1->SetParameters(1, 3.1, 0.01);
///     f1->SetParLimits(0, 1, 1); // fix the normalization parameter to 1
///     data->UnbinnedFit("f1", "jpsimass", "jpsipt>3.0");
/// ~~~
/// 1, 2 and 3 Dimensional fits are supported.
/// See also TTree::Fit
/// ### Return status
/// The function return the status of the fit in the following form
/// ~~~{.cpp}
///     fitResult = migradResult + 10*minosResult + 100*hesseResult + 1000*improveResult
/// -  The fitResult is 0 is the fit is OK.
/// -  The fitResult is negative in case of an error not connected with the fit.
/// -  The number of entries used in the fit can be obtained via
/// ~~~{.cpp}
///     mytree.GetSelectedRows();
/// ~~~
/// -  If the number of selected entries is null the function returns -1
/// new implementation using new Fitter classes

   virtual void      UpdateFormulaLeaves();
/// this function is called by TChain::LoadTree when a new Tree is loaded.
/// Because Trees in a TChain may have a different list of leaves, one
/// must update the leaves numbers in the TTreeFormula used by the TreePlayer.
```

## code

```cpp
// Long64_t TTreePlayer::Scan(const char *varexp, const char *selection,
//                            Option_t * option,
//                            Long64_t nentries, Long64_t firstentry)

tree->Scan("a:b:c","","colsize=30 precision=3 col=::20.10:#x:5ld");

/// Will print 3 columns, the first 2 columns will be 30 characters long,
/// the third columns will be 20 characters long.  The printing format used
/// for the columns (assuming they are numbers) will be respectively:
/// `%30.3g %30.3g %20.10g %#x %5ld`
```


```cpp
// Long64_t TTreePlayer::Process(const char *filename,Option_t *option, Long64_t nentries, Long64_t firstentry)

///  It may be more interesting to invoke directly the other Process function
///  accepting a TSelector* as argument.eg

MySelector *selector = (MySelector*)TSelector::GetSelector(filename);
selector->CallSomeFunction(..);
mytree.Process(selector,..);

///  One should not call this function twice with the same selector file
///  in the same script. If this is required, proceed as indicated in NOTE1,
///  by getting a pointer to the corresponding TSelector,eg
void stubs1() {
   TSelector *selector = TSelector::GetSelector("h1test.C");
   TFile *f1 = new TFile("stubs_nood_le1.root");
   TTree *h1 = (TTree*)f1->Get("h1");
   h1->Process(selector);
   TFile *f2 = new TFile("stubs_nood_le1_coarse.root");
   TTree *h2 = (TTree*)f2->Get("h1");
   h2->Process(selector);
}

///  or use ACLIC to compile the selector
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
// Int_t TTreePlayer::Fit(const char *formula ,const char *varexp, const char *selection,Option_t *option ,Option_t *goption,Long64_t nentries, Long64_t firstentry)

tree.Fit("pol4","sqrt(x)>>hsqrt","y>0")
/// will fit sqrt(x) and save the histogram as "hsqrt" in the current directory.
```

```cpp
// TTree *TTreePlayer::CopyTree(const char *selection, Option_t *, Long64_t nentries, Long64_t firstentry)

/// The following example illustrates how to copy some events from the Tree
/// generated in $ROOTSYS/test/Event
gSystem->Load("libEvent");
TFile f("Event.root");
TTree *T = (TTree*)f.Get("T");
Event *event = new Event();
T->SetBranchAddress("event",&event);
TFile f2("Event2.root","recreate");
TTree *T2 = T->CopyTree("fNtrack<595");
T2->Write();
```



## example

**txt文本输出**

```
root [] .> ttree.txt
tree->Scan("*");
.>
root []
```

```cpp
TTreePlayer *player = ((TTreePlayer*)(tree->GetPlayer()));
player->SetScanRedirect(true); 
player->SetScanFileName("ttree.txt"); 
palyer->Scan("","","",100,0);
```




<!-- TTreePlayer.md ends here -->
