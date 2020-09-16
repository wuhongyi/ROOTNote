<!-- TSeqCollection.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 六 9月 15 13:23:07 2018 (+0800)
;; Last-Updated: 三 9月 16 12:44:55 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 3
;; URL: http://wuhongyi.cn -->

# TSeqCollection*

Sequenceable collection abstract base class. 
TSeqCollection's have an ordering relation, i.e. there is a first and last element.

TSeqCollection : public TCollection

## class

```cpp
protected:
   Bool_t            fSorted;    // true if collection has been sorted

   TSeqCollection() : fSorted(kFALSE) { }
   virtual void      Changed() { fSorted = kFALSE; }

public:
   virtual           ~TSeqCollection() { }
   virtual void      Add(TObject *obj) { AddLast(obj); }
   virtual void      AddFirst(TObject *obj) = 0;
   virtual void      AddLast(TObject *obj) = 0;
   virtual void      AddAt(TObject *obj, Int_t idx) = 0;
   virtual void      AddAfter(const TObject *after, TObject *obj) = 0;
   virtual void      AddBefore(const TObject *before, TObject *obj) = 0;
   virtual void      RemoveFirst() { Remove(First()); }
   virtual void      RemoveLast() { Remove(Last()); }
   virtual TObject  *RemoveAt(Int_t idx) { return Remove(At(idx)); }
   virtual void      RemoveAfter(TObject *after) { Remove(After(after)); }
   virtual void      RemoveBefore(TObject *before) { Remove(Before(before)); }

   virtual TObject  *At(Int_t idx) const = 0;
   virtual TObject  *Before(const TObject *obj) const = 0;
   virtual TObject  *After(const TObject *obj) const = 0;
   virtual TObject  *First() const = 0;
   virtual TObject  *Last() const = 0;
   Int_t             LastIndex() const { return GetSize() - 1; }
   virtual Int_t     GetLast() const;
/// Returns index of last object in collection. Returns -1 when no
/// objects in collection.   
   
   virtual Int_t     IndexOf(const TObject *obj) const;
/// Return index of object in collection. Returns -1 when object not found.
/// Uses member IsEqual() to find object.   
   
   virtual Bool_t    IsSorted() const { return fSorted; }
   void              UnSort() { fSorted = kFALSE; }
   Long64_t          Merge(TCollection *list);
/// Merge this collection with all collections coming in the input list. The
/// input list must contain other collections of objects compatible with the
/// ones in this collection and ordered in the same manner. For example, if this
/// collection contains a TH1 object and a tree, all collections in the input
/// list have to contain a histogram and a tree. In case the list contains
/// collections, the objects in the input lists must also be collections with
/// the same structure and number of objects.
/// If some objects inside the collection are instances of a class that do not
/// have a Merge function (like TObjString), rather than merging, a copy of each
/// instance (via a call to Clone) is appended to the output.
/// ### Example
///   this                          list
/// ____________                  ---------------------|
/// | A (TH1F) |  __________      | L1 (TSeqCollection)|- [A1, B1(C1,D1,E1)]
/// | B (TList)|-| C (TTree)|     | L1 (TSeqCollection)|- [A2, B2(C2,D2,E2)]
/// |__________| | D (TH1F) |     | ...                |- [...]
///              | E (TH1F) |     |____________________|
///              |__________|

   static Int_t       ObjCompare(TObject *a, TObject *b);
/// Compare to objects in the collection. Use member Compare() of object a.   
   
   static void        QSort(TObject **a, Int_t first, Int_t last);
/// Sort array of TObject pointers using a quicksort algorithm.
/// The algorithm used is a non stable sort (i.e. already sorted
/// elements might switch/change places).
/// Uses ObjCompare() to compare objects.

   static inline void QSort(TObject **a, TObject **b, Int_t first, Int_t last) { QSort(a, 1, &b, first, last); }
   static void        QSort(TObject **a, Int_t nBs, TObject ***b, Int_t first, Int_t last);
/// Sort array a of TObject pointers using a quicksort algorithm.
/// Arrays b will be sorted just like a (a determines the sort).
/// Argument nBs is the number of TObject** arrays in b.
/// The algorithm used is a non stable sort (i.e. already sorted
/// elements might switch/change places).
/// Uses ObjCompare() to compare objects.      
```


<!-- TSeqCollection.md ends here -->
