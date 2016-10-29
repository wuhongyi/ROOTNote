<!-- TROOT.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 六 8月 13 19:05:04 2016 (+0800)
;; Last-Updated: 六 8月 13 20:55:43 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 3
;; URL: http://wuhongyi.cn -->

# TROOT

继承 TDirectory

The TROOT object is the entry point to the ROOT system.  
The single instance of TROOT is accessible via the global gROOT.  
Using the gROOT pointer one has access to basically every object created in a ROOT based program. The TROOT object is essentially a container of several lists pointing to the main ROOT objects.


## class

```cpp
   void              AddClass(TClass *cl);
   void              AddClassGenerator(TClassGenerator *gen);
   void              Browse(TBrowser *b);
   Bool_t            ClassSaved(TClass *cl);
   void              CloseFiles();
   void              EndOfProcessCleanups();
   virtual TObject  *FindObject(const char *name) const;
   virtual TObject  *FindObject(const TObject *obj) const;
   virtual TObject  *FindObjectAny(const char *name) const;
   virtual TObject  *FindObjectAnyFile(const char *name) const;
   TObject          *FindSpecialObject(const char *name, void *&where);
   const char       *FindObjectClassName(const char *name) const;
   const char       *FindObjectPathName(const TObject *obj) const;
   TClass           *FindSTLClass(const char *name, Bool_t load, Bool_t silent = kFALSE) const;
   void              ForceStyle(Bool_t force = kTRUE) { fForceStyle = force; }
   Bool_t            FromPopUp() const { return fFromPopUp; }
   TPluginManager   *GetPluginManager() const { return fPluginManager; }
   TApplication     *GetApplication() const { return fApplication; }
   TInterpreter     *GetInterpreter() const { return fInterpreter; }
   TClass           *GetClass(const char *name, Bool_t load = kTRUE, Bool_t silent = kFALSE) const;
   TClass           *GetClass(const type_info &typeinfo, Bool_t load = kTRUE, Bool_t silent = kFALSE) const;
   TColor           *GetColor(Int_t color) const;
   const char       *GetConfigOptions() const { return fConfigOptions; }
   const char       *GetConfigFeatures() const { return fConfigFeatures; }
   const char       *GetCutClassName() const { return fCutClassName; }
   const char       *GetDefCanvasName() const { return fDefCanvasName; }
   Bool_t            GetEditHistograms() const { return fEditHistograms; }
   Int_t             GetEditorMode() const { return fEditorMode; }
   Bool_t            GetForceStyle() const { return fForceStyle; }
   Int_t             GetBuiltDate() const { return fBuiltDate; }
   Int_t             GetBuiltTime() const { return fBuiltTime; }
   const char       *GetGitCommit() const { return fGitCommit; }
   const char       *GetGitBranch() const { return fGitBranch; }
   const char       *GetGitDate();
   Int_t             GetVersionDate() const { return fVersionDate; }
   Int_t             GetVersionTime() const { return fVersionTime; }
   Int_t             GetVersionInt() const { return fVersionInt; }
   Int_t             GetVersionCode() const { return fVersionCode; }
   const char       *GetVersion() const { return fVersion; }
   TCollection      *GetListOfClasses() const { return fClasses; }
   TSeqCollection   *GetListOfColors() const { return fColors; }
   TCollection      *GetListOfTypes(Bool_t load = kFALSE);
   TCollection      *GetListOfGlobals(Bool_t load = kFALSE);
   TCollection      *GetListOfGlobalFunctions(Bool_t load = kFALSE);
   TSeqCollection   *GetListOfClosedObjects() const { return fClosedObjects; }
   TSeqCollection   *GetListOfFiles() const       { return fFiles; }
   TSeqCollection   *GetListOfMappedFiles() const { return fMappedFiles; }
   TSeqCollection   *GetListOfSockets() const     { return fSockets; }
   TSeqCollection   *GetListOfCanvases() const    { return fCanvases; }
   TSeqCollection   *GetListOfStyles() const      { return fStyles; }
   TCollection      *GetListOfFunctions() const   { return fFunctions; }
   TCollection      *GetListOfFunctionOverloads(const char* name) const;
   TSeqCollection   *GetListOfGeometries() const  { return fGeometries; }
   TSeqCollection   *GetListOfBrowsers() const    { return fBrowsers; }
   TSeqCollection   *GetListOfSpecials() const    { return fSpecials; }
   TSeqCollection   *GetListOfTasks() const       { return fTasks; }
   TSeqCollection   *GetListOfCleanups() const    { return fCleanups; }
   TSeqCollection   *GetListOfStreamerInfo() const { return fStreamerInfo; }
   TSeqCollection   *GetListOfMessageHandlers() const { return fMessageHandlers; }
   TCollection      *GetListOfClassGenerators() const { return fClassGenerators; }
   TSeqCollection   *GetListOfSecContexts() const { return fSecContexts; }
   TSeqCollection   *GetListOfProofs() const { return fProofs; }
   TSeqCollection   *GetClipboard() const { return fClipboard; }
   TSeqCollection   *GetListOfDataSets() const { return fDataSets; }
   TCollection      *GetListOfEnums(Bool_t load = kFALSE);
   TCollection      *GetListOfFunctionTemplates();
   TList            *GetListOfBrowsables() const { return fBrowsables; }
   TDataType        *GetType(const char *name, Bool_t load = kFALSE) const;
   TFile            *GetFile() const { if (gDirectory != this) return gDirectory->GetFile(); else return 0;}
   TFile            *GetFile(const char *name) const;
   TFunctionTemplate*GetFunctionTemplate(const char *name);
   TStyle           *GetStyle(const char *name) const;
   TObject          *GetFunction(const char *name) const;
   TGlobal          *GetGlobal(const char *name, Bool_t load = kFALSE) const;
   TGlobal          *GetGlobal(const TObject *obj, Bool_t load = kFALSE) const;
   TFunction        *GetGlobalFunction(const char *name, const char *params = 0, Bool_t load = kFALSE);
   TFunction        *GetGlobalFunctionWithPrototype(const char *name, const char *proto = 0, Bool_t load = kFALSE);
   TObject          *GetGeometry(const char *name) const;
   const TObject    *GetSelectedPrimitive() const { return fPrimitive; }
   TVirtualPad      *GetSelectedPad() const { return fSelectPad; }
   Int_t             GetNclasses() const { return fClasses->GetSize(); }
   Int_t             GetNtypes() const { return fTypes->GetSize(); }
   TFolder          *GetRootFolder() const { return fRootFolder; }
   TProcessUUID     *GetUUIDs() const { return fUUIDs; }
   void              Idle(UInt_t idleTimeInSec, const char *command = 0);
   Int_t             IgnoreInclude(const char *fname, const char *expandedfname);
   Bool_t            IsBatch() const { return fBatch; }
   Bool_t            IsExecutingMacro() const { return fExecutingMacro; }
   Bool_t            IsFolder() const { return kTRUE; }
   Bool_t            IsInterrupted() const { return fInterrupt; }
   Bool_t            IsEscaped() const { return fEscape; }
   Bool_t            IsLineProcessing() const { return fLineIsProcessing ? kTRUE : kFALSE; }
   Bool_t            IsProofServ() const { return fName == "proofserv" ? kTRUE : kFALSE; }
   Bool_t            IsRootFile(const char *filename) const;
   void              ls(Option_t *option = "") const;
   Int_t             LoadClass(const char *classname, const char *libname, Bool_t check = kFALSE);
   TClass           *LoadClass(const char *name, Bool_t silent = kFALSE) const;
   Int_t             LoadMacro(const char *filename, Int_t *error = 0, Bool_t check = kFALSE);
   Long_t            Macro(const char *filename, Int_t *error = 0, Bool_t padUpdate = kTRUE);
   TCanvas          *MakeDefCanvas() const;
   void              Message(Int_t id, const TObject *obj);
   Bool_t            MustClean() const { return fMustClean; }
   Long_t            ProcessLine(const char *line, Int_t *error = 0);
   Long_t            ProcessLineSync(const char *line, Int_t *error = 0);
   Long_t            ProcessLineFast(const char *line, Int_t *error = 0);
   Bool_t            ReadingObject() const;
   void              RefreshBrowsers();
   static void       RegisterModule(const char* modulename,
                                    const char** headers,
                                    const char** includePaths,
                                    const char* payLoadCode,
                                    const char* fwdDeclCode,
                                    void (*triggerFunc)(),
                                    const FwdDeclArgsToKeepCollection_t& fwdDeclsArgToSkip,
                                    const char** classesHeaders);
   void              RemoveClass(TClass *);
   void              Reset(Option_t *option="");
   void              SaveContext();
   void              SetApplication(TApplication *app) { fApplication = app; }
   void              SetBatch(Bool_t batch = kTRUE) { fBatch = batch; }
   void              SetCutClassName(const char *name = "TCutG");
   void              SetDefCanvasName(const char *name = "c1") { fDefCanvasName = name; }
   void              SetEditHistograms(Bool_t flag = kTRUE) { fEditHistograms = flag; }
   void              SetEditorMode(const char *mode = "");
   void              SetExecutingMacro(Bool_t flag = kTRUE) { fExecutingMacro = flag; }
   void              SetFromPopUp(Bool_t flag = kTRUE) { fFromPopUp = flag; }
   void              SetInterrupt(Bool_t flag = kTRUE) { fInterrupt = flag; }
   void              SetEscape(Bool_t flag = kTRUE) { fEscape = flag; }
   void              SetLineIsProcessing() { fLineIsProcessing++; }
   void              SetLineHasBeenProcessed() { if (fLineIsProcessing) fLineIsProcessing--; }
   void              SetReadingObject(Bool_t flag = kTRUE);
   void              SetMustClean(Bool_t flag = kTRUE) { fMustClean=flag; }
   void              SetSelectedPrimitive(const TObject *obj) { fPrimitive = obj; }
   void              SetSelectedPad(TVirtualPad *pad) { fSelectPad = pad; }
   void              SetStyle(const char *stylename = "Default");
   void              Time(Int_t casetime=1) { fTimer = casetime; }
   Int_t             Timer() const { return fTimer; }

   //---- static functions
   static Int_t       DecreaseDirLevel();
   static Int_t       GetDirLevel();
   static const char *GetMacroPath();
   static void        SetMacroPath(const char *newpath);
   static Int_t       IncreaseDirLevel();
   static void        IndentLevel();
   static Bool_t      Initialized();
   static Bool_t      MemCheck();
   static void        SetDirLevel(Int_t level = 0);
   static Int_t       ConvertVersionCode2Int(Int_t code);
   static Int_t       ConvertVersionInt2Code(Int_t v);
   static Int_t       RootVersionCode();
   static const char**&GetExtraInterpreterArgs();
   static const char *GetTutorialsDir();
```

## code

```cpp
// The following lists are accessible from gROOT object:
gROOT->GetListOfClasses
gROOT->GetListOfColors
gROOT->GetListOfTypes
gROOT->GetListOfGlobals
gROOT->GetListOfGlobalFunctions
gROOT->GetListOfFiles
gROOT->GetListOfMappedFiles
gROOT->GetListOfSockets
gROOT->GetListOfSecContexts
gROOT->GetListOfCanvases
gROOT->GetListOfStyles
gROOT->GetListOfFunctions
gROOT->GetListOfSpecials (for example graphical cuts)
gROOT->GetListOfGeometries
gROOT->GetListOfBrowsers
gROOT->GetListOfCleanups
gROOT->GetListOfMessageHandlers
```

```cpp
//  The ROOT object must be created as a static object. An example
//  of a main program creating an interactive version is shown below:

#include "TRint.h"

int main(int argc, char **argv)
{
   TRint *theApp = new TRint("ROOT example", &argc, argv);

   // Init Intrinsics, build all windows, and enter event loop
   theApp->Run();

   return(0);
}
```



<!-- TROOT.md ends here -->
