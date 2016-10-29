<!-- TCanvas.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 11:44:41 2014 (+0800)
;; Last-Updated: 日 9月 25 21:01:35 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 12
;; URL: http://wuhongyi.cn -->

# TCanvas

继承 TPad

A Canvas is an area mapped to a window directly under the control of the display
manager. A ROOT session may have several canvases open at any given time.

A Canvas may be subdivided into independent graphical areas: the __Pads__.
A canvas has a default pad which has the name of the canvas itself.



## class

```cpp
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
   TCanvas(const char *name, const char *title, Int_t ww, Int_t wh);
   TCanvas(const char *name, const char *title, Int_t wtopx, Int_t wtopy,
           Int_t ww, Int_t wh);
   TCanvas(const char *name, Int_t ww, Int_t wh, Int_t winid);
   virtual ~TCanvas();

   //-- used by friend TThread class
   void Constructor();
   void Constructor(const char *name, const char *title, Int_t form);
   void Constructor(const char *name, const char *title, Int_t ww, Int_t wh);
   void Constructor(const char *name, const char *title,
           Int_t wtopx, Int_t wtopy, Int_t ww, Int_t wh);
   void Destructor();

   TVirtualPad      *cd(Int_t subpadnumber=0);
/// Set current canvas & pad. Returns the new current pad,
/// or 0 in case of failure.
/// See TPad::cd() for an explanation of the parameter.

   virtual void      Browse(TBrowser *b);
   void              Clear(Option_t *option="");
// Remove all primitives from the canvas.
// If option "D" is specified, direct subpads are cleared but not deleted.
// This option is not recursive, i.e. pads in direct subpads are deleted.
   
   void              Close(Option_t *option="");
   virtual void      Delete(Option_t * = "") { MayNotUse("Delete()"); }
   void              DisconnectWidget();  // used by TCanvasImp
   virtual void      Draw(Option_t *option="");
   virtual TObject  *DrawClone(Option_t *option="") const; // *MENU*
/// Draw a clone of this canvas
/// A new canvas is created that is a clone of this canvas

   virtual TObject  *DrawClonePad(); // *MENU*
/// Draw a clone of this canvas into the current pad
/// In an interactive session, select the destination/current pad
/// with the middle mouse button, then point to the canvas area to select
/// the canvas context menu item DrawClonePad.
/// Note that the original canvas may have subpads.

   virtual void      EditorBar();
   void              EmbedInto(Int_t winid, Int_t ww, Int_t wh);
   void              EnterLeave(TPad *prevSelPad, TObject *prevSelObj);
   void              FeedbackMode(Bool_t set);
   void              Flush();
   void              UseCurrentStyle(); // *MENU*
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
   Int_t             GetWindowTopX();
   Int_t             GetWindowTopY();
   UInt_t            GetWindowWidth() const { return fWindowWidth; }
   UInt_t            GetWindowHeight() const { return fWindowHeight; }
   UInt_t            GetWw() const { return fCw; }
   UInt_t            GetWh() const { return fCh; }
   virtual void      GetCanvasPar(Int_t &wtopx, Int_t &wtopy, UInt_t &ww, UInt_t &wh)
                     {wtopx=GetWindowTopX(); wtopy=fWindowTopY; ww=fWindowWidth; wh=fWindowHeight;}
   virtual void      HandleInput(EEventType button, Int_t x, Int_t y);
   Bool_t            HasMenuBar() const { return TestBit(kMenuBar); }
   void              Iconify() { fCanvasImp->Iconify(); }
   Bool_t            IsBatch() const { return fBatch; }
   Bool_t            IsDrawn() { return fDrawn; }
   Bool_t            IsFolder() const;
   Bool_t            IsGrayscale();
   Bool_t            IsRetained() const { return fRetained; }
   virtual void      ls(Option_t *option="") const;
   void              MoveOpaque(Int_t set=1);
   Bool_t            OpaqueMoving() const { return TestBit(kMoveOpaque); }
   Bool_t            OpaqueResizing() const { return TestBit(kResizeOpaque); }
   virtual void      Paint(Option_t *option="");
   virtual TPad     *Pick(Int_t px, Int_t py, TObjLink *&pickobj) { return TPad::Pick(px, py, pickobj); }
   virtual TPad     *Pick(Int_t px, Int_t py, TObject *prevSelObj);
   virtual void      Picked(TPad *selpad, TObject *selected, Int_t event);             // *SIGNAL*
   virtual void      ProcessedEvent(Int_t event, Int_t x, Int_t y, TObject *selected); // *SIGNAL*
   virtual void      Selected(TVirtualPad *pad, TObject *obj, Int_t event);            // *SIGNAL*
   virtual void      Cleared(TVirtualPad *pad);                                        // *SIGNAL*
   virtual void      Closed();                                                         // *SIGNAL*
   void              RaiseWindow() { fCanvasImp->RaiseWindow(); }
   void              ResetDrawn() { fDrawn=kFALSE; }
   virtual void      Resize(Option_t *option="");
   void              ResizeOpaque(Int_t set=1);
   void              SaveSource(const char *filename="", Option_t *option="");
// Save primitives in this canvas as a C++ macro file.
// This function loops on all the canvas primitives and for each primitive
// calls the object SavePrimitive function.
// When outputing floating point numbers, the default precision is 7 digits.
// The precision can be changed (via system.rootrc) by changing the value
// of the environment variable "Canvas.SavePrecision"
   
   void              SavePrimitive(std::ostream &out, Option_t *option = "");
   // Save primitives in this canvas in C++ macro file with GUI.
   
   virtual void      SetCursor(ECursor cursor);
   virtual void      SetDoubleBuffer(Int_t mode=1);
   virtual void      SetFixedAspectRatio(Bool_t fixed = kTRUE);  // *TOGGLE*
   void              SetGrayscale(Bool_t set = kTRUE); // *TOGGLE* *GETTER=IsGrayscale
   void              SetWindowPosition(Int_t x, Int_t y) { fCanvasImp->SetWindowPosition(x, y); }
   void              SetWindowSize(UInt_t ww, UInt_t wh) { fCanvasImp->SetWindowSize(ww, wh); }
   void              SetCanvasSize(UInt_t ww, UInt_t wh); // *MENU*
   void              SetHighLightColor(Color_t col) { fHighLightColor = col; }
   void              SetSelected(TObject *obj);
   void              SetClickSelected(TObject *obj) { fClickSelected = obj; }
   void              SetSelectedPad(TPad *pad) { fSelectedPad = pad; }
   void              SetClickSelectedPad(TPad *pad) { fClickSelectedPad = pad; }
   void              Show() { fCanvasImp->Show(); }
   virtual void      Size(Float_t xsizeuser=0, Float_t ysizeuser=0);
   void              SetBatch(Bool_t batch=kTRUE);
   static  void      SetFolder(Bool_t isfolder=kTRUE);
   void              SetPadSave(TPad *pad) {fPadSave = pad;}
   void              SetRetained(Bool_t retained=kTRUE) { fRetained=retained;}
   void              SetTitle(const char *title="");
   virtual void      ToggleEventStatus();
   virtual void      ToggleAutoExec();
   virtual void      ToggleToolBar();
   virtual void      ToggleEditor();
   virtual void      ToggleToolTips();
   virtual void      Update();//刷新画板

   Bool_t              UseGL() const { return fUseGL; }
   void                SetSupportGL(Bool_t support) {fUseGL = support;}
   TVirtualPadPainter *GetCanvasPainter();
   void                DeleteCanvasPainter();

   static TCanvas   *MakeDefCanvas();
   static Bool_t     SupportAlpha();
```



## code

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


<!-- TCanvas.md ends here -->
