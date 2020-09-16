<!-- TFileMerger.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 日 1月  6 14:22:04 2019 (+0800)
;; Last-Updated: 三 9月 16 10:31:25 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TFileMerger*

```
This class provides file copy and merging services.

It can be used to copy files (not only ROOT files), using TFile or
any of its remote file access plugins. It is therefore useful in
a Grid environment where the files might be accessible via Castor,
rfio, dcap, etc.
The merging interface allows files containing histograms and trees
to be merged, like the standalone hadd program.
```


```cpp
class TFileMerger : public TObject
```

## class

```cpp
private:
   using TIOFeatures = ROOT::TIOFeatures;

   TFileMerger(const TFileMerger&) = delete;
   TFileMerger& operator=(const TFileMerger&) = delete;

protected:
   TStopwatch     fWatch;                     ///< Stop watch to measure file copy speed
   TList          fFileList;                  ///< A list the file (TFile*) which shall be merged
   TFile         *fOutputFile{nullptr};       ///< The outputfile for merging
   TString        fOutputFilename;            ///< The name of the outputfile for merging
   Bool_t         fFastMethod{kTRUE};         ///< True if using Fast merging algorithm (default)
   Bool_t         fNoTrees{kFALSE};           ///< True if Trees should not be merged (default is kFALSE)
   Bool_t         fExplicitCompLevel{kFALSE}; ///< True if the user explicitly requested a compressio level change (default kFALSE)
   Bool_t         fCompressionChange{kFALSE}; ///< True if the output and input have different compression level (default kFALSE)
   Int_t          fPrintLevel{0};             ///< How much information to print out at run time
   TString        fMergeOptions;              ///< Options (in string format) to be passed down to the Merge functions
   TIOFeatures   *fIOFeatures{nullptr};       ///< IO features to use in the output file.
   TString        fMsgPrefix{"TFileMerger"};  ///< Prefix to be used when printing informational message (default TFileMerger)

   Int_t          fMaxOpenedFiles;            ///< Maximum number of files opened at the same time by the TFileMerger
   Bool_t         fLocal;                     ///< Makes local copies of merging files if True (default is kTRUE)
   Bool_t         fHistoOneGo;                ///< Merger histos in one go (default is kTRUE)
   TString        fObjectNames;               ///< List of object names to be either merged exclusively or skipped
   TList          fMergeList;                 ///< list of TObjString containing the name of the files need to be merged
   TList          fExcessFiles;               ///<! List of TObjString containing the name of the files not yet added to fFileList due to user or system limitiation on the max number of files opened.

   Bool_t         OpenExcessFiles();/// Open up to fMaxOpenedFiles of the excess files.
   virtual Bool_t AddFile(TFile *source, Bool_t own, Bool_t cpProgress);
/// Add the TFile to this file merger and give ownership of the TFile to this
/// object (unless kFALSE is returned).
/// Return kTRUE if the addition was successful.
   
   virtual Bool_t MergeRecursive(TDirectory *target, TList *sourcelist, Int_t type = kRegular | kAll);
/// Merge all objects in a directory
/// The type is defined by the bit values in TFileMerger::EPartialMergeType.

public:
   /// Type of the partial merge
   enum EPartialMergeType {
      kRegular      = 0,             ///< Normal merge, overwritting the output file.
      kIncremental  = BIT(1),        ///< Merge the input file with the content of the output file (if already exising).
      kResetable    = BIT(2),        ///< Only the objects with a MergeAfterReset member function.
      kNonResetable = BIT(3),        ///< Only the objects without a MergeAfterReset member function.

      kAll            = BIT(2)|BIT(3),      ///< Merge all type of objects (default)
      kAllIncremental = kIncremental | kAll, ///< Merge incrementally all type of objects.

      kOnlyListed     = BIT(4),        ///< Only the objects specified in fObjectNames list
      kSkipListed     = BIT(5),        ///< Skip objects specified in fObjectNames list
      kKeepCompression= BIT(6)         ///< Keep compression level unchanged for each input files
   };

   TFileMerger(Bool_t isLocal = kTRUE, Bool_t histoOneGo = kTRUE);
   virtual ~TFileMerger();

   Int_t       GetPrintLevel() const { return fPrintLevel; }
   void        SetPrintLevel(Int_t level) { fPrintLevel = level; }
   Bool_t      HasCompressionChange() const { return fCompressionChange; }
   const char *GetOutputFileName() const { return fOutputFilename; }
   TList      *GetMergeList() { return &fMergeList; }
   TFile      *GetOutputFile() const { return fOutputFile; }
   Int_t       GetMaxOpenedFiles() const { return fMaxOpenedFiles; }
   void        SetMaxOpenedFiles(Int_t newmax);
/// Set a limit to the number of files that TFileMerger will open simultaneously.
/// If the request is higher than the system limit, we reset it to the system limit.
/// If the request is less than two, we reset it to 2 (one for the output file and one for the input file).   
   
   const char *GetMsgPrefix() const { return fMsgPrefix; }
   void        SetMsgPrefix(const char *prefix);/// Set the prefix to be used when printing informational message.
   const char *GetMergeOptions() { return fMergeOptions; }
   void        SetMergeOptions(const TString &options) { fMergeOptions = options; }
   void        SetMergeOptions(const std::string_view &options) { fMergeOptions = options; }
   void        SetIOFeatures(ROOT::TIOFeatures &features) { fIOFeatures = &features; }
   void        AddObjectNames(const char *name) {fObjectNames += name; fObjectNames += " ";}
   const char *GetObjectNames() const {return fObjectNames.Data();}
   void        ClearObjectNames() {fObjectNames.Clear();}

    //--- file management interface
   virtual Bool_t SetCWD(const char * /*path*/) { MayNotUse("SetCWD"); return kFALSE; }
   virtual const char *GetCWD() { MayNotUse("GetCWD"); return 0; }

   //--- file merging interface
   virtual void   Reset();/// Reset merger file list.
   virtual Bool_t AddFile(const char *url, Bool_t cpProgress = kTRUE);
/// Add file to file merger.   
   
   virtual Bool_t AddFile(TFile *source, Bool_t cpProgress = kTRUE);
/// Add the TFile to this file merger and *do not* give ownership of the TFile to this
/// object.
/// Return kTRUE if the addition was successful.   
   
   virtual Bool_t AddAdoptFile(TFile *source, Bool_t cpProgress = kTRUE);
/// Add the TFile to this file merger and give ownership of the TFile to this
/// object (unless kFALSE is returned).
/// Return kTRUE if the addition was successful.   
   
   virtual Bool_t OutputFile(const char *url, Bool_t force);/// Open merger output file.
   virtual Bool_t OutputFile(const char *url, Bool_t force, Int_t compressionLevel);/// Open merger output file.
   virtual Bool_t OutputFile(const char *url, const char *mode = "RECREATE");
/// Open merger output file.  'mode' is passed to the TFile constructor as the option, it should
/// be one of 'NEW','CREATE','RECREATE','UPDATE'
/// 'UPDATE' is usually used in conjunction with IncrementalMerge.   
   
   virtual Bool_t OutputFile(const char *url, const char *mode, Int_t compressionLevel);
/// Open merger output file.
/// The 'mode' parameter is passed to the TFile constructor as the option, it
/// should be one of 'NEW','CREATE','RECREATE','UPDATE'
/// 'UPDATE' is usually used in conjunction with IncrementalMerge.   
   
   virtual Bool_t OutputFile(std::unique_ptr<TFile> file);/// Set an output file opened externally by the users
   virtual void   PrintFiles(Option_t *options);/// Print list of files being merged.
   virtual Bool_t Merge(Bool_t = kTRUE);
/// Merge the files.
/// If no output file was specified it will write into
/// the file "FileMerger.root" in the working directory. Returns true
/// on success, false in case of error.   
   
   virtual Bool_t PartialMerge(Int_t type = kAll | kIncremental);
/// Merge the files. If no output file was specified it will write into
/// the file "FileMerger.root" in the working directory. Returns true
/// on success, false in case of error.
/// The type is defined by the bit values in EPartialMergeType:
///   kRegular      : normal merge, overwritting the output file
///   kIncremental  : merge the input file with the content of the output file (if already exising) (default)
///   kAll          : merge all type of objects (default)
///   kResetable    : merge only the objects with a MergeAfterReset member function.
///   kNonResetable : merge only the objects without a MergeAfterReset member function.
/// If the type is set to kIncremental the output file is done deleted at the end of
/// this operation.  If the type is not set to kIncremental, the output file is closed.   
   
   virtual void   SetFastMethod(Bool_t fast=kTRUE)  {fFastMethod = fast;}
   virtual void   SetNotrees(Bool_t notrees=kFALSE) {fNoTrees = notrees;}
   virtual void        RecursiveRemove(TObject *obj);/// Intercept the case where the output TFile is deleted!
```


<!-- TFileMerger.md ends here -->
