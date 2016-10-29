<!-- TNamed.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 六 8月 13 14:44:03 2016 (+0800)
;; Last-Updated: 六 10月 29 21:15:00 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 4
;; URL: http://wuhongyi.cn -->

# TNamed

**继承 TObject**

The TNamed class is the base class for all named ROOT classes.

A TNamed contains the essential elements (name, title)
to identify a derived object in containers, directories and files.
Most member functions defined in this base class are in general
overridden by the derived classes.

## class

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
/// Change (i.e. set) the name of the TNamed.
/// WARNING: if the object is a member of a THashTable or THashList container
/// the container must be Rehash()'ed after SetName(). For example the list
/// of objects in the current directory is a THashList.

   virtual void     SetNameTitle(const char *name, const char *title);
/// Change (i.e. set) all the TNamed parameters (name and title).
/// WARNING: if the name is changed and the object is a member of a
/// THashTable or THashList container the container must be Rehash()'ed
/// after SetName(). For example the list of objects in the current
/// directory is a THashList.

   virtual void     SetTitle(const char *title=""); // *MENU*  设置object title
/// Change (i.e. set) the title of the TNamed.

   virtual void     ls(Option_t *option="") const;// List TNamed name and title.
   virtual void     Print(Option_t *option="") const;// Print TNamed name and title.
   virtual Int_t    Sizeof() const;// Return size of the TNamed part of the TObject.
```


<!-- TNamed.md ends here -->
