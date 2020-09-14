<!-- TFilePrefetch.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 日 1月  6 15:09:46 2019 (+0800)
;; Last-Updated: 日 1月  6 15:18:01 2019 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# TFilePrefetch

```
The prefetching mechanism uses two classes (TFilePrefetch and
TFPBlock) to prefetch in advance a block of tree entries. There is
a thread which takes care of actually transferring the blocks and
making them available to the main requesting thread. Therefore,
the time spent by the main thread waiting for the data before
processing considerably decreases. Besides the prefetching
mechanisms there is also a local caching option which can be
enabled by the user. Both capabilities are disabled by default
and must be explicitly enabled by the user.
```


```cpp
class TFilePrefetch : public TObject
```

## class

```cpp
private:
   TFile      *fFile;              // reference to the file
   TList      *fPendingBlocks;     // list of pending blocks to be read
   TList      *fReadBlocks;        // list of blocks read
   TThread    *fConsumer;          // consumer thread
   std::mutex fMutexPendingList;   // mutex for the pending list
   std::mutex fMutexReadList;      // mutex for the list of read blocks
   std::condition_variable fNewBlockAdded;  // signal the addition of a new pending block
   std::condition_variable fReadBlockAdded; // signal the addition of a new red block
   TSemaphore *fSemChangeFile;     // semaphore used when changin a file in TChain
   TString     fPathCache;         // path to the cache directory
   TStopwatch  fWaitTime;          // time wating to prefetch a buffer (in usec)
   Bool_t      fThreadJoined;      // mark if async thread was joined
   std::atomic<Bool_t> fPrefetchFinished;  // true if prefetching is over

   static TThread::VoidRtnFunc_t ThreadProc(void*);  //create a joinable worker thread
/// Execution loop of the consumer thread.

public:
   TFilePrefetch(TFile*);
   virtual ~TFilePrefetch();

   void      ReadAsync(TFPBlock*, Bool_t&);/// Read one block and insert it in prefetchBuffers list.
   void      ReadListOfBlocks();/// Get blocks specified in prefetchBlocks.

   void      AddPendingBlock(TFPBlock*);/// Safe method to add a block to the pendingList.
   TFPBlock *GetPendingBlock();/// Safe method to remove a block from the pendingList.

   void      AddReadBlock(TFPBlock*);/// Safe method to add a block to the readList.
   Bool_t    ReadBuffer(char*, Long64_t, Int_t);/// Return a prefetched element.
   void      ReadBlock(Long64_t*, Int_t*, Int_t);
/// Create a TFPBlock object or recycle one and add it to the prefetchBlocks list.   
   
   TFPBlock *CreateBlockObj(Long64_t*, Int_t*, Int_t);/// Create a new block or recycle an old one.

   TThread  *GetThread() const;/// Return reference to the consumer thread.
   Int_t     ThreadStart();/// Used to start the consumer thread.

   Bool_t    SetCache(const char*);/// Set the path of the cache directory.
   Bool_t    CheckBlockInCache(char*&, TFPBlock*);/// Test if the block is in cache.
   char     *GetBlockFromCache(const char*, Int_t);/// Return a buffer from cache.
   void      SaveBlockInCache(TFPBlock*);/// Save the block content in cache.

   Int_t     SumHex(const char*);/// Sum up individual hex values to obtain a decimal value.
   Bool_t    BinarySearchReadList(TFPBlock*, Long64_t, Int_t, Int_t*);
/// Search for a requested element in a block and return the index.   
   
   Long64_t  GetWaitTime();
/// Return the time spent wating for buffer to be read in microseconds.   

   void      SetFile(TFile*);
/// Change the file
/// When prefetching is enabled we also need to:
///  - make sure the async thread is not doing any work
///  - clear all blocks from prefetching and read list
///  - reset the file pointer   
   
   std::condition_variable &GetCondNewBlock() { return fNewBlockAdded; };
   void      WaitFinishPrefetch();/// Killing the async prefetching thread
   Bool_t    IsPrefetchFinished() const { return fPrefetchFinished; }

```

<!-- TFilePrefetch.md ends here -->
