<!-- TGView.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  8 15:35:27 2016 (+0800)
;; Last-Updated: 二 11月  8 15:46:50 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TGView

TGView 继承 TGCompositeFrame, TGWidget , friend TGViewFrame

A TGView provides the infrastructure for text viewer and editor     
widgets. It provides a canvas (TGViewFrame) and (optionally) a       
vertical and horizontal scrollbar and methods for marking and        
scrolling.


TGViewFrame 继承 TGCompositeFrame


## class

**TGView**

```cpp
   enum { kNoHSB = BIT(0), kNoVSB = BIT(1) };
   enum { kHorizontal = 0, kVertical = 1 };

   TGView(const TGWindow *p = 0, UInt_t w = 1, UInt_t h = 1, Int_t id = -1,
          UInt_t xMargin = 0, UInt_t yMargin = 0,
          UInt_t options = kSunkenFrame | kDoubleBorder,
          UInt_t sboptions = 0,
          Pixel_t back = GetWhitePixel());

   virtual ~TGView();

   TGViewFrame   *GetCanvas() const { return fCanvas; }

   virtual void   Clear(Option_t * = "");
   virtual void   SetVisibleStart(Int_t newTop, Int_t direction);
   virtual void   ScrollCanvas(Int_t newTop, Int_t direction);
   virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t parm2);
   virtual void   DrawBorder();
   virtual void   Layout();
   virtual void   SetLayoutManager(TGLayoutManager*) { }
   virtual void   DrawRegion(Int_t x, Int_t y, UInt_t width, UInt_t height);

   virtual void ScrollToPosition(TGLongPosition newPos);
   void ScrollUp(Int_t pixels)
      { ScrollToPosition(TGLongPosition(fVisible.fX, fVisible.fY + pixels)); }
   void ScrollDown(Int_t pixels)
      { ScrollToPosition(TGLongPosition(fVisible.fX, fVisible.fY - pixels)); }
   void ScrollLeft(Int_t pixels)
      { ScrollToPosition(TGLongPosition(fVisible.fX + pixels, fVisible.fY)); }
   void ScrollRight(Int_t  pixels)
      { ScrollToPosition(TGLongPosition(fVisible.fX - pixels, fVisible.fY)); }

   virtual TGDimension GetDefaultSize() const { return TGDimension(fWidth, fHeight); }
   TGDimension GetVirtualSize() const { return fVirtualSize; }
   TGLongPosition  GetScrollValue() const { return fScrollVal; }
   TGLongPosition  GetScrollPosition() const { return fVisible; }

   TGLongPosition ToVirtual(TGLongPosition coord)  const { return coord + fVisible; }
   TGLongPosition ToPhysical(TGLongPosition coord) const { return coord - fVisible; }

   virtual Bool_t HandleButton(Event_t *event);
   virtual Bool_t HandleExpose(Event_t *event);

   virtual void   ChangeBackground(Pixel_t);
   virtual void   SetBackgroundColor(Pixel_t);
   virtual void   SetBackgroundPixmap(Pixmap_t p);
   virtual void   UpdateBackgroundStart();

   const TGGC &GetViewWhiteGC() { return fWhiteGC; }
```


**TGViewFrame**

```cpp
   TGViewFrame(TGView *v, UInt_t w, UInt_t h, UInt_t options = 0,
               Pixel_t back = GetWhitePixel());

   Bool_t HandleSelectionRequest(Event_t *event)
            { return fView->HandleSelectionRequest(event); }
   Bool_t HandleSelectionClear(Event_t *event)
            { return fView->HandleSelectionClear(event); }
   Bool_t HandleSelection(Event_t *event)
            { return fView->HandleSelection(event); }
   Bool_t HandleButton(Event_t *event)
            { return fView->HandleButton(event); }
   Bool_t HandleExpose(Event_t *event)
            { return fView->HandleExpose(event); }
   Bool_t HandleCrossing(Event_t *event)
            { return fView->HandleCrossing(event); }
   Bool_t HandleMotion(Event_t *event)
            { return fView->HandleMotion(event); }
   Bool_t HandleKey(Event_t *event)
            { return fView->HandleKey(event); }
   Bool_t HandleDoubleClick(Event_t *event)
            { return fView->HandleDoubleClick(event); }
```


## code




## example





<!-- TGView.md ends here -->
