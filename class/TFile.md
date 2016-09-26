<!-- TFile.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 11:38:01 2014 (+0800)
;; Last-Updated: 一 9月 26 22:13:59 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 11
;; URL: http://wuhongyi.github.io -->

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
   virtual void        Copy(TObject &) const { MayNotUse("Copy(TObject &)"); }
   virtual Bool_t      Cp(const char *dst, Bool_t progressbar = kTRUE,UInt_t buffersize = 1000000);
   virtual TKey*       CreateKey(TDirectory* mother, const TObject* obj, const char* name, Int_t bufsize);
   virtual TKey*       CreateKey(TDirectory* mother, const void* obj, const TClass* cl,
                                 const char* name, Int_t bufsize);
   static TFile      *&CurrentFile(); // Return the current file for this thread.
   virtual void        Delete(const char *namecycle="");
   virtual void        Draw(Option_t *option="");
   virtual void        DrawMap(const char *keys="*",Option_t *option=""); // *MENU*
   virtual void        FillBuffer(char *&buffer);
   virtual void        Flush();
   TArchiveFile       *GetArchive() const { return fArchive; }
   Long64_t            GetArchiveOffset() const { return fArchiveOffset; }
   Int_t               GetBestBuffer() const;
   virtual Int_t       GetBytesToPrefetch() const;
   TFileCacheRead     *GetCacheRead(TObject* tree = 0) const;
   TFileCacheWrite    *GetCacheWrite() const;
   TArrayC            *GetClassIndex() const { return fClassIndex; }
   Int_t               GetCompressionAlgorithm() const;
   Int_t               GetCompressionLevel() const;
   Int_t               GetCompressionSettings() const;
   Float_t             GetCompressionFactor();
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
   virtual Int_t       GetReadCalls() const { return fReadCalls; }
   Int_t               GetVersion() const { return fVersion; }
   Int_t               GetRecordHeader(char *buf, Long64_t first, Int_t maxbytes,
                                       Int_t &nbytes, Int_t &objlen, Int_t &keylen);
   virtual Int_t       GetNbytesInfo() const {return fNbytesInfo;}
   virtual Int_t       GetNbytesFree() const {return fNbytesFree;}
   virtual TString     GetNewUrl() { return ""; }
   Long64_t            GetRelOffset() const { return fOffset - fArchiveOffset; }
   virtual Long64_t    GetSeekFree() const {return fSeekFree;}
   virtual Long64_t    GetSeekInfo() const {return fSeekInfo;}
   virtual Long64_t    GetSize() const;
   virtual TList      *GetStreamerInfoList();
   const   TList      *GetStreamerInfoCache();
   virtual void        IncrementProcessIDs() { fNProcessIDs++; }
   virtual Bool_t      IsArchive() const { return fIsArchive; }
           Bool_t      IsBinary() const { return TestBit(kBinaryFile); }
           Bool_t      IsRaw() const { return !fIsRootFile; }
   virtual Bool_t      IsOpen() const;
   virtual void        ls(Option_t *option="") const;
   virtual void        MakeFree(Long64_t first, Long64_t last);
   virtual void        MakeProject(const char *dirname, const char *classes="*",
                                   Option_t *option="new"); // *MENU*
   virtual void        Map(); // *MENU*
   virtual Bool_t      Matches(const char *name);
   virtual Bool_t      MustFlush() const {return fMustFlush;}
   virtual void        Paint(Option_t *option="");
   virtual void        Print(Option_t *option="") const;
   virtual Bool_t      ReadBufferAsync(Long64_t offs, Int_t len);
   virtual Bool_t      ReadBuffer(char *buf, Int_t len);
   virtual Bool_t      ReadBuffer(char *buf, Long64_t pos, Int_t len);
   virtual Bool_t      ReadBuffers(char *buf, Long64_t *pos, Int_t *len, Int_t nbuf);
   virtual void        ReadFree();
   virtual TProcessID *ReadProcessID(UShort_t pidf);
   virtual void        ReadStreamerInfo();
   virtual Int_t       Recover();
   virtual Int_t       ReOpen(Option_t *mode);
   virtual void        Seek(Long64_t offset, ERelativeTo pos = kBeg);
   virtual void        SetCacheRead(TFileCacheRead *cache, TObject* tree = 0, ECacheAction action = kDisconnect);
   virtual void        SetCacheWrite(TFileCacheWrite *cache);
   virtual void        SetCompressionAlgorithm(Int_t algorithm=0);
   virtual void        SetCompressionLevel(Int_t level=1);
   virtual void        SetCompressionSettings(Int_t settings=1);
   virtual void        SetEND(Long64_t last) { fEND = last; }
   virtual void        SetOffset(Long64_t offset, ERelativeTo pos = kBeg);
   virtual void        SetOption(Option_t *option=">") { fOption = option; }
   virtual void        SetReadCalls(Int_t readcalls = 0) { fReadCalls = readcalls; }
   virtual void        ShowStreamerInfo();
   virtual Int_t       Sizeof() const;
   void                SumBuffer(Int_t bufsize);
   virtual Bool_t      WriteBuffer(const char *buf, Int_t len);
   virtual Int_t       Write(const char *name=0, Int_t opt=0, Int_t bufsiz=0);
   virtual Int_t       Write(const char *name=0, Int_t opt=0, Int_t bufsiz=0) const;
   virtual void        WriteFree();
   virtual void        WriteHeader();
   virtual UShort_t    WriteProcessID(TProcessID *pid);
   virtual void        WriteStreamerInfo();

   static TFileOpenHandle
                      *AsyncOpen(const char *name, Option_t *option = "",
                                 const char *ftitle = "", Int_t compress = 1,
                                 Int_t netopt = 0);
   static TFile       *Open(const char *name, Option_t *option = "",
                            const char *ftitle = "", Int_t compress = 1,
                            Int_t netopt = 0);
   static TFile       *Open(TFileOpenHandle *handle);

   static EFileType    GetType(const char *name, Option_t *option = "", TString *prefix = 0);

   static EAsyncOpenStatus GetAsyncOpenStatus(const char *name);
   static EAsyncOpenStatus GetAsyncOpenStatus(TFileOpenHandle *handle);
   static const TUrl  *GetEndpointUrl(const char *name);

   static Long64_t     GetFileBytesRead();
   static Long64_t     GetFileBytesWritten();
   static Int_t        GetFileReadCalls();
   static Int_t        GetReadaheadSize();

   static void         SetFileBytesRead(Long64_t bytes = 0);
   static void         SetFileBytesWritten(Long64_t bytes = 0);
   static void         SetFileReadCalls(Int_t readcalls = 0);
   static void         SetReadaheadSize(Int_t bufsize = 256000);
   static void         SetReadStreamerInfo(Bool_t readinfo=kTRUE);
   static Bool_t       GetReadStreamerInfo();

   static Long64_t     GetFileCounter();
   static void         IncrementFileCounter();

   static Bool_t       SetCacheFileDir(const char *cacheDir, Bool_t operateDisconnected = kTRUE,
                                       Bool_t forceCacheread = kFALSE);
   static const char  *GetCacheFileDir();
   static Bool_t       ShrinkCacheFileDir(Long64_t shrinkSize, Long_t cleanupInteval = 0);
   static Bool_t       Cp(const char *src, const char *dst, Bool_t progressbar = kTRUE,
                          UInt_t buffersize = 1000000);

   static UInt_t       SetOpenTimeout(UInt_t timeout);  // in ms
   static UInt_t       GetOpenTimeout(); // in ms
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
