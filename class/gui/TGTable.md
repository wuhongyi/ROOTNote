<!-- TGTable.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  8 14:33:53 2016 (+0800)
;; Last-Updated: 二 11月  8 14:38:13 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# TGTable

TGTable 继承 TGCompositeFrame, TGWidget

A table used to visualize data from diffent sources.

## class

```cpp
   TGTable(const TGWindow *p = 0, Int_t id = 0,
           TVirtualTableInterface *interface = 0, UInt_t nrows = 50,
           UInt_t ncolumns = 20);
   virtual ~TGTable();

   virtual TObjArray *GetRow(UInt_t row);
   virtual TObjArray *GetColumn(UInt_t columns);

//    // Selection
//    virtual void Select(TGTableCell *celltl, TGTableCell *cellbr);
//    virtual void Select(UInt_t xcell1, UInt_t ycell1, UInt_t xcell2, UInt_t ycell2);
//    virtual void SelectAll();
//    virtual void SelectRow(TGTableCell *cell);
//    virtual void SelectRow(UInt_t row);
//    virtual void SelectRows(UInt_t row, UInt_t nrows);
//    virtual void SelectColumn(TGTableCell *cell);
//    virtual void SelectColumn(UInt_t column);
//    virtual void SelectColumns(UInt_t column, UInt_t ncolumns);

//    virtual void SetSelectGC(TGGC *gc);
//    virtual void SetTextJustify(Int_t tmode);

   // Cells
   virtual const TGTableCell* GetCell(UInt_t i, UInt_t j) const;
   virtual TGTableCell* GetCell(UInt_t i, UInt_t j);

   virtual const TGTableCell* FindCell(TGString label) const;
   virtual TGTableCell* FindCell(TGString label);

   virtual void Show();

   // Because insertion and removal of columns in the middle of a data
   // set is not yet supported in this design iteration, these methods
   // have been commented out.

//    // Insert a range of columns or rows, if the label is empty, a
//    // default scheme will be used.
//    virtual void InsertRowBefore(UInt_t row, UInt_t nrows);
//    virtual void InsertRowBefore(TGString label, UInt_t nrows);
//    virtual void InsertRowAfter(UInt_t row, UInt_t nrows);
//    virtual void InsertRowAfter(TGString label, UInt_t nrows);
//    virtual void InsertRowAt(UInt_t row, UInt_t nrows = 1);
//    virtual void InsertRowAt(TGString label, UInt_t nrows);

//    virtual void InsertColumnBefore(UInt_t column, UInt_t ncolumns);
//    virtual void InsertColumnBefore(TGString label, UInt_t ncolumns);
//    virtual void InsertColumnAfter(UInt_t column, UInt_t ncolumns);
//    virtual void InsertColumnAfter(TGString label, UInt_t ncolumns);
//    virtual void InsertColumnAt(UInt_t column, UInt_t ncolumns = 1);
//    virtual void InsertColumnAt(TGString label, UInt_t ncolumns);

//    // Remove rows or columns.
//    virtual void RemoveRows(UInt_t row, UInt_t nrows = 1);
//    virtual void RemoveColumns(UInt_t column, UInt_t ncolumns = 1);

   // Update view
   virtual void UpdateView();

   // Getters
   virtual UInt_t       GetNTableRows() const;
   virtual UInt_t       GetNDataRows() const;
   virtual UInt_t       GetNTableColumns() const;
   virtual UInt_t       GetNDataColumns() const;
   virtual UInt_t       GetNTableCells() const;
   virtual UInt_t       GetNDataCells() const;
   virtual const  TTableRange *GetCurrentRange() const;

   virtual TVirtualTableInterface *GetInterface() { return fInterface; }

   virtual TGCanvas                 *GetCanvas() { return fCanvas; }
   virtual const TGTableHeaderFrame *GetRHdrFrame() { return fRHdrFrame; }
   virtual const TGTableHeaderFrame *GetCHdrFrame() { return fCHdrFrame; }
   virtual const TGTableHeader      *GetRowHeader(const UInt_t row) const;
   virtual TGTableHeader            *GetRowHeader(const UInt_t row);
   virtual const TGTableHeader      *GetColumnHeader(const UInt_t column) const;
   virtual TGTableHeader            *GetColumnHeader(const UInt_t column);
   virtual TGTableHeader            *GetTableHeader();

//    virtual const TGGC*  GetSelectGC() const;
//    virtual const TGGC*  GetCellBckgndGC(TGTableCell *cell) const;
//    virtual const TGGC*  GetCellBckgndGC(UInt_t row, UInt_t column) const;

   virtual Pixel_t GetRowBackground(UInt_t row) const;
   virtual Pixel_t GetHeaderBackground() const ;

   virtual void SetOddRowBackground(Pixel_t pixel);
   virtual void SetEvenRowBackground(Pixel_t pixel);
   virtual void SetHeaderBackground(Pixel_t pixel);
   virtual void SetDefaultColors();

   // Range manipulators
   virtual void MoveTable(Int_t rows, Int_t columns);
   virtual void GotoTableRange(Int_t xtl, Int_t ytl,
                               Int_t xbr, Int_t ybr);
   // Operators
   virtual TGTableCell* operator() (UInt_t row, UInt_t column);

   // Internal slots
   virtual void ScrollCHeaders(Int_t xpos);
   virtual void ScrollRHeaders(Int_t ypos);
   virtual void NextChunk();
   virtual void PreviousChunk();
   virtual void UserRangeChange();
   virtual void Goto();
   virtual void Update();
```

## code


## example



<!-- TGTable.md ends here -->
