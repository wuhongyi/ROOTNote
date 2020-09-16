<!-- TGColorSelect.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  8 19:35:20 2016 (+0800)
;; Last-Updated: 三 9月 16 10:57:41 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 3
;; URL: http://wuhongyi.cn -->

# TGColorSelect*

The TGColorFrame is a small frame with border showing a specific color.       

The TG16ColorSelector is a composite frame with 16 TGColorFrames.    

The TGColorPopup is a popup containing a TG16ColorSelector and a     
"More..." button which popups up a TGColorDialog allowing custom     
color selection.                                                     

The TGColorSelect widget is like a checkbutton but instead of the    
check mark there is color area with a little down arrow. When        
clicked on the arrow the TGColorPopup pops up.                       


```
Selecting a color in this widget will generate the event:            
kC_COLORSEL, kCOL_SELCHANGED, widget id, pixel.                      
and the signal:                                                      
ColorSelected(Pixel_t pixel)
```

TGColorFrame 继承 TGFrame  
Frame for color cell


TG16ColorSelector 继承 TGCompositeFrame  
16 color cells  

TGColorPopup 继承 TGCompositeFrame  
Color selector popup

TGColorSelect 继承 TGCheckButton  
Color selection checkbutton


## class

**TGColorFrame**

```cpp
   TGColorFrame(const TGWindow *p = 0, Pixel_t c = 0, Int_t n = 1);
/// TGColorFrame constructor.
/// The TGColorFrame is a small frame with border showing a specific color.

   virtual ~TGColorFrame() { }

   virtual Bool_t  HandleButton(Event_t *event);/// Handle button events in TGColorFrame.
   virtual void    DrawBorder();/// Draw TGColorFrame border.

   void     SetActive(Bool_t in) { fActive = in; gClient->NeedRedraw(this); }
   Pixel_t  GetColor() const { return fColor; }
```


**TG16ColorSelector**

```cpp
   TG16ColorSelector(const TGWindow *p = 0);
/// TG16ColorSelector constructor.
/// The TG16ColorSelector is a composite frame with 16 TGColorFrames.

   virtual ~TG16ColorSelector();/// TG16ColorSelector destructor.

   virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t parm2);/// Process messages for TG16ColorSelector.

   void    SetActive(Int_t newat);/// Set active color frame.
   Int_t   GetActive() { return fActive; }
```


**TGColorPopup**

```cpp
   TGColorPopup(const TGWindow *p = 0, const TGWindow *m = 0, Pixel_t color = 0);
/// TGColorPopup constructor.
/// The TGColorPopup is a popup containing a TG16ColorSelector and a "More..."
/// button which popups up a TGColorDialog allowing custom color selection.

   virtual ~TGColorPopup();/// TGColorPopup destructor.

   virtual Bool_t HandleButton(Event_t *event);/// Handle mouse button events for TGColorPopup.
   virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t parm2);/// Process messages for TGColorPopup.

   void    PlacePopup(Int_t x, Int_t y, UInt_t w, UInt_t h);/// Popup TGColorPopup at x,y position
   void    EndPopup();/// Ungrab pointer and unmap window.
   void    PreviewColor(Pixel_t color);/// Emit a signal to see preview.
   void    PreviewAlphaColor(ULong_t color);/// Emit a signal to see preview.
```


**TGColorSelect**

```cpp
   TGColorSelect(const TGWindow *p = 0, Pixel_t color = 0,
                 Int_t id = -1);
/// TGColorSelect constructor.
/// The TGColorSelect widget is like a checkbutton but instead of the check
/// mark there is color area with a little down arrow.
/// When clicked on the arrow the TGColorPopup pops up.

   virtual ~TGColorSelect();/// TGColorSelect destructor.

   virtual Bool_t HandleButton(Event_t *event);/// Handle button events for TGColorSelect.
   virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t parm2);/// Process messages for TGColorSelect.

   void    SetColor(Pixel_t color, Bool_t emit = kTRUE);/// Set color.
   void    SetAlphaColor(ULong_t color, Bool_t emit = kTRUE);/// Set color.
   Pixel_t GetColor() const { return fColor; }
   void    Enable(Bool_t on = kTRUE);  //*TOGGLE* *GETTER=IsEnabled  /// Set state of widget as enabled.
   void    Disable();/// Set state of widget as disabled.

   // dummy methods just to remove from context menu
   void SetDown(Bool_t on = kTRUE, Bool_t emit = kFALSE) { TGButton::SetDown(on, emit); }
   void Rename(const char *title)  { TGTextButton::SetTitle(title); }
   void SetEnabled(Bool_t e = kTRUE) {TGButton::SetEnabled(e); }

   virtual TGDimension GetDefaultSize() const { return TGDimension(43, 21); }
   virtual void SavePrimitive(std::ostream &out, Option_t * = "");
/// Save a color select widget as a C++ statement(s) on output stream out

   virtual void ColorSelected(Pixel_t color = 0)
            { Emit("ColorSelected(Pixel_t)", color ? color : GetColor()); }  //*SIGNAL*
   virtual void AlphaColorSelected(ULong_t colptr = 0)
            { Emit("AlphaColorSelected(ULong_t)", colptr); }  //*SIGNAL*
```



## code



## example




<!-- TGColorSelect.md ends here -->
