<!-- TGSimpleTable.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  8 14:30:51 2016 (+0800)
;; Last-Updated: 三 9月 16 11:11:52 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 3
;; URL: http://wuhongyi.cn -->

# TGSimpleTable+

TGSimpleTable 继承 TGTable

A simple table that owns it's interface.

## class

```cpp
   TGSimpleTable(TGWindow *p, Int_t id, Double_t **data,
                 UInt_t nrows, UInt_t ncolumns);
   virtual ~TGSimpleTable();
```

## code

```cpp
#include "TGSimpleTable.h"

// TGSimpleTable
// 简单数据表格
Double_t     **fData;
UInt_t         fNDataRows;
UInt_t         fNDataColumns;
UInt_t         fNTableRows;
UInt_t         fNTableColumns;
TGSimpleTable *fSimpleTable;
Int_t i = 0, j = 0;
fData = new Double_t*[fNDataRows];// Create the needed data.
for (i = 0; i < (Int_t)fNDataRows; i++) {
   fData[i] = new Double_t[fNDataColumns];
   for (j = 0; j < (Int_t)fNDataColumns; j++) {
      fData[i][j] = 10 * i + j;
   }
}
fSimpleTable = new TGSimpleTable(frame, IDs, fData, fNTableRows, fNTableColumns);
frame->AddFrame(fSimpleTable, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));
```

## example



<!-- TGSimpleTable.md ends here -->
