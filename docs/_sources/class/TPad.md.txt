<!-- TPad.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 11:44:41 2014 (+0800)
;; Last-Updated: 三 9月 16 12:50:17 2020 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 31
;; URL: http://wuhongyi.cn -->

# TPad*

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
/// Pad constructor.
///  A pad is a linked list of primitives.
///  A pad is contained in a canvas. It may contain other pads.
///  A pad has attributes. When a pad is created, the attributes
///  defined in the current style are copied to the pad attributes.
/// \param[in] name        pad name
/// \param[in] title       pad title
/// \param[in] xlow [0,1]  is the position of the bottom left point of the pad
///             expressed  in the mother pad reference system
/// \param[in] ylow [0,1]  is the Y position of this point.
/// \param[in] xup  [0,1]  is the x position of the top right point of the pad
///                        expressed in the mother pad reference system
/// \param[in] yup  [0,1]  is the Y position of this point.
/// \param[in] color       pad color
/// \param[in] bordersize  border size in pixels
/// \param[in] bordermode  border mode
///                        - bordermode = -1 box looks as it is behind the screen
///                        - bordermode = 0  no special effects
///                        - bordermode = 1  box looks as it is in front of the screen

   virtual ~TPad();
   void              AbsCoordinates(Bool_t set) { fAbsCoord = set; }
   Double_t          AbsPixeltoX(Int_t px) {return fAbsPixeltoXk + px*fPixeltoX;}
   Double_t          AbsPixeltoY(Int_t py) {return fAbsPixeltoYk + py*fPixeltoY;}
   virtual void      AbsPixeltoXY(Int_t xpixel, Int_t ypixel, Double_t &x, Double_t &y);
   virtual void      AddExec(const char *name, const char *command);
/// Add a new TExec object to the list of Execs.
/// When an event occurs in the pad (mouse click, etc) the list of C++ commands
/// in the list of Execs are executed via TPad::AutoExec.
/// When a pad event occurs (mouse move, click, etc) all the commands
/// contained in the fExecs list are executed in the order found in the list.
/// This facility is activated by default. It can be deactivated by using
/// the canvas "Option" menu.
/// When moving the mouse in the canvas, a second canvas shows the
/// projection along X of the bin corresponding to the Y position
/// of the mouse. The resulting histogram is fitted with a gaussian.
/// A "dynamic" line shows the current bin position in Y.
/// This more elaborated example can be used as a starting point
/// to develop more powerful interactive applications exploiting the C++
/// interpreter as a development engine.

   virtual void      AutoExec();/// Execute the list of Execs when a pad event occurs.
   virtual void      Browse(TBrowser *b);/// Browse pad.
   virtual TLegend  *BuildLegend(Double_t x1=0.5, Double_t y1=0.67, Double_t x2=0.88, Double_t y2=0.88, const char *title=""); // *MENU*
/// Build a legend from the graphical objects in the pad
/// A simple method to build automatically a TLegend from the
/// primitives in a TPad. Only those deriving from TAttLine,
/// TAttMarker and TAttFill are added, excluding TPave and TFrame
/// derived classes. x1, y1, x2, y2 are the TLegend coordinates.
/// title is the legend title. By default it is " ". The caller
/// program owns the returned TLegend.
/// If the pad contains some TMultiGraph or THStack the individual
/// graphs or histograms in them are added to the TLegend.

   TVirtualPad*      cd(Int_t subpadnumber=0); // *MENU*
/// Set Current pad.
/// When a canvas/pad is divided via TPad::Divide, one can directly
/// set the current path to one of the subdivisions.
/// See TPad::Divide for the convention to number sub-pads.
/// Returns the new current pad, or 0 in case of failure.
///  Note1:  c1.cd() is equivalent to c1.cd(0) and sets the current pad
///          to c1 itself.
///  Note2:  after a statement like c1.cd(6), the global variable gPad
///          points to the current pad. One can use gPad to set attributes
///          of the current pad.
///  Note3:  One can get a pointer to one of the sub-pads of pad with:
///          TPad *subpad = (TPad*)pad->GetPad(subpadnumber);

   void              Clear(Option_t *option="");
/// Delete all pad primitives.
/// If the bit kClearAfterCR has been set for this pad, the Clear function
/// will execute only after having pressed a CarriageReturn
/// Set the bit with mypad->SetBit(TPad::kClearAfterCR)

   virtual Int_t     Clip(Float_t *x, Float_t *y, Float_t xclipl, Float_t yclipb, Float_t xclipr, Float_t yclipt);
/// Clipping routine: Cohen Sutherland algorithm.
///  - If Clip ==2 the segment is outside the boundary.
///  - If Clip ==1 the segment has one point outside the boundary.
///  - If Clip ==0 the segment is inside the boundary.
/// \param[in]  x[],y[]                       Segment coordinates (2 points)
/// \param[in]  xclipl,yclipb,xclipr,yclipt   Clipping boundary
/// \param[out] x[],y[]                       New segment coordinates( 2 points)

   virtual Int_t     Clip(Double_t *x, Double_t *y, Double_t xclipl, Double_t yclipb, Double_t xclipr, Double_t yclipt);
/// Clipping routine: Cohen Sutherland algorithm.
///  - If Clip ==2 the segment is outside the boundary.
///  - If Clip ==1 the segment has one point outside the boundary.
///  - If Clip ==0 the segment is inside the boundary.
/// \param[in]  x[],y[]                       Segment coordinates (2 points)
/// \param[in]  xclipl,yclipb,xclipr,yclipt   Clipping boundary
/// \param[out] x[],y[]                       New segment coordinates(2 points)

   virtual Int_t     ClippingCode(Double_t x, Double_t y, Double_t xcl1, Double_t ycl1, Double_t xcl2, Double_t ycl2);/// Compute the endpoint codes for TPad::Clip.
   virtual Int_t     ClipPolygon(Int_t n, Double_t *x, Double_t *y, Int_t nn, Double_t *xc, Double_t *yc, Double_t xclipl, Double_t yclipb, Double_t xclipr, Double_t yclipt);
/// Clip polygon using the Sutherland-Hodgman algorithm.
/// \param[in]  n                            Number of points in the polygon to
///                                          be clipped
/// \param[in]  x[n],y[n]                    Polygon do be clipped vertices
/// \param[in]  xclipl,yclipb,xclipr,yclipt  Clipping boundary
/// \param[out] nn                           Number of points in xc and yc
/// \param[out] xc,yc                        Clipped polygon vertices. The Int_t
///                                          returned by this function is
///                                          the number of points in the clipped
///                                          polygon. These vectors must
///                                          be allocated by the calling function.
///                                          A size of 2*n for each is
///                                          enough.
/// Sutherland and Hodgman's polygon-clipping algorithm uses a divide-and-conquer
/// strategy: It solves a series of simple and identical problems that, when
/// combined, solve the overall problem. The simple problem is to clip a polygon
/// against a single infinite clip edge. Four clip edges, each defining one boundary
/// of the clip rectangle, successively clip a polygon against a clip rectangle.
///
/// Steps of Sutherland-Hodgman's polygon-clipping algorithm:
/// * Polygons can be clipped against each edge of the window one at a time.
///   Windows/edge intersections, if any, are easy to find since the X or Y coordinates
///   are already known.
/// * Vertices which are kept after clipping against one window edge are saved for
///   clipping against the remaining edges.
/// * Note that the number of vertices usually changes and will often increases.
/// The clip boundary determines a visible and invisible region. The edges from
/// vertex i to vertex i+1 can be one of four types:
/// * Case 1 : Wholly inside visible region - save endpoint
/// * Case 2 : Exit visible region - save the intersection
/// * Case 3 : Wholly outside visible region - save nothing
/// * Case 4 : Enter visible region - save intersection and endpoint

   virtual void      Close(Option_t *option="");
/// Delete all primitives in pad and pad itself.
/// Pad cannot be used anymore after this call.
/// Emits signal Closed().

   virtual void      Closed() { Emit("Closed()"); } // *SIGNAL*
   virtual void      CopyPixmap();/// Copy the pixmap of the pad to the canvas.
   virtual void      CopyPixmaps();/// Copy the sub-pixmaps of the pad to the canvas.
   virtual void      DeleteExec(const char *name);/// Remove TExec name from the list of Execs.
   virtual void      Divide(Int_t nx=1, Int_t ny=1, Float_t xmargin=0.01, Float_t ymargin=0.01, Int_t color=0); // *MENU*
/// Automatic pad generation by division.
///  - The current canvas is divided in nx by ny equal divisions (pads).
///  - xmargin is the space along x between pads in percent of canvas.
///  - ymargin is the space along y between pads in percent of canvas.
///  - color is the color of the new pads. If 0, color is the canvas color.
/// Pads are automatically named canvasname_n where n is the division number
/// starting from top left pad.

   virtual void      DivideSquare(Int_t n, Float_t xmargin=0.01, Float_t ymargin=0.01, Int_t color=0);
/// "n" is the total number of sub-pads. The number of sub-pads along the X
/// and Y axis are computed according to the square root of n.

   virtual void      Draw(Option_t *option="");/// Draw Pad in Current pad (re-parent pad if necessary).
   virtual void      DrawClassObject(const TObject *obj, Option_t *option="");
/// Draw class inheritance tree of the class to which obj belongs.
/// If a class B inherits from a class A, description of B is drawn
/// on the right side of description of A.
/// Member functions overridden by B are shown in class A with a blue line
/// crossing-out the corresponding member function.

   static  void      DrawColorTable();/// Static function to Display Color Table in a pad.

  virtual void      DrawCrosshair();
/// Function called to draw a crosshair in the canvas
/// When moving the mouse in the canvas, a crosshair is drawn
///  - if the canvas fCrosshair = 1 , the crosshair spans the full canvas
///  - if the canvas fCrosshair > 1 , the crosshair spans only the pad

   TH1F             *DrawFrame(Double_t xmin, Double_t ymin, Double_t xmax, Double_t ymax, const char *title="");
///  Draw an empty pad frame with X and Y axis.
///   \param[in] xmin      X axis lower limit
///   \param[in] xmax      X axis upper limit
///   \param[in] ymin      Y axis lower limit
///   \param[in] ymax      Y axis upper limit
///   \param[in] title     Pad title.If title is of the form "stringt;stringx;stringy"
///                        the pad title is set to stringt, the x axis title to
///                        stringx, the y axis title to stringy.

   virtual void      ExecuteEventAxis(Int_t event, Int_t px, Int_t py, TAxis *axis);
/// Execute action corresponding to one event for a TAxis object (called by TAxis::ExecuteEvent.)
///  This member function is called when an axis is clicked with the locator
/// The axis range is set between the position where the mouse is pressed
/// and the position where it is released.
/// If the mouse position is outside the current axis range when it is released
/// the axis is unzoomed with the corresponding proportions.
/// Note that the mouse does not need to be in the pad or even canvas
/// when it is released.

   virtual TObject  *FindObject(const char *name) const;
/// Search if object named name is inside this pad or in pads inside this pad.
/// In case name is in several sub-pads the first one is returned.

   virtual TObject  *FindObject(const TObject *obj) const;
/// Search if obj is in pad or in pads inside this pad.
/// In case obj is in several sub-pads the first one is returned.

   virtual void      UseCurrentStyle();  // *MENU*
/// Force a copy of current style for all objects in pad.

   virtual Short_t   GetBorderMode() const { return fBorderMode;}
   virtual Short_t   GetBorderSize() const { return fBorderSize;}
   Int_t             GetCrosshair() const;
/// Return the crosshair type (from the mother canvas)
/// crosshair type = 0 means no crosshair.

   virtual Int_t     GetCanvasID() const;/// Get canvas identifier.
   virtual TCanvasImp *GetCanvasImp() const;/// Get canvas implementation pointer if any
   TFrame           *GetFrame();/// Get frame.
   virtual Int_t     GetEvent() const;/// Get Event.
   virtual Int_t     GetEventX() const;/// Get X event.
   virtual Int_t     GetEventY() const;/// Get Y event.
   virtual Color_t   GetHighLightColor() const;/// Get highlight color.
   virtual void      GetRange(Double_t &x1, Double_t &y1, Double_t &x2, Double_t &y2);/// Return pad world coordinates range.
   virtual void      GetRangeAxis(Double_t &xmin, Double_t &ymin, Double_t &xmax, Double_t &ymax);/// Return pad axis coordinates range.
   virtual void      GetPadPar(Double_t &xlow, Double_t &ylow, Double_t &xup, Double_t &yup);/// Return lower and upper bounds of the pad in NDC coordinates.
   Double_t          GetXlowNDC() const {return fXlowNDC;}
   Double_t          GetYlowNDC() const {return fYlowNDC;}
   Double_t          GetWNDC() const {return fWNDC;}
   Double_t          GetHNDC() const {return fHNDC;}
   virtual UInt_t    GetWw() const;/// Get Ww.
   virtual UInt_t    GetWh() const;/// Get Wh.
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
   static Int_t      GetMaxPickDistance();/// Static function (see also TPad::SetMaxPickDistance)
   TList            *GetListOfPrimitives() const {return fPrimitives;}
   TList            *GetListOfExecs() const {return fExecs;}
   virtual TObject  *GetPrimitive(const char *name) const;  //obsolete, use FindObject instead
   virtual TObject  *GetSelected() const;/// Get selected.
   virtual TVirtualPad  *GetPad(Int_t subpadnumber) const;/// Get a pointer to subpadnumber of this pad.
   virtual TObject  *GetPadPointer() const {return fPadPointer;}
   TVirtualPad      *GetPadSave() const;/// Get save pad.
   TVirtualPad      *GetSelectedPad() const;/// Get selected pad.
   Int_t             GetGLDevice();/// Get GL device.
   TView            *GetView() const {return fView;}
   TObject          *GetView3D() const {return fPadView3D;}// Return 3D View of this TPad
   Int_t             GetLogx() const {return fLogx;}
   Int_t             GetLogy() const {return fLogy;}
   Int_t             GetLogz() const {return fLogz;}
   virtual TVirtualPad *GetMother() const {return fMother;}
   const char       *GetName() const {return fName.Data();}
   const char       *GetTitle() const {return fTitle.Data();}
   virtual TCanvas  *GetCanvas() const { return fCanvas; }
   virtual TVirtualPad *GetVirtCanvas() const ;/// Get virtual canvas.
   virtual TVirtualPadPainter *GetPainter();/// Get pad painter from TCanvas.
   Int_t             GetPadPaint() const {return fPadPaint;}
   Int_t             GetPixmapID() const {return fPixmapID;}
   ULong_t           Hash() const { return fName.Hash(); }
   virtual Bool_t    HasCrosshair() const;/// Return kTRUE if the crosshair has been activated (via SetCrosshair).
   void              HighLight(Color_t col=kRed, Bool_t set=kTRUE);
/// Highlight pad.
/// do not highlight when printing on Postscript

   Bool_t            HasFixedAspectRatio() const { return fFixedAspectRatio; }
   virtual Bool_t    IsBatch() const;/// Is pad in batch mode ?
   virtual Bool_t    IsEditable() const {return fEditable;}
   Bool_t            IsFolder() const {return kTRUE;}
   Bool_t            IsModified() const {return fModified;}
   virtual Bool_t    IsRetained() const;/// Is pad retained ?
   virtual Bool_t    IsVertical() const {return !TestBit(kHori);}
   virtual void      ls(Option_t *option="") const;/// List all primitives in pad.
   void              Modified(Bool_t flag=1);  // *SIGNAL*   //  Set to true when pad is modified
   virtual Bool_t    OpaqueMoving() const;/// Is pad moving in opaque mode ?
   virtual Bool_t    OpaqueResizing() const;/// Is pad resizing in opaque mode ?
   Double_t          PadtoX(Double_t x) const;/// Convert x from pad to X.
   Double_t          PadtoY(Double_t y) const;/// Convert y from pad to Y.
   virtual void      Paint(Option_t *option="");/// Paint all primitives in pad.
   void              PaintBox(Double_t x1, Double_t y1, Double_t x2, Double_t y2, Option_t *option="");
/// Paint box in CurrentPad World coordinates.
///  - if option[0] = 's' the box is forced to be paint with style=0
///  - if option[0] = 'l' the box contour is drawn

   void              PaintFillArea(Int_t n, Float_t *x, Float_t *y, Option_t *option=""); // Obsolete
   void              PaintFillArea(Int_t n, Double_t *x, Double_t *y, Option_t *option=""); /// Paint fill area in CurrentPad World coordinates.
   void              PaintFillAreaHatches(Int_t n, Double_t *x, Double_t *y, Int_t FillStyle);
/// This function paints hatched fill area according to the FillStyle value
/// The convention for the Hatch is the following:
///     FillStyle = 3ijk
///  -  i (1-9) : specify the space between each hatch
///             1 = minimum  9 = maximum
///             the final spacing is i*GetHatchesSpacing(). The hatches spacing
///             is set by SetHatchesSpacing()
///  -  j (0-9) : specify angle between 0 and 90 degrees
///             * 0 = 0
///             * 1 = 10
///             * 2 = 20
///             * 3 = 30
///             * 4 = 45
///             * 5 = Not drawn
///             * 6 = 60
///             * 7 = 70
///             * 8 = 80
///             * 9 = 90
///  -  k (0-9) : specify angle between 90 and 180 degrees
///             * 0 = 180
///             * 1 = 170
///             * 2 = 160
///             * 3 = 150
///             * 4 = 135
///             * 5 = Not drawn
///             * 6 = 120
///             * 7 = 110
///             * 8 = 100
///             * 9 = 90

   void              PaintHatches(Double_t dy, Double_t angle, Int_t nn, Double_t *xx, Double_t *yy);
/// This routine draw hatches inclined with the
/// angle "angle" and spaced of "dy" in normalized device
/// coordinates in the surface defined by n,xx,yy.

   void              PaintPadFrame(Double_t xmin, Double_t ymin, Double_t xmax, Double_t ymax);/// Paint histogram/graph frame.
   void              PaintLine(Double_t x1, Double_t y1, Double_t x2, Double_t y2);/// Paint line in CurrentPad World coordinates.
   void              PaintLineNDC(Double_t u1, Double_t v1,Double_t u2, Double_t v2);/// Paint line in normalized coordinates.
   void              PaintLine3D(Float_t *p1, Float_t *p2);/// Paint 3-D line in the CurrentPad.
   void              PaintLine3D(Double_t *p1, Double_t *p2);/// Paint 3-D line in the CurrentPad.
   void              PaintPolyLine(Int_t n, Float_t *x, Float_t *y, Option_t *option="");
/// Paint polyline in CurrentPad World coordinates.

   void              PaintPolyLine(Int_t n, Double_t *x, Double_t *y, Option_t *option="");
/// Paint polyline in CurrentPad World coordinates.
///  If option[0] == 'C' no clipping

   void              PaintPolyLine3D(Int_t n, Double_t *p);/// Paint 3-D polyline in the CurrentPad.
   void              PaintPolyLineNDC(Int_t n, Double_t *x, Double_t *y, Option_t *option="");
/// Paint polyline in CurrentPad NDC coordinates.

   void              PaintPolyMarker(Int_t n, Float_t *x, Float_t *y, Option_t *option="");
/// Paint polymarker in CurrentPad World coordinates.

   void              PaintPolyMarker(Int_t n, Double_t *x, Double_t *y, Option_t *option="");
/// Paint polymarker in CurrentPad World coordinates.
   
   virtual void      PaintModified();
   void              PaintText(Double_t x, Double_t y, const char *text);/// Paint text in CurrentPad World coordinates.
   void              PaintText(Double_t x, Double_t y, const wchar_t *text);/// Paint text in CurrentPad World coordinates.
   void              PaintTextNDC(Double_t u, Double_t v, const char *text);/// Paint text in CurrentPad NDC coordinates.
   void              PaintTextNDC(Double_t u, Double_t v, const wchar_t *text);/// Paint text in CurrentPad NDC coordinates.
   virtual TPad     *Pick(Int_t px, Int_t py, TObjLink *&pickobj);
/// Search for an object at pixel position px,py.
///  Check if point is in this pad.
///  If yes, check if it is in one of the sub-pads
///  If found in the pad, compute closest distance of approach to each primitive.
///  If one distance of approach is found to be within the limit Distancemaximum
///  the corresponding primitive is selected and the routine returns.

   Double_t          PixeltoX(Int_t px);
   Double_t          PixeltoY(Int_t py);
   virtual void      PixeltoXY(Int_t xpixel, Int_t ypixel, Double_t &x, Double_t &y);
   virtual void      Pop();  // *MENU* /// Pop pad to the top of the stack.
   virtual void      Print(const char *filename="") const;
/// Save Pad contents in a file in one of various formats.
///  - if filename is "", the file produced is padname.ps
///  - if filename starts with a dot, the padname is added in front
///  - if filename contains .eps, an Encapsulated Postscript file is produced
///  - if filename contains .gif, a GIF file is produced
///  - if filename contains .gif+NN, an animated GIF file is produced
///       See comments in TASImage::WriteImage for meaning of NN and other
///       .gif suffix variants
///  - if filename contains .C or .cxx, a C++ macro file is produced
///  - if filename contains .root, a Root file is produced
///  - if filename contains .xml,  a XML file is produced
///  See comments in TPad::SaveAs or the TPad::Print function below

   virtual void      Print(const char *filename, Option_t *option);
/// Save Canvas contents in a file in one of various formats.
/// option can be:
///       -          0   - as "ps"
///       -        "ps"  - Postscript file is produced (see special cases below)
///       -   "Portrait" - Postscript file is produced (Portrait)
///       -  "Landscape" - Postscript file is produced (Landscape)
///       -     "Title:" - The character string after "Title:" becomes a table
///       -                of content entry (for PDF files).
///       -        "eps" - an Encapsulated Postscript file is produced
///       -    "Preview" - an Encapsulated Postscript file with preview is produced.
///       -        "pdf" - a PDF file is produced
///       -        "svg" - a SVG file is produced
///       -        "tex" - a TeX file is produced
///       -        "gif" - a GIF file is produced
///       -     "gif+NN" - an animated GIF file is produced, where NN is delay in 10ms units NOTE: See other variants for looping animation in TASImage::WriteImage
///       -        "xpm" - a XPM file is produced
///       -        "png" - a PNG file is produced
///       -        "jpg" - a JPEG file is produced. NOTE: JPEG's lossy compression will make all sharp edges fuzzy.
///        -      "tiff" - a TIFF file is produced
///        -       "cxx" - a C++ macro file is produced
///        -       "xml" - a XML file
///        -      "root" - a ROOT binary file
///     filename = 0 - filename  is defined by the GetName and its
///                    extension is defined with the option
/// When Postscript output is selected (ps, eps), the canvas is saved
/// to filename.ps or filename.eps. The aspect ratio of the canvas is preserved
/// on the Postscript file. When the "ps" option is selected, the Postscript
/// page will be landscape format if the canvas is in landscape format, otherwise
/// portrait format is selected.
/// The physical size of the Postscript page is the one selected in the
/// current style. This size can be modified via TStyle::SetPaperSize.

   virtual void      Range(Double_t x1, Double_t y1, Double_t x2, Double_t y2); // *MENU* *ARGS={x1=>fX1,y1=>fY1,x2=>fX2,y2=>fY2}
/// Set world coordinate system for the pad.
/// Emits signal "RangeChanged()", in the slot get the range
/// via GetRange().

   virtual void      RangeChanged() { Emit("RangeChanged()"); } // *SIGNAL*
   virtual void      RangeAxis(Double_t xmin, Double_t ymin, Double_t xmax, Double_t ymax);
/// Set axis coordinate system for the pad.
/// The axis coordinate system is a subset of the world coordinate system
/// xmin,ymin is the origin of the current coordinate system,
/// xmax is the end of the X axis, ymax is the end of the Y axis.
/// By default a margin of 10 per cent is left on all sides of the pad
/// Emits signal "RangeAxisChanged()", in the slot get the axis range
/// via GetRangeAxis().

   virtual void      RangeAxisChanged() { Emit("RangeAxisChanged()"); } // *SIGNAL*
   virtual void      RecursiveRemove(TObject *obj);/// Recursively remove object from a pad and its sub-pads.
   virtual void      RedrawAxis(Option_t *option="");
///  Redraw the frame axis
///  Redrawing axis may be necessary in case of superimposed histograms
///  when one or more histograms have a fill color
///  Instead of calling this function, it may be more convenient
///  to call directly h1->Draw("sameaxis") where h1 is the pointer
///  to the first histogram drawn in the pad.
///  By default, if the pad has the options gridx or/and gridy activated,
///  the grid is not drawn by this function.
///  if option="g" is specified, this will force the drawing of the grid
///  on top of the picture

   virtual void      ResetView3D(TObject *view=0){fPadView3D=view;}
   virtual void      ResizePad(Option_t *option="");/// Compute pad conversion coefficients.
   virtual void      SaveAs(const char *filename="",Option_t *option="") const; // *MENU*
/// Save Pad contents in a file in one of various formats.
///  - if filename is "", the file produced is padname.ps
///  - if filename starts with a dot, the padname is added in front
///  - if filename contains .eps, an Encapsulated Postscript file is produced
///  - if filename contains .pdf, a PDF file is produced
///  - if filename contains .svg, a SVG file is produced
///  - if filename contains .tex, a TeX file is produced
///  - if filename contains .gif, a GIF file is produced
///  - if filename contains .gif+NN, an  animated GIF file is produced See comments in TASImage::WriteImage for meaning of NN and other .gif sufix variants
///  - if filename contains .xpm, a XPM file is produced
///  - if filename contains .png, a PNG file is produced
///  - if filename contains .jpg, a JPEG file is produced NOTE: JPEG's lossy compression will make all sharp edges fuzzy.
///  - if filename contains .tiff, a TIFF file is produced
///  - if filename contains .C or .cxx, a C++ macro file is produced
///  - if filename contains .root, a Root file is produced
///  - if filename contains .xml, a XML file is produced
///   See comments in TPad::Print for the Postscript formats

   virtual void      SetBorderMode(Short_t bordermode) {fBorderMode = bordermode; Modified();} // *MENU*
   virtual void      SetBorderSize(Short_t bordersize) {fBorderSize = bordersize; Modified();} // *MENU*
   void              SetCanvas(TCanvas *c) { fCanvas = c; }
   virtual void      SetCanvasSize(UInt_t ww, UInt_t wh);/// Set canvas size.
   virtual void      SetCrosshair(Int_t crhair=1); // *TOGGLE*
/// Set crosshair active/inactive.
///  - If crhair != 0, a crosshair will be drawn in the pad and its sub-pads.
///  - If the canvas crhair = 1 , the crosshair spans the full canvas.
///  - If the canvas crhair > 1 , the crosshair spans only the pad.

   virtual void      SetCursor(ECursor cursor);/// Set cursor type.
   virtual void      SetDoubleBuffer(Int_t mode=1);/// Set double buffer mode ON or OFF.
   virtual void      SetDrawOption(Option_t *option="");
   virtual void      SetEditable(Bool_t mode=kTRUE); // *TOGGLE*
/// Set pad editable yes/no
/// If a pad is not editable:
/// - one cannot modify the pad and its objects via the mouse.
/// - one cannot add new objects to the pad

   virtual void      SetFixedAspectRatio(Bool_t fixed = kTRUE);  // *TOGGLE* /// Fix pad aspect ratio to current value if fixed is true.
   virtual void      SetGrid(Int_t valuex = 1, Int_t valuey = 1) {fGridx = valuex; fGridy = valuey; Modified();}
   virtual void      SetGridx(Int_t value = 1) {fGridx = value; Modified();} // *TOGGLE*
   virtual void      SetGridy(Int_t value = 1) {fGridy = value; Modified();} // *TOGGLE*
   virtual void      SetFillStyle(Style_t fstyle);
/// Override TAttFill::FillStyle for TPad because we want to handle style=0
/// as style 4000.

   virtual void      SetLogx(Int_t value = 1); // *TOGGLE*
/// Set Lin/Log scale for X
///  - value = 0 X scale will be linear
///  - value = 1 X scale will be logarithmic (base 10)
///  - value > 1 reserved for possible support of base e or other

   virtual void      SetLogy(Int_t value = 1); // *TOGGLE*
/// Set Lin/Log scale for Y
///  - value = 0 Y scale will be linear
///  - value = 1 Y scale will be logarithmic (base 10)
///  - value > 1 reserved for possible support of base e or other

   virtual void      SetLogz(Int_t value = 1); // *TOGGLE* /// Set Lin/Log scale for Z
   virtual void      SetNumber(Int_t number) {fNumber = number;}
   virtual void      SetPad(const char *name, const char *title,
                           Double_t xlow, Double_t ylow, Double_t xup,
                           Double_t yup, Color_t color=35,
                           Short_t bordersize=5, Short_t bordermode=-1);/// Set all pad parameters.
   virtual void      SetPad(Double_t xlow, Double_t ylow, Double_t xup, Double_t yup);
/// Set canvas range for pad and resize the pad. If the aspect ratio
/// was fixed before the call it will be un-fixed.

   virtual void      SetAttFillPS(Color_t color, Style_t style);/// Set postscript fill area attributes.
   virtual void      SetAttLinePS(Color_t color, Style_t style, Width_t lwidth);/// Set postscript line attributes.
   virtual void      SetAttMarkerPS(Color_t color, Style_t style, Size_t msize);/// Set postscript marker attributes.
   virtual void      SetAttTextPS(Int_t align, Float_t angle, Color_t color, Style_t font, Float_t tsize);/// Set postscript text attributes.
   static  void      SetMaxPickDistance(Int_t maxPick=5);
/// static function to set the maximum Pick Distance fgMaxPickDistance
/// This parameter is used in TPad::Pick to select an object if
/// its DistancetoPrimitive returns a value < fgMaxPickDistance
/// The default value is 5 pixels. Setting a smaller value will make
/// picking more precise but also more difficult

   virtual void      SetName(const char *name) {fName = name;} // *MENU*
   virtual void      SetSelected(TObject *obj);/// Set selected.
   virtual void      SetTicks(Int_t valuex = 1, Int_t valuey = 1) {fTickx = valuex; fTicky = valuey; Modified();}
   virtual void      SetTickx(Int_t value = 1) {fTickx = value; Modified();} // *TOGGLE*
   virtual void      SetTicky(Int_t value = 1) {fTicky = value; Modified();} // *TOGGLE*
   virtual void      SetTitle(const char *title="") {fTitle = title;}
   virtual void      SetTheta(Double_t theta=30) {fTheta = theta; Modified();}
   virtual void      SetPhi(Double_t phi=30) {fPhi = phi; Modified();}
   virtual void      SetToolTipText(const char *text, Long_t delayms = 1000);
/// Set tool tip text associated with this pad. The delay is in
/// milliseconds (minimum 250). To remove tool tip call method with
/// text = 0.

   virtual void      SetVertical(Bool_t vert=kTRUE);/// Set pad vertical (default) or horizontal
   virtual void      SetView(TView *view = 0);/// Set the current TView. Delete previous view if view=0
   virtual void      SetViewer3D(TVirtualViewer3D *viewer3d) {fViewer3D = viewer3d;}

   virtual void      SetGLDevice(Int_t dev) {fGLDevice = dev;}
   virtual void      SetCopyGLDevice(Bool_t copy) {fCopyGLDevice = copy;}

   virtual void      ShowGuidelines(TObject *object, const Int_t event, const char mode = 'i', const bool cling = true);
/// Shows lines to indicate if a TAttBBox2D object is aligned to
/// the center or to another object, shows distance arrows if two
/// objects on screen have the same distance to another object
/// Call from primitive in Execute Event, in ButtonMotion after
/// the new coordinates have been set, to 'stick'
/// once when button is up to delete lines
/// modes: t (Top), b (bottom), l (left), r (right), i (inside)
/// in resize modes (t,b,l,r) only size arrows are sticky
/// in mode, the function gets the point on the element that is clicked to
/// move (i) or resize (all others). 

   virtual void      Update();/// Update pad.
   Int_t             UtoAbsPixel(Double_t u) const {return Int_t(fUtoAbsPixelk + u*fUtoPixel);}
   Int_t             VtoAbsPixel(Double_t v) const {return Int_t(fVtoAbsPixelk + v*fVtoPixel);}
   Int_t             UtoPixel(Double_t u) const;
   Int_t             VtoPixel(Double_t v) const;
   virtual TObject  *WaitPrimitive(const char *pname="", const char *emode="");
/// Loop and sleep until a primitive with name=pname is found in the pad.
/// If emode is given, the editor is automatically set to emode, ie
/// it is not required to have the editor control bar.
/// The possible values for emode are:
///  - emode = "" (default). User will select the mode via the editor bar
///  - emode = "Arc", "Line", "Arrow", "Button", "Diamond", "Ellipse",
///  - emode = "Pad","pave", "PaveLabel","PaveText", "PavesText",
///  - emode = "PolyLine", "CurlyLine", "CurlyArc", "Text", "Marker", "CutG"
/// If emode is specified and it is not valid, "PolyLine" is assumed. If emode
/// is not specified or ="", an attempt is to use pname[1...]
///
/// for example if pname="TArc", emode="Arc" will be assumed.
/// When this function is called within a macro, the macro execution
/// is suspended until a primitive corresponding to the arguments
/// is found in the pad.
/// If CRTL/C is typed in the pad, the function returns 0.
/// While this function is executing, one can use the mouse, interact
/// with the graphics pads, use the Inspector, Browser, TreeViewer, etc.
/// Examples:
///   c1.WaitPrimitive();      // Return the first created primitive
///                            // whatever it is.
///                            // If a double-click with the mouse is executed
///                            // in the pad or any key pressed, the function
///                            // returns 0.
///   c1.WaitPrimitive("ggg"); // Set the editor in mode "PolyLine/Graph"
///                            // Create a polyline, then using the context
///                            // menu item "SetName", change the name
///                            // of the created TGraph to "ggg"
///   c1.WaitPrimitive("TArc");// Set the editor in mode "Arc". Returns
///                            // as soon as a TArc object is created.
///   c1.WaitPrimitive("lat","Text"); // Set the editor in Text/Latex mode.
///                            // Create a text object, then Set its name to "lat"

   Int_t             XtoAbsPixel(Double_t x) const;
   Int_t             YtoAbsPixel(Double_t y) const;
   Double_t          XtoPad(Double_t x) const;/// Convert x from X to pad.
   Double_t          YtoPad(Double_t y) const;/// Convert y from Y to pad.
   Int_t             XtoPixel(Double_t x) const;
   Int_t             YtoPixel(Double_t y) const;
   virtual void      XYtoAbsPixel(Double_t x, Double_t y, Int_t &xpixel, Int_t &ypixel) const;
   virtual void      XYtoPixel(Double_t x, Double_t y, Int_t &xpixel, Int_t &ypixel) const;

   virtual TObject  *CreateToolTip(const TBox *b, const char *text, Long_t delayms);/// Create a tool tip and return its pointer.
   virtual void      DeleteToolTip(TObject *tip);/// Delete tool tip object.
   virtual void      ResetToolTip(TObject *tip);
/// Reset tool tip, i.e. within time specified in CreateToolTip the
/// tool tip will pop up.

   virtual void      CloseToolTip(TObject *tip);/// Hide tool tip.

   virtual void      x3d(Option_t *type=""); // Depreciated
/// Deprecated: use TPad::GetViewer3D() instead

   virtual TVirtualViewer3D *GetViewer3D(Option_t * type = "");
/// Create/obtain handle to 3D viewer. Valid types are:
///  - 'pad' - pad drawing via TViewer3DPad
/// any others registered with plugin manager supporting TVirtualViewer3D
/// If an invalid/null type is requested then the current viewer is returned
/// (if any), otherwise a default 'pad' type is returned

   virtual Bool_t            HasViewer3D() const { return (fViewer3D); }
   virtual void              ReleaseViewer3D(Option_t * type = "");/// Release current (external) viewer

   virtual Rectangle_t  GetBBox();/// Return the bounding Box of the Pad
   virtual TPoint       GetBBoxCenter();/// Return the center of the Pad as TPoint in pixels

   virtual void         SetBBoxCenter(const TPoint &p);/// Set center of the Pad

   virtual void         SetBBoxCenterX(const Int_t x);
/// Set X coordinate of the center of the Pad

   virtual void         SetBBoxCenterY(const Int_t y);
/// Set Y coordinate of the center of the Pad

   virtual void         SetBBoxX1(const Int_t x);
/// Set lefthandside of BoundingBox to a value
/// (resize in x direction on left)

   virtual void         SetBBoxX2(const Int_t x);
/// Set right hand side of BoundingBox to a value
/// (resize in x direction on right)

   virtual void         SetBBoxY1(const Int_t y);
/// Set top of BoundingBox to a value (resize in y direction on top)

   virtual void         SetBBoxY2(const Int_t y);
/// Set bottom of BoundingBox to a value
/// (resize in y direction on bottom)

   virtual void      RecordPave(const TObject *obj);              // *SIGNAL*
/// Emit RecordPave() signal.

   virtual void      RecordLatex(const TObject *obj);             // *SIGNAL*
/// Emit RecordLatex() signal.

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

```cpp
/// The following macro waits for 10 primitives of any type to be created.

   TCanvas c1("c1");
   TObject *obj;
   for (Int_t i=0;i<10;i++) {
      obj = gPad->WaitPrimitive();
      if (!obj) break;
      printf("Loop i=%d, found objIsA=%s, name=%s\n",
         i,obj->ClassName(),obj->GetName());
   }
```

```cpp
/// Function called to draw a crosshair in the canvas
/// When moving the mouse in the canvas, a crosshair is drawn
///  - if the canvas fCrosshair = 1 , the crosshair spans the full canvas
///  - if the canvas fCrosshair > 1 , the crosshair spans only the pad

TFile f("hsimple.root");
hpxpy.Draw();
c1.SetCrosshair();
```

```cpp
///  The following examples of TExec commands are provided in the tutorials:

Root > TFile f("hsimple.root")
Root > hpx.Draw()
Root > c1.AddExec("ex1",".x exec1.C")

/// At this point you can use the mouse to click on the contour of
/// the histogram hpx. When the mouse is clicked, the bin number and its
/// contents are printed.

Root > TFile f("hsimple.root")
Root > hpxpy.Draw()
Root > c1.AddExec("ex2",".x exec2.C")
```



```cpp
/// The physical size of the Postscript page is the one selected in the
/// current style. This size can be modified via TStyle::SetPaperSize.

gStyle->SetPaperSize(TStyle::kA4);  //default
gStyle->SetPaperSize(TStyle::kUSLetter);

/// where TStyle::kA4 and TStyle::kUSLetter are defined in the enum
/// EPaperSize in TStyle.h

/// An alternative is to call:

gStyle->SetPaperSize(20,26);  same as kA4
gStyle->SetPaperSize(20,24);  same as kUSLetter

///   The above numbers take into account some margins and are in centimeters.

///  The "Preview" option allows to generate a preview (in the TIFF format) within
///  the Encapsulated Postscript file. This preview can be used by programs like
///  MSWord to visualize the picture on screen. The "Preview" option relies on the
///  epstool command (http://www.cs.wisc.edu/~ghost/gsview/epstool.htm).

canvas->Print("example.eps","Preview");

///  To generate a Postscript file containing more than one picture, see
///  class TPostScript.
///
/// ### Writing several canvases to the same Postscript or PDF file:
///
///  - if the Postscript or PDF file name finishes with "(", the file is not closed
///  - if the Postscript or PDF file name finishes with ")" and the file has been opened
///    with "(", the file is closed.

TCanvas c1("c1");
h1.Draw();
c1.Print("c1.ps("); //write canvas and keep the ps file open
h2.Draw();
c1.Print("c1.ps"); canvas is added to "c1.ps"
h3.Draw();
c1.Print("c1.ps)"); canvas is added to "c1.ps" and ps file is closed


/// In the previous example replacing "ps" by "pdf" will create a multi-pages PDF file.

/// Note that the following sequence writes the canvas to "c1.ps" and closes the ps file.:

TCanvas c1("c1");
h1.Draw();
c1.Print("c1.ps");

///  The TCanvas::Print("file.ps(") mechanism is very useful, but it can be
///  a little inconvenient to have the action of opening/closing a file
///  being atomic with printing a page. Particularly if pages are being
///  generated in some loop one needs to detect the special cases of first
///  and last page and then munge the argument to Print() accordingly.
///
///  The "[" and "]" can be used instead of "(" and ")".

c1.Print("file.ps[");   // No actual print, just open file.ps
for (int i=0; i<10; ++i) {
  // fill canvas for context i
  // ...

  c1.Print("file.ps");  // actually print canvas to file
}// end loop
c1.Print("file.ps]");   // No actual print, just close.


/// As before, the same macro is valid for PDF files.
///
/// It is possible to print a canvas into an animated GIF file by specifying the
/// file name as "myfile.gif+" or "myfile.gif+NN", where NN*10ms is delay
/// between the subimages' display. If NN is omitted the delay between
/// subimages is zero. Each picture is added in the animation thanks to a loop
/// similar to the following one:

for (int i=0; i<10; ++i) {
  // fill canvas for context i
  // ...
  c1.Print("file.gif+5");  // print canvas to GIF file with 50ms delays
 }// end loop

/// The delay between each frame must be specified in each Print() statement.
/// If the file "myfile.gif" already exists, the new frame are appended at
/// the end of the file. To avoid this, delete it first with gSystem->Unlink(myfile.gif);
/// If you want the gif file to repeat or loop forever, check TASImage::WriteImage documentation
```


## example



<!-- TPad.md ends here -->
