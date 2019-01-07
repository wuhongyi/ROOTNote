<!-- TBufferSQL2.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 一 1月  7 14:08:08 2019 (+0800)
;; Last-Updated: 一 1月  7 14:29:20 2019 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TBufferSQL2

Converts data to SQL statements or read data from SQL tables.

Class for serializing/deserializing object to/from SQL data base.
It redefines most of TBuffer class function to convert simple types,
array of simple types and objects to/from TSQLStructure objects.
TBufferSQL2 class uses streaming mechanism, provided by ROOT system,
therefore most of ROOT and user classes can be stored. There are
limitations for complex objects like TTree, TClonesArray, TDirectory and
few other, which can not be converted to SQL (yet).

```cpp
class TBufferSQL2 : public TBufferFile
```

## class

```cpp
   friend class TSQLStructure;

protected:
   TSQLFile *fSQL;            ///<!   instance of TSQLFile
   TSQLStructure *fStructure; ///<!   structures, created by object storing
   TSQLStructure *fStk;       ///<!   pointer on current active structure (stack head)
   TExMap *fObjMap;           ///<!   Map between stored objects and object id
   TString fReadBuffer;       ///<!   Buffer for read value
   Int_t fErrorFlag;          ///<!   Error id value
   Bool_t fExpectedChain; ///<!   flag to resolve situation when several elements of same basic type stored as FastArray
   Int_t fCompressLevel;  ///<!   compress level used to minimize size of data in database
   Int_t fReadVersionBuffer;     ///<!   buffer, used to by ReadVersion method
   Long64_t fObjIdCounter;       ///<!   counter of objects id
   Bool_t fIgnoreVerification;   ///<!   ignore verification of names
   TSQLObjectData *fCurrentData; ///<!
   TObjArray *fObjectsInfos;     ///<!   array of objects info for selected key
   Long64_t fFirstObjId;         ///<!   id of first object to be read from the database
   Long64_t fLastObjId;          ///<!   id of last object correspond to this key
   TMap *fPoolsMap;              ///<!   map of pools with data from different tables

   // TBufferSQL2 objects cannot be copied or assigned
   TBufferSQL2(const TBufferSQL2 &);    // not implemented
   void operator=(const TBufferSQL2 &); // not implemented

   TBufferSQL2();

   // redefined protected virtual functions

   virtual void WriteObjectClass(const void *actualObjStart, const TClass *actualClass, Bool_t cacheReuse);/// Write object to buffer. Only used from TBuffer

   // end redefined protected virtual functions

   TSQLStructure *PushStack();/// Push stack with structurual information about streamed object
   TSQLStructure *PopStack();/// Pop stack
   TSQLStructure *Stack(Int_t depth = 0);/// returns head of stack

   void WorkWithClass(const char *classname, Version_t classversion);
/// This function is a part of IncrementLevel method.
/// Also used in StartClass method   
   
   void WorkWithElement(TStreamerElement *elem, Int_t comp_type);
/// This function is a part of SetStreamerElementNumber method.
/// It is introduced for reading of data for specified data memeber of class.
/// Used also in ReadFastArray methods to resolve problem of compressed data,
/// when several data memebers of the same basic type streamed with single ...FastArray call

   Int_t SqlReadArraySize();
   Bool_t SqlObjectInfo(Long64_t objid, TString &clname, Version_t &version);
/// Returns object info like classname and version
/// Should be taken from buffer, which is produced in the beginning   
   
   TSQLObjectData *SqlObjectData(Long64_t objid, TSQLClassInfo *sqlinfo);
/// Creates TSQLObjectData for specified object id and specified class
/// Object data for each class can be stored in two different tables.
/// First table contains data in column-wise form for simple types like integer,
/// strings and so on when second table contains any other data which cannot
/// be converted into column-wise representation.
/// TSQLObjectData will contain results of the requests to both such tables for
/// concrete object id.

   Bool_t SqlWriteBasic(Char_t value);
   Bool_t SqlWriteBasic(Short_t value);
   Bool_t SqlWriteBasic(Int_t value);
   Bool_t SqlWriteBasic(Long_t value);
   Bool_t SqlWriteBasic(Long64_t value);
   Bool_t SqlWriteBasic(Float_t value);
   Bool_t SqlWriteBasic(Double_t value);
   Bool_t SqlWriteBasic(Bool_t value);
   Bool_t SqlWriteBasic(UChar_t value);
   Bool_t SqlWriteBasic(UShort_t value);
   Bool_t SqlWriteBasic(UInt_t value);
   Bool_t SqlWriteBasic(ULong_t value);
   Bool_t SqlWriteBasic(ULong64_t value);// converts ULong64_t to string and creates correspondent sql structure
   Bool_t SqlWriteValue(const char *value, const char *tname);

   void SqlReadBasic(Char_t &value);
   void SqlReadBasic(Short_t &value);
   void SqlReadBasic(Int_t &value);
   void SqlReadBasic(Long_t &value);
   void SqlReadBasic(Long64_t &value);
   void SqlReadBasic(Float_t &value);
   void SqlReadBasic(Double_t &value);
   void SqlReadBasic(Bool_t &value);
   void SqlReadBasic(UChar_t &value);
   void SqlReadBasic(UShort_t &value);
   void SqlReadBasic(UInt_t &value);
   void SqlReadBasic(ULong_t &value);
   void SqlReadBasic(ULong64_t &value);
   const char *SqlReadValue(const char *tname);/// Read string value from current stack node
   const char *SqlReadCharStarValue();
/// Read CharStar value, if it has special code, request it from large table

   Int_t
   SqlWriteObject(const void *obj, const TClass *objClass, Bool_t cacheReuse, TMemberStreamer *streamer = 0, Int_t streamer_index = 0);
/// Write object to buffer.
/// If object was written before, only pointer will be stored
/// Return id of saved object   
   
   void *SqlReadObject(void *obj, TClass **cl = 0, TMemberStreamer *streamer = 0, Int_t streamer_index = 0,
                       const TClass *onFileClass = 0);/// Read object from the buffer
   void *SqlReadObjectDirect(void *obj, TClass **cl, Long64_t objid, TMemberStreamer *streamer = 0,
                             Int_t streamer_index = 0, const TClass *onFileClass = 0);
/// Read object data.
/// Class name and version are taken from special objects table.

public:
   TBufferSQL2(TBuffer::EMode mode);
/// Creates buffer object to serialize/deserialize data to/from sql.
/// Mode should be either TBuffer::kRead or TBuffer::kWrite.   
   
   TBufferSQL2(TBuffer::EMode mode, TSQLFile *file);
/// Creates buffer object to serialize/deserialize data to/from sql.
/// This constructor should be used, if data from buffer supposed to be stored in file.
/// Mode should be either TBuffer::kRead or TBuffer::kWrite.   
   
   virtual ~TBufferSQL2();

   void SetCompressionLevel(int level) { fCompressLevel = level; }

   TSQLStructure *GetStructure() const { return fStructure; }

   Int_t GetErrorFlag() const { return fErrorFlag; }

   void SetIgnoreVerification() { fIgnoreVerification = kTRUE; }

   TSQLStructure *SqlWriteAny(const void *obj, const TClass *cl, Long64_t objid);
/// Convert object of any class to sql structures
/// Return pointer on created TSQLStructure
/// TSQLStructure object will be owned by TBufferSQL2

   void *SqlReadAny(Long64_t keyid, Long64_t objid, TClass **cl, void *obj = 0);
/// Recreate object from sql structure.
/// Return pointer to read object.
/// if (cl!=0) returns pointer to class of object

   // suppress class writing/reading

   virtual TClass *ReadClass(const TClass *cl = 0, UInt_t *objTag = 0);
   virtual void WriteClass(const TClass *cl);

   // redefined virtual functions of TBuffer

   virtual Int_t CheckByteCount(UInt_t startpos, UInt_t bcnt, const TClass *clss);    // SL
   virtual Int_t CheckByteCount(UInt_t startpos, UInt_t bcnt, const char *classname); // SL
   virtual void SetByteCount(UInt_t cntpos, Bool_t packInVersion = kFALSE);           // SL

   virtual void SkipVersion(const TClass *cl = 0);/// Skip class version from I/O buffer.
   virtual Version_t ReadVersion(UInt_t *start = 0, UInt_t *bcnt = 0, const TClass *cl = 0); // SL
/// Read version value from buffer
/// actually version is normally defined by table name
/// and kept in intermediate variable fReadVersionBuffer   
   
   virtual UInt_t WriteVersion(const TClass *cl, Bool_t useBcnt = kFALSE);                   // SL
/// Copies class version to buffer, but not writes it to sql immidiately
/// Version will be used to produce complete table
/// name, which will include class version

   virtual void *ReadObjectAny(const TClass *clCast);/// Read object from buffer. Only used from TBuffer.
   virtual void SkipObjectAny();

   virtual void IncrementLevel(TVirtualStreamerInfo *);
/// Function is called from TStreamerInfo WriteBuffer and Readbuffer functions
/// and indent new level in data structure.
/// This call indicates, that TStreamerInfo functions starts streaming
/// object data of correspondent class   
   
   virtual void SetStreamerElementNumber(TStreamerElement *elem, Int_t comp_type);
/// Function is called from TStreamerInfo WriteBuffer and Readbuffer functions
/// and add/verify next element in sql tables
/// This calls allows separate data, correspondent to one class member, from another   
   
   virtual void DecrementLevel(TVirtualStreamerInfo *);
/// Function is called from TStreamerInfo WriteBuffer and Readbuffer functions
/// and decrease level in sql structure.

   virtual void ClassBegin(const TClass *, Version_t = -1);
/// This method inform buffer data of which class now
/// will be streamed. When reading, classversion should be specified
/// as was read by TBuffer::ReadVersion().
/// ClassBegin(), ClassEnd() & ClassMemeber() should be used in
/// custom class streamers to specify which kind of data are
/// now streamed to/from buffer. That information is used to correctly
/// convert class data to/from "normal" sql tables with meaningfull names
/// and correct datatypes. Without that functions data from custom streamer
/// will be saved as "raw" data in special _streamer_ table one value after another
/// Such MUST be used when object is written with standard ROOT streaming
/// procedure, but should be read back in custom streamer.
/// For example, custom streamer of TNamed class may look like:   
   
   virtual void ClassEnd(const TClass *);
/// Method indicates end of streaming of classdata in custom streamer.
/// See ClassBegin() method for more details.   
   
   virtual void ClassMember(const char *name, const char *typeName = 0, Int_t arrsize1 = -1, Int_t arrsize2 = -1);
/// Method indicates name and typename of class memeber,
/// which should be now streamed in custom streamer
/// Following combinations are supported:
/// see TBufferXML::ClassMember for the details.

   virtual void ReadFloat16(Float_t *f, TStreamerElement *ele = 0);
   virtual void WriteFloat16(Float_t *f, TStreamerElement *ele = 0);
   virtual void ReadDouble32(Double_t *d, TStreamerElement *ele = 0);
   virtual void WriteDouble32(Double_t *d, TStreamerElement *ele = 0);
   virtual void ReadWithFactor(Float_t *ptr, Double_t factor, Double_t minvalue);
   virtual void ReadWithNbits(Float_t *ptr, Int_t nbits);
   virtual void ReadWithFactor(Double_t *ptr, Double_t factor, Double_t minvalue);
   virtual void ReadWithNbits(Double_t *ptr, Int_t nbits);

   virtual Int_t ReadArray(Bool_t *&b);
   virtual Int_t ReadArray(Char_t *&c);
   virtual Int_t ReadArray(UChar_t *&c);
   virtual Int_t ReadArray(Short_t *&h);
   virtual Int_t ReadArray(UShort_t *&h);
   virtual Int_t ReadArray(Int_t *&i);
   virtual Int_t ReadArray(UInt_t *&i);
   virtual Int_t ReadArray(Long_t *&l);
   virtual Int_t ReadArray(ULong_t *&l);
   virtual Int_t ReadArray(Long64_t *&l);
   virtual Int_t ReadArray(ULong64_t *&l);
   virtual Int_t ReadArray(Float_t *&f);
   virtual Int_t ReadArray(Double_t *&d);
   virtual Int_t ReadArrayFloat16(Float_t *&f, TStreamerElement *ele = 0);
   virtual Int_t ReadArrayDouble32(Double_t *&d, TStreamerElement *ele = 0);

   virtual Int_t ReadStaticArray(Bool_t *b);
   virtual Int_t ReadStaticArray(Char_t *c);
   virtual Int_t ReadStaticArray(UChar_t *c);
   virtual Int_t ReadStaticArray(Short_t *h);
   virtual Int_t ReadStaticArray(UShort_t *h);
   virtual Int_t ReadStaticArray(Int_t *i);
   virtual Int_t ReadStaticArray(UInt_t *i);
   virtual Int_t ReadStaticArray(Long_t *l);
   virtual Int_t ReadStaticArray(ULong_t *l);
   virtual Int_t ReadStaticArray(Long64_t *l);
   virtual Int_t ReadStaticArray(ULong64_t *l);
   virtual Int_t ReadStaticArray(Float_t *f);
   virtual Int_t ReadStaticArray(Double_t *d);
   virtual Int_t ReadStaticArrayFloat16(Float_t *f, TStreamerElement *ele = 0);
   virtual Int_t ReadStaticArrayDouble32(Double_t *d, TStreamerElement *ele = 0);

   virtual void ReadFastArray(Bool_t *b, Int_t n);
   virtual void ReadFastArray(Char_t *c, Int_t n);
   virtual void ReadFastArray(UChar_t *c, Int_t n);
   virtual void ReadFastArray(Short_t *h, Int_t n);
   virtual void ReadFastArray(UShort_t *h, Int_t n);
   virtual void ReadFastArray(Int_t *i, Int_t n);
   virtual void ReadFastArray(UInt_t *i, Int_t n);
   virtual void ReadFastArray(Long_t *l, Int_t n);
   virtual void ReadFastArray(ULong_t *l, Int_t n);
   virtual void ReadFastArray(Long64_t *l, Int_t n);
   virtual void ReadFastArray(ULong64_t *l, Int_t n);
   virtual void ReadFastArray(Float_t *f, Int_t n);
   virtual void ReadFastArray(Double_t *d, Int_t n);
   virtual void ReadFastArrayFloat16(Float_t *f, Int_t n, TStreamerElement *ele = 0);
   virtual void ReadFastArrayDouble32(Double_t *d, Int_t n, TStreamerElement *ele = 0);
   virtual void ReadFastArrayWithFactor(Float_t *ptr, Int_t n, Double_t factor, Double_t minvalue);
   virtual void ReadFastArrayWithNbits(Float_t *ptr, Int_t n, Int_t nbits);
   virtual void ReadFastArrayWithFactor(Double_t *ptr, Int_t n, Double_t factor, Double_t minvalue);
   virtual void ReadFastArrayWithNbits(Double_t *ptr, Int_t n, Int_t nbits);

   virtual void WriteArray(const Bool_t *b, Int_t n);
   virtual void WriteArray(const Char_t *c, Int_t n);
   virtual void WriteArray(const UChar_t *c, Int_t n);
   virtual void WriteArray(const Short_t *h, Int_t n);
   virtual void WriteArray(const UShort_t *h, Int_t n);
   virtual void WriteArray(const Int_t *i, Int_t n);
   virtual void WriteArray(const UInt_t *i, Int_t n);
   virtual void WriteArray(const Long_t *l, Int_t n);
   virtual void WriteArray(const ULong_t *l, Int_t n);
   virtual void WriteArray(const Long64_t *l, Int_t n);
   virtual void WriteArray(const ULong64_t *l, Int_t n);
   virtual void WriteArray(const Float_t *f, Int_t n);
   virtual void WriteArray(const Double_t *d, Int_t n);
   virtual void WriteArrayFloat16(const Float_t *f, Int_t n, TStreamerElement *ele = 0);
   virtual void WriteArrayDouble32(const Double_t *d, Int_t n, TStreamerElement *ele = 0);
   virtual void
   ReadFastArray(void *start, const TClass *cl, Int_t n = 1, TMemberStreamer *s = 0, const TClass *onFileClass = 0);
   virtual void ReadFastArray(void **startp, const TClass *cl, Int_t n = 1, Bool_t isPreAlloc = kFALSE,
                              TMemberStreamer *s = 0, const TClass *onFileClass = 0);

   virtual void WriteFastArray(const Bool_t *b, Int_t n);
   virtual void WriteFastArray(const Char_t *c, Int_t n);
   virtual void WriteFastArray(const UChar_t *c, Int_t n);
   virtual void WriteFastArray(const Short_t *h, Int_t n);
   virtual void WriteFastArray(const UShort_t *h, Int_t n);
   virtual void WriteFastArray(const Int_t *i, Int_t n);
   virtual void WriteFastArray(const UInt_t *i, Int_t n);
   virtual void WriteFastArray(const Long_t *l, Int_t n);
   virtual void WriteFastArray(const ULong_t *l, Int_t n);
   virtual void WriteFastArray(const Long64_t *l, Int_t n);
   virtual void WriteFastArray(const ULong64_t *l, Int_t n);
   virtual void WriteFastArray(const Float_t *f, Int_t n);
   virtual void WriteFastArray(const Double_t *d, Int_t n);
   virtual void WriteFastArrayFloat16(const Float_t *f, Int_t n, TStreamerElement *ele = 0);
   virtual void WriteFastArrayDouble32(const Double_t *d, Int_t n, TStreamerElement *ele = 0);/// Write array of Double32_t to buffer
   virtual void WriteFastArray(void *start, const TClass *cl, Int_t n = 1, TMemberStreamer *s = 0);
/// Same functionality as TBuffer::WriteFastArray(...) but
/// instead of calling cl->Streamer(obj,buf) call here
/// buf.StreamObject(obj, cl). In that case it is easy to understand where
/// object data is started and finished   
   
   virtual Int_t
   WriteFastArray(void **startp, const TClass *cl, Int_t n = 1, Bool_t isPreAlloc = kFALSE, TMemberStreamer *s = 0);
/// Same functionality as TBuffer::WriteFastArray(...) but
/// instead of calling cl->Streamer(obj,buf) call here
/// buf.StreamObject(obj, cl). In that case it is easy to understand where
/// object data is started and finished

   virtual void StreamObject(void *obj, const std::type_info &typeinfo, const TClass *onFileClass = 0);
   virtual void StreamObject(void *obj, const char *className, const TClass *onFileClass = 0);
   virtual void StreamObject(void *obj, const TClass *cl, const TClass *onFileClass = 0);
   virtual void StreamObject(TObject *obj);/// Stream object to/from buffer
   virtual void
   StreamObject(void *obj, TMemberStreamer *streamer, const TClass *cl, Int_t n = 0, const TClass *onFileClass = 0);/// Stream object to/from buffer

   virtual void ReadBool(Bool_t &b);
   virtual void ReadChar(Char_t &c);
   virtual void ReadUChar(UChar_t &c);
   virtual void ReadShort(Short_t &s);
   virtual void ReadUShort(UShort_t &s);
   virtual void ReadInt(Int_t &i);
   virtual void ReadUInt(UInt_t &i);
   virtual void ReadLong(Long_t &l);
   virtual void ReadULong(ULong_t &l);
   virtual void ReadLong64(Long64_t &l);
   virtual void ReadULong64(ULong64_t &l);
   virtual void ReadFloat(Float_t &f);
   virtual void ReadDouble(Double_t &d);
   virtual void ReadCharP(Char_t *c);
   virtual void ReadTString(TString &s);
   virtual void ReadStdString(std::string *s);
   using TBuffer::ReadStdString;
   virtual void ReadCharStar(char *&s);

   virtual void WriteBool(Bool_t b);
   virtual void WriteChar(Char_t c);
   virtual void WriteUChar(UChar_t c);
   virtual void WriteShort(Short_t s);
   virtual void WriteUShort(UShort_t s);
   virtual void WriteInt(Int_t i);
   virtual void WriteUInt(UInt_t i);
   virtual void WriteLong(Long_t l);
   virtual void WriteULong(ULong_t l);
   virtual void WriteLong64(Long64_t l);
   virtual void WriteULong64(ULong64_t l);
   virtual void WriteFloat(Float_t f);
   virtual void WriteDouble(Double_t d);
   virtual void WriteCharP(const Char_t *c);/// Writes array of characters to buffer
   virtual void WriteTString(const TString &s);
   virtual void WriteStdString(const std::string *s);
   using TBuffer::WriteStdString;
   virtual void WriteCharStar(char *s);

   virtual Int_t ApplySequence(const TStreamerInfoActions::TActionSequence &sequence, void *object);
/// Read one collection of objects from the buffer using the StreamerInfoLoopAction.
/// The collection needs to be a split TClonesArray or a split vector of pointers.   
   
   virtual Int_t ApplySequenceVecPtr(const TStreamerInfoActions::TActionSequence &sequence, void *start_collection,
                                     void *end_collection);
/// Read one collection of objects from the buffer using the StreamerInfoLoopAction.
/// The collection needs to be a split TClonesArray or a split vector of pointers.

   virtual Int_t
   ApplySequence(const TStreamerInfoActions::TActionSequence &sequence, void *start_collection, void *end_collection);
/// Read one collection of objects from the buffer using the StreamerInfoLoopAction.


   static void SetFloatFormat(const char *fmt = "%e");
/// set printf format for float/double members, default "%e"
/// changes global TSQLServer variable   
   
   static const char *GetFloatFormat();
/// return current printf format for float/double members, default "%e"
/// return format, hold by TSQLServer

   // end of redefined virtual functions
```




<!-- TBufferSQL2.md ends here -->
