<!-- TFileCacheWrite.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 日 1月  6 15:35:49 2019 (+0800)
;; Last-Updated: 三 9月 16 10:31:18 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TFileCacheWrite*

```
A cache when writing files over the network

A caching system to speed up network I/O, i.e. when there is
no operating system caching support (like the buffer cache for
local disk I/O). The cache makes sure that every I/O is done with
a (large) fixed length buffer thereby avoiding many small I/O's.
Currently the write cache system is used by the classes TNetFile,
TXNetFile and TWebFile (via TFile::WriteBuffers()).

The write cache is automatically created when writing a remote file
(created in TFile::Open()).
```

```cpp
class TFileCacheWrite : public TObject 
```

## class

```cpp
protected:
   Long64_t      fSeekStart;      ///< Seek value of first block in cache
   Int_t         fBufferSize;     ///< Allocated size of fBuffer
   Int_t         fNtot;           ///< Total size of cached blocks
   TFile        *fFile;           ///< Pointer to file
   char         *fBuffer;         ///< [fBufferSize] buffer of contiguous prefetched blocks
   Bool_t        fRecursive;      ///< flag to avoid recursive calls

private:
   TFileCacheWrite(const TFileCacheWrite &);            //cannot be copied
   TFileCacheWrite& operator=(const TFileCacheWrite &);

public:
   TFileCacheWrite();
   TFileCacheWrite(TFile *file, Int_t buffersize);
/// Creates a TFileCacheWrite data structure.
/// The write cache will be connected to file.
/// The size of the cache will be buffersize,
/// if buffersize < 10000 a default size of 512 Kbytes is used   
   
   virtual ~TFileCacheWrite();
   virtual Bool_t      Flush();
/// Flush the current write buffer to the file.
/// Returns kTRUE in case of error.

   virtual Int_t       GetBytesInCache() const { return fNtot; }
   virtual void        Print(Option_t *option="") const;/// Print class internal structure.
   virtual Int_t       ReadBuffer(char *buf, Long64_t pos, Int_t len);
/// Called by the read cache to check if the requested data is not
/// in the write cache buffer.
///        Returns -1 if data not in write cache,
///        0 otherwise.   
   
   virtual Int_t       WriteBuffer(const char *buf, Long64_t pos, Int_t len);
/// Write buffer at position pos in the write buffer.
/// The function returns 1 if the buffer has been successfully entered into the write buffer.
/// The function returns 0 in case WriteBuffer() was recusively called via Flush().
/// The function returns -1 in case of error.   
   
   virtual void        SetFile(TFile *file);
/// Set the file using this cache.
/// Any write not yet flushed will be lost.   
```


<!-- TFileCacheWrite.md ends here -->
