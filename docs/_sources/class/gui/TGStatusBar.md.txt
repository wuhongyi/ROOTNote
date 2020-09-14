<!-- TGStatusBar.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 一 11月 14 20:08:53 2016 (+0800)
;; Last-Updated: 一 11月 14 20:16:37 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 1
;; URL: http://wuhongyi.cn -->

# TGStatusBar

Provides a StatusBar widget.

TGStatusBar 继承 TGHorizontalFrame ,friend TGStatusBarPart


## class

```cpp
   TGStatusBar(const TGWindow *p = 0, UInt_t w = 4, UInt_t h = 2,
               UInt_t options = kSunkenFrame | kHorizontalFrame,
               Pixel_t back = GetDefaultFrameBackground());
/// Create a status bar widget. By default it consist of one part.
/// Multiple parts can be created using SetParts().

   virtual ~TGStatusBar();/// Delete status bar widget.

   virtual void DrawBorder();/// Draw the status bar border (including cute 3d corner).
   virtual void SetText(TGString *text, Int_t partidx = 0);
/// Set text in partition partidx in status bar. The TGString is
/// adopted by the status bar.

   virtual void SetText(const char *text, Int_t partidx = 0);/// Set text in partion partidx in status bar.
           void AddText(const char *text, Int_t partidx = 0)
                  { SetText(text, partidx); }                  //*MENU*
   const char  *GetText(Int_t partidx = 0) const;/// return text in the part partidx
   virtual void SetParts(Int_t npart);                         //*MENU*
/// Divide the status bar in npart equal sized parts.

   virtual void SetParts(Int_t *parts, Int_t npart);
/// Divide the status bar in nparts. Size of each part is given in parts
/// array (percentual).

   void         Draw3DCorner(Bool_t corner) { f3DCorner = corner; }
   TGCompositeFrame *GetBarPart(Int_t npart) const;
/// Returns bar part. That allows to put in the bar part
/// something more interesting than text ;-)

   TGDimension GetDefaultSize() const;/// Return default size.

   virtual void SavePrimitive(std::ostream &out, Option_t *option = "");
/// Save a status bar widget as a C++ statement(s) on output stream out.
```


## code




## example




<!-- TGStatusBar.md ends here -->
