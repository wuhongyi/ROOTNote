<!-- TGColorSelect.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  8 19:35:20 2016 (+0800)
;; Last-Updated: 二 11月  8 19:46:29 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# TGColorSelect

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
   virtual ~TGColorFrame() { }

   virtual Bool_t  HandleButton(Event_t *event);
   virtual void    DrawBorder();

   void     SetActive(Bool_t in) { fActive = in; gClient->NeedRedraw(this); }
   Pixel_t  GetColor() const { return fColor; }
```


**TG16ColorSelector**

```cpp
   TG16ColorSelector(const TGWindow *p = 0);
   virtual ~TG16ColorSelector();

   virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t parm2);

   void    SetActive(Int_t newat);
   Int_t   GetActive() { return fActive; }
```


**TGColorPopup**

```cpp
   TGColorPopup(const TGWindow *p = 0, const TGWindow *m = 0, Pixel_t color = 0);
   virtual ~TGColorPopup();

   virtual Bool_t HandleButton(Event_t *event);
   virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t parm2);

   void    PlacePopup(Int_t x, Int_t y, UInt_t w, UInt_t h);
   void    EndPopup();
   void    PreviewColor(Pixel_t color);
   void    PreviewAlphaColor(ULong_t color);
```


**TGColorSelect**

```cpp
   TGColorSelect(const TGWindow *p = 0, Pixel_t color = 0,
                 Int_t id = -1);
   virtual ~TGColorSelect();

   virtual Bool_t HandleButton(Event_t *event);
   virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t parm2);

   void    SetColor(Pixel_t color, Bool_t emit = kTRUE);
   void    SetAlphaColor(ULong_t color, Bool_t emit = kTRUE);
   Pixel_t GetColor() const { return fColor; }
   void    Enable(Bool_t on = kTRUE);  //*TOGGLE* *GETTER=IsEnabled
   void    Disable();

   // dummy methods just to remove from context menu
   void SetDown(Bool_t on = kTRUE, Bool_t emit = kFALSE) { TGButton::SetDown(on, emit); }
   void Rename(const char *title)  { TGTextButton::SetTitle(title); }
   void SetEnabled(Bool_t e = kTRUE) {TGButton::SetEnabled(e); }

   virtual TGDimension GetDefaultSize() const { return TGDimension(43, 21); }
   virtual void SavePrimitive(std::ostream &out, Option_t * = "");

   virtual void ColorSelected(Pixel_t color = 0)
            { Emit("ColorSelected(Pixel_t)", color ? color : GetColor()); }  //*SIGNAL*
   virtual void AlphaColorSelected(ULong_t colptr = 0)
            { Emit("AlphaColorSelected(ULong_t)", colptr); }  //*SIGNAL*
```



## code



## example




<!-- TGColorSelect.md ends here -->
