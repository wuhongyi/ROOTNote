<!-- TCollection.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 四 1月 18 23:35:51 2018 (+0800)
;; Last-Updated: 三 9月 16 12:44:34 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TCollection*

继承 public TObject

Collection abstract base class. This class describes the base
protocol all collection classes have to implement. The ROOT
collection classes always store pointers to objects that inherit
from TObject. They never adopt the objects. Therefore, it is the
user's responsibility to take care of deleting the actual objects
once they are not needed anymore. In exceptional cases, when the
user is 100% sure nothing else is referencing the objects in the
collection, one can delete all objects and the collection at the
same time using the Delete() function.

Collections can be iterated using an iterator object (see
TIterator). Depending on the concrete collection class there may be
some additional methods of iterating. See the respective classes.

TCollection inherits from TObject since we want to be able to have
collections of collections.

In a later release the collections may become templatized.


## class

```cpp
// TCollection

public:
   enum { kInitCapacity = 16, kInitHashTableCapacity = 17 };

   virtual            ~TCollection() { }
   virtual void       Add(TObject *obj) = 0;

/// Add all arguments to the collection. The list of objects must be
/// terminated by 0, e.g.: l.AddVector(o1, o2, o3, o4, 0);
   void               AddVector(TObject *obj1, ...);

/// Add all objects from collection col to this collection.
   virtual void       AddAll(const TCollection *col);

/// Make sure all objects in this collection inherit from class cl.
   Bool_t             AssertClass(TClass *cl) const;

/// Browse this collection (called by TBrowser).
/// If b=0, there is no Browse call TObject::Browse(0) instead.
///         This means TObject::Inspect() will be invoked indirectly
   void               Browse(TBrowser *b);
   Int_t              Capacity() const { return fSize; }
   virtual void       Clear(Option_t *option="") = 0;

/// Make a clone of an collection using the Streamer facility.
/// If newname is specified, this will be the name of the new collection.
   virtual TObject   *Clone(const char *newname="") const;

/// Compare two TCollection objects. Returns 0 when equal, -1 when this is
/// smaller and +1 when bigger (like strcmp()).
   Int_t              Compare(const TObject *obj) const;
   Bool_t             Contains(const char *name) const { return FindObject(name) != 0; }
   Bool_t             Contains(const TObject *obj) const { return FindObject(obj) != 0; }
   virtual void       Delete(Option_t *option="") = 0;

/// Draw all objects in this collection.
   virtual void       Draw(Option_t *option="");

/// Dump all objects in this collection.
   virtual void       Dump() const ;

/// Find an object in this collection using its name. Requires a sequential
/// scan till the object has been found. Returns 0 if object with specified
/// name is not found.
   virtual TObject   *FindObject(const char *name) const;

/// Find an object in this collection by name.
   TObject           *operator()(const char *name) const;

/// Find an object in this collection using the object's IsEqual()
/// member function. Requires a sequential scan till the object has
/// been found. Returns 0 if object is not found.
/// Typically this function is overridden by a more efficient version
/// in concrete collection classes (e.g. THashTable).
   virtual TObject   *FindObject(const TObject *obj) const;
   virtual Int_t      GetEntries() const { return GetSize(); }

/// Return name of this collection.
/// if no name, return the collection class name.
   virtual const char *GetName() const;
   virtual TObject  **GetObjectRef(const TObject *obj) const = 0;
   virtual Int_t      GetSize() const { return fSize; }

/// Increase the collection's capacity by delta slots.
   virtual Int_t      GrowBy(Int_t delta) const;
   ULong_t            Hash() const { return fName.Hash(); }

/// Returns true if object is a null pointer.
   Bool_t             IsArgNull(const char *where, const TObject *obj) const;
   virtual Bool_t     IsEmpty() const { return GetSize() <= 0; }
   virtual Bool_t     IsFolder() const { return kTRUE; }
   Bool_t             IsOwner() const { return TestBit(kIsOwner); }
   Bool_t             IsSortable() const { return kTRUE; }

/// List (ls) all objects in this collection.
/// Wildcarding supported, eg option="xxx*" lists only objects
/// with names xxx*.
   virtual void       ls(Option_t *option="") const ;

/// 'Notify' all objects in this collection.
   virtual Bool_t     Notify();
   virtual TIterator *MakeIterator(Bool_t dir = kIterForward) const = 0;
   virtual TIterator *MakeReverseIterator() const { return MakeIterator(kIterBackward); }

/// Paint all objects in this collection.
   virtual void       Paint(Option_t *option="");

/// Default print for collections, calls Print(option, 1).
/// This will print the collection header and Print() methods of
/// all the collection entries.
/// If you want to override Print() for a collection class, first
/// see if you can accomplish it by overriding the following protected
/// methods:
///   void        PrintCollectionHeader(Option_t* option) const;
///   const char* GetCollectionEntryName(TObject* entry) const;
///   void        PrintCollectionEntry(TObject* entry, Option_t* option, Int_t recurse) const;
/// Otherwise override the `Print(Option_t *option, Int_t)`
/// variant. Remember to declare:
///   using TCollection::Print;
/// somewhere close to the method declaration.
   virtual void       Print(Option_t *option="") const;

/// Print the collection header and its elements.
/// If recurse is non-zero, descend into printing of
/// collection-entries with recurse - 1.
/// This means, if recurse is negative, the recursion is infinite.
/// Option is passed recursively.
   virtual void       Print(Option_t *option, Int_t recurse) const;

/// Print the collection header and its elements that match the wildcard.
/// If recurse is non-zero, descend into printing of
/// collection-entries with recurse - 1.
/// This means, if recurse is negative, the recursion is infinite.
/// Option is passed recursively, but wildcard is only used on the
/// first level.
   virtual void       Print(Option_t *option, const char* wildcard, Int_t recurse=1) const;

/// Print the collection header and its elements that match the regexp.
/// If recurse is non-zero, descend into printing of
/// collection-entries with recurse - 1.
/// This means, if recurse is negative, the recursion is infinite.
/// Option is passed recursively, but regexp is only used on the
/// first level.
   virtual void       Print(Option_t *option, TPRegexp& regexp, Int_t recurse=1) const;

/// Remove object from this collection and recursively remove the object
/// from all other objects (and collections).
   virtual void       RecursiveRemove(TObject *obj);
   virtual TObject   *Remove(TObject *obj) = 0;

/// Remove all objects in collection col from this collection.
   virtual void       RemoveAll(TCollection *col);
   void               RemoveAll() { Clear(); }

/// Set this collection to be the globally accesible collection.
   void               SetCurrentCollection();
   void               SetName(const char *name) { fName = name; }

/// Set whether this collection is the owner (enable==true)
/// of its content.  If it is the owner of its contents,
/// these objects will be deleted whenever the collection itself
/// is delete.   The objects might also be deleted or destructed when Clear
/// is called (depending on the collection).
   virtual void       SetOwner(Bool_t enable = kTRUE);

/// Write all objects in this collection. By default all objects in
/// the collection are written individually (each object gets its
/// own key). Note, this is recursive, i.e. objects in collections
/// in the collection are also written individually. To write all
/// objects using a single key specify a name and set option to
/// TObject::kSingleKey (i.e. 1).
   virtual Int_t      Write(const char *name=0, Int_t option=0, Int_t bufsize=0);

/// Write all objects in this collection. By default all objects in
/// the collection are written individually (each object gets its
/// own key). Note, this is recursive, i.e. objects in collections
/// in the collection are also written individually. To write all
/// objects using a single key specify a name and set option to
/// TObject::kSingleKey (i.e. 1).
   virtual Int_t      Write(const char *name=0, Int_t option=0, Int_t bufsize=0) const;

/// Return the globally accessible collection.
   static TCollection  *GetCurrentCollection();

/// Set up for garbage collection.
   static void          StartGarbageCollection();

/// Add to the list of things to be cleaned up.
   static void          GarbageCollect(TObject *obj);

/// Do the garbage collection.
   static void          EmptyGarbageCollection();

   TIter begin() const;
   TIter end() const;
```



```cpp
// TIter

public:
   TIter(const TCollection *col, Bool_t dir = kIterForward)
         : fIterator(col ? col->MakeIterator(dir) : 0) { }
   TIter(TIterator *it) : fIterator(it) { }

/// Copy a TIter. This involves allocating a new TIterator of the right
/// sub class and assigning it with the original.
   TIter(const TIter &iter);
   TIter &operator=(const TIter &rhs);
   virtual ~TIter() { SafeDelete(fIterator); }
   TObject           *operator()() { return Next(); }
   TObject           *Next() { return fIterator ? fIterator->Next() : nullptr; }
   const TCollection *GetCollection() const { return fIterator ? fIterator->GetCollection() : nullptr; }
   Option_t          *GetOption() const { return fIterator ? fIterator->GetOption() : ""; }
   void               Reset() { if (fIterator) fIterator->Reset(); }
   TIter             &operator++() { Next(); return *this; }
   Bool_t             operator==(const TIter &aIter) const {
      if (fIterator == nullptr)
         return aIter.fIterator == nullptr || **aIter.fIterator == nullptr;
      if (aIter.fIterator == nullptr)
         return fIterator == nullptr || **fIterator == nullptr;
      return *fIterator == *aIter.fIterator;
   }
   Bool_t             operator!=(const TIter &aIter) const {
      return !(*this == aIter);
   }

/// Assigning an TIter to another. This involves allocating a new TIterator
/// of the right sub class and assigning it with the original.
   TObject           *operator*() const { return fIterator ? *(*fIterator): nullptr; }

/// Pointing to the first element of the container.
   TIter             &Begin();

/// Pointing to the element after the last - to a nullptr value in our case.
   static TIter       End();

```

## code





## example


<!-- TCollection.md ends here -->
