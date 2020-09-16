<!-- TGScrollBar.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  8 16:37:11 2016 (+0800)
;; Last-Updated: 三 9月 16 11:11:38 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 3
;; URL: http://wuhongyi.cn -->

# TGScrollBar+

The classes in this file implement scrollbars. Scrollbars can be     
either placed horizontal or vertical. A scrollbar contains three     
TGScrollBarElements: The "head", "tail" and "slider". The head and   
tail are fixed at either end and have the typical arrows in them.    

```
The TGHScrollBar will generate the following event messages:         
kC_HSCROLL, kSB_SLIDERPOS, position, 0                               
kC_HSCROLL, kSB_SLIDERTRACK, position, 0                             

The TGVScrollBar will generate the following event messages:         
kC_VSCROLL, kSB_SLIDERPOS, position, 0                               
kC_VSCROLL, kSB_SLIDERTRACK, position, 0
```


TGScrollBarElement 继承 TGFrame

TGScrollBar 继承 TGFrame, TGWidget

TGHScrollBar 继承 TGScrollBar

TGVScrollBar 继承 TGScrollBar



## class

```cpp
//--- scrollbar types

enum EScrollBarMode {
   kSBHorizontal,
   kSBVertical
};
```


**TGScrollBarElement**

```cpp
   TGScrollBarElement(const TGWindow *p = 0, const TGPicture *pic = 0,
                      UInt_t w = 1, UInt_t h = 1,
                      UInt_t options = kRaisedFrame | kDoubleBorder,
                      Pixel_t back = GetDefaultFrameBackground());
   virtual ~TGScrollBarElement();

   virtual void SetState(Int_t state);
   virtual void DrawBorder();
   virtual void SetEnabled(Bool_t on = kTRUE);
   virtual Bool_t IsEnabled() const { return !(fState & kButtonDisabled); }
   virtual Bool_t HandleCrossing(Event_t *event);
```


**TGScrollBar**

```cpp
   static Pixmap_t  GetBckgndPixmap();
   static Int_t     GetScrollBarWidth();

   TGScrollBar(const TGWindow *p = 0, UInt_t w = 1, UInt_t h = 1,
               UInt_t options = kChildFrame,
               Pixel_t back = GetDefaultFrameBackground());
   virtual ~TGScrollBar();

   void           GrabPointer(Bool_t grab) { fGrabPointer = grab; }

   virtual void   DrawBorder() { }
   virtual Bool_t HandleButton(Event_t *event) = 0;
   virtual Bool_t HandleCrossing(Event_t *event);
   virtual Bool_t HandleMotion(Event_t *event) = 0;
   virtual Bool_t HandleTimer(TTimer *t);
   virtual void   Layout() = 0;

   virtual void  SetDragging(Bool_t drag) { fDragging = drag; }
   virtual void  SetRange(Int_t range, Int_t page_size) = 0;
   virtual void  SetPosition(Int_t pos) = 0;
   virtual Int_t GetPosition() const { return fPos; }
   virtual Int_t GetPageSize() const { return fPsize; }
   virtual Int_t GetRange() const { return fRange; }
   virtual void  Resize(UInt_t w = 0, UInt_t h = 0) { TGFrame::Resize(w, h); SetRange(fRange, fPsize); }
   virtual void  MoveResize(Int_t x, Int_t y, UInt_t w = 0, UInt_t h = 0)
                  { TGFrame::MoveResize(x, y, w, h); SetRange(fRange, fPsize); }
   virtual void  Resize(TGDimension size) { Resize(size.fWidth, size.fHeight); }
   virtual void  ChangeBackground(Pixel_t back);
   virtual void  SetAccelerated(Bool_t m = kTRUE) { fAccelerated = m; }
         Bool_t  IsAccelerated() const { return fAccelerated; }

   virtual void MapSubwindows() { TGWindow::MapSubwindows(); }
   TGScrollBarElement *GetHead() const { return fHead; }
   TGScrollBarElement *GetTail() const { return fTail; }
   TGScrollBarElement *GetSlider() const { return fSlider; }

   virtual void  PositionChanged(Int_t pos) { Emit("PositionChanged(Int_t)", pos); } //*SIGNAL*
   virtual void  RangeChanged(Int_t range) { Emit("RangeChanged(Int_t)", range); } //*SIGNAL*
   virtual void  PageSizeChanged(Int_t range) { Emit("PageSizeChanged(Int_t)", range); } //*SIGNAL*

   virtual Int_t GetSmallIncrement() { return fSmallInc; }
   virtual void  SetSmallIncrement(Int_t increment) { fSmallInc = increment; }
```


**TGHScrollBar**

```cpp
   TGHScrollBar(const TGWindow *p = 0, UInt_t w = 4, UInt_t h = 2,
                UInt_t options = kHorizontalFrame,
                Pixel_t back = GetDefaultFrameBackground());
   virtual ~TGHScrollBar() { }

   virtual Bool_t HandleButton(Event_t *event);
   virtual Bool_t HandleMotion(Event_t *event);
   virtual TGDimension GetDefaultSize() const
                        { return TGDimension(fWidth, GetScrollBarWidth()); }
   virtual void Layout();

   virtual void SetRange(Int_t range, Int_t page_size);  //*MENU*
   virtual void SetPosition(Int_t pos);                  //*MENU* *GETTER=GetPosition
   virtual void SavePrimitive(std::ostream &out, Option_t *option = "");
```


**TGVScrollBar**

```cpp
   TGVScrollBar(const TGWindow *p = 0, UInt_t w = 2, UInt_t h = 4,
                UInt_t options = kVerticalFrame,
                Pixel_t back = GetDefaultFrameBackground());
   virtual ~TGVScrollBar() { }

   virtual Bool_t HandleButton(Event_t *event);
   virtual Bool_t HandleMotion(Event_t *event);
   virtual TGDimension GetDefaultSize() const
                        { return TGDimension(GetScrollBarWidth(), fHeight); }
   virtual void Layout();

   virtual void SetRange(Int_t range, Int_t page_size);  //*MENU*
   virtual void SetPosition(Int_t pos);                  //*MENU*  *GETTER=GetPosition
   virtual void SavePrimitive(std::ostream &out, Option_t *option = "");
```

## code




## example





<!-- TGScrollBar.md ends here -->
