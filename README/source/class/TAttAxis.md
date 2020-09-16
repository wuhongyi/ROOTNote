<!-- TAttAxis.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 9月 13 17:52:38 2016 (+0800)
;; Last-Updated: 三 9月 16 12:47:08 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 3
;; URL: http://wuhongyi.cn -->

# TAttAxis*

基类

## class

```cpp
   TAttAxis();
   virtual          ~TAttAxis();
   void     Copy(TAttAxis &attaxis) const;/// Copy of the object.
   virtual Int_t    GetNdivisions()  const {return fNdivisions;}
   virtual Color_t  GetAxisColor()   const {return fAxisColor;}
   virtual Color_t  GetLabelColor()  const {return fLabelColor;}
   virtual Style_t  GetLabelFont()   const {return fLabelFont;}
   virtual Float_t  GetLabelOffset() const {return fLabelOffset;}
   virtual Float_t  GetLabelSize()   const {return fLabelSize;}
   virtual Float_t  GetTitleOffset() const {return fTitleOffset;}
   virtual Float_t  GetTitleSize()   const {return fTitleSize;}
   virtual Float_t  GetTickLength()  const {return fTickLength;}
   virtual Color_t  GetTitleColor()  const {return fTitleColor;}
   virtual Style_t  GetTitleFont()   const {return fTitleFont;}
   virtual void     ResetAttAxis(Option_t *option="");/// Reset axis attributes
   virtual void     SaveAttributes(std::ostream &out, const char *name, const char *subname);/// Save axis attributes as C++ statement(s) on output stream out

/// Set the number of divisions for this axis.
///
///  - if optim = kTRUE (default), the number of divisions will be
///                     optimized around the specified value.
///  - if optim = kFALSE, or n < 0, the axis will be forced to use
///                     exactly n divisions.
/// n = n1 + 100*n2 + 10000*n3
/// Where n1 is the number of primary divisions,
/// n2 is the number of second order divisions and
/// n3 is the number of third order divisions.
/// If the number of divisions is "optimized" (see above) n1, n2, n3 are maximum values.
   virtual void     SetNdivisions(Int_t n=510, Bool_t optim=kTRUE);   // *MENU*
   virtual void     SetNdivisions(Int_t n1, Int_t n2, Int_t n3, Bool_t optim=kTRUE);
   virtual void     SetAxisColor(Color_t color=1, Float_t alpha=1.);  // *MENU* /// Set color of the line axis and tick marks
   virtual void     SetLabelColor(Color_t color=1, Float_t alpha=1.); // *MENU* /// Set color of labels
   virtual void     SetLabelFont(Style_t font=62);                    // *MENU* /// Set labels' font.

/// Set distance between the axis and the labels
/// The distance is expressed in per cent of the pad width
   virtual void     SetLabelOffset(Float_t offset=0.005);             // *MENU*
   virtual void     SetLabelSize(Float_t size=0.04);                  // *MENU* /// Set size of axis labels. The size is expressed in per cent of the pad width
   virtual void     SetTickLength(Float_t length=0.03);               // *MENU* /// Set tick mark length. The length is expressed in per cent of the pad width
   virtual void     SetTickSize(Float_t size=0.03) {SetTickLength(size);}

/// Set distance between the axis and the axis title
/// Offset is a correction factor with respect to the "standard" value.
///  - offset = 1   uses the default position that is computed in function
///                 of the label offset and size.
///  - offset = 1.2 will add 20 per cent more to the default offset.
   virtual void     SetTitleOffset(Float_t offset=1);                 // *MENU*
   virtual void     SetTitleSize(Float_t size=0.04);                  // *MENU* /// Set size of axis title. The size is expressed in per cent of the pad width
   virtual void     SetTitleColor(Color_t color=1);                   // *MENU* /// Set color of axis title
   virtual void     SetTitleFont(Style_t font=62);                    // *MENU* /// Set the title font.
```

## code




## example




<!-- TAttAxis.md ends here -->
