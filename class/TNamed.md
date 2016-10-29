<!-- TNamed.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 六 8月 13 14:44:03 2016 (+0800)
;; Last-Updated: 六 8月 13 14:51:18 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# TNamed

## class

**继承 TObject**

```cpp
   virtual void     Clear(Option_t *option ="");//Set name and title to empty strings ("")
   virtual TObject *Clone(const char *newname="") const;// Make a clone of an object using the Streamer facility. If newname is specified, this will be the name of the new object.
   virtual Int_t    Compare(const TObject *obj) const;// Compare two TNamed objects. Returns 0 when equal, -1 when this is smaller and +1 when bigger (like strcmp).
   virtual void     Copy(TObject &named) const;// Copy this to obj.
   virtual void     FillBuffer(char *&buffer);// Encode TNamed into output buffer.
   virtual const char  *GetName() const { return fName; }
   virtual const char  *GetTitle() const { return fTitle; }
   virtual ULong_t  Hash() const { return fName.Hash(); }
   virtual Bool_t   IsSortable() const { return kTRUE; }
   virtual void     SetName(const char *name); // *MENU*   设置object identifier
   virtual void     SetNameTitle(const char *name, const char *title);
   virtual void     SetTitle(const char *title=""); // *MENU*  设置object title
   virtual void     ls(Option_t *option="") const;// List TNamed name and title.
   virtual void     Print(Option_t *option="") const;// Print TNamed name and title.
   virtual Int_t    Sizeof() const;// Return size of the TNamed part of the TObject.
```




<!-- TNamed.md ends here -->
