<!-- TCanvas.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 11:44:41 2014 (+0800)
;; Last-Updated: 三 9月 16 12:50:27 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 20
;; URL: http://wuhongyi.cn -->

# TCanvas*

继承 TPad

A Canvas is an area mapped to a window directly under the control of the display
manager. A ROOT session may have several canvases open at any given time.

A Canvas may be subdivided into independent graphical areas: the __Pads__.
A canvas has a default pad which has the name of the canvas itself.



## class

```cpp
public:
   // TCanvas status bits
   enum {
      kShowEventStatus  = BIT(15),
      kAutoExec         = BIT(16),
      kMenuBar          = BIT(17),
      kShowToolBar      = BIT(18),
      kShowEditor       = BIT(19),
      kMoveOpaque       = BIT(20),
      kResizeOpaque     = BIT(21),
      kIsGrayscale      = BIT(22),
      kShowToolTips     = BIT(23)
   };

   TCanvas(Bool_t build=kTRUE);
   TCanvas(const char *name, const char *title="", Int_t form=1);
/// Create a new canvas with a predefined size form.
/// If form < 0  the menubar is not shown.
/// - form = 1    700x500 at 10,10 (set by TStyle::SetCanvasDefH,W,X,Y)
/// - form = 2    500x500 at 20,20
/// - form = 3    500x500 at 30,30
/// - form = 4    500x500 at 40,40
/// - form = 5    500x500 at 50,50
/// If "name" starts with "gl" the canvas is ready to receive GL output.

   TCanvas(const char *name, const char *title, Int_t ww, Int_t wh);
/// Create a new canvas at a random position.
/// \param[in] name    canvas name
/// \param[in] title   canvas title
/// \param[in] ww      is the canvas size in pixels along X
///                    (if ww < 0  the menubar is not shown)
/// \param[in] wh      is the canvas size in pixels along Y
/// If "name" starts with "gl" the canvas is ready to receive GL output.

   TCanvas(const char *name, const char *title, Int_t wtopx, Int_t wtopy,
           Int_t ww, Int_t wh);
/// Create a new canvas.
/// \param[in] name         canvas name
/// \param[in] title        canvas title
/// \param[in] wtopx,wtopy  are the pixel coordinates of the top left corner of
///                         the canvas  (if wtopx < 0) the menubar is not shown)
/// \param[in] ww           is the canvas size in pixels along X
/// \param[in] wh           is the canvas size in pixels along Y
/// If "name" starts with "gl" the canvas is ready to receive GL output.

   TCanvas(const char *name, Int_t ww, Int_t wh, Int_t winid);
/// Create an embedded canvas, i.e. a canvas that is in a TGCanvas widget
/// which is placed in a TGFrame. This ctor is only called via the
/// TRootEmbeddedCanvas class.
/// If "name" starts with "gl" the canvas is ready to receive GL output.

   virtual ~TCanvas();

   //-- used by friend TThread class
   void Constructor();
   void Constructor(const char *name, const char *title, Int_t form);
/// Create a new canvas with a predefined size form.
/// If form < 0  the menubar is not shown.
/// - form = 1    700x500 at 10,10 (set by TStyle::SetCanvasDefH,W,X,Y)
/// - form = 2    500x500 at 20,20
/// - form = 3    500x500 at 30,30
/// - form = 4    500x500 at 40,40
/// - form = 5    500x500 at 50,50

   void Constructor(const char *name, const char *title, Int_t ww, Int_t wh);
/// Create a new canvas at a random position.
/// \param[in] name    canvas name
/// \param[in] title   canvas title
/// \param[in] ww      is the canvas size in pixels along X
///                    (if ww < 0  the menubar is not shown)
/// \param[in] wh      is the canvas size in pixels along Y

   void Constructor(const char *name, const char *title,
           Int_t wtopx, Int_t wtopy, Int_t ww, Int_t wh);
/// Create a new canvas.
/// \param[in] name         canvas name
/// \param[in] title        canvas title
/// \param[in] wtopx,wtopy  are the pixel coordinates of the top left corner of
///                         the canvas  (if wtopx < 0) the menubar is not shown)
/// \param[in] ww           is the canvas size in pixels along X
/// \param[in] wh           is the canvas size in pixels along Y

   void Destructor();/// Actual canvas destructor.

   TVirtualPad      *cd(Int_t subpadnumber=0);
/// Set current canvas & pad. Returns the new current pad,
/// or 0 in case of failure.
/// See TPad::cd() for an explanation of the parameter.

   virtual void      Browse(TBrowser *b);
   void              Clear(Option_t *option="");
// Remove all primitives from the canvas.
// If option "D" is specified, direct subpads are cleared but not deleted.
// This option is not recursive, i.e. pads in direct subpads are deleted.
   
   void              Close(Option_t *option="");/// Close canvas. Delete window/pads data structure
   virtual void      Delete(Option_t * = "") { MayNotUse("Delete()"); }
   void              DisconnectWidget();  // used by TCanvasImp  /// Used by friend class TCanvasImp.
   virtual void      Draw(Option_t *option="");
/// Draw a canvas.
/// If a canvas with the name is already on the screen, the canvas is repainted.
/// This function is useful when a canvas object has been saved in a Root file.

   virtual TObject  *DrawClone(Option_t *option="") const; // *MENU*
/// Draw a clone of this canvas
/// A new canvas is created that is a clone of this canvas

   virtual TObject  *DrawClonePad(); // *MENU*
/// Draw a clone of this canvas into the current pad
/// In an interactive session, select the destination/current pad
/// with the middle mouse button, then point to the canvas area to select
/// the canvas context menu item DrawClonePad.
/// Note that the original canvas may have subpads.

   virtual void      EditorBar();/// Get editor bar.
   void              EmbedInto(Int_t winid, Int_t ww, Int_t wh);
/// Embedded a canvas into a TRootEmbeddedCanvas. This method is only called
/// via TRootEmbeddedCanvas::AdoptCanvas.

   void              EnterLeave(TPad *prevSelPad, TObject *prevSelObj);
/// Generate kMouseEnter and kMouseLeave events depending on the previously
/// selected object and the currently selected object. Does nothing if the
/// selected object does not change.

   void              FeedbackMode(Bool_t set);/// Turn rubberband feedback mode on or off.
   void              Flush();/// Flush canvas buffers.
   void              UseCurrentStyle(); // *MENU* /// Force a copy of current style for all objects in canvas.
   void              ForceUpdate() { fCanvasImp->ForceUpdate(); }
   const char       *GetDISPLAY() const {return fDISPLAY.Data();}
   TContextMenu     *GetContextMenu() const {return fContextMenu;};
   Int_t             GetDoubleBuffer() const {return fDoubleBuffer;}
   Int_t             GetEvent() const { return fEvent; }
   Int_t             GetEventX() const { return fEventX; }
   Int_t             GetEventY() const { return fEventY; }
   Color_t           GetHighLightColor() const { return fHighLightColor; }
   TVirtualPad      *GetPadSave() const { return fPadSave; }
   void              ClearPadSave() { fPadSave = 0; }
   TObject          *GetSelected() const {return fSelected;}
   TObject          *GetClickSelected() const {return fClickSelected;}
   Int_t             GetSelectedX() const {return fSelectedX;}
   Int_t             GetSelectedY() const {return fSelectedY;}
   Option_t         *GetSelectedOpt() const {return fSelectedOpt.Data();}
   TVirtualPad      *GetSelectedPad() const { return fSelectedPad; }
   TVirtualPad      *GetClickSelectedPad() const { return fClickSelectedPad; }
   Bool_t            GetShowEventStatus() const { return TestBit(kShowEventStatus); }
   Bool_t            GetShowToolBar() const { return TestBit(kShowToolBar); }
   Bool_t            GetShowEditor() const { return TestBit(kShowEditor); }
   Bool_t            GetShowToolTips() const { return TestBit(kShowToolTips); }
   Bool_t            GetAutoExec() const { return TestBit(kAutoExec); }
   Size_t            GetXsizeUser() const {return fXsizeUser;}
   Size_t            GetYsizeUser() const {return fYsizeUser;}
   Size_t            GetXsizeReal() const {return fXsizeReal;}
   Size_t            GetYsizeReal() const {return fYsizeReal;}
   Int_t             GetCanvasID() const {return fCanvasID;}
   TCanvasImp       *GetCanvasImp() const {return fCanvasImp;}
   Int_t             GetWindowTopX();/// Returns current top x position of window on screen.
   Int_t             GetWindowTopY();/// Returns current top y position of window on screen.
   UInt_t            GetWindowWidth() const { return fWindowWidth; }
   UInt_t            GetWindowHeight() const { return fWindowHeight; }
   UInt_t            GetWw() const { return fCw; }
   UInt_t            GetWh() const { return fCh; }
   virtual void      GetCanvasPar(Int_t &wtopx, Int_t &wtopy, UInt_t &ww, UInt_t &wh)
                     {wtopx=GetWindowTopX(); wtopy=fWindowTopY; ww=fWindowWidth; wh=fWindowHeight;}
   virtual void      HandleInput(EEventType button, Int_t x, Int_t y);
/// Handle Input Events.
/// Handle input events, like button up/down in current canvas.

   Bool_t            HasMenuBar() const { return TestBit(kMenuBar); }
   void              Iconify() { fCanvasImp->Iconify(); }
   Bool_t            IsBatch() const { return fBatch; }
   Bool_t            IsDrawn() { return fDrawn; }
   Bool_t            IsFolder() const;/// Is folder ?
   Bool_t            IsGrayscale();/// Check whether this canvas is to be drawn in grayscale mode.
   Bool_t            IsRetained() const { return fRetained; }
   virtual void      ls(Option_t *option="") const;/// List all pads.
   void              MoveOpaque(Int_t set=1);
/// Set option to move objects/pads in a canvas.
///  - set = 1 (default) graphics objects are moved in opaque mode
///  - set = 0 only the outline of objects is drawn when moving them
/// The option opaque produces the best effect. It requires however a
/// a reasonably fast workstation or response time.

   Bool_t            OpaqueMoving() const { return TestBit(kMoveOpaque); }
   Bool_t            OpaqueResizing() const { return TestBit(kResizeOpaque); }
   virtual void      Paint(Option_t *option="");/// Paint canvas.
   virtual TPad     *Pick(Int_t px, Int_t py, TObjLink *&pickobj) { return TPad::Pick(px, py, pickobj); }
   virtual TPad     *Pick(Int_t px, Int_t py, TObject *prevSelObj);
/// Prepare for pick, call TPad::Pick() and when selected object
/// is different from previous then emit Picked() signal.

   virtual void      Picked(TPad *selpad, TObject *selected, Int_t event);             // *SIGNAL*
/// Emit Picked() signal.

   virtual void      ProcessedEvent(Int_t event, Int_t x, Int_t y, TObject *selected); // *SIGNAL*
/// Emit ProcessedEvent() signal.

   virtual void      Selected(TVirtualPad *pad, TObject *obj, Int_t event);            // *SIGNAL*
/// Emit Selected() signal.

   virtual void      Cleared(TVirtualPad *pad);                                        // *SIGNAL*
/// Emit pad Cleared signal.

   virtual void      Closed();                                                         // *SIGNAL*
/// Emit Closed signal.

   void              RaiseWindow() { fCanvasImp->RaiseWindow(); }
   void              ResetDrawn() { fDrawn=kFALSE; }
   virtual void      Resize(Option_t *option="");/// Recompute canvas parameters following a X11 Resize.
   void              ResizeOpaque(Int_t set=1);
/// Set option to resize objects/pads in a canvas.
///  - set = 1 (default) graphics objects are resized in opaque mode
///  - set = 0 only the outline of objects is drawn when resizing them
/// The option opaque produces the best effect. It requires however a
/// a reasonably fast workstation or response time.

   void              SaveSource(const char *filename="", Option_t *option="");
// Save primitives in this canvas as a C++ macro file.
// This function loops on all the canvas primitives and for each primitive
// calls the object SavePrimitive function.
// When outputing floating point numbers, the default precision is 7 digits.
// The precision can be changed (via system.rootrc) by changing the value
// of the environment variable "Canvas.SavePrecision"
   
   void              SavePrimitive(std::ostream &out, Option_t *option = "");
   // Save primitives in this canvas in C++ macro file with GUI.
   
   virtual void      SetCursor(ECursor cursor);/// Set cursor.
   virtual void      SetDoubleBuffer(Int_t mode=1);/// Set Double Buffer On/Off.
   virtual void      SetFixedAspectRatio(Bool_t fixed = kTRUE);  // *TOGGLE*
/// Fix canvas aspect ratio to current value if fixed is true.

   void              SetGrayscale(Bool_t set = kTRUE); // *TOGGLE* *GETTER=IsGrayscale
/// Set whether this canvas should be painted in grayscale, and re-paint
/// it if necessary.

   void              SetWindowPosition(Int_t x, Int_t y) { fCanvasImp->SetWindowPosition(x, y); }
   void              SetWindowSize(UInt_t ww, UInt_t wh) { fCanvasImp->SetWindowSize(ww, wh); }
   void              SetCanvasSize(UInt_t ww, UInt_t wh); // *MENU*
/// Set Width and Height of canvas to ww and wh respectively. If ww and/or wh
/// are greater than the current canvas window a scroll bar is automatically
/// generated. Use this function to zoom in a canvas and navigate via
/// the scroll bars. The Width and Height in this method are different from those
/// given in the TCanvas constructors where these two dimension include the size
/// of the window decoration whereas they do not in this method.

   void              SetHighLightColor(Color_t col) { fHighLightColor = col; }
   void              SetSelected(TObject *obj);/// Set selected canvas.
   void              SetClickSelected(TObject *obj) { fClickSelected = obj; }
   void              SetSelectedPad(TPad *pad) { fSelectedPad = pad; }
   void              SetClickSelectedPad(TPad *pad) { fClickSelectedPad = pad; }
   void              Show() { fCanvasImp->Show(); }
   virtual void      Size(Float_t xsizeuser=0, Float_t ysizeuser=0);
/// Set the canvas scale in centimeters.
/// This information is used by PostScript to set the page size.
/// \param[in] xsize   size of the canvas in centimeters along X
/// \param[in] ysize   size of the canvas in centimeters along Y
///  if xsize and ysize are not equal to 0, then the scale factors will
///  be computed to keep the ratio ysize/xsize independently of the canvas
///  size (parts of the physical canvas will be unused).
///  if xsize = 0 and ysize is not zero, then xsize will be computed
///     to fit to the current canvas scale. If the canvas is resized,
///     a new value for xsize will be recomputed. In this case the aspect
///     ratio is not preserved.
///  if both xsize = 0 and ysize = 0, then the scaling is automatic.
///  the largest dimension will be allocated a size of 20 centimeters.

   void              SetBatch(Bool_t batch=kTRUE);
/// Toggle batch mode. However, if the canvas is created without a window
/// then batch mode always stays set.

   static  void      SetFolder(Bool_t isfolder=kTRUE);
/// If isfolder=kTRUE, the canvas can be browsed like a folder
/// by default a canvas is not browsable.

   void              SetPadSave(TPad *pad) {fPadSave = pad;}
   void              SetRetained(Bool_t retained=kTRUE) { fRetained=retained;}
   void              SetTitle(const char *title="");/// Set canvas title.
   virtual void      ToggleEventStatus();/// Toggle event statusbar.
   virtual void      ToggleAutoExec();/// Toggle pad auto execution of list of TExecs.
   virtual void      ToggleToolBar();/// Toggle toolbar.
   virtual void      ToggleEditor();/// Toggle editor.
   virtual void      ToggleToolTips();/// Toggle tooltip display.
   virtual void      Update();/// Update canvas pad buffers.  刷新画板

   Bool_t              UseGL() const { return fUseGL; }
   void                SetSupportGL(Bool_t support) {fUseGL = support;}
   TVirtualPadPainter *GetCanvasPainter();/// Access and (probably) creation of pad painter.
   void                DeleteCanvasPainter();///assert on IsBatch() == false?

   static TCanvas   *MakeDefCanvas();/// Static function to build a default canvas.
   static Bool_t     SupportAlpha();/// Static function returning "true" if transparency is supported.
```



## code

```cpp
//判断画板是否已经存在
  TCanvas *c = ((TCanvas *)(gROOT->GetListOfCanvases()->FindObject("c")));
  if (c) { c->Clear(); } else { c = new TCanvas("c", "c"); }
```


```cpp
TCanvas *MyC = new TCanvas("MyC","Test canvas",1)     //新建画板
MyC->SetFillColor(42);                                //设置画板背景颜色
MyC->Divide(2,2);                                     //将画板分成2*2四个区域
MyC->cd(1);                                           //指向第一个区域
f1->Draw();                                           //在第一个区域画图f1

MyC->SaveAs("");

TH1* hc = (TH1*)f1->Clone();                          //克隆直方图

//设置画板
TCanvas *c1 = new TCanvas("c1","画板标题在这",200,10,700,700);	
TCanvas *c1 = new TCanvas("c1","画板标题在这",900,700);

c1->Divide(2,2);//将画板分成四份，2*2	
c1->SetFillColor(40);//设置画板背景颜色


TCanvas *canv = new TCanvas("image", "ccc");
canv->ToggleEventStatus();
canv->SetRightMargin(0.2);
canv->SetLeftMargin(0.01);
canv->SetTopMargin(0.01);
canv->SetBottomMargin(0.01);
```

```cpp
// At creation time, no matter if in interactive or batch mode, the canvas size
// defines the size of the canvas window (including the size of the window
// manager's decoration). To define precisely the graphics area size of a canvas in
// the interactive mode, the following four lines of code should be used:

      Double_t w = 600;
      Double_t h = 600;
      TCanvas * c1 = new TCanvas("c", "c", w, h);
      c->SetWindowSize(w + (w - c->GetWw()), h + (h - c->GetWh()));

// and in the batch mode simply do:

      c->SetCanvasSize(w,h);
```


```cpp
// 不能手动关闭画板
((TRootCanvas *)c1->GetCanvasImp())->SetMWMHints(kMWMDecorAll, kMWMFuncResize | kMWMFuncMaximize | kMWMFuncMinimize | kMWMFuncMove, kMWMInputModeless);
```


## example

```cpp
Canvas *statsEditing() {
//    - how to remove a stat element from the stat box 
//    - how to add a new one
//如何除去图上右上角box中的信息已经添加信息

   // Create and plot a test histogram with stats
   TCanvas *se = new TCanvas;
   TH1F *h = new TH1F("h","test",100,-3,3);
   h->FillRandom("gaus",3000);
   gStyle->SetOptStat();
   h->Draw();
   se->Update();

   // Retrieve the stat box
   TPaveStats *ps = (TPaveStats*)se->GetPrimitive("stats");
   ps->SetName("mystats");
   TList *list = ps->GetListOfLines();

   // Remove the RMS line
   TText *tconst = ps->GetLineWith("RMS");
   list->Remove(tconst);

   // Add a new line in the stat box.
   // Note that "=" is a control character
   TLatex *myt = new TLatex(0,0,"Test = 10");
   myt ->SetTextFont(42);
   myt ->SetTextSize(0.04);
   myt ->SetTextColor(kRed);
   list->Add(myt);

   // the following line is needed to avoid that the automatic redrawing of stats
   h->SetStats(0);

   se->Modified();
   return se;
}

```







```cpp
// Event
   // kNoEvent       =  0,
   // kButton1Down   =  1, kButton2Down   =  2, kButton3Down   =  3, kKeyDown  =  4,
   // kWheelUp       =  5, kWheelDown     =  6, kButton1Shift  =  7, kButton1ShiftMotion  =  8,
   // kButton1Up     = 11, kButton2Up     = 12, kButton3Up     = 13, kKeyUp    = 14,
   // kButton1Motion = 21, kButton2Motion = 22, kButton3Motion = 23, kKeyPress = 24,
   // kArrowKeyPress = 25, kArrowKeyRelease = 26,
   // kButton1Locate = 41, kButton2Locate = 42, kButton3Locate = 43, kESC      = 27,
   // kMouseMotion   = 51, kMouseEnter    = 52, kMouseLeave    = 53,
   // kButton1Double = 61, kButton2Double = 62, kButton3Double = 63

#include "TObject.h"
#include "TH1.h"
#include "TPad.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TRandom.h"
#include <iostream>
using namespace std;

void DynamicExec()
{
  // int pe = gPad->GetEvent();


  
  TObject *select = gPad->GetSelected();
  if(!select) return;

  // 拿到鼠标放置位置的TH1
  if (!select->InheritsFrom(TH1::Class())) {gPad->SetUniqueID(0); return;}
  TH1 *h = (TH1*)select;
  gPad->GetCanvas()->FeedbackMode(kTRUE);

  
  //erase old position and draw a line at current position
  int pold = gPad->GetUniqueID();
  int px = gPad->GetEventX();
  int py = gPad->GetEventY();
  float uxmin = gPad->GetUxmin();
  float uxmax = gPad->GetUxmax();
  float uymin = gPad->GetUymin();
  float uymax = gPad->GetUymax();
  int pxmin = gPad->XtoAbsPixel(uxmin);
  int pxmax = gPad->XtoAbsPixel(uxmax);
  int pymin = gPad->YtoAbsPixel(uymin);
  int pymax = gPad->YtoAbsPixel(uymax);


  // 画出本画板的线
  if(pold) gVirtualX->DrawLine(pold,pymin,pold,pymax);
  gVirtualX->DrawLine(px,pymin,px,pymax);
  gPad->SetUniqueID(px);
  Float_t upx = gPad->AbsPixeltoX(px);
  Float_t x = gPad->PadtoX(upx);

  // 当前TH1 x位置坐标
  cout<<px<<endl;

  // 当前指向的子画板
  // cout<<gPad->GetName()<<endl;

  // 取得最外面的画板 c1
  // cout<<gPad->GetMother()<<endl;

  // gPad->GetMother()->cd(1)->GetListOfPrimitives()->Last()->Print();


  // 画出第一个画板的线
  gPad->GetMother()->cd(1);
  TLine *ll;
  if(gPad->GetMother()->cd(1)->GetListOfPrimitives()->FindObject("TLine"))
    {
      TLine *lll =(TLine*)gPad->GetMother()->cd(1)->GetListOfPrimitives()->FindObject("TLine");
      lll->PaintLine(x,gPad->GetMother()->cd(1)->GetUymin(),x,gPad->GetMother()->cd(1)->GetUymax());      
    }
  else
    {
      ll = new TLine;
      ll->PaintLine(x,gPad->GetMother()->cd(1)->GetUymin(),x,gPad->GetMother()->cd(1)->GetUymax());
    }
    
  

  gPad->GetMother()->Update();
    
}

void dynamic()
{
  TCanvas* c1 = new TCanvas("c1","c1");
  TH1D *h1 = new TH1D("h1","",4096,0,2048);
  TH1D *h2 = new TH1D("h2","",4096,0,2048);

  Double_t px,py;
  for (Int_t i = 0; i < 50000; i++)
    {
      gRandom->Rannor(px,py);
       
      h1->Fill(px*100+1024);
      h2->Fill(py*200+1024);
    }


  c1->Divide(1,2);

  c1->cd(1);
  h1->Draw();
  c1->cd(2);
  h2->Draw();

  
  // 开启画板响应
  c1->cd(2)->AddExec("asasdsfdgdggd","DynamicExec()");
  // 关闭画板响应
  // c1->cd(2)->DeleteExec("asasdsfdgdggd");
}
```



<!-- TCanvas.md ends here -->
