<!-- TZIPFile.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 日 1月  6 13:41:53 2019 (+0800)
;; Last-Updated: 三 9月 16 10:33:01 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TZIPFile*

```
Describes a ZIP archive file containing multiple sub-files.

Typically the sub-files are ROOT files. Notice that
the ROOT files should not be compressed when being added to the
ZIP file, since ROOT files are normally already compressed.
Such a ZIP file should be created like:
    zip -n root multi file1.root file2.root
which creates a ZIP file multi.zip.
A ZIP archive consists of files compressed with the popular ZLIB
compression algorithm. The archive format is used among others by
PKZip and Info-ZIP. The compression algorithm is also used by
GZIP and the PNG graphics standard. The format of the archives is
explained briefly below. This class provides an interface to read
such archives.
A ZIP archive contains a prefix, series of archive members
(sub-files), and a central directory. In theory the archive could
span multiple disks (or files) with the central directory of the
whole archive on the last disk, but this class does not support
such multi-part archives. The prefix is only used in self-extracting
executable archive files.
The members are stored in the archive sequentially, each with a
local header followed by the (optionally) compressed data; the local
header describes the member, including its file name and compressed
and real sizes. The central directory includes the member details
again, plus allows an extra member comment to be added. The last
member in the central directory is an end marker that can contain
a comment for the whole archive. Both the local header and the
central directory can also carry extra member-specific data; the
data in the local and global parts can be different.
The fact that the archive has a global directory makes it efficient
and allows for only the reading of the desired data, one does not
have to scan through the whole file to find the desired sub-file.
The Zip64 extensions are supported so files larger than 2GB can be
stored in archives larger than 4 GB.
Once the archive has been opened, the client can query the members
and read their contents by asking the archive for an offset where
the sub-file starts. The members can be accessed in any order.
```


```cpp
class TZIPFile : public TArchiveFile

class TZIPMember : public TArchiveMember
```

## class

```cpp
protected:
   Long64_t    fDirPos;     ///< Central directory position
   Long64_t    fDirSize;    ///< Central directory size
   Long64_t    fDirOffset;  ///< Central directory offset (from the beginning of the archive)
   TString     fComment;    ///< Archive comment

   Long64_t   FindEndHeader();
/// Find the end header of the ZIP archive. Returns 0 in case of error.   
   
   Int_t      ReadEndHeader(Long64_t pos);
/// Read the end header of the ZIP archive including the archive comment
/// at the current file position. Check that it really was a single-disk
/// archive with all the entries as expected. Most importantly, figure
/// out where the central directory begins. Returns -1 in case of error,
/// 0 otherwise.   
   
   Long64_t   ReadZip64EndLocator(Long64_t pos);
/// Read Zip64 end of central directory locator. Returns -1 in case of error,
/// -2 in case end locator magic is not found (i.e. not a zip64 file) and
/// offset of Zip64 end of central directory record in case of success.   
   
   Int_t      ReadZip64EndRecord(Long64_t pos);
/// Read Zip64 end of central directory record. Returns -1 in case of error
/// and 0 in case of success.   
   
   Int_t      ReadDirectory();
/// Read the directory of the ZIP archive. Returns -1 in case of error,
/// 0 otherwise.   
   
   Int_t      ReadMemberHeader(TZIPMember *member);
/// Read the member header of the ZIP archive. Sets the position where
/// the data starts in the member object. Returns -1 in case of error,
/// 0 otherwise.   
   
   UInt_t     Get(const void *buffer, Int_t bytes);
/// Read a "bytes" long little-endian integer value from "buffer".   
   
   ULong64_t  Get64(const void *buffer, Int_t bytes);
/// Read a 8 byte long little-endian integer value from "buffer".   
   
   Int_t      DecodeZip64ExtendedExtraField(TZIPMember *m, Bool_t global = kTRUE);
/// Decode the Zip64 extended extra field. If global is true, decode the
/// extra field coming from the central directory, if false decode the
/// extra field coming from the local file header. Returns -1 in case of
/// error, -2 in case Zip64 extra block was not found and 0 in case of
/// success.

   /// ZIP archive constants
   enum EZIPConstants {
      // - Archive version required (and made)
      kARCHIVE_VERSION     = 45,

      // - Magic header constants
      kDIR_HEADER_MAGIC       = 0x02014b50,
      kENTRY_HEADER_MAGIC     = 0x04034b50,
      kEND_HEADER_MAGIC       = 0x06054b50,
      kZIP64_EDR_HEADER_MAGIC = 0x06064b50,
      kZIP64_EDL_HEADER_MAGIC = 0x07064b50,
      kZIP64_EXTENDED_MAGIC   = 0x0001,     ///< Zip64 Extended Information Extra Field
      kZIP_MAGIC_LEN          = 4,          ///< Length of magic's
      kMAX_VAR_LEN            = 0xffff,     ///< Max variable-width field length
      kMAX_SIZE               = 0xffffffff, ///< Max size of things

      // - Offsets into the central directory headers
      kDIR_MAGIC_OFF      = 0,
      kDIR_VMADE_OFF      = 4,    kDIR_VMADE_LEN          = 2,
      kDIR_VREQD_OFF      = 6,    kDIR_VREQD_LEN          = 2,
      kDIR_FLAG_OFF       = 8,    kDIR_FLAG_LEN           = 2,
      kDIR_METHOD_OFF     = 10,   kDIR_METHOD_LEN         = 2,
      kDIR_DATE_OFF       = 12,   kDIR_DATE_LEN           = 4,
      kDIR_CRC32_OFF      = 16,   kDIR_CRC32_LEN          = 4,
      kDIR_CSIZE_OFF      = 20,   kDIR_CSIZE_LEN          = 4,
      kDIR_USIZE_OFF      = 24,   kDIR_USIZE_LEN          = 4,
      kDIR_NAMELEN_OFF    = 28,   kDIR_NAMELEN_LEN        = 2,
      kDIR_EXTRALEN_OFF   = 30,   kDIR_EXTRALEN_LEN       = 2,
      kDIR_COMMENTLEN_OFF = 32,   kDIR_COMMENTLEN_LEN     = 2,
      kDIR_DISK_START_OFF = 34,   kDIR_DISK_START_LEN     = 2,
      kDIR_INT_ATTR_OFF   = 36,   kDIR_INT_ATTR_LEN       = 2,
      kDIR_EXT_ATTR_OFF   = 38,   kDIR_EXT_ATTR_LEN       = 4,
      kDIR_ENTRY_POS_OFF  = 42,   kDIR_ENTRY_POS_LEN      = 4,
      kDIR_HEADER_SIZE    = 46,

      // - Offsets into the Zip64 end of central directory record (EDR)
      kZIP64_EDR_MAGIC_OFF      = 0,
      kZIP64_EDR_SIZE_OFF       = 4,  kZIP64_EDR_SIZE_LEN       = 8,
      kZIP64_EDR_VERS_MADE_OFF  = 12, kZIP64_EDR_VERS_MADE_LEN  = 2,
      kZIP64_EDR_VERS_EXT_OFF   = 14, kZIP64_EDR_VERS_EXT_LEN   = 2,
      kZIP64_EDR_DISK_OFF       = 16, kZIP64_EDR_DISK_LEN       = 4,
      kZIP64_EDR_DIR_DISK_OFF   = 20, kZIP64_EDR_DIR_DISK_LEN   = 4,
      kZIP64_EDR_DISK_HDRS_OFF  = 24, kZIP64_EDR_DISK_HDRS_LEN  = 8,
      kZIP64_EDR_TOTAL_HDRS_OFF = 32, kZIP64_EDR_TOTAL_HDRS_LEN = 8,
      kZIP64_EDR_DIR_SIZE_OFF   = 40, kZIP64_EDR_DIR_SIZE_LEN   = 8,
      kZIP64_EDR_DIR_OFFSET_OFF = 48, kZIP64_EDR_DIR_OFFSET_LEN = 8,
      kZIP64_EDR_HEADER_SIZE    = 56,

      // - Offsets into the Zip64 end of central directory locator (EDL)
      kZIP64_EDL_MAGIC_OFF      = 0,
      kZIP64_EDL_DISK_OFF       = 4,  kZIP64_EDL_DISK_LEN       = 4,
      kZIP64_EDL_REC_OFFSET_OFF = 8,  kZIP64_EDL_REC_OFFSET_LEN = 8,
      kZIP64_EDL_TOTAL_DISK_OFF = 16, kZIP64_EDL_TOTAL_DISK_LEN = 4,
      kZIP64_EDL_HEADER_SIZE    = 20,

      // - Offsets into the end-of-archive header
      kEND_MAGIC_OFF      = 0,
      kEND_DISK_OFF       = 4,    kEND_DISK_LEN           = 2,
      kEND_DIR_DISK_OFF   = 6,    kEND_DIR_DISK_LEN       = 2,
      kEND_DISK_HDRS_OFF  = 8,    kEND_DISK_HDRS_LEN      = 2,
      kEND_TOTAL_HDRS_OFF = 10,   kEND_TOTAL_HDRS_LEN     = 2,
      kEND_DIR_SIZE_OFF   = 12,   kEND_DIR_SIZE_LEN       = 4,
      kEND_DIR_OFFSET_OFF = 16,   kEND_DIR_OFFSET_LEN     = 4,
      kEND_COMMENTLEN_OFF = 20,   kEND_COMMENTLEN_LEN     = 2,
      kEND_HEADER_SIZE    = 22,

      // - Offsets into the local entry headers
      kENTRY_MAGIC_OFF    = 0,
      kENTRY_VREQD_OFF    = 4,    kENTRY_VREQD_LEN        = 2,
      kENTRY_FLAG_OFF     = 6,    kENTRY_FLAG_LEN         = 2,
      kENTRY_METHOD_OFF   = 8,    kENTRY_METHOD_LEN       = 2,
      kENTRY_DATE_OFF     = 10,   kENTRY_DATE_LEN         = 4,
      kENTRY_CRC32_OFF    = 14,   kENTRY_CRC32_LEN        = 4,
      kENTRY_CSIZE_OFF    = 18,   kENTRY_CSIZE_LEN        = 4,
      kENTRY_USIZE_OFF    = 22,   kENTRY_USIZE_LEN        = 4,
      kENTRY_NAMELEN_OFF  = 26,   kENTRY_NAMELEN_LEN      = 2,
      kENTRY_EXTRALEN_OFF = 28,   kENTRY_EXTRALEN_LEN     = 2,
      kENTRY_HEADER_SIZE  = 30,

      // - Offsets into the Zip64 Extended Information Extra Field
      kZIP64_EXTENDED_MAGIC_OFF      = 0,  kZIP64_EXTENDED_MAGIC_LEN      = 2,
      kZIP64_EXTENDED_SIZE_OFF       = 2,  kZIP64_EXTENDED_SIZE_LEN       = 2,
      kZIP64_EXTENDED_USIZE_OFF      = 4,  kZIP64_EXTENDED_USIZE_LEN      = 8,
      kZIP64_EXTENTED_CSIZE_OFF      = 12, kZIP64_EXTENDED_CSIZE_LEN      = 8,
      kZIP64_EXTENDED_HDR_OFFSET_OFF = 20, kZIP64_EXTENDED_HDR_OFFSET_LEN = 8,
      kZIP64_EXTENDED_DISK_OFF       = 28, kZIP64_EXTENDED_DISK_LEN       = 4,
      kZIP64_EXTENDED_SIZE           = 32,

      // - Compression method and strategy
      kSTORED              = 0,            ///< Stored as is
      kDEFLATED            = 8             ///< Stored using deflate
   };

   TZIPFile(const TZIPFile&); // Not implemented
   TZIPFile& operator=(const TZIPFile&); // Not implemented

public:
   TZIPFile();
   TZIPFile(const char *archive, const char *member, TFile *file);
/// Specify the archive name and member name. The member can be a decimal
/// number which allows to access the n-th member.   
   
   virtual ~TZIPFile() { }

   virtual Int_t OpenArchive();
/// Open archive and read end-header and directory. Returns -1 in case
/// of error, 0 otherwise.   
   
   virtual Int_t SetCurrentMember();
/// Find the desired member in the member array and make it the
/// current member. Returns -1 in case member is not found, 0 otherwise.

   void          Print(Option_t *option = "") const;
/// Pretty print ZIP archive members.
```

----

**TZIPMember**

```cpp
/**
\class TZIPMember
\ingroup IO
A ZIP archive consists of files compressed with the popular ZLIB
compression algorithm; this class records the information about a
single archive member.
*/

friend class TZIPFile;

private:
   void          *fLocal;     ///< Extra file header data
   UInt_t         fLocalLen;  ///< Length of extra file header data
   void          *fGlobal;    ///< Extra directory data
   UInt_t         fGlobalLen; ///< Length of extra directory data
   UInt_t         fCRC32;     ///< CRC-32 for all decompressed data
   UInt_t         fAttrInt;   ///< Internal file attributes
   UInt_t         fAttrExt;   ///< External file attributes
   UInt_t         fMethod;    ///< Compression type
   UInt_t         fLevel;     ///< Compression level

public:
   TZIPMember();
   TZIPMember(const char *name);/// Create ZIP member file.
   TZIPMember(const TZIPMember &member);
   TZIPMember &operator=(const TZIPMember &rhs);
   virtual ~TZIPMember();

   void     *GetLocal() const { return fLocal; }
   UInt_t    GetLocalLen() const { return fLocalLen; }
   void     *GetGlobal() const { return fGlobal; }
   UInt_t    GetGlobalLen() const { return fGlobalLen; }
   UInt_t    GetCRC32() const { return fCRC32; }
   UInt_t    GetAttrInt() const { return fAttrInt; }
   UInt_t    GetAttrExt() const { return fAttrExt; }
   UInt_t    GetMethod() const { return fMethod; }
   UInt_t    GetLevel() const { return fLevel; }

   void      Print(Option_t *option = "") const;
/// Pretty print basic ZIP member info.   
```

<!-- TZIPFile.md ends here -->
