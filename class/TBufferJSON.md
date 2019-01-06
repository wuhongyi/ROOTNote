<!-- TBufferJSON.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 日 1月  6 12:56:34 2019 (+0800)
;; Last-Updated: 日 1月  6 13:23:40 2019 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TBufferJSON

Class for serializing object into JavaScript Object Notation (JSON) format.

It creates such object representation, which can be directlycused in JavaScript ROOT (JSROOT) for drawing.

TBufferJSON implements TBuffer interface, therefore most of ROOT and user classes can be converted into JSON.

There are certain limitations for classes with custom streamers, which should be equipped specially for this purposes (see TCanvas::Streamer() as example).


```cpp
class TBufferJSON : public TBuffer
```

## class

**TBufferJSON**

```cpp
public:

   TBufferJSON();/// Creates buffer object to serialize data into json.
   virtual ~TBufferJSON();

   void SetCompact(int level);
// Set level of space/newline/array compression
// Lower digit of compact parameter define formatting rules
//  - 0 - no any compression, human-readable form
//  - 1 - exclude spaces in the begin
//  - 2 - remove newlines
//  - 3 - exclude spaces as much as possible
// Second digit of compact parameter defines algorithm for arrays compression
//  - 0 - no compression, standard JSON array
//  - 1 - exclude leading, trailing zeros, required JSROOT v5
//  - 2 - check values repetition and empty gaps, required JSROOT v5

   static TString   ConvertToJSON(const TObject *obj, Int_t compact = 0, const char *member_name = 0);
/// Converts object, inherited from TObject class, to JSON string
/// Lower digit of compact parameter define formatting rules
///  - 0 - no any compression, human-readable form
///  - 1 - exclude spaces in the begin
///  - 2 - remove newlines
///  - 3 - exclude spaces as much as possible
/// Second digit of compact parameter defines algorithm for arrays compression
///  - 0 - no compression, standard JSON array
///  - 1 - exclude leading, trailing zeros, required JSROOT v5
///  - 2 - check values repetition and empty gaps, required JSROOT v5
/// Maximal compression achieved when compact parameter equal to 23
/// When member_name specified, converts only this data member   
   
   static TString   ConvertToJSON(const void *obj, const TClass *cl, Int_t compact = 0, const char *member_name = 0);
/// Converts any type of object to JSON string
/// One should provide pointer on object and its class name
/// Lower digit of compact parameter define formatting rules
///  - 0 - no any compression, human-readable form
///  - 1 - exclude spaces in the begin
///  - 2 - remove newlines
///  - 3 - exclude spaces as much as possible
/// Second digit of compact parameter defines algorithm for arrays compression
///  - 0 - no compression, standard JSON array
///  - 1 - exclude leading, trailing zeros, required JSROOT v5
///  - 2 - check values repetition and empty gaps, required JSROOT v5
/// Maximal compression achieved when compact parameter equal to 23
/// When member_name specified, converts only this data member

   static TString   ConvertToJSON(const void *obj, TDataMember *member, Int_t compact = 0, Int_t arraylen = -1);
/// Converts selected data member into json
/// Parameter ptr specifies address in memory, where data member is located
/// compact parameter defines compactness of produced JSON (from 0 to 3)
/// arraylen (when specified) is array length for this data member,  //[fN] case

   static Int_t     ExportToFile(const char* filename, const TObject *obj, const char* option = 0);
/// Convert object into JSON and store in text file
/// Returns size of the produce file
/// Used in TObject::SaveAs()

   static Int_t     ExportToFile(const char* filename, const void *obj, const TClass *cl, const char* option = 0);
/// Convert object into JSON and store in text file
/// Returns size of the produce file

   // suppress class writing/reading

   virtual TClass  *ReadClass(const TClass *cl = 0, UInt_t *objTag = 0);
   virtual void     WriteClass(const TClass *cl);

   // redefined virtual functions of TBuffer

   virtual Int_t    CheckByteCount(UInt_t startpos, UInt_t bcnt, const TClass *clss); // SL
   virtual Int_t    CheckByteCount(UInt_t startpos, UInt_t bcnt, const char *classname); // SL
   virtual void     SetByteCount(UInt_t cntpos, Bool_t packInVersion = kFALSE);  // SL

   virtual void      SkipVersion(const TClass *cl = 0);
   virtual Version_t ReadVersion(UInt_t *start = 0, UInt_t *bcnt = 0, const TClass *cl = 0);  // SL
   virtual Version_t ReadVersionNoCheckSum(UInt_t *, UInt_t *)
   {
      return 0;
   }
   virtual UInt_t    WriteVersion(const TClass *cl, Bool_t useBcnt = kFALSE);  // SL

   virtual void    *ReadObjectAny(const TClass *clCast);
   virtual void     SkipObjectAny();

   // these methods used in streamer info to indicate currently streamed element,
   virtual void     IncrementLevel(TVirtualStreamerInfo *);
/// Function is called from TStreamerInfo WriteBuffer and ReadBuffer functions
/// and indent new level in json structure.
/// This call indicates, that TStreamerInfo functions starts streaming
/// object data of correspondent class   
   
   virtual void     SetStreamerElementNumber(TStreamerElement *elem, Int_t comp_type);
/// Function is called from TStreamerInfo WriteBuffer and Readbuffer functions
/// and add/verify next element of json structure
/// This calls allows separate data, correspondent to one class member, from another   
   
   virtual void     DecrementLevel(TVirtualStreamerInfo *);
/// Function is called from TStreamerInfo WriteBuffer and ReadBuffer functions
/// and decrease level in json structure.

   virtual void     ClassBegin(const TClass *, Version_t = -1);
/// Should be called in the beginning of custom class streamer.
/// Informs buffer data about class which will be streamed now.
/// ClassBegin(), ClassEnd() and ClassMember() should be used in
/// custom class streamers to specify which kind of data are
/// now streamed. Such information is used to correctly
/// convert class data to JSON. Without that functions calls
/// classes with custom streamers cannot be used with TBufferJSON   
   
   virtual void     ClassEnd(const TClass *);
/// Should be called at the end of custom streamer
/// See TBufferJSON::ClassBegin for more details   
   
   virtual void     ClassMember(const char *name, const char *typeName = 0, Int_t arrsize1 = -1, Int_t arrsize2 = -1);
/// Method indicates name and typename of class member,
/// which should be now streamed in custom streamer
/// Following combinations are supported:
/// 1. name = "ClassName", typeName = 0 or typename==ClassName
///    This is a case, when data of parent class "ClassName" should be streamed.
///     For instance, if class directly inherited from TObject, custom
///     streamer should include following code:
/// ~~~{.cpp}
///       b.ClassMember("TObject");
///       TObject::Streamer(b);
/// ~~~
/// 2. Basic data type
/// ~~~{.cpp}
///      b.ClassMember("fInt","Int_t");
///      b >> fInt;
/// ~~~
/// 3. Array of basic data types
/// ~~~{.cpp}
///      b.ClassMember("fArr","Int_t", 5);
///      b.ReadFastArray(fArr, 5);
/// ~~~
/// 4. Object as data member
/// ~~~{.cpp}
///      b.ClassMember("fName","TString");
///      fName.Streamer(b);
/// ~~~
/// 5. Pointer on object as data member
/// ~~~{.cpp}
///      b.ClassMember("fObj","TObject*");
///      b.StreamObject(fObj);
/// ~~~
/// arrsize1 and arrsize2 arguments (when specified) indicate first and
/// second dimension of array. Can be used for array of basic types.
/// See ClassBegin() method for more details.

   virtual void     WriteObject(const TObject *obj, Bool_t cacheReuse = kTRUE);
/// Convert object into json structures.
/// !!! Should be used only by TBufferJSON itself.
/// Use ConvertToJSON() methods to convert object to json

   using TBuffer::WriteObject;

   virtual void     ReadFloat16(Float_t *f, TStreamerElement *ele = 0);
   virtual void     WriteFloat16(Float_t *f, TStreamerElement *ele = 0);
   virtual void     ReadDouble32(Double_t *d, TStreamerElement *ele = 0);
   virtual void     WriteDouble32(Double_t *d, TStreamerElement *ele = 0);
   virtual void     ReadWithFactor(Float_t *ptr, Double_t factor, Double_t minvalue);
   virtual void     ReadWithNbits(Float_t *ptr, Int_t nbits);
   virtual void     ReadWithFactor(Double_t *ptr, Double_t factor, Double_t minvalue);
   virtual void     ReadWithNbits(Double_t *ptr, Int_t nbits);

   virtual Int_t    ReadArray(Bool_t    *&b);
   virtual Int_t    ReadArray(Char_t    *&c);
   virtual Int_t    ReadArray(UChar_t   *&c);
   virtual Int_t    ReadArray(Short_t   *&h);
   virtual Int_t    ReadArray(UShort_t  *&h);
   virtual Int_t    ReadArray(Int_t     *&i);
   virtual Int_t    ReadArray(UInt_t    *&i);
   virtual Int_t    ReadArray(Long_t    *&l);
   virtual Int_t    ReadArray(ULong_t   *&l);
   virtual Int_t    ReadArray(Long64_t  *&l);
   virtual Int_t    ReadArray(ULong64_t *&l);
   virtual Int_t    ReadArray(Float_t   *&f);
   virtual Int_t    ReadArray(Double_t  *&d);
   virtual Int_t    ReadArrayFloat16(Float_t  *&f, TStreamerElement *ele = 0);
   virtual Int_t    ReadArrayDouble32(Double_t  *&d, TStreamerElement *ele = 0);

   virtual Int_t    ReadStaticArray(Bool_t    *b);
   virtual Int_t    ReadStaticArray(Char_t    *c);
   virtual Int_t    ReadStaticArray(UChar_t   *c);
   virtual Int_t    ReadStaticArray(Short_t   *h);
   virtual Int_t    ReadStaticArray(UShort_t  *h);
   virtual Int_t    ReadStaticArray(Int_t     *i);
   virtual Int_t    ReadStaticArray(UInt_t    *i);
   virtual Int_t    ReadStaticArray(Long_t    *l);
   virtual Int_t    ReadStaticArray(ULong_t   *l);
   virtual Int_t    ReadStaticArray(Long64_t  *l);
   virtual Int_t    ReadStaticArray(ULong64_t *l);
   virtual Int_t    ReadStaticArray(Float_t   *f);
   virtual Int_t    ReadStaticArray(Double_t  *d);
   virtual Int_t    ReadStaticArrayFloat16(Float_t  *f, TStreamerElement *ele = 0);
   virtual Int_t    ReadStaticArrayDouble32(Double_t  *d, TStreamerElement *ele = 0);

   virtual void     ReadFastArray(Bool_t    *b, Int_t n);
   virtual void     ReadFastArray(Char_t    *c, Int_t n);
   virtual void     ReadFastArrayString(Char_t *c, Int_t n);
   virtual void     ReadFastArray(UChar_t   *c, Int_t n);
   virtual void     ReadFastArray(Short_t   *h, Int_t n);
   virtual void     ReadFastArray(UShort_t  *h, Int_t n);
   virtual void     ReadFastArray(Int_t     *i, Int_t n);
   virtual void     ReadFastArray(UInt_t    *i, Int_t n);
   virtual void     ReadFastArray(Long_t    *l, Int_t n);
   virtual void     ReadFastArray(ULong_t   *l, Int_t n);
   virtual void     ReadFastArray(Long64_t  *l, Int_t n);
   virtual void     ReadFastArray(ULong64_t *l, Int_t n);
   virtual void     ReadFastArray(Float_t   *f, Int_t n);
   virtual void     ReadFastArray(Double_t  *d, Int_t n);
   virtual void     ReadFastArrayFloat16(Float_t  *f, Int_t n, TStreamerElement *ele = 0);
   virtual void     ReadFastArrayDouble32(Double_t  *d, Int_t n, TStreamerElement *ele = 0);
   virtual void     ReadFastArrayWithFactor(Float_t *ptr, Int_t n, Double_t factor, Double_t minvalue) ;
   virtual void     ReadFastArrayWithNbits(Float_t *ptr, Int_t n, Int_t nbits);
   virtual void     ReadFastArrayWithFactor(Double_t *ptr, Int_t n, Double_t factor, Double_t minvalue);
   virtual void     ReadFastArrayWithNbits(Double_t *ptr, Int_t n, Int_t nbits) ;

   virtual void     WriteArray(const Bool_t    *b, Int_t n);
   virtual void     WriteArray(const Char_t    *c, Int_t n);
   virtual void     WriteArray(const UChar_t   *c, Int_t n);
   virtual void     WriteArray(const Short_t   *h, Int_t n);
   virtual void     WriteArray(const UShort_t  *h, Int_t n);
   virtual void     WriteArray(const Int_t     *i, Int_t n);
   virtual void     WriteArray(const UInt_t    *i, Int_t n);
   virtual void     WriteArray(const Long_t    *l, Int_t n);
   virtual void     WriteArray(const ULong_t   *l, Int_t n);
   virtual void     WriteArray(const Long64_t  *l, Int_t n);
   virtual void     WriteArray(const ULong64_t *l, Int_t n);
   virtual void     WriteArray(const Float_t   *f, Int_t n);
   virtual void     WriteArray(const Double_t  *d, Int_t n);
   virtual void     WriteArrayFloat16(const Float_t  *f, Int_t n, TStreamerElement *ele = 0);
   virtual void     WriteArrayDouble32(const Double_t  *d, Int_t n, TStreamerElement *ele = 0);
   virtual void     ReadFastArray(void  *start , const TClass *cl, Int_t n = 1, TMemberStreamer *s = 0, const TClass *onFileClass = 0);
   virtual void     ReadFastArray(void **startp, const TClass *cl, Int_t n = 1, Bool_t isPreAlloc = kFALSE, TMemberStreamer *s = 0, const TClass *onFileClass = 0);

   virtual void     WriteFastArray(const Bool_t    *b, Int_t n);
   virtual void     WriteFastArray(const Char_t    *c, Int_t n);
   virtual void     WriteFastArrayString(const Char_t    *c, Int_t n);
   virtual void     WriteFastArray(const UChar_t   *c, Int_t n);
   virtual void     WriteFastArray(const Short_t   *h, Int_t n);
   virtual void     WriteFastArray(const UShort_t  *h, Int_t n);
   virtual void     WriteFastArray(const Int_t     *i, Int_t n);
   virtual void     WriteFastArray(const UInt_t    *i, Int_t n);
   virtual void     WriteFastArray(const Long_t    *l, Int_t n);
   virtual void     WriteFastArray(const ULong_t   *l, Int_t n);
   virtual void     WriteFastArray(const Long64_t  *l, Int_t n);
   virtual void     WriteFastArray(const ULong64_t *l, Int_t n);
   virtual void     WriteFastArray(const Float_t   *f, Int_t n);
   virtual void     WriteFastArray(const Double_t  *d, Int_t n);
   virtual void     WriteFastArrayFloat16(const Float_t  *d, Int_t n, TStreamerElement *ele = 0);
   virtual void     WriteFastArrayDouble32(const Double_t  *d, Int_t n, TStreamerElement *ele = 0);
   virtual void     WriteFastArray(void  *start,  const TClass *cl, Int_t n = 1, TMemberStreamer *s = 0);
   virtual Int_t    WriteFastArray(void **startp, const TClass *cl, Int_t n = 1, Bool_t isPreAlloc = kFALSE, TMemberStreamer *s = 0);

   virtual void     StreamObject(void *obj, const std::type_info &typeinfo, const TClass *onFileClass = 0);/// stream object to/from buffer
   virtual void     StreamObject(void *obj, const char *className, const TClass *onFileClass = 0);/// stream object to/from buffer
   virtual void     StreamObject(void *obj, const TClass *cl, const TClass *onFileClass = 0);/// stream object to/from buffer
   virtual void     StreamObject(TObject *obj);

   virtual   void     ReadBool(Bool_t       &b);
   virtual   void     ReadChar(Char_t       &c);
   virtual   void     ReadUChar(UChar_t     &c);
   virtual   void     ReadShort(Short_t     &s);
   virtual   void     ReadUShort(UShort_t   &s);
   virtual   void     ReadInt(Int_t         &i);
   virtual   void     ReadUInt(UInt_t       &i);
   virtual   void     ReadLong(Long_t       &l);
   virtual   void     ReadULong(ULong_t     &l);
   virtual   void     ReadLong64(Long64_t   &l);
   virtual   void     ReadULong64(ULong64_t &l);
   virtual   void     ReadFloat(Float_t     &f);
   virtual   void     ReadDouble(Double_t   &d);
   virtual   void     ReadCharP(Char_t      *c);
   virtual   void     ReadTString(TString   &s);
   virtual   void     ReadStdString(std::string *s);
   using              TBuffer::ReadStdString;
   virtual   void     ReadCharStar(char* &s);

   virtual   void     WriteBool(Bool_t       b);
   virtual   void     WriteChar(Char_t       c);
   virtual   void     WriteUChar(UChar_t     c);
   virtual   void     WriteShort(Short_t     s);
   virtual   void     WriteUShort(UShort_t   s);
   virtual   void     WriteInt(Int_t         i);
   virtual   void     WriteUInt(UInt_t       i);
   virtual   void     WriteLong(Long_t       l);
   virtual   void     WriteULong(ULong_t     l);
   virtual   void     WriteLong64(Long64_t   l);
   virtual   void     WriteULong64(ULong64_t l);
   virtual   void     WriteFloat(Float_t     f);
   virtual   void     WriteDouble(Double_t   d);
   virtual   void     WriteCharP(const Char_t *c);
   virtual   void     WriteTString(const TString &s);
   virtual   void     WriteStdString(const std::string *s);
   using              TBuffer::WriteStdString;
   virtual   void     WriteCharStar(char *s);

   virtual   Int_t    WriteClones(TClonesArray *a, Int_t nobjects);
/// Interface to TStreamerInfo::WriteBufferClones.

   virtual   Int_t    WriteObjectAny(const void *obj, const TClass *ptrClass, Bool_t cacheReuse = kTRUE);
/// Write object to I/O buffer.
/// This function assumes that the value in 'obj' is the value stored in
/// a pointer to a "ptrClass". The actual type of the object pointed to
/// can be any class derived from "ptrClass".
/// Return:
///  - 0: failure
///  - 1: success
///  - 2: truncated success (i.e actual class is missing. Only ptrClass saved.)
/// If 'cacheReuse' is true (default) upon seeing an object address a second time,
/// we record the offset where its was written the first time rather than streaming
/// the object a second time.
/// If 'cacheReuse' is false, we always stream the object.  This allows the (re)use
/// of temporary object to store different data in the same buffer.   
   
   virtual   Int_t    WriteClassBuffer(const TClass *cl, void *pointer);
/// Function called by the Streamer functions to serialize object at p
/// to buffer b. The optional argument info may be specified to give an
/// alternative StreamerInfo instead of using the default StreamerInfo
/// automatically built from the class definition.
/// For more information, see class TStreamerInfo.

   virtual Int_t      ApplySequence(const TStreamerInfoActions::TActionSequence &sequence, void *object);
/// Read one collection of objects from the buffer using the StreamerInfoLoopAction.
/// The collection needs to be a split TClonesArray or a split vector of pointers.   
   
   virtual Int_t      ApplySequenceVecPtr(const TStreamerInfoActions::TActionSequence &sequence, void *start_collection, void *end_collection);
/// Read one collection of objects from the buffer using the StreamerInfoLoopAction.
/// The collection needs to be a split TClonesArray or a split vector of pointers.   
   
   virtual Int_t      ApplySequence(const TStreamerInfoActions::TActionSequence &sequence, void *start_collection, void *end_collection);
/// Read one collection of objects from the buffer using the StreamerInfoLoopAction.

   virtual void       TagStreamerInfo(TVirtualStreamerInfo * /*info*/) {}

   virtual Bool_t     CheckObject(const TObject * /*obj*/);
/// Check that object already stored in the buffer

   virtual Bool_t     CheckObject(const void * /*ptr*/, const TClass * /*cl*/);
/// Check that object already stored in the buffer

   // abstract virtual methods from TBuffer, which should be redefined

   virtual Int_t      ReadBuf(void * /*buf*/, Int_t /*max*/)
   {
      Error("ReadBuf", "useless");
      return 0;
   }
   virtual void       WriteBuf(const void * /*buf*/, Int_t /*max*/)
   {
      Error("WriteBuf", "useless");
   }

   virtual char      *ReadString(char * /*s*/, Int_t /*max*/)
   {
      Error("ReadString", "useless");
      return 0;
   }
   virtual void       WriteString(const char * /*s*/)
   {
      Error("WriteString", "useless");
   }

   virtual Int_t      GetVersionOwner() const
   {
      Error("GetVersionOwner", "useless");
      return 0;
   }
   virtual Int_t      GetMapCount() const
   {
      Error("GetMapCount", "useless");
      return 0;
   }
   virtual void       GetMappedObject(UInt_t /*tag*/, void *&/*ptr*/, TClass *&/*ClassPtr*/) const
   {
      Error("GetMappedObject", "useless");
   }
   virtual void       MapObject(const TObject * /*obj*/, UInt_t /*offset*/ = 1)
   {
      Error("MapObject", "useless");
   }
   virtual void       MapObject(const void * /*obj*/, const TClass * /*cl*/, UInt_t /*offset*/ = 1)
   {
      Error("MapObject", "useless");
   }
   virtual void       Reset()
   {
      Error("Reset", "useless");
   }
   virtual void       InitMap()
   {
      Error("InitMap", "useless");
   }
   virtual void       ResetMap()
   {
      Error("ResetMap", "useless");
   }
   virtual void       SetReadParam(Int_t /*mapsize*/)
   {
      Error("SetReadParam", "useless");
   }
   virtual void       SetWriteParam(Int_t /*mapsize*/)
   {
      Error("SetWriteParam", "useless");
   }

   virtual Version_t  ReadVersionForMemberWise(const TClass * /*cl*/ = 0)
   {
      Error("ReadVersionForMemberWise", "useless");
      return 0;
   }
   virtual UInt_t     WriteVersionMemberWise(const TClass * /*cl*/, Bool_t /*useBcnt*/ = kFALSE)
   {
      Error("WriteVersionMemberWise", "useless");
      return 0;
   }

   virtual TVirtualStreamerInfo *GetInfo()
   {
      Error("GetInfo", "useless");
      return 0;
   }

   virtual TObject   *ReadObject(const TClass * /*cl*/)
   {
      Error("ReadObject", "useless");
      return 0;
   }

   virtual UShort_t   GetPidOffset() const
   {
      Error("GetPidOffset", "useless");
      return 0;
   }
   virtual void       SetPidOffset(UShort_t /*offset*/)
   {
      Error("SetPidOffset", "useless");
   }
   virtual Int_t      GetBufferDisplacement() const
   {
      Error("GetBufferDisplacement", "useless");
      return 0;
   }
   virtual void       SetBufferDisplacement()
   {
      Error("SetBufferDisplacement", "useless");
   }
   virtual void       SetBufferDisplacement(Int_t /*skipped*/)
   {
      Error("SetBufferDisplacement", "useless");
   }

   virtual   TProcessID *GetLastProcessID(TRefTable * /*reftable*/) const
   {
      Error("GetLastProcessID", "useless");
      return 0;
   }
   virtual   UInt_t      GetTRefExecId()
   {
      Error("GetTRefExecId", "useless");
      return 0;
   }
   virtual   TProcessID *ReadProcessID(UShort_t /*pidf*/)
   {
      Error("ReadProcessID", "useless");
      return 0;
   }
   virtual   UShort_t    WriteProcessID(TProcessID * /*pid*/)
   {
      // Error("WriteProcessID", "useless");
      return 0;
   }

   // Utilities for TStreamerInfo
   virtual   void     ForceWriteInfo(TVirtualStreamerInfo * /*info*/, Bool_t /*force*/)
   {
      Error("ForceWriteInfo", "useless");
   }
   virtual   void     ForceWriteInfoClones(TClonesArray * /*a*/)
   {
      Error("ForceWriteInfoClones", "useless");
   }
   virtual   Int_t    ReadClones(TClonesArray * /*a*/, Int_t /*nobjects*/, Version_t /*objvers*/)
   {
      Error("ReadClones", "useless");
      return 0;
   }

   // Utilities for TClass
   virtual   Int_t    ReadClassEmulated(const TClass * /*cl*/, void * /*object*/, const TClass * /*onfile_class*/ = 0)
   {
      Error("ReadClassEmulated", "useless");
      return 0;
   }
   virtual   Int_t    ReadClassBuffer(const TClass * /*cl*/, void * /*pointer*/, const TClass * /*onfile_class*/ = 0)
   {
      Error("ReadClassBuffer", "useless");
      return 0;
   }
   virtual   Int_t    ReadClassBuffer(const TClass * /*cl*/, void * /*pointer*/, Int_t /*version*/, UInt_t /*start*/, UInt_t /*count*/, const TClass * /*onfile_class*/ = 0)
   {
      Error("ReadClassBuffer", "useless");
      return 0;
   }

   // end of redefined virtual functions

   static    void     SetFloatFormat(const char *fmt = "%e");
/// set printf format for float/double members, default "%e"
/// to change format only for doubles, use SetDoubleFormat   
   
   static const char *GetFloatFormat();
/// return current printf format for float members, default "%e"   
   
   static    void     SetDoubleFormat(const char *fmt = "%.14e");
/// set printf format for double members, default "%.14e"
/// use it after SetFloatFormat, which also overwrites format for doubles   
   
   static const char *GetDoubleFormat();
/// return current printf format for double members, default "%.14e"

   static    void     CompactFloatString(char* buf, unsigned len);
/// method compress float string, excluding exp and/or move float point
///  - 1.000000e-01 -> 0.1
///  - 3.750000e+00 -> 3.75
///  - 3.750000e-03 -> 0.00375
///  - 3.750000e-04 -> 3.75e-4
///  - 1.100000e-10 -> 1.1e-10

protected:
   // redefined protected virtual functions

   virtual void     WriteObjectClass(const void *actualObjStart, const TClass *actualClass, Bool_t cacheReuse);

   // end redefined protected virtual functions

   TString          JsonWriteMember(const void *ptr, TDataMember *member, TClass *memberClass, Int_t arraylen);
/// Convert single data member to JSON structures
/// Returns string with converted member

   TJSONStackObj   *PushStack(Int_t inclevel = 0);/// add new level to the structures stack
   TJSONStackObj   *PopStack();/// remove one level from stack
   TJSONStackObj   *Stack(Int_t depth = 0);/// return stack object of specified depth

   void             WorkWithClass(TStreamerInfo *info, const TClass *cl = 0);
/// Prepares buffer to stream data of specified class   
   
   void             WorkWithElement(TStreamerElement *elem, Int_t);
/// This is call-back from streamer which indicates
/// that class member will be streamed
/// Name of element used in JSON

   void             JsonDisablePostprocessing();
   Int_t            JsonSpecialClass(const TClass *cl) const;
/// return non-zero value when class has special handling in JSON
/// it is TCollection (-130), TArray (100), TString (110), std::string (120) and STL containers (1..6)

   void             JsonStartElement(const TStreamerElement *elem, const TClass *base_class = 0);

   void             PerformPostProcessing(TJSONStackObj *stack, const TClass *obj_cl = 0);
/// Function is converts TObject and TString structures to more compact representation

   void              JsonWriteBasic(Char_t value);
   void              JsonWriteBasic(Short_t value);
   void              JsonWriteBasic(Int_t value);
   void              JsonWriteBasic(Long_t value);
   void              JsonWriteBasic(Long64_t value);
   void              JsonWriteBasic(Float_t value);
   void              JsonWriteBasic(Double_t value);
   void              JsonWriteBasic(Bool_t value);
   void              JsonWriteBasic(UChar_t value);
   void              JsonWriteBasic(UShort_t value);
   void              JsonWriteBasic(UInt_t value);
   void              JsonWriteBasic(ULong_t value);
   void              JsonWriteBasic(ULong64_t value);
/// converts ULong64_t to string and add to json value buffer

   void              JsonWriteConstChar(const char* value, Int_t len = -1);
/// writes string value, processing all kind of special characters

   void              JsonWriteObject(const void *obj, const TClass *objClass, Bool_t check_map = kTRUE);
/// Write object to buffer
/// If object was written before, only pointer will be stored
/// If check_map==kFALSE, object will be stored in any case and pointer will not be registered in the map

   void              JsonStreamCollection(TCollection *obj, const TClass *objClass);/// store content of collection

   void              AppendOutput(const char *line0, const char *line1 = 0);

   TString                   fOutBuffer;    //!  main output buffer for json code
   TString                  *fOutput;       //!  current output buffer for json code
   TString                   fValue;        //!  buffer for current value
   std::map<const void *, unsigned>  fJsonrMap;   //!  map of recorded objects, used in JsonR to restore references
   unsigned                  fJsonrCnt;     //!  counter for all objects and arrays
   TObjArray                 fStack;        //!  stack of streamer infos
   Int_t                     fCompact;       //!  0 - no any compression, 1 - no spaces in the begin, 2 - no new lines, 3 - no spaces at all
   TString                   fSemicolon;     //!  depending from compression level, " : " or ":"
   TString                   fArraySepar;    //!  depending from compression level, ", " or ","
   TString                   fNumericLocale; //!  stored value of setlocale(LC_NUMERIC), which should be recovered at the end

   static const char *fgFloatFmt;          //!  printf argument for floats, either "%f" or "%e" or "%10f" and so on
   static const char *fgDoubleFmt;         //!  printf argument for doubles, either "%f" or "%e" or "%10f" and so on
```

----

```cpp
// TArrayIndexProducer is used to correctly create
// JSON array separators for multi-dimensional JSON arrays
// It fully reproduces array dimensions as in original ROOT classes
// Contrary to binary I/O, which always writes flat arrays

class TArrayIndexProducer {
   protected:

      Int_t fTotalLen;
      Int_t fCnt;
      const char* fSepar;
      TArrayI fIndicies;
      TArrayI fMaxIndex;
      TString fRes;
      Bool_t fIsArray;

   public:
      TArrayIndexProducer(TStreamerElement* elem, Int_t arraylen, const char* separ) :
         fTotalLen(0),
         fCnt(-1),
         fSepar(separ),
         fIndicies(),
         fMaxIndex(),
         fRes(),
         fIsArray(kFALSE)
      {
         Bool_t usearrayindx = elem && (elem->GetArrayDim() > 0);
         Bool_t isloop = elem && ((elem->GetType() == TStreamerInfo::kStreamLoop) ||
                                  (elem->GetType() == TStreamerInfo::kOffsetL + TStreamerInfo::kStreamLoop));
         Bool_t usearraylen = (arraylen > (isloop ? 0 : 1));

         if (usearrayindx && (arraylen > 0)) {
            if (isloop) {
               usearrayindx = kFALSE;
               usearraylen = kTRUE;
            } else if (arraylen != elem->GetArrayLength()) {
               printf("Problem with JSON coding of element %s type %d \n", elem->GetName(), elem->GetType());
            }
         }

         if (usearrayindx) {
            fTotalLen = elem->GetArrayLength();
            fMaxIndex.Set(elem->GetArrayDim());
            for(int dim=0;dim<elem->GetArrayDim();dim++)
               fMaxIndex[dim] = elem->GetMaxIndex(dim);
            fIsArray = fTotalLen>1;
         } else
         if (usearraylen) {
            fTotalLen = arraylen;
            fMaxIndex.Set(1);
            fMaxIndex[0] = arraylen;
            fIsArray = kTRUE;
         }

         if (fMaxIndex.GetSize() > 0) {
            fIndicies.Set(fMaxIndex.GetSize());
            fIndicies.Reset(0);
         }
      }

      TArrayIndexProducer(TDataMember* member, Int_t extradim, const char* separ) :
         fTotalLen(0),
         fCnt(-1),
         fSepar(separ),
         fIndicies(),
         fMaxIndex(),
         fRes(),
         fIsArray(kFALSE)
      {
         Int_t ndim = member->GetArrayDim();
         if (extradim > 0) ndim++;

         if (ndim > 0) {
            fIndicies.Set(ndim);
            fIndicies.Reset(0);
            fMaxIndex.Set(ndim);
            fTotalLen = 1;
            for (int dim=0;dim<member->GetArrayDim();dim++) {
               fMaxIndex[dim] = member->GetMaxIndex(dim);
               fTotalLen *= member->GetMaxIndex(dim);
            }

            if (extradim > 0) {
               fMaxIndex[ndim-1] = extradim;
               fTotalLen *= extradim;
            }
         }
         fIsArray = fTotalLen>1;
      }

      Int_t ReduceDimension()
      {
         // reduce one dimension of the array
         // return size of reduced dimension
         if (fMaxIndex.GetSize() == 0) return 0;
         Int_t ndim = fMaxIndex.GetSize()-1;
         Int_t len = fMaxIndex[ndim];
         fMaxIndex.Set(ndim);
         fIndicies.Set(ndim);
         fTotalLen = fTotalLen/len;
         fIsArray = fTotalLen>1;
         return len;
      }


      Bool_t IsArray() const
      {
         return fIsArray;
      }

      Bool_t IsDone() const
      {
         // return true when iteration over all arrays indexes are done
         return !IsArray() || (fCnt >= fTotalLen);
      }

      const char* GetBegin()
      {
         ++fCnt;
         // return starting separator
         fRes.Clear();
         for (Int_t n=0;n<fIndicies.GetSize();++n) fRes.Append("[");
         return fRes.Data();
      }

      const char* GetEnd()
      {
         // return ending separator
         fRes.Clear();
         for (Int_t n=0;n<fIndicies.GetSize();++n) fRes.Append("]");
         return fRes.Data();
      }

      const char* NextSeparator()
      {
         // return intermediate or last separator

         if (++fCnt >= fTotalLen) return GetEnd();

         Int_t cnt = fIndicies.GetSize() - 1;
         fIndicies[cnt]++;

         fRes.Clear();

         while ((cnt >= 0) && (cnt < fIndicies.GetSize()))  {
            if (fIndicies[cnt] >= fMaxIndex[cnt]) {
               fRes.Append("]");
               fIndicies[cnt--] = 0;
               if (cnt >= 0) fIndicies[cnt]++;
               continue;
            }
            fRes.Append(fIndicies[cnt] == 0 ? "[" : fSepar);
            cnt++;
         }
         return fRes.Data();
      }

};


// TJSONStackObj is used to keep stack of object hierarchy,
// stored in TBuffer. For instance, data for parent class(es)
// stored in subnodes, but initial object node will be kept.

class TJSONStackObj : public TObject {
public:
   TStreamerInfo    *fInfo;           //!
   TStreamerElement *fElem;           //! element in streamer info
   Bool_t            fIsStreamerInfo; //!
   Bool_t            fIsElemOwner;    //!
   Bool_t            fIsPostProcessed;//! indicate that value is written
   Bool_t            fIsObjStarted;   //! indicate that object writing started, should be closed in postprocess
   Bool_t            fAccObjects;     //! if true, accumulate whole objects in values
   TObjArray         fValues;         //! raw values
   Int_t             fLevel;          //! indent level
   TArrayIndexProducer *fIndx;        //! producer of ndim indexes

   TJSONStackObj() :
      TObject(),
      fInfo(0),
      fElem(0),
      fIsStreamerInfo(kFALSE),
      fIsElemOwner(kFALSE),
      fIsPostProcessed(kFALSE),
      fIsObjStarted(kFALSE),
      fAccObjects(kFALSE),
      fValues(),
      fLevel(0),
      fIndx(0)
   {
      fValues.SetOwner(kTRUE);
   }

   virtual ~TJSONStackObj()
   {
      if (fIsElemOwner) delete fElem;
      if (fIndx) delete fIndx;
   }

   Bool_t IsStreamerInfo() const
   {
      return fIsStreamerInfo;
   }
   Bool_t IsStreamerElement() const
   {
      return !fIsStreamerInfo && (fElem != 0);
   }

   void PushValue(TString &v)
   {
      fValues.Add(new TObjString(v));
      v.Clear();
   }
};
```

## code


## example


```cpp
// To perform conversion, one should use TBufferJSON::ConvertToJSON method like:
   TH1* h1 = new TH1I("h1","title",100, 0, 10);
   h1->FillRandom("gaus",10000);
   TString json = TBufferJSON::ConvertToJSON(h1);
```

<!-- TBufferJSON.md ends here -->
