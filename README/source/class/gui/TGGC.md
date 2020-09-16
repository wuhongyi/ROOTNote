<!-- TGGC.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 三 11月  9 15:29:49 2016 (+0800)
;; Last-Updated: 三 9月 16 10:58:48 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 3
;; URL: http://wuhongyi.cn -->

# TGGC*

Encapsulate a graphics context used in the low level graphics.       
TGGCPool provides a pool of graphics contexts.

TGGC 继承 TObject, TRefCnt, friend TGGCPool

TGGCPool 继承 TGObject , friend TGGC

## class

**TGGC**

```cpp
   TGGC(GCValues_t *values = 0);/// Create a graphics context, registers GC in GCPool.
   TGGC(const TGGC &g);/// Copy a graphics context.
   virtual ~TGGC();
   TGGC &operator=(const TGGC &rhs);

   GContext_t GetGC() const { return fContext; }
   GContext_t operator()() const;

   void SetAttributes(GCValues_t *values);/// Set attributes as specified in the values structure.
   void SetFunction(EGraphicsFunction v);/// Set graphics context drawing function.
   void SetPlaneMask(ULong_t v);/// Set plane mask.
   void SetForeground(Pixel_t v);/// Set foreground color.
   void SetBackground(Pixel_t v);/// Set background color.
   void SetLineWidth(Int_t v);/// Set line width.
   void SetLineStyle(Int_t v);/// Set line style (kLineSolid, kLineOnOffDash, kLineDoubleDash).
   void SetCapStyle(Int_t v);/// Set cap style (kCapNotLast, kCapButt, kCapRound, kCapProjecting).
   void SetJoinStyle(Int_t v);/// Set line join style (kJoinMiter, kJoinRound, kJoinBevel).
   void SetFillStyle(Int_t v);/// Set fill style (kFillSolid, kFillTiled, kFillStippled, kFillOpaeueStippled).
   void SetFillRule(Int_t v);/// Set fill rule (kEvenOddRule, kWindingRule).
   void SetTile(Pixmap_t v);/// Set tile pixmap for tiling operations.
   void SetStipple(Pixmap_t v);/// Set 1 plane pixmap for stippling.
   void SetTileStipXOrigin(Int_t v);/// X offset for tile or stipple operations.
   void SetTileStipYOrigin(Int_t v);/// Y offset for tile or stipple operations.
   void SetFont(FontH_t v);/// Set font.
   void SetSubwindowMode(Int_t v);/// Set sub window mode (kClipByChildren, kIncludeInferiors).
   void SetGraphicsExposures(Bool_t v);/// True if graphics exposure should be generated.
   void SetClipXOrigin(Int_t v);/// X origin for clipping.
   void SetClipYOrigin(Int_t v);/// Y origin for clipping.
   void SetClipMask(Pixmap_t v);/// Bitmap for clipping.
   void SetDashOffset(Int_t v);/// Patterned/dashed line offset.
   void SetDashList(const char v[], Int_t len);/// Set dash pattern. First use SetDashOffset() if not 0.
   void SetArcMode(Int_t v);/// Set arc mode (kArcChord, kArcPieSlice).

   const GCValues_t *GetAttributes() const { return &fValues; }
   Mask_t            GetMask() const { return fValues.fMask; }
   EGraphicsFunction GetFunction() const { return fValues.fFunction; }
   ULong_t           GetPlaneMask() const { return fValues.fPlaneMask; }
   Pixel_t           GetForeground() const { return fValues.fForeground; }
   Pixel_t           GetBackground() const { return fValues.fBackground; }
   Int_t             GetLineWidth() const { return fValues.fLineWidth; }
   Int_t             GetLineStyle() const { return fValues.fLineStyle; }
   Pixmap_t          GetTile() const { return fValues.fTile; }
   Pixmap_t          GetStipple() const { return fValues.fStipple; }
   Int_t             GetTileStipXOrigin() const { return fValues.fTsXOrigin; }
   Int_t             GetTileStipYOrigin() const { return fValues.fTsYOrigin; }
   Int_t             GetSubwindowMode() const { return fValues.fSubwindowMode; }
   FontH_t           GetFont() const { return fValues.fFont; }
   Bool_t            GetGraphicsExposures() const { return fValues.fGraphicsExposures; }
   Int_t             GetClipXOrigin() const { return fValues.fClipXOrigin; }
   Int_t             GetClipYOrigin() const { return fValues.fClipYOrigin; }
   Pixmap_t          GetClipMask() const { return fValues.fClipMask; }
   Int_t             GetCapStyle() const { return fValues.fCapStyle; }
   Int_t             GetJoinStyle() const { return fValues.fJoinStyle; }
   Int_t             GetFillStyle() const { return fValues.fFillStyle; }
   Int_t             GetFillRule() const { return fValues.fFillRule; }
   Int_t             GetDashOffset() const { return fValues.fDashOffset; }
   Int_t             GetDashLen() const { return fValues.fDashLen; }
   const char       *GetDashes() const { return fValues.fDashes; }
   Int_t             GetArcMode() const { return fValues.fArcMode; }

   void Print(Option_t *option="") const;/// Print graphics contexts info.
   void SavePrimitive(std::ostream &out, Option_t *option = "");
/// Save graphics context info as a C++ statement(s) on output stream out   
```


**TGGCPool**

```cpp
   TGGCPool(TGClient *client);
   virtual ~TGGCPool();

   TGGC *GetGC(GCValues_t *values, Bool_t rw = kFALSE);
/// Get the best matching graphics context depending on values.
/// If rw is false only a readonly, not modifiable graphics context
/// is returned. If rw is true a new modifiable graphics context is
/// returned.

   TGGC *GetGC(GContext_t gct);/// returns graphics context based on its GContext_t handle.
   void  FreeGC(const TGGC *gc);/// Delete graphics context if it is not used anymore.
   void  FreeGC(GContext_t gc);/// Delete graphics context if it is not used anymore.

   TGGC *FindGC(const TGGC *gc);
/// Find graphics context. Returns 0 in case gc is not found.

   TGGC *FindGC(GContext_t gc);
/// Find graphics context based on its GContext_t handle. Returns 0
/// in case gc is not found.

   void  Print(Option_t *option="") const;/// List all graphics contexts in the pool.
```

## code


## example



<!-- TGGC.md ends here -->
