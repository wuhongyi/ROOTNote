<!-- TSystemDirectory.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 六 8月 13 18:55:10 2016 (+0800)
;; Last-Updated: 六 8月 13 18:56:12 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# TSystemDirectory

继承 TSystemFile

Describes an Operating System directory for the browser.

## class

```cpp
   TSystemDirectory();
   TSystemDirectory(const char *dirname, const char *path);

   virtual ~TSystemDirectory();

   virtual Bool_t IsFolder() const { return kTRUE; }
   virtual Bool_t IsDirectory(const char * = 0) const { return kTRUE; }

   virtual void   Browse(TBrowser *b);
   virtual void   Edit() { }
   virtual TList *GetListOfFiles() const;
   virtual void   SetDirectory(const char *name);
   virtual void   Delete() {}
   virtual void   Copy(const char *) {}
   virtual void   Move(const char *) {}

   // dummy methods from TObject
   void        DrawClass() const { }
   TObject    *DrawClone(Option_t *) const { return 0; }
   void        SetDrawOption(Option_t *) { }
   void        SetName(const char *name) { TSystemFile::SetName(name); }
   void        SetTitle(const char *title) { TSystemFile::SetTitle(title); }
   void        Delete(Option_t *) { }
   void        Copy(TObject & ) const { }
```

<!-- TSystemDirectory.md ends here -->
