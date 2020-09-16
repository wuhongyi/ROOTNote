<!-- TGProgressBar.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 一 11月 14 20:16:55 2016 (+0800)
;; Last-Updated: 三 9月 16 11:11:28 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 2
;; URL: http://wuhongyi.cn -->

# TGProgressBar*

TGProgressBar, TGHProgressBar and TGVProgressBar                     
                                                                      
The classes in this file implement progress bars. Progress bars can  
be used to show progress of tasks taking more then a few seconds.    
TGProgressBar is an abstract base class, use either TGHProgressBar   
or TGVProgressBar. TGHProgressBar can in addition show the position  
as text in the bar. 


TGProgressBar 继承 TGFrame

TGHProgressBar 继承 TGProgressBar

TGVProgressBar 继承 TGProgressBar

## class

**TGProgressBar**

```cpp
   enum EBarType { kStandard, kFancy };
   enum EFillType { kSolidFill, kBlockFill };
   enum { kProgressBarStandardWidth = 16, kProgressBarTextWidth = 24,
          kBlockSize = 8, kBlockSpace = 2 };

   static FontStruct_t  GetDefaultFontStruct();/// Return default font structure in use.
   static const TGGC   &GetDefaultGC();/// Return default graphics context in use.

   TGProgressBar(const TGWindow *p, UInt_t w, UInt_t h,
                 Pixel_t back = GetWhitePixel(),
                 Pixel_t barcolor = GetDefaultSelectedBackground(),
                 GContext_t norm = GetDefaultGC()(),
                 FontStruct_t font = GetDefaultFontStruct(),
                 UInt_t options = kDoubleBorder | kSunkenFrame);/// Create progress bar.
   virtual ~TGProgressBar() { }

   Float_t      GetMin() const { return fMin; }
   Float_t      GetMax() const { return fMax; }
   Float_t      GetPosition() const { return fPos; }
   EFillType    GetFillType() const { return fFillType; }
   EBarType     GetBarType() const { return fBarType; }
   Bool_t       GetShowPos() const { return fShowPos; }
   TString      GetFormat() const { return fFormat; }
   const char*  GetValueFormat() const { return fFormat.Data(); }
   Bool_t       UsePercent() const { return fPercent; }
   Pixel_t      GetBarColor() const { return fBarColorGC.GetForeground(); }
   GContext_t   GetNormGC() const { return fNormGC; }
   FontStruct_t GetFontStruct() const { return fFontStruct; }

   void         SetPosition(Float_t pos);                //*MENU*  *GETTER=GetPosition
/// Set progress position between [min,max].

   void         SetRange(Float_t min, Float_t max);      //*MENU*
/// Set min and max of progress bar.

   void         Increment(Float_t inc);/// Increment progress position.
   void         SetBarType(EBarType type);               //*SUBMENU*
/// Set bar type.

   void         SetFillType(EFillType type);             //*SUBMENU*
/// Set fill type.

   virtual void Percent(Bool_t on) { fPercent = on; fClient->NeedRedraw(this); } //*TOGGLE* *GETTER=UsePercent
   virtual void ShowPos(Bool_t on) { fShowPos = on; fClient->NeedRedraw(this); } //*TOGGLE* *GETTER=GetShowPos
   virtual void Format(const char *format = "%.2f");     //*MENU* *GETTER=GetValueFormat
/// Set format for displaying a value.

   void         SetMin(Float_t min) { fMin = min; }
   void         SetMax(Float_t max) { fMax = max; }
   virtual void SetBarColor(Pixel_t color);/// Set progress bar color.
   void         SetBarColor(const char *color="blue");/// Set progress bar color.
   virtual void Reset();                                 //*MENU*
/// Reset progress bar (i.e. set pos to 0).

   virtual void SetForegroundColor(Pixel_t pixel);
/// Change text color drawing.

   virtual void SavePrimitive(std::ostream &out, Option_t *option = "");
/// Save progress bar parameters as a C++ statement(s) on output stream out.
```


**TGHProgressBar**

```cpp
   TGHProgressBar(const TGWindow *p = 0,
                  UInt_t w = 4, UInt_t h = kProgressBarTextWidth,
                  Pixel_t back = GetWhitePixel(),
                  Pixel_t barcolor = GetDefaultSelectedBackground(),
                  GContext_t norm = GetDefaultGC()(),
                  FontStruct_t font = GetDefaultFontStruct(),
                  UInt_t options = kDoubleBorder | kSunkenFrame);/// Horizontal progress bar constructor.
   TGHProgressBar(const TGWindow *p, EBarType type, UInt_t w);
/// Simple constructor allow you to create either a standard progress
/// bar, or a more fancy progress bar (fancy means: double sized border,
/// white background and a bit wider to allow for text to be printed
/// in the bar.

   virtual ~TGHProgressBar() { }

   virtual TGDimension GetDefaultSize() const
                     { return TGDimension(fWidth, fBarWidth); }

   void ShowPosition(Bool_t set = kTRUE, Bool_t percent = kTRUE,
                     const char *format = "%.2f");
/// Show postion text, either in percent or formatted according format.

   virtual void SavePrimitive(std::ostream &out, Option_t *option = "");
/// Save a horizontal progress bar as a C++ statement(s) on output stream out
```


**TGVProgressBar**

```cpp
   TGVProgressBar(const TGWindow *p = 0,
                  UInt_t w = kProgressBarTextWidth, UInt_t h = 4,
                  Pixel_t back = GetWhitePixel(),
                  Pixel_t barcolor = GetDefaultSelectedBackground(),
                  GContext_t norm = GetDefaultGC()(),
                  FontStruct_t font = GetDefaultFontStruct(),
                  UInt_t options = kDoubleBorder | kSunkenFrame);/// cconstructor
   TGVProgressBar(const TGWindow *p, EBarType type, UInt_t h);
/// Simple constructor allow you to create either a standard progress
/// bar, or a more fancy progress bar (fancy means: double sized border,
/// white background and a bit wider to allow for text to be printed
/// in the bar.

   virtual ~TGVProgressBar() { }

   virtual TGDimension GetDefaultSize() const
                     { return TGDimension(fBarWidth, fHeight); }
   virtual void SavePrimitive(std::ostream &out, Option_t *option = "");
   void ShowPos(Bool_t) { }
   void Percent(Bool_t) { }
/// Save a vertical progress bar as a C++ statement(s) on output stream out.
```

## code



## example



<!-- TGProgressBar.md ends here -->
