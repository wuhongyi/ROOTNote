<!-- TSystemFile.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 六 8月 13 18:53:18 2016 (+0800)
;; Last-Updated: 三 9月 16 10:30:37 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TSystemFile+

继承 TNamed

A TSystemFile describes an operating system file.
The information is used by the browser (see TBrowser).

## class

```cpp
   TSystemFile();
   TSystemFile(const char *filename, const char *dirname);
   virtual ~TSystemFile();
   virtual void     Browse(TBrowser *b);
   virtual void     Rename(const char *name);      // *MENU*
   virtual void     Delete();                      // *MENU*
   virtual void     Copy(const char *to);          // *MENU*
   virtual void     Move(const char *to);          // *MENU*
   virtual void     Edit();                        // *MENU*

   virtual Bool_t   IsDirectory(const char *dir = 0) const;
   virtual void     SetIconName(const char *name) { fIconName = name; }
   const char      *GetIconName() const { return fIconName.Data(); }

   // dummy methods from TObject
   virtual void     Inspect() const;
   virtual void     Dump() const;

   void        DrawClass() const { }
   TObject    *DrawClone(Option_t *) const { return 0; }
   void        SetDrawOption(Option_t *) { }
   void        SetName(const char *name) { TNamed::SetName(name); }
   void        SetTitle(const char *title) { TNamed::SetTitle(title); }
   void        Delete(Option_t *) { }
   void        Copy(TObject & ) const { }
```

<!-- TSystemFile.md ends here -->
