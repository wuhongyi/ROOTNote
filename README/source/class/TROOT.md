<!-- TROOT.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 六 8月 13 19:05:04 2016 (+0800)
;; Last-Updated: 三 9月 16 10:28:42 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 7
;; URL: http://wuhongyi.cn -->

# TROOT*

继承 TDirectory

The TROOT object is the entry point to the ROOT system.  
The single instance of TROOT is accessible via the global gROOT.  
Using the gROOT pointer one has access to basically every object created in a ROOT based program. The TROOT object is essentially a container of several lists pointing to the main ROOT objects.


## class

```cpp
   void              AddClass(TClass *cl);
/// Add a class to the list and map of classes.
/// This routine is deprecated, use TClass::AddClass directly.

   void              AddClassGenerator(TClassGenerator *gen);
/// Add a class generator.  This generator will be called by TClass::GetClass
/// in case its does not find a loaded rootcint dictionary to request the
/// creation of a TClass object.

   void              Browse(TBrowser *b);/// Add browsable objects to TBrowser.
   Bool_t            ClassSaved(TClass *cl);
/// return class status bit kClassSaved for class cl
/// This function is called by the SavePrimitive functions writing
/// the C++ code for an object.

   void              CloseFiles();
/// Close any files and sockets that gROOT knows about.
/// This can be used to insures that the files and sockets are closed before any library is unloaded!

   void              EndOfProcessCleanups();
/// Execute the cleanups necessary at the end of the process, in particular
/// those that must be executed before the library start being unloaded.

   virtual TObject  *FindObject(const char *name) const;
/// Returns address of a ROOT object if it exists
/// If name contains at least one "/" the function calls FindObjectany
/// else
/// This function looks in the following order in the ROOT lists:
///     - List of files
///     - List of memory mapped files
///     - List of functions
///     - List of geometries
///     - List of canvases
///     - List of styles
///     - List of specials
///     - List of materials in current geometry
///     - List of shapes in current geometry
///     - List of matrices in current geometry
///     - List of Nodes in current geometry
///     - Current Directory in memory
///     - Current Directory on file

   virtual TObject  *FindObject(const TObject *obj) const;/// Find an object in one Root folder
   virtual TObject  *FindObjectAny(const char *name) const;
/// Return a pointer to the first object with name starting at //root.
/// This function scans the list of all folders.
/// if no object found in folders, it scans the memory list of all files.

   virtual TObject  *FindObjectAnyFile(const char *name) const;/// Scan the memory lists of all files for an object with name
   TObject          *FindSpecialObject(const char *name, void *&where);
/// Returns address and folder of a ROOT object if it exists
/// This function looks in the following order in the ROOT lists:
///     - List of files
///     - List of memory mapped files
///     - List of functions
///     - List of geometries
///     - List of canvases
///     - List of styles
///     - List of specials
///     - List of materials in current geometry
///     - List of shapes in current geometry
///     - List of matrices in current geometry
///     - List of Nodes in current geometry
///     - Current Directory in memory
///     - Current Directory on file

   const char       *FindObjectClassName(const char *name) const;/// Returns class name of a ROOT object including CINT globals.
   const char       *FindObjectPathName(const TObject *obj) const;
/// Return path name of obj somewhere in the //root/... path.
/// The function returns the first occurence of the object in the list
/// of folders. The returned string points to a static char array in TROOT.
/// If this function is called in a loop or recursively, it is the
/// user's responsibility to copy this string in their area.

   TClass           *FindSTLClass(const char *name, Bool_t load, Bool_t silent = kFALSE) const;
/// return a TClass object corresponding to 'name' assuming it is an STL container.
/// In particular we looking for possible alternative name (default template
/// parameter, typedefs template arguments, typedefed name).
   // Example of inputs are
   //   vector<int>  (*)
   //   vector<Int_t>
   //   vector<long long>
   //   vector<Long_64_t> (*)
   //   vector<int, allocator<int> >
   //   vector<Int_t, allocator<int> >
   //   One of the possibly expensive operation is the resolving of the typedef
   //   which can provoke the parsing of the header files (and/or the loading
   //   of clang pcms information).


   void              ForceStyle(Bool_t force = kTRUE) { fForceStyle = force; }
   Bool_t            FromPopUp() const { return fFromPopUp; }
   TPluginManager   *GetPluginManager() const { return fPluginManager; }
   TApplication     *GetApplication() const { return fApplication; }
   TInterpreter     *GetInterpreter() const { return fInterpreter; }
   TClass           *GetClass(const char *name, Bool_t load = kTRUE, Bool_t silent = kFALSE) const;
/// Return pointer to class with name. Obsolete, use TClass::GetClass directly

   TClass           *GetClass(const type_info &typeinfo, Bool_t load = kTRUE, Bool_t silent = kFALSE) const;
/// Return pointer to class from its name. Obsolete, use TClass::GetClass directly
/// See TClass::GetClass

   TColor           *GetColor(Int_t color) const;/// Return address of color with index color.
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
   const char       *GetGitDate();/// Return date/time make was run.
   Int_t             GetVersionDate() const { return fVersionDate; }
   Int_t             GetVersionTime() const { return fVersionTime; }
   Int_t             GetVersionInt() const { return fVersionInt; }
   Int_t             GetVersionCode() const { return fVersionCode; }
   const char       *GetVersion() const { return fVersion; }
   TCollection      *GetListOfClasses() const { return fClasses; }
   TSeqCollection   *GetListOfColors() const { return fColors; }
   TCollection      *GetListOfTypes(Bool_t load = kFALSE);/// Return a dynamic list giving access to all TDataTypes (typedefs)
/// currently defined.
   TCollection      *GetListOfGlobals(Bool_t load = kFALSE);
/// Return list containing the TGlobals currently defined.
/// Since globals are created and deleted during execution of the
/// program, we need to update the list of globals every time we
/// execute this method. However, when calling this function in
/// a (tight) loop where no interpreter symbols will be created
/// you can set load=kFALSE (default).

   TCollection      *GetListOfGlobalFunctions(Bool_t load = kFALSE);
/// Return list containing the TFunctions currently defined.
/// Since functions are created and deleted during execution of the
/// program, we need to update the list of functions every time we
/// execute this method. However, when calling this function in
/// a (tight) loop where no interpreter symbols will be created
/// you can set load=kFALSE (default).

   TSeqCollection   *GetListOfClosedObjects() const { return fClosedObjects; }
   TSeqCollection   *GetListOfFiles() const       { return fFiles; }
   TSeqCollection   *GetListOfMappedFiles() const { return fMappedFiles; }
   TSeqCollection   *GetListOfSockets() const     { return fSockets; }
   TSeqCollection   *GetListOfCanvases() const    { return fCanvases; }
   TSeqCollection   *GetListOfStyles() const      { return fStyles; }
   TCollection      *GetListOfFunctions() const   { return fFunctions; }
   TCollection      *GetListOfFunctionOverloads(const char* name) const;/// Return the collection of functions named "name".
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
   TDataType        *GetType(const char *name, Bool_t load = kFALSE) const;/// Return pointer to type with name.
   TFile            *GetFile() const { if (gDirectory != this) return gDirectory->GetFile(); else return 0;}
   TFile            *GetFile(const char *name) const;/// Return pointer to file with name.
   TFunctionTemplate*GetFunctionTemplate(const char *name);
   TStyle           *GetStyle(const char *name) const;/// Return pointer to style with name
   TObject          *GetFunction(const char *name) const;/// Return pointer to function with name.
   TGlobal          *GetGlobal(const char *name, Bool_t load = kFALSE) const;
/// Return pointer to global variable by name. If load is true force
/// reading of all currently defined globals from CINT (more expensive).

   TGlobal          *GetGlobal(const TObject *obj, Bool_t load = kFALSE) const;/// Return pointer to global variable with address addr.
   TFunction        *GetGlobalFunction(const char *name, const char *params = 0, Bool_t load = kFALSE);
/// Return pointer to global function by name.
/// If params != 0 it will also resolve overloading other it returns the first
/// name match.
/// If params == 0 and load is true force reading of all currently defined
/// global functions from Cling.
/// The param string must be of the form: "3189,\"aap\",1.3".

   TFunction        *GetGlobalFunctionWithPrototype(const char *name, const char *proto = 0, Bool_t load = kFALSE);
/// Return pointer to global function by name. If proto != 0
/// it will also resolve overloading. If load is true force reading
/// of all currently defined global functions from CINT (more expensive).
/// The proto string must be of the form: "int, char*, float".

   TObject          *GetGeometry(const char *name) const;/// Return pointer to Geometry with name
   const TObject    *GetSelectedPrimitive() const { return fPrimitive; }
   TVirtualPad      *GetSelectedPad() const { return fSelectPad; }
   Int_t             GetNclasses() const { return fClasses->GetSize(); }
   Int_t             GetNtypes() const { return fTypes->GetSize(); }
   TFolder          *GetRootFolder() const { return fRootFolder; }
   TProcessUUID     *GetUUIDs() const { return fUUIDs; }
   void              Idle(UInt_t idleTimeInSec, const char *command = 0);/// Execute command when system has been idle for idleTimeInSec seconds.
   Int_t             IgnoreInclude(const char *fname, const char *expandedfname);
/// Return 1 if the name of the given include file corresponds to a class that
///  is known to ROOT, e.g. "TLorentzVector.h" versus TLorentzVector.

   Bool_t            IsBatch() const { return fBatch; }
   Bool_t            IsExecutingMacro() const { return fExecutingMacro; }
   Bool_t            IsFolder() const { return kTRUE; }
   Bool_t            IsInterrupted() const { return fInterrupt; }
   Bool_t            IsEscaped() const { return fEscape; }
   Bool_t            IsLineProcessing() const { return fLineIsProcessing ? kTRUE : kFALSE; }
   Bool_t            IsProofServ() const { return fName == "proofserv" ? kTRUE : kFALSE; }
   Bool_t            IsRootFile(const char *filename) const;/// Return true if the file is local and is (likely) to be a ROOT file
   void              ls(Option_t *option = "") const;
/// To list all objects of the application.
/// Loop on all objects created in the ROOT linked lists.
/// Objects may be files and windows or any other object directly
/// attached to the ROOT linked list.

   Int_t             LoadClass(const char *classname, const char *libname, Bool_t check = kFALSE);
/// Check if class "classname" is known to the interpreter (in fact,
/// this check is not needed anymore, so classname is ignored). If
/// not it will load library "libname". If the library name does
/// not start with "lib", "lib" will be prepended and a search will
/// be made in the DynamicPath (see .rootrc). If not found a search
/// will be made on libname (without "lib" prepended) and if not found
/// a direct try of libname will be made (in case it contained an
/// absolute path).
/// If check is true it will only check if libname exists and is
/// readable.
/// Returns 0 on successful loading, -1 in case libname does not
/// exist or in case of error and -2 in case of version mismatch.

   TClass           *LoadClass(const char *name, Bool_t silent = kFALSE) const;
/// Helper function used by TClass::GetClass().
/// This function attempts to load the dictionary for 'classname'
/// either from the TClassTable or from the list of generator.
/// If silent is 'true', do not warn about missing dictionary for the class.
/// (typically used for class that are used only for transient members)
/// The 'requestedname' is expected to be already normalized.

   Int_t             LoadMacro(const char *filename, Int_t *error = 0, Bool_t check = kFALSE);
/// Load a macro in the interpreter's memory. Equivalent to the command line
/// command ".L filename". If the filename has "+" or "++" appended
/// the macro will be compiled by ACLiC. The filename must have the format:
/// [path/]macro.C[+|++[g|O]].
/// The possible error codes are defined by TInterpreter::EErrorCode.
/// If check is true it will only check if filename exists and is
/// readable.
/// Returns 0 on successful loading and -1 in case filename does not
/// exist or in case of error.

   Long_t            Macro(const char *filename, Int_t *error = 0, Bool_t padUpdate = kTRUE);
/// Execute a macro in the interpreter. Equivalent to the command line
/// command ".x filename". If the filename has "+" or "++" appended
/// the macro will be compiled by ACLiC. The filename must have the format:
/// [path/]macro.C[+|++[g|O]][(args)].
/// The possible error codes are defined by TInterpreter::EErrorCode.
/// If padUpdate is true (default) update the current pad.
/// Returns the macro return value.

   TCanvas          *MakeDefCanvas() const;/// Return a default canvas.
   void              Message(Int_t id, const TObject *obj);/// Process message id called by obj.
   Bool_t            MustClean() const { return fMustClean; }
   Long_t            ProcessLine(const char *line, Int_t *error = 0);
/// Process interpreter command via TApplication::ProcessLine().
/// On Win32 the line will be processed asynchronously by sending
/// it to the CINT interpreter thread. For explicit synchronous processing
/// use ProcessLineSync(). On non-Win32 platforms there is no difference
/// between ProcessLine() and ProcessLineSync().
/// The possible error codes are defined by TInterpreter::EErrorCode. In
/// particular, error will equal to TInterpreter::kProcessing until the
/// CINT interpreted thread has finished executing the line.
/// Returns the result of the command, cast to a Long_t.

   Long_t            ProcessLineSync(const char *line, Int_t *error = 0);
/// Process interpreter command via TApplication::ProcessLine().
/// On Win32 the line will be processed synchronously (i.e. it will
/// only return when the CINT interpreter thread has finished executing
/// the line). On non-Win32 platforms there is no difference between
/// ProcessLine() and ProcessLineSync().
/// The possible error codes are defined by TInterpreter::EErrorCode.
/// Returns the result of the command, cast to a Long_t.

   Long_t            ProcessLineFast(const char *line, Int_t *error = 0);
// Process interpreter command directly via CINT interpreter.
/// Only executable statements are allowed (no variable declarations),
/// In all other cases use TROOT::ProcessLine().
/// The possible error codes are defined by TInterpreter::EErrorCode.

   Bool_t            ReadingObject() const;/// Deprecated (will be removed in next release).
   void              RefreshBrowsers();
/// Refresh all browsers. Call this method when some command line
/// command or script has changed the browser contents. Not needed
/// for objects that have the kMustCleanup bit set. Most useful to
/// update browsers that show the file system or other objects external
/// to the running ROOT session.

   static void       RegisterModule(const char* modulename,
                                    const char** headers,
                                    const char** includePaths,
                                    const char* payLoadCode,
                                    const char* fwdDeclCode,
                                    void (*triggerFunc)(),
                                    const FwdDeclArgsToKeepCollection_t& fwdDeclsArgToSkip,
                                    const char** classesHeaders);
/// Called by static dictionary initialization to register clang modules
/// for headers. Calls TCling::RegisterModule() unless gCling
/// is NULL, i.e. during startup, where the information is buffered in
/// the static GetModuleHeaderInfoBuffer().
   // First a side track to insure proper end of process behavior.
   // Register for each loaded dictionary (and thus for each library),
   // that we need to Close the ROOT files as soon as this library
   // might start being unloaded after main.
   // By calling atexit here (rather than directly from within the
   // library) we make sure that this is not called if the library is
   // 'only' dlclosed.
   // On Ubuntu the linker strips the unused libraries.  Eventhough
   // stressHistogram is explicitly linked against libNet, it is not
   // retained and thus is loaded only as needed in the middle part of
   // the execution.  Concretely this also means that it is loaded
   // *after* the construction of the TApplication object and thus
   // after the registration (atexit) of the EndOfProcessCleanups
   // routine.  Consequently, after the end of main, libNet is
   // unloaded before EndOfProcessCleanups is called.  When
   // EndOfProcessCleanups is executed it indirectly needs the TClass
   // for TSocket and its search will use resources that have already
   // been unloaded (technically the function static in TUnixSystem's
   // DynamicPath and the dictionary from libNet).
   // Similarly, the ordering (before this commit) was broken in the
   // following case:
   //    TApplication creation (EndOfProcessCleanups registration)
   //    load UserLibrary
   //    create TFile
   //    Append UserObject to TFile
   // and after the end of main the order of execution was
   //    unload UserLibrary
   //    call EndOfProcessCleanups
   //       Write the TFile
   //         attempt to write the user object.
   //    ....
   // where what we need is to have the files closen/written before
   // the unloading of the library.
   // To solve the problem we now register an atexit function for
   // every dictionary thus making sure there is at least one executed
   // before the first library tear down after main.
   // If atexit is called directly within a library's code, the
   // function will called *either* when the library is 'dlclose'd or
   // after then end of main (whichever comes first).  We do *not*
   // want the files to be closed whenever a library is unloaded via
   // dlclose.  To avoid this, we add the function (CallCloseFiles)
   // from the dictionary indirectly (via ROOT::RegisterModule).  In
   // this case the function will only only be called either when
   // libCore is 'dlclose'd or right after the end of main.


    void              RemoveClass(TClass *);
/// Remove a class from the list and map of classes.
/// This routine is deprecated, use TClass::RemoveClass directly.

    void              Reset(Option_t *option="");
/// Delete all global interpreter objects created since the last call to Reset
/// If option="a" is set reset to startup context (i.e. unload also
/// all loaded files, classes, structs, typedefs, etc.).
/// This function is typically used at the beginning (or end) of an unnamed macro
/// to clean the environment.
/// IMPORTANT WARNING:
/// Do not use this call from within any function (neither compiled nor
/// interpreted.  This should only be used from a unnamed macro
/// (which starts with a { (curly braces)  ).  For example, using TROOT::Reset
/// from within an interpreted function will lead to the unloading of the
/// dictionary and source file, including the one defining the function being
/// executed.

   void              SaveContext();/// Save the current interpreter context.
   void              SetApplication(TApplication *app) { fApplication = app; }
   void              SetBatch(Bool_t batch = kTRUE) { fBatch = batch; }
   void              SetCutClassName(const char *name = "TCutG");
/// Set the default graphical cut class name for the graphics editor
/// By default the graphics editor creates an instance of a class TCutG.
/// This function may be called to specify a different class that MUST
/// derive from TCutG

   void              SetDefCanvasName(const char *name = "c1") { fDefCanvasName = name; }
   void              SetEditHistograms(Bool_t flag = kTRUE) { fEditHistograms = flag; }
   void              SetEditorMode(const char *mode = "");/// Set editor mode
// mode: "Arc" "Line" "Arrow" "Button" "Diamond" "Ellipse" "Pad" "Pave" "PaveLabel" "PaveText" "PavesText" "PolyLine" "CurlyLine" "CurlyArc" "Text" "Marker" "CutG"

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
   void              SetStyle(const char *stylename = "Default");/// Change current style to style with name stylename
   void              Time(Int_t casetime=1) { fTimer = casetime; }
   Int_t             Timer() const { return fTimer; }

   //---- static functions
   static Int_t       DecreaseDirLevel();/// Decrease the indentation level for ls().
   static Int_t       GetDirLevel();///return directory level
   static const char *GetMacroPath();/// Get macro search path. Static utility function.
   static void        SetMacroPath(const char *newpath);
/// Set or extend the macro search path. Static utility function.
/// If newpath=0 or "" reset to value specified in the rootrc file.

   static Int_t       IncreaseDirLevel();/// Increase the indentation level for ls().
   static void        IndentLevel();/// Functions used by ls() to indent an object hierarchy.
   static Bool_t      Initialized();/// Return kTRUE if the TROOT object has been initialized.
   static Bool_t      MemCheck();/// Return kTRUE if the memory leak checker is on.
   static void        SetDirLevel(Int_t level = 0);/// Return Indentation level for ls().
   static Int_t       ConvertVersionCode2Int(Int_t code);/// Convert version code to an integer, i.e. 331527 -> 51507.
   static Int_t       ConvertVersionInt2Code(Int_t v);/// Convert version as an integer to version code as used in RVersion.h.
   static Int_t       RootVersionCode();/// Return ROOT version code as defined in RVersion.h.
   static const char**&GetExtraInterpreterArgs();
   static const char *GetTutorialsDir();/// Get the tutorials directory in the installation. Static utility function.
```

----

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

```cpp
/// Return a dynamic list giving access to all TDataTypes (typedefs)
/// currently defined.
///
/// The list is populated on demand.  Calling

gROOT->GetListOfTypes()->FindObject(nameoftype);

/// will return the TDataType corresponding to 'nameoftype'.  If the
/// TDataType is not already in the list itself and the type does exist,
/// a new TDataType will be created and added to the list.
/// Calling

gROOT->GetListOfTypes()->ls(); // or Print()

/// list only the typedefs that have been previously accessed through the
/// list (plus the builtins types).
```



<!-- TROOT.md ends here -->
