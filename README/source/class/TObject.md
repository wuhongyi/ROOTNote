<!-- TObject.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 六 8月 13 16:22:48 2016 (+0800)
;; Last-Updated: 六 9月  9 14:58:30 2017 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TObject

v6.10.04

Mother of all ROOT objects.

The TObject class provides default behaviour and protocol for  
all objects in the ROOT system. It provides protocol for object I/O,  
error handling, sorting, inspection, printing, drawing, etc.  
Every object which inherits from TObject can be stored in the  
ROOT collection classes.

TObject's bits can be used as flags, bits 0 - 13 and 24-31 are  
reserved as  global bits while bits 14 - 23 can be used in different  
class hierarchies (watch out for overlaps).


## class

```cpp
   //----- Global bits (can be set for any object and should not be reused).
   //----- Bits 0 - 13 are reserved as global bits. Bits 14 - 23 can be used
   //----- in different class hierarchies (make sure there is no overlap in
   //----- any given hierarchy).
   enum EStatusBits {
      kCanDelete        = BIT(0),   ///< if object in a list can be deleted
      kMustCleanup      = BIT(3),   ///< if object destructor must call RecursiveRemove()
      kObjInCanvas      = BIT(3),   ///< for backward compatibility only, use kMustCleanup
      kIsReferenced     = BIT(4),   ///< if object is referenced by a TRef or TRefArray
      kHasUUID          = BIT(5),   ///< if object has a TUUID (its fUniqueID=UUIDNumber)
      kCannotPick       = BIT(6),   ///< if object in a pad cannot be picked
      kNoContextMenu    = BIT(8),   ///< if object does not want context menu
      kInvalidObject    = BIT(13)   ///< if object ctor succeeded but object should not be used
   };

   //----- Private bits, clients can only test but not change them
   enum {
      kIsOnHeap      = 0x01000000,    ///< object is on heap
      kNotDeleted    = 0x02000000,    ///< object has not been deleted
      kZombie        = 0x04000000,    ///< object ctor failed
      kBitMask       = 0x00ffffff
   };

   //----- Write() options
   enum {
      kSingleKey     = BIT(0),        ///< write collection with single key
      kOverwrite     = BIT(1),        ///< overwrite existing object with same name
      kWriteDelete   = BIT(2)         ///< write object, then delete previous key with same name
   };

   TObject();
   TObject(const TObject &object);
   TObject &operator=(const TObject &rhs);
   virtual ~TObject();
/// TObject destructor. Removes object from all canvases and object browsers
/// if observer bit is on and remove from the global object table.

   virtual void        AppendPad(Option_t *option="");
/// Append graphics object to current pad. In case no current pad is set
/// yet, create a default canvas with the name "c1".

   virtual void        Browse(TBrowser *b);
/// Browse object. May be overridden for another default action

   virtual const char *ClassName() const;
/// Returns name of class to which the object belongs.
   
   virtual void        Clear(Option_t * /*option*/ ="") { }
   virtual TObject    *Clone(const char *newname="") const;
/// Make a clone of an object using the Streamer facility.
/// If the object derives from TNamed, this function is called
/// by TNamed::Clone. TNamed::Clone uses the optional argument to set
/// a new name to the newly created object.
/// If the object class has a DirectoryAutoAdd function, it will be
/// called at the end of the function with the parameter gDirectory.
/// This usually means that the object will be appended to the current
/// ROOT directory.

   virtual Int_t       Compare(const TObject *obj) const;
/// Compare abstract method. Must be overridden if a class wants to be able
/// to compare itself with other objects. Must return -1 if this is smaller
/// than obj, 0 if objects are equal and 1 if this is larger than obj.

   virtual void        Copy(TObject &object) const;
   virtual void        Delete(Option_t *option=""); // *MENU*
/// Delete this object. Typically called as a command via the interpreter.
/// Normally use "delete" operator when object has been allocated on the heap.

   virtual Int_t       DistancetoPrimitive(Int_t px, Int_t py);
/// Computes distance from point (px,py) to the object.
/// This member function must be implemented for each graphics primitive.
/// This default function returns a big number (999999).

   virtual void        Draw(Option_t *option="");/// Default Draw method for all objects
   virtual void        DrawClass() const; // *MENU*
/// Draw class inheritance tree of the class to which this object belongs.
/// If a class B inherits from a class A, description of B is drawn
/// on the right side of description of A.
/// Member functions overridden by B are shown in class A with a blue line
/// crossing-out the corresponding member function.
/// The following picture is the class inheritance tree of class TPaveLabel:
/// \image html base_object.png

   virtual TObject    *DrawClone(Option_t *option="") const; // *MENU*
/// Draw a clone of this object in the current selected pad for instance with:
/// `gROOT->SetSelectedPad(gPad)`.

   virtual void        Dump() const; // *MENU*   // Get the actual address of the object.
/// Dump contents of object on stdout.
/// Using the information in the object dictionary (class TClass)
/// each data member is interpreted.
/// If a data member is a pointer, the pointer value is printed
/// The following output is the Dump of a TArrow object:
/// ~~~ {.cpp}
///   fAngle                   0           Arrow opening angle (degrees)
///   fArrowSize               0.2         Arrow Size
///   fOption.*fData
///   fX1                      0.1         X of 1st point
///   fY1                      0.15        Y of 1st point
///   fX2                      0.67        X of 2nd point
///   fY2                      0.83        Y of 2nd point
///   fUniqueID                0           object unique identifier
///   fBits                    50331648    bit field status word
///   fLineColor               1           line color
///   fLineStyle               1           line style
///   fLineWidth               1           line width
///   fFillColor               19          fill area color
///   fFillStyle               1001        fill area style
/// ~~~

   virtual void        Execute(const char *method,  const char *params, Int_t *error=0);
/// Execute method on this object with the given parameter string, e.g.
/// "3.14,1,\"text\"".

   virtual void        Execute(TMethod *method, TObjArray *params, Int_t *error=0);
/// Execute method on this object with parameters stored in the TObjArray.
/// The TObjArray should contain an argv vector like:
/// ~~~ {.cpp}
///  argv[0] ... argv[n] = the list of TObjString parameters
/// ~~~

   virtual void        ExecuteEvent(Int_t event, Int_t px, Int_t py);
/// Execute action corresponding to an event at (px,py). This method
/// must be overridden if an object can react to graphics events.

   virtual TObject    *FindObject(const char *name) const;
/// Must be redefined in derived classes.
/// This function is typically used with TCollections, but can also be used
/// to find an object by name inside this object.

   virtual TObject    *FindObject(const TObject *obj) const;
/// Must be redefined in derived classes.
/// This function is typically used with TCollections, but can also be used
/// to find an object inside this object.

   virtual Option_t   *GetDrawOption() const;
/// Get option used by the graphics system to draw this object.
/// Note that before calling object.GetDrawOption(), you must
/// have called object.Draw(..) before in the current pad.

   virtual UInt_t      GetUniqueID() const;/// Return the unique object id.
   virtual const char *GetName() const;
/// Returns name of object. This default method returns the class name.
/// Classes that give objects a name should override this method.

   virtual const char *GetIconName() const;
/// Returns mime type name of object. Used by the TBrowser (via TGMimeTypes
/// class). Override for class of which you would like to have different
/// icons for objects of the same class.

   virtual Option_t   *GetOption() const { return ""; }
   virtual char       *GetObjectInfo(Int_t px, Int_t py) const;
/// Returns string containing info about the object at position (px,py).
/// This method is typically overridden by classes of which the objects
/// can report peculiarities for different positions.
/// Returned string will be re-used (lock in MT environment).

   virtual const char *GetTitle() const;
/// Returns title of object. This default method returns the class title
/// (i.e. description). Classes that give objects a title should override
/// this method.

   virtual Bool_t      HandleTimer(TTimer *timer);
   virtual ULong_t     Hash() const;/// Return hash value for this object.
   virtual Bool_t      InheritsFrom(const char *classname) const;
/// Returns kTRUE if object inherits from class "classname".

   virtual Bool_t      InheritsFrom(const TClass *cl) const;
/// Returns kTRUE if object inherits from TClass cl.

   virtual void        Inspect() const; // *MENU*
/// Dump contents of this object in a graphics canvas.
/// Same action as Dump but in a graphical form.
/// In addition pointers to other objects can be followed.
/// The following picture is the Inspect of a histogram object:
/// \image html base_inspect.png

   virtual Bool_t      IsFolder() const;
/// Returns kTRUE in case object contains browsable objects (like containers
/// or lists of other objects).

   virtual Bool_t      IsEqual(const TObject *obj) const;
/// Default equal comparison (objects are equal if they have the same
/// address in memory). More complicated classes might want to override
/// this function.

   virtual Bool_t      IsSortable() const { return kFALSE; }
           Bool_t      IsOnHeap() const { return TestBit(kIsOnHeap); }
           Bool_t      IsZombie() const { return TestBit(kZombie); }
   virtual Bool_t      Notify();
/// This method must be overridden to handle object notification.

   virtual void        ls(Option_t *option="") const;
/// The ls function lists the contents of a class on stdout. Ls output
/// is typically much less verbose then Dump().

   virtual void        Paint(Option_t *option="");
/// This method must be overridden if a class wants to paint itself.
/// The difference between Paint() and Draw() is that when a object
/// draws itself it is added to the display list of the pad in
/// which it is drawn (and automatically redrawn whenever the pad is
/// redrawn). While paint just draws the object without adding it to
/// the pad display list.

   virtual void        Pop();
/// Pop on object drawn in a pad to the top of the display list. I.e. it
/// will be drawn last and on top of all other primitives.

   virtual void        Print(Option_t *option="") const;
/// This method must be overridden when a class wants to print itself.

   virtual Int_t       Read(const char *name);
/// Read contents of object with specified name from the current directory.
/// First the key with the given name is searched in the current directory,
/// next the key buffer is deserialized into the object.
/// The object must have been created before via the default constructor.
/// See TObject::Write().

   virtual void        RecursiveRemove(TObject *obj);
/// Recursively remove this object from a list. Typically implemented
/// by classes that can contain multiple references to a same object.

   virtual void        SaveAs(const char *filename="",Option_t *option="") const; // *MENU*
/// Save this object in the file specified by filename.
/// - if "filename" contains ".root" the object is saved in filename as root
///   binary file.
/// - if "filename" contains ".xml"  the object is saved in filename as a xml
///   ascii file.
/// - if "filename" contains ".cc" the object is saved in filename as C code
///   independant from ROOT. The code is generated via SavePrimitive().
///   Specific code should be implemented in each object to handle this
///   option. Like in TF1::SavePrimitive().
/// - otherwise the object is written to filename as a CINT/C++ script. The
///   C++ code to rebuild this object is generated via SavePrimitive(). The
///   "option" parameter is passed to SavePrimitive. By default it is an empty
///   string. It can be used to specify the Draw option in the code generated
///   by SavePrimitive.
///  The function is available via the object context menu.

   virtual void        SavePrimitive(std::ostream &out, Option_t *option = "");
/// Save a primitive as a C++ statement(s) on output stream "out".

   virtual void        SetDrawOption(Option_t *option="");  // *MENU*
/// Set drawing option for object. This option only affects
/// the drawing style and is stored in the option field of the
/// TObjOptLink supporting a TPad's primitive list (TList).
/// Note that it does not make sense to call object.SetDrawOption(option)
/// before having called object.Draw().

   virtual void        SetUniqueID(UInt_t uid);/// Set the unique object id.
   virtual void        UseCurrentStyle();
   virtual Int_t       Write(const char *name=0, Int_t option=0, Int_t bufsize=0);
/// Write this object to the current directory. For more see the
/// const version of this method.

   virtual Int_t       Write(const char *name=0, Int_t option=0, Int_t bufsize=0) const;
/// Write this object to the current directory.
/// The data structure corresponding to this object is serialized.
/// The corresponding buffer is written to the current directory
/// with an associated key with name "name".
/// Writing an object to a file involves the following steps:
///  - Creation of a support TKey object in the current directory.
///    The TKey object creates a TBuffer object.
///  - The TBuffer object is filled via the class::Streamer function.
///  - If the file is compressed (default) a second buffer is created to
///    hold the compressed buffer.
///  - Reservation of the corresponding space in the file by looking
///    in the TFree list of free blocks of the file.
///  - The buffer is written to the file.
///  Bufsize can be given to force a given buffer size to write this object.
///  By default, the buffersize will be taken from the average buffer size
///  of all objects written to the current file so far.
///  If a name is specified, it will be the name of the key.
///  If name is not given, the name of the key will be the name as returned
///  by GetName().
///  The option can be a combination of: kSingleKey, kOverwrite or kWriteDelete
///  Using the kOverwrite option a previous key with the same name is
///  overwritten. The previous key is deleted before writing the new object.
///  Using the kWriteDelete option a previous key with the same name is
///  deleted only after the new object has been written. This option
///  is safer than kOverwrite but it is slower.
///  The kSingleKey option is only used by TCollection::Write() to write
///  a container with a single key instead of each object in the container
///  with its own key.
///  An object is read from the file into memory via TKey::Read() or
///  via TObject::Read().
///  The function returns the total number of bytes written to the file.
///  It returns 0 if the object cannot be written.   

   //----- operators
   void    *operator new(size_t sz) { return TStorage::ObjectAlloc(sz); }
   void    *operator new[](size_t sz) { return TStorage::ObjectAllocArray(sz); }
   void    *operator new(size_t sz, void *vp) { return TStorage::ObjectAlloc(sz, vp); }
   void    *operator new[](size_t sz, void *vp) { return TStorage::ObjectAlloc(sz, vp); }
   void     operator delete(void *ptr);/// Operator delete
   void     operator delete[](void *ptr);/// Operator delete []
#ifdef R__SIZEDDELETE
   // Sized deallocation.
   void     operator delete(void*, size_t);
/// Operator delete for sized deallocation.   
   void     operator delete[](void*, size_t);
/// Operator delete [] for sized deallocation.   
#endif
#ifdef R__PLACEMENTDELETE
   void     operator delete(void *ptr, void *vp);
/// Only called by placement new when throwing an exception.
   
   void     operator delete[](void *ptr, void *vp);
/// Only called by placement new[] when throwing an exception.
#endif

   //----- bit manipulation
   void     SetBit(UInt_t f, Bool_t set);/// Set or unset the user status bits as specified in f.
   void     SetBit(UInt_t f) { fBits |= f & kBitMask; }
   void     ResetBit(UInt_t f) { fBits &= ~(f & kBitMask); }
   Bool_t   TestBit(UInt_t f) const { return (Bool_t) ((fBits & f) != 0); }
   Int_t    TestBits(UInt_t f) const { return (Int_t) (fBits & f); }
   void     InvertBit(UInt_t f) { fBits ^= f & kBitMask; }

   //---- error handling
   virtual void     Info(const char *method, const char *msgfmt, ...) const
#if defined(__GNUC__) && !defined(__CINT__)
   __attribute__((format(printf, 3, 4)))   /* 1 is the this pointer */
#endif
   ;
   virtual void     Warning(const char *method, const char *msgfmt, ...) const
#if defined(__GNUC__) && !defined(__CINT__)
   __attribute__((format(printf, 3, 4)))   /* 1 is the this pointer */
#endif
   ;
   virtual void     Error(const char *method, const char *msgfmt, ...) const
#if defined(__GNUC__) && !defined(__CINT__)
   __attribute__((format(printf, 3, 4)))   /* 1 is the this pointer */
#endif
   ;
   virtual void     SysError(const char *method, const char *msgfmt, ...) const
#if defined(__GNUC__) && !defined(__CINT__)
   __attribute__((format(printf, 3, 4)))   /* 1 is the this pointer */
#endif
   ;
   virtual void     Fatal(const char *method, const char *msgfmt, ...) const
#if defined(__GNUC__) && !defined(__CINT__)
   __attribute__((format(printf, 3, 4)))   /* 1 is the this pointer */
#endif
   ;

   void     AbstractMethod(const char *method) const;
/// Use this method to implement an "abstract" method that you don't
/// want to leave purely abstract.

   void     MayNotUse(const char *method) const;
/// Use this method to signal that a method (defined in a base class)
/// may not be called in a derived class (in principle against good
/// design since a child class should not provide less functionality
/// than its parent, however, sometimes it is necessary).

   void     Obsolete(const char *method, const char *asOfVers, const char *removedFromVers) const;
/// Use this method to declare a method obsolete. Specify as of which version
/// the method is obsolete and as from which version it will be removed.

   //---- static functions
   static Long_t    GetDtorOnly();/// Return destructor only flag
   static void      SetDtorOnly(void *obj);/// Set destructor only flag
   static Bool_t    GetObjectStat();/// Get status of object stat flag.
   static void      SetObjectStat(Bool_t stat);/// Turn on/off tracking of objects in the TObjectTable.

   friend class TClonesArray; // needs to reset kNotDeleted in fBits
```

```cpp
//全局
// Global bits (can be set for any object and should not be reused).
// Only here for backward compatibility reasons.
// For detailed description see TObject::EStatusBits above.
enum EObjBits {
   kCanDelete        = TObject::kCanDelete,
   kMustCleanup      = TObject::kMustCleanup,
   kObjInCanvas      = TObject::kObjInCanvas,
   kIsReferenced     = TObject::kIsReferenced,
   kHasUUID          = TObject::kHasUUID,
   kCannotPick       = TObject::kCannotPick,
   kNoContextMenu    = TObject::kNoContextMenu,
   kInvalidObject    = TObject::kInvalidObject
};
```




<!-- TObject.md ends here -->
