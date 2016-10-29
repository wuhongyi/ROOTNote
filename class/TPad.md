<!-- TPad.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 11:44:41 2014 (+0800)
;; Last-Updated: 六 10月 29 21:42:19 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 23
;; URL: http://wuhongyi.cn -->

# TPad

继承 TVirtualPad, TAttBBox2D

The most important graphics class in the ROOT system.

A Pad is contained in a Canvas.

A Pad may contain other pads (unlimited pad hierarchy).

A pad is a linked list of primitives of any type (graphics objects,
histograms, detectors, tracks, etc.).

Adding a new element into a pad is in general performed by the Draw
member function of the object classes.

It is important to realize that the pad is a linked list of references
to the original object.
For example, in case of a histogram, the histogram.Draw() operation
only stores a reference to the histogram object and not a graphical
representation of this histogram.
When the mouse is used to change (say the bin content), the bin content
of the original histogram is changed.

The convention used in ROOT is that a Draw operation only adds
a reference to the object. The effective drawing is performed
when the canvas receives a signal to be painted.


In ExecuteEvent, move, changes can be performed on the object.

For examples of DistancetoPrimitive and ExecuteEvent functions,
see classes
~~~ {.cpp}
      TLine::DistancetoPrimitive, TLine::ExecuteEvent
      TBox::DistancetoPrimitive,  TBox::ExecuteEvent
      TH1::DistancetoPrimitive,   TH1::ExecuteEvent
~~~
A Pad supports linear and log scales coordinate systems.
The transformation coefficients are explained in TPad::ResizePad.


## class

```cpp
   // TPad status bits
   enum {
      kFraming      = BIT(6),
      kHori         = BIT(9),
      kClipFrame    = BIT(10),
      kPrintingPS   = BIT(11),
      kCannotMove   = BIT(12),
      kClearAfterCR = BIT(14)
   };

   TPad();
   TPad(const char *name, const char *title, Double_t xlow,
        Double_t ylow, Double_t xup, Double_t yup,
        Color_t color=-1, Short_t bordersize=-1, Short_t bordermode=-2);
   virtual ~TPad();
   void              AbsCoordinates(Bool_t set) { fAbsCoord = set; }
   Double_t          AbsPixeltoX(Int_t px) {return fAbsPixeltoXk + px*fPixeltoX;}
   Double_t          AbsPixeltoY(Int_t py) {return fAbsPixeltoYk + py*fPixeltoY;}
   virtual void      AbsPixeltoXY(Int_t xpixel, Int_t ypixel, Double_t &x, Double_t &y);
   virtual void      AddExec(const char *name, const char *command);
   virtual void      AutoExec();
   virtual void      Browse(TBrowser *b);
   virtual TLegend  *BuildLegend(Double_t x1=0.5, Double_t y1=0.67, Double_t x2=0.88, Double_t y2=0.88, const char *title=""); // *MENU*
   TVirtualPad*      cd(Int_t subpadnumber=0); // *MENU*
   void              Clear(Option_t *option="");
   virtual Int_t     Clip(Float_t *x, Float_t *y, Float_t xclipl, Float_t yclipb, Float_t xclipr, Float_t yclipt);
   virtual Int_t     Clip(Double_t *x, Double_t *y, Double_t xclipl, Double_t yclipb, Double_t xclipr, Double_t yclipt);
   virtual Int_t     ClippingCode(Double_t x, Double_t y, Double_t xcl1, Double_t ycl1, Double_t xcl2, Double_t ycl2);
   virtual Int_t     ClipPolygon(Int_t n, Double_t *x, Double_t *y, Int_t nn, Double_t *xc, Double_t *yc, Double_t xclipl, Double_t yclipb, Double_t xclipr, Double_t yclipt);
   virtual void      Close(Option_t *option="");
   virtual void      Closed() { Emit("Closed()"); } // *SIGNAL*
   virtual void      CopyPixmap();
   virtual void      CopyPixmaps();
   virtual void      DeleteExec(const char *name);
   virtual void      Divide(Int_t nx=1, Int_t ny=1, Float_t xmargin=0.01, Float_t ymargin=0.01, Int_t color=0); // *MENU*
   virtual void      DivideSquare(Int_t n, Float_t xmargin=0.01, Float_t ymargin=0.01, Int_t color=0);
   virtual void      Draw(Option_t *option="");
   virtual void      DrawClassObject(const TObject *obj, Option_t *option="");
   static  void      DrawColorTable();
   virtual void      DrawCrosshair();
   TH1F             *DrawFrame(Double_t xmin, Double_t ymin, Double_t xmax, Double_t ymax, const char *title="");
   virtual void      ExecuteEventAxis(Int_t event, Int_t px, Int_t py, TAxis *axis);
   virtual TObject  *FindObject(const char *name) const;
   virtual TObject  *FindObject(const TObject *obj) const;
   virtual void      UseCurrentStyle();  // *MENU*
   virtual Short_t   GetBorderMode() const { return fBorderMode;}
   virtual Short_t   GetBorderSize() const { return fBorderSize;}
   Int_t             GetCrosshair() const;
   virtual Int_t     GetCanvasID() const;
   virtual TCanvasImp *GetCanvasImp() const;
   TFrame           *GetFrame();
   virtual Int_t     GetEvent() const;
   virtual Int_t     GetEventX() const;
   virtual Int_t     GetEventY() const;
   virtual Color_t   GetHighLightColor() const;
   virtual void      GetRange(Double_t &x1, Double_t &y1, Double_t &x2, Double_t &y2);
   virtual void      GetRangeAxis(Double_t &xmin, Double_t &ymin, Double_t &xmax, Double_t &ymax);
   virtual void      GetPadPar(Double_t &xlow, Double_t &ylow, Double_t &xup, Double_t &yup);
   Double_t          GetXlowNDC() const {return fXlowNDC;}
   Double_t          GetYlowNDC() const {return fYlowNDC;}
   Double_t          GetWNDC() const {return fWNDC;}
   Double_t          GetHNDC() const {return fHNDC;}
   virtual UInt_t    GetWw() const;
   virtual UInt_t    GetWh() const;
   Double_t          GetAbsXlowNDC() const {return fAbsXlowNDC;}
   Double_t          GetAbsYlowNDC() const {return fAbsYlowNDC;}
   Double_t          GetAbsWNDC() const {return fAbsWNDC;}
   Double_t          GetAbsHNDC() const {return fAbsHNDC;}
   Double_t          GetAspectRatio() const { return fAspectRatio; }
   Double_t          GetPhi() const   {return fPhi;}
   Double_t          GetTheta() const {return fTheta;}
   Double_t          GetUxmin() const {return fUxmin;}
   Double_t          GetUymin() const {return fUymin;}
   Double_t          GetUxmax() const {return fUxmax;}
   Double_t          GetUymax() const {return fUymax;}
   Bool_t            GetGridx() const {return fGridx;}
   Bool_t            GetGridy() const {return fGridy;}
   Int_t             GetNumber() const {return fNumber;}
   Int_t             GetTickx() const {return fTickx;}
   Int_t             GetTicky() const {return fTicky;}
   Double_t          GetX1() const { return fX1; }
   Double_t          GetX2() const { return fX2; }
   Double_t          GetY1() const { return fY1; }
   Double_t          GetY2() const { return fY2; }
   static Int_t      GetMaxPickDistance();
   TList            *GetListOfPrimitives() const {return fPrimitives;}
   TList            *GetListOfExecs() const {return fExecs;}
   virtual TObject  *GetPrimitive(const char *name) const;  //obsolete, use FindObject instead
   virtual TObject  *GetSelected() const;
   virtual TVirtualPad  *GetPad(Int_t subpadnumber) const;
   virtual TObject  *GetPadPointer() const {return fPadPointer;}
   TVirtualPad      *GetPadSave() const;
   TVirtualPad      *GetSelectedPad() const;
   Int_t             GetGLDevice();
   TView            *GetView() const {return fView;}
   TObject          *GetView3D() const {return fPadView3D;}// Return 3D View of this TPad
   Int_t             GetLogx() const {return fLogx;}
   Int_t             GetLogy() const {return fLogy;}
   Int_t             GetLogz() const {return fLogz;}
   virtual TVirtualPad *GetMother() const {return fMother;}
   const char       *GetName() const {return fName.Data();}
   const char       *GetTitle() const {return fTitle.Data();}
   virtual TCanvas  *GetCanvas() const { return fCanvas; }
   virtual TVirtualPad *GetVirtCanvas() const ;
   virtual TVirtualPadPainter *GetPainter();
   Int_t             GetPadPaint() const {return fPadPaint;}
   Int_t             GetPixmapID() const {return fPixmapID;}
   ULong_t           Hash() const { return fName.Hash(); }
   virtual Bool_t    HasCrosshair() const;
   void              HighLight(Color_t col=kRed, Bool_t set=kTRUE);
   Bool_t            HasFixedAspectRatio() const { return fFixedAspectRatio; }
   virtual Bool_t    IsBatch() const;
   virtual Bool_t    IsEditable() const {return fEditable;}
   Bool_t            IsFolder() const {return kTRUE;}
   Bool_t            IsModified() const {return fModified;}
   virtual Bool_t    IsRetained() const;
   virtual Bool_t    IsVertical() const {return !TestBit(kHori);}
   virtual void      ls(Option_t *option="") const;
   void              Modified(Bool_t flag=1);  // *SIGNAL*   //  Set to true when pad is modified
   virtual Bool_t    OpaqueMoving() const;
   virtual Bool_t    OpaqueResizing() const;
   Double_t          PadtoX(Double_t x) const;
   Double_t          PadtoY(Double_t y) const;
   virtual void      Paint(Option_t *option="");
   void              PaintBox(Double_t x1, Double_t y1, Double_t x2, Double_t y2, Option_t *option="");
   void              PaintFillArea(Int_t n, Float_t *x, Float_t *y, Option_t *option=""); // Obsolete
   void              PaintFillArea(Int_t n, Double_t *x, Double_t *y, Option_t *option="");
   void              PaintFillAreaHatches(Int_t n, Double_t *x, Double_t *y, Int_t FillStyle);
   void              PaintHatches(Double_t dy, Double_t angle, Int_t nn, Double_t *xx, Double_t *yy);
   void              PaintPadFrame(Double_t xmin, Double_t ymin, Double_t xmax, Double_t ymax);
   void              PaintLine(Double_t x1, Double_t y1, Double_t x2, Double_t y2);
   void              PaintLineNDC(Double_t u1, Double_t v1,Double_t u2, Double_t v2);
   void              PaintLine3D(Float_t *p1, Float_t *p2);
   void              PaintLine3D(Double_t *p1, Double_t *p2);
   void              PaintPolyLine(Int_t n, Float_t *x, Float_t *y, Option_t *option="");
   void              PaintPolyLine(Int_t n, Double_t *x, Double_t *y, Option_t *option="");
   void              PaintPolyLine3D(Int_t n, Double_t *p);
   void              PaintPolyLineNDC(Int_t n, Double_t *x, Double_t *y, Option_t *option="");
   void              PaintPolyMarker(Int_t n, Float_t *x, Float_t *y, Option_t *option="");
   void              PaintPolyMarker(Int_t n, Double_t *x, Double_t *y, Option_t *option="");
   virtual void      PaintModified();
   void              PaintText(Double_t x, Double_t y, const char *text);
   void              PaintText(Double_t x, Double_t y, const wchar_t *text);
   void              PaintTextNDC(Double_t u, Double_t v, const char *text);
   void              PaintTextNDC(Double_t u, Double_t v, const wchar_t *text);
   virtual TPad     *Pick(Int_t px, Int_t py, TObjLink *&pickobj);
   Double_t          PixeltoX(Int_t px);
   Double_t          PixeltoY(Int_t py);
   virtual void      PixeltoXY(Int_t xpixel, Int_t ypixel, Double_t &x, Double_t &y);
   virtual void      Pop();  // *MENU*
   virtual void      Print(const char *filename="") const;
   virtual void      Print(const char *filename, Option_t *option);
   virtual void      Range(Double_t x1, Double_t y1, Double_t x2, Double_t y2); // *MENU* *ARGS={x1=>fX1,y1=>fY1,x2=>fX2,y2=>fY2}
   virtual void      RangeChanged() { Emit("RangeChanged()"); } // *SIGNAL*
   virtual void      RangeAxis(Double_t xmin, Double_t ymin, Double_t xmax, Double_t ymax);
   virtual void      RangeAxisChanged() { Emit("RangeAxisChanged()"); } // *SIGNAL*
   virtual void      RecursiveRemove(TObject *obj);
   virtual void      RedrawAxis(Option_t *option="");
   virtual void      ResetView3D(TObject *view=0){fPadView3D=view;}
   virtual void      ResizePad(Option_t *option="");
   virtual void      SaveAs(const char *filename="",Option_t *option="") const; // *MENU*
   virtual void      SetBorderMode(Short_t bordermode) {fBorderMode = bordermode; Modified();} // *MENU*
   virtual void      SetBorderSize(Short_t bordersize) {fBorderSize = bordersize; Modified();} // *MENU*
   void              SetCanvas(TCanvas *c) { fCanvas = c; }
   virtual void      SetCanvasSize(UInt_t ww, UInt_t wh);
   virtual void      SetCrosshair(Int_t crhair=1); // *TOGGLE*
   virtual void      SetCursor(ECursor cursor);
   virtual void      SetDoubleBuffer(Int_t mode=1);
   virtual void      SetDrawOption(Option_t *option="");
   virtual void      SetEditable(Bool_t mode=kTRUE); // *TOGGLE*
   virtual void      SetFixedAspectRatio(Bool_t fixed = kTRUE);  // *TOGGLE*
   virtual void      SetGrid(Int_t valuex = 1, Int_t valuey = 1) {fGridx = valuex; fGridy = valuey; Modified();}
   virtual void      SetGridx(Int_t value = 1) {fGridx = value; Modified();} // *TOGGLE*
   virtual void      SetGridy(Int_t value = 1) {fGridy = value; Modified();} // *TOGGLE*
   virtual void      SetFillStyle(Style_t fstyle);
   virtual void      SetLogx(Int_t value = 1); // *TOGGLE*
   virtual void      SetLogy(Int_t value = 1); // *TOGGLE*
   virtual void      SetLogz(Int_t value = 1); // *TOGGLE*
   virtual void      SetNumber(Int_t number) {fNumber = number;}
   virtual void      SetPad(const char *name, const char *title,
                           Double_t xlow, Double_t ylow, Double_t xup,
                           Double_t yup, Color_t color=35,
                           Short_t bordersize=5, Short_t bordermode=-1);
   virtual void      SetPad(Double_t xlow, Double_t ylow, Double_t xup, Double_t yup);
   virtual void      SetAttFillPS(Color_t color, Style_t style);
   virtual void      SetAttLinePS(Color_t color, Style_t style, Width_t lwidth);
   virtual void      SetAttMarkerPS(Color_t color, Style_t style, Size_t msize);
   virtual void      SetAttTextPS(Int_t align, Float_t angle, Color_t color, Style_t font, Float_t tsize);
   static  void      SetMaxPickDistance(Int_t maxPick=5);
   virtual void      SetName(const char *name) {fName = name;} // *MENU*
   virtual void      SetSelected(TObject *obj);
   virtual void      SetTicks(Int_t valuex = 1, Int_t valuey = 1) {fTickx = valuex; fTicky = valuey; Modified();}
   virtual void      SetTickx(Int_t value = 1) {fTickx = value; Modified();} // *TOGGLE*
   virtual void      SetTicky(Int_t value = 1) {fTicky = value; Modified();} // *TOGGLE*
   virtual void      SetTitle(const char *title="") {fTitle = title;}
   virtual void      SetTheta(Double_t theta=30) {fTheta = theta; Modified();}
   virtual void      SetPhi(Double_t phi=30) {fPhi = phi; Modified();}
   virtual void      SetToolTipText(const char *text, Long_t delayms = 1000);
   virtual void      SetVertical(Bool_t vert=kTRUE);
   virtual void      SetView(TView *view = 0);
   virtual void      SetViewer3D(TVirtualViewer3D *viewer3d) {fViewer3D = viewer3d;}

   virtual void      SetGLDevice(Int_t dev) {fGLDevice = dev;}
   virtual void      SetCopyGLDevice(Bool_t copy) {fCopyGLDevice = copy;}

   virtual void      ShowGuidelines(TObject *object, const Int_t event, const char mode = 'i', const bool cling = true);
   virtual void      Update();
   Int_t             UtoAbsPixel(Double_t u) const {return Int_t(fUtoAbsPixelk + u*fUtoPixel);}
   Int_t             VtoAbsPixel(Double_t v) const {return Int_t(fVtoAbsPixelk + v*fVtoPixel);}
   Int_t             UtoPixel(Double_t u) const;
   Int_t             VtoPixel(Double_t v) const;
   virtual TObject  *WaitPrimitive(const char *pname="", const char *emode="");
   Int_t             XtoAbsPixel(Double_t x) const;
   Int_t             YtoAbsPixel(Double_t y) const;
   Double_t          XtoPad(Double_t x) const;
   Double_t          YtoPad(Double_t y) const;
   Int_t             XtoPixel(Double_t x) const;
   Int_t             YtoPixel(Double_t y) const;
   virtual void      XYtoAbsPixel(Double_t x, Double_t y, Int_t &xpixel, Int_t &ypixel) const;
   virtual void      XYtoPixel(Double_t x, Double_t y, Int_t &xpixel, Int_t &ypixel) const;

   virtual TObject  *CreateToolTip(const TBox *b, const char *text, Long_t delayms);
   virtual void      DeleteToolTip(TObject *tip);
   virtual void      ResetToolTip(TObject *tip);
   virtual void      CloseToolTip(TObject *tip);

   virtual void      x3d(Option_t *type=""); // Depreciated

   virtual TVirtualViewer3D *GetViewer3D(Option_t * type = "");
   virtual Bool_t            HasViewer3D() const { return (fViewer3D); }
   virtual void              ReleaseViewer3D(Option_t * type = "");

   virtual Rectangle_t  GetBBox();
   virtual TPoint       GetBBoxCenter();
   virtual void         SetBBoxCenter(const TPoint &p);
   virtual void         SetBBoxCenterX(const Int_t x);
   virtual void         SetBBoxCenterY(const Int_t y);
   virtual void         SetBBoxX1(const Int_t x);
   virtual void         SetBBoxX2(const Int_t x);
   virtual void         SetBBoxY1(const Int_t y);
   virtual void         SetBBoxY2(const Int_t y);

   virtual void      RecordPave(const TObject *obj);              // *SIGNAL*
   virtual void      RecordLatex(const TObject *obj);             // *SIGNAL*
   virtual void      EventPave() { Emit("EventPave()"); }         // *SIGNAL*
   virtual void      StartEditing() { Emit("StartEditing()"); }   // *SIGNAL*
```


## code

```cpp
//图片修饰
gPad->SetTickx(1);//上边框有刻度
gPad->SetTicky(1);//右边框有刻度
gPad->SetTickx(2);//上边框有刻度和数值
gPad->SetTicky(2);//右边框有刻度和数值



TPad* pad1 = new TPad("pad1","pad1",0.03,0.62,0.50,0.92,32);//x起点，y起点，x终点，y终点，颜色
pad1->Draw();
pad1->cd();
pad1->SetLogy();//y轴 对数坐标
pad1->SetGridy();//y轴 网格
pad2->SetLogx();
pad2->SetGridx();
```

## example



<!-- TPad.md ends here -->
