<!-- TDirectory.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 六 8月 13 19:14:29 2016 (+0800)
;; Last-Updated: 三 9月 16 10:30:14 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 4
;; URL: http://wuhongyi.cn -->

# TDirectory*

v6.10.04

继承TNamed

Describe directory structure in memory.

```
This class defines an abstract interface that must be implemented    
by all classes that contain dictionary information.                  
                                                                     
The dictionary is defined by the followling classes:                 
TDataType                              (typedef definitions)         
TGlobal                                (global variables)            
TFunction                              (global functions)            
TClass                                 (classes)                     
   TBaseClass                          (base classes)                
   TDataMember                         (class datamembers)           
   TMethod                             (class methods)               
      TMethodArg                       (method arguments)            
                                                                     
All the above classes implement the TDictionary abstract interface   
(note: the indentation shows aggregation not inheritance).           
The ROOT dictionary system provides a very extensive RTTI            
environment that facilitates a.o. object inspectors, object I/O,     
ROOT Trees, etc. Most of the type information is provided by the     
CINT C++ interpreter.                                                
                                                                     
TMethodCall                            (method call environment)     
```


## class

```cpp
// 全局
#ifndef __CINT__
#define gDirectory (TDirectory::CurrentDirectory())

#elif defined(__MAKECINT__)
// To properly handle the use of gDirectory in header files (in static declarations)
R__EXTERN TDirectory *gDirectory;
#endif
```


```cpp
   /** @class Context
     *
     *  Small helper to keep current directory context.
     *  Automatically reverts to "old" directory
     */
   class TContext  {
   private:
      TDirectory *fDirectory;   //! Pointer to the previous current directory.
      TContext   *fPrevious;    //! Pointer to the next TContext in the implied list of context pointing to fPrevious.
      TContext   *fNext;        //! Pointer to the next TContext in the implied list of context pointing to fPrevious.
      TContext(TContext&);
      TContext& operator=(TContext&);
      void CdNull();
      friend class TDirectory;
   public:
      TContext(TDirectory* previous, TDirectory* newCurrent)
         : fDirectory(previous),fPrevious(0),fNext(0)
      {
         // Store the current directory so we can restore it
         // later and cd to the new directory.
         if ( fDirectory ) fDirectory->RegisterContext(this);
         if ( newCurrent ) newCurrent->cd();
         else CdNull();
      }
      TContext() : fDirectory(TDirectory::CurrentDirectory()),fPrevious(0),fNext(0)
      {
         // Store the current directory so we can restore it
         // later and cd to the new directory.
         if ( fDirectory ) fDirectory->RegisterContext(this);
      }
      TContext(TDirectory* newCurrent) : fDirectory(TDirectory::CurrentDirectory()),fPrevious(0),fNext(0)
      {
         // Store the current directory so we can restore it
         // later and cd to the new directory.
         if ( fDirectory ) fDirectory->RegisterContext(this);
         if ( newCurrent ) newCurrent->cd();
         else CdNull();
      }
      ~TContext()
      {
         // Destructor.   Reset the current directory to its
         // previous state.
         if ( fDirectory ) {
            fDirectory->UnregisterContext(this);
            fDirectory->cd();
         }
         else CdNull();
      }
   };



   TDirectory();
/// Create a new Directory.
///  A new directory with name,title is created in the current directory
///  The directory header information is immediately saved in the file
///  A new key is added in the parent directory
///  When this constructor is called from a class directly derived
///  from TDirectory, the third argument classname MUST be specified.
///  In this case, classname must be the name of the derived class.
///  Note that the directory name cannot contain slashes.

   TDirectory(const char *name, const char *title, Option_t *option="", TDirectory* motherDir = 0);
   virtual ~TDirectory();
   static  void        AddDirectory(Bool_t add=kTRUE);
/// Sets the flag controlling the automatic add objects like histograms, TGraph2D, etc
/// in memory
/// By default (fAddDirectory = kTRUE), these objects are automatically added
/// to the list of objects in memory.
/// Note that in the classes like TH1, TGraph2D supporting this facility,
/// one object can be removed from its support directory
/// by calling object->SetDirectory(0) or object->SetDirectory(dir) to add it
/// to the list of objects in the directory dir.
///  NOTE that this is a static function. To call it, use:
/// ~~~ {.cpp}
///     TDirectory::AddDirectory
/// ~~~

   static  Bool_t      AddDirectoryStatus();
/// Static function: see TDirectory::AddDirectory for more comments.

   virtual void        Append(TObject *obj, Bool_t replace = kFALSE);
/// Append object to this directory.
/// If `replace` is true:
///   remove any existing objects with the same name (if the name is not "")

   virtual void        Add(TObject *obj, Bool_t replace = kFALSE) { Append(obj,replace); }
   virtual Int_t       AppendKey(TKey *) {return 0;}
   virtual void        Browse(TBrowser *b);/// Browse the content of the directory.
   virtual void        Build(TFile* motherFile = 0, TDirectory* motherDir = 0);
/// Initialise directory to defaults.
/// If directory is created via default ctor (when dir is read from file)
/// don't add it here to the directory since its name is not yet known.
/// It will be added to the directory in TKey::ReadObj().

   virtual void        Clear(Option_t *option="");
/// Delete all objects from a Directory list.

   virtual TObject    *CloneObject(const TObject *obj, Bool_t autoadd = kTRUE);
/// Clone an object.
/// This function is called when the directory is not a TDirectoryFile.
/// This version has to load the I/O package, hence via Cling.
/// If autoadd is true and if the object class has a
/// DirectoryAutoAdd function, it will be called at the end of the
/// function with the parameter gDirector.  This usually means that
/// the object will be appended to the current ROOT directory.

   virtual void        Close(Option_t *option="");
/// Delete all objects from memory and directory structure itself.

   static TDirectory *&CurrentDirectory();  // Return the current directory for this thread.
   virtual void        Copy(TObject &) const { MayNotUse("Copy(TObject &)"); }
   virtual Bool_t      cd(const char *path = 0);
/// Change current directory to "this" directory.
/// Using path one can change the current directory to "path". The absolute path
/// syntax is: `file.root:/dir1/dir2`
/// where `file.root` is the file and `/dir1/dir2` the desired subdirectory
/// in the file.
/// Relative syntax is relative to "this" directory. E.g: `../aa`.
/// Returns kTRUE in case of success.

   virtual void        DeleteAll(Option_t *option="");
/// Delete all objects from memory.

   virtual void        Delete(const char *namecycle="");
/// Delete Objects or/and keys in a directory.
///  - namecycle has the format name;cycle
///  - namecycle = "" same as namecycle ="T*"
///  - name  = * means all
///  - cycle = * means all cycles (memory and keys)
///  - cycle = "" or cycle = 9999 ==> apply to a memory object
///    When name=* use T* to delete subdirectories also
/// To delete one directory, you must specify the directory cycle,
/// eg.  `file.Delete("dir1;1");`
/// examples:
///  - foo   : delete object named foo in memory
///  - foo*  : delete all objects with a name starting with foo
///  - foo;1 : delete cycle 1 of foo on file
///  - foo;* : delete all cycles of foo on file and also from memory
///  - *;2   : delete all objects on file having the cycle 2
///  - *;*   : delete all objects from memory and file
///  - T*;*  : delete all objects from memory and file and all subdirectories

   virtual void        Draw(Option_t *option="");
/// Fill Graphics Structure and Paint.
/// Loop on all objects (memory or file) and all subdirectories

   virtual TKey       *FindKey(const char * /*keyname*/) const {return 0;}
   virtual TKey       *FindKeyAny(const char * /*keyname*/) const {return 0;}
   virtual TObject    *FindObject(const char *name) const;
/// Find object in the list of memory objects.

   virtual TObject    *FindObject(const TObject *obj) const;
/// Find object by name in the list of memory objects.

   virtual TObject    *FindObjectAny(const char *name) const;
/// Find object by name in the list of memory objects of the current
/// directory or its sub-directories.
/// After this call the current directory is not changed.
/// To automatically set the current directory where the object is found,
/// use FindKeyAny(aname)->ReadObj().

   virtual TObject    *FindObjectAnyFile(const char * /*name*/) const {return 0;}
   virtual TObject    *Get(const char *namecycle);
/// Return pointer to object identified by namecycle.
///   namecycle has the format name;cycle
///  - name  = * is illegal, cycle = * is illegal
///  - cycle = "" or cycle = 9999 ==> apply to a memory object
/// examples:
///  - foo   : get object named foo in memory
///                if object is not in memory, try with highest cycle from file
///  - foo;1 : get cycle 1 of foo on file
///  The retrieved object should in principle derive from TObject.
///  If not, the function TDirectory::GetObject should be called.
///  However, this function will still work for a non-TObject, providing that
///  the calling application cast the return type to the correct type (which
///  is the actual type of the object).
///  NOTE:
///  The method GetObject offer better protection and avoid the need
///  for any cast:
/// ~~~ {.cpp}
///      MyClass *obj;
///      directory->GetObject("some object",obj);
///      if (obj) { ... the object exist and inherits from MyClass ... }
/// ~~~
///  VERY IMPORTANT NOTE:
///  In case the class of this object derives from TObject but not
///  as a first inheritance, one must use dynamic_cast<>().
/// #### Example 1: Normal case:
/// ~~~ {.cpp}
///      class MyClass : public TObject, public AnotherClass
/// ~~~
///   then on return, one can do:
/// ~~~ {.cpp}
///      MyClass *obj = (MyClass*)directory->Get("some object of MyClass");
/// ~~~
/// #### Example 2: Special case:
/// ~~~ {.cpp}
///      class MyClass : public AnotherClass, public TObject
/// ~~~
///  then on return, one must do:
/// ~~~ {.cpp}
///      MyClass *obj = dynamic_cast<MyClass*>(directory->Get("some object of MyClass"));
/// ~~~
///  Of course, dynamic_cast<> can also be used in the example 1.

   virtual TDirectory *GetDirectory(const char *namecycle, Bool_t printError = false, const char *funcname = "GetDirectory");
/// Find a directory using apath.
/// It apath is null or empty, returns "this" directory.
/// Otherwise use apath to find a directory.
/// The absolute path syntax is: `file.root:/dir1/dir2`
/// where file.root is the file and /dir1/dir2 the desired subdirectory
/// in the file. Relative syntax is relative to "this" directory. E.g: `../aa`.
/// Returns 0 in case path does not exist.
/// If printError is true, use Error with 'funcname' to issue an error message.

   template <class T> inline void GetObject(const char* namecycle, T*& ptr) // See TDirectory::Get for information
      {
         ptr = (T*)GetObjectChecked(namecycle,TBuffer::GetClass(typeid(T)));
      }
   virtual void       *GetObjectChecked(const char *namecycle, const char* classname);
/// See documentation of TDirectory::GetObjectCheck(const char *namecycle, const TClass *cl)

   virtual void       *GetObjectChecked(const char *namecycle, const TClass* cl);
/// Return pointer to object identified by namecycle if and only if the actual
/// object is a type suitable to be stored as a pointer to a "expectedClass"
/// If expectedClass is null, no check is performed.
/// namecycle has the format `name;cycle`
///  - name  = * is illegal, cycle = * is illegal
///  - cycle = "" or cycle = 9999 ==> apply to a memory object
///  VERY IMPORTANT NOTE:
///  The calling application must cast the returned pointer to
///  the type described by the 2 arguments (i.e. cl):
/// ~~~ {.cpp}
///      MyClass *obj = (MyClass*)directory->GetObjectChecked("some object of MyClass","MyClass"));
/// ~~~
///  Note: We recommend using the method TDirectory::GetObject:
/// ~~~ {.cpp}
///      MyClass *obj = 0;
///      directory->GetObject("some object inheriting from MyClass",obj);
///      if (obj) { ... we found what we are looking for ... }
/// ~~~

   virtual void       *GetObjectUnchecked(const char *namecycle);
/// Return pointer to object identified by namecycle.
/// The returned object may or may not derive from TObject.
///  - namecycle has the format name;cycle
///  - name  = * is illegal, cycle = * is illegal
///  - cycle = "" or cycle = 9999 ==> apply to a memory object
///  VERY IMPORTANT NOTE:
///  The calling application must cast the returned object to
///  the final type, e.g.
/// ~~~ {.cpp}
///      MyClass *obj = (MyClass*)directory->GetObject("some object of MyClass");
/// ~~~

   virtual Int_t       GetBufferSize() const {return 0;}
   virtual TFile      *GetFile() const { return 0; }
   virtual TKey       *GetKey(const char * /*name */, Short_t /* cycle */=9999) const {return 0;}
   virtual TList      *GetList() const { return fList; }
   virtual TList      *GetListOfKeys() const { return 0; }
   virtual TObject    *GetMother() const { return fMother; }
   virtual TDirectory *GetMotherDir() const { return fMother==0 ? 0 : dynamic_cast<TDirectory*>(fMother); }
   virtual Int_t       GetNbytesKeys() const { return 0; }
   virtual Int_t       GetNkeys() const { return 0; }
   virtual Long64_t    GetSeekDir() const { return 0; }
   virtual Long64_t    GetSeekParent() const { return 0; }
   virtual Long64_t    GetSeekKeys() const { return 0; }
   virtual const char *GetPathStatic() const;
/// Returns the full path of the directory. E.g. `file:/dir1/dir2`.
/// The returned path will be re-used by the next call to GetPath().

   virtual const char *GetPath() const;
/// Returns the full path of the directory. E.g. `file:/dir1/dir2`.
/// The returned path will be re-used by the next call to GetPath().

   TUUID               GetUUID() const {return fUUID;}
   virtual Bool_t      IsFolder() const { return kTRUE; }
   virtual Bool_t      IsModified() const { return kFALSE; }
   virtual Bool_t      IsWritable() const { return kFALSE; }
   virtual void        ls(Option_t *option="") const;
/// List Directory contents.
/// Indentation is used to identify the directory tree
/// Subdirectories are listed first, then objects in memory.
/// The option can has the following format:
///      [<regexp>]
/// The `<regexp>` will be used to match the name of the objects.
/// By default memory and disk objects are listed.

   virtual TDirectory *mkdir(const char *name, const char *title="");
/// Create a sub-directory "a" or a hierarchy of sub-directories "a/b/c/...".
/// Returns 0 in case of error or if a sub-directory (hierarchy) with the requested
/// name already exists.
/// Returns a pointer to the created sub-directory or to the top sub-directory of
/// the hierarchy (in the above example, the returned TDirectory * always points
/// to "a").
/// In particular, the steps to create first a/b/c and then a/b/d without receiving
/// errors are:
/// ~~~ {.cpp}
///    TFile * file = new TFile("afile","RECREATE");
///    file->mkdir("a");
///    file->cd("a");
///    gDirectory->mkdir("b/c");
///    gDirectory->cd("b");
///    gDirectory->mkdir("d");
/// ~~~

   virtual TFile      *OpenFile(const char * /*name*/, Option_t * /*option*/ = "",
                            const char * /*ftitle*/ = "", Int_t /*compress*/ = 1,
                            Int_t /*netopt*/ = 0) {return 0;}
   virtual void        Paint(Option_t *option="");/// Paint all objects in the directory.
   virtual void        Print(Option_t *option="") const;/// Print all objects in the directory.
   virtual void        Purge(Short_t /*nkeep*/=1) {}
   virtual void        pwd() const;/// Print the path of the directory.
   virtual void        ReadAll(Option_t * /*option*/="") {}
   virtual Int_t       ReadKeys(Bool_t /*forceRead*/=kTRUE) {return 0;}
   virtual Int_t       ReadTObject(TObject * /*obj*/, const char * /*keyname*/) {return 0;}
   virtual TObject    *Remove(TObject*);/// Remove an object from the in-memory list.
   virtual void        RecursiveRemove(TObject *obj);/// Recursively remove object from a Directory.
   virtual void        rmdir(const char *name);
/// Removes subdirectory from the directory
/// When directory is deleted, all keys in all subdirectories will be
/// read first and deleted from file (if exists)
/// Equivalent call is Delete("name;*");

   virtual void        Save() {}
   virtual Int_t       SaveObjectAs(const TObject * /*obj*/, const char * /*filename*/="", Option_t * /*option*/="") const;
/// Save object in filename,
/// if filename is 0 or "", a file with "objectname.root" is created.
/// The name of the key is the object name.
/// If the operation is successful, it returns the number of bytes written to the file
/// otherwise it returns 0.
/// By default a message is printed. Use option "q" to not print the message.
/// If filename contains ".json" extension, JSON representation of the object
/// will be created and saved in the text file. Such file can be used in
/// JavaScript ROOT (https://root.cern.ch/js/) to display object in web browser
/// When creating JSON file, option string may contain compression level from 0 to 3 (default 0)

   virtual void        SaveSelf(Bool_t /*force*/ = kFALSE) {}
   virtual void        SetBufferSize(Int_t /* bufsize */) {}
   virtual void        SetModified() {}
   virtual void        SetMother(TObject *mother) {fMother = (TObject*)mother;}
   virtual void        SetName(const char* newname);
/// Set the name for directory
/// If the directory name is changed after the directory was written once,
/// ROOT currently would NOT change the name of correspondent key in the
/// mother directory.
/// DO NOT use this method to 'rename a directory'.
/// Renaming a directory is currently NOT supported.

   virtual void        SetTRefAction(TObject * /*ref*/, TObject * /*parent*/) {}
   virtual void        SetSeekDir(Long64_t) {}
   virtual void        SetWritable(Bool_t) {}
   virtual Int_t       Sizeof() const {return 0;}
   virtual Int_t       Write(const char * /*name*/=0, Int_t /*opt*/=0, Int_t /*bufsize*/=0){return 0;}
   virtual Int_t       Write(const char * /*name*/=0, Int_t /*opt*/=0, Int_t /*bufsize*/=0) const {return 0;}
   virtual Int_t       WriteTObject(const TObject *obj, const char *name =0, Option_t * /*option*/="", Int_t /*bufsize*/ =0);
/// See TDirectoryFile::WriteTObject for details

   template <class T> inline Int_t WriteObject(const T* obj, const char* name, Option_t *option="", Int_t bufsize=0) // see TDirectory::WriteTObject or TDirectoryWriteObjectAny for explanation
      {
         return WriteObjectAny(obj,TBuffer::GetClass(typeid(T)),name,option,bufsize);
      }
   virtual Int_t       WriteObjectAny(const void *, const char * /*classname*/, const char * /*name*/, Option_t * /*option*/="", Int_t /*bufsize*/ =0) {return 0;}
   virtual Int_t       WriteObjectAny(const void *, const TClass * /*cl*/, const char * /*name*/, Option_t * /*option*/="", Int_t /*bufsize*/ =0) {return 0;}
   virtual void        WriteDirHeader() {}
   virtual void        WriteKeys() {}

   static Bool_t       Cd(const char *path);
   static void         DecodeNameCycle(const char *namecycle, char *name, Short_t &cycle, const size_t namesize = 0);
/// Decode a namecycle "aap;2" into name "aap" and cycle "2". Destination
/// buffer size for name (including string terminator) should be specified in
/// namesize.

   static void         EncodeNameCycle(char *buffer, const char *name, Short_t cycle);
// Encode the name and cycle into buffer like: "aap;2".
```








<!-- TDirectory.md ends here -->
