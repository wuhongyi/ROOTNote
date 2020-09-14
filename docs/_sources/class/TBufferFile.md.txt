<!-- TBufferFile.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 日 1月  6 12:10:43 2019 (+0800)
;; Last-Updated: 日 1月  6 12:53:51 2019 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# TBufferFile

The concrete implementation of TBuffer for writing/reading to/from a ROOT file or socket.

```cpp
class TBufferFile : public TBuffer
```

## class

```cpp
protected:
   typedef std::vector<TStreamerInfo*> InfoList_t;

   Int_t           fMapCount;      ///< Number of objects or classes in map
   Int_t           fMapSize;       ///< Default size of map
   Int_t           fDisplacement;  ///< Value to be added to the map offsets
   UShort_t        fPidOffset;     ///< Offset to be added to the pid index in this key/buffer.
   TExMap         *fMap;           ///< Map containing object,offset pairs for reading/writing
   TExMap         *fClassMap;      ///< Map containing object,class pairs for reading
   TStreamerInfo  *fInfo;          ///< Pointer to TStreamerInfo object writing/reading the buffer
   InfoList_t      fInfoStack;     ///< Stack of pointers to the TStreamerInfos

   static Int_t    fgMapSize;      ///< Default map size for all TBuffer objects

   // Default ctor
   TBufferFile() : TBuffer(), fMapCount(0), fMapSize(0),
               fDisplacement(0),fPidOffset(0), fMap(0), fClassMap(0),
     fInfo(0), fInfoStack() {}

   // TBuffer objects cannot be copied or assigned
   TBufferFile(const TBufferFile &);       ///<  not implemented
   void operator=(const TBufferFile &);    ///<  not implemented

   Int_t  CheckByteCount(UInt_t startpos, UInt_t bcnt, const TClass *clss, const char* classname);
/// Check byte count with current buffer position. They should
/// match. If not print warning and position buffer in correct
/// place determined by the byte count. Startpos is position of
/// first byte where the byte count is written in buffer.
/// Returns 0 if everything is ok, otherwise the bytecount offset
/// (< 0 when read too little, >0 when read too much).   
   
   void   CheckCount(UInt_t offset);
/// Check if offset is not too large (< kMaxMapCount) when writing.   
   
   UInt_t CheckObject(UInt_t offset, const TClass *cl, Bool_t readClass = kFALSE);
/// Check for object in the read map. If the object is 0 it still has to be
/// read. Try to read it from the buffer starting at location offset. If the
/// object is -1 then it really does not exist and we return 0. If the object
/// exists just return the offset.

   virtual  void  WriteObjectClass(const void *actualObjStart, const TClass *actualClass, Bool_t cacheReuse);
/// Write object to I/O buffer.
/// This function assumes that the value of 'actualObjectStart' is the actual start of
/// the object of class 'actualClass'
/// If 'cacheReuse' is true (default) upon seeing an object address a second time,
/// we record the offset where its was written the first time rather than streaming
/// the object a second time.
/// If 'cacheReuse' is false, we always stream the object.  This allows the (re)use
/// of temporary object to store different data in the same buffer.

public:
   enum { kMapSize = 503 };
   enum { kStreamedMemberWise = BIT(14) }; //added to version number to know if a collection has been stored member-wise
   enum EStatusBits {
     kNotDecompressed    = BIT(15),    //indicates a weird buffer, used by TBasket
     kTextBasedStreaming = BIT(18), //indicates if buffer used for XML/SQL object streaming

     kUser1 = BIT(21), //free for user
     kUser2 = BIT(22), //free for user
     kUser3 = BIT(23)  //free for user
   };

   TBufferFile(TBuffer::EMode mode);
/// Create an I/O buffer object. Mode should be either TBuffer::kRead or
/// TBuffer::kWrite. By default the I/O buffer has a size of
/// TBuffer::kInitialSize (1024) bytes.   
   
   TBufferFile(TBuffer::EMode mode, Int_t bufsiz);
/// Create an I/O buffer object. Mode should be either TBuffer::kRead or
/// TBuffer::kWrite.   
   
   TBufferFile(TBuffer::EMode mode, Int_t bufsiz, void *buf, Bool_t adopt = kTRUE, ReAllocCharFun_t reallocfunc = 0);
/// Create an I/O buffer object.
/// Mode should be either TBuffer::kRead or
/// TBuffer::kWrite. By default the I/O buffer has a size of
/// TBuffer::kInitialSize (1024) bytes. An external buffer can be passed
/// to TBuffer via the buf argument. By default this buffer will be adopted
/// unless adopt is false.
/// If the new buffer is <b>not</b> adopted and no memory allocation routine
/// is provided, a Fatal error will be issued if the Buffer attempts to
/// expand.   
   
   virtual ~TBufferFile();

   Int_t    GetMapCount() const { return fMapCount; }
   void     GetMappedObject(UInt_t tag, void* &ptr, TClass* &ClassPtr) const;
/// Retrieve the object stored in the buffer's object map at 'tag'
/// Set ptr and ClassPtr respectively to the address of the object and
/// a pointer to its TClass.   
   
   void     MapObject(const TObject *obj, UInt_t offset = 1);
/// Add object to the fMap container.
/// If obj is not 0 add object to the map (in read mode also add 0 objects to
/// the map). This method may only be called outside this class just before
/// calling obj->Streamer() to prevent self reference of obj, in case obj
/// contains (via via) a pointer to itself. In that case offset must be 1
/// (default value for offset).   
   
   void     MapObject(const void *obj, const TClass *cl, UInt_t offset = 1);
/// Add object to the fMap container.
/// If obj is not 0 add object to the map (in read mode also add 0 objects to
/// the map). This method may only be called outside this class just before
/// calling obj->Streamer() to prevent self reference of obj, in case obj
/// contains (via via) a pointer to itself. In that case offset must be 1
/// (default value for offset).   
   
   void     Reset() { SetBufferOffset(); ResetMap(); }
   void     InitMap();
/// Create the fMap container and initialize them
/// with the null object.   
   
   void     ResetMap();
/// Delete existing fMap and reset map counter.   
   
   void     SetReadParam(Int_t mapsize);
/// Set the initial size of the map used to store object and class
/// references during reading. The default size is TBufferFile::kMapSize.
/// Increasing the default has the benefit that when reading many
/// small objects the map does not need to be resized too often
/// (the system is always dynamic, even with the default everything
/// will work, only the initial resizing will cost some time).
/// This method can only be called directly after the creation of
/// the TBuffer, before any reading is done. Globally this option
/// can be changed using SetGlobalReadParam().   
   
   void     SetWriteParam(Int_t mapsize);
/// Set the initial size of the hashtable used to store object and class
/// references during writing. The default size is TBufferFile::kMapSize.
/// Increasing the default has the benefit that when writing many
/// small objects the hashtable does not get too many collisions
/// (the system is always dynamic, even with the default everything
/// will work, only a large number of collisions will cost performance).
/// For optimal performance hashsize should always be a prime.
/// This method can only be called directly after the creation of
/// the TBuffer, before any writing is done. Globally this option
/// can be changed using SetGlobalWriteParam().

   Bool_t   CheckObject(const TObject *obj);
/// Check if the specified object is already in the buffer.
/// Returns kTRUE if object already in the buffer, kFALSE otherwise
/// (also if obj is 0 or TBuffer not in writing mode).

   Bool_t   CheckObject(const void *obj, const TClass *ptrClass);
/// Check if the specified object of the specified class is already in
/// the buffer. Returns kTRUE if object already in the buffer,
/// kFALSE otherwise (also if obj is 0 ).

   virtual Int_t      GetVersionOwner() const;
/// Return the version number of the owner file.   
   
   virtual Int_t      CheckByteCount(UInt_t startpos, UInt_t bcnt, const TClass *clss);
/// Check byte count with current buffer position. They should
/// match. If not print warning and position buffer in correct
/// place determined by the byte count. Startpos is position of
/// first byte where the byte count is written in buffer.
/// Returns 0 if everything is ok, otherwise the bytecount offset
/// (< 0 when read too little, >0 when read too much).   
   
   virtual Int_t      CheckByteCount(UInt_t startpos, UInt_t bcnt, const char *classname);
/// Check byte count with current buffer position. They should
/// match. If not print warning and position buffer in correct
/// place determined by the byte count. Startpos is position of
/// first byte where the byte count is written in buffer.
/// Returns 0 if everything is ok, otherwise the bytecount offset
/// (< 0 when read too little, >0 when read too much).   
   
   virtual void       SetByteCount(UInt_t cntpos, Bool_t packInVersion = kFALSE);
/// Set byte count at position cntpos in the buffer. Generate warning if
/// count larger than kMaxMapCount. The count is excluded its own size.

   virtual void       SkipVersion(const TClass *cl = 0);
/// Skip class version from I/O buffer.   
   
   virtual Version_t  ReadVersion(UInt_t *start = 0, UInt_t *bcnt = 0, const TClass *cl = 0);
/// Read class version from I/O buffer.   
   
   virtual Version_t  ReadVersionNoCheckSum(UInt_t *start = 0, UInt_t *bcnt = 0);
/// Read class version from I/O buffer, when the caller knows for sure that
/// there is no checksum written/involved.   
   
   virtual Version_t  ReadVersionForMemberWise(const TClass *cl = 0);
/// Read class version from I/O buffer
/// To be used when streaming out member-wise streamed collection where we do not
/// care (not save) about the byte count and can safely ignore missing streamerInfo
/// (since they usually indicate empty collections).   
   
   virtual UInt_t     WriteVersion(const TClass *cl, Bool_t useBcnt = kFALSE);
/// Write class version to I/O buffer.   
   
   virtual UInt_t     WriteVersionMemberWise(const TClass *cl, Bool_t useBcnt = kFALSE);
/// Write class version to I/O buffer after setting the kStreamedMemberWise
/// bit in the version number.   

   virtual void      *ReadObjectAny(const TClass* cast);
/// Read object from I/O buffer.
/// A typical use for this function is:
///     MyClass *ptr = (MyClass*)b.ReadObjectAny(MyClass::Class());
/// I.e. clCast should point to a TClass object describing the class pointed
/// to by your pointer.
/// In case of multiple inheritance, the return value might not be the
/// real beginning of the object in memory.  You will need to use a
/// dynamic_cast later if you need to retrieve it.   
   
   virtual void       SkipObjectAny();
/// Skip any kind of object from buffer

   virtual void       TagStreamerInfo(TVirtualStreamerInfo* info);
/// Mark the classindex of the current file as using this TStreamerInfo   
   
   virtual void       IncrementLevel(TVirtualStreamerInfo* info);
/// Increment level.   
   
   virtual void       SetStreamerElementNumber(TStreamerElement*,Int_t) {}
   virtual void       DecrementLevel(TVirtualStreamerInfo*);
/// Decrement level.   
   
   TVirtualStreamerInfo  *GetInfo() {return (TVirtualStreamerInfo*)fInfo;}
   virtual void       ClassBegin(const TClass*, Version_t = -1) {}
   virtual void       ClassEnd(const TClass*) {}
   virtual void       ClassMember(const char*, const char* = 0, Int_t = -1, Int_t = -1) {}

   virtual Int_t      ReadBuf(void *buf, Int_t max);
/// Read max bytes from the I/O buffer into buf. The function returns
/// the actual number of bytes read.   
   
   virtual void       WriteBuf(const void *buf, Int_t max);
/// Write max bytes from buf into the I/O buffer.

   virtual char      *ReadString(char *s, Int_t max);
/// Read string from I/O buffer. String is read till 0 character is
/// found or till max-1 characters are read (i.e. string s has max
/// bytes allocated). If max = -1 no check on number of character is
/// made, reading continues till 0 character is found.

   virtual void       WriteString(const char *s);
/// Write string to I/O buffer. Writes string upto and including the
/// terminating 0.

   virtual TClass    *ReadClass(const TClass *cl = 0, UInt_t *objTag = 0);
/// Read class definition from I/O buffer.
/// \param[in] clReq Can be used to cross check if the actually read object is of the requested class.
/// \param[in] objTag Set in case the object is a reference to an already read object.   
   
   virtual void       WriteClass(const TClass *cl);
/// Write class description to I/O buffer.   

   virtual TObject   *ReadObject(const TClass *cl);
/// Read object from I/O buffer. clReq is NOT used.
/// The value returned is the address of the actual start in memory of
/// the object. Note that if the actual class of the object does not
/// inherit first from TObject, the type of the pointer is NOT 'TObject*'.
/// [More accurately, the class needs to start with the TObject part, for
/// the pointer to be a real TObject*].
/// We recommend using ReadObjectAny instead of ReadObject

   virtual void       WriteObject(const TObject *obj, Bool_t cacheReuse = kTRUE);
/// Write object to I/O buffer.

   using TBuffer::WriteObject;

   virtual Int_t      WriteObjectAny(const void *obj, const TClass *ptrClass, Bool_t cacheReuse = kTRUE);
/// Write object to I/O buffer.
/// This function assumes that the value in 'obj' is the value stored in
/// a pointer to a "ptrClass". The actual type of the object pointed to
/// can be any class derived from "ptrClass".
/// Return:
///   - 0: failure
///   - 1: success
///   - 2: truncated success (i.e actual class is missing. Only ptrClass saved.)
/// If 'cacheReuse' is true (default) upon seeing an object address a second time,
/// we record the offset where its was written the first time rather than streaming
/// the object a second time.
/// If 'cacheReuse' is false, we always stream the object.  This allows the (re)use
/// of temporary object to store different data in the same buffer.

   UShort_t GetPidOffset() const {
      // See comment in TBuffer::SetPidOffset
      return fPidOffset;
   }
   void     SetPidOffset(UShort_t offset);
/// This offset is used when a key (or basket) is transfered from one
/// file to the other.  In this case the TRef and TObject might have stored a
/// pid index (to retrieve TProcessIDs) which referred to their order on the original
/// file, the fPidOffset is to be added to those values to correctly find the
/// TProcessID.  This fPidOffset needs to be increment if the key/basket is copied
/// and need to be zero for new key/basket.   
   
   Int_t    GetBufferDisplacement() const { return fDisplacement; }
   void     SetBufferDisplacement() { fDisplacement = 0; }
   void     SetBufferDisplacement(Int_t skipped)
            { fDisplacement =  (Int_t)(Length() - skipped); }

   // basic types and arrays of basic types
   virtual   void     ReadFloat16 (Float_t *f, TStreamerElement *ele=0);
/// Read a Float16_t from the buffer,
/// see comments about Float16_t encoding at TBufferFile::WriteFloat16().   
   
   virtual   void     WriteFloat16(Float_t *f, TStreamerElement *ele=0);
/// Write a Float16_t to the buffer.
/// The following cases are supported for streaming a Float16_t type
/// depending on the range declaration in the comment field of the data member:
/// Case | Example |
/// -----|---------|
///  A   | Float16_t     fNormal; |
///  B   | Float16_t     fTemperature; //[0,100]|
///  C   | Float16_t     fCharge;      //[-1,1,2]|
///  D   | Float16_t     fVertex[3];   //[-30,30,10]|
///  E   | Float16_t     fChi2;        //[0,0,6]|
///  F   | Int_t         fNsp;<br>Float16_t*    fPointValue;   //[fNsp][0,3]|
///   - In case A fNormal is converted from a Float_t to a Float_t with mantissa truncated to 12 bits
///   - In case B fTemperature is converted to a 32 bit unsigned integer
///   - In case C fCharge is converted to a 2 bits unsigned integer
///   - In case D the array elements of fVertex are converted to an unsigned 10 bits integer
///   - In case E fChi2 is converted to a Float_t with truncated precision at 6 bits
///   - In case F the fNsp elements of array fPointvalue are converted to an unsigned 32 bit integer
/// Note that the range specifier must follow the dimension specifier.
/// Case B has more precision (9 to 10 significative digits than case A (6 to 7 digits).
/// The range specifier has the general format: [xmin,xmax] or [xmin,xmax,nbits]
///   - [0,1];
///   - [-10,100];
///   - [-pi,pi], [-pi/2,pi/4],[-2pi,2*pi]
///   - [-10,100,16]
///   - [0,0,8]
/// if nbits is not specified, or nbits <2 or nbits>16 it is set to 16. If
/// (xmin==0 and xmax==0 and nbits <=14) the float word will have
/// its mantissa truncated to nbits significative bits.
/// ## IMPORTANT NOTE
/// ### NOTE 1
/// Lets assume an original variable float x:
/// When using the format [0,0,8] (ie range not specified) you get the best
/// relative precision when storing and reading back the truncated x, say xt.
/// The variance of (x-xt)/x will be better than when specifying a range
/// for the same number of bits. However the precision relative to the
/// range (x-xt)/(xmax-xmin) will be worst, and vice-versa.
/// The format [0,0,8] is also interesting when the range of x is infinite
/// or unknown.
/// ### NOTE 2
/// It is important to understand the difference with the meaning of nbits
///   - in case of [-1,1,nbits], nbits is the total number of bits used to make
/// the conversion from a float to an integer
///   - in case of [0,0,nbits], nbits is the number of bits used for the mantissa
///  See example of use of the Float16_t data type in tutorial double32.C
///  \image html tbufferfile_double32.gif   
   
   virtual   void     ReadDouble32 (Double_t *d, TStreamerElement *ele=0);
/// Read a Double32_t from the buffer,
/// see comments about Double32_t encoding at TBufferFile::WriteDouble32().   
   
   virtual   void     WriteDouble32(Double_t *d, TStreamerElement *ele=0);
/// Write a Double32_t to the buffer.
/// The following cases are supported for streaming a Double32_t type
/// depending on the range declaration in the comment field of the data member:
/// Case | Example |
/// -----|---------|
///  A   | Double32_t     fNormal; |
///  B   | Double32_t     fTemperature; //[0,100]|
///  C   | Double32_t     fCharge;      //[-1,1,2]|
///  D   | Double32_t     fVertex[3];   //[-30,30,10]|
///  E   | Double32_t     fChi2;        //[0,0,6]|
///  F   | Int_t         fNsp;<br>Double32_t*    fPointValue;   //[fNsp][0,3]|
/// In case A fNormal is converted from a Double_t to a Float_t
/// In case B fTemperature is converted to a 32 bit unsigned integer
/// In case C fCharge is converted to a 2 bits unsigned integer
/// In case D the array elements of fVertex are converted to an unsigned 10 bits integer
/// In case E fChi2 is converted to a Float_t with mantissa truncated precision at 6 bits
/// In case F the fNsp elements of array fPointvalue are converted to an unsigned 32 bit integer
///           Note that the range specifier must follow the dimension specifier.
/// Case B has more precision (9 to 10 significative digits than case A (6 to 7 digits).
/// See TBufferFile::WriteFloat16 for more information.
///  see example of use of the Double32_t data type in tutorial double32.C
///  \image html tbufferfile_double32.gif   
   
   virtual   void     ReadWithFactor(Float_t *ptr, Double_t factor, Double_t minvalue);
/// Read a Float16_t from the buffer when the factor and minimum value have been specified
/// see comments about Double32_t encoding at TBufferFile::WriteDouble32().   
   
   virtual   void     ReadWithNbits(Float_t *ptr, Int_t nbits);
/// Read a Float16_t from the buffer when the number of bits is specified (explicitly or not)
/// see comments about Float16_t encoding at TBufferFile::WriteFloat16().   
   
   virtual   void     ReadWithFactor(Double_t *ptr, Double_t factor, Double_t minvalue);
/// Read a Double32_t from the buffer when the factor and minimum value have been specified
/// see comments about Double32_t encoding at TBufferFile::WriteDouble32().   
   
   virtual   void     ReadWithNbits(Double_t *ptr, Int_t nbits);
/// Read a Double32_t from the buffer when the number of bits is specified (explicitly or not)
/// see comments about Double32_t encoding at TBufferFile::WriteDouble32().   

   virtual   Int_t    ReadArray(Bool_t    *&b);
   virtual   Int_t    ReadArray(Char_t    *&c);
   virtual   Int_t    ReadArray(UChar_t   *&c);
   virtual   Int_t    ReadArray(Short_t   *&h);
   virtual   Int_t    ReadArray(UShort_t  *&h);
   virtual   Int_t    ReadArray(Int_t     *&i);
   virtual   Int_t    ReadArray(UInt_t    *&i);
   virtual   Int_t    ReadArray(Long_t    *&l);
   virtual   Int_t    ReadArray(ULong_t   *&l);
   virtual   Int_t    ReadArray(Long64_t  *&l);
   virtual   Int_t    ReadArray(ULong64_t *&l);
   virtual   Int_t    ReadArray(Float_t   *&f);
   virtual   Int_t    ReadArray(Double_t  *&d);
   virtual   Int_t    ReadArrayFloat16(Float_t  *&f, TStreamerElement *ele=0);
/// Read array of floats (written as truncated float) from the I/O buffer.
/// Returns the number of floats read.
/// If argument is a 0 pointer then space will be allocated for the array.
/// see comments about Float16_t encoding at TBufferFile::WriteFloat16   
   
   virtual   Int_t    ReadArrayDouble32(Double_t  *&d, TStreamerElement *ele=0);
/// Read array of doubles (written as float) from the I/O buffer.
/// Returns the number of doubles read.
/// If argument is a 0 pointer then space will be allocated for the array.
/// see comments about Double32_t encoding at TBufferFile::WriteDouble32


   virtual   Int_t    ReadStaticArray(Bool_t    *b);
   virtual   Int_t    ReadStaticArray(Char_t    *c);
   virtual   Int_t    ReadStaticArray(UChar_t   *c);
   virtual   Int_t    ReadStaticArray(Short_t   *h);
   virtual   Int_t    ReadStaticArray(UShort_t  *h);
   virtual   Int_t    ReadStaticArray(Int_t     *i);
   virtual   Int_t    ReadStaticArray(UInt_t    *i);
   virtual   Int_t    ReadStaticArray(Long_t    *l);
   virtual   Int_t    ReadStaticArray(ULong_t   *l);
   virtual   Int_t    ReadStaticArray(Long64_t  *l);
   virtual   Int_t    ReadStaticArray(ULong64_t *l);
   virtual   Int_t    ReadStaticArray(Float_t   *f);
   virtual   Int_t    ReadStaticArray(Double_t  *d);
   virtual   Int_t    ReadStaticArrayFloat16(Float_t  *f, TStreamerElement *ele=0);
/// Read array of floats (written as truncated float) from the I/O buffer.
/// Returns the number of floats read.
/// see comments about Float16_t encoding at TBufferFile::WriteFloat16   
   
   virtual   Int_t    ReadStaticArrayDouble32(Double_t  *d, TStreamerElement *ele=0);
/// Read array of doubles (written as float) from the I/O buffer.
/// Returns the number of doubles read.
/// see comments about Double32_t encoding at TBufferFile::WriteDouble32


   virtual   void     ReadFastArray(Bool_t    *b, Int_t n);
   virtual   void     ReadFastArray(Char_t    *c, Int_t n);
   virtual   void     ReadFastArrayString(Char_t    *c, Int_t n);
   virtual   void     ReadFastArray(UChar_t   *c, Int_t n);
   virtual   void     ReadFastArray(Short_t   *h, Int_t n);
   virtual   void     ReadFastArray(UShort_t  *h, Int_t n);
   virtual   void     ReadFastArray(Int_t     *i, Int_t n);
   virtual   void     ReadFastArray(UInt_t    *i, Int_t n);
   virtual   void     ReadFastArray(Long_t    *l, Int_t n);
   virtual   void     ReadFastArray(ULong_t   *l, Int_t n);
   virtual   void     ReadFastArray(Long64_t  *l, Int_t n);
   virtual   void     ReadFastArray(ULong64_t *l, Int_t n);
   virtual   void     ReadFastArray(Float_t   *f, Int_t n);
   virtual   void     ReadFastArray(Double_t  *d, Int_t n);
   virtual   void     ReadFastArrayFloat16(Float_t  *f, Int_t n, TStreamerElement *ele=0);
/// Read array of n floats (written as truncated float) from the I/O buffer.
/// see comments about Float16_t encoding at TBufferFile::WriteFloat16   
   
   virtual   void     ReadFastArrayDouble32(Double_t  *d, Int_t n, TStreamerElement *ele=0);
/// Read array of n doubles (written as float) from the I/O buffer.
/// see comments about Double32_t encoding at TBufferFile::WriteDouble32   
   
   virtual   void     ReadFastArrayWithFactor(Float_t *ptr, Int_t n, Double_t factor, Double_t minvalue) ;
/// Read array of n floats (written as truncated float) from the I/O buffer.
/// see comments about Float16_t encoding at TBufferFile::WriteFloat16   
   
   virtual   void     ReadFastArrayWithNbits(Float_t *ptr, Int_t n, Int_t nbits);
/// Read array of n floats (written as truncated float) from the I/O buffer.
/// see comments about Float16_t encoding at TBufferFile::WriteFloat16   
   
   virtual   void     ReadFastArrayWithFactor(Double_t *ptr, Int_t n, Double_t factor, Double_t minvalue);
/// Read array of n doubles (written as float) from the I/O buffer.
/// see comments about Double32_t encoding at TBufferFile::WriteDouble32   
   
   virtual   void     ReadFastArrayWithNbits(Double_t *ptr, Int_t n, Int_t nbits) ;
/// Read array of n doubles (written as float) from the I/O buffer.
/// see comments about Double32_t encoding at TBufferFile::WriteDouble32   
   
   virtual   void     ReadFastArray(void  *start , const TClass *cl, Int_t n=1, TMemberStreamer *s=0, const TClass* onFileClass=0 );
/// Read an array of 'n' objects from the I/O buffer.
/// Stores the objects read starting at the address 'start'.
/// The objects in the array are assume to be of class 'cl'.   
   
   virtual   void     ReadFastArray(void **startp, const TClass *cl, Int_t n=1, Bool_t isPreAlloc=kFALSE, TMemberStreamer *s=0, const TClass* onFileClass=0);
/// Read an array of 'n' objects from the I/O buffer.
/// The objects read are stored starting at the address '*start'
/// The objects in the array are assumed to be of class 'cl' or a derived class.
/// 'mode' indicates whether the data member is marked with '->'


   virtual   void     WriteArray(const Bool_t    *b, Int_t n);
   virtual   void     WriteArray(const Char_t    *c, Int_t n);
   virtual   void     WriteArray(const UChar_t   *c, Int_t n);
   virtual   void     WriteArray(const Short_t   *h, Int_t n);
   virtual   void     WriteArray(const UShort_t  *h, Int_t n);
   virtual   void     WriteArray(const Int_t     *i, Int_t n);
   virtual   void     WriteArray(const UInt_t    *i, Int_t n);
   virtual   void     WriteArray(const Long_t    *l, Int_t n);
   virtual   void     WriteArray(const ULong_t   *l, Int_t n);
   virtual   void     WriteArray(const Long64_t  *l, Int_t n);
   virtual   void     WriteArray(const ULong64_t *l, Int_t n);
   virtual   void     WriteArray(const Float_t   *f, Int_t n);
   virtual   void     WriteArray(const Double_t  *d, Int_t n);
   virtual   void     WriteArrayFloat16(const Float_t  *f, Int_t n, TStreamerElement *ele=0);
/// Write array of n floats (as truncated float) into the I/O buffer.
/// see comments about Float16_t encoding at TBufferFile::WriteFloat16   
   
   virtual   void     WriteArrayDouble32(const Double_t  *d, Int_t n, TStreamerElement *ele=0);
/// Write array of n doubles (as float) into the I/O buffer.
/// see comments about Double32_t encoding at TBufferFile::WriteDouble32

   virtual   void     WriteFastArray(const Bool_t    *b, Int_t n);
   virtual   void     WriteFastArray(const Char_t    *c, Int_t n);
   virtual   void     WriteFastArrayString(const Char_t    *c, Int_t n);/// Write array of n characters into the I/O buffer.
   virtual   void     WriteFastArray(const UChar_t   *c, Int_t n);
   virtual   void     WriteFastArray(const Short_t   *h, Int_t n);
   virtual   void     WriteFastArray(const UShort_t  *h, Int_t n);
   virtual   void     WriteFastArray(const Int_t     *i, Int_t n);
   virtual   void     WriteFastArray(const UInt_t    *i, Int_t n);
   virtual   void     WriteFastArray(const Long_t    *l, Int_t n);
   virtual   void     WriteFastArray(const ULong_t   *l, Int_t n);
   virtual   void     WriteFastArray(const Long64_t  *l, Int_t n);
   virtual   void     WriteFastArray(const ULong64_t *l, Int_t n);
   virtual   void     WriteFastArray(const Float_t   *f, Int_t n);/// Write array of n floats into the I/O buffer.
   virtual   void     WriteFastArray(const Double_t  *d, Int_t n);/// Write array of n doubles into the I/O buffer.
   virtual   void     WriteFastArrayFloat16(const Float_t  *f, Int_t n, TStreamerElement *ele=0);
/// Write array of n floats (as truncated float) into the I/O buffer.
/// see comments about Float16_t encoding at TBufferFile::WriteFloat16   
   
   virtual   void     WriteFastArrayDouble32(const Double_t  *d, Int_t n, TStreamerElement *ele=0);
/// Write array of n doubles (as float) into the I/O buffer.
/// see comments about Double32_t encoding at TBufferFile::WriteDouble32   
   
   virtual   void     WriteFastArray(void  *start,  const TClass *cl, Int_t n=1, TMemberStreamer *s=0);
/// Write an array of object starting at the address 'start' and of length 'n'
/// the objects in the array are assumed to be of class 'cl'   
   
   virtual   Int_t    WriteFastArray(void **startp, const TClass *cl, Int_t n=1, Bool_t isPreAlloc=kFALSE, TMemberStreamer *s=0);
/// Write an array of object starting at the address '*start' and of length 'n'
/// the objects in the array are of class 'cl'
/// 'isPreAlloc' indicates whether the data member is marked with '->'
/// Return:
///   - 0: success
///   - 2: truncated success (i.e actual class is missing. Only ptrClass saved.)

   virtual   void     StreamObject(void *obj, const std::type_info &typeinfo, const TClass* onFileClass = 0 );
/// Stream an object given its C++ typeinfo information.   
   
   virtual   void     StreamObject(void *obj, const char *className, const TClass* onFileClass = 0 );
/// Stream an object given the name of its actual class.   
   
   virtual   void     StreamObject(void *obj, const TClass *cl, const TClass* onFileClass = 0 );
/// Stream an object given a pointer to its actual class.   
   
   virtual   void     StreamObject(TObject *obj);
/// Stream an object inheriting from TObject using its streamer.   

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
/// Read char* from TBuffer.

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
   using              TBuffer::WriteStdString;
   virtual   void     WriteStdString(const std::string *s);
   virtual   void     WriteCharStar(char *s);
/// Write char* into TBuffer.

   // Special basic ROOT objects and collections
   virtual   TProcessID *GetLastProcessID(TRefTable *reftable) const;
/// Return the last TProcessID in the file.   
   
   virtual   UInt_t      GetTRefExecId();
/// Return the exec id stored in the current TStreamerInfo element.
/// The execid has been saved in the unique id of the TStreamerElement
/// being read by TStreamerElement::Streamer.
/// The current element (fgElement) is set as a static global
/// by TStreamerInfo::ReadBuffer (Clones) when reading this TRef.   
   
   virtual   TProcessID *ReadProcessID(UShort_t pidf);
/// The TProcessID with number pidf is read from file.
/// If the object is not already entered in the gROOT list, it is added.   
   
   virtual   UShort_t    WriteProcessID(TProcessID *pid);
/// Check if the ProcessID pid is already in the file.
/// If not, add it and return the index number in the local file list.

   // Utilities for TStreamerInfo
   virtual   void   ForceWriteInfo(TVirtualStreamerInfo *info, Bool_t force);
/// force writing the TStreamerInfo to the file   
   
   virtual   void   ForceWriteInfoClones(TClonesArray *a);
/// Make sure TStreamerInfo is not optimized, otherwise it will not be
/// possible to support schema evolution in read mode.
/// In case the StreamerInfo has already been computed and optimized,
/// one must disable the option BypassStreamer.   
   
   virtual   Int_t  ReadClones (TClonesArray *a, Int_t nobjects, Version_t objvers);
/// Interface to TStreamerInfo::ReadBufferClones.   
   
   virtual   Int_t  WriteClones(TClonesArray *a, Int_t nobjects);
/// Interface to TStreamerInfo::WriteBufferClones.

   // Utilities for TClass
   virtual   Int_t  ReadClassEmulated(const TClass *cl, void *object, const TClass *onfile_class);
/// Read emulated class.   
   
   virtual   Int_t  ReadClassBuffer(const TClass *cl, void *pointer, const TClass *onfile_class);
/// Deserialize information from a buffer into an object.
/// Note: This function is called by the xxx::Streamer()
/// functions in rootcint-generated dictionaries.   
   
   virtual   Int_t  ReadClassBuffer(const TClass *cl, void *pointer, Int_t version, UInt_t start, UInt_t count, const TClass *onfile_class);
/// Deserialize information from a buffer into an object.
/// Note: This function is called by the xxx::Streamer() functions in
/// rootcint-generated dictionaries.
/// This function assumes that the class version and the byte count
/// information have been read.
/// \param[in] version The version number of the class
/// \param[in] start   The starting position in the buffer b
/// \param[in] count   The number of bytes for this object in the buffer   
   
   virtual   Int_t  WriteClassBuffer(const TClass *cl, void *pointer);
/// Function called by the Streamer functions to serialize object at p
/// to buffer b. The optional argument info may be specified to give an
/// alternative StreamerInfo instead of using the default StreamerInfo
/// automatically built from the class definition.
/// For more information, see class TStreamerInfo.

   // Utilites to streamer using sequences.
   Int_t ApplySequence(const TStreamerInfoActions::TActionSequence &sequence, void *object);
/// Read one collection of objects from the buffer using the StreamerInfoLoopAction.
/// The collection needs to be a split TClonesArray or a split vector of pointers.   
   
   Int_t ApplySequenceVecPtr(const TStreamerInfoActions::TActionSequence &sequence, void *start_collection, void *end_collection);
/// Read one collection of objects from the buffer using the StreamerInfoLoopAction.
/// The collection needs to be a split TClonesArray or a split vector of pointers.   
   
   Int_t ApplySequence(const TStreamerInfoActions::TActionSequence &sequence, void *start_collection, void *end_collection);
/// Read one collection of objects from the buffer using the StreamerInfoLoopAction.

   static void    SetGlobalReadParam(Int_t mapsize);
/// Set the initial size of the map used to store object and class
/// references during reading.
/// The default size is kMapSize.
/// Increasing the default has the benefit that when reading many
/// small objects the array does not need to be resized too often
/// (the system is always dynamic, even with the default everything
/// will work, only the initial resizing will cost some time).
/// Per TBuffer object this option can be changed using SetReadParam().   
   
   static void    SetGlobalWriteParam(Int_t mapsize);
/// Set the initial size of the map used to store object and class
/// references during reading.
/// The default size is kMapSize.
/// Increasing the default has the benefit that when reading many
/// small objects the array does not need to be resized too often
/// (the system is always dynamic, even with the default everything
/// will work, only the initial resizing will cost some time).
/// Per TBuffer object this option can be changed using SetReadParam().   
   
   static Int_t   GetGlobalReadParam();
/// Get default read map size.

   static Int_t   GetGlobalWriteParam();
/// Get default write map size.   
```


<!-- TBufferFile.md ends here -->
