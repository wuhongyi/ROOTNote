<!-- TMemFile.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 日 1月  6 14:36:17 2019 (+0800)
;; Last-Updated: 三 9月 16 10:31:36 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TMemFile*

A TMemFile is like a normal TFile except that it reads and writes only from memory.

```cpp
TMemFile : public TFile
```

## class

```cpp
private:
   struct TMemBlock {
   private:
      TMemBlock(const TMemBlock&);            // Not implemented
      TMemBlock &operator=(const TMemBlock&); // Not implemented.
   public:
      TMemBlock();
      TMemBlock(Long64_t size, TMemBlock *previous = 0);
      ~TMemBlock();

      void CreateNext(Long64_t size);

      TMemBlock *fPrevious;
      TMemBlock *fNext;
      UChar_t   *fBuffer;
      Long64_t   fSize;
   };
   TMemBlock    fBlockList;   ///< Colletion of memory blocks of size fBlockSize
   Long64_t     fSize;        ///< Total file size (sum of the size of the chunks)
   Long64_t     fSysOffset;   ///< Seek offset in file
   TMemBlock   *fBlockSeek;   ///< Pointer to the block we seeked to.
   Long64_t     fBlockOffset; ///< Seek offset within the block

   static Long64_t fgDefaultBlockSize;

   Long64_t MemRead(Int_t fd, void *buf, Long64_t len) const;

   // Overload TFile interfaces.
   Int_t    SysOpen(const char *pathname, Int_t flags, UInt_t mode);/// Open a file in 'MemFile'.
   Int_t    SysClose(Int_t fd);/// Close the mem file.
   Int_t    SysReadImpl(Int_t fd, void *buf, Long64_t len);
/// Read specified number of bytes from current offset into the buffer.
/// See documentation for TFile::SysRead().   
   
   Int_t    SysWriteImpl(Int_t fd, const void *buf, Long64_t len);/// Write a buffer into the file.
   Int_t    SysRead(Int_t fd, void *buf, Int_t len);
/// Read specified number of bytes from current offset into the buffer.
/// See documentation for TFile::SysRead().   
   
   Int_t    SysWrite(Int_t fd, const void *buf, Int_t len);/// Write a buffer into the file.
   Long64_t SysSeek(Int_t fd, Long64_t offset, Int_t whence);
/// Seek to a specified position in the file.  See TFile::SysSeek().
/// Note that TMemFile does not support seeks when the file is open for write.   
   
   Int_t    SysStat(Int_t fd, Long_t *id, Long64_t *size, Long_t *flags, Long_t *modtime);
/// Perform a stat on the HDFS file; see TFile::SysStat().   
   
   Int_t    SysSync(Int_t fd);
/// Sync remaining data to disk.
/// Nothing to do here.

   void ResetObjects(TDirectoryFile *, TFileMergeInfo *) const;
/// Wipe all the data from the permanent buffer but keep, the in-memory object
/// alive.

   TMemFile &operator=(const TMemFile&); // Not implemented.

public:
   TMemFile(const char *name, Option_t *option="", const char *ftitle="", Int_t compress=1);
/// Usual Constructor.  See the TFile constructor for details.   
   
   TMemFile(const char *name, char *buffer, Long64_t size, Option_t *option="", const char *ftitle="", Int_t compress=1);
/// Usual Constructor.  See the TFile constructor for details.   
   
   TMemFile(const TMemFile &orig);/// Copying the content of the TMemFile into another TMemFile.
   virtual ~TMemFile();/// Close and clean-up file.

   virtual Long64_t CopyTo(void *to, Long64_t maxsize) const;
/// Copy the binary representation of the TMemFile into
/// the memory area starting at 'to' and of length at most 'maxsize'
/// returns the number of bytes actually copied.

   virtual void     CopyTo(TBuffer &tobuf) const;
/// Copy the binary representation of the TMemFile into
/// the TBuffer tobuf   
   
   virtual Long64_t GetSize() const;/// Return the current size of the memory file

   void ResetAfterMerge(TFileMergeInfo *);
/// Wipe all the data from the permanent buffer but keep, the in-memory object
/// alive.   
   
   void ResetErrno() const;/// Simply calls TSystem::ResetErrno().

   virtual void        Print(Option_t *option="") const;
```



<!-- TMemFile.md ends here -->
