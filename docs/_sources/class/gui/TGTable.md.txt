<!-- TGTable.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  8 14:33:53 2016 (+0800)
;; Last-Updated: 三 9月 16 11:15:32 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 3
;; URL: http://wuhongyi.cn -->

# TGTable*

TGTable 继承 TGCompositeFrame, TGWidget

A table used to visualize data from diffent sources.

TGTable implements a table widget to display data in rows and  
columns. The data is supplied by a TVirtualTableInterface.

The table is a TGCanvas to make use of already available viewport
functionality and drawing optimizations.

The top left cell in a table has coordinates (0,0)

A TObjArray is used internally to ensure little overhead and fast
acces to cells.

If the data source has more rows than the default 50 rows of cells in
memory, buttons at the bottom of the table can be used to load the
next or previous chunk of data.

At the top of the table, a frame is visible that shows the coordinates
of the top left cell currently in memmory in row,column. The amount of
rows and columns is also shown in rows x columns. These values can be
edited to move to a different area of the data source or to resize the
table. Tab will switch between the enties, return will move to the
currently entered range and resize the table if needed. Clicking the
goto button has the same effect.

A TGTable is created by first creating an appropriate
TVirtualTableInterface from the data that needs visualization and
then creating the TGTable using this interface.

## class

```cpp
   TGTable(const TGWindow *p = 0, Int_t id = 0,
           TVirtualTableInterface *interface = 0, UInt_t nrows = 50,
           UInt_t ncolumns = 20);
   virtual ~TGTable();

   virtual TObjArray *GetRow(UInt_t row);
/// Get row. NOTE: Do not delete the TObjArray returned or the cells
/// it contains, they are owned by the TGTable.

   virtual TObjArray *GetColumn(UInt_t columns);
/// Return a pointer to a TObjArray that contains pointers to all
/// the cells in column. NOTE: The user will have to delete the
/// TObjArray, but do NOT delete the cells it contains, they are
/// owned by the TGTable and will be deleted from the TGTable with
/// undefined consequenses.

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
   virtual const TGTableCell* GetCell(UInt_t i, UInt_t j) const;/// Const version of GetCell().
   virtual TGTableCell* GetCell(UInt_t i, UInt_t j);/// Return a pointer to the TGTableCell at position i,j.

   virtual const TGTableCell* FindCell(TGString label) const;/// Const version of FindCell().
   virtual TGTableCell* FindCell(TGString label);/// Find the TGTableCell with label.

   virtual void Show();/// Show the contents of the TGTable in stdout.

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
   virtual void UpdateView();/// Update and layout the visible part of the TGTable.

   // Getters
   virtual UInt_t       GetNTableRows() const;/// Return the amount of rows in the table.
   virtual UInt_t       GetNDataRows() const;/// Return the amount of rows in the data source.
   virtual UInt_t       GetNTableColumns() const;/// Return the amount of columns in the table.
   virtual UInt_t       GetNDataColumns() const;/// Return the amount of columns in the data source.
   virtual UInt_t       GetNTableCells() const;/// Return the amount of cells in the table.
   virtual UInt_t       GetNDataCells() const;/// Return the amount of cell in the data source.
   virtual const  TTableRange *GetCurrentRange() const;/// Return the current range of the TGTable.

   virtual TVirtualTableInterface *GetInterface() { return fInterface; }

   virtual TGCanvas                 *GetCanvas() { return fCanvas; }
   virtual const TGTableHeaderFrame *GetRHdrFrame() { return fRHdrFrame; }
   virtual const TGTableHeaderFrame *GetCHdrFrame() { return fCHdrFrame; }
   virtual const TGTableHeader      *GetRowHeader(const UInt_t row) const;
/// Const version of GetRowHeader();

   virtual TGTableHeader            *GetRowHeader(const UInt_t row);
/// Return a pointer to the header of row.

   virtual const TGTableHeader      *GetColumnHeader(const UInt_t column) const;
/// Const version of GetColumnHeader();

   virtual TGTableHeader            *GetColumnHeader(const UInt_t column);
/// Return a pointer to the header of column.

   virtual TGTableHeader            *GetTableHeader();

//    virtual const TGGC*  GetSelectGC() const;
//    virtual const TGGC*  GetCellBckgndGC(TGTableCell *cell) const;
//    virtual const TGGC*  GetCellBckgndGC(UInt_t row, UInt_t column) const;

   virtual Pixel_t GetRowBackground(UInt_t row) const;/// Get the background collor for row.
   virtual Pixel_t GetHeaderBackground() const ;/// Get the background color of headers.

   virtual void SetOddRowBackground(Pixel_t pixel);/// Set the background color for all odd numbered rows.
   virtual void SetEvenRowBackground(Pixel_t pixel);/// Set the background color for all even numbered rows.
   virtual void SetHeaderBackground(Pixel_t pixel);/// Set the background color for the headers.
   virtual void SetDefaultColors();
/// Set the background color for all rows and headers to their defaults.

   // Range manipulators
   virtual void MoveTable(Int_t rows, Int_t columns);/// Move and layout the table to the specified range.
   virtual void GotoTableRange(Int_t xtl, Int_t ytl,
                               Int_t xbr, Int_t ybr);
/// Move and resize the table to the specified range.

   // Operators
   virtual TGTableCell* operator() (UInt_t row, UInt_t column);

   // Internal slots
   virtual void ScrollCHeaders(Int_t xpos);/// Scroll the column headers horizontally.
   virtual void ScrollRHeaders(Int_t ypos);/// Scroll the row headers vertically
   virtual void NextChunk();
/// Move the table to the next chunk of the data set with the same size.

   virtual void PreviousChunk();
/// Move the table to the previous chunk of the data set with the same size.

   virtual void UserRangeChange();
/// Slot used when the text in one of the range frame text entries changes.

   virtual void Goto();
/// Slot used by the Goto button and whenever return is pressed in
/// on of the text entries in the range frame.

   virtual void Update();
/// Update the range of the available data and refresh the current view.   
```

## code

```cpp
// A simple macro to use a TGTable with a TGSimpleTableInterface:

   Int_t i = 0, j = 0;
   UInt_t nrows = 6, ncolumns = 5;
   Double_t** data = new Double_t*[nrows];
   for (i = 0; i < nrows; i++) {
      data[i] = new Double_t[ncolumns];
      for (j = 0; j < ncolumns; j++) {
         data[i][j] = 10 * i + j;
      }
   }

   // Create a main frame to contain the table
   TGMainFrame* mainframe = new TGMainFrame(0, 400, 200);
   mainframe->SetCleanup(kDeepCleanup) ;

   // Create an interface
   TGSimpleTableInterface *iface = new TGSimpleTableInterface(data, 6, 5);

   // Create the table
   TGTable *table = new TGTable(mainframe, 999, iface);

   // Add the table to the main frame
   mainframe->AddFrame(table, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

   //Update data
   data[5][1] = 3.01;
   //update the table view
   table->Update();

   // Layout and map the main frame
   mainframe->SetWindowName("Tree Table Test") ;
   mainframe->MapSubwindows() ;
   mainframe->Layout();
   mainframe->Resize() ;
   mainframe->MapWindow() ;

   return mainframe;
```


```cpp
// It is also possible to visualise data from a tree. A simple macro
// showing the use of a TTreeTableInterface follows.

   // Open a root file.
   TFile *file = new TFile("$ROOTSYS/tutorials/hsimple.root");
   // Load a tree from the file
   TNtuple *ntuple = (TNtuple *)file->Get("ntuple");

   // Create an interface
   TTreeTableInterface *iface = new TTreeTableInterface(ntuple);

   // Create a main frame to contain the table
   TGMainFrame* mainframe = new TGMainFrame(0, 400, 200);
   mainframe->SetCleanup(kDeepCleanup) ;

   // Create the table
   TGTable *table = new TGTable(mainframe, 999, iface, 10, 6);

   // Add the table to the main frame
   mainframe->AddFrame(table, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY));

   // Set a selection
   iface->SetSelection("px > 0.");
   // Add a column
   iface->AddColumn("(px+py)/(px-py)", 0);
   //update the table view
   table->Update();

   // Layout and map the main frame
   mainframe->SetWindowName("Tree Table Test") ;
   mainframe->MapSubwindows() ;
   mainframe->Layout();
   mainframe->Resize() ;
   mainframe->MapWindow() ;

   return mainframe;
```


## example



<!-- TGTable.md ends here -->
