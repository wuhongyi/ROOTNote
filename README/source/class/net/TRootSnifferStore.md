<!-- TRootSnifferStore.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 三 6月  6 01:27:10 2018 (+0800)
;; Last-Updated: 三 6月  6 01:30:04 2018 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# TRootSnifferStore

Used to store different results of objects scanning by TRootSniffer

TRootSnifferStore : public TObject  

Used to store scanned objects hierarchy in XML form

TRootSnifferStoreXml : public TRootSnifferStore  

Used to store scanned objects hierarchy in JSON form

TRootSnifferStoreJson : public TRootSnifferStore  

## class

TRootSnifferStore

```cpp
   TRootSnifferStore();
   virtual ~TRootSnifferStore();

   virtual void CreateNode(Int_t, const char *) {}
   virtual void SetField(Int_t, const char *, const char *, Bool_t) {}
   virtual void BeforeNextChild(Int_t, Int_t, Int_t) {}
   virtual void CloseNode(Int_t, Int_t) {}

   void SetResult(void *_res, TClass *_rescl, TDataMember *_resmemb, Int_t _res_chld, Int_t restr = 0);

   void *GetResPtr() const { return fResPtr; }
   TClass *GetResClass() const { return fResClass; }
   TDataMember *GetResMember() const { return fResMember; }
   Int_t GetResNumChilds() const { return fResNumChilds; }
   Int_t GetResRestrict() const { return fResRestrict; }
   virtual Bool_t IsXml() const { return kFALSE; }
```


TRootSnifferStoreXml

```cpp
   TRootSnifferStoreXml(TString &_buf, Bool_t _compact = kFALSE) : TRootSnifferStore(), fBuf(&_buf), fCompact(_compact)
   {
   }

   virtual ~TRootSnifferStoreXml() {}

   virtual void CreateNode(Int_t lvl, const char *nodename);
   virtual void SetField(Int_t lvl, const char *field, const char *value, Bool_t);
   virtual void BeforeNextChild(Int_t lvl, Int_t nchld, Int_t);
   virtual void CloseNode(Int_t lvl, Int_t numchilds);

   virtual Bool_t IsXml() const { return kTRUE; }
```


TRootSnifferStoreJson

```cpp
   TRootSnifferStoreJson(TString &_buf, Bool_t _compact = kFALSE) : TRootSnifferStore(), fBuf(&_buf), fCompact(_compact)
   {
   }
   virtual ~TRootSnifferStoreJson() {}

   virtual void CreateNode(Int_t lvl, const char *nodename);
   virtual void SetField(Int_t lvl, const char *field, const char *value, Bool_t with_quotes);
   virtual void BeforeNextChild(Int_t lvl, Int_t nchld, Int_t nfld);
   virtual void CloseNode(Int_t lvl, Int_t numchilds);
```


<!-- TRootSnifferStore.md ends here -->
