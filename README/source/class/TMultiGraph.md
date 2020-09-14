<!-- TMultiGraph.md --- 
;; 
;; Description: 
;; Author: Hongyi Wu(吴鸿毅)
;; Email: wuhongyi@qq.com 
;; Created: 五 12月  5 11:52:37 2014 (+0800)
;; Last-Updated: 六 10月 29 21:32:29 2016 (+0800)
;;           By: Hongyi Wu(吴鸿毅)
;;     Update #: 4
;; URL: http://wuhongyi.cn -->

# TMultiGraph

继承 TNamed

## class

```cpp
   TMultiGraph();
   TMultiGraph(const char *name, const char *title);
   virtual ~TMultiGraph();

   virtual void      Add(TGraph *graph, Option_t *chopt="");
/// Add a new graph to the list of graphs.
/// Note that the graph is now owned by the TMultigraph.
/// Deleting the TMultiGraph object will automatically delete the graphs.
/// You should not delete the graphs when the TMultigraph is still active.

   virtual void      Add(TMultiGraph *multigraph, Option_t *chopt="");
/// Add all the graphs in "multigraph" to the list of graphs.
/// If "chopt" is defined all the graphs in "multigraph" will be added with
/// the "chopt" option.
/// If "chopt" is undefined each graph will be added with the option it had
/// in "multigraph".

   virtual void      Browse(TBrowser *b);/// Browse multigraph.
   virtual Int_t     DistancetoPrimitive(Int_t px, Int_t py);
/// Compute distance from point px,py to each graph.

   virtual void      Draw(Option_t *chopt="");
/// Draw this multigraph with its current attributes.
///   Options to draw a graph are described in TGraphPainter.
///  The drawing option for each TGraph may be specified as an optional
///  second argument of the Add function. You can use GetGraphDrawOption
///  to return this option.
///  If a draw option is specified, it will be used to draw the graph,
///  otherwise the graph will be drawn with the option specified in
///  TMultiGraph::Draw. Use GetDrawOption to return the option specified
///  when drawing the TMultiGraph.

   virtual TFitResultPtr Fit(const char *formula ,Option_t *option="" ,Option_t *goption="", Axis_t xmin=0, Axis_t xmax=0);
/// Fit this graph with function with name fname.
///  interface to TF1::Fit(TF1 *f1...

   virtual TFitResultPtr Fit(TF1 *f1 ,Option_t *option="" ,Option_t *goption="", Axis_t rxmin=0, Axis_t rxmax=0);
/// Fit this multigraph with function f1.
///   In this function all graphs of the multigraph are fitted simultaneously
///   f1 is an already predefined function created by TF1.
///   Predefined functions such as gaus, expo and poln are automatically
///   created by ROOT.
///
///   The list of fit options is given in parameter option.
///      option = "W"  Set all errors to 1
///             = "U" Use a User specified fitting algorithm (via SetFCN)
///             = "Q" Quiet mode (minimum printing)
///             = "V" Verbose mode (default is between Q and V)
///             = "B" Use this option when you want to fix one or more parameters
///                   and the fitting function is like "gaus","expo","poln","landau".
///             = "R" Use the Range specified in the function range
///             = "N" Do not store the graphics function, do not draw
///             = "0" Do not plot the result of the fit. By default the fitted function
///                   is drawn unless the option"N" above is specified.
///             = "+" Add this new fitted function to the list of fitted functions
///                   (by default, any previous function is deleted)
///             = "C" In case of linear fitting, not calculate the chisquare
///                    (saves time)
///             = "F" If fitting a polN, switch to minuit fitter
///             = "ROB" In case of linear fitting, compute the LTS regression
///                     coefficients (robust(resistant) regression), using
///                     the default fraction of good points
///               "ROB=0.x" - compute the LTS regression coefficients, using
///                           0.x as a fraction of good points
///
///   When the fit is drawn (by default), the parameter goption may be used
///   to specify a list of graphics options. See TGraph::Paint for a complete
///   list of these options.
///
///   In order to use the Range option, one must first create a function
///   with the expression to be fitted. For example, if your graph
///   has a defined range between -4 and 4 and you want to fit a gaussian
///   only in the interval 1 to 3, you can do:
///        TF1 *f1 = new TF1("f1","gaus",1,3);
///        graph->Fit("f1","R");
///
///   who is calling this function
///   ============================
///   Note that this function is called when calling TGraphErrors::Fit
///   or TGraphAsymmErrors::Fit ot TGraphBentErrors::Fit
///   see the discussion below on the errors calulation.
///
///   Setting initial conditions
///   ==========================
///   Parameters must be initialized before invoking the Fit function.
///   The setting of the parameter initial values is automatic for the
///   predefined functions : poln, expo, gaus, landau. One can however disable
///   this automatic computation by specifying the option "B".
///   You can specify boundary limits for some or all parameters via
///        f1->SetParLimits(p_number, parmin, parmax);
///   if parmin>=parmax, the parameter is fixed
///   Note that you are not forced to fix the limits for all parameters.
///   For example, if you fit a function with 6 parameters, you can do:
///     func->SetParameters(0,3.1,1.e-6,0.1,-8,100);
///     func->SetParLimits(4,-10,-4);
///     func->SetParLimits(5, 1,1);
///   With this setup, parameters 0->3 can vary freely
///   Parameter 4 has boundaries [-10,-4] with initial value -8
///   Parameter 5 is fixed to 100.
///
///  Fit range
///  =========
///  The fit range can be specified in two ways:
///    - specify rxmax > rxmin (default is rxmin=rxmax=0)
///    - specify the option "R". In this case, the function will be taken
///      instead of the full graph range.
///
///  Changing the fitting function
///  =============================
///   By default a chi2 fitting function is used for fitting the TGraphs's.
///   The function is implemented in FitUtil::EvaluateChi2.
///   In case of TGraphErrors an effective chi2 is used
///   (see TGraphErrors fit in TGraph::Fit) and is implemented in
///   FitUtil::EvaluateChi2Effective
///   To specify a User defined fitting function, specify option "U" and
///   call the following functions:
///     TVirtualFitter::Fitter(mygraph)->SetFCN(MyFittingFunction)
///   where MyFittingFunction is of type:
///   extern void MyFittingFunction(Int_t &npar, Double_t *gin, Double_t &f, Double_t *u, Int_t flag);
///
///  Access to the fit result
///  ========================
///  The function returns a TFitResultPtr which can hold a  pointer to a TFitResult object.
///  By default the TFitResultPtr contains only the status of the fit and it converts
///  automatically to an integer. If the option "S" is instead used, TFitResultPtr contains
///  the TFitResult and behaves as a smart pointer to it. For example one can do:
///     TFitResultPtr r = graph->Fit("myFunc","S");
///     TMatrixDSym cov = r->GetCovarianceMatrix();  //  to access the covariance matrix
///     Double_t par0   = r->Parameter(0); // retrieve the value for the parameter 0
///     Double_t err0   = r->ParError(0); // retrieve the error for the parameter 0
///     r->Print("V");     // print full information of fit including covariance matrix
///     r->Write();        // store the result in a file
///
///   The fit parameters, error and chi2 (but not covariance matrix) can be retrieved also
///   from the fitted function.
///
///
///   Associated functions
///   ====================
///  One or more object (typically a TF1*) can be added to the list
///  of functions (fFunctions) associated to each graph.
///  When TGraph::Fit is invoked, the fitted function is added to this list.
///  Given a graph gr, one can retrieve an associated function
///  with:  TF1 *myfunc = gr->GetFunction("myfunc");
///
///  If the graph is made persistent, the list of
///  associated functions is also persistent. Given a pointer (see above)
///  to an associated function myfunc, one can retrieve the function/fit
///  parameters with calls such as:
///    Double_t chi2 = myfunc->GetChisquare();
///    Double_t par0 = myfunc->GetParameter(0); //value of 1st parameter
///    Double_t err0 = myfunc->GetParError(0);  //error on first parameter
///
///   Fit Statistics
///   ==============
///  You can change the statistics box to display the fit parameters with
///  the TStyle::SetOptFit(mode) method. This mode has four digits.
///  mode = pcev  (default = 0111)
///    v = 1;  print name/values of parameters
///    e = 1;  print errors (if e=1, v must be 1)
///    c = 1;  print Chisquare/Number of degress of freedom
///    p = 1;  print Probability
///
///  For example: gStyle->SetOptFit(1011);
///  prints the fit probability, parameter names/values, and errors.
///  You can change the position of the statistics box with these lines
///  (where g is a pointer to the TGraph):
///
///  Root > TPaveStats *st = (TPaveStats*)g->GetListOfFunctions()->FindObject("stats")
///  Root > st->SetX1NDC(newx1); //new x start position
///  Root > st->SetX2NDC(newx2); //new x end position

   virtual void      FitPanel(); // *MENU*
/// Display a panel with all histogram fit options.
/// See class TFitPanel for example

   virtual Option_t *GetGraphDrawOption(const TGraph *gr) const;
/// Return the draw option for the TGraph gr in this TMultiGraph.
/// The return option is the one specified when calling TMultiGraph::Add(gr,option).

   virtual void      LeastSquareLinearFit(Int_t ndata, Double_t &a0, Double_t &a1, Int_t &ifail, Double_t xmin, Double_t xmax);
/// Least square linear fit without weights.
///  Fit a straight line (a0 + a1*x) to the data in this graph.
///  ndata:  number of points to fit
///  first:  first point number to fit
///  last:   last point to fit O(ndata should be last-first
///  ifail:  return parameter indicating the status of the fit (ifail=0, fit is OK)
///   extracted from CERNLIB LLSQ: Translated to C++ by Rene Brun

   virtual void      LeastSquareFit(Int_t m, Double_t *a, Double_t xmin, Double_t xmax);
/// Least squares lpolynomial fitting without weights.
///  m     number of parameters
///  a     array of parameters
///  first 1st point number to fit (default =0)
///  last  last point number to fit (default=fNpoints-1)
///   based on CERNLIB routine LSQ: Translated to C++ by Rene Brun

   virtual void      InitPolynom(Double_t xmin, Double_t xmax);
/// Compute Initial values of parameters for a polynom.
   
   virtual void      InitExpo(Double_t xmin, Double_t xmax);
/// Compute Initial values of parameters for an exponential.

   virtual void      InitGaus(Double_t xmin, Double_t xmax);
/// Compute Initial values of parameters for a gaussian.

   virtual Int_t     IsInside(Double_t x, Double_t y) const;
/// Return 1 if the point (x,y) is inside one of the graphs 0 otherwise.

   TH1F             *GetHistogram() const;
/// Returns a pointer to the histogram used to draw the axis.
/// Takes into account the two following cases.
///    1- option 'A' was specified in TMultiGraph::Draw. Return fHistogram
///    2- user had called TPad::DrawFrame. return pointer to hframe histogram

   TF1              *GetFunction(const char *name) const;
/// Return pointer to function with name.
/// Functions such as TGraph::Fit store the fitted function in the list of
/// functions of this graph.

   TList            *GetListOfGraphs() const { return fGraphs; }
   TList            *GetListOfFunctions();  // non const method (create list if empty)
/// Return pointer to list of functions.
/// If pointer is null create the list

   const TList      *GetListOfFunctions() const { return fFunctions; }
   TAxis            *GetXaxis() const;
/// Get x axis of the graph.
/// This method returns a valid axis only after the TMultigraph has been drawn.

   TAxis            *GetYaxis() const;
/// Get y axis of the graph.
/// This method returns a valid axis only after the TMultigraph has been drawn.

   virtual void      Paint(Option_t *chopt="");/// Paint all the graphs of this multigraph.
   void              PaintPads(Option_t *chopt="");/// Divides the active pad and draws all Graphs in the Multigraph separately.
   void              PaintPolyLine3D(Option_t *chopt="");/// Paint all the graphs of this multigraph as 3D lines.
   virtual void      Print(Option_t *chopt="") const;/// Print the list of graphs.
   virtual void      RecursiveRemove(TObject *obj);
/// Recursively remove this object from a list. Typically implemented
/// by classes that can contain multiple references to a same object.

   virtual void      SavePrimitive(std::ostream &out, Option_t *option = "");/// Save primitive as a C++ statement(s) on output stream out.
   virtual void      SetMaximum(Double_t maximum=-1111); /// Set multigraph maximum.
   virtual void      SetMinimum(Double_t minimum=-1111); /// Set multigraph minimum.
```

## code

```cpp
// A TMultiGraph is a collection of TGraph (or derived) objects. It allows to
// manipulate a set of graphs as a single entity. In particular, when drawn,
// the X and Y axis ranges are automatically computed such as all the graphs
// will be visible.

TGraph *gr1 = new TGraph(...
TGraphErrors *gr2 = new TGraphErrors(...
TMultiGraph *mg = new TMultiGraph();
mg->Add(gr1,"lp");
mg->Add(gr2,"cp");
mg->Draw("a");
```


```cpp
// The number of graphs in a multigraph can be retrieve with:

mg->GetListOfGraphs()->GetSize();
```

```cpp
// The axis titles can be modified the following way:

TMultiGraph *mg = new TMultiGraph;
mg->SetTitle("title;xaxis title; yaxis title");
mg->Add(g1);
mg->Add(g2);
mg->Draw("apl");
```


## example

```cpp
//Draw three graphs with an exclusion zone.一个画板上画出多个Graph。
   
TCanvas *c1 = new TCanvas("c1","Exclusion graphs examples",200,10,600,400);
c1->SetGrid();

TMultiGraph *mg = new TMultiGraph();
mg->SetTitle("Exclusion graphs");

const Int_t n = 35;
Double_t x1[n], x2[n], x3[n], y1[n], y2[n], y3[n];
for (Int_t i=0;i<n;i++) {
  x1[i]  = i*0.1;
  x2[i]  = x1[i];
  x3[i]  = x1[i]+.5;
  y1[i] = 10*sin(x1[i]);
  y2[i] = 10*cos(x1[i]);
  y3[i] = 10*sin(x1[i])-2;
 }

TGraph *gr1 = new TGraph(n,x1,y1);
gr1->SetLineColor(2);
gr1->SetLineWidth(1504);
gr1->SetFillStyle(3005);

TGraph *gr2 = new TGraph(n,x2,y2);
gr2->SetLineColor(4);
gr2->SetLineWidth(-2002);
gr2->SetFillStyle(3004);
gr2->SetFillColor(9);

TGraph *gr3 = new TGraph(n,x3,y3);
gr3->SetLineColor(5);
gr3->SetLineWidth(-802);
gr3->SetFillStyle(3002);
gr3->SetFillColor(2);

mg->Add(gr1);
mg->Add(gr2);
mg->Add(gr3);
mg->Draw("AC");
```


```cpp
   c0 = new TCanvas("c1","multigraph L3",200,10,700,500);
   c0->SetFrameFillColor(30);

   TMultiGraph *mg = new TMultiGraph();

   TGraph *gr1 = new TGraph(); gr1->SetLineColor(kBlue);
   TGraph *gr2 = new TGraph(); gr2->SetLineColor(kRed);
   TGraph *gr3 = new TGraph(); gr3->SetLineColor(kGreen);
   TGraph *gr4 = new TGraph(); gr4->SetLineColor(kOrange);

   Double_t dx = 6.28/100;
   Double_t x  = -3.14;

   for (int i=0; i<=100; i++) {
      x = x+dx;
      gr1->SetPoint(i,x,2.*TMath::Sin(x));
      gr2->SetPoint(i,x,TMath::Cos(x));
      gr3->SetPoint(i,x,TMath::Cos(x*x));
      gr4->SetPoint(i,x,TMath::Cos(x*x*x));
   }

   mg->Add(gr4); gr4->SetTitle("Cos(x*x*x)"); gr4->SetLineWidth(3);
   mg->Add(gr3); gr3->SetTitle("Cos(x*x)")  ; gr3->SetLineWidth(3);
   mg->Add(gr2); gr2->SetTitle("Cos(x)")    ; gr2->SetLineWidth(3);
   mg->Add(gr1); gr1->SetTitle("2*Sin(x)")  ; gr1->SetLineWidth(3);

   mg->Draw("a fb l3d");
   return c0;
```

```cpp
   TCanvas *c1 = new TCanvas("c1","c1",600,400);

   Double_t px1[2] = {2.,4.};
   Double_t dx1[2] = {0.1,0.1};
   Double_t py1[2] = {2.1,4.0};
   Double_t dy1[2] = {0.3,0.2};

   Double_t px2[2] = {3.,5.};
   Double_t dx2[2] = {0.1,0.1};
   Double_t py2[2] = {3.2,4.8};
   Double_t dy2[2] = {0.3,0.2};

   gStyle->SetOptFit(0001);

   TGraphErrors *g1 = new TGraphErrors(2,px1,py1,dx1,dy1);
   g1->SetMarkerStyle(21);
   g1->SetMarkerColor(2);

   TGraphErrors *g2 = new TGraphErrors(2,px2,py2,dx2,dy2);
   g2->SetMarkerStyle(22);
   g2->SetMarkerColor(3);

   TMultiGraph *g = new TMultiGraph();
   g->Add(g1);
   g->Add(g2);

   g->Draw("AP");

   g->Fit("pol1","FQ");
   return c1;
```

```cpp
// The axis limits can be changed the like for TGraph. The same methods apply on the multigraph.
// Note the two differents ways to change limits on X and Y axis.

   TCanvas *c2 = new TCanvas("c2","c2",600,400);

   TGraph *g[3];
   Double_t x[10] = {0,1,2,3,4,5,6,7,8,9};
   Double_t y[10] = {1,2,3,4,5,5,4,3,2,1};
   TMultiGraph *mg = new TMultiGraph();
   for (int i=0; i<3; i++) {
      g[i] = new TGraph(10, x, y);
      g[i]->SetMarkerStyle(20);
      g[i]->SetMarkerColor(i+2);
      for (int j=0; j<10; j++) y[j] = y[j]-1;
      mg->Add(g[i]);
   }
   mg->Draw("APL");
   mg->GetXaxis()->SetTitle("E_{#gamma} (GeV)");
   mg->GetYaxis()->SetTitle("Coefficients");

   // Change the axis limits
   gPad->Modified();
   mg->GetXaxis()->SetLimits(1.5,7.5);
   mg->SetMinimum(0.);
   mg->SetMaximum(10.);
```

```cpp
// The method TPad::BuildLegend is able to extract the graphs inside a
// multigraph. The following example demonstrate this.

   TCanvas *c3 = new TCanvas("c3","c3",600, 400);

   TMultiGraph * mg = new TMultiGraph("mg","mg");

   const Int_t size = 10;

   double px[size];
   double py1[size];
   double py2[size];
   double py3[size];

   for ( int i = 0; i <  size ; ++i ) {
      px[i] = i;
      py1[i] = size - i;
      py2[i] = size - 0.5 * i;
      py3[i] = size - 0.6 * i;
   }

   TGraph * gr1 = new TGraph( size, px, py1 );
   gr1->SetName("gr1");
   gr1->SetTitle("graph 1");
   gr1->SetMarkerStyle(21);
   gr1->SetDrawOption("AP");
   gr1->SetLineColor(2);
   gr1->SetLineWidth(4);
   gr1->SetFillStyle(0);

   TGraph * gr2 = new TGraph( size, px, py2 );
   gr2->SetName("gr2");
   gr2->SetTitle("graph 2");
   gr2->SetMarkerStyle(22);
   gr2->SetMarkerColor(2);
   gr2->SetDrawOption("P");
   gr2->SetLineColor(3);
   gr2->SetLineWidth(4);
   gr2->SetFillStyle(0);

   TGraph * gr3 = new TGraph( size, px, py3 );
   gr3->SetName("gr3");
   gr3->SetTitle("graph 3");
   gr3->SetMarkerStyle(23);
   gr3->SetLineColor(4);
   gr3->SetLineWidth(4);
   gr3->SetFillStyle(0);

   mg->Add( gr1 );
   mg->Add( gr2 );

   gr3->Draw("ALP");
   mg->Draw("LP");
   c3->BuildLegend();
```



<!-- TMultiGraph.md ends here -->
