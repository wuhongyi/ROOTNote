<!-- TGDoubleSlider.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  8 12:51:36 2016 (+0800)
;; Last-Updated: 二 11月  8 13:06:09 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# TGDoubleSlider

TGDoubleSlider 继承 TGFrame, TGWidget

TGDoubleVSlider 继承 TGDoubleSlider

TGDoubleHSlider 继承 TGDoubleSlider

## class

**TGDoubleSlider**

```cpp
   TGDoubleSlider(const TGWindow *p = 0, UInt_t w = 1, UInt_t h = 1, UInt_t type = 1, Int_t id = -1,
                  UInt_t options = kChildFrame,
                  Pixel_t back = GetDefaultFrameBackground(),
                  Bool_t reversed = kFALSE,
                  Bool_t mark_ends = kFALSE);

   virtual ~TGDoubleSlider() { }

   virtual Bool_t HandleButton(Event_t *event) = 0;
   virtual Bool_t HandleMotion(Event_t *event) = 0;

   virtual void  SetScale(Int_t scale) { fScale = scale; }
   virtual void  SetRange(Float_t min, Float_t max) {
      fVmin = min; fVmax = max;
      FixBounds(fVmin, fVmax);
   }

   virtual void SetPosition(Float_t min, Float_t max) {
      if (fReversedScale) { fSmin = fVmin+fVmax-max; fSmax = fVmin+fVmax-min; }
      else { fSmin = min; fSmax = max; }
      fClient->NeedRedraw(this);
   }

   virtual Float_t GetMinPosition() const {
      if (fReversedScale) return fVmin+fVmax-fSmax;
      else return fSmin;
   }
   virtual Float_t GetMaxPosition() const {
      if (fReversedScale) return fVmin+fVmax-fSmin;
      else return fSmax;
   }
   virtual void GetPosition(Float_t &min, Float_t &max) const {
      if (fReversedScale) { min = fVmin+fVmax-fSmax; max = fVmin+fVmax-fSmin; }
      else { min = fSmin; max = fSmax; }
   }
   virtual void GetPosition(Float_t *min, Float_t *max) const {
      if (fReversedScale) { *min = fVmin+fVmax-fSmax; *max = fVmin+fVmax-fSmin; }
      else { *min = fSmin; *max = fSmax; }
   }

   virtual void  MapSubwindows() { TGWindow::MapSubwindows(); }

   virtual void  PositionChanged() { Emit("PositionChanged()"); } //*SIGNAL*
   virtual void  Pressed() { Emit("Pressed()"); }                 //*SIGNAL*
   virtual void  Released() { Emit("Released()"); }               //*SIGNAL*
```


**TGDoubleVSlider**

```cpp
   TGDoubleVSlider(const TGWindow *p = 0, UInt_t h = 1, UInt_t type = 1, Int_t id = -1,
                   UInt_t options = kVerticalFrame,
                   Pixel_t back = GetDefaultFrameBackground(),
                   Bool_t reversed = kFALSE,
                   Bool_t mark_ends = kFALSE);

   virtual ~TGDoubleVSlider();

   virtual Bool_t HandleButton(Event_t *event);
   virtual Bool_t HandleMotion(Event_t *event);
   virtual TGDimension GetDefaultSize() const
                     { return TGDimension(kDoubleSliderWidth, fHeight); }
   virtual void   SavePrimitive(std::ostream &out, Option_t *option = "");
```


**TGDoubleHSlider **

```cpp
   TGDoubleHSlider(const TGWindow *p = 0, UInt_t w = 1, UInt_t type = 1, Int_t id = -1,
                   UInt_t options = kHorizontalFrame,
                   Pixel_t back = GetDefaultFrameBackground(),
                   Bool_t reversed = kFALSE,
                   Bool_t mark_ends = kFALSE);

   virtual ~TGDoubleHSlider();

   virtual Bool_t HandleButton(Event_t *event);
   virtual Bool_t HandleMotion(Event_t *event);
   virtual TGDimension GetDefaultSize() const
                     { return TGDimension(fWidth, kDoubleSliderHeight); }
   virtual void   SavePrimitive(std::ostream &out, Option_t *option = "");
```

## code




## example





<!-- TGDoubleSlider.md ends here -->
