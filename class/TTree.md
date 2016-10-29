<!-- TTree.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 六 3月 14 08:35:28 2015 (+0800)
;; Last-Updated: 五 8月 12 22:24:05 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# TTree

## class

```cpp
virtual Long64_t        AutoSave(Option_t* option = "");
// AutoSave tree header every fAutoSave bytes.
//
//   When large Trees are produced, it is safe to activate the AutoSave
//   procedure. Some branches may have buffers holding many entries.
//   AutoSave is automatically called by TTree::Fill when the number of bytes
//   generated since the previous AutoSave is greater than fAutoSave bytes.
//   This function may also be invoked by the user, for example every
//   N entries.
//   Each AutoSave generates a new key on the file.
//   Once the key with the tree header has been written, the previous cycle
//   (if any) is deleted.
//
//   Note that calling TTree::AutoSave too frequently (or similarly calling
//   TTree::SetAutoSave with a small value) is an expensive operation.
//   You should make tests for your own application to find a compromise
//   between speed and the quantity of information you may loose in case of
//   a job crash.
//
//   In case your program crashes before closing the file holding this tree,
//   the file will be automatically recovered when you will connect the file
//   in UPDATE mode.
//   The Tree will be recovered at the status corresponding to the last AutoSave.
//
//   if option contains "SaveSelf", gDirectory->SaveSelf() is called.
//   This allows another process to analyze the Tree while the Tree is being filled.
//
//   if option contains "FlushBaskets", TTree::FlushBaskets is called and all
//   the current basket are closed-out and written to disk individually.
//
//   By default the previous header is deleted after having written the new header.
//   if option contains "Overwrite", the previous Tree header is deleted
//   before written the new header. This option is slightly faster, but
//   the default option is safer in case of a problem (disk quota exceeded)
//   when writing the new header.
//
//   The function returns the number of bytes written to the file.
//   if the number of bytes is null, an error has occurred while writing
//   the header to the file.


virtual Int_t           Fill();//填充到buffer中，一定数量之后写入硬盘
virtual Long64_t        GetEntries() const   { return fEntries; }//获取entry数

virtual Int_t           MakeSelector(const char* selector = 0);//生成要Process()的文件

virtual void            Reset(Option_t* option = "");// Reset baskets, buffers and entries count in all branches and leaves.

virtual Long64_t        Scan(const char* varexp = "", const char* selection = "", Option_t* option = "", Long64_t nentries = 1000000000, Long64_t firstentry = 0); // *MENU*
// Loop over tree entries and print entries passing selection.
//
// If varexp is 0 (or "") then print only first 8 columns.
// If varexp = "*" print all columns.
// Otherwise a columns selection can be made using "var1:var2:var3".
// See TTreePlayer::Scan for more information


virtual void            SetAutoSave(Long64_t autos = 300000000);
```

<!-- TTree.md ends here -->
