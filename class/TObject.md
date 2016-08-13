<!-- TObject.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 六 8月 13 16:22:48 2016 (+0800)
;; Last-Updated: 六 8月 13 16:32:43 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.github.io -->

# TObject

## class

```cpp
   virtual void        AppendPad(Option_t *option="");
   virtual void        Browse(TBrowser *b);
   virtual const char *ClassName() const;
   virtual void        Clear(Option_t * /*option*/ ="") { }
   virtual TObject    *Clone(const char *newname="") const;
   virtual Int_t       Compare(const TObject *obj) const;
   virtual void        Copy(TObject &object) const;
   virtual void        Delete(Option_t *option=""); // *MENU*
   virtual Int_t       DistancetoPrimitive(Int_t px, Int_t py);
   virtual void        Draw(Option_t *option="");
   virtual void        DrawClass() const; // *MENU*
   virtual TObject    *DrawClone(Option_t *option="") const; // *MENU*
   virtual void        Dump() const; // *MENU*
   virtual void        Execute(const char *method,  const char *params, Int_t *error=0);
   virtual void        Execute(TMethod *method, TObjArray *params, Int_t *error=0);
   virtual void        ExecuteEvent(Int_t event, Int_t px, Int_t py);
   virtual TObject    *FindObject(const char *name) const;
   virtual TObject    *FindObject(const TObject *obj) const;
   virtual Option_t   *GetDrawOption() const;
   virtual UInt_t      GetUniqueID() const;
   virtual const char *GetName() const;
   virtual const char *GetIconName() const;
   virtual Option_t   *GetOption() const { return ""; }
   virtual char       *GetObjectInfo(Int_t px, Int_t py) const;
   virtual const char *GetTitle() const;
   virtual Bool_t      HandleTimer(TTimer *timer);
   virtual ULong_t     Hash() const;
   virtual Bool_t      InheritsFrom(const char *classname) const;
   virtual Bool_t      InheritsFrom(const TClass *cl) const;
   virtual void        Inspect() const; // *MENU*
   virtual Bool_t      IsFolder() const;
   virtual Bool_t      IsEqual(const TObject *obj) const;
   virtual Bool_t      IsSortable() const { return kFALSE; }
           Bool_t      IsOnHeap() const { return TestBit(kIsOnHeap); }
           Bool_t      IsZombie() const { return TestBit(kZombie); }
   virtual Bool_t      Notify();
   virtual void        ls(Option_t *option="") const;
   virtual void        Paint(Option_t *option="");
   virtual void        Pop();
   virtual void        Print(Option_t *option="") const;
   virtual Int_t       Read(const char *name);
   virtual void        RecursiveRemove(TObject *obj);
   virtual void        SaveAs(const char *filename="",Option_t *option="") const; // *MENU*
   virtual void        SavePrimitive(std::ostream &out, Option_t *option = "");
   virtual void        SetDrawOption(Option_t *option="");  // *MENU*
   virtual void        SetUniqueID(UInt_t uid);
   virtual void        UseCurrentStyle();
   virtual Int_t       Write(const char *name=0, Int_t option=0, Int_t bufsize=0);
   virtual Int_t       Write(const char *name=0, Int_t option=0, Int_t bufsize=0) const;
```




<!-- TObject.md ends here -->
