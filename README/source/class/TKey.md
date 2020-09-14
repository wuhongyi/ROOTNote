<!-- TKey.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 日 1月  6 13:54:54 2019 (+0800)
;; Last-Updated: 日 1月  6 14:09:44 2019 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# TKey

```
 Book space in a file, create I/O buffers, to fill them, (un)compress them.

 The TKey class includes functions to book space in a file, to create I/O
 buffers, to fill these buffers, to compress/uncompress data buffers.
 Before saving (making persistent) an object in a file, a key must
 be created. The key structure contains all the information to
 uniquely identify a persistent object in a file.
 | Data Member | Explanation |
 |-------------|-------------|
 |  fNbytes    | Number of bytes for the compressed object and key. |
 |  fObjlen    | Length of uncompressed object. |
 |  fDatime    | Date/Time when the object was written. |
 |  fKeylen    | Number of bytes for the key structure. |
 |  fCycle     | Cycle number of the object. |
 |  fSeekKey   | Address of the object on file (points to fNbytes). This is a redundant information used to cross-check the data base integrity. |
 |  fSeekPdir  | Pointer to the directory supporting this object.|
 |  fClassName | Object class name. |
 |  fName      | Name of the object. |
 |  fTitle     | Title of the object. |

 In the 16 highest bits of fSeekPdir is encoded a pid offset.  This
 offset is to be added to the pid index stored in the TRef object
 and the referenced TObject.

 The TKey class is used by ROOT to:
   - Write an object in the current directory
   - Write a new ntuple buffer

 The structure of a file is shown in TFile::TFile.
 The structure of a directory is shown in TDirectoryFile::TDirectoryFile.
 The TKey class is used by the TBasket class.
 See also TTree.
```

```cpp
class TKey : public TNamed
```

## class

```cpp
private:
   enum EStatusBits {
      kIsDirectoryFile = BIT(14)
   };
   TKey(const TKey&);            // TKey objects are not copiable.
   TKey& operator=(const TKey&); // TKey objects are not copiable.

protected:
   Int_t       fVersion;     ///< Key version identifier
   Int_t       fNbytes;      ///< Number of bytes for the object on file
   Int_t       fObjlen;      ///< Length of uncompressed object in bytes
   TDatime     fDatime;      ///< Date/Time of insertion in file
   Short_t     fKeylen;      ///< Number of bytes for the key itself
   Short_t     fCycle;       ///< Cycle number
   Long64_t    fSeekKey;     ///< Location of object on file
   Long64_t    fSeekPdir;    ///< Location of parent directory on file
   TString     fClassName;   ///< Object Class name
   Int_t       fLeft;        ///< Number of bytes left in current segment
   char       *fBuffer;      ///< Object buffer
   TBuffer    *fBufferRef;   ///< Pointer to the TBuffer object
   UShort_t    fPidOffset;   ///<!Offset to be added to the pid index in this key/buffer.  This is actually saved in the high bits of fSeekPdir
   TDirectory *fMotherDir;   ///<!pointer to mother directory

   virtual Int_t    Read(const char *name) { return TObject::Read(name); }
   virtual void     Create(Int_t nbytes, TFile* f = 0);
/// Create a TKey object of specified size.
/// If externFile!=0, key will be allocated in specified file, otherwise file
/// of mother directory will be used.   
   
           void     Build(TDirectory* motherDir, const char* classname, Long64_t filepos);
/// Method used in all TKey constructor to initialize basic data fields.
/// The member filepos is used to calculate correct version number of key
/// if filepos==-1, end of file position is used.		   
		   
   virtual void     Reset(); // Currently only for the use of TBasket.
/// Reset the key as it had not been 'filled' yet.   
   
   virtual Int_t    WriteFileKeepBuffer(TFile *f = 0);
/// Write the encoded object supported by this key.
/// The function returns the number of bytes committed to the file.
/// If a write error occurs, the number of bytes returned is -1.

 public:
   TKey();/// TKey default constructor.
   TKey(TDirectory* motherDir);/// TKey default constructor.
   TKey(TDirectory* motherDir, const TKey &orig, UShort_t pidOffset);
/// Copy a TKey from its original directory to the new 'motherDir'   
   
   TKey(const char *name, const char *title, const TClass *cl, Int_t nbytes, TDirectory* motherDir);
/// Create a TKey object with the specified name, title for the given class.
///  WARNING: in name avoid special characters like '^','$','.' that are used
///  by the regular expression parser (see TRegexp).   
   
   TKey(const TString &name, const TString &title, const TClass *cl, Int_t nbytes, TDirectory* motherDir);
/// Create a TKey object with the specified name, title for the given class.
///  WARNING: in name avoid special characters like '^','$','.' that are used
///  by the regular expression parser (see TRegexp).   
   
   TKey(const TObject *obj, const char *name, Int_t bufsize, TDirectory* motherDir);
/// Create a TKey object for a TObject* and fill output buffer
///  WARNING: in name avoid special characters like '^','$','.' that are used
///  by the regular expression parser (see TRegexp).   
   
   TKey(const void *obj, const TClass *cl, const char *name, Int_t bufsize, TDirectory* motherDir);
/// Create a TKey object for any object obj of class cl d and fill
/// output buffer.
///  WARNING: in name avoid special characters like '^','$','.' that are used
///  by the regular expression parser (see TRegexp).   
   
   TKey(Long64_t pointer, Int_t nbytes, TDirectory* motherDir = 0);
/// Create a TKey object to read keys.
/// Constructor called by TDirectoryFile::ReadKeys and by TFile::TFile.
/// A TKey object is created to read the keys structure itself.   
   
   virtual ~TKey();

   virtual void        Browse(TBrowser *b);
/// Read object from disk and call its Browse() method.
/// If object with same name already exist in memory delete it (like
/// TDirectoryFile::Get() is doing), except when the key references a
/// folder in which case we don't want to re-read the folder object
/// since it might contain new objects not yet saved.   
   
   virtual void        Delete(Option_t *option="");
/// Delete an object from the file.
/// Note: the key is not deleted. You still have to call "delete key".
/// This is different from the behaviour of TObject::Delete()!   
   
   virtual void        DeleteBuffer();/// Delete key buffer(s).
   virtual void        FillBuffer(char *&buffer);/// Encode key header into output buffer.
   virtual const char *GetClassName() const {return fClassName.Data();}
   virtual const char *GetIconName() const;/// Title can keep 32x32 xpm thumbnail/icon of the parent object.
   virtual const char *GetTitle() const;/// Returns title (title can contain 32x32 xpm thumbnail/icon).
   virtual char       *GetBuffer() const {return fBuffer+fKeylen;}
           TBuffer    *GetBufferRef() const {return fBufferRef;}
           Short_t     GetCycle() const;/// Return cycle number associated to this key.
   const   TDatime    &GetDatime() const   {return fDatime;}
           TFile      *GetFile() const;/// Returns file to which key belong.
           Short_t     GetKeep() const;/// Returns the "KEEP" status.
           Int_t       GetKeylen() const   {return fKeylen;}
           TDirectory* GetMotherDir() const { return fMotherDir; }
           Int_t       GetNbytes() const   {return fNbytes;}
           Int_t       GetObjlen() const   {return fObjlen;}
           Int_t       GetVersion() const  {return fVersion;}
   virtual Long64_t    GetSeekKey() const  {return fSeekKey;}
   virtual Long64_t    GetSeekPdir() const {return fSeekPdir;}
   virtual void        IncrementPidOffset(UShort_t offset);
/// Increment fPidOffset by 'offset'.
/// This offset is used when a key (or basket) is transfered from one file to
/// the other.  In this case the TRef and TObject might have stored a pid
/// index (to retrieve TProcessIDs) which refered to their order on the
/// original file, the fPidOffset is to be added to those values to correctly
/// find the TProcessID.  This fPidOffset needs to be increment if the
/// key/basket is copied and need to be zero for new key/basket.   
   
           Bool_t      IsFolder() const;/// Check if object referenced by the key is a folder.
   virtual void        Keep();
/// Set the "KEEP" status.
/// When the KEEP flag is set to 1 the object cannot be purged.   
   
   virtual void        ls(Option_t *option="") const;/// List Key contents.
   virtual void        Print(Option_t *option="") const;/// Print key contents.
   virtual Int_t       Read(TObject *obj);
/// To read an object from the file.
/// The object associated to this key is read from the file into memory.
/// Before invoking this function, obj has been created via the
/// default constructor.   
   
   virtual TObject    *ReadObj();
/// To read a TObject* from the file.
/// The object associated to this key is read from the file into memory
/// Once the key structure is read (via Streamer) the class identifier
/// of the object is known.
/// Using the class identifier we find the TClass object for this class.
/// A TClass object contains a full description (i.e. dictionary) of the
/// associated class. In particular the TClass object can create a new
/// object of the class type it describes. This new object now calls its
/// Streamer function to rebuilt itself.
/// Use TKey::ReadObjectAny to read any object non-derived from TObject
/// ### Note
/// A C style cast can only be used in the case where the final class
/// of this object derives from TObject as a first inheritance, otherwise
/// one must use a dynamic_cast.
/// #### Example1: simplified case
///     class MyClass : public TObject, public AnotherClass
/// then on return, one get away with using:
///     MyClass *obj = (MyClass*)key->ReadObj();
/// #### Example2: Usual case (recommended unless performance is critical)
///     MyClass *obj = dynamic_cast<MyClass*>(key->ReadObj());
/// which support also the more complex inheritance like:
///     class MyClass : public AnotherClass, public TObject
/// Of course, dynamic_cast<> can also be used in the example 1.   
   
   virtual TObject    *ReadObjWithBuffer(char *bufferRead);
/// To read a TObject* from bufferRead.
/// This function is identical to TKey::ReadObj, but it reads directly from
/// bufferRead instead of reading from a file.
/// The object associated to this key is read from the buffer into memory
/// Using the class identifier we find the TClass object for this class.
/// A TClass object contains a full description (i.e. dictionary) of the
/// associated class. In particular the TClass object can create a new
/// object of the class type it describes. This new object now calls its
/// Streamer function to rebuilt itself.
/// ### Note
/// This function is called only internally by ROOT classes.
/// Although being public it is not supposed to be used outside ROOT.
/// If used, you must make sure that the bufferRead is large enough to
/// accomodate the object being read.   
   
   /// To read an object (non deriving from TObject) from the file.
   /// This is more user friendly version of TKey::ReadObjectAny.
   /// See TKey::ReadObjectAny for more details.
   template <typename T> T *ReadObject() {
      return reinterpret_cast<T*>(ReadObjectAny(TClass::GetClass(typeid(T))));
   }
   virtual void       *ReadObjectAny(const TClass *expectedClass);
/// To read an object (non deriving from TObject) from the file.
/// If expectedClass is not null, we checked that that actual class of the
/// object stored is suitable to be stored in a pointer pointing to an object
/// of class 'expectedClass'.  We also adjust the value of the returned address
/// so that it is suitable to be cast (C-Style)
/// a pointer pointing to an object of class 'expectedClass'.
/// So for example if the class Bottom inherits from Top and the object
/// stored is of type Bottom you can safely do:
/// ~~~{.cpp}
/// auto TopClass = TClass::GetClass("Top");
/// auto ptr = (Top*) key->ReadObjectAny( TopClass );
/// if (ptr==0) printError("the object stored in the key is not of the expected type\n");
/// ~~~
/// The object associated to this key is read from the file into memory.
/// Once the key structure is read (via Streamer) the class identifier
/// of the object is known.
/// Using the class identifier we find the TClass object for this class.
/// A TClass object contains a full description (i.e. dictionary) of the
/// associated class. In particular the TClass object can create a new
/// object of the class type it describes. This new object now calls its
/// Streamer function to rebuilt itself.   
   
   virtual void        ReadBuffer(char *&buffer);
/// Decode input buffer.
/// In some situation will add key to gDirectory.   
   
           void        ReadKeyBuffer(char *&buffer);/// Decode input buffer.
   virtual Bool_t      ReadFile();/// Read the key structure from the file
   virtual void        SetBuffer() { fBuffer = new char[fNbytes];}
   virtual void        SetParent(const TObject *parent);/// Set parent in key buffer.
           void        SetMotherDir(TDirectory* dir) { fMotherDir = dir; }
   virtual Int_t       Sizeof() const;
/// Return the size in bytes of the key header structure.
/// An explaination about the nbytes (Int_t nbytes) variable used in the
/// function. The size of fSeekKey and fSeekPdir is 8 instead of 4 if version is
/// greater than 1000.
/// | Component         | Sizeof |
/// |-------------------|--------|
/// | fNbytes           | 4      |
/// | sizeof(Version_t) | 2      |
/// | fObjlen           | 4      |
/// | fKeylen           | 2      |
/// | fCycle            | 2      |
/// | fSeekKey          | 4 or 8 |
/// | fSeekPdir         | 4 or 8 |
/// | **TOTAL**         |   22   |   
   
   virtual Int_t       WriteFile(Int_t cycle=1, TFile* f = 0);   
/// Write the encoded object supported by this key.
/// The function returns the number of bytes committed to the file.
/// If a write error occurs, the number of bytes returned is -1.   
```




<!-- TKey.md ends here -->
