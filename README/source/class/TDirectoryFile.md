<!-- TDirectoryFile.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 六 8月 13 19:18:13 2016 (+0800)
;; Last-Updated: 三 9月 16 10:30:21 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 4
;; URL: http://wuhongyi.cn -->

# TDirectoryFile*

v6.10.04

继承TDirectory

Describe directory structure in a ROOT file.

A ROOT file is structured in Directories (like a file system).  
Each Directory has a list of Keys (see TKeys) and a list of objects in memory. A Key is a small object that describes the type and location of a persistent object in a file. The persistent object may be a directory.


## class

```cpp
   // TDirectory status bits
   enum { kCloseDirectory = BIT(7) };

   TDirectoryFile();
   TDirectoryFile(const char *name, const char *title, Option_t *option="", TDirectory* motherDir = 0);
/// Create a new TDirectoryFile
///  A new directory with a name and a title is created in the current directory.
///  The directory header information is immediatly saved on the file
///  A new key is added in the parent directory.
///  When this constructor is called from a class directly derived
///  from TDirectoryFile, the third argument, classname, MUST be specified.
///  In this case, classname must be the name of the derived class.
///  Note that the directory name cannot contain slashes.

   virtual ~TDirectoryFile();
   virtual void        Append(TObject *obj, Bool_t replace = kFALSE);
/// Append object to this directory.
/// If replace is true:
///   remove any existing objects with the same same (if the name is not ""

           void        Add(TObject *obj, Bool_t replace = kFALSE) { Append(obj,replace); }
           Int_t       AppendKey(TKey *key);/// Insert key in the linked list of keys of this directory.
   virtual void        Browse(TBrowser *b);/// Browse the content of the directory.
           void        Build(TFile* motherFile = 0, TDirectory* motherDir = 0);/// Initialise directory to defaults.
   virtual TObject    *CloneObject(const TObject *obj, Bool_t autoadd = kTRUE);
/// Make a clone of an object using the Streamer facility.
/// If the object derives from TNamed, this function is called
/// by TNamed::Clone. TNamed::Clone uses the optional argument newname to set
/// a new name to the newly created object.
/// If autoadd is true and if the object class has a
/// DirectoryAutoAdd function, it will be called at the end of the
/// function with the parameter gDirectory.  This usually means that
/// the object will be appended to the current ROOT directory.

   virtual void        Close(Option_t *option="");/// Delete all objects from memory and directory structure itself.
   virtual void        Copy(TObject &) const { MayNotUse("Copy(TObject &)"); }
   virtual Bool_t      cd(const char *path = 0);
/// Change current directory to "this" directory.
/// Using path one can
/// change the current directory to "path". The absolute path syntax is:
///     file.root:/dir1/dir2
/// where file.root is the file and /dir1/dir2 the desired subdirectory
/// in the file. Relative syntax is relative to "this" directory. E.g:
/// ../aa. Returns kTRUE in case of success.

   virtual void        Delete(const char *namecycle="");
/// Delete Objects or/and keys in a directory
/// Properties of the namecycle string:
///   - namecycle has the format name;cycle
///   - namecycle = "" is same as namecycle ="T*"
///   - name  = * means all
///   - cycle = * means all cycles (memory and keys)
///   - cycle = "" or cycle = 9999 ==> apply to a memory object
/// When name=* use T* to delete subdirectories also
/// To delete one directory, you must specify the directory cycle,
/// eg.  file.Delete("dir1;1");
/// Examples:
/// | Pattern | Description |
/// |---------|-------------|
/// |   foo   | delete object named foo in memory |
/// |   foo*  | delete all objects with a name starting with foo |
/// |   foo;1 | delete cycle 1 of foo on file |
/// |   foo;* | delete all cycles of foo on file and also from memory |
/// |   *;2   | delete all objects on file having the cycle 2 |
/// |   *;*   | delete all objects from memory and file |
/// |   T*;*  | delete all objects from memory and file and all subdirectories |
/// ## WARNING
/// If the key to be deleted contains special characters ("+","^","?", etc
/// that have a special meaning for the regular expression parser (see TRegexp)
/// then you must specify 2 backslash characters to escape the regular expression.
/// For example, if the key to be deleted is namecycle = "C++", you must call
///     mydir.Delete("C\\+\\+"));

   virtual void        FillBuffer(char *&buffer);
/// Encode directory header into output buffer

   virtual TKey       *FindKey(const char *keyname) const;
/// Find key with name keyname in the current directory

   virtual TKey       *FindKeyAny(const char *keyname) const;
/// Find key with name keyname in the current directory or
/// its subdirectories.
/// NOTE: that If a key is found, the directory containing the key becomes
/// the current directory

   virtual TObject    *FindObjectAny(const char *name) const;
/// Find object by name in the list of memory objects of the current
/// directory or its sub-directories.
/// After this call the current directory is not changed.
/// To automatically set the current directory where the object is found,
/// use FindKeyAny(aname)->ReadObj().

   virtual TObject    *FindObjectAnyFile(const char *name) const;
/// Scan the memory lists of all files for an object with name

   virtual TObject    *Get(const char *namecycle);
/// Return pointer to object identified by namecycle.
/// Properties:
///   - namecycle has the format name;cycle
///   - name  = * is illegal, cycle = * is illegal
///   - cycle = "" or cycle = 9999 ==> apply to a memory object
/// Examples:
/// | Pattern | Explanation |
/// |---------|-------------|
/// |  foo    | get object named foo in memory if object is not in memory, try with highest cycle from file |
/// |  foo;1  | get cycle 1 of foo on file |
/// The retrieved object should in principle derive from TObject.
/// If not, the function TDirectoryFile::GetObject should be called.
/// However, this function will still work for a non-TObject, provided that
/// the calling application cast the return type to the correct type (which
/// is the actual type of the object).
/// ### The GetObjectMethod
/// The method GetObject offers better protection and avoids the need
/// for any cast:
/// ~~~{.cpp}
/// MyClass *obj;
/// directory->GetObject("some object",obj);
/// if (obj) { ... the object exist and inherits from MyClass ... }
/// ~~~
/// ### Very important note about inheritance
/// In case the class of this object derives from TObject but not
/// as a first inheritance, one must use dynamic_cast<>().
/// #### Example 1 - Normal case:
///     class MyClass : public TObject, public AnotherClass
/// then on return, one can adopt a C style cast:
///     auto objPtr = (MyClass*)directory->Get("some object of MyClass");
/// #### Example 2 - Special case:
///     class MyClass : public AnotherClass, public TObject
/// then on return, one must do:
///     auto objPtr = dynamic_cast<MyClass*>(directory->Get("some object of MyClass"));
/// Of course, dynamic_cast<> can also be used in the example 1.

   virtual TDirectory *GetDirectory(const char *apath, Bool_t printError = false, const char *funcname = "GetDirectory");
/// Find a directory named "apath".
/// It apath is null or empty, returns "this" directory.
/// Otherwise use the name "apath" to find a directory.
/// The absolute path syntax is:
///     file.root:/dir1/dir2
/// where file.root is the file and /dir1/dir2 the desired subdirectory
/// in the file. Relative syntax is relative to "this" directory. E.g:
/// ../aa.
/// Returns 0 in case path does not exist.
/// If printError is true, use Error with 'funcname' to issue an error message.

   template <class T> inline void GetObject(const char* namecycle, T*& ptr) // See TDirectory::Get for information
      {
         ptr = (T*)GetObjectChecked(namecycle,TBuffer::GetClass(typeid(T)));
      }
   virtual void       *GetObjectChecked(const char *namecycle, const char* classname);
/// See documentation of TDirectoryFile::GetObjectCheck(const char *namecycle, const TClass *cl)

   virtual void       *GetObjectChecked(const char *namecycle, const TClass* cl);
/// Return pointer to object identified by namecycle if and only if the actual
/// object is a type suitable to be stored as a pointer to a "expectedClass"
/// If expectedClass is null, no check is performed.
///   - namecycle has the format name;cycle
///   - name  = * is illegal, cycle = * is illegal
///   - cycle = "" or cycle = 9999 ==> apply to a memory object
/// ### Very important note
/// The calling application must cast the returned pointer to
/// the type described by the 2 arguments (i.e. cl):
/// auto objPtr = (MyClass*)directory->GetObjectChecked("some object of MyClass","MyClass"));
/// Note: We recommend using the method TDirectoryFile::GetObject:
/// ~~~{.cpp}
/// MyClass *obj = nullptr;
/// directory->GetObject("some object inheriting from MyClass",obj);
/// if (obj) { ... we found what we are looking for ... }
/// ~~~

   virtual void       *GetObjectUnchecked(const char *namecycle);
/// Return pointer to object identified by namecycle.
/// The returned object may or may not derive from TObject.
///   - namecycle has the format name;cycle
///   - name  = * is illegal, cycle = * is illegal
///   - cycle = "" or cycle = 9999 ==> apply to a memory object
/// ## Very important note
/// The calling application must cast the returned object to
/// the final type, e.g.
///   auto objPtr = (MyClass*)directory->GetObject("some object of MyClass");

   virtual Int_t       GetBufferSize() const;
/// Return the buffer size to create new TKeys.
/// If the stored fBufferSize is null, the value returned is the average
/// buffer size of objects in the file so far.

   const TDatime      &GetCreationDate() const { return fDatimeC; }
   virtual TFile      *GetFile() const { return fFile; }
   virtual TKey       *GetKey(const char *name, Short_t cycle=9999) const;
/// Return pointer to key with name,cycle
///  if cycle = 9999 returns highest cycle

   virtual TList      *GetListOfKeys() const { return fKeys; }
   const TDatime      &GetModificationDate() const { return fDatimeM; }
   virtual Int_t       GetNbytesKeys() const { return fNbytesKeys; }
   virtual Int_t       GetNkeys() const { return fKeys->GetSize(); }
   virtual Long64_t    GetSeekDir() const { return fSeekDir; }
   virtual Long64_t    GetSeekParent() const { return fSeekParent; }
   virtual Long64_t    GetSeekKeys() const { return fSeekKeys; }
   Bool_t              IsModified() const { return fModified; }
   Bool_t              IsWritable() const { return fWritable; }
   virtual void        ls(Option_t *option="") const;
/// List Directory contents
/// Indentation is used to identify the directory tree
/// Subdirectories are listed first, then objects in memory, then objects on the file
/// The option can has the following format: <b>[-d |-m][<regexp>]</b>
/// Options:
///   - -d: only list objects in the file
///   - -m: only list objects in memory
///  The <regexp> will be used to match the name of the objects.
///  By default memory and disk objects are listed.

   virtual TDirectory *mkdir(const char *name, const char *title="");
/// Create a sub-directory "a" or a hierarchy of sub-directories "a/b/c/...".
/// Returns 0 in case of error or if a sub-directory (hierarchy) with the requested
/// name already exists.
/// Returns a pointer to the created sub-directory or to the top sub-directory of
/// the hierarchy (in the above example, the returned TDirectory * always points
/// to "a").

   virtual TFile      *OpenFile(const char *name, Option_t *option= "",
                            const char *ftitle = "", Int_t compress = 1,
                            Int_t netopt = 0);/// Interface to TFile::Open
    virtual void        Purge(Short_t nkeep=1);
/// Purge lowest key cycles in a directory.
/// By default, only the highest cycle of a key is kept. Keys for which
/// the "KEEP" flag has been set are not removed. See TKey::Keep().

   virtual void        ReadAll(Option_t *option="");
/// Read objects from a ROOT file directory into memory.
/// If an object is already in memory, the memory copy is deleted
/// and the object is again read from the file.
/// If opt=="dirs", only subdirectories will be read
/// If opt=="dirs*" complete directory tree will be read

   virtual Int_t       ReadKeys(Bool_t forceRead=kTRUE);
/// Read the linked list of keys.
/// Every directory has a linked list (fKeys). This linked list has been
/// written on the file via WriteKeys as a single data record.
/// It is interesting to call this function in the following situation.
/// Assume another process1 is connecting this directory in Update mode
///   - Process1 is adding/updating objects in this directory
///   - You want to see the latest status from process1.
/// Example Process1:
/// ~~~{.cpp}
/// obj1.Write();
/// obj2.Write();
/// gDirectory->SaveSelf();
/// ~~~
/// Example Process2:
/// ~~~{.cpp}
/// gDirectory->ReadKeys();
/// obj1->Draw();
/// ~~~
/// This is an efficient way (without opening/closing files) to view
/// the latest updates of a file being modified by another process
/// as it is typically the case in a data acquisition system.

   virtual Int_t       ReadTObject(TObject *obj, const char *keyname);
/// Read object with keyname from the current directory
/// Read contents of object with specified name from the current directory.
/// First the key with keyname is searched in the current directory,
/// next the key buffer is deserialized into the object.
/// The object must have been created before via the default constructor.
/// See TObject::Write().

   virtual void        ResetAfterMerge(TFileMergeInfo *);
/// Reset the TDirectory after its content has been merged into another
/// Directory.
/// This returns the TDirectoryFile object back to its state
/// before any data has been written to the file.
/// The object in the in-memory list are assumed to also have been reset.

   virtual void        rmdir(const char *name);
/// Removes subdirectory from the directory
/// When diredctory is deleted, all keys in all subdirectories will be
/// read first and deleted from file (if exists)
/// Equivalent call is Delete("name;*");

   virtual void        Save();/// Save recursively all directory keys and headers
   virtual void        SaveSelf(Bool_t force = kFALSE);
/// Save Directory keys and header
/// If the directory has been modified (fModified set), write the keys
/// and the directory header. This function assumes the cd is correctly set.
/// It is recommended to use this function in the following situation:
/// Assume a process1 using a directory in Update mode
///   - New objects or modified objects have been written to the directory.
///   - You do not want to close the file.
///   - You want your changes be visible from another process2 already connected
///     to this directory in read mode.
///   - Call this function.
///   - In process2, use TDirectoryFile::ReadKeys to refresh the directory.

   virtual Int_t       SaveObjectAs(const TObject *obj, const char *filename="", Option_t *option="") const;
/// Save object in filename.
/// If filename is 0 or "", a file with "objectname.root" is created.
/// The name of the key is the object name.
/// If the operation is successful, it returns the number of bytes written to the file
/// otherwise it returns 0.
/// By default a message is printed. Use option "q" to not print the message.
/// If filename contains ".json" extension, JSON representation of the object
/// will be created and saved in the text file. Such file can be used in
/// JavaScript ROOT (https://root.cern.ch/js/) to display object in web browser
/// When creating JSON file, option string may contain compression level from 0 to 3 (default 0)

   virtual void        SetBufferSize(Int_t bufsize);
/// Set the default buffer size when creating new TKeys.
/// See also TDirectoryFile::GetBufferSize

   void                SetModified() {fModified = kTRUE;}
   void                SetSeekDir(Long64_t v) { fSeekDir = v; }
   virtual void        SetTRefAction(TObject *ref, TObject *parent);
/// Find the action to be executed in the dictionary of the parent class
/// and store the corresponding exec number into fBits.
/// This function searches a data member in the class of parent with an
/// offset corresponding to this.
/// If a comment "TEXEC:" is found in the comment field of the data member,
/// the function stores the exec identifier of the exec statement
/// following this keyword.

   void                SetWritable(Bool_t writable=kTRUE);
///  Set the new value of fWritable recursively

   virtual Int_t       Sizeof() const;
/// Return the size in bytes of the directory header

   virtual Int_t       Write(const char *name=0, Int_t opt=0, Int_t bufsize=0);
/// Write all objects in memory to disk.
/// Loop on all objects in memory (including subdirectories).
/// A new key is created in the keys linked list for each object.
/// For allowed options see TObject::Write().
/// The directory header info is rewritten on the directory header record.   

   virtual Int_t       Write(const char *name=0, Int_t opt=0, Int_t bufsize=0) const ;
/// One can not save a const TDirectory object.

   virtual Int_t       WriteTObject(const TObject *obj, const char *name=0, Option_t *option="", Int_t bufsize=0);
/// Write object obj to this directory.
/// The data structure corresponding to this object is serialized.
/// The corresponding buffer is written to this directory
/// with an associated key with name "name".
/// Writing an object to a file involves the following steps:
///   - Creation of a support TKey object in the directory. The TKey object
/// creates a TBuffer object.
///   - The TBuffer object is filled via the class::Streamer function.
///   - If the file is compressed (default) a second buffer is created to hold
/// the compressed buffer.
///   - Reservation of the corresponding space in the file by looking in the
/// TFree list of free blocks of the file.
///   - The buffer is written to the file.
/// By default, the buffersize will be taken from the average buffer size
/// of all objects written to the current file so far.
/// Use TDirectoryFile::SetBufferSize to force a given buffer size.
/// If a name is specified, it will be the name of the key.
/// If name is not given, the name of the key will be the name as returned
/// by obj->GetName().
/// The option can be a combination of:
///   - "SingleKey"
///   - "Overwrite"
///   - "WriteDelete"
/// Using the "Overwrite" option a previous key with the same name is
/// overwritten. The previous key is deleted before writing the new object.
/// Using the "WriteDelete" option a previous key with the same name is
/// deleted only after the new object has been written. This option
/// is safer than kOverwrite but it is slower.
/// The "SingleKey" option is only used by TCollection::Write() to write
/// a container with a single key instead of each object in the container
/// with its own key.
/// An object is read from this directory via TDirectoryFile::Get.
/// The function returns the total number of bytes written to the directory.
/// It returns 0 if the object cannot be written.
/// WARNING: avoid special characters like '^','$','.' in the name as they
/// are used by the regular expression parser (see TRegexp).

   virtual Int_t       WriteObjectAny(const void *obj, const char *classname, const char *name, Option_t *option="", Int_t bufsize=0);
/// Write object from pointer of class classname in this directory.
/// obj may not derive from TObject. See TDirectoryFile::WriteTObject for comments
/// ## Very important note
/// The value passed as 'obj' needs to be from a pointer to the type described by classname.
/// For example:
/// ~~~{.cpp}
/// TopClass *top;
/// BottomClass *bottom;
/// top = bottom;
/// ~~~
/// you can do:
/// ~~~{.cpp}
/// directory->WriteObjectAny(top,"top","name of object");
/// directory->WriteObjectAny(bottom,"bottom","name of object");
/// ~~~
/// <b>BUT YOU CAN NOT DO</b> the following since it will fail with multiple inheritance:
/// ~~~{.cpp}
/// directory->WriteObjectAny(top,"bottom","name of object");
/// ~~~
/// We <b>STRONGLY</b> recommend to use
/// ~~~{.cpp}
/// TopClass *top = ....;
/// directory->WriteObject(top,"name of object")
/// ~~~
/// See also remarks in TDirectoryFile::WriteTObject

   virtual Int_t       WriteObjectAny(const void *obj, const TClass *cl, const char *name, Option_t *option="", Int_t bufsize=0);
/// Write object of class with dictionary cl in this directory.
/// obj may not derive from TObject
/// To get the TClass* cl pointer, one can use
///     TClass *cl = TClass::GetClass("classname");
/// An alternative is to call the function WriteObjectAny above.
/// see TDirectoryFile::WriteTObject for comments

   virtual void        WriteDirHeader();/// Overwrite the Directory header record.
   virtual void        WriteKeys();
/// Write Keys linked list on the file.
///  The linked list of keys (fKeys) is written as a single data record  
```

<!-- TDirectoryFile.md ends here -->
