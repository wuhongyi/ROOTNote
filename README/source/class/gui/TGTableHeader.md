<!-- TGTableHeader.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 三 11月  9 15:25:06 2016 (+0800)
;; Last-Updated: 三 9月 16 11:15:52 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 3
;; URL: http://wuhongyi.cn -->

# TGTableHeader-

TGTableHeader is the class that implements a header for a row or     
column. Interactivity on a per column or row basis is implemented    
using this header.                                                   

TGTableHeader is for internal use in TGTable only.

TGTableHeader 继承 TGTableCell


## class

```cpp
   TGTableHeader(const TGWindow *p = 0, TGTable *table = 0,
                 TGString *label = 0, UInt_t position = 0,
                 EHeaderType type = kColumnHeader, UInt_t width = 80,
                 UInt_t height = 25, GContext_t norm = GetDefaultGC()(),
                 FontStruct_t font = GetDefaultFontStruct(),
                 UInt_t option = 0);
   TGTableHeader(const TGWindow *p, TGTable *table, const char *label,
                 UInt_t position, EHeaderType type = kColumnHeader,
                 UInt_t width = 80, UInt_t height = 25,
                 GContext_t norm = GetDefaultGC()(),
                 FontStruct_t font = GetDefaultFontStruct(),
                 UInt_t option = 0);
   virtual ~TGTableHeader();

   virtual void SetWidth(UInt_t width);/// Resize the TGTableHeader.
   virtual void SetHeight(UInt_t height);/// Resize the TGTableHeader.

   virtual void SetLabel(const char *label);/// Set the label of the TGTableHeader to label.

   virtual void SetDefaultLabel();/// Set the label of the TGTableHeader to the default label, "Row #" or "Col #".
   virtual void SetPosition(UInt_t pos);/// Set the position of the TGTableHeader to pos.
   virtual void Resize(UInt_t width, UInt_t height);  // Resize width or height
   virtual void Resize(TGDimension newsize);          // depending on type
   virtual void Sort(Bool_t order = kSortAscending);/// Sort the contents of this row or column in given order.
   virtual void UpdatePosition();/// Update the positon of the TGTableHeader.

   virtual EHeaderType GetType() { return fType; }
```


<!-- TGTableHeader.md ends here -->
