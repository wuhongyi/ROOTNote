<!-- TMapFile.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 日 1月  6 14:46:33 2019 (+0800)
;; Last-Updated: 日 1月  6 15:03:24 2019 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# TMapFile

```
This class implements a shared memory region mapped to a file.
Objects can be placed into this shared memory area using the Add()
member function. To actually place a copy of the object is shared
memory call Update() also whenever the mapped object(s) change(s)
call Update() to put a fresh copy in the shared memory. This extra
step is necessary since it is not possible to share objects with
virtual pointers between processes (the vtbl ptr points to the
originators unique address space and can not be used by the
consumer process(es)). Consumer processes can map the memory region
from this file and access the objects stored in it via the Get()
method (which returns a copy of the object stored in the shared
memory with correct vtbl ptr set). Only objects of classes with a
Streamer() member function defined can be shared.

I know the current implementation is not ideal (you need to copy to
and from the shared memory file) but the main problem is with the
class' virtual_table pointer. This pointer points to a table unique
for every process. Therefore, different options are:
  -# One could allocate an object directly in shared memory in the
     producer, but the consumer still has to copy the object from
     shared memory into a local object which has the correct vtbl
     pointer for that process (copy ctor's can be used for creating
     the local copy).
  -# Another possibility is to only allow objects without virtual
     functions in shared memory (like simple C structs), or to
     forbid (how?) the consumer from calling any virtual functions
     of the objects in shared memory.
  -# A last option is to copy the object internals to shared memory
     and copy them again from there. This is what is done in the
     TMapFile (using the object Streamer() to make a deep copy).

Option 1) saves one copy, but requires solid copy ctor's (along the
full inheritance chain) to rebuild the object in the consumer. Most
classes don't provide these copy ctor's, especially not when objects
contain collections, etc. 2) is too limiting or dangerous (calling
accidentally a virtual function will segv). So since we have a
robust Streamer mechanism I opted for 3).
```


```cpp
class TMapFile : public TObject
```

## class

**TMapFile**

```cpp
friend class TMapRec;

private:
   Int_t       fFd;             ///< Descriptor of mapped file
   Int_t       fVersion;        ///< ROOT version (or -1 for shadow map file)
   char       *fName;           ///< Name of mapped file
   char       *fTitle;          ///< Title of mapped file
   char       *fOption;         ///< Directory creation options
   void       *fMmallocDesc;    ///< Pointer to mmalloc descriptor
   ULong_t     fBaseAddr;       ///< Base address of mapped memory region
   Int_t       fSize;           ///< Original start size of memory mapped region
   TMapRec    *fFirst;          ///< List of streamed objects is shared memory
   TMapRec    *fLast;           ///< Last object in list of shared objects
   Long_t      fOffset;         ///< Offset in bytes for region mapped by reader
   TDirectory *fDirectory;      ///< Pointer to directory associated to this mapfile
   TList      *fBrowseList;     ///< List of KeyMapFile objects
   Bool_t      fWritable;       ///< TRUE if mapped file opened in RDWR mode
   Int_t       fSemaphore;      ///< Modification semaphore (or getpid() for WIN32)
   ULong_t     fhSemaphore;     ///< HANDLE of WIN32 Mutex object to implement semaphore
   TObject    *fGetting;        ///< Don't deadlock in update mode, when from Get() Add() is called
   Int_t       fWritten;        ///< Number of objects written sofar
   Double_t    fSumBuffer;      ///< Sum of buffer sizes of objects written sofar
   Double_t    fSum2Buffer;     ///< Sum of squares of buffer sizes of objects written so far

   static Long_t fgMapAddress;  ///< Map to this address, set address via SetMapAddress()
   static void  *fgMmallocDesc; ///< Used in Close() and operator delete()

protected:
   TMapFile();
   TMapFile(const char *name, const char *title, Option_t *option, Int_t size, TMapFile *&newMapFile);
/// Create a memory mapped file.
/// This opens a file (to which the
/// memory will be mapped) and attaches a memory region to it.
/// Option can be either: "NEW", "CREATE", "RECREATE", "UPDATE" or
/// "READ" (see TFile). The default open mode is "READ". The size
/// argument specifies the maximum size of shared memory file in bytes.
/// This protected ctor is called via the static Create() method.   
   
   TMapFile(const TMapFile &f, Long_t offset = 0);
/// Private copy ctor.
/// Used by the the ctor to create a new version
/// of TMapFile in the memory mapped heap. It's main purpose is to
/// correctly create the string data members.   
   
   void       operator=(const TMapFile &rhs);  // not implemented

   TMapFile  *FindShadowMapFile();/// Returns shadow map file.
   void       InitDirectory();/// Create the directory associated to this mapfile
   TObject   *Remove(TObject *obj, Bool_t lock);
/// Remove object from shared memory.
/// Returns pointer to removed object if successful, 0 otherwise.   
   
   TObject   *Remove(const char *name, Bool_t lock);
/// Remove object by name from shared memory.
/// Returns pointer to removed object if successful, 0 otherwise.   
   
   void       SumBuffer(Int_t bufsize);/// Increment statistics for buffer sizes of objects in this file.
   Int_t      GetBestBuffer();
/// Return the best buffer size for objects in this file.
/// The best buffer size is estimated based on the current mean value
/// and standard deviation of all objects written so far to this file.
/// Returns mean value + one standard deviation.

   void   CreateSemaphore(Int_t pid=0);/// Create semaphore used for synchronizing access to shared memory.
   Int_t  AcquireSemaphore();/// Acquire semaphore. Returns 0 if OK, -1 on error.
   Int_t  ReleaseSemaphore();/// Release semaphore. Returns 0 if OK, -1 on error.
   void   DeleteSemaphore();/// Delete the semaphore.

   static void *MapToAddress();
/// Return the base address at which we would like the next TMapFile's
/// mapped data to start.
/// For now, we let the system decide (start address 0). There are
/// a lot of issues to deal with here to make this work reasonably,
/// including:
///   - Avoid memory collisions with existing mapped address spaces
///   - Reclaim address spaces when their mmalloc heaps are unmapped
///   - When mmalloc heaps are shared between processes they have to be
///   mapped at the same addresses in each
/// Once created, a mmalloc heap that is to be mapped back in must be
/// mapped at the original address.  I.e. each TMapFile will expect
/// to be remapped at it's original address. This becomes a problem if
/// the desired address is already in use.

public:
   enum { kDefaultMapSize = 0x80000 }; // default size of mapped heap is 500 KB

   // Should both be protected (waiting for cint)
   virtual ~TMapFile();
/// TMapFiles may not be deleted, since we want to keep the complete
/// TMapFile object in the mapped file for later re-use. To enforce this
/// the delete operator has been made private. Use Close() to properly
/// terminate a TMapFile (also done via the TROOT dtor).   
   
   void     operator delete(void *vp);

   void          Browse(TBrowser *b);/// Browse contents of TMapFile.
   void          Close(Option_t *option = "");
/// Close a mapped file.
/// First detach mapped memory then close file.
/// No member functions of a TMapFile that was opened in write mode
/// may be called after Close() (this includes, of course, "delete" which
/// would call the dtors). The option="dtor" is only used when called
/// via the ~TMapFile.   
   
   void         *GetBaseAddr() const { return (void *)fBaseAddr; }
   void         *GetBreakval() const;
/// Return the current location in the memory region for this malloc heap which
/// represents the end of memory in use. Returns 0 if map file was closed.   
   
   TDirectory   *GetDirectory() const {return fDirectory;}
   Int_t         GetFd() const { return fFd; }
   void         *GetMmallocDesc() const { return fMmallocDesc; }
   const char   *GetName() const { return fName; }
   Int_t         GetSize() const { return fSize; }
   const char   *GetOption() const { return fOption; }
   const char   *GetTitle() const { return fTitle; }
   TMapRec      *GetFirst() const { return (TMapRec*)((Long_t) fFirst + fOffset); }
   TMapRec      *GetLast() const { return (TMapRec*)((Long_t) fLast + fOffset); }
   Bool_t        IsFolder() const;/// Returns kTRUE in case object is a folder (i.e. contains browsable lists).
   Bool_t        IsWritable() const { return fWritable; }
   void         *OrgAddress(void *addr) const { return (void *)((Long_t)addr - fOffset); }
   void          Print(Option_t *option="") const;/// Print some info about the mapped file.
   void          ls(Option_t *option="") const;/// List contents of TMapFile.
   Bool_t        cd(const char *path = 0);/// Cd to associated directory.

   void          Add(const TObject *obj, const char *name = "");
/// Add an object to the list of objects to be stored in shared memory.
/// To place the object actually into shared memory call Update().   
   
   void          Update(TObject *obj = 0);
/// Update an object (or all objects, if obj == 0) in shared memory.   
   
   TObject      *Remove(TObject *obj) { return Remove(obj, kTRUE); }
   TObject      *Remove(const char *name) { return Remove(name, kTRUE); }
   void          RemoveAll();/// Remove all objects from shared memory.
   TObject      *Get(const char *name, TObject *retObj = 0);
/// Return pointer to object retrieved from shared memory.
/// The object must
/// be deleted after use. If delObj is a pointer to a previously allocated
/// object it will be deleted. Returns 0 in case object with the given
/// name does not exist.

   static TMapFile *Create(const char *name, Option_t *option="READ", Int_t size=kDefaultMapSize, const char *title="");
/// Create a memory mapped file.
/// This opens a file (to which the
/// memory will be mapped) and attaches a memory region to it.
/// Option can be either: "NEW", "CREATE", "RECREATE", "UPDATE"
/// or "READ" (see TFile). The default open mode is "READ". The size
/// argument specifies the maximum size of shared memory file in bytes.
/// TMapFile's can only be created via this method. Create() enforces that
/// a TMapFile is always on the memory mapped heap (when "NEW", "CREATE"
/// or "RECREATE" are used).   
   
   static TMapFile *WhichMapFile(void *addr);
   static void      SetMapAddress(Long_t addr);
/// Set preferred map address.
/// Find out preferred map address as follows:
///   -# Run consumer program to find the preferred map address. Remember begin of mapped region, i.e. 0x40b4c000
/// ~~~{.cpp}
/// $ root
/// root [0] m = TMapFile::Create("dummy.map", "recreate", 10000000);
/// root [1] m.Print()
/// Memory mapped file:   dummy.map
/// Title:
/// Option:               CREATE
/// Mapped Memory region: 0x40b4c000 - 0x40d95f00 (2.29 MB)
/// Current breakval:     0x40b53000
/// root [2] .q
/// $ rm dummy.map
/// ~~~
///   -# Add to producer program, just before creating the TMapFile:
///    TMapFile::SetMapAddress(0x40b4c000);
/// Repeat this if more than one map file is being used.
/// The above procedure allow programs using, e.g., different number of
/// shared libraries (that cause the default mapping address to be
/// different) to create shared memory regions in the same location
/// without overwriting a shared library. The above assumes the consumer
/// program is larger (i.e. has more shared memory occupied) than the
/// producer. If this is not true inverse the procedure.   
```

----

**TMapRec**

```cpp
/**
\class TMapRec
\ingroup IO

Keep track of an object in the mapped file.

A TMapFile contains a list of TMapRec objects which keep track of
the actual objects stored in the mapped file.
*/

friend class TMapFile;

private:
   char            *fName;       ///< Object name
   char            *fClassName;  ///< Class name
   TObject         *fObject;     ///< Pointer to original object
   void            *fBuffer;     ///< Buffer containing object of class name
   Int_t            fBufSize;    ///< Buffer size
   TMapRec         *fNext;       ///< Next MapRec in list

   TMapRec(const TMapRec&);            // Not implemented.
   TMapRec &operator=(const TMapRec&); // Not implemented.

public:
   TMapRec(const char *name, const TObject *obj, Int_t size, void *buf);
   ~TMapRec();
   const char   *GetName(Long_t offset = 0) const { return (char *)((Long_t) fName + offset); }
   const char   *GetClassName(Long_t offset = 0) const { return (char *)((Long_t) fClassName + offset); }
   void         *GetBuffer(Long_t offset = 0) const { return (void *)((Long_t) fBuffer + offset); }
   Int_t         GetBufSize() const { return fBufSize; }
   TObject      *GetObject() const;
   TMapRec      *GetNext(Long_t offset = 0) const { return (TMapRec *)((Long_t) fNext + offset); }
```


<!-- TMapFile.md ends here -->
