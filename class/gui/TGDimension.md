<!-- TGDimension.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 1月 27 21:49:05 2017 (+0800)
;; Last-Updated: 五 1月 27 21:53:46 2017 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# TGDimension

TGDimension, TGPosition, TGLongPosition, TGInsets and TGRectangle    
                                                                    
Several small geometry classes that implement dimensions             
(width and height), positions (x and y), insets and rectangles.      
They are trivial and their members are public.  


## class

**TGDimension**

```cpp
   UInt_t  fWidth;       // width
   UInt_t  fHeight;      // height

   TGDimension(): fWidth(0), fHeight(0) { }
   TGDimension(UInt_t width, UInt_t height): fWidth(width), fHeight(height) { }
   TGDimension(const TGDimension &d): fWidth(d.fWidth), fHeight(d.fHeight) { }
   virtual ~TGDimension() { }

   Bool_t operator==(const TGDimension &b) const
      { return ((fWidth == b.fWidth) && (fHeight == b.fHeight)); }
   TGDimension operator-(const TGDimension &b) const
      { return TGDimension(fWidth - b.fWidth, fHeight - b.fHeight); }
   TGDimension operator+(const TGDimension &b) const
      { return TGDimension(fWidth + b.fWidth, fHeight + b.fHeight); }
```


**TGPosition**

```cpp
   Int_t  fX;         // x position
   Int_t  fY;         // y position

   TGPosition(): fX(0), fY(0) { }
   TGPosition(Int_t xc, Int_t yc): fX(xc), fY(yc) { }
   TGPosition(const TGPosition &p): fX(p.fX), fY(p.fY) { }
   virtual ~TGPosition() { }

   Bool_t operator==(const TGPosition &b) const
      { return ((fX == b.fX) && (fY == b.fY)); }
   TGPosition operator-(const TGPosition &b) const
      { return TGPosition(fX - b.fX, fY - b.fY); }
   TGPosition operator+(const TGPosition &b) const
      { return TGPosition(fX + b.fX, fY + b.fY); }
```


**TGLongPosition**

```cpp
   Long_t  fX;         // x position
   Long_t  fY;         // y position

   TGLongPosition(): fX(0), fY(0) { }
   TGLongPosition(Long_t xc, Long_t yc): fX(xc), fY(yc) { }
   TGLongPosition(const TGLongPosition &p): fX(p.fX), fY(p.fY) { }
   virtual ~TGLongPosition() { }

   Bool_t operator==(const TGLongPosition &b) const
      { return ((fX == b.fX) && (fY == b.fY)); }
   TGLongPosition operator-(const TGLongPosition &b) const
      { return TGLongPosition(fX - b.fX, fY - b.fY); }
   TGLongPosition operator+(const TGLongPosition &b) const
      { return TGLongPosition(fX + b.fX, fY + b.fY); }
```


**TGInsets**

```cpp
   Int_t  fL;    // left
   Int_t  fR;    // right
   Int_t  fT;    // top
   Int_t  fB;    // bottom

   TGInsets(): fL(0), fR(0), fT(0), fB(0) { }
   TGInsets(Int_t lf, Int_t rg, Int_t tp, Int_t bt):
      fL(lf), fR(rg), fT(tp), fB(bt) { }
   TGInsets(const TGInsets &in):
      fL(in.fL), fR(in.fR), fT(in.fT), fB(in.fB) { }
   virtual ~TGInsets() { }

   Bool_t operator==(const TGInsets &in) const
      { return ((fL == in.fL) && (fR == in.fR) && (fT == in.fT) && (fB == in.fB)); }
```


**TGRectangle**

```cpp
   Int_t         fX;    // x position
   Int_t         fY;    // y position
   UInt_t        fW;    // width
   UInt_t        fH;    // height

   // constructors
   TGRectangle(): fX(0), fY(0), fW(0), fH(0) { Empty(); }
   TGRectangle(Int_t rx, Int_t ry, UInt_t rw, UInt_t rh):
                fX(rx), fY(ry), fW(rw), fH(rh) { }
   TGRectangle(const TGPosition &p, const TGDimension &d):
                fX(p.fX), fY(p.fY), fW(d.fWidth), fH(d.fHeight) { }
   TGRectangle(const TGRectangle &r):
                fX(r.fX), fY(r.fY), fW(r.fW), fH(r.fH) { }
   virtual ~TGRectangle() { }

   // methods
   Bool_t Contains(Int_t px, Int_t py) const
                { return ((px >= fX) && (px < fX + (Int_t) fW) &&
                          (py >= fY) && (py < fY + (Int_t) fH)); }
   Bool_t Contains(const TGPosition &p) const
                { return ((p.fX >= fX) && (p.fX < fX + (Int_t) fW) &&
                          (p.fY >= fY) && (p.fY < fY + (Int_t) fH)); }
   Bool_t Intersects(const TGRectangle &r) const
                { return ((fX <= r.fX + (Int_t) r.fW - 1) && (fX + (Int_t) fW - 1 >= r.fX) &&
                          (fY <= r.fY + (Int_t) r.fH - 1) && (fY + (Int_t) fH - 1 >= r.fY)); }
   Int_t Area() const
                { return (fW * fH); }
   TGDimension Size() const
                { return TGDimension(fW, fH); }
   TGPosition LeftTop() const
                { return TGPosition(fX, fY); }
   TGPosition RightBottom() const
                { return TGPosition(fX + (Int_t) fW - 1, fY + (Int_t) fH - 1); }
   void Merge(const TGRectangle &r);// Merge parameters
   void Empty() { fX = fY = 0; fW = fH = 0; }
   Bool_t IsEmpty() const { return ((fW == 0) && (fH == 0)); }
```



## code



<!-- TGDimension.md ends here -->
