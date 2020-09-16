<!-- TGSlider.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  8 16:10:15 2016 (+0800)
;; Last-Updated: 三 9月 16 11:11:59 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TGSlider+

Slider widgets allow easy selection of a range.                      
Sliders can be either horizontal or vertical oriented and there is   
a choice of two different slider types and three different types     
of tick marks.                                                       

TGSlider is an abstract base class. Use the concrete TGVSlider and TGHSlider.                                                           

```
Dragging the slider will generate the event:                         
kC_VSLIDER, kSL_POS, slider id, position  (for vertical slider)      
kC_HSLIDER, kSL_POS, slider id, position  (for horizontal slider)    
                                                                   
Pressing the mouse will generate the event:                         
kC_VSLIDER, kSL_PRESS, slider id, 0  (for vertical slider)           
kC_HSLIDER, kSL_PRESS, slider id, 0  (for horizontal slider)         

Releasing the mouse will generate the event:                         
kC_VSLIDER, kSL_RELEASE, slider id, 0  (for vertical slider)         
kC_HSLIDER, kSL_RELEASE, slider id, 0  (for horizontal slider) 
```

TGSlider 继承 TGFrame, TGWidget

TGVSlider 继承 TGSlider  
Vertical slider widget

TGHSlider 继承 TGSlider  
Horizontal slider widget


## class

```cpp
//--- sizes for vert. and horz. sliders

enum ESliderSize {
   kSliderWidth  = 24,
   kSliderHeight = kSliderWidth
};


enum ESliderType {
   //--- slider types (type of slider picture)
   kSlider1        = BIT(0),
   kSlider2        = BIT(1),

   //--- scaling of slider
   kScaleNo        = BIT(2),
   kScaleDownRight = BIT(3),
   kScaleBoth      = BIT(4)
};
```


**TGSlider**

```cpp
   TGSlider(const TGWindow *p = 0, UInt_t w = 1, UInt_t h = 1,
            UInt_t type = kSlider1 | kScaleBoth, Int_t id = -1,
            UInt_t options = kChildFrame,
            Pixel_t back = GetDefaultFrameBackground());

   virtual ~TGSlider() { }

   virtual Bool_t HandleButton(Event_t *event) = 0;
   virtual Bool_t HandleConfigureNotify(Event_t* event) = 0;
   virtual Bool_t HandleMotion(Event_t *event) = 0;

   virtual void  SetEnabled(Bool_t flag = kTRUE) { SetState( flag ); }              //*TOGGLE* *GETTER=IsEnabled
   virtual void  SetState(Bool_t state);
   virtual void  SetScale(Int_t scale) { fScale = scale; }                          //*MENU*
   virtual void  SetRange(Int_t min, Int_t max) { fVmin = min; fVmax = max; }       //*MENU*
   virtual void  SetPosition(Int_t pos) { fPos = pos; fClient->NeedRedraw(this); }  //*MENU*
   virtual Int_t GetPosition() const { return fPos; }
   virtual Int_t GetMinPosition() const { return fVmin; }
   virtual Int_t GetMaxPosition() const { return fVmax; }
   virtual Int_t GetScale() const { return fScale; }
   virtual void  MapSubwindows() { TGWindow::MapSubwindows(); }
   virtual void  ChangeSliderPic(const char *name) {
                    if (fSliderPic) fClient->FreePicture(fSliderPic);
                    fSliderPic = fClient->GetPicture(name);
                 }

   virtual void  PositionChanged(Int_t pos) { Emit("PositionChanged(Int_t)", pos); } // *SIGNAL*
   virtual void  Pressed() { Emit("Pressed()"); }    // *SIGNAL*
   virtual void  Released() { Emit("Released()"); }  // *SIGNAL*
```


**TGVSlider**

```cpp
   TGVSlider(const TGWindow *p = 0, UInt_t h = 40,
             UInt_t type = kSlider1 | kScaleBoth, Int_t id = -1,
             UInt_t options = kVerticalFrame,
             Pixel_t back = GetDefaultFrameBackground());
   virtual ~TGVSlider();

   virtual Bool_t HandleButton(Event_t *event);
   virtual Bool_t HandleConfigureNotify(Event_t* event);
   virtual Bool_t HandleMotion(Event_t *event);
   virtual TGDimension GetDefaultSize() const
                     { return TGDimension(kSliderWidth, fHeight); }
   virtual void   Resize(UInt_t w, UInt_t h) { TGFrame::Resize(w, h ? h+16 : fHeight + 16); }
   virtual void   Resize(TGDimension size) { Resize(size.fWidth, size.fHeight); }
   virtual void   SavePrimitive(std::ostream &out, Option_t *option = "");
```


**TGHSlider**

```cpp
   TGHSlider(const TGWindow *p = 0, UInt_t w = 40,
             UInt_t type = kSlider1 | kScaleBoth, Int_t id = -1,
             UInt_t options = kHorizontalFrame,
             Pixel_t back = GetDefaultFrameBackground());
   virtual ~TGHSlider();

   virtual Bool_t HandleButton(Event_t *event);
   virtual Bool_t HandleConfigureNotify(Event_t* event);
   virtual Bool_t HandleMotion(Event_t *event);
   virtual TGDimension GetDefaultSize() const
                     { return TGDimension(fWidth, kSliderHeight); }
   virtual void   Resize(UInt_t w, UInt_t h) { TGFrame::Resize(w ? w+16 : fWidth + 16, h); }
   virtual void   Resize(TGDimension size) { Resize(size.fWidth, size.fHeight); }
   virtual void   SavePrimitive(std::ostream &out, Option_t *option = "");
```

## code



## example




<!-- TGSlider.md ends here -->
