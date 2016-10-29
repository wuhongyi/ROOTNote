<!-- TFile.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 11:38:01 2014 (+0800)
;; Last-Updated: 六 10月 29 20:55:44 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 20
;; URL: http://wuhongyi.cn -->

# TFile


继承TDirectoryFile

A ROOT file is a suite of consecutive data records (TKey instances) with
a well defined format.

If the key is located past the 32 bit file limit (> 2 GB) then some fields will
be 8 instead of 4 bytes:

```
Byte Range      | Member Name | Description
----------------|-----------|--------------
1->4            | Nbytes    | Length of compressed object (in bytes)
5->6            | Version   | TKey version identifier
7->10           | ObjLen    | Length of uncompressed object
11->14          | Datime    | Date and time when object was written to file
15->16          | KeyLen    | Length of the key structure (in bytes)
17->18          | Cycle     | Cycle of key
19->22 [19->26] | SeekKey   | Pointer to record itself (consistency check)
23->26 [27->34] | SeekPdir  | Pointer to directory header
27->27 [35->35] | lname     | Number of bytes in the class name
28->.. [36->..] | ClassName | Object Class Name
..->..          | lname     | Number of bytes in the object name
..->..          | Name      | lName bytes with the name of the object
..->..          | lTitle    | Number of bytes in the object title
..->..          | Title     | Title of the object
----->          | DATA      | Data bytes associated to the object
```

The first data record starts at byte fBEGIN (currently set to kBEGIN).
Bytes 1->kBEGIN contain the file description, when fVersion >= 1000000
it is a large file (> 2 GB) and the offsets will be 8 bytes long and
fUnits will be set to 8:

```
Byte Range      | Record Name | Description
----------------|-------------|------------
1->4            | "root"      | Root file identifier
5->8            | fVersion    | File format version
9->12           | fBEGIN      | Pointer to first data record
13->16 [13->20] | fEND        | Pointer to first free word at the EOF
17->20 [21->28] | fSeekFree   | Pointer to FREE data record
21->24 [29->32] | fNbytesFree | Number of bytes in FREE data record
25->28 [33->36] | nfree       | Number of free data records
29->32 [37->40] | fNbytesName | Number of bytes in TNamed at creation time
33->33 [41->41] | fUnits      | Number of bytes for file pointers
34->37 [42->45] | fCompress   | Compression level and algorithm
38->41 [46->53] | fSeekInfo   | Pointer to TStreamerInfo record
42->45 [54->57] | fNbytesInfo | Number of bytes in TStreamerInfo record
46->63 [58->75] | fUUID       | Universal Unique ID
```

```
/// A ROOT file is designed such that one can write in the file in pure
/// sequential mode (case of BATCH jobs). In this case, the file may be
/// read sequentially again without using the file index written
/// at the end of the file. In case of a job crash, all the information
/// on the file is therefore protected.
/// A ROOT file can be used interactively. In this case, one has the
/// possibility to delete existing objects and add new ones.
/// When an object is deleted from the file, the freed space is added
/// into the FREE linked list (fFree). The FREE list consists of a chain
/// of consecutive free segments on the file. At the same time, the first
/// 4 bytes of the freed record on the file are overwritten by GAPSIZE
/// where GAPSIZE = -(Number of bytes occupied by the record).
/// Option compress is used to specify the compression level and algorithm:
///
///     compress = 100 * algorithm + level
///
/// Level | Explanation
/// ------|-------------
/// 0   | objects written to this file will not be compressed.
/// 1   | minimal compression level but fast.
/// ... | ....
/// 9   | maximal compression level but slower and might use more memory.
/// (For the currently supported algorithms, the maximum level is 9)
/// If compress is negative it indicates the compression level is not set yet.
/// The enumeration ROOT::ECompressionAlgorithm associates each
/// algorithm with a number. There is a utility function to help
/// to set the value of compress. For example,
///     ROOT::CompressionSettings(ROOT::kLZMA, 1)
/// will build an integer which will set the compression to use
/// the LZMA algorithm and compression level 1.  These are defined
/// in the header file <em>Compression.h</em>.
/// Note that the compression settings may be changed at any time.
/// The new compression settings will only apply to branches created
/// or attached after the setting is changed and other objects written
/// after the setting is changed.
```


## class


```cpp
   /// TFile status bits. BIT(13) is taken up by TObject
   enum EStatusBits {
      kRecovered     = BIT(10),
      kHasReferences = BIT(11),
      kDevNull       = BIT(12),
      kWriteError    = BIT(14),
      kBinaryFile    = BIT(15),
      kRedirected    = BIT(16)
   };
   enum ERelativeTo { kBeg = 0, kCur = 1, kEnd = 2 };
   enum { kStartBigFile  = 2000000000 };
   /// File type
   enum EFileType { kDefault = 0, kLocal = 1, kNet = 2, kWeb = 3, kFile = 4, kMerge = 5};

   TFile();

   /// \param[in] fname1 The name of the file
   /// \param[in] option Specifies the mode in which the file is opened
   /// \param[in] ftitle The title of the file
   /// \param[in] compress Specifies the compression algorithm and level
   ///
   /// will be used by object browsers to automatically identify the file as
   /// a ROOT file. If the constructor fails in any way IsZombie() will
   /// return true. Use IsOpen() to check if the file is (still) open.
   /// To open non-local files use the static TFile::Open() method, that
   /// will take care of opening the files using the correct remote file
   /// access plugin.
   ///
   /// Option | Description
   /// -------|------------
   /// NEW or CREATE | Create a new file and open it for writing, if the file already exists the file is not opened.
   /// RECREATE      | Create a new file, if the file already exists it will be overwritten.
   /// UPDATE        | Open an existing file for writing. If no file exists, it is created.
   /// READ          | Open an existing file for reading (default).
   /// NET           | Used by derived remote file access classes, not a user callable option.
   /// WEB           | Used by derived remote http access class, not a user callable option.
   TFile(const char *fname, Option_t *option="", const char *ftitle="", Int_t compress=1);


   virtual ~TFile();
   virtual void        Close(Option_t *option=""); // *MENU*
/// Close a file.
/// \param[in] option If option == "R", all TProcessIDs referenced by this file are deleted.
/// Calling TFile::Close("R") might be necessary in case one reads a long list
/// of files having TRef, writing some of the referenced objects or TRef
/// to a new file. If the TRef or referenced objects of the file being closed
/// will not be referenced again, it is possible to minimize the size
/// of the TProcessID data structures in memory by forcing a delete of
/// the unused TProcessID.

   virtual void        Copy(TObject &) const { MayNotUse("Copy(TObject &)"); }
   virtual Bool_t      Cp(const char *dst, Bool_t progressbar = kTRUE,UInt_t buffersize = 1000000);
/// Allows to copy this file to the dst URL. Returns kTRUE in case of success,
/// kFALSE otherwise.

   virtual TKey*       CreateKey(TDirectory* mother, const TObject* obj, const char* name, Int_t bufsize);
/// Creates key for object and converts data to buffer.

   virtual TKey*       CreateKey(TDirectory* mother, const void* obj, const TClass* cl,
                                 const char* name, Int_t bufsize);
/// Creates key for object and converts data to buffer.

   static TFile      *&CurrentFile(); // Return the current file for this thread.
/// Return the current ROOT file if any.
/// Note that if 'cd' has been called on a TDirectory that does not belong to a file,
/// gFile will be unchanged and still points to the file of the previous current
/// directory that was a file.

   virtual void        Delete(const char *namecycle="");
/// Delete object namecycle.
/// \param[in] namecycle Encodes the name and cycle of the objects to delete
/// Namecycle identifies an object in the top directory of the file namecycle
/// has the format <em>name;cycle</em>.
///   - <em>name  = *</em> means all objects
///   - <em>cycle = *</em> means all cycles (memory and keys)
///   - <em>cycle = ""</em> or cycle = 9999 ==> apply to a memory object
/// When name=* use T* to delete subdirectories also
///
/// Examples:
/// name/cycle | Action
/// -----------|-------
/// foo   | delete object named foo in memory
/// foo;1 | delete cycle 1 of foo on file
/// foo;* | delete all cycles of foo on disk and also from memory
/// *;2   | delete all objects on file having the cycle 2
/// *;*   | delete all objects from memory and file
/// T*;*  | delete all objects from memory and file and all subdirectories

   virtual void        Draw(Option_t *option="");
/// Fill Graphics Structure and Paint.
/// Loop on all objects (memory or file) and all subdirectories.

   virtual void        DrawMap(const char *keys="*",Option_t *option=""); // *MENU*
/// Draw map of objects in this file.

   virtual void        FillBuffer(char *&buffer);
/// Encode file output buffer.
/// The file output buffer contains only the FREE data record.

   virtual void        Flush();
/// Synchronize a file's in-memory and on-disk states.

   TArchiveFile       *GetArchive() const { return fArchive; }
   Long64_t            GetArchiveOffset() const { return fArchiveOffset; }
   Int_t               GetBestBuffer() const;
/// Return the best buffer size of objects on this file.
/// The best buffer size is estimated based on the current mean value
/// and standard deviation of all objects written so far to this file.
/// Returns mean value + one standard deviation.

   virtual Int_t       GetBytesToPrefetch() const;
/// Max number of bytes to prefetch.
/// By default this is 75% of the
/// read cache size. But specific TFile implementations may need to change it

   TFileCacheRead     *GetCacheRead(TObject* tree = 0) const;
   TFileCacheWrite    *GetCacheWrite() const;
   TArrayC            *GetClassIndex() const { return fClassIndex; }
   Int_t               GetCompressionAlgorithm() const;
   Int_t               GetCompressionLevel() const;
   Int_t               GetCompressionSettings() const;
   Float_t             GetCompressionFactor();
/// Return the file compression factor.
/// Add total number of compressed/uncompressed bytes for each key.
/// Returns the ratio of the two.

   virtual Long64_t    GetEND() const { return fEND; }
   virtual Int_t       GetErrno() const;
   virtual void        ResetErrno() const;
   Int_t               GetFd() const { return fD; }
   virtual const TUrl *GetEndpointUrl() const { return &fUrl; }
   TObjArray          *GetListOfProcessIDs() const {return fProcessIDs;}
   TList              *GetListOfFree() const { return fFree; }
   virtual Int_t       GetNfree() const { return fFree->GetSize(); }
   virtual Int_t       GetNProcessIDs() const { return fNProcessIDs; }
   Option_t           *GetOption() const { return fOption.Data(); }
   virtual Long64_t    GetBytesRead() const { return fBytesRead; }
   virtual Long64_t    GetBytesReadExtra() const { return fBytesReadExtra; }
   virtual Long64_t    GetBytesWritten() const;
/// Return the total number of bytes written so far to the file.

   virtual Int_t       GetReadCalls() const { return fReadCalls; }
   Int_t               GetVersion() const { return fVersion; }
   Int_t               GetRecordHeader(char *buf, Long64_t first, Int_t maxbytes,
                                       Int_t &nbytes, Int_t &objlen, Int_t &keylen);
/// Read the logical record header starting at a certain postion.
/// \param[in] maxbytes Bytes which are read into buf.
/// \param[out] nbytes Number of bytes in record if negative, this is a deleted
/// record if 0, cannot read record, wrong value of argument first
/// \param[out] objlen Uncompressed object size
/// \param[out] keylen Length of logical record header
/// The function reads nread bytes
/// where nread is the minimum of maxbytes and the number of bytes
/// before the end of file. The function returns nread.
/// Note that the arguments objlen and keylen are returned only
/// if maxbytes >=16

   virtual Int_t       GetNbytesInfo() const {return fNbytesInfo;}
   virtual Int_t       GetNbytesFree() const {return fNbytesFree;}
   virtual TString     GetNewUrl() { return ""; }
   Long64_t            GetRelOffset() const { return fOffset - fArchiveOffset; }
   virtual Long64_t    GetSeekFree() const {return fSeekFree;}
   virtual Long64_t    GetSeekInfo() const {return fSeekInfo;}
   virtual Long64_t    GetSize() const;
/// Returns the current file size. Returns -1 in case the file could not
/// be stat'ed.

   virtual TList      *GetStreamerInfoList();
/// Read the list of TStreamerInfo objects written to this file.
/// The function returns a TList. It is the user's responsibility
/// to delete the list created by this function.

   const   TList      *GetStreamerInfoCache();
   virtual void        IncrementProcessIDs() { fNProcessIDs++; }
   virtual Bool_t      IsArchive() const { return fIsArchive; }
           Bool_t      IsBinary() const { return TestBit(kBinaryFile); }
           Bool_t      IsRaw() const { return !fIsRootFile; }
   virtual Bool_t      IsOpen() const;
   virtual void        ls(Option_t *option="") const;
/// List file contents.
/// Indentation is used to identify the file tree.
/// Subdirectories are listed first, then objects in memory,
/// then objects on the file.

   virtual void        MakeFree(Long64_t first, Long64_t last);
/// Mark unused bytes on the file.
/// The list of free segments is in the fFree linked list.
/// When an object is deleted from the file, the freed space is added
/// into the FREE linked list (fFree). The FREE list consists of a chain
/// of consecutive free segments on the file. At the same time, the first
/// 4 bytes of the freed record on the file are overwritten by GAPSIZE
/// where GAPSIZE = -(Number of bytes occupied by the record).

   virtual void        MakeProject(const char *dirname, const char *classes="*",
                                   Option_t *option="new"); // *MENU*
/// Generate source code necessary to access the objects stored in the file.
/// Generate code in directory dirname for all classes specified in
/// argument classes If classes = "*" (default and currently the
/// only supported value), the function generates an include file
/// for each class in the StreamerInfo list for which a TClass
/// object does not exist.
///
/// The code generated includes:
///   - dirnameProjectHeaders.h, which contains one #include statement per generated header file
///   - dirnameProjectSource.cxx,which contains all the constructors and destructors implementation.
/// and one header per class that is not nested inside another class.
/// The header file name is the fully qualified name of the class after all the special characters
/// "<>,:" are replaced by underscored.  For example for std::pair<edm::Vertex,int> the file name is
/// pair_edm__Vertex_int_.h
///
/// In the generated classes, map, multimap when the first template parameter is a class
/// are replaced by a vector of pair. set and multiset when the tempalte parameter
/// is a class are replaced by a vector. This is required since we do not have the
/// code needed to order and/or compare the object of the classes.
/// This is a quick explanation of the options available:
/// Option | Details
/// -------|--------
/// new (default) | A new directory dirname is created. If dirname already exist, an error message is printed and the function returns.
/// recreate      | If dirname does not exist, it is created (like in "new"). If dirname already exist, all existing files in dirname are deleted before creating the new files.
/// update        | New classes are added to the existing directory. Existing classes with the same name are replaced by the new definition. If the directory dirname doest not exist, same effect as "new".
/// genreflex     | Use genreflex rather than rootcint to generate the dictionary.
/// par           | Create a PAR file with the minimal set of code needed to read the content of the ROOT file. The name of the PAR file is basename(dirname), with extension '.par' enforced; the PAR file will be created at dirname(dirname).
///
/// If, in addition to one of the 3 above options, the option "+" is specified,
/// the function will generate:
///   - a script called MAKEP to build the shared lib
///   - a dirnameLinkDef.h file
///   - rootcint will be run to generate a dirnameProjectDict.cxx file
///   - dirnameProjectDict.cxx will be compiled with the current options in compiledata.h
///   - a shared lib dirname.so will be created.
/// If the option "++" is specified, the generated shared lib is dynamically
/// linked with the current executable module.
/// If the option "+" and "nocompile" are specified, the utility files are generated
/// as in the option "+" but they are not executed.
/// Example:
///  file.MakeProject("demo","*","recreate++");
///   - creates a new directory demo unless it already exist
///   - clear the previous directory content
///   - generate the xxx.h files for all classes xxx found in this file
///    and not yet known to the CINT dictionary.
///   - creates the build script MAKEP
///   - creates a LinkDef.h file
///   - runs rootcint generating demoProjectDict.cxx
///   - compiles demoProjectDict.cxx into demoProjectDict.o
///   - generates a shared lib demo.so
///   - dynamically links the shared lib demo.so to the executable
///  If only the option "+" had been specified, one can still link the
///  shared lib to the current executable module with:
///      gSystem->load("demo/demo.so");
/// The following feature is not yet enabled:
/// One can restrict the list of classes to be generated by using expressions like:
///
///     classes = "Ali*" generate code only for classes starting with Ali
///     classes = "myClass" generate code for class MyClass only.

   virtual void        Map(); // *MENU*
   virtual Bool_t      Matches(const char *name);
/// Return kTRUE if 'url' matches the coordinates of this file.
/// The check is implementation dependent and may need to be overload
/// by each TFile implementation relying on this check.
/// The default implementation checks the file name only.

   virtual Bool_t      MustFlush() const {return fMustFlush;}
   virtual void        Paint(Option_t *option="");
/// Paint all objects in the file.

   virtual void        Print(Option_t *option="") const;
/// Print all objects in the file.

   virtual Bool_t      ReadBufferAsync(Long64_t offs, Int_t len);
   virtual Bool_t      ReadBuffer(char *buf, Int_t len);
/// Read a buffer from the file. This is the basic low level read operation.
/// Returns kTRUE in case of failure.

   virtual Bool_t      ReadBuffer(char *buf, Long64_t pos, Int_t len);
/// Read a buffer from the file at the offset 'pos' in the file.
/// Returns kTRUE in case of failure.
/// Compared to ReadBuffer(char*, Int_t), this routine does _not_
/// change the cursor on the physical file representation (fD)
/// if the data is in this TFile's cache.

   virtual Bool_t      ReadBuffers(char *buf, Long64_t *pos, Int_t *len, Int_t nbuf);
/// Read the nbuf blocks described in arrays pos and len.
/// The value pos[i] is the seek position of block i of length len[i].
/// Note that for nbuf=1, this call is equivalent to TFile::ReafBuffer.
/// This function is overloaded by TNetFile, TWebFile, etc.
/// Returns kTRUE in case of failure.

   virtual void        ReadFree();
/// Read the FREE linked list.
/// Every file has a linked list (fFree) of free segments.
/// This linked list has been written on the file via WriteFree
/// as a single data record.

   virtual TProcessID *ReadProcessID(UShort_t pidf);
/// The TProcessID with number pidf is read from this file.
/// If the object is not already entered in the gROOT list, it is added.

   virtual void        ReadStreamerInfo();
/// Read the list of StreamerInfo from this file.
/// The key with name holding the list of TStreamerInfo objects is read.
/// The corresponding TClass objects are updated.
/// Note that this function is not called if the static member fgReadInfo is false.
/// (see TFile::SetReadStreamerInfo)

   virtual Int_t       Recover();
/// Attempt to recover file if not correctly closed
/// The function returns the number of keys that have been recovered.
/// If no keys can be recovered, the file will be declared Zombie by
/// the calling function. This function is automatically called when
/// opening a file.
/// If the file is open in read only mode, the file is not modified.
/// If open in update mode and the function finds something to recover,
/// a new directory header is written to the file. When opening the file gain
/// no message from Recover will be reported.
/// If keys have been recovered, the file is usable and you can safely
/// read the corresponding objects.
/// If the file is not usable (a zombie), you can test for this case
/// with code like:
/// ~~~{.cpp}
/// TFile f("myfile.root");
/// if (f.IsZombie()) {<actions to take if file is unusable>}
/// ~~~
/// If the file has been recovered, the bit kRecovered is set in the TFile object in memory.
/// You can test if the file has been recovered with
///     if (f.TestBit(TFile::kRecovered)) {... the file has been recovered}
/// When writing TTrees to a file, it is important to save the Tree header
/// at regular intervals (see TTree::AutoSave). If a file containing a Tree
/// is recovered, the last Tree header written to the file will be used.
/// In this case all the entries in all the branches written before writing
/// the header are valid entries.
/// One can disable the automatic recovery procedure by setting
///     TFile.Recover 0
/// in the system.rootrc file.

   virtual Int_t       ReOpen(Option_t *mode);
/// Reopen a file with a different access mode.
/// For example, it is possible to change from READ to
/// UPDATE or from NEW, CREATE, RECREATE, UPDATE to READ. Thus the
/// mode argument can be either "READ" or "UPDATE". The method returns
/// 0 in case the mode was successfully modified, 1 in case the mode
/// did not change (was already as requested or wrong input arguments)
/// and -1 in case of failure, in which case the file cannot be used
/// anymore. The current directory (gFile) is changed to this file.

   virtual void        Seek(Long64_t offset, ERelativeTo pos = kBeg);
/// Seek to a specific position in the file. Pos it either kBeg, kCur or kEnd.

   virtual void        SetCacheRead(TFileCacheRead *cache, TObject* tree = 0, ECacheAction action = kDisconnect);
/// Set a pointer to the read cache.
/// This relinquishes ownership</b> of the previous cache, so if you do not
/// already have a pointer to the previous cache (and there was a previous
/// cache), you ought to retrieve (and delete it if needed) using:
///     TFileCacheRead *older = myfile->GetCacheRead();
/// The action specifies how to behave when detaching a cache from the
/// the TFile.  If set to (default) kDisconnect, the contents of the cache
/// will be flushed when it is removed from the file, and it will disconnect
/// the cache object from the file.  In almost all cases, this is what you want.
/// If you want to disconnect the cache temporarily from this tree and re-attach
/// later to the same fil, you can set action to kDoNotDisconnect.  This will allow
/// things like prefetching to continue in the background while it is no longer the
/// default cache for the TTree.  Except for a few expert use cases, kDisconnect is
/// likely the correct setting.
/// WARNING: if action=kDoNotDisconnect, you MUST delete the cache before TFile.

   virtual void        SetCacheWrite(TFileCacheWrite *cache);
/// Set a pointer to the write cache.
/// If file is null the existing write cache is deleted.

   virtual void        SetCompressionAlgorithm(Int_t algorithm=0);
/// See comments for function SetCompressionSettings

   virtual void        SetCompressionLevel(Int_t level=1);
/// See comments for function SetCompressionSettings

   virtual void        SetCompressionSettings(Int_t settings=1);
/// Used to specify the compression level and algorithm.
/// See the TFile constructor for the details.

   virtual void        SetEND(Long64_t last) { fEND = last; }
   virtual void        SetOffset(Long64_t offset, ERelativeTo pos = kBeg);
/// Set position from where to start reading.

   virtual void        SetOption(Option_t *option=">") { fOption = option; }
   virtual void        SetReadCalls(Int_t readcalls = 0) { fReadCalls = readcalls; }
   virtual void        ShowStreamerInfo();
/// Show the StreamerInfo of all classes written to this file.

   virtual Int_t       Sizeof() const;
   void                SumBuffer(Int_t bufsize);
   virtual Bool_t      WriteBuffer(const char *buf, Int_t len);
/// Write a buffer to the file. This is the basic low level write operation.
/// Returns kTRUE in case of failure.

   virtual Int_t       Write(const char *name=0, Int_t opt=0, Int_t bufsiz=0);
/// Write memory objects to this file.
/// Loop on all objects in memory (including subdirectories).
/// A new key is created in the KEYS linked list for each object.
/// The list of keys is then saved on the file (via WriteKeys)
/// as a single data record.
/// For values of opt see TObject::Write().
/// The directory header info is rewritten on the directory header record.
/// The linked list of FREE segments is written.
/// The file header is written (bytes 1->fBEGIN).

   virtual Int_t       Write(const char *name=0, Int_t opt=0, Int_t bufsiz=0) const;
   virtual void        WriteFree();
/// Write FREE linked list on the file.
/// The linked list of FREE segments (fFree) is written as a single data
/// record.

   virtual void        WriteHeader();
/// Write File Header.

   virtual UShort_t    WriteProcessID(TProcessID *pid);
/// Check if the ProcessID pidd is already in the file,
/// if not, add it and return the index  number in the local file list.

   virtual void        WriteStreamerInfo();
/// Write the list of TStreamerInfo as a single object in this file
/// The class Streamer description for all classes written to this file
/// is saved. See class TStreamerInfo.

   static TFileOpenHandle
                      *AsyncOpen(const char *name, Option_t *option = "",
                                 const char *ftitle = "", Int_t compress = 1,
                                 Int_t netopt = 0);
/// Submit an asynchronous open request.
/// See TFile::Open(const char *, ...) for an
/// explanation of the arguments. A handler is returned which is to be passed
/// to TFile::Open(TFileOpenHandle *) to get the real TFile instance once
/// the file is open.
/// This call never blocks and it is provided to allow parallel submission
/// of file opening operations expected to take a long time.
/// TFile::Open(TFileOpenHandle *) may block if the file is not yet ready.
/// The sequence
///     TFile::Open(TFile::AsyncOpen(const char *, ...))
/// is equivalent to
///     TFile::Open(const char *, ...)
/// To be effective, the underlying TFile implementation must be able to
/// support asynchronous open functionality. Currently, only TXNetFile
/// supports it. If the functionality is not implemented, this call acts
/// transparently by returning an handle with the arguments for the
/// standard synchronous open run by TFile::Open(TFileOpenHandle *).
/// The retuned handle will be adopted by TFile after opening completion
/// in TFile::Open(TFileOpenHandle *); if opening is not finalized the
/// handle must be deleted by the caller.

   static TFile       *Open(const char *name, Option_t *option = "",
                            const char *ftitle = "", Int_t compress = 1,
                            Int_t netopt = 0);
/// Create / open a file
/// The type of the file can be either a
/// TFile, TNetFile, TWebFile or any TFile derived class for which an
/// plugin library handler has been registered with the plugin manager
/// (for the plugin manager see the TPluginManager class). The returned
/// type of TFile depends on the file name specified by 'url'.
/// If 'url' is a '|'-separated list of file URLs, the 'URLs' are tried
/// sequentially in the specified order until a successful open.
/// If the file starts with "root:", "roots:" or "rootk:" a TNetFile object
/// will be returned, with "http:" a TWebFile, with "file:" a local TFile,
/// etc. (see the list of TFile plugin handlers in $ROOTSYS/etc/system.rootrc
/// for regular expressions that will be checked) and as last a local file will
/// be tried.
/// Before opening a file via TNetFile a check is made to see if the URL
/// specifies a local file. If that is the case the file will be opened
/// via a normal TFile. To force the opening of a local file via a
/// TNetFile use either TNetFile directly or specify as host "localhost".
/// The netopt argument is only used by TNetFile. For the meaning of the
/// options and other arguments see the constructors of the individual
/// file classes. In case of error returns 0.
/// For TFile implementations supporting asynchronous file open, see
/// TFile::AsyncOpen(...), it is possible to request a timeout with the
/// option <b>TIMEOUT=<secs></b>: the timeout must be specified in seconds and
/// it will be internally checked with granularity of one millisec.
/// For remote files there is the option: <b>CACHEREAD</b> opens an existing
/// file for reading through the file cache. The file will be downloaded to
/// the cache and opened from there. If the download fails, it will be opened remotely.
/// The file will be downloaded to the directory specified by SetCacheFileDir().

   static TFile       *Open(TFileOpenHandle *handle);
/// Waits for the completion of an asynchronous open request.
/// Returns the pointer to the associated TFile, transferring ownership of the
/// handle to the TFile instance.

   static EFileType    GetType(const char *name, Option_t *option = "", TString *prefix = 0);
/// Resolve the file type as a function of the protocol field in 'name'
/// If defined, the string 'prefix' is added when testing the locality of
/// a 'name' with network-like structure (i.e. root://host//path); if the file
/// is local, on return 'prefix' will contain the actual local path of the file.

   static EAsyncOpenStatus GetAsyncOpenStatus(const char *name);
/// Get status of the async open request related to 'name'.

   static EAsyncOpenStatus GetAsyncOpenStatus(TFileOpenHandle *handle);
/// Get status of the async open request related to 'handle'.

   static const TUrl  *GetEndpointUrl(const char *name);
/// Get final URL for file being opened asynchronously.
/// Returns 0 is the information is not yet available.

   static Long64_t     GetFileBytesRead();
   static Long64_t     GetFileBytesWritten();
/// Static function returning the total number of bytes written to all files.
/// Does not take into account what might still be in the write caches.

   static Int_t        GetFileReadCalls();
/// Static function returning the total number of read calls from all files.

   static Int_t        GetReadaheadSize();
/// Static function returning the readahead buffer size.

   static void         SetFileBytesRead(Long64_t bytes = 0);
   static void         SetFileBytesWritten(Long64_t bytes = 0);
   static void         SetFileReadCalls(Int_t readcalls = 0);
   static void         SetReadaheadSize(Int_t bufsize = 256000);
   static void         SetReadStreamerInfo(Bool_t readinfo=kTRUE);
/// Specify if the streamerinfos must be read at file opening.
/// If fgReadInfo is true (default) TFile::ReadStreamerInfo is called
///  when opening the file.
/// It may be interesting to set fgReadInfo to false to speedup the file
/// opening time or in case libraries containing classes referenced
/// by the file have not yet been loaded.
/// if fgReadInfo is false, one can still read the StreamerInfo with
///    myfile.ReadStreamerInfo();

   static Bool_t       GetReadStreamerInfo();
/// If the streamerinfos are to be read at file opening.
/// See TFile::SetReadStreamerInfo for more documentation.

   static Long64_t     GetFileCounter();
   static void         IncrementFileCounter();

   static Bool_t       SetCacheFileDir(const char *cacheDir, Bool_t operateDisconnected = kTRUE,
                                       Bool_t forceCacheread = kFALSE);
/// Sets the directory where to locally stage/cache remote files.
/// If the directory is not writable by us return kFALSE.

   static const char  *GetCacheFileDir();
/// Get the directory where to locally stage/cache remote files.

   static Bool_t       ShrinkCacheFileDir(Long64_t shrinkSize, Long_t cleanupInteval = 0);
/// Try to shrink the cache to the desired size.
/// With the clenupinterval you can specify the minimum amount of time after
/// the previous cleanup before the cleanup operation is repeated in
/// the cache directory

   static Bool_t       Cp(const char *src, const char *dst, Bool_t progressbar = kTRUE,
                          UInt_t buffersize = 1000000);
/// Allows to copy file from src to dst URL. Returns kTRUE in case of success,
/// kFALSE otherwise.

   static UInt_t       SetOpenTimeout(UInt_t timeout);  // in ms
/// Sets open timeout time (in ms). Returns previous timeout value.

   static UInt_t       GetOpenTimeout(); // in ms
/// Returns open timeout (in ms).

   static Bool_t       SetOnlyStaged(Bool_t onlystaged);
   static Bool_t       GetOnlyStaged();
```

## code

```cpp
//打开文件
TFile f("demo.root");
if (f.IsZombie()) {
cout << "Error opening file" << endl;
exit(-1);} 
else {
 .....
 }
 ```


```cpp
//多个cycle时候读取某一部分数据
TTree *tt;
gFile->GetObject("NameOfTree;1",tt)

```

```cpp
//Saving/Reading Histograms to/from a File
//The following statements create a ROOT file and store a histogram on the file. Because TH1 derives from TNamed , the key identifier on the file is the histogram name:
TFile f("histos.root","new");
TH1F h1("hgaus","histo from a gaussian",100,-3,3);
h1.FillRandom("gaus",10000);
h1->Write();
//To read this histogram in another ROOT session, do:
TFile f("histos.root");
TH1F *h = (TH1F*)f.Get("hgaus");
One can save all histograms in memory to the file by:
file->Write();
For a more detailed explanation, see “Input/Output”.


TTree *fChain = (TTree*)gFile->Get("t");
Long64_t nentries = fChain->GetEntriesFast(); 
```




```cpp
/// If the file is not usable (a zombie), you can test for this case
/// with code like:
TFile f("myfile.root");
if (f.IsZombie()) {/*<actions to take if file is unusable>*/}

/// If the file has been recovered, the bit kRecovered is set in the TFile object in memory.
/// You can test if the file has been recovered with
if (f.TestBit(TFile::kRecovered)) {/*... the file has been recovered*/}
```

```cpp
// function  File::Map()

/// List the contents of a file sequentially.
/// For each logical record found, it prints:
///
///     Date/Time  Record_Adress Logical_Record_Length  ClassName  CompressionFactor
///
/// Example of output
///
///     20010404/150437  At:64        N=150       TFile
///     20010404/150440  At:214       N=28326     TBasket        CX =  1.13
///     20010404/150440  At:28540     N=29616     TBasket        CX =  1.08
///     20010404/150440  At:58156     N=29640     TBasket        CX =  1.08
///     20010404/150440  At:87796     N=29076     TBasket        CX =  1.10
///     20010404/150440  At:116872    N=10151     TBasket        CX =  3.15
///     20010404/150441  At:127023    N=28341     TBasket        CX =  1.13
///     20010404/150441  At:155364    N=29594     TBasket        CX =  1.08
///     20010404/150441  At:184958    N=29616     TBasket        CX =  1.08
///     20010404/150441  At:214574    N=29075     TBasket        CX =  1.10
///     20010404/150441  At:243649    N=9583      TBasket        CX =  3.34
///     20010404/150442  At:253232    N=28324     TBasket        CX =  1.13
///     20010404/150442  At:281556    N=29641     TBasket        CX =  1.08
///     20010404/150442  At:311197    N=29633     TBasket        CX =  1.08
///     20010404/150442  At:340830    N=29091     TBasket        CX =  1.10
///     20010404/150442  At:369921    N=10341     TBasket        CX =  3.09
///     20010404/150442  At:380262    N=509       TH1F           CX =  1.93
///     20010404/150442  At:380771    N=1769      TH2F           CX =  4.32
///     20010404/150442  At:382540    N=1849      TProfile       CX =  1.65
///     20010404/150442  At:384389    N=18434     TNtuple        CX =  4.51
///     20010404/150442  At:402823    N=307       KeysList
///     20010404/150443  At:403130    N=4548      StreamerInfo   CX =  3.65
///     20010404/150443  At:407678    N=86        FreeSegments
///     20010404/150443  At:407764    N=1         END
```


```cpp
// function TFile::GetStreamerInfoList()

/// Read the list of TStreamerInfo objects written to this file.
/// The function returns a TList. It is the user's responsibility
/// to delete the list created by this function.
/// Using the list, one can access additional information, e.g.:

TFile f("myfile.root");
auto list = f.GetStreamerInfoList();
auto info = (TStreamerInfo*)list->FindObject("MyClass");
auto classversionid = info->GetClassVersion();
delete list;
```


## example

```cpp
//文本读取数据存ROOT文件：
#include "Riostream.h"
void basic() {
//  Read data from an ascii file and create a root file with an histogram and an ntuple.
// this file has 3 columns of float data
   TString dir = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
   std::cout<<dir<<std::endl;
   dir.ReplaceAll("basic.C","");
   dir.ReplaceAll("/./","/");std::cout<<dir<<std::endl;//当前目录路径

   ifstream in;
   in.open(Form("%sbasic.dat",dir.Data()));

   Float_t x,y,z;
   Int_t nlines = 0;
   TFile *f = new TFile("basic.root","RECREATE");
   TH1F *h1 = new TH1F("h1","x distribution",100,-4,4);
   TNtuple *ntuple = new TNtuple("ntuple","data from ascii file","x:y:z");

   while (1) {
      in >> x >> y >> z;
      if (!in.good()) break;
      if (nlines < 5) printf("x=%8f, y=%8f, z=%8f\n",x,y,z);
      h1->Fill(x);
      ntuple->Fill(x,y,z);
      nlines++;
   }
   printf(" found %d points\n",nlines);

   in.close();

   f->Write();
}

void basic2() {
//   example of macro to create can ntuple reading data from an ascii file.
   TString dir = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
   dir.ReplaceAll("basic2.C","");
   dir.ReplaceAll("/./","/");
   
   TFile *f = new TFile("basic2.root","RECREATE");
   TH1F *h1 = new TH1F("h1","x distribution",100,-4,4);
   TTree *T = new TTree("ntuple","data from ascii file");
   Long64_t nlines = T->ReadFile(Form("%sbasic.dat",dir.Data()),"x:y:z");
   printf(" found %lld points\n",nlines);
   T->Draw("x","z>2");
   T->Write();
}
```

<!-- TFile.md ends here -->
