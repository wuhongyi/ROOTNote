<!-- TSelector.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 六 5月  6 15:43:39 2017 (+0800)
;; Last-Updated: 六 5月  6 15:57:31 2017 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 3
;; URL: http://wuhongyi.cn -->

# TSelector

**V6.06.02**

**继承 TObject**


A TSelector object is used by the TTree::Draw, TTree::Scan,
TTree::Process to navigate in a TTree and make selections.
It contains the following main methods:

- void TSelector::Init(TTree *t). Called every time a new TTree is
   attached.

- void TSelector::SlaveBegin(). Create e.g. histograms in this method.
  This method is called (with or without PROOF) before looping on the
  entries in the Tree. When using PROOF, this method is called on
  each worker node.

- void TSelector::Begin(). Mostly for backward compatibility; use
  SlaveBegin() instead. Both methods are called before looping on the
  entries in the Tree. When using PROOF, Begin() is called on the
  client only.

- Bool_t TSelector::Notify(). This method is called at the first entry
  of a new file in a chain.

- Bool_t TSelector::Process(Long64_t entry). This method is called
  to process an entry. It is the user's responsability to read
  the corresponding entry in memory (may be just a partial read).
  Once the entry is in memory one can apply a selection and if the
  entry is selected histograms can be filled. Processing stops
  when this function returns kFALSE. This function combines the
  next two functions in one, avoiding to have to maintain state
  in the class to communicate between these two functions.
  See WARNING below about entry.
  This method is used by PROOF.

- Bool_t TSelector::ProcessCut(Long64_t entry). This method is called
  before processing entry. It is the user's responsability to read
  the corresponding entry in memory (may be just a partial read).
  The function returns kTRUE if the entry must be processed,
  kFALSE otherwise. This method is obsolete, use Process().
  See WARNING below about entry.

- void TSelector::ProcessFill(Long64_t entry). This method is called
  for all selected entries. User fills histograms in this function.
  This method is obsolete, use Process().
  See WARNING below about entry.

- void TSelector::SlaveTerminate(). This method is called at the end of
  the loop on all PROOF worker nodes. In local mode this method is
  called on the client too.

- void TSelector::Terminate(). This method is called at the end of
  the loop on all entries. When using PROOF Terminate() is call on
  the client only. Typically one performs the fits on the produced
  histograms or write the histograms to file in this method.

__WARNING when a selector is used with a TChain:__

in the Process, ProcessCut, ProcessFill function, you must use
the pointer to the current Tree to call `GetEntry(entry)`.
entry is always the local entry number in the current tree.
Assuming that fChain is the pointer to the TChain being processed,
use `fChain->GetTree()->GetEntry(entry);`



## class

```cpp
   enum EAbort { kContinue, kAbortProcess, kAbortFile };

   TSelector();
   virtual            ~TSelector();

   virtual int         Version() const { return 0; }
   virtual void        Init(TTree *) { }
   virtual void        Begin(TTree *) { }
   virtual void        SlaveBegin(TTree *) { }
   virtual Bool_t      Notify() { return kTRUE; }
   virtual const char *GetOption() const { return fOption; }
   virtual Long64_t    GetStatus() const { return fStatus; }
   virtual Int_t       GetEntry(Long64_t /*entry*/, Int_t /*getall*/ = 0) { return 0; }
   virtual Bool_t      ProcessCut(Long64_t /*entry*/);
   virtual void        ProcessFill(Long64_t /*entry*/);
   virtual Bool_t      Process(Long64_t /*entry*/);
   virtual void        SetOption(const char *option) { fOption = option; }
   virtual void        SetObject(TObject *obj) { fObject = obj; }
   virtual void        SetInputList(TList *input) { fInput = input; }
   virtual void        SetStatus(Long64_t status) { fStatus = status; }
   virtual TList      *GetInputList() const { return fInput; }
   virtual TList      *GetOutputList() const { return fOutput; }
   virtual void        SlaveTerminate() { }
   virtual void        Terminate() { }
   virtual void        Abort(const char *why, EAbort what = kAbortProcess);
/// Abort processing. If what = kAbortProcess, the Process() loop will be
/// aborted. If what = kAbortFile, the current file in a chain will be
/// aborted and the processing will continue with the next file, if there
/// is no next file then Process() will be aborted. Abort() can also  be
/// called from Begin(), SlaveBegin(), Init() and Notify(). After abort
/// the SlaveTerminate() and Terminate() are always called. The abort flag
/// can be checked in these methods using GetAbort().

   virtual EAbort      GetAbort() const { return fAbort; }
   virtual void        ResetAbort() { fAbort = kContinue; }

   static  TSelector  *GetSelector(const char *filename);
/// The code in filename is loaded (interpreted or compiled, see below),
/// filename must contain a valid class implementation derived from TSelector.
///
/// If filename is of the form file.C, the file will be interpreted.
/// If filename is of the form file.C++, the file file.C will be compiled
/// and dynamically loaded. The corresponding binary file and shared
/// library will be deleted at the end of the function.
/// If filename is of the form file.C+, the file file.C will be compiled
/// and dynamically loaded. At next call, if file.C is older than file.o
/// and file.so, the file.C is not compiled, only file.so is loaded.
///
/// The static function returns a pointer to a TSelector object

   static  Bool_t      IsStandardDraw(const char *selec);
/// Find out if this is a standard selection used for Draw actions
/// (either TSelectorDraw, TProofDraw or deriving from them).


```




<!-- TSelector.md ends here -->
