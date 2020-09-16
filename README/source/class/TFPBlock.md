<!-- TFPBlock.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 日 1月  6 15:19:12 2019 (+0800)
;; Last-Updated: 三 9月 16 10:33:29 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TFPBlock*

```
This class represents the encapsulation of a block request.
It contains the chunks to be prefetched and also serves as a
container for the information read.
These blocks are prefetch in a special reader thread by the
TFilePrefetch class.
```


```cpp
class TFPBlock : public TObject
```

## class

```cpp
private:
   char     *fBuffer;       ///< Content of the block
   Int_t     fNblock;       ///< Number of segment in the block
   Long64_t  fDataSize;     ///< Total size of useful data in the block
   Long64_t  fCapacity;     ///< Capacity of the buffer
   Int_t    *fLen;          ///< Array of lengths of each segment
   Long64_t *fPos;          ///< Array of positions of each segment
   Long64_t *fRelOffset;    ///< Relative offset of piece in the buffer

   TFPBlock(const TFPBlock&);            // Not implemented.
   TFPBlock &operator=(const TFPBlock&); // Not implemented.

public:

   TFPBlock(Long64_t*, Int_t*, Int_t);
   virtual ~TFPBlock();

   Long64_t  GetPos(Int_t) const;
   Int_t     GetLen(Int_t) const;

   Long64_t *GetPos() const;
   Int_t    *GetLen() const;
   Long64_t  GetDataSize() const;
   Long64_t  GetCapacity() const;
   Int_t     GetNoElem() const;
   char     *GetBuffer() const;
   char     *GetPtrToPiece(Int_t index) const;

   void SetBuffer(char*);/// Set block buffer.
   void SetPos(Int_t, Long64_t);/// Set pos value for index idx.
   void ReallocBlock(Long64_t*, Int_t*, Int_t);
/// Reallocate the block's buffer based on the length
/// of the elements it will contain.
```

<!-- TFPBlock.md ends here -->
