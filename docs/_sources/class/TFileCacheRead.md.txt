<!-- TFileCacheRead.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 日 1月  6 15:39:41 2019 (+0800)
;; Last-Updated: 三 9月 16 10:31:14 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TFileCacheRead*

```
 A cache when reading files over the network.

 A caching system to speed up network I/O, i.e. when there is
 no operating system caching support (like the buffer cache for
 local disk I/O). The cache makes sure that every I/O is done with
 a (large) fixed length buffer thereby avoiding many small I/O's.
 Currently the read cache system is used by the classes TNetFile,
 TXNetFile and TWebFile (via TFile::ReadBuffers()).
 When processing TTree, TChain, a specialized class TTreeCache that
 derives from this class is automatically created.
```

```cpp
class TFileCacheRead : public TObject
```

## class

```cpp
protected:
   TFilePrefetch *fPrefetch;         ///<! Object that does the asynchronous reading in another thread
   Int_t          fBufferSizeMin;    ///< Original size of fBuffer
   Int_t          fBufferSize;       ///< Allocated size of fBuffer (at a given time)
   Int_t          fBufferLen;        ///< Current buffer length (<= fBufferSize)

   Long64_t       fBytesRead;        ///< Number of bytes read for this cache
   Long64_t       fBytesReadExtra;   ///< Number of extra bytes (overhead) read by the readahead buffer
   Int_t          fReadCalls;        ///< Number of read calls for this cache
   Long64_t       fNoCacheBytesRead; ///< Number of bytes read by basket to fill cached tree
   Int_t          fNoCacheReadCalls; ///< Number of read calls by basket to fill cached tree

   Bool_t         fAsyncReading;
   Bool_t         fEnablePrefetching;///< reading by prefetching asynchronously

   Int_t          fNseek;            ///< Number of blocks to be prefetched
   Int_t          fNtot;             ///< Total size of prefetched blocks
   Int_t          fNb;               ///< Number of long buffers
   Int_t          fSeekSize;         ///< Allocated size of fSeek
   Long64_t      *fSeek;             ///<[fNseek] Position on file of buffers to be prefetched
   Long64_t      *fSeekSort;         ///<[fNseek] Position on file of buffers to be prefetched (sorted)
   Int_t         *fSeekIndex;        ///<[fNseek] sorted index table of fSeek
   Long64_t      *fPos;              ///<[fNb] start of long buffers
   Int_t         *fSeekLen;          ///<[fNseek] Length of buffers to be prefetched
   Int_t         *fSeekSortLen;      ///<[fNseek] Length of buffers to be prefetched (sorted)
   Int_t         *fSeekPos;          ///<[fNseek] Position of sorted blocks in fBuffer
   Int_t         *fLen;              ///<[fNb] Length of long buffers
   TFile         *fFile;             ///< Pointer to file
   char          *fBuffer;           ///<[fBufferSize] buffer of contiguous prefetched blocks
   Bool_t         fIsSorted;         ///< True if fSeek array is sorted
   Bool_t         fIsTransferred;    ///< True when fBuffer contains something valid
   Long64_t       fPrefetchedBlocks; ///< Number of blocks prefetched.

   //variables for the second block prefetched with the same semantics as for the first one
   Int_t          fBNseek;
   Int_t          fBNtot;
   Int_t          fBNb;
   Int_t          fBSeekSize;
   Long64_t      *fBSeek;        ///<[fBNseek]
   Long64_t      *fBSeekSort;    ///<[fBNseek]
   Int_t         *fBSeekIndex;   ///<[fBNseek]
   Long64_t      *fBPos;         ///<[fBNb]
   Int_t         *fBSeekLen;     ///<[fBNseek]
   Int_t         *fBSeekSortLen; ///<[fBNseek]
   Int_t         *fBSeekPos;     ///<[fBNseek]
   Int_t         *fBLen;         ///<[fBNb]
   Bool_t         fBIsSorted;
   Bool_t         fBIsTransferred;

   void SetEnablePrefetchingImpl(Bool_t setPrefetching = kFALSE); // Can not be virtual as it is called from the constructor.
/// TFileCacheRead implementation of SetEnablePrefetching.
/// This function is called from the constructor and should not be virtual.

private:
   TFileCacheRead(const TFileCacheRead &);            //cannot be copied
   TFileCacheRead& operator=(const TFileCacheRead &);

public:
   TFileCacheRead();
   TFileCacheRead(TFile *file, Int_t buffersize, TObject *tree = 0);/// Creates a TFileCacheRead data structure.
   virtual ~TFileCacheRead();
   virtual Int_t       AddBranch(TBranch * /*b*/, Bool_t /*subbranches*/ = kFALSE) { return 0; }
   virtual Int_t       AddBranch(const char * /*branch*/, Bool_t /*subbranches*/ = kFALSE) { return 0; }
   virtual void        AddNoCacheBytesRead(Long64_t len) { fNoCacheBytesRead += len; }
   virtual void        AddNoCacheReadCalls(Int_t reads) { fNoCacheReadCalls += reads; }
   virtual void        Close(Option_t *option="");
/// Close out any threads or asynchronous fetches used by the underlying
/// implementation.
/// This is called by TFile::Close to prevent usage of the file handles
/// after the closing of the file.   
   
   virtual Int_t       GetBufferSize() const { return fBufferSize; };
   virtual Long64_t    GetBytesRead() const { return fBytesRead; }
   virtual Long64_t    GetNoCacheBytesRead() const { return fNoCacheBytesRead; }
   virtual Long64_t    GetBytesReadExtra() const { return fBytesReadExtra; }
           TFile      *GetFile() const { return fFile; }   // Return the TFile being cached.
           Int_t       GetNseek() const { return fNseek; } // Return the number of blocks in the current cache.
           Int_t       GetNtot() const { return fNtot; }   // Return the total size of the prefetched blocks.
   virtual Int_t       GetReadCalls() const { return fReadCalls; }
   virtual Int_t       GetNoCacheReadCalls() const { return fNoCacheReadCalls; }
   virtual Int_t       GetUnzipBuffer(char ** /*buf*/, Long64_t /*pos*/, Int_t /*len*/, Bool_t * /*free*/) { return -1; }
           Long64_t    GetPrefetchedBlocks() const { return fPrefetchedBlocks; }
   virtual Bool_t      IsAsyncReading() const { return fAsyncReading; };
   virtual void        SetEnablePrefetching(Bool_t setPrefetching = kFALSE);
/// Set the prefetching mode of this file.
/// If 'setPrefetching', enable the asynchronous prefetching
/// (using TFilePrefetch) and if the gEnv and rootrc
/// variable Cache.Directory is set, also enable the local
/// caching of the prefetched blocks.
/// if 'setPrefetching', the old prefetcher is enabled is
/// the gEnv and rootrc variable is TFile.AsyncReading   
   
   virtual Bool_t      IsEnablePrefetching() const { return fEnablePrefetching; };
   virtual Bool_t      IsLearning() const {return kFALSE;}
   virtual void        Prefetch(Long64_t pos, Int_t len);
/// Add block of length len at position pos in the list of blocks to
/// be prefetched. If pos <= 0 the current blocks (if any) are reset.   
   
   virtual void        Print(Option_t *option="") const;
/// Print cache statistics.
/// The format is:
///     ******TreeCache statistics for file: cms2.root ******
///     Reading............................: 72761843 bytes in 7 transactions
///     Readahead..........................: 256000 bytes with overhead = 0 bytes
///     Average transaction................: 10394.549000 Kbytes
///     Number of blocks in current cache..: 210, total size: 6280352
/// If option = "a" the list of blocks in the cache is printed
/// NB: this function is automatically called by TTreeCache::Print   
   
   virtual Int_t       ReadBufferExt(char *buf, Long64_t pos, Int_t len, Int_t &loc);
   virtual Int_t       ReadBufferExtNormal(char *buf, Long64_t pos, Int_t len, Int_t &loc);
/// Base function for ReadBuffer.
/// Also gives out the position of the block in the internal buffer.
/// This helps TTreeCacheUnzip to avoid doing twice the binary search.   
   
   virtual Int_t       ReadBufferExtPrefetch(char *buf, Long64_t pos, Int_t len, Int_t &loc);
///prefetch the first block   
   
   virtual Int_t       ReadBuffer(char *buf, Long64_t pos, Int_t len);
/// Read buffer at position pos.
/// If pos is in the list of prefetched blocks read from fBuffer,
/// otherwise need to make a normal read from file. Returns -1 in case of
/// read error, 0 in case not in cache, 1 in case read from cache.   
   
   virtual Int_t       SetBufferSize(Int_t buffersize);
/// Sets the buffer size.
/// If the current prefetch list is too large to fit in
/// the new buffer some or all of the prefetch blocks are dropped. The
/// requested buffersize must be greater than zero.
/// Return values:
///   - 0 if the prefetch block lists remain unchanged
///   - 1 if some or all blocks have been removed from the prefetch list
///   - -1 on error   
   
   virtual void        SetFile(TFile *file, TFile::ECacheAction action = TFile::kDisconnect);
/// Set the file using this cache and reset the current blocks (if any).   
   
   virtual void        SetSkipZip(Bool_t /*skip*/ = kTRUE) {} // This function is only used by TTreeCacheUnzip (ignore it)
   virtual void        Sort();
/// Sort buffers to be prefetched in increasing order of positions.
/// Merge consecutive blocks if necessary.   
   
   virtual void        SecondSort();                          //Method used to sort and merge the chunks in the second block
/// Sort buffers to be prefetched in increasing order of positions.
/// Merge consecutive blocks if necessary.   
   
   virtual void        SecondPrefetch(Long64_t, Int_t);       //Used to add chunks to the second block
   virtual TFilePrefetch* GetPrefetchObj();
   virtual void        WaitFinishPrefetch();                  //Gracefully join the prefetching thread

```

<!-- TFileCacheRead.md ends here -->
