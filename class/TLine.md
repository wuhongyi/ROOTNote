<!-- TLine.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 一 10月 31 23:23:26 2016 (+0800)
;; Last-Updated: 一 10月 31 23:32:10 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# TLine

继承 TObject, TAttLine, TAttBBox2D

## class

```cpp
   // TLine status bits
   enum {
      kLineNDC    = BIT(14), // Use NDC coordinates
      kVertical   = BIT(15), // Line is vertical
      kHorizontal = BIT(16)  // Line is horizontal
   };

   TLine();/// Line default constructor.
   TLine(Double_t x1, Double_t y1,Double_t x2, Double_t  y2);/// Line normal constructor.
   TLine(const TLine &line);/// Line copy constructor.
   virtual ~TLine();

   void                 Copy(TObject &line) const;/// Copy this line to line.
   virtual Int_t        DistancetoPrimitive(Int_t px, Int_t py);/// Compute distance from point px,py to a line.
   virtual TLine       *DrawLine(Double_t x1, Double_t y1,Double_t x2, Double_t y2);/// Draw this line with new coordinates.
   virtual TLine       *DrawLineNDC(Double_t x1, Double_t y1,Double_t x2, Double_t y2);/// Draw this line with new coordinates in NDC.
   virtual void         ExecuteEvent(Int_t event, Int_t px, Int_t py);
/// Execute action corresponding to one event.
///  This member function is called when a line is clicked with the locator
///  If Left button clicked on one of the line end points, this point
///     follows the cursor until button is released.
///  if Middle button clicked, the line is moved parallel to itself
///     until the button is released.

   Double_t             GetX1() const {return fX1;}
   Double_t             GetX2() const {return fX2;}
   Double_t             GetY1() const {return fY1;}
   Double_t             GetY2() const {return fY2;}
   Bool_t               IsHorizontal();/// Check whether this line is to be drawn horizontally.
   Bool_t               IsVertical();/// Check whether this line is to be drawn vertically.
   virtual void         ls(Option_t *option="") const;/// List this line with its attributes.
   virtual void         Paint(Option_t *option="");/// Paint this line with its current attributes.
   virtual void         PaintLine(Double_t x1, Double_t y1,Double_t x2, Double_t  y2);/// Draw this line with new coordinates.
   virtual void         PaintLineNDC(Double_t u1, Double_t v1,Double_t u2, Double_t  v2);/// Draw this line with new coordinates in NDC.
   virtual void         Print(Option_t *option="") const;
   virtual void         SavePrimitive(std::ostream &out, Option_t *option = "");/// Save primitive as a C++ statement(s) on output stream out
   virtual void         SetNDC(Bool_t isNDC=kTRUE);/// Set NDC mode on if isNDC = kTRUE, off otherwise
   void                 SetHorizontal(Bool_t set = kTRUE); // *TOGGLE* *GETTER=IsHorizontal
/// Force the line to be drawn horizontally.
/// Makes fY2 equal to fY1. The line length is kept.
/// TArrow and TGaxis also get this function by inheritance.

   void                 SetVertical(Bool_t set = kTRUE); // *TOGGLE* *GETTER=IsVertical
/// Force the line to be drawn vertically.
/// Makes fX2 equal to fX1. The line length is kept.
/// TArrow and TGaxis also get this function by inheritance.

   virtual void         SetX1(Double_t x1) {fX1=x1;}
   virtual void         SetX2(Double_t x2) {fX2=x2;}
   virtual void         SetY1(Double_t y1) {fY1=y1;}
   virtual void         SetY2(Double_t y2) {fY2=y2;}
   virtual Rectangle_t  GetBBox();/// Return the bounding Box of the Line
   virtual TPoint       GetBBoxCenter();/// Return the center of the BoundingBox as TPoint in pixels
   virtual void         SetBBoxCenter(const TPoint &p);/// Set center of the BoundingBox
   virtual void         SetBBoxCenterX(const Int_t x);/// Set X coordinate of the center of the BoundingBox
   virtual void         SetBBoxCenterY(const Int_t y);/// Set Y coordinate of the center of the BoundingBox
   virtual void         SetBBoxX1(const Int_t x);
/// Set left hand side of BoundingBox to a value
/// (resize in x direction on left)

   virtual void         SetBBoxX2(const Int_t x);
/// Set right hand side of BoundingBox to a value
/// (resize in x direction on right)

   virtual void         SetBBoxY1(const Int_t y);
/// Set top of BoundingBox to a value (resize in y direction on top)

   virtual void         SetBBoxY2(const Int_t y);
/// Set bottom of BoundingBox to a value
/// (resize in y direction on bottom)
```

## code


## example


<!-- TLine.md ends here -->
