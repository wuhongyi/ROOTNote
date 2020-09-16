<!-- TXMLFile.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 一 1月  7 15:39:41 2019 (+0800)
;; Last-Updated: 三 9月 16 10:40:56 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TXMLFile-

```
// The main motivation for the XML  format is to facilitate the
// communication with other non ROOT applications. Currently
// writing and reading XML files is limited to ROOT applications.
// It is our intention to develop a simple reader independent
// of the ROOT libraries that could be used as an example for
// real applications. One of possible approach with code generation
// is implemented in TXMLPlayer class.
//
// The XML format should be used only for small data volumes,
// typically histogram files, pictures, geometries, calibrations.
// The XML file is built in memory before being dumped to disk.
//
// Like for normal ROOT files, XML files use the same I/O mechanism
// exploiting the ROOT/CINT dictionary. Any class having a dictionary
// can be saved in XML format.
//
// This first implementation does not support subdirectories
// or Trees.
//
// The shared library libRXML.so may be loaded dynamically
// via gSystem->Load("libRXML"). This library is automatically
// loaded by the plugin manager as soon as a XML file is created
// via, eg
//   TFile::Open("file.xml","recreate");
// TFile::Open returns a TXMLFile object. When a XML file is open in write mode,
// one can use the normal TObject::Write to write an object in the file.
// Alternatively one can use the new functions TDirectoryFile::WriteObject and
// TDirectoryFile::WriteObjectAny to write a TObject* or any class not deriving
// from TObject.
```

```cpp
class TXMLFile : public TFile, public TXMLSetup
```

## class

```cpp
protected:
   void InitXmlFile(Bool_t create);
   // Interface to basic system I/O routines
   virtual Int_t SysOpen(const char *, Int_t, UInt_t) { return 0; }
   virtual Int_t SysClose(Int_t) { return 0; }
   virtual Int_t SysRead(Int_t, void *, Int_t) { return 0; }
   virtual Int_t SysWrite(Int_t, const void *, Int_t) { return 0; }
   virtual Long64_t SysSeek(Int_t, Long64_t, Int_t) { return 0; }
   virtual Int_t SysStat(Int_t, Long_t *, Long64_t *, Long_t *, Long_t *) { return 0; }
   virtual Int_t SysSync(Int_t) { return 0; }

   // Overwrite methods for directory I/O
   virtual Long64_t DirCreateEntry(TDirectory *);
   virtual Int_t DirReadKeys(TDirectory *);
   virtual void DirWriteKeys(TDirectory *);
   virtual void DirWriteHeader(TDirectory *);

private:
   // let the compiler do the job. gcc complains when the following line is activated
   // TXMLFile(const TXMLFile &) {}            //Files cannot be copied
   void operator=(const TXMLFile &);

public:
   TXMLFile();
   TXMLFile(const char *filename, Option_t *option = "read", const char *title = "title", Int_t compression = 1);
   virtual ~TXMLFile();

   virtual void Close(Option_t *option = ""); // *MENU*
   virtual TKey *CreateKey(TDirectory *mother, const TObject *obj, const char *name, Int_t bufsize);
   virtual TKey *CreateKey(TDirectory *mother, const void *obj, const TClass *cl, const char *name, Int_t bufsize);
   virtual void DrawMap(const char * = "*", Option_t * = "") {}
   virtual void FillBuffer(char *&) {}
   virtual void Flush() {}

   virtual Long64_t GetEND() const { return 0; }
   virtual Int_t GetErrno() const { return 0; }
   virtual void ResetErrno() const {}

   virtual Int_t GetNfree() const { return 0; }
   virtual Int_t GetNbytesInfo() const { return 0; }
   virtual Int_t GetNbytesFree() const { return 0; }
   virtual Long64_t GetSeekFree() const { return 0; }
   virtual Long64_t GetSeekInfo() const { return 0; }
   virtual Long64_t GetSize() const { return 0; }
   virtual TList *GetStreamerInfoList();
   Int_t GetIOVersion() const { return fIOVersion; }

   virtual Bool_t IsOpen() const;

   virtual void MakeFree(Long64_t, Long64_t) {}
   virtual void MakeProject(const char *, const char * = "*", Option_t * = "new") {} // *MENU*
   virtual void Map(Option_t *) {}                                                   //
   virtual void Map() {}                                                             //
   virtual void Paint(Option_t * = "") {}
   virtual void Print(Option_t * = "") const {}
   virtual Bool_t ReadBuffer(char *, Int_t) { return kFALSE; }
   virtual Bool_t ReadBuffer(char *, Long64_t, Int_t) { return kFALSE; }
   virtual void ReadFree() {}
   virtual Int_t Recover() { return 0; }
   virtual Int_t ReOpen(Option_t *mode);
   virtual void Seek(Long64_t, ERelativeTo = kBeg) {}

   virtual void SetEND(Long64_t) {}
   virtual Int_t Sizeof() const { return 0; }

   virtual Bool_t WriteBuffer(const char *, Int_t) { return kFALSE; }
   virtual Int_t Write(const char * = 0, Int_t = 0, Int_t = 0) { return 0; }
   virtual Int_t Write(const char * = 0, Int_t = 0, Int_t = 0) const { return 0; }
   virtual void WriteFree() {}
   virtual void WriteHeader() {}
   virtual void WriteStreamerInfo();

   // XML specific functions

   virtual void SetXmlLayout(EXMLLayout layout);
   virtual void SetStoreStreamerInfos(Bool_t iConvert = kTRUE);
   virtual void SetUsedDtd(Bool_t use = kTRUE);
   virtual void SetUseNamespaces(Bool_t iUseNamespaces = kTRUE);

   Bool_t AddXmlComment(const char *comment);
   Bool_t AddXmlStyleSheet(const char *href, const char *type = "text/css", const char *title = 0, int alternate = -1,
                           const char *media = 0, const char *charset = 0);
   Bool_t AddXmlLine(const char *line);

   TXMLEngine *XML() { return fXML; }

protected:
   // functions to store streamer infos

   void StoreStreamerElement(XMLNodePointer_t node, TStreamerElement *elem);
   void ReadStreamerElement(XMLNodePointer_t node, TStreamerInfo *info);

   Bool_t ReadFromFile();
   Int_t ReadKeysList(TDirectory *dir, XMLNodePointer_t topnode);
   TKeyXML *FindDirKey(TDirectory *dir);
   TDirectory *FindKeyDir(TDirectory *mother, Long64_t keyid);
   void CombineNodesTree(TDirectory *dir, XMLNodePointer_t topnode, Bool_t dolink);

   void SaveToFile();

   static void ProduceFileNames(const char *filename, TString &fname, TString &dtdname);

   XMLDocPointer_t fDoc; //!

   XMLNodePointer_t fStreamerInfoNode; //!  pointer of node with streamer info data

   TXMLEngine *fXML; //! object for interface with xml library

   Int_t fIOVersion; //! indicates format of ROOT xml file

   Long64_t fKeyCounter; //! counter of created keys, used for keys id
```

## code

```cpp
// example of a session saving a histogram to a XML file
TFile *f = TFile::Open("Example.xml","recreate");
TH1F *h = new TH1F("h","test",1000,-2,2);
h->FillRandom("gaus");
h->Write();
delete f;
```

```cpp
// example of a session reading the histogram from the file
TFile *f = TFile::Open("Example.xml");
TH1F *h = (TH1F*)f->Get("h");
h->Draw();
```

```cpp
// A new option in the canvas "File" menu is available to save
// a TCanvas as a XML file. One can also do
canvas->Print("Example.xml");
```

<!-- TXMLFile.md ends here -->
