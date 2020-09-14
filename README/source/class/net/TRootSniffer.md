<!-- TRootSniffer.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 三 6月  6 01:04:23 2018 (+0800)
;; Last-Updated: 三 6月  6 01:26:47 2018 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# TRootSniffer

**TRootSnifferScanRec**

- Structure used to scan hierarchies of ROOT objects
- Represents single level of hierarchy   

TRootSnifferScanRec friend class TRootSniffer


**TRootSniffer**

- Sniffer of ROOT objects, data provider for THttpServer   
- Provides methods to scan different structures like folders, directories, files, trees, collections 
- Can locate objects (or its data member) per name                    
- Can be extended to application-specific classes 

TRootSniffer : public TNamed

## class

TRootSnifferScanRec

```cpp
   TRootSnifferScanRec();
   virtual ~TRootSnifferScanRec();

   void CloseNode();/// close started node

   /** return true when fields could be set to the hierarchy item */
   Bool_t CanSetFields() const { return (fMask & kScan) && (fStore != 0); }

   /** return true when only fields are scanned by the sniffer */
   Bool_t ScanOnlyFields() const { return (fMask & kOnlyFields) && (fMask & kScan); }

   /** Starts new node, must be closed at the end */
   void CreateNode(const char *_node_name);
/// creates new node with specified name
/// if special symbols like "[]&<>" are used, node name
/// will be replaced by default name like "extra_item_N" and
/// original node name will be recorded as "_original_name" field
/// Optionally, object name can be recorded as "_realname" field

   void BeforeNextChild();
/// indicates that new child for current element will be started

   /** Set item field only when creating is specified */
   void SetField(const char *name, const char *value, Bool_t with_quotes = kTRUE);
/// record field for current element

   /** Mark item with ROOT class and correspondent streamer info */
   void SetRootClass(TClass *cl);
/// set root class name as node kind
/// in addition, path to master item (streamer info) specified
/// Such master item required to correctly unstream data on JavaScript

   /** Returns true when item can be expanded */
   Bool_t CanExpandItem();
/// returns true if current item can be expanded - means one could explore
/// objects members

   /** Checks if result will be accepted. Used to verify if sniffer should read object from the file */
   Bool_t IsReadyForResult() const;
/// Checks if result will be accepted.
/// Used to verify if sniffer should read object from the file

   /** Obsolete, use SetFoundResult instead */
   Bool_t SetResult(void *obj, TClass *cl, TDataMember *member = 0);
/// set results of scanning
/// when member should be specified, use SetFoundResult instead

   /** Set found element with class and datamember (optional) */
   Bool_t SetFoundResult(void *obj, TClass *cl, TDataMember *member = 0);
/// set results of scanning
/// when member specified, obj is pointer on object to which member belongs

   /** Returns depth of hierarchy */
   Int_t Depth() const;/// returns current depth of scanned hierarchy

   /** Method indicates that scanning can be interrupted while result is set */
   Bool_t Done() const;
/// returns true if scanning is done
/// Can happen when searched element is found

   /** Construct item name, using object name as basis */
   void MakeItemName(const char *objname, TString &itemname);
/// constructs item name from object name
/// if special symbols like '/', '#', ':', '&', '?'  are used in object name
/// they will be replaced with '_'.
/// To avoid item name duplication, additional id number can be appended

   /** Produces full name for the current item */
   void BuildFullName(TString &buf, TRootSnifferScanRec *prnt = 0);/// Produce full name, including all parents

   /** Returns read-only flag for current item */
   Bool_t IsReadOnly(Bool_t dflt = kTRUE);
/// returns read-only flag for current item
/// Depends from default value and current restrictions

   Bool_t GoInside(TRootSnifferScanRec &super, TObject *obj, const char *obj_name = 0, TRootSniffer *sniffer = 0);
/// Method verifies if new level of hierarchy
/// should be started with provided object.
/// If required, all necessary nodes and fields will be created
/// Used when different collection kinds should be scanned
```

TRootSniffer

```cpp
   enum {
      kItemField = BIT(21) // item property stored as TNamed
   };


   TRootSniffer(const char *name, const char *objpath = "Objects");
   virtual ~TRootSniffer();

   static Bool_t IsDrawableClass(TClass *cl);
/// return true if object can be drawn

   /** When readonly on (default), sniffer is not allowed to change ROOT structures
     * For instance, it is not allowed to read new objects from files */
   void SetReadOnly(Bool_t on = kTRUE) { fReadOnly = on; }

   /** Returns readonly mode */
   Bool_t IsReadOnly() const { return fReadOnly; }

   void Restrict(const char *path, const char *options);
/// Restrict access to the specified location
///
/// Hides or provides read-only access to different parts of the hierarchy
/// Restriction done base on user-name specified with http requests
/// Options can be specified in URL style (separated with &)
/// Following parameters can be specified:
///    visible = [all|user(s)] - make item visible for all users or only specified user
///    hidden = [all|user(s)] - make item hidden from all users or only specified user
///    readonly = [all|user(s)] - make item read-only for all users or only specified user
///    allow = [all|user(s)] - make full access for all users or only specified user
///    allow_method = method(s)  - allow method(s) execution even when readonly flag specified for the object
/// Like make command seen by all but can be executed only by admin
///    sniff->Restrict("/CmdReset","allow=admin");
/// Or fully hide command from guest account
///    sniff->Restrict("/CmdRebin","hidden=guest");

   Bool_t HasRestriction(const char *item_name);
/// Made fast check if item with specified name is in restriction list
/// If returns true, requires precise check with CheckRestriction() method

   Int_t CheckRestriction(const char *item_name);
/// Checked if restriction is applied to the item
/// full_item_name should have full path to the item
///
/// Returns -1 - object invisible, cannot be accessed or listed
///          0 -  no explicit restrictions, use default
///          1 - read-only access
///          2 - full access

   /** When enabled (default), sniffer scans gROOT for files, canvases, histograms */
   void SetScanGlobalDir(Bool_t on = kTRUE) { fScanGlobalDir = on; }

   void SetAutoLoad(const char *scripts = "");
/// When specified, _autoload attribute will be always add
/// to top element of h.json/h.hml requests
/// Used to instruct browser automatically load special code

   const char *GetAutoLoad() const;
/// return name of configured autoload scripts (or 0)

   /** Returns true when sniffer allowed to scan global directories */
   Bool_t IsScanGlobalDir() const { return fScanGlobalDir; }

   Bool_t RegisterObject(const char *subfolder, TObject *obj);
/// Register object in subfolder structure
/// subfolder parameter can have many levels like:
///
/// TRootSniffer* sniff = new TRootSniffer("sniff");
/// sniff->RegisterObject("my/sub/subfolder", h1);
///
/// Such objects can be later found in "Objects" folder of sniffer like
///
/// h1 = sniff->FindTObjectInHierarchy("/Objects/my/sub/subfolder/h1");
///
/// If subfolder name starts with '/', object will be registered starting from top folder.
///
/// One could provide additional fields for registered objects
/// For instance, setting "_more" field to true let browser
/// explore objects members. For instance:
///
/// TEvent* ev = new TEvent("ev");
/// sniff->RegisterObject("Events", ev);
/// sniff->SetItemField("Events/ev", "_more", "true");

   Bool_t UnregisterObject(TObject *obj);
/// unregister (remove) object from folders structures
/// folder itself will remain even when it will be empty

   Bool_t RegisterCommand(const char *cmdname, const char *method, const char *icon);
/// Register command which can be executed from web interface
///
/// As method one typically specifies string, which is executed with
/// gROOT->ProcessLine() method. For instance
///    serv->RegisterCommand("Invoke","InvokeFunction()");
///
/// Or one could specify any method of the object which is already registered
/// to the server. For instance:
///     serv->Register("/", hpx);
///     serv->RegisterCommand("/ResetHPX", "/hpx/->Reset()");
/// Here symbols '/->' separates item name from method to be executed
///
/// One could specify additional arguments in the command with
/// syntax like %arg1%, %arg2% and so on. For example:
///     serv->RegisterCommand("/ResetHPX", "/hpx/->SetTitle(\"%arg1%\")");
///     serv->RegisterCommand("/RebinHPXPY", "/hpxpy/->Rebin2D(%arg1%,%arg2%)");
/// Such parameter(s) will be requested when command clicked in the browser.
///
/// Once command is registered, one could specify icon which will appear in the browser:
///     serv->SetIcon("/ResetHPX", "rootsys/icons/ed_execute.png");
///
/// One also can set extra property '_fastcmd', that command appear as
/// tool button on the top of the browser tree:
///     serv->SetItemField("/ResetHPX", "_fastcmd", "true");
/// Or it is equivalent to specifying extra argument when register command:
///     serv->RegisterCommand("/ResetHPX", "/hpx/->Reset()", "button;rootsys/icons/ed_delete.png");

   Bool_t CreateItem(const char *fullname, const char *title);/// create item element

   Bool_t SetItemField(const char *fullname, const char *name, const char *value);
/// set field for specified item

   const char *GetItemField(const char *fullname, const char *name);
/// return field for specified item

   void SetCurrentCallArg(THttpCallArg *arg);
/// set current http arguments, which then used in different process methods
/// For instance, if user authorized with some user name,
/// depending from restrictions some objects will be invisible
/// or user get full access to the element

   /** Method scans normal objects, registered in ROOT */
   void ScanHierarchy(const char *topname, const char *path, TRootSnifferStore *store, Bool_t only_fields = kFALSE);
/// scan ROOT hierarchy with provided store object

   TObject *FindTObjectInHierarchy(const char *path);
/// Search element in hierarchy, derived from TObject

   virtual void *FindInHierarchy(const char *path, TClass **cl = 0, TDataMember **member = 0, Int_t *chld = 0);
/// Search element with specified path
/// Returns pointer on element
/// Optionally one could obtain element class, member description
/// and number of childs. When chld!=0, not only element is searched,
/// but also number of childs are counted. When member!=0, any object
/// will be scanned for its data members (disregard of extra options)

   Bool_t CanDrawItem(const char *path);
/// Method verifies if object can be drawn

   Bool_t CanExploreItem(const char *path);
/// Method returns true when object has childs or
/// one could try to expand item

   Bool_t IsStreamerInfoItem(const char *itemname);
/// Return true if it is streamer info item name

   ULong_t GetStreamerInfoHash();
/// Returns hash value for streamer infos
/// At the moment - just number of items in streamer infos list.

   ULong_t GetItemHash(const char *itemname);
/// Get hash function for specified item
/// used to detect any changes in the specified object

   Bool_t ProduceJson(const char *path, const char *options, TString &res);
/// produce JSON data for specified item
/// For object conversion TBufferJSON is used

   Bool_t ProduceXml(const char *path, const char *options, TString &res);
/// produce XML data for specified item
/// For object conversion TBufferXML is used

   Bool_t ProduceBinary(const char *path, const char *options, void *&ptr, Long_t &length);
/// produce binary data for specified item
/// if "zipped" option specified in query, buffer will be compressed

   Bool_t ProduceImage(Int_t kind, const char *path, const char *options, void *&ptr, Long_t &length);
/// Method to produce image from specified object
///
/// Parameters:
///    kind - image kind TImage::kPng, TImage::kJpeg, TImage::kGif
///    path - path to object
///    options - extra options
///
/// By default, image 300x200 is produced
/// In options string one could provide following parameters:
///    w - image width
///    h - image height
///    opt - draw options
///  For instance:
///     http://localhost:8080/Files/hsimple.root/hpx/get.png?w=500&h=500&opt=lego1
///
///  Return is memory with produced image
///  Memory must be released by user with free(ptr) call

   Bool_t ProduceExe(const char *path, const char *options, Int_t reskind, TString *ret_str, void **ret_ptr = 0,
                     Long_t *ret_length = 0);
/// execute command for specified object
/// options include method and extra list of parameters
/// sniffer should be not-readonly to allow execution of the commands
/// reskind defines kind of result 0 - debug, 1 - json, 2 - binary

   Bool_t ExecuteCmd(const char *path, const char *options, TString &res);
/// execute command marked as _kind=='Command'

   Bool_t ProduceItem(const char *path, const char *options, TString &res, Bool_t asjson = kTRUE);
/// produce JSON/XML for specified item
/// contrary to h.json request, only fields for specified item are stored

   Bool_t ProduceMulti(const char *path, const char *options, void *&ptr, Long_t &length, TString &str,
                       Bool_t asjson = kTRUE);
/// Process several requests, packing all results into binary or JSON buffer
/// Input parameters should be coded in the POST block and has
/// individual request relative to current path, separated with '\n' symbol like
/// item1/root.bin\n
/// item2/exe.bin?method=GetList\n
/// item3/exe.bin?method=GetTitle\n
/// Request requires 'number' URL option which contains number of requested items
///
/// In case of binary request output buffer looks like:
/// 4bytes length + payload, 4bytes length + payload, ...
/// In case of JSON request output is array with results for each item
/// multi.json request do not support binary requests for the items

   Bool_t Produce(const char *path, const char *file, const char *options, void *&ptr, Long_t &length, TString &str);
/// Method produce different kind of data out of object
/// Parameter 'path' specifies object or object member
/// Supported 'file' (case sensitive):
///   "root.bin"  - binary data
///   "root.png"  - png image
///   "root.jpeg" - jpeg image
///   "root.gif"  - gif image
///   "root.xml"  - xml representation
///   "root.json" - json representation
///   "exe.json"  - method execution with json reply
///   "exe.bin"   - method execution with binary reply
///   "exe.txt"   - method execution with debug output
///   "cmd.json"  - execution of registered commands
/// Result returned either as string or binary buffer,
/// which should be released with free() call
```


<!-- TRootSniffer.md ends here -->
