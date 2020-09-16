<!-- TGTableCell.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 三 11月  9 15:25:47 2016 (+0800)
;; Last-Updated: 三 9月 16 11:15:40 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 3
;; URL: http://wuhongyi.cn -->

# TGTableCell-

TGTableCell is the class that represents a single cell in a TGTable.  This class is for internal use in TGTable only.

TGTableCell 继承 TGFrame ，friend TGTable


## class

```cpp
   static FontStruct_t GetDefaultFontStruct();/// Return default font structure.
   static const TGGC   &GetDefaultGC();/// Return default graphics context.

   TGTableCell(const TGWindow *p = 0, TGTable *table = 0, TGString *label = 0,
               UInt_t row = 0, UInt_t column = 0, UInt_t width = 80,
               UInt_t height = 25, GContext_t norm = GetDefaultGC()(),
               FontStruct_t font = GetDefaultFontStruct(), UInt_t option = 0,
               Bool_t resize = kTRUE);
   TGTableCell(const TGWindow *p, TGTable *table, const char *label,
               UInt_t row = 0, UInt_t column = 0, UInt_t width = 80,
               UInt_t height = 25, GContext_t norm = GetDefaultGC()(),
               FontStruct_t font = GetDefaultFontStruct(),
               UInt_t option = 0, Bool_t resize =  kTRUE);
//    TGTableCell(const TGWindow *p, TGTable *table, TGPicture *image,
//                TGString *label,  UInt_t row, UInt_t column,
//                UInt_t width, UInt_t height, GContext_t norm = GetDefaultGC()(),
//                FontStruct_t font = GetDefaultFontStruct(),
//                UInt_t option = 0, Bool_t resize = kTRUE);
//    TGTableCell(const TGWindow *p, TGTable *table, TGPicture *image,
//                const char *label, UInt_t row, UInt_t column, UInt_t width,
//                UInt_t height, GContext_t norm = GetDefaultGC()(),
//                FontStruct_t font = GetDefaultFontStruct(),
//                UInt_t option = 0, Bool_t resize = kTRUE);
   virtual ~TGTableCell();

   virtual void DrawCopy(Handle_t id, Int_t x, Int_t y);
/// Draw list view item in other window.
/// List view item is placed and layout in the container frame,
/// but is drawn in viewport.

   virtual void SetLabel(const char *label);/// Set the label of this cell to label.

   virtual void SetImage(TGPicture *image);/// Set the image that this cell contains to image.
   //   virtual void SetBckgndGC(TGGC *gc);

   virtual void SetTextJustify(Int_t tmode);/// Set the text justify mode of the cell to mode.
   virtual void SetFont(FontStruct_t font);
/// Changes text font.
/// If global is kTRUE font is changed globally, otherwise - locally.

   virtual void SetFont(const char *fontName);
/// Changes text font specified by name.
/// If global is true color is changed globally, otherwise - locally.

   virtual void Select();
   virtual void SelectRow();
   virtual void SelectColumn();

   virtual UInt_t      GetColumn() const { return fColumn; }
   virtual UInt_t      GetRow() const { return fRow; };
   virtual TGString*   GetLabel() const { return fLabel; }
   virtual TGPicture*  GetImage() const { return fImage; }
   virtual UInt_t      GetWidth() const { return fWidth; }
   virtual UInt_t      GetHeight() const {return fHeight; }
   virtual TGDimension GetSize() const { return TGDimension(fWidth, fHeight); }
   virtual Int_t       GetTextJustify() const { return fTMode; }
```

## code



## example




<!-- TGTableCell.md ends here -->
