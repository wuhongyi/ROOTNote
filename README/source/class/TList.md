<!-- TList.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  1 22:08:29 2016 (+0800)
;; Last-Updated: 三 9月 16 12:45:08 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TList*

继承 TSeqCollection

A doubly linked list. All classes inheriting from TObject can be inserted in a TList.

All classes inheriting from TObject can be
inserted in a TList. Before being inserted into the list the object
pointer is wrapped in a TObjLink object which contains, besides
the object pointer also a previous and next pointer.

## class

```cpp
   typedef TListIter Iterator_t;

   TList() : fFirst(0), fLast(0), fCache(0), fAscending(kTRUE) { }
   TList(TObject *) : fFirst(0), fLast(0), fCache(0), fAscending(kTRUE) { } // for backward compatibility, don't use
   virtual           ~TList();
   virtual void      Clear(Option_t *option="");
/// Remove all objects from the list. Does not delete the objects
/// unless the TList is the owner (set via SetOwner()) and option
/// "nodelete" is not set.
/// If option="nodelete" then don't delete any heap objects that were
/// marked with the kCanDelete bit, otherwise these objects will be
/// deleted (this option is used by THashTable::Clear()).

   virtual void      Delete(Option_t *option="");
/// Remove all objects from the list AND delete all heap based objects.
/// If option="slow" then keep list consistent during delete. This allows
/// recursive list operations during the delete (e.g. during the dtor
/// of an object in this list one can still access the list to search for
/// other not yet deleted objects).

   virtual TObject  *FindObject(const char *name) const;
/// Find an object in this list using its name. Requires a sequential
/// scan till the object has been found. Returns 0 if object with specified
/// name is not found. This method overrides the generic FindObject()
/// of TCollection for efficiency reasons.

   virtual TObject  *FindObject(const TObject *obj) const;
/// Find an object in this list using the object's IsEqual()
/// member function. Requires a sequential scan till the object has
/// been found. Returns 0 if object is not found.
/// This method overrides the generic FindObject() of TCollection for
/// efficiency reasons.

   virtual TIterator *MakeIterator(Bool_t dir = kIterForward) const;

   virtual void      Add(TObject *obj) { AddLast(obj); }
   virtual void      Add(TObject *obj, Option_t *opt) { AddLast(obj, opt); }
   virtual void      AddFirst(TObject *obj);/// Add object at the beginning of the list.
   virtual void      AddFirst(TObject *obj, Option_t *opt);
/// Add object at the beginning of the list and also store option.
/// Storing an option is useful when one wants to change the behaviour
/// of an object a little without having to create a complete new
/// copy of the object. This feature is used, for example, by the Draw()
/// method. It allows the same object to be drawn in different ways.

   virtual void      AddLast(TObject *obj);/// Add object at the end of the list.
   virtual void      AddLast(TObject *obj, Option_t *opt);
/// Add object at the end of the list and also store option.
/// Storing an option is useful when one wants to change the behaviour
/// of an object a little without having to create a complete new
/// copy of the object. This feature is used, for example, by the Draw()
/// method. It allows the same object to be drawn in different ways.

   virtual void      AddAt(TObject *obj, Int_t idx);/// Insert object at position idx in the list.
   virtual void      AddAfter(const TObject *after, TObject *obj);/// Insert object after object after in the list.
   virtual void      AddAfter(TObjLink *after, TObject *obj);
/// Insert object after the specified ObjLink object. If after = 0 then add
/// to the tail of the list. An ObjLink can be obtained by looping over a list
/// using the above describe iterator method 3.

   virtual void      AddBefore(const TObject *before, TObject *obj);/// Insert object before object before in the list.
   virtual void      AddBefore(TObjLink *before, TObject *obj);
/// Insert object before the specified ObjLink object. If before = 0 then add
/// to the head of the list. An ObjLink can be obtained by looping over a list
/// using the above describe iterator method 3.

   virtual TObject  *Remove(TObject *obj);/// Remove object from the list.
   virtual TObject  *Remove(TObjLink *lnk);/// Remove object link (and therefore the object it contains) from the list.
   virtual void      RemoveLast();/// Remove the last object of the list.
   virtual void      RecursiveRemove(TObject *obj);
/// Remove object from this collection and recursively remove the object
/// from all other objects (and collections).

   virtual TObject  *At(Int_t idx) const;/// Returns the object at position idx. Returns 0 if idx is out of range.
   virtual TObject  *After(const TObject *obj) const;
/// Returns the object after object obj. Obj is found using the
/// object's IsEqual() method.  Returns 0 if obj is last in list.

   virtual TObject  *Before(const TObject *obj) const;
/// Returns the object before object obj. Obj is found using the
/// object's IsEqual() method.  Returns 0 if obj is first in list.

   virtual TObject  *First() const;/// Return the first object in the list. Returns 0 when list is empty.
   virtual TObjLink *FirstLink() const { return fFirst; }
   virtual TObject **GetObjectRef(const TObject *obj) const;/// Return address of pointer to obj
   virtual TObject  *Last() const;/// Return the last object in the list. Returns 0 when list is empty.
   virtual TObjLink *LastLink() const { return fLast; }

   virtual void      Sort(Bool_t order = kSortAscending);
/// Sort linked list. Real sorting is done in private function DoSort().
/// The list can only be sorted when is contains objects of a sortable
/// class.

   Bool_t            IsAscending() { return fAscending; }
```

## code

```cpp
// There are basically four ways to iterate over a TList (in order
// of preference, if not forced by other constraints):

//   1. Using the R__FOR_EACH macro:

GetListOfPrimitives()->R__FOR_EACH(TObject,Paint)(option);

//  2. Using the TList iterator TListIter (via the wrapper class TIter):

TIter next(GetListOfPrimitives());
while ((TObject *obj = next()))
   obj->Draw(next.GetOption());

//  3. Using the TList iterator TListIter and std::for_each algorithm:

  // A function object, which will be applied to each element
  // of the given range.
struct STestFunctor {
   bool operator()(TObject *aObj) {
      ...
      return true;
   }
}
...
...
TIter iter(mylist);
for_each( iter.Begin(), TIter::End(), STestFunctor() );

//  4. Using the TObjLink list entries (that wrap the TObject*):

TObjLink *lnk = GetListOfPrimitives()->FirstLink();
while (lnk) {
   lnk->GetObject()->Draw(lnk->GetOption());
   lnk = lnk->Next();
}

//  5. Using the TList's After() and Before() member functions:

TFree *idcur = this;
while (idcur) {
   ...
   ...
   idcur = (TFree*)GetListOfFree()->After(idcur);
         }

// Methods 2, 3 and 4 can also easily iterate backwards using either
// a backward TIter (using argument kIterBackward) or by using
// LastLink() and lnk->Prev() or by using the Before() member.
```

## example



<!-- TList.md ends here -->
