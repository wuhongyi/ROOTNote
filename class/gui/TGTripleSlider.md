<!-- TGTripleSlider.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  8 20:49:32 2016 (+0800)
;; Last-Updated: 二 11月  8 20:53:55 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# TGTripleSlider

TripleSlider inherit from DoubleSlider widgets and allow easy        
selection of a min, max and pointer value out of a range.            
The pointer position can be constrained to edges of slider and / or  
can be relative to the slider position.                              

To change the min value press the mouse near to the left / bottom    
edge of the slider.                                                  
To change the max value press the mouse near to the right / top      
edge of the slider.                                                  
To change both values simultaneously press the mouse near to the     
center of the slider.                                                
To change pointer value press the mouse on the pointer and drag it   
to the desired position                                              

```
Dragging the slider will generate the event:                         
kC_VSLIDER, kSL_POS, slider id, 0  (for vertical slider)             
kC_HSLIDER, kSL_POS, slider id, 0  (for horizontal slider)           
                                                                     
Pressing the mouse will generate the event:                          
kC_VSLIDER, kSL_PRESS, slider id, 0  (for vertical slider)           
kC_HSLIDER, kSL_PRESS, slider id, 0  (for horizontal slider)         
                                                                     
Releasing the mouse will generate the event:                         
kC_VSLIDER, kSL_RELEASE, slider id, 0  (for vertical slider)         
kC_HSLIDER, kSL_RELEASE, slider id, 0  (for horizontal slider)       
                                                                     
Moving the pointer will generate the event:                          
kC_VSLIDER, kSL_POINTER, slider id, 0  (for vertical slider)         
kC_HSLIDER, kSL_POINTER, slider id, 0  (for horizontal slider)       
```

Use the functions GetMinPosition(), GetMaxPosition() and             
GetPosition() to retrieve the position of the slider.                
Use the function GetPointerPosition() to retrieve the position of    
the pointer


TGTripleVSlider 继承 TGDoubleVSlider

TGTripleHSlider 继承 TGDoubleHSlider


## class

**TGTripleVSlider**

```cpp
   TGTripleVSlider(const TGWindow *p = 0, UInt_t h = 1, UInt_t type = 1, Int_t id = -1,
                   UInt_t options = kVerticalFrame,
                   Pixel_t back = GetDefaultFrameBackground(),
                   Bool_t reversed = kFALSE,
                   Bool_t mark_ends = kFALSE,
                   Bool_t constrained = kTRUE,
                   Bool_t relative = kFALSE);

   virtual ~TGTripleVSlider();

   virtual void      PointerPositionChanged() { Emit("PointerPositionChanged()"); } //*SIGNAL*
   virtual void      DrawPointer();
   virtual Float_t   GetPointerPosition() const {
      if (fReversedScale) return fVmin + fVmax - fSCz;
      else return fSCz;
   }
   virtual Bool_t    HandleButton(Event_t *event);
   virtual Bool_t    HandleConfigureNotify(Event_t* event);
   virtual Bool_t    HandleMotion(Event_t *event);
   virtual void      SetConstrained(Bool_t on = kTRUE);
   virtual void      SetPointerPosition(Float_t pos);
   virtual void      SetRelative(Bool_t rel = kTRUE) { fRelative = rel; }
   virtual void      SavePrimitive(std::ostream &out, Option_t *option = "");
```


**TGTripleHSlider**

```cpp
   TGTripleHSlider(const TGWindow *p = 0, UInt_t w = 1, UInt_t type = 1, Int_t id = -1,
                   UInt_t options = kHorizontalFrame,
                   Pixel_t back = GetDefaultFrameBackground(),
                   Bool_t reversed = kFALSE,
                   Bool_t mark_ends = kFALSE,
                   Bool_t constrained = kTRUE,
                   Bool_t relative = kFALSE);

   virtual ~TGTripleHSlider();

   virtual void      PointerPositionChanged() { Emit("PointerPositionChanged()"); } //*SIGNAL*
   virtual void      DrawPointer();
   virtual Float_t   GetPointerPosition() const {
      if (fReversedScale) return fVmin + fVmax - fSCz;
      else return fSCz;
   }
   virtual Bool_t    HandleButton(Event_t *event);
   virtual Bool_t    HandleConfigureNotify(Event_t* event);
   virtual Bool_t    HandleMotion(Event_t *event);
   virtual void      SetConstrained(Bool_t on = kTRUE);
   virtual void      SetPointerPosition(Float_t pos);
   virtual void      SetRelative(Bool_t rel = kTRUE) { fRelative = rel; }
   virtual void      SavePrimitive(std::ostream &out, Option_t *option = "");
```

## code

```cpp
#include "TGTripleSlider.h"

// TGTripleSlider
// 可调节范围，左右边界外加一个中间值
TGTripleHSlider *fHslider1;
fHslider1 = new TGTripleHSlider(frame, 190, kDoubleScaleBoth, IDs,
				kHorizontalFrame,
				GetDefaultFrameBackground(),
				kFALSE, kFALSE, kFALSE, kFALSE);
fHslider1->Connect("PointerPositionChanged()", "TTripleSliderDemo", this, "DoSlider()");
fHslider1->Connect("PositionChanged()", "TTripleSliderDemo", this, "DoSlider()");
fHslider1->SetRange(0.05,5.0);
frame->AddFrame(fHslider1, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 5, 5, 5, 5));
fHslider1->GetMinPosition();//Float_t
fHslider1->GetPointerPosition();//Float_t
fHslider1->GetMaxPosition());//Float_t
fHslider1->SetPointerPosition(atof("1.23"));
fHslider1->SetPosition(atof("5.0"), fHslider1->GetMaxPosition());
fHslider1->SetPosition(fHslider1->GetMinPosition(), atof("0.1");
fHslider1->SetConstrained(kTRUE);
fHslider1->SetRelative(kTRUE);	
```

## example




<!-- TGTripleSlider.md ends here -->
