<!-- TGColorDialog.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 二 11月  8 19:46:57 2016 (+0800)
;; Last-Updated: 六 11月 19 15:18:19 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
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
/// TGColorPalette widget: this is just a grid of color cells of the
/// specified size. Colors can be selected by clicking on them or by
/// using the arrow keys.

   virtual ~TGColorPalette();/// Destructor.

   virtual Bool_t HandleButton(Event_t *event);/// Handle button events in color palette
   virtual Bool_t HandleMotion(Event_t *event);/// Handle mouse motion events in color palette.
   virtual Bool_t HandleKey(Event_t *event);/// Handle keyboard events in color palette.

   virtual TGDimension GetDefaultSize() const
            { return TGDimension((fCw + 5) * fCols, (fCh + 5) * fRows); }

   void    SetColors(Pixel_t colors[]);/// Set color entries in color samples.
   void    SetColor(Int_t ix, Pixel_t color);/// Set color at index ix of color entries.
   void    SetCurrentCellColor(Pixel_t color);/// Set current cell color.

   void    SetCellSize(Int_t w = 20, Int_t h = 17);/// Set color cell size.

   Pixel_t GetColorByIndex(Int_t ix) const { return fPixels[ix]; }
   Pixel_t GetCurrentColor() const;/// Return currently selected color value.

   virtual void ColorSelected(Pixel_t col = 0)
            { Emit("ColorSelected(Pixel_t)", col ? col : GetCurrentColor()); }  //*SIGNAL*
````


**TGColorPick**

```cpp
   TGColorPick(const TGWindow *p = 0, Int_t w = 1, Int_t h = 1, Int_t id = -1);
/// TGColorPick constructor.
/// TGColorPick is a widget which allows a color to be picked from HLS space.
/// It consists of two elements: a color map window from where the user can
/// select the hue and saturation level of a color, and a slider to select
/// color's lightness.

   virtual ~TGColorPick();/// TGColorPick destructor.

   virtual Bool_t HandleButton(Event_t *event);/// Handle mouse button events in color pick widget.
   virtual Bool_t HandleMotion(Event_t *event);/// Handle mouse motion events in color pick widget.

   void     SetColor(Pixel_t color);/// Position the slider cursor on right color position.
   Pixel_t  GetCurrentColor() const { return fCurrentColor; }

   virtual  void ColorSelected(Pixel_t col = 0)
            { Emit("ColorSelected(Pixel_t)", col ? col : GetCurrentColor()); }  //*SIGNAL*
````


**TGColorDialog**

```cpp
   TGColorDialog(const TGWindow *p = 0, const TGWindow *m = 0, Int_t *retc = 0,
                 Pixel_t *color = 0, Bool_t wait = kTRUE);
/// Color selection dialog constructor.
/// The TGColorDialog presents a full featured color selection dialog.
/// It uses 2 TGColorPalette's and the TGColorPick widgets.

   virtual ~TGColorDialog();/// TGColorDialog destructor.

   TGColorPalette *GetPalette() const { return fPalette; }
   TGColorPalette *GetCustomPalette() const { return fCpalette; }

   virtual void ColorSelected(Pixel_t); //*SIGNAL*  /// Emit signal about selected color.
   virtual void AlphaColorSelected(ULong_t); //*SIGNAL*  /// Emit signal about selected alpha and color.
           void DoPreview();/// Slot method called when Preview button is clicked.
   virtual void SetCurrentColor(Pixel_t col);/// Change current color.
           void SetColorInfo(Int_t event, Int_t px, Int_t py, TObject *selected);
///  Set the color info in RGB and HLS parts
````


## code



## example




<!-- TGColorDialog.md ends here -->
