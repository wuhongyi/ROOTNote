<!-- TGColorDialog.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  8 19:46:57 2016 (+0800)
;; Last-Updated: 二 11月  8 19:52:48 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# TGColorDialog

The TGColorPalette is a widget showing an matrix of color cells. The 
colors can be set and selected.                                      
                                                                      
The TGColorPick is a widget which allows a color to be picked from   
HLS space. It consists of two elements: a color map window from      
where the user can select the hue and saturation level of a color,   
and a slider to select color's lightness.                            

```
Selecting a color in these two widgets will generate the event:      
kC_COLORSEL, kCOL_CLICK, widget id, 0.                               
and the signal:                                                      
ColorSelected(Pixel_t color)                                         
```

The TGColorDialog presents a full featured color selection dialog.   
It uses 2 TGColorPalette's and the TGColorPick widgets.


TGColorPalette 继承 TGFrame, TGWidget  
Color palette widget

TGColorPick 继承 TGFrame, TGWidget  
Color picker widget

TGColorDialog 继承 TGTransientFrame  
Color selection dialog



## class

**TGColorPalette**

```cpp
   TGColorPalette(const TGWindow *p = 0, Int_t cols = 8, Int_t rows = 8, Int_t id = -1);
   virtual ~TGColorPalette();

   virtual Bool_t HandleButton(Event_t *event);
   virtual Bool_t HandleMotion(Event_t *event);
   virtual Bool_t HandleKey(Event_t *event);

   virtual TGDimension GetDefaultSize() const
            { return TGDimension((fCw + 5) * fCols, (fCh + 5) * fRows); }

   void    SetColors(Pixel_t colors[]);
   void    SetColor(Int_t ix, Pixel_t color);
   void    SetCurrentCellColor(Pixel_t color);

   void    SetCellSize(Int_t w = 20, Int_t h = 17);

   Pixel_t GetColorByIndex(Int_t ix) const { return fPixels[ix]; }
   Pixel_t GetCurrentColor() const;

   virtual void ColorSelected(Pixel_t col = 0)
            { Emit("ColorSelected(Pixel_t)", col ? col : GetCurrentColor()); }  //*SIGNAL*
````


**TGColorPick**

```cpp
   TGColorPick(const TGWindow *p = 0, Int_t w = 1, Int_t h = 1, Int_t id = -1);
   virtual ~TGColorPick();

   virtual Bool_t HandleButton(Event_t *event);
   virtual Bool_t HandleMotion(Event_t *event);

   void     SetColor(Pixel_t color);
   Pixel_t  GetCurrentColor() const { return fCurrentColor; }

   virtual  void ColorSelected(Pixel_t col = 0)
            { Emit("ColorSelected(Pixel_t)", col ? col : GetCurrentColor()); }  //*SIGNAL*
````


**TGColorDialog**

```cpp
   TGColorDialog(const TGWindow *p = 0, const TGWindow *m = 0, Int_t *retc = 0,
                 Pixel_t *color = 0, Bool_t wait = kTRUE);
   virtual ~TGColorDialog();

   TGColorPalette *GetPalette() const { return fPalette; }
   TGColorPalette *GetCustomPalette() const { return fCpalette; }

   virtual void ColorSelected(Pixel_t); //*SIGNAL*
   virtual void AlphaColorSelected(ULong_t); //*SIGNAL*
           void DoPreview();
   virtual void SetCurrentColor(Pixel_t col);
           void SetColorInfo(Int_t event, Int_t px, Int_t py, TObject *selected);
````


## code



## example




<!-- TGColorDialog.md ends here -->
