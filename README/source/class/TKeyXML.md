<!-- TKeyXML.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 一 1月  7 15:36:31 2019 (+0800)
;; Last-Updated: 三 9月 16 10:38:17 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TKeyXML-

TKeyXML is represents one block of data in TXMLFile

Normally this block corresponds to data of single object like histogram, TObjArray and so on.

```cpp
class TKeyXML : public TKey
```

## class

```cpp
private:
   TKeyXML(const TKeyXML &);            // TKeyXML objects are not copiable.
   TKeyXML &operator=(const TKeyXML &); // TKeyXML objects are not copiable.

protected:
   TKeyXML();

public:
   TKeyXML(TDirectory *mother, Long64_t keyid, const TObject *obj, const char *name = 0, const char *title = 0);
   TKeyXML(TDirectory *mother, Long64_t keyid, const void *obj, const TClass *cl, const char *name,
           const char *title = 0);
   TKeyXML(TDirectory *mother, Long64_t keyid, XMLNodePointer_t keynode);
   virtual ~TKeyXML();

   // redefined TKey Methods
   virtual void Delete(Option_t *option = "");
   virtual void DeleteBuffer() {}
   virtual void FillBuffer(char *&) {}
   virtual char *GetBuffer() const { return 0; }
   virtual Long64_t GetSeekKey() const { return fKeyNode ? 1024 : 0; }
   virtual Long64_t GetSeekPdir() const { return fKeyNode ? 1024 : 0; }
   // virtual ULong_t   Hash() const { return 0; }
   virtual void Keep() {}
   // virtual void      ls(Option_t* ="") const;
   // virtual void      Print(Option_t* ="") const {}

   virtual Int_t Read(TObject *tobj);
   virtual TObject *ReadObj();
   virtual TObject *ReadObjWithBuffer(char *bufferRead);
   virtual void *ReadObjectAny(const TClass *expectedClass);

   virtual void ReadBuffer(char *&) {}
   virtual Bool_t ReadFile() { return kTRUE; }
   virtual void SetBuffer() { fBuffer = 0; }
   virtual Int_t WriteFile(Int_t = 1, TFile * = 0) { return 0; }

   // TKeyXML specific methods

   XMLNodePointer_t KeyNode() const { return fKeyNode; }
   Long64_t GetKeyId() const { return fKeyId; }
   Bool_t IsSubdir() const { return fSubdir; }
   void SetSubir() { fSubdir = kTRUE; }
   void UpdateObject(TObject *obj);
   void UpdateAttributes();

protected:
   virtual Int_t Read(const char *name) { return TKey::Read(name); }
   void StoreObject(const void *obj, const TClass *cl, Bool_t check_tobj = kFALSE);
   void StoreKeyAttributes();
   TXMLEngine *XMLEngine();

   void *XmlReadAny(void *obj, const TClass *expectedClass);

   XMLNodePointer_t fKeyNode; //! node with stored object
   Long64_t fKeyId;           //! unique identifier of key for search methods
   Bool_t fSubdir;            //! indicates that key contains subdirectory
```

<!-- TKeyXML.md ends here -->
