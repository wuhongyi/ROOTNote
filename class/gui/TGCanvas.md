<!-- TGCanvas.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  8 18:30:40 2016 (+0800)
;; Last-Updated: 二 11月  8 19:08:57 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# TGCanvas

A TGCanvas is a frame containing two scrollbars (horizontal and      
vertical) and a viewport. The viewport acts as the window through    
which we look at the contents of the container frame. 


TGContainer 继承 TGCompositeFrame , friend TGViewPort , TGCanvas , TGContainerKeyboardTimer , TGContainerScrollTimer , TGListView


TGViewPort 继承 TGCompositeFrame

TGCanvas 继承 TGFrame


## class

**TGContainer**

```cpp
   TGContainer(const TGWindow *p = 0, UInt_t w = 1, UInt_t h = 1,
               UInt_t options = kSunkenFrame,
               Pixel_t back = GetDefaultFrameBackground());
   TGContainer(TGCanvas *p,UInt_t options = kSunkenFrame,
               Pixel_t back = GetDefaultFrameBackground());

   virtual ~TGContainer();

   virtual void DrawRegion(Int_t x, Int_t y, UInt_t w, UInt_t h);
   virtual void ClearViewPort();
   virtual void Associate(const TGWindow *w) { fMsgWindow = w; }
   virtual void AdjustPosition();
   virtual void SetPagePosition(const TGPosition& pos);
   virtual void SetPagePosition(Int_t x, Int_t y);
   virtual void SetPageDimension(const TGDimension& dim);
   virtual void SetPageDimension(UInt_t w, UInt_t h);
   virtual void RemoveAll();
   virtual void RemoveItem(TGFrame *item);
   virtual void Layout();

   TGCanvas         *GetCanvas() const { return fCanvas; }
   const TGWindow   *GetMessageWindow() const { return fMsgWindow; }
   virtual TGPosition   GetPagePosition() const;
   virtual TGDimension  GetPageDimension() const;

   virtual Int_t  NumSelected() const { return fSelected; }
   virtual Int_t  NumItems() const { return fTotal; }
   virtual TGFrameElement *FindFrame(Int_t x,Int_t y,Bool_t exclude=kTRUE);
   virtual TGFrame        *FindFrameByName(const char *name);
   virtual TGHScrollBar *GetHScrollbar() const;
   virtual TGVScrollBar *GetVScrollbar() const;
   virtual void SetHsbPosition(Int_t newPos);
   virtual void SetVsbPosition(Int_t newPos);
   virtual void LineUp(Bool_t select = kFALSE);
   virtual void LineDown(Bool_t select = kFALSE);
   virtual void LineLeft(Bool_t select = kFALSE);
   virtual void LineRight(Bool_t select = kFALSE);
   virtual void PageUp(Bool_t select = kFALSE);
   virtual void PageDown(Bool_t select = kFALSE);
   virtual void Home(Bool_t select = kFALSE);
   virtual void End(Bool_t select = kFALSE);
   virtual void Search(Bool_t close = kTRUE);
   virtual void *FindItem(const TString& name,
                          Bool_t direction = kTRUE,
                          Bool_t caseSensitive = kTRUE,
                          Bool_t subString = kFALSE);

   virtual const TGFrame *GetNextSelected(void **current);
   virtual TGFrame *GetLastActive() const { return fLastActiveEl ? fLastActiveEl->fFrame : 0; }
   virtual void SavePrimitive(std::ostream &out, Option_t *option = "");

   virtual Bool_t HandleDNDFinished() { fBdown = kFALSE; return kTRUE; }
   virtual Bool_t HandleExpose(Event_t *event);
   virtual Bool_t HandleButton(Event_t *event);
   virtual Bool_t HandleDoubleClick(Event_t *event);
   virtual Bool_t HandleMotion(Event_t *event);
   virtual Bool_t HandleKey(Event_t *event);

   const TGPicture *GetObjPicture(TGFrame *f);
   virtual void SetDragPixmap(const TGPicture *pic);

   virtual void SelectAll();                    //*SIGNAL*
   virtual void UnSelectAll();                  //*SIGNAL*
   virtual void InvertSelection();              //*SIGNAL*
   virtual void ReturnPressed(TGFrame*);        //*SIGNAL*
   virtual void SpacePressed(TGFrame*);         //*SIGNAL*
   virtual void KeyPressed(TGFrame*, UInt_t keysym, UInt_t mask); //*SIGNAL*
   virtual void OnMouseOver(TGFrame*);          //*SIGNAL*
   virtual void CurrentChanged(Int_t x,Int_t y);//*SIGNAL*
   virtual void CurrentChanged(TGFrame* f);     //*SIGNAL*
   virtual void Clicked(TGFrame *f, Int_t btn); //*SIGNAL*
   virtual void DoubleClicked(TGFrame *f, Int_t btn);  //*SIGNAL*
   virtual void DoubleClicked(TGFrame *f, Int_t btn, Int_t x, Int_t y); //*SIGNAL*
   virtual void Clicked(TGFrame *f, Int_t btn, Int_t x, Int_t y);       //*SIGNAL*
```


**TGViewPort**

```cpp
   TGViewPort(const TGWindow *p = 0, UInt_t w = 1, UInt_t h = 1,
              UInt_t options = kChildFrame,
              Pixel_t back = GetDefaultFrameBackground());

   TGFrame *GetContainer() const { return fContainer; }
   void SetContainer(TGFrame *f);

   virtual void DrawBorder() { };
   virtual void Layout() { }
   virtual TGDimension GetDefaultSize() const { return TGDimension(fWidth, fHeight); }

   virtual void SetHPos(Int_t xpos);
   virtual void SetVPos(Int_t ypos);
   void SetPos(Int_t xpos, Int_t ypos);

   Int_t GetHPos() const { return fX0; }
   Int_t GetVPos() const { return fY0; }
   virtual Bool_t HandleConfigureNotify(Event_t *event);
```


**TGCanvas**

```cpp
   enum { kCanvasNoScroll         = 0,
          kCanvasScrollHorizontal = BIT(0),
          kCanvasScrollVertical   = BIT(1),
          kCanvasScrollBoth       = (kCanvasScrollHorizontal | kCanvasScrollVertical)
   };

   TGCanvas(const TGWindow *p = 0, UInt_t w = 1, UInt_t h = 1,
            UInt_t options = kSunkenFrame | kDoubleBorder,
            Pixel_t back = GetDefaultFrameBackground());
   virtual ~TGCanvas();

   TGFrame      *GetContainer() const { return fVport->GetContainer(); }
   TGViewPort   *GetViewPort() const { return fVport; }
   TGHScrollBar *GetHScrollbar() const { return fHScrollbar; }
   TGVScrollBar *GetVScrollbar() const { return fVScrollbar; }

   virtual void  AddFrame(TGFrame *f, TGLayoutHints *l = 0);
   virtual void  SetContainer(TGFrame *f) { fVport->SetContainer(f); }
   virtual void  MapSubwindows();
   virtual void  DrawBorder();
   virtual void  Layout();
   virtual void  ClearViewPort();
   virtual Int_t GetHsbPosition() const;
   virtual Int_t GetVsbPosition() const;
   virtual void  SetHsbPosition(Int_t newPos);
   virtual void  SetVsbPosition(Int_t newPos);
   void          SetScrolling(Int_t scrolling);
   Int_t         GetScrolling() const { return fScrolling; }

   virtual TGDimension GetDefaultSize() const { return TGDimension(fWidth, fHeight); }
   virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t parm2);

   virtual void SavePrimitive(std::ostream &out, Option_t *option = "");
```





## code




## example




<!-- TGCanvas.md ends here -->
