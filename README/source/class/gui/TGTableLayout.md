<!-- TGTableLayout.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 三 11月  9 15:24:48 2016 (+0800)
;; Last-Updated: 三 12月  7 20:06:50 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TGTableLayout

```cpp
//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TGTableLayout                                                        //
//                                                                      //
// A layout manager, which places child frames in a table arranged in   //
// rows and columns, making it easy to align many widgets next each to  //
// other horizontally and vertivally. It uses TGTableLayoutHints        //
// (not TGLayoutHints!!!) and works like TGMatrixLayout with the        //
// addition that:                                                       //
//  - Child frames can span more than one column/row.                   //
//  - Child frames can resize with the frame.                           //
//  - Column and row sizes are not fixed nor (optionally) homogeneous.  //
//  - The number of columns and rows must be fully specified in the     //
//    constructor.                                                      //
// The gaps between all rows or columns can be specified by 'sep'       //
// parameter in the constructor. All rows and columns will have the     //
// same size (set by widest and the highest child frame) if the         //
// parameter 'homogeneous' is set to kTRUE.                             //
//                                                                      //
//                                                                      //
// TGTableLayoutHints                                                   //
//                                                                      //
// This class describes layout hints used by the TGTableLayout class.   //
// It specifies the column/row division number on which to attach the   //
// child frame. This number starts from 0 and goes to #_columns/#_rows  //
// respectively (0 indicates the first row/column).                     //
//                                                                      //
// Below are described all parameters of TGTableLayoutHints constructor //
//     attach_left   - the column to the left of the widget;            //
//     attach_right  - the column to the right of the widget;           //
//     attach_top    - the row above the widget;                        //
//     attach_bottom - the row below the widget;                        //
//                                                                      //
//     hints - layout hints (combination of ELayoutHints)               //
//                                                                      //
// The next parameters determine the extra padding added around the     //
// child frame. By default these are 0.                                 //
//     padleft   - determines the extra padding added on the left       //
//     padright  - determines the extra padding added on the right      //
//     padtop    - determines the extra padding added on the top        //
//     padbottom - determines the extra padding added on the bottom     //
//                                                                      //
//////////////////////////////////////////////////////////////////////////
```

TGTableLayoutHints 继承 TGLayoutHints

TGTableLayout 继承 TGLayoutManager

## class

**TGTableLayoutHints**

```cpp
   TGTableLayoutHints(UInt_t attach_left, UInt_t attach_right,
                      UInt_t attach_top, UInt_t attach_bottom,
                      ULong_t hints = kLHintsNormal,
                      UInt_t padleft = 0, UInt_t padright = 0,
                      UInt_t padtop = 0, UInt_t padbottom = 0)
      : TGLayoutHints(hints,padleft,padright,padtop,padbottom),
         fAttachLeft(attach_left),
         fAttachRight(attach_right),
         fAttachTop(attach_top),
         fAttachBottom(attach_bottom) { }
   virtual ~TGTableLayoutHints() { }

   UInt_t GetAttachLeft() const { return fAttachLeft; }
   UInt_t GetAttachRight() const { return fAttachRight; }
   UInt_t GetAttachTop() const { return fAttachTop; }
   UInt_t GetAttachBottom() const { return fAttachBottom; }
   virtual void SavePrimitive(std::ostream &out, Option_t * = "");
```

**TGTableLayout**

```cpp
   // these are public in TGMatrixLayout ???  Perpetuate it.
   Int_t   fSep;               // interval between frames
   Int_t   fHints;             // layout hints (currently not used)
   UInt_t  fNrows;             // number of rows
   UInt_t  fNcols;             // number of columns

   TGTableLayout(TGCompositeFrame *main, UInt_t nrows, UInt_t ncols,
                 Bool_t homogeneous = kFALSE, Int_t sep = 0, Int_t hints = 0);
/// Note:
/// - Number of rows first, number of Columns second
/// - homogeneous == true means all table cells are the same size,
///   set by the widest and the highest child frame.
/// - s gives the amount of separation in pixels between cells
/// - h are the hints, see TGTableLayoutHints.

   virtual ~TGTableLayout();

   virtual void Layout();/// Make a table layout of all frames in the list.
   virtual TGDimension GetDefaultSize() const; // return sum of all child sizes
   virtual void SavePrimitive(std::ostream &out, Option_t * = "");
```


<!-- TGTableLayout.md ends here -->
